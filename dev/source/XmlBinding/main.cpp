﻿#include <QCoreApplication>
#include <QFileInfo>
#include <QStringList>

#include <iostream>
using namespace std;

#include <QTextCodec>
#include "XmlCode.h"
#include "XmlModelCode.h"
#include "XmlGlobalCode.h"

// 帮助函数
void help()
{
	cout << endl;
	cout << "useage:" << endl;
	cout << "	xmlbinding -f filename -lib libname -out path"<<endl;
	cout << "	argv filename: the xml file name" << endl;
	cout << "	argv libname: the name of library" << endl;
	cout << "   argc path: the out path" << endl;

}

int main(int argc,char* argv[])
{
	QCoreApplication app(argc,argv);

	QTextCodec* code = QTextCodec::codecForName("ANSI");
// 	QTextCodec::setCodecForTr(code);
// 	QTextCodec::setCodecForCStrings(code);
	QTextCodec::setCodecForLocale(code);
	cout << "making C++ code......"<<endl;

	// 参数处理
	quint8 index = 0;
	QStringList arguments = app.arguments();
	int count =  arguments.count();
	if (7 != count)		// 缺少参数
	{
		cout << "less arguments" << endl;
		help();
		return 0;
	}

	index = arguments.indexOf("-f");
	if (-1 == index || index >= count)
	{
		help();
		return 0;
	}
	QString filename = arguments.at(index+1);
	QFileInfo fileInfo(filename);
	if (!fileInfo.exists())
	{
		cout << "the special file " << filename.toStdString() << " not exist!~" << endl;
		return 0;
	}
	index = arguments.indexOf("-lib");
	if (-1 == index || index >= count)
	{
		help();
		return 0;
	}
	QString libname = arguments.at(index+1);

	index = arguments.indexOf("-out");
	if (-1 == index || index >= count)
	{
		help();
		return 0;
	}
	QString outpath = arguments.at(index+1);

	CXmlCode cfgcode;

	cfgcode.setLibraryName(libname);
	cfgcode.setOutPath(outpath);
	if (!cfgcode.readfile(filename))
	{
		return 0;
	}
	if (!cfgcode.build())
	{
		cout << "generate code error!" << endl;
	}

	CXmlModelCode mdCfgCode;
	mdCfgCode.setLibraryName(libname);
	mdCfgCode.setOutPath(outpath);
	if (!mdCfgCode.readfile(filename))
	{
		return 0;
	}
	if (!mdCfgCode.build())
	{
		cout << "generate model code error!" << endl;
	}

	CXmlGlobalCode gobalCode;
	gobalCode.setLibraryName(libname);
	gobalCode.setOutPath(outpath);
	if (!gobalCode.readfile(filename))
	{
		return 0;
	}
	if (!gobalCode.build())
	{
		cout << "generate global code error!~" << endl;
	}
	return 0;
}