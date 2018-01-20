#include "XmlModelCode.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include "XmlHelper.h"
using namespace std;

CXmlModelCode::CXmlModelCode()
{
	m_iedcfgDoc = new QDomDocument();
}


CXmlModelCode::~CXmlModelCode()
{
	delete m_iedcfgDoc;
}

bool CXmlModelCode::readfile( const QString& filename )
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
			<< "<line " << errorLine << "column " << errorColumn << ")" << endl;
		file.close();
		return false;
	}

	file.close();
	return true;
}

bool CXmlModelCode::build()
{
	if (m_iedcfgDoc == NULL)
		return false;

	QDomElement docEle = m_iedcfgDoc->documentElement();
	QDomNamedNodeMap attrs = docEle.attributes();
	int c = attrs.count();

	for (int i = 0; i< c; ++i)
	{
		QDomNode attrNode = attrs.item(0);
		QDomAttr attr = attrNode.toAttr();
		docEle.removeAttribute(attr.name());
	}

	generateModelCls(docEle);

	return true;
}

QString CXmlModelCode::outPath() const
{
	QString path = CXmlCodeBase::outPath() + "/model";
	QDir dir;
	if (!dir.exists(path))
	{
		if (!dir.mkdir(path))
			return CXmlCodeBase::outPath();
	}

	return path;
}

void CXmlModelCode::generateModelCls( QDomNode node, QDomNode  parentNode/* = QDomNode()*/ )
{
	QList<QString> childNames;
	QList<QString> attrsNames;

	if (node.isNull())
		return ;
	QDomElement element = node.toElement();
	if (element.isNull())
		return ;

	QString parentName;
	if (!parentNode.isNull())
	{
		QDomElement parentE = parentNode.toElement();
		if (!parentE.isNull())
		{
			parentName = parentE.tagName();
		}
	}
	// 处理成员
	QDomNodeList nodes = node.childNodes();
	for (int i = 0; i<nodes.count(); ++i)
	{
		QDomNode n = nodes.item(i);
		QDomElement e = n.toElement();
		if (!e.isNull())
		{
			QString childName = e.tagName()+"Tag";
			if (!childNames.contains(childName))
				childNames.append(childName);
			// cout << "ele:" << e.tagName().toStdString() << endl;
		}
		generateModelCls(n);
	}

	// 处理属性
	QDomNamedNodeMap attributes = element.attributes();
	int count = attributes.count();
	for (int i = 0; i <= count-1 ; ++i)
	{
		QDomNode attNode = attributes.item(i);
		QDomAttr attr = attNode.toAttr();
		attrsNames.append(attr.name());
	}

	// 生成类代码
	QString clsName = element.tagName()+"Tag";
	if (!generateClsCode(clsName,childNames,attrsNames))
		cout << "C" << clsName.toStdString() << " generate class error！" <<endl;
}

bool CXmlModelCode::generateClsCode( const QString clsName,
									const QList<QString> childrenNames,
									const QList<QString> attrNames,
									const QString& parentName/* = QString()*/
									)
{
	if (m_haveCode.contains(clsName))
		return true;
	m_haveCode.append(clsName);

	bool flag = true;

	if (!genClsCodeH(clsName,childrenNames,attrNames, parentName))
	{
		flag =  false;
	}

	if (!genClsCodeCpp(clsName,childrenNames,attrNames, parentName))
	{
		flag = false;
	}
	return flag;
}

bool CXmlModelCode::genClsCodeH( const QString clsName, 
								const QList<QString> childrenNames, 
								const QList<QString> attrNames, 
								const QString& parentName/* = QString()*/ )
{
	QString clsCode;
	QString tmp;
	if (parentName.isEmpty())
	{
		if (!CXmlHelper::readCodetemplates(templateDir() + "/Model.header.withoutparent.tpl", clsCode))
			return false;
	}
	else
	{
		if (!CXmlHelper::readCodetemplates(templateDir() + "/Model.header.withparent.tpl", clsCode))
			return false;
	}

	// 宏处理
	clsCode.replace("$(TYPENAME_U)",clsName);

	// 头文件处理
	QString includeCode;
	includeCode += "#include \"" + libraryName() + "_global.h\"\n";
	includeCode = "#include <QList>\n";
	includeCode += "#include \"" + clsName + ".h\"\n";
	clsCode.replace("$(INCLUDES)",includeCode);

	QString preDelcareCode;
	preDelcareCode = "";
	clsCode.replace("$(PREDEFINES)",preDelcareCode);

	// 属性处理 (Enum CASE)
	QString attrCode;
	QString attrTmp;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/Attributes.Enum.header.tpl", attrTmp))
		return false;

	foreach (QString attrName,attrNames)
	{
		tmp = attrTmp;
		tmp.replace("$(ATTR_NAME)",attrName);
		attrCode += tmp;
	}

	clsCode.replace("$(ATTRIBUTES_Enum_DECLARE)",attrCode);
	clsCode.replace("$(EXPORTDEF)",libraryName().toUpper());
	clsCode.replace("$(TYPECLASSNAME)","C"+clsName);
	clsCode.replace("$(PARENTTYPECLASSNAME)", "C"+clsName);

	if (!CXmlHelper::writeCode(outPath() + "/" + clsName + "Model.h", clsCode))
		return false;
	
	return true;
}

bool CXmlModelCode::genClsCodeCpp( const QString clsName, 
								  const QList<QString> childrenNames, 
								  const QList<QString> attrNames, 
								  const QString& parentName/* = QString()*/ )
{
	QString clsCode;
	QString tmp;

	if (parentName.isEmpty())
	{
		if (!CXmlHelper::readCodetemplates(templateDir() + "/Model.source.withoutparent.tpl", clsCode))
			return false;
	}
	else
	{
		if (!CXmlHelper::readCodetemplates(templateDir() + "/Model.source.withparent.tpl", clsCode))
			return false;
	}

	// 处理头文件
	QString includes;
	includes = "#include \"" + clsName + "Model.h\"\n";
	clsCode.replace("$(INCLUDES)",includes);

	// 处理 Case
	QString hData_case;
	QString data_case;
	QString sData_cae;

	QString strHeader;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/headData.Case.tpl", strHeader))
		return false;

	QString strData;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/data.Case.tpl", strData))
		return false;

	QString strSet;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/setData.case.tpl", strSet))
		return false;

	foreach (QString attr,attrNames)
	{
		tmp = strHeader;
		tmp.replace("$(ATTR_NAME)",attr);
		hData_case += tmp;

		tmp = strData;
		tmp.replace("$(ATTR_NAME)",attr);
		data_case += tmp;

		tmp = strSet;
		tmp.replace("$(ATTR_NAME)",attr);
		sData_cae += tmp;
	}
	clsCode.replace("$(HEADDATA_CASE)",hData_case);
	clsCode.replace("$(DATA_CASE)",data_case);
	clsCode.replace("$(SETDATA_CASE)",sData_cae);

	// 处理类名
	clsCode.replace("$(TYPECLASSNAME)","C"+clsName);

	// 保存成文件
	if (!CXmlHelper::writeCode(outPath() + "/" + clsName + "Model.cpp", clsCode))
		return false;

	return true;
}

QString CXmlModelCode::templateDir()
{
	return QCoreApplication::applicationDirPath() + "/../config/xmlbinding/modelcodetemplates";
}
