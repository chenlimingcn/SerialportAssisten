#include <QCoreApplication>
#include <QStringList>

#include <iostream>
using namespace std;

#include <QFileInfo>
#include <QTextCodec>

#include "XmlCodeThread.h"
#include "XmlCode.h"

// 帮助函数
void help()
{
	cout << endl;
	cout << "useage:" << endl;
	cout << "	XmlBinding -f filename [-api exportname] -out path"<<endl;
	cout << "	argv filename: the xml file name" << endl;
	cout << "	argv exportname: the macro of export" << endl;
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

	CXmlCode cfgcode;
	CXmlCodeThread cfgcodeThread(&(cfgcode));

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
		cout << "the special file " << filename.toStdString() << "not exist!~" << endl;
		return 0;
	}

	if (!cfgcode.readfile(filename))	// 默认-f后面做为文件名
	{
		cout<<"error:read file error!"<<endl;
		return 0;
	}	

	index = arguments.indexOf("-api");
	if (-1 == index || index >= count)
	{
		help();
		return 0;
	}
	cfgcode.setExportName(arguments.at(index+1));

	index = arguments.indexOf("-out");
	if (-1 == index || index >= count)
	{
		help();
		return 0;
	}
	cfgcode.setOutPath(arguments.at(index+1));

	cfgcodeThread.start();
	
	cfgcodeThread.wait();

	if (!cfgcodeThread.isSuccess() )
	{
		cout << "generate error!"<<endl;
		return 0;
	}
	cout << "generate successfully!" << endl;
	return 0;
}