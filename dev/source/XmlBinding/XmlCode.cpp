﻿#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include "XmlCode.h"
#include <QDebug>
#include <iostream>
#include "XmlHelper.h"
using namespace std;


CXmlCode::CXmlCode(void)
{
	m_iedcfgDoc = new QDomDocument();
}


CXmlCode::~CXmlCode(void)
{
	delete m_iedcfgDoc;
}

bool CXmlCode::readfile( const QString& filename )
{
	QFile file(filename);
	QString errorMsg;
	int errorLine = 0;
	int errorColumn = 0;

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;

	if (m_iedcfgDoc == NULL)
		return false;

	bool flag = m_iedcfgDoc->setContent(&file,&errorMsg,&errorLine,&errorColumn);
	if (!flag)
	{
		cout << errorMsg.toStdString() 
			<< "(line " << errorLine << "column " << errorColumn <<")" << endl;
		file.close();
		return false;
	}
	file.close();
	return true;
}

bool CXmlCode::build()
{
	if (m_iedcfgDoc == NULL)
		return false;

	QDomElement docElem = m_iedcfgDoc->documentElement();
	// cout << "root:" << docElem.tagName().toStdString() <<endl;
	QDomNamedNodeMap attributes = docElem.attributes();
	int c = attributes.count();
	// 移除根数据属性
	for (int i = 0; i < c; ++i)
	{
		QDomNode attNode = attributes.item(0);
		QDomAttr attr = attNode.toAttr();
		docElem.removeAttribute(attr.name());
	}
	generateDocment(docElem);

	generateUnknownTag();

	generateCls(docElem);

	return true;
}

QString CXmlCode::outPath() const
{
	QString path = CXmlCodeBase::outPath() + "/code";
	QDir dir;
	if (!dir.exists(path))
	{
		if (!dir.mkdir(path))
			return CXmlCodeBase::outPath();
	}

	return path;
}

void CXmlCode::generateDocment(QDomNode node)
{
	QString hCode;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/Document.header.tpl", hCode))
		return ;

	QString libName = libraryName();
	if (!libName.isEmpty())
	{
		libName[0] = libName[0].toUpper();
	}

	hCode.replace("$(LIBNAME_UPPERCASE)", libName.toUpper());
	QString rootname;
	QDomElement ele = node.toElement();
	if (ele.isNull())
		return ;
	rootname = ele.tagName();

	if (rootname.isEmpty())
		return ;

	hCode.replace("$(ROOTNAME)", rootname + "Tag");
	hCode.replace("$(ROOTNAME_K)", rootname);
	hCode.replace("$(LIBNAME)", libName);

	if (!CXmlHelper::writeCode(outPath() + "/" + libName + "Document.h", hCode))
		return ;

	QString sCode;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/Document.source.tpl", sCode))
		return ;

	sCode.replace("$(LIBNAME)", libName);
	sCode.replace("$(ROOTNAME)", rootname + "Tag");
	sCode.replace("$(ROOTNAME_K)", rootname);

	CXmlHelper::writeCode(outPath() + "/" + libName + "Document.cpp", sCode);
}

void CXmlCode::generateUnknownTag()
{
	QString libn = libraryName();
	if (libn.isEmpty())
		return ;
	
	libn[0] = libn[0].toUpper();

	QString hCode;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/UnknownTag.header.tpl", hCode))
		return ;

	hCode.replace("$(LIBNAME)", libn);

	if (!CXmlHelper::writeCode(outPath() + "/" + libn + "UnknownTag.h", hCode))
		return ;

	QString sCode;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/UnknownTag.source.tpl", sCode))
		return ;

	sCode.replace("$(LIBNAME)", libn);

	if (!CXmlHelper::writeCode(outPath() + "/" + libn + "UnknownTag.cpp", sCode))
		return ;
}

void CXmlCode::generateCls( QDomNode node )
{
	QList<QString> childrenNames;	//	类名列表
	QList<QString> attributesNames;	// 属性名列表

	if (node.isNull())
		return ;
	QDomElement element = node.toElement();
	if (element.isNull())
		return ;

	// 处理成员
	QDomNodeList nodes = node.childNodes();
	int c = nodes.count();
	for (int i = 0; i<c; ++i)
	{
		QDomNode n = nodes.item(i);
		QDomElement e = n.toElement();
		if (!e.isNull())
		{
			QString childName = e.tagName()+"Tag";
			if (!childrenNames.contains(childName))
				childrenNames.append(childName);
			// cout << "ele:" << e.tagName().toStdString() << endl;
		}
		generateCls(n);
	}

	// 处理属性
	QDomNamedNodeMap attributes = node.attributes();
	int count = attributes.count();
	for (int i = 0; i <= count-1 ; ++i)
	{
		QDomNode attNode = attributes.item(i);
		QDomAttr attr = attNode.toAttr();
		attributesNames.append(attr.name());
	}

	// 生成类代码
	QString clsName = element.tagName()+"Tag";
	if (!generateClsCode(clsName,childrenNames,attributesNames))
		cout << "C" << clsName.toStdString() << "class generate error" <<endl;

	// 生成all
	QString allCode;
	allCode = "#ifndef " + libraryName().toUpper() + "_ALLTAGS_H__\n";
	allCode = allCode + "#define " + libraryName().toUpper() + "_ALLTAGS_H__\n\n";
	foreach (QString clsTag, m_haveCode)
	{
		if (clsTag.isEmpty())
			continue;
		allCode = allCode + "#include \"" + clsTag.right(clsTag.size()-1) + ".h\"\n\n";
	}
	allCode = allCode + "#endif //" + libraryName().toUpper() + "_ALLTAGS_H__";

	CXmlHelper::writeCode(outPath() + "/" + libraryName() + "_AllTags.h", allCode);
}

bool CXmlCode::generateClsCode( const QString clsName,const QList<QString> childrenNames,const QList<QString> attrNames )
{
	if (m_haveCode.contains(clsName))
		return true;
	m_haveCode.append(clsName);
	
	bool flag = true;
	
	if (!genClsCodeH(clsName,childrenNames,attrNames))
	{
		flag =  false;
	}

	if (!genClsCodeCpp(clsName,childrenNames,attrNames))
	{
		flag = false;
	}
	return flag;
}

bool CXmlCode::genClsCodeH( const QString clsName,const QList<QString> childrenNames,const QList<QString> attrNames )
{
	QString clsCode;
	QString tmp;

	QString filname = templateDir() + "/ComplexType.header.tpl";
	if (!CXmlHelper::readCodetemplates(filname, clsCode))
	{
		return false;
	}

	// 宏处理
	clsCode.replace("$(TYPENAME_U)",clsName);

	// 头文件处理
	QString includesCode;
	includesCode = "#include <QList>\n";
	includesCode += "#include \"" + libraryName() + "_global.h\"\n";
	includesCode += "#include \"xsdcomplextype.h\"\n";
	clsCode.replace("$(INCLUDES)",includesCode);

		// 向前声明
	QString preDeclareCode;
	foreach (QString child,childrenNames)
	{
		// includesCode += "#include \""+child+".h\"\n";
		preDeclareCode += "class C" + child +";\n";
	}
	clsCode.replace("$(PREDEFINES)",preDeclareCode);

	// 属性处理
	QString attrCode;
	QString attrVarCode;
	if (!genClsCodeHAttr(attrNames,attrCode,attrVarCode))
		return false;
	clsCode.replace("$(ATTRIBUTE_FUNC_DEFINE)",attrCode);
	clsCode.replace("$(ATTRIBUTES_VAR_DEFINE)",attrVarCode);

	// 成员处理
	QString eleCode;
	QString eleVarCode;
	if (!genClsCodeHEle(childrenNames,eleCode,eleVarCode))
		return false;
	clsCode.replace("$(ELEMENTS_FUNC_DEFINE)",eleCode);
	clsCode.replace("$(ELEMENTS_VAR_DEFINE)",eleVarCode);

	clsCode.replace("$(TYPENAME)",clsName);
	clsCode.replace("$(EXPORTDEF)",libraryName().toUpper());
	clsCode.replace("$(BASECLASS)","XSDComplexType");

	QString libN = libraryName();
	if (!libN.isEmpty())
	{
		libN[0] = libN[0].toUpper();
		clsCode.replace("$(LIBNAME)", libN);
	}
	else
	{
		clsCode.replace("$(LIBNAME)", "");
	}

	//处理类名
	clsCode.replace("$(TYPECLASSNAME)","C"+clsName);
		
	// 保存成文件
	filname = outPath() + "/" + clsName+".h";
	if (!CXmlHelper::writeCode(filname, clsCode))
		return false;

	return true;
}

bool CXmlCode::genClsCodeHAttr( const QList<QString>& attrNames,QString& attrCode,QString& attrVarCode )
{
	QString tmp;
	QString strFun;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/Attribute.func.header.tpl", strFun))
		return false;

	QString strVar;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/Attribute.var.header.tpl", strVar))
		return false;

	foreach (QString attr, attrNames)
	{
		tmp = strFun;
		tmp.replace("$(ATTTRIBUTE_NAME)",attr);
		attrCode += tmp;

		tmp = strVar;
		tmp.replace("$(ATTTRIBUTE_NAME)",attr);
		attrVarCode += tmp;
	}

	return true;
}

bool CXmlCode::genClsCodeHEle( const QList<QString>& childrenNames,QString& eleCode,QString& eleVarCode )
{
	QString tmp;
	QString strFun;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/Elements.func.header.tpl", strFun))
		return false;

	QString strVar;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/Elements.var.header.tpl", strVar))
		return false;

	foreach (QString child,childrenNames)
	{
		tmp = strFun;
		tmp.replace("$(ELEMENTCLASS)","C"+child);
		tmp.replace("$(ELEMENTNAME_K)",child);
		tmp.replace("$(ELEMENTNAME)",child);
		eleCode += tmp;

		tmp = strVar;
		tmp.replace("$(ELEMENTCLASS)","C"+child);
		tmp.replace("$(ELEMENTNAME_K)",child);
		eleVarCode += tmp;
	}

	return true;
}

bool CXmlCode::genClsCodeCpp( const QString clsName,const QList<QString> childrenNames,const QList<QString> attrNames )
{
	QString clsCode;
	QString tmp;

	if (!CXmlHelper::readCodetemplates(templateDir() + "/ComplexType.source.tpl", clsCode))
		return false;
	
	// 处理头文件
	QString includesCode;
	includesCode = "#include \""+clsName+".h\"\n";
	foreach (QString child, childrenNames)
	{
		includesCode += "#include \""+child+".h\"\n";
	}
	clsCode.replace("$(INCLUDES)",includesCode);

	// 处理属性函数	
	QString attrFuncDeclareCode;
	if (!genClsCodeCppAttr(attrNames,attrFuncDeclareCode))
		return false;
	clsCode.replace("$(ATTRIBUTE_FUNC_DECLARE)",attrFuncDeclareCode);
	
	// 处理成员函数
	QString childFuncCode;
	if (!genClsCodeCppEle(childrenNames,childFuncCode))
		return false;
	clsCode.replace("$(ELEMENTS_FUNC_DECLARE)",childFuncCode);

	// 处理创建
	QString createObjCode;
	if (!genClsCodeCppCreateObj(childrenNames,createObjCode))
		return false;
	clsCode.replace("$(CREATE_OBJECT)",createObjCode);

	// 处理保存成员
	QString saveCode;
	if (!genClsCodeCppSave(childrenNames,saveCode))
		return false;
	clsCode.replace("$(SAVECODE)",saveCode);

	// 处理保存属性
	QString saveAttr;
	if (!genClsCodeCppSaveAttr(attrNames,saveAttr))
		return false;
	clsCode.replace("$(SAVEATTRIBUTE)",saveAttr);

	// 处理读入属性
	QString loadAttrCode;
	if (!genClsCodeCppLoadAttr(attrNames,loadAttrCode))
		return false;
	clsCode.replace("$(LOADATTRIBUTE)",loadAttrCode);

	// 处理clear
	QString clearCode;
	if (!genClsCodeCppClear(childrenNames,clearCode))
		return false;
	clsCode.replace("$(ELEMENTS_CLEAR)",clearCode);
	
	// 处理copy
	QString membercopyCode;
	QString attrcopyCode;
	if (!genClsCodeCppCopy(childrenNames,membercopyCode))
		return false;
	if (!genClsCodeCppCopyAttr(attrNames, attrcopyCode))
		return false;
	clsCode.replace("$(COPYCODE)",membercopyCode+attrcopyCode);
	
	// 处理类名
	QString className = clsName;
	className.replace("Tag","");	//  把后面的Ele后缀去掉
	clsCode.replace("$(TYPECLASSNAME)","C"+clsName);
	clsCode.replace("$(BASECLASS)","XSDComplexType");
	clsCode.replace("$(ELEMENTNAME)",className);

	QString libN = libraryName();
	if (!libN.isEmpty())
	{
		libN[0] = libN[0].toUpper();
		clsCode.replace("$(LIBNAME)", libN);
	}
	else
	{
		clsCode.replace("$(LIBNAME)", "");
	}

	// 保存成文件
	if (!CXmlHelper::writeCode(outPath() + "/" + clsName + ".cpp", clsCode))
		return false;

	return true;
}

bool CXmlCode::genClsCodeCppAttr( const QList<QString>& attrNames,QString& code )
{
	QString tmp;
	QString strFun;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/Attribute.func.source.tpl", strFun))
		return false;
	
	foreach (QString attrName,attrNames)
	{
		tmp = strFun;
		tmp.replace("$(ATTTRIBUTE_NAME)",attrName);
		code += tmp;
	}

	return true;
}

bool CXmlCode::genClsCodeCppEle( const QList<QString>& childrenNames,QString& code )
{
	QString tmp;
	QString strFun;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/Elements.func.source.tpl", strFun))
		return false;

	foreach (QString childName,childrenNames)
	{
		tmp = strFun;
		tmp.replace("$(ELEMENTCLASS)","C"+childName);
		tmp.replace("$(ELEMENTNAME_K)",childName);
		code += tmp;
	}

	return true;
}

bool CXmlCode::genClsCodeCppCreateObj( const QList<QString>& childrenNames,QString & code )
{
	QString tmp;
	QString strTmp;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/ReadElements.tpl", strTmp))
		return false;

	foreach (QString childName,childrenNames)
	{
		tmp = strTmp;
		tmp.replace("$(ELEMENTCLASS)","C"+childName);
		tmp.replace("$(ELEMENTNAME_K)",childName);
		childName.replace("Tag","");
		tmp.replace("$(ELEMENTNAME)",childName);
		code += tmp;
	}

	return true;
}

bool CXmlCode::genClsCodeCppSave( const QList<QString>& childrenNames,QString& code )
{
	QString tmp;
	QString strFun;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/ElementSave.tpl", strFun))
		return false;

	foreach (QString childName,childrenNames)
	{
		tmp = strFun;
		tmp.replace("$(ELEMENTCLASS)","C"+childName);
		tmp.replace("$(ELEMENTNAME_K)",childName);
		childName.replace("Ele","");
		tmp.replace("$(ELEMENTNAME",childName);
		code += tmp;
	}

	return true;
}

bool CXmlCode::genClsCodeCppSaveAttr( const QList<QString>& attrNames,QString& code )
{
	QString tmp;
	QString strTmp;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/WriteAttribute.tpl", strTmp))
		return false;

	foreach (QString attrName,attrNames)
	{
		tmp = strTmp;
		tmp.replace("$(ATTRIBUTENAME)",attrName);
		code += tmp;
	}

	return true;
}

bool CXmlCode::genClsCodeCppLoadAttr(const QList<QString>& attrNames,QString& code)
{
	QString tmp;
	QString strTmp;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/ReadAttribute.tpl", strTmp))
		return false;

	foreach (QString attr,attrNames)
	{
		tmp = strTmp;
		tmp.replace("$(ATTRIBUTENAME)",attr);
		code += tmp;
	}

	return true;
}

bool CXmlCode::genClsCodeCppClear( const QList<QString>& childrenNames,QString& code )
{
	QString tmp;
	QString strTmp;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/ElementDestructor.tpl", strTmp))
		return false;

	foreach (QString child,childrenNames)
	{
		tmp = strTmp;
		tmp.replace("$(ELEMENTNAME_K)",child);
		tmp.replace("$(ELEMENTCLASS)","C"+child);
		child.replace("Tag","");
		tmp.replace("$(ELEMENTNAME)",child);
		code += tmp;
	}

	return true;
}

bool CXmlCode::genClsCodeCppCopy(const QList<QString> childrenNames,QString& code)
{
	QString tmp;
	QString strTmp;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/ElementCopy.tpl", strTmp))
		return false;

	foreach (QString child,childrenNames)
	{
		tmp = strTmp;
		tmp.replace("$(ELEMENTNAME)", child);
		tmp.replace("$(ELEMENTNAME_K)",child);
		tmp.replace("$(ELEMENTCLASS)","C"+child);
		tmp.replace("$(ELEMENTNAME)",child);
		code += tmp;
	}

	return true;
}

bool CXmlCode::genClsCodeCppCopyAttr( const QList<QString> attrNames, QString& code )
{
	QString tmp;
	QString strTmp;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/AttributeCopy.tpl", strTmp))
		return false;

	foreach (QString attrName, attrNames)
	{
		tmp = strTmp;
		tmp.replace("$(ATTRIBUTENAME)", attrName);
		code += tmp;
	}

	return true;
}

QString CXmlCode::templateDir()
{
	return QCoreApplication::applicationDirPath() + "/../config/xmlbinding/codetemplates";
}
