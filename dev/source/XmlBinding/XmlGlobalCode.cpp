#include "XmlGlobalCode.h"

#include <QCoreApplication>

#include <iostream>
using namespace std;

#include "XmlHelper.h"

CXmlGlobalCode::CXmlGlobalCode()
	: CXmlCodeBase()
{

}

CXmlGlobalCode::~CXmlGlobalCode()
{

}

bool CXmlGlobalCode::readfile(const QString& /*filename*/)
{
	return true;
}

bool CXmlGlobalCode::build()
{
	generateExportfile();
	return true;
}

void CXmlGlobalCode::generateExportfile()
{
	QString hCode;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/Exportfile.header.tpl", hCode))
		return ;

	hCode.replace("$(LIBNAME_UPPERCASE)", libraryName().toUpper());
	hCode.replace("$(EXPORTDEF)", libraryName().toUpper());

	if (!CXmlHelper::writeCode(outPath() + "/" + libraryName() + "_global.h", hCode))
	{
		cout << "generate export h file error!" << endl;
		return ;
	}

	QString sCode;
	if (!CXmlHelper::readCodetemplates(templateDir() + "/Exportfile.source.tpl", sCode))
		return ;
	sCode.replace("$(LIBNAME)", libraryName());

	if (!CXmlHelper::writeCode(outPath() + "/" + libraryName() + "_global.cpp", sCode))
	{
		cout << "generate export cpp file error!" << endl;
		return ;
	}
}

QString CXmlGlobalCode::templateDir()
{
	return QCoreApplication::applicationDirPath() + "/../config/xmlbinding/global";
}

