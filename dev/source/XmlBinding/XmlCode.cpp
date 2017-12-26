#include <QCoreApplication>

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include "XmlCode.h"
#include <QDebug>
#include <iostream>
using namespace std;


CXmlCode::CXmlCode(QObject* parent/* = 0*/)
	: CAbstractXmlCode(parent)
{
	m_iedcfgDoc = new QDomDocument();
	m_exportname.clear();
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
	// �Ƴ�����������
	for (int i = 0; i < c; ++i)
	{
		QDomNode attNode = attributes.item(0);
		QDomAttr attr = attNode.toAttr();
		docElem.removeAttribute(attr.name());
	}
	generateCls(docElem);

	return true;
}

void CXmlCode::generateCls( QDomNode node )
{
	QList<QString> childrenNames;	//	�����б�
	QList<QString> attributesNames;	// �������б�

	if (node.isNull())
		return ;
	QDomElement element = node.toElement();
	if (element.isNull())
		return ;

	// �����Ա
	QDomNodeList nodes = node.childNodes();
	int c = nodes.count();
	for (int i = 0; i<c; ++i)
	{
		QDomNode n = nodes.item(i);
		QDomElement e = n.toElement();
		if (!e.isNull())
		{
			QString childName = e.tagName()+"Ele";
			if (!childrenNames.contains(childName))
				childrenNames.append(childName);
			// cout << "ele:" << e.tagName().toStdString() << endl;
		}
		generateCls(n);
	}

	// ��������
	QDomNamedNodeMap attributes = node.attributes();
	int count = attributes.count();
	for (int i = 0; i <= count-1 ; ++i)
	{
		QDomNode attNode = attributes.item(i);
		QDomAttr attr = attNode.toAttr();
		attributesNames.append(attr.name());
	}

	// ���������
	QString clsName = element.tagName()+"Tag";
	if (!generateClsCode(clsName,childrenNames,attributesNames))
		cout << clsName.toStdString() << "class generate errors" <<endl;
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

	QFile file(getAbsoluteConfigPath() + "/codetemplates/ComplexType.header.txt");
	if (!file.open(QIODevice::ReadOnly|QFile::Text))
	{
		cout << "temple file ComplexType.header.txt read error!" << endl;
		file.close();
		return false;
	}
	// QString d = file.readAll();
	// printf("\n\n%s\n",d.toStdString().c_str());
	clsCode = file.readAll();
	file.close();

	// �괦��
	clsCode.replace("$(TYPENAME_U)",clsName);

	// ͷ�ļ�����
	QString includesCode;
	includesCode = "#include <QList>\n";
// 	includesCode += "#include \"iedcfgcode_global.hpp\"\n";
	includesCode += "#include \"XmlBase.h\"\n";
	clsCode.replace("$(INCLUDES)",includesCode);

	// ��ǰ����
	QString preDeclareCode;
	foreach (QString child,childrenNames)
	{
		// includesCode += "#include \""+child+".h\"\n";
		preDeclareCode += "class C" + child +";\n";
	}
	clsCode.replace("$(PREDEFINES)",preDeclareCode);

	// ���Դ���
	QString attrCode;
	QString attrVarCode;
	if (!genClsCodeHAttr(attrNames,attrCode,attrVarCode))
		return false;
	clsCode.replace("$(ATTRIBUTE_FUNC_DEFINE)",attrCode);
	clsCode.replace("$(ATTRIBUTES_VAR_DEFINE)",attrVarCode);

	// ��Ա����
	QString eleCode;
	QString eleVarCode;
	if (!genClsCodeHEle(childrenNames,eleCode,eleVarCode))
		return false;
	clsCode.replace("$(ELEMENTS_FUNC_DEFINE)",eleCode);
	clsCode.replace("$(ELEMENTS_VAR_DEFINE)",eleVarCode);

	clsCode.replace("$(TYPENAME)",clsName);
	clsCode.replace("$(EXPORTDEF)",m_exportname);
	clsCode.replace("$(BASECLASS)","CXmlBase");

	//��������
	clsCode.replace("$(TYPECLASSNAME)","C"+clsName);
		
	// ������ļ�
	QFile codeFile(m_outpath + QDir::separator() +clsName+".h");
	if (!codeFile.open(QIODevice::WriteOnly | QFile::Text))
	{
		cout << "��д����ļ�"+clsName.toStdString()+".h"+"�򿪴���!" << endl;
		codeFile.close();
		return false;
	}
	QTextStream out(&codeFile);
	out.setCodec("ANSI");
	out << clsCode;
	out.flush();
	codeFile.close();
	// cout << clsCode.toStdString() << endl;

	return true;
}

bool CXmlCode::genClsCodeHAttr( const QList<QString>& attrNames,QString& attrCode,QString& attrVarCode )
{
	QString tmp;
	foreach (QString attr, attrNames)
	{
		QFile file(getAbsoluteConfigPath() + "/codetemplates/Attribute.func.define.txt");
		if (!file.open(QIODevice::ReadOnly|QFile::Text))
		{
			cout << "ģ���ļ�Attribute.func.define.txt�������!" << endl;
			file.close();
			return false;
		}
		tmp = file.readAll();
		file.close();
		tmp.replace("$(ATTTRIBUTE_NAME)",attr);
		attrCode += tmp;

		QFile fileVar(getAbsoluteConfigPath() + "/codetemplates/Attribute.var.define.txt");
		if (!fileVar.open(QIODevice::ReadOnly|QFile::Text))
		{
			cout << "ģ���ļ�Attribute.var.define.txt�������!" << endl;
			fileVar.close();
			return false;
		}
		tmp = fileVar.readAll();
		fileVar.close();
		tmp.replace("$(ATTTRIBUTE_NAME)",attr);
		attrVarCode += tmp;
	}

	return true;
}

bool CXmlCode::genClsCodeHEle( const QList<QString>& childrenNames,QString& eleCode,QString& eleVarCode )
{
	QString tmp;
	foreach (QString child,childrenNames)
	{
		QFile file(getAbsoluteConfigPath() + "/codetemplates/Elements.func.define.txt");
		if (!file.open(QIODevice::ReadOnly|QFile::Text))
		{
			cout << "ģ���ļ�Elements.func.define.txt�������!" << endl;
			file.close();
			return false;
		}
		tmp = file.readAll();
		file.close();
		tmp.replace("$(ELEMENTCLASS)","C"+child);
		tmp.replace("$(ELEMENTNAME_K)",child);
		tmp.replace("$(ELEMENTNAME)",child);
		eleCode += tmp;

		QFile fileVar(getAbsoluteConfigPath() + "/codetemplates/Elements.var.define.txt");
		if (!fileVar.open(QIODevice::ReadOnly|QFile::Text))
		{
			cout << "ģ���ļ�Elements.var.define.txt�������!" << endl;
			fileVar.close();
			return false;
		}
		tmp = fileVar.readAll();
		fileVar.close();
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

	QFile file(getAbsoluteConfigPath() + "/codetemplates/ComplexType.source.txt");
	if (!file.open(QIODevice::ReadOnly|QFile::Text))
	{
		cout << "ģ���ļ�ComplexType.source.txt�������!" << endl;
		file.close();
		return false;
	}
	clsCode = file.readAll();
	file.close();

	
	// ����ͷ�ļ�
	QString includesCode;
	includesCode = "#include \""+clsName+".h\"\n";
	foreach (QString child, childrenNames)
	{
		includesCode += "#include \""+child+".h\"\n";
	}
	clsCode.replace("$(INCLUDES)",includesCode);

	// �������Ժ���	
	QString attrFuncDeclareCode;
	if (!genClsCodeCppAttr(attrNames,attrFuncDeclareCode))
		return false;
	clsCode.replace("$(ATTRIBUTE_FUNC_DECLARE)",attrFuncDeclareCode);
	
	// �����Ա����
	QString childFuncCode;
	if (!genClsCodeCppEle(childrenNames,childFuncCode))
		return false;
	clsCode.replace("$(ELEMENTS_FUNC_DECLARE)",childFuncCode);

	// ������
	QString createObjCode;
	if (!genClsCodeCppCreateObj(childrenNames,createObjCode))
		return false;
	clsCode.replace("$(CREATE_OBJECT)",createObjCode);

	// �������Ա
	QString saveCode;
	if (!genClsCodeCppSave(childrenNames,saveCode))
		return false;
	clsCode.replace("$(SAVECODE)",saveCode);

	// ����������
	QString saveAttr;
	if (!genClsCodeCppSaveAttr(attrNames,saveAttr))
		return false;
	clsCode.replace("$(SAVEATTRIBUTE)",saveAttr);

	// �����������
	QString loadAttrCode;
	if (!genClsCodeCppLoadAttr(attrNames,loadAttrCode))
		return false;
	clsCode.replace("$(LOADATTRIBUTE)",loadAttrCode);

	// ����clear
	QString clearCode;
	if (!genClsCodeCppClear(childrenNames,clearCode))
		return false;
	clsCode.replace("$(ELEMENTS_CLEAR)",clearCode);
	
	// ����copy
	QString membercopyCode;
	QString attrcopyCode;
	if (!genClsCodeCppCopy(childrenNames,membercopyCode))
		return false;
	if (!genClsCodeCppCopyAttr(attrNames, attrcopyCode))
		return false;
	clsCode.replace("$(COPYCODE)",membercopyCode+attrcopyCode);

	
	// ��������
	QString className = clsName;
	className.replace("Ele","");	//  �Ѻ����Ele��׺ȥ��
	clsCode.replace("$(TYPECLASSNAME)","C"+clsName);
	clsCode.replace("$(BASECLASS)","XSDComplexType");
	clsCode.replace("$(ELEMENTNAME)",className);

	// ������ļ�
	QFile codeFile(m_outpath + QDir::separator() +clsName+".cpp");
	if (!codeFile.open(QIODevice::WriteOnly | QFile::Text))
	{
		cout <<"��д���ļ�"+clsName.toStdString()+".cpp"+"�򿪴���" << endl;
		codeFile.close();
		return false;
	}
	QTextStream out(&codeFile);
	out.setCodec("ANSI");
	out << clsCode;
	out.flush();
	codeFile.close();

	return true;
}

bool CXmlCode::genClsCodeCppAttr( const QList<QString>& attrNames,QString& code )
{
	QString tmp;
	QFile file(getAbsoluteConfigPath() + "/codetemplates/Attribute.func.declare.txt");
	if (!file.open(QIODevice::ReadOnly| QFile::Text))
	{
		cout << "ģ���ļ�Attribute.func.declare.txt�������!" <<endl;
		file.close();
		return false;
	}
	foreach (QString attrName,attrNames)
	{
		file.reset();
		tmp = file.readAll();
		tmp.replace("$(ATTTRIBUTE_NAME)",attrName);
		code += tmp;
	}
	file.close();

	return true;
}

bool CXmlCode::genClsCodeCppEle( const QList<QString>& childrenNames,QString& code )
{
	QString tmp;
	QFile file(getAbsoluteConfigPath() + "/codetemplates/Elements.func.declare.txt");
	if (!file.open(QIODevice::ReadOnly| QFile::Text))
	{
		cout << "ģ���ļ�Elements.func.declare.txt�������!" <<endl;
		file.close();
		return false;
	}
	foreach (QString childName,childrenNames)
	{
		file.reset();
		tmp = file.readAll();
		tmp.replace("$(ELEMENTCLASS)","C"+childName);
		tmp.replace("$(ELEMENTNAME_K)",childName);
		code += tmp;
	}
	file.close();

	return true;
}

bool CXmlCode::genClsCodeCppCreateObj( const QList<QString>& childrenNames,QString & code )
{
	QString tmp;
	QFile file(getAbsoluteConfigPath() + "/codetemplates/ReadElements.txt");
	if (!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		cout << "ģ���ļ�ReadElements.txt�������!" << endl;
		file.close();
		return false;
	}
	foreach (QString childName,childrenNames)
	{
		file.reset();
		tmp = file.readAll();
		tmp.replace("$(ELEMENTCLASS)","C"+childName);
		tmp.replace("$(ELEMENTNAME_K)",childName);
		childName.replace("Ele","");
		tmp.replace("$(ELEMENTNAME)",childName);
		code += tmp;
	}
	file.close();

	return true;
}

bool CXmlCode::genClsCodeCppSave( const QList<QString>& childrenNames,QString& code )
{
	QString tmp;
	QFile file(getAbsoluteConfigPath() + "/codetemplates/ElementSave.txt");
	if (!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		cout << "ģ���ļ�ElementSave.txt�������!" << endl;
		file.close();
		return false;
	}
	foreach (QString childName,childrenNames)
	{
		file.reset();
		tmp = file.readAll();
		tmp.replace("$(ELEMENTCLASS)","C"+childName);
		tmp.replace("$(ELEMENTNAME_K)",childName);
		childName.replace("Ele","");
		tmp.replace("$(ELEMENTNAME",childName);
		code += tmp;
	}
	file.close();

	return true;
}

bool CXmlCode::genClsCodeCppSaveAttr( const QList<QString>& attrNames,QString& code )
{
	QString tmp;
	QFile file(getAbsoluteConfigPath() + "/codetemplates/WriteAttribute.txt");
	if (!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		cout << "ģ���ļ�ElementSave.txt�������!" << endl;
		file.close();
		return false;
	}
	foreach (QString attrName,attrNames)
	{
		file.reset();
		tmp = file.readAll();
		tmp.replace("$(ATTRIBUTENAME)",attrName);
		code += tmp;
	}
	file.close();

	return true;
}

bool CXmlCode::genClsCodeCppLoadAttr(const QList<QString>& attrNames,QString& code)
{
	QString tmp;
	QFile file(getAbsoluteConfigPath() + "/codetemplates/ReadAttribute.txt");
	if (!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		cout << "ģ���ļ�ReadAttribute.txt�������!" << endl;
		file.close();
		return false;
	}
	foreach (QString attr,attrNames)
	{
		file.reset();
		tmp = file.readAll();
		tmp.replace("$(ATTRIBUTENAME)",attr);
		code += tmp;
	}
	file.close();

	return true;
}

bool CXmlCode::genClsCodeCppClear( const QList<QString>& childrenNames,QString& code )
{
	QString tmp;
	QFile file(getAbsoluteConfigPath() + "/codetemplates/ElementDestructor.txt");
	if (!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		cout << "ģ���ļ�ElementDestructor.txt�������!" << endl;
		file.close();
		return false;
	}
	foreach (QString child,childrenNames)
	{
		file.reset();
		tmp = file.readAll();
		tmp.replace("$(ELEMENTNAME_K)",child);
		tmp.replace("$(ELEMENTCLASS)","C"+child);
		child.replace("Ele","");
		tmp.replace("$(ELEMENTNAME)",child);
		code += tmp;
	}
	file.close();

	return true;
}

bool CXmlCode::genClsCodeCppCopy(const QList<QString> childrenNames,QString& code)
{
	QString tmp;
	QFile file(getAbsoluteConfigPath() + "/codetemplates/ElementCopy.txt");
	if (!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		cout << "ģ���ļ�ElementCopy.txt�������!" << endl;
		file.close();
		return false;
	}
	foreach (QString child,childrenNames)
	{
		file.reset();
		tmp = file.readAll();
		tmp.replace("$(ELEMENTNAME)", child);
		tmp.replace("$(ELEMENTNAME_K)",child);
		tmp.replace("$(ELEMENTCLASS)","C"+child);
		tmp.replace("$(ELEMENTNAME)",child);
		code += tmp;
	}
	file.close();

	return true;
}

bool CXmlCode::genClsCodeCppCopyAttr( const QList<QString> attrNames, QString& code )
{
	QString tmp;
	QFile file(getAbsoluteConfigPath() + "/codetemplates/AttributeCopy.txt");
	if (!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		cout << "ģ���ļ�AttributeCopy.txt�������" << endl;
		file.close();
		return false;
	}
	foreach (QString attrName, attrNames)
	{
		file.reset();
		tmp = file.readAll();
		tmp.replace("$(ATTRIBUTENAME)", attrName);
		code += tmp;
	}
	file.close();

	return true;
}

QString CXmlCode::getAbsoluteConfigPath()
{
	return QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "config";
}
