#include <QCoreApplication>

#include <QFile>
#include "XmlCode.h"
#include <QDebug>
#include <iostream>
using namespace std;


CXmlCode::CXmlCode(QObject* parent/* = 0*/)
	: CAbstractXmlCode(parent)
{
	m_iedcfgDoc = new QDomDocument();
	m_libName.clear();
}


CXmlCode::~CXmlCode()
{
	delete m_iedcfgDoc;
}

bool CXmlCode::readfile( QString filename )
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

	generateExportfile();
	
	generateDocment(docElem);

	generateCls(docElem);

	generateAllh();

	return true;
}

void CXmlCode::generateExportfile()
{
	QString hCode;
	if (!CXmlCodeHelper::readCodetemplates("Exportfile.header.tpl", hCode))
		return ;

	hCode.replace("$(LIBNAME_UPPERCASE)", m_libName.toUpper());
	hCode.replace("$(EXPORTDEF)", exportName());

	if (!CXmlCodeHelper::writeCode(m_outpath + "/" + m_libName + "_global.h", hCode))
	{
		cout << "generate export h file error!" << endl;
		return ;
	}

	QString sCode;
	if (!CXmlCodeHelper::readCodetemplates("Exportfile.source.tpl", sCode))
		return ;
	sCode.replace("$(LIBNAME)", m_libName);

	if (!CXmlCodeHelper::writeCode(m_outpath + "/" + m_libName + "_global.cpp", sCode))
	{
		cout << "generate export cpp file error!" << endl;
		return ;
	}
}

void CXmlCode::generateDocment(QDomNode node)
{
	QString hCode;
	if (!CXmlCodeHelper::readCodetemplates("Document.header.tpl", hCode))
		return ;

	QString libName = m_libName;
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
	hCode.replace("$(LIBNAME)", libName);

	if (!CXmlCodeHelper::writeCode(libName + "Document.h", hCode))
		return ;

	QString sCode;
	if (!CXmlCodeHelper::readCodetemplates("Document.source.tpl", sCode))
		return ;

	sCode.replace("$(LIBNAME)", libName);
	sCode.replace("$(ROOTNAME)", rootname + "Tag");
	sCode.replace("$(ROOTNAME_K)", rootname);

	CXmlCodeHelper::writeCode(libName + "Document.cpp", sCode);
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
		cout << clsName.toStdString() << "class generate errors" <<endl;
	
	if (!m_eleNames.contains(clsName))
		m_eleNames << clsName;
}

void CXmlCode::generateAllh()
{
	// 处理All.h
	QString filename = m_outpath + "/" + m_libName + "_AllTags.h";
	QFile file(filename);
	if (!file.open(QFile::WriteOnly))
	{
		cout << m_libName.toStdString() + "_AllTags.h open error!" << endl;
		return ;
	}
	QString strH;
	strH = "#ifndef " + m_libName.toUpper() + "_H__\n" +
		"#define " +  m_libName.toUpper() + "_H__\n\n";

	file.write(strH.toStdString().c_str());
	foreach (QString clsName, m_eleNames)
	{
		QString iCode = "#include \"" + clsName + ".h\"\n";
		file.write(iCode.toStdString().c_str());
	}
	QString strE = "\n#endif // " + m_libName.toUpper() + "_H__\n";
	file.write(strE.toStdString().c_str());
	file.close();

}
bool CXmlCode::generateClsCode( const QString clsName,const QList<QString> childrenNames,const QList<QString> attrNames )
{
	if (m_haveCode.contains(clsName))
		return true;
	m_haveCode.append(clsName);
	
	bool flag = true;
	
	if (!genClsCodeH(clsName,childrenNames,attrNames))
	{
		cout << clsName.toStdString() << ".h create fail!" <<endl;
		flag =  false;
	}

	if (!genClsCodeCpp(clsName,childrenNames,attrNames))
	{
		cout << clsName.toStdString() << ".cpp create fail!" << endl;
		flag = false;
	}
	return flag;
}

bool CXmlCode::genClsCodeH( const QString clsName,const QList<QString> childrenNames,const QList<QString> attrNames )
{
	QString clsCode;
	QString tmp;

	if (!CXmlCodeHelper::readCodetemplates("ComplexType.header.tpl", clsCode))
		return false;

	// 宏处理
	clsCode.replace("$(TYPECLASSNAME_U)",clsName);

	// 头文件处理
	QString includesCode;
	clsCode.replace("$(LIBNAME)", m_libName);
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
	clsCode.replace("$(ATTRIBUTES_FUNC_HEADER)",attrCode);
	clsCode.replace("$(ATTRIBUTES_VAR_HEADER)",attrVarCode);

	// 成员处理
	QString eleCode;
	QString eleVarCode;
	if (!genClsCodeHEle(childrenNames,eleCode,eleVarCode))
		return false;
	clsCode.replace("$(ELEMENTS_FUNC_HEADER)",eleCode);
	clsCode.replace("$(ELEMENTS_VAR_HEADER)",eleVarCode);

	clsCode.replace("$(TYPENAME)",clsName);
	clsCode.replace("$(EXPORTDEF)", exportName());

	//处理类名
	clsCode.replace("$(TYPECLASSNAME)", clsName);
		
	// 保存成文件
	return CXmlCodeHelper::writeCode(m_outpath + "/" +clsName+".h", clsCode);
}

bool CXmlCode::genClsCodeHAttr( const QList<QString>& attrNames,QString& attrCode,QString& attrVarCode )
{
	QString tmpFun;
	QString tmpVar;
	QString tmp;
	
	if (!CXmlCodeHelper::readCodetemplates("Attribute.func.header.tpl", tmpFun))
		return false;

	if (!CXmlCodeHelper::readCodetemplates("Attribute.var.header.tpl", tmpVar))
		return false;

	foreach (QString attr, attrNames)
	{
		tmp = tmpFun;
		tmp.replace("$(ATTTRIBUTE_NAME)",attr);
		attrCode += tmp;

		tmp = tmpVar;
		tmp.replace("$(ATTTRIBUTE_NAME)",attr);
		attrVarCode += tmp;
	}

	return true;
}

bool CXmlCode::genClsCodeHEle( const QList<QString>& childrenNames,QString& eleCode,QString& eleVarCode )
{
	QString tmpFun;
	QString tmpVar;
	QString tmp;

	if (!CXmlCodeHelper::readCodetemplates("Elements.func.header.tpl", tmpFun))
		return false;

	if (!CXmlCodeHelper::readCodetemplates("Elements.var.header.tpl", tmpVar))
		return false;

	foreach (QString child,childrenNames)
	{
		tmp = tmpFun;
		tmp.replace("$(ELEMENTCLASS)","C"+child);
		tmp.replace("$(ELEMENTNAME_K)",child);
		tmp.replace("$(ELEMENTNAME)",child);
		eleCode += tmp;

		tmp = tmpVar;
		tmp.replace("$(ELEMENTCLASS)","C"+child);
		tmp.replace("$(ELEMENTNAME_K)",child);
		eleVarCode += tmp;
	}

	return true;
}

bool CXmlCode::genClsCodeCpp( const QString clsName,const QList<QString> childrenNames,const QList<QString> attrNames )
{
	QString clsCode;

	if (!CXmlCodeHelper::readCodetemplates("ComplexType.source.tpl", clsCode))
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
	clsCode.replace("$(ATTRIBUTE_FUNC_SOURCE)",attrFuncDeclareCode);
	
	// 处理成员函数
	QString childFuncCode;
	if (!genClsCodeCppEle(childrenNames,childFuncCode))
		return false;
	clsCode.replace("$(ELEMENTS_FUNC_SOURCE)",childFuncCode);

	// 处理创建
	QString createObjCode;
	if (!genClsCodeCppCreateObj(childrenNames,createObjCode))
		return false;
	clsCode.replace("$(CREATE_OBJECT)",createObjCode);

	// 处理保存成员
	QString saveCode;
	if (!genClsCodeCppSave(childrenNames,saveCode))
		return false;
	clsCode.replace("$(ELEMENTS_SAVE)",saveCode);

	// 处理保存属性
	QString saveAttr;
	if (!genClsCodeCppSaveAttr(attrNames,saveAttr))
		return false;
	clsCode.replace("$(ATTRIBUTE_SAVE)",saveAttr);

	// 处理读入属性
	QString loadAttrCode;
	if (!genClsCodeCppLoadAttr(attrNames,loadAttrCode))
		return false;
	clsCode.replace("$(ATTRIBUTE_READ)",loadAttrCode);

	// 处理clear
	QString clearCode;
	if (!genClsCodeCppClear(childrenNames,clearCode))
		return false;
	clsCode.replace("$(ELEMENTS_CLEAR)",clearCode);
	
// 	// 处理copy
// 	QString copyCode;
// 	if (!genClsCodeCppCopy(childrenNames,copyCode))
// 		return false;
// 	clsCode.replace("$(COPYCODE)",copyCode);
	
	// 处理类名
	QString className = clsName;
	className.replace("Tag","");	//  把后面的Ele后缀去掉
	clsCode.replace("$(TYPECLASSNAME)","C"+clsName);
	clsCode.replace("$(ELEMENTNAME)",className);

	// 保存成文件
	return CXmlCodeHelper::writeCode(m_outpath + "/" + clsName+".cpp", clsCode);
}

bool CXmlCode::genClsCodeCppAttr( const QList<QString>& attrNames,QString& code )
{
	QString tmp;
	QString tmpFun;
	if (!CXmlCodeHelper::readCodetemplates("Attribute.func.source.tpl", tmpFun))
		return false;

	foreach (QString attrName,attrNames)
	{
		tmp = tmpFun;
		tmp.replace("$(ATTTRIBUTE_NAME)",attrName);
		code += tmp;
	}
	return true;
}

bool CXmlCode::genClsCodeCppEle( const QList<QString>& childrenNames,QString& code )
{
	QString tmp;
	QString tmpFun;
	if (!CXmlCodeHelper::readCodetemplates("Elements.func.source.tpl", tmpFun))
		return false;

	foreach (QString childName,childrenNames)
	{
		tmp = tmpFun;
		tmp.replace("$(ELEMENTCLASS)","C"+childName);
		tmp.replace("$(ELEMENTNAME_K)",childName);
		code += tmp;
	}

	return true;
}

bool CXmlCode::genClsCodeCppCreateObj( const QList<QString>& childrenNames,QString & code )
{
	QString tmp;
	QString tmpEle;
	if (!CXmlCodeHelper::readCodetemplates("ElementsRead.tpl", tmpEle))
		return false;

	foreach (QString childName,childrenNames)
	{
		tmp = tmpEle;
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
	QString tmpEle;
	if (!CXmlCodeHelper::readCodetemplates("ElementsWrite.tpl", tmpEle))
		return false;

	foreach (QString childName,childrenNames)
	{
		tmp = tmpEle;
		tmp.replace("$(ELEMENTCLASS)","C"+childName);
		tmp.replace("$(ELEMENTNAME)",childName);
		code += tmp;
	}

	return true;
}

bool CXmlCode::genClsCodeCppSaveAttr( const QList<QString>& attrNames,QString& code )
{
	QString tmp;
	QString tmpAttr;
	if (!CXmlCodeHelper::readCodetemplates("AttributeWrite.tpl", tmpAttr))
		return false;

	foreach (QString attrName,attrNames)
	{
		tmp = tmpAttr;
		tmp.replace("$(ATTTRIBUTE_NAME)",attrName);
		code += tmp;
	}

	return true;
}

bool CXmlCode::genClsCodeCppLoadAttr(const QList<QString>& attrNames,QString& code)
{
	QString tmp;
	QString tmpAttr;
	if (!CXmlCodeHelper::readCodetemplates("AttributeRead.tpl", tmpAttr))
		return false;

	foreach (QString attr,attrNames)
	{
		tmp = tmpAttr;
		tmp.replace("$(ATTTRIBUTE_NAME)",attr);
		code += tmp;
	}

	return true;
}

bool CXmlCode::genClsCodeCppClear( const QList<QString>& childrenNames,QString& code )
{
	QString tmp;
	QString tmpDes;
	if (!CXmlCodeHelper::readCodetemplates("ElementDestructor.tpl", tmpDes))
		return false;

	foreach (QString child,childrenNames)
	{
		tmp = tmpDes;
		tmp.replace("$(ELEMENTNAME_K)",child);
		tmp.replace("$(ELEMENTCLASS)","C"+child);
		child.replace("Tag","");
		tmp.replace("$(ELEMENTNAME)",child);
		code += tmp;
	}

	return true;
}

bool CXmlCode::genClsCodeCppCopy(const QList<QString> childrenNames,QString code)
{
	QString tmp;
	QString tmpCpy;
	if (!CXmlCodeHelper::readCodetemplates("ElementCopy.txt", tmpCpy))
		return false;

	foreach (QString child,childrenNames)
	{
		tmp = tmpCpy;
		tmp.replace("$(ELEMENTNAME_K)",child);
		tmp.replace("$(ELEMENTCLASS)","C"+child);
		child.replace("Tag","");
		tmp.replace("$(ELEMENTNAME)",child);
		code += tmp;
	}

	return true;
}

QString CXmlCode::exportName()
{
	if (!m_libName.isEmpty())
		return m_libName.toUpper()+"_API";
	return "";
}

bool CXmlCodeHelper::readCodetemplates( const QString& filename, QString& strCode )
{
	QString abFilename = QCoreApplication::applicationDirPath() + "/../config/xmlstreambinding/codetemplates/" + filename;

	QFile file(abFilename);
	if (!file.open(QIODevice::ReadOnly|QFile::Text))
	{
		cout <<  "template file " << abFilename.toStdString() << " read error!" << endl;
		file.close();
		return false;
	}

	QTextStream in(&file);
	in.setCodec("UTF-8");
	strCode = in.readAll();
	file.close();

	return true;
}

bool CXmlCodeHelper::writeCode( const QString& filename , const QString& strCode )
{
	QFile codeFile(filename);
	if (!codeFile.open(QIODevice::WriteOnly | QFile::Text))
	{
		cout << "write "+filename.toStdString()+".h"+" error!" << endl;
		codeFile.close();
		return false;
	}
	QTextStream out(&codeFile);
	out.setCodec("ANSI");
	out << strCode;
	out.flush();
	codeFile.close();

	return true;
}


