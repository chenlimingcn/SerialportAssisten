#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QSerialPort>
#include <QStringList>

#include <iostream>
using namespace std;

#include "Communication.h"
#include "CommunicationThread.h"
#include "SerialportServerDoc.h"


// SerialportServer -port COM3 -frm aa.frm
void help()
{
	cout << endl;
	cout << "useage:" << endl;
	cout << "SerialportServer -port port -frm framfile" << endl;
	cout << "argv port: the name of the serial port" << endl;
	cout << "argv frmfile: the name of frm file" << endl;

}
int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);

	QByteArray ba("Montreal");
	ba.remove(1, 4);
	// ba == "Meal"
	// 参数处理
	QStringList arguments = app.arguments();
	if (5 != argc)
	{
		cout << "less arguments" << endl;
		help();
		return 0;
	}

	int index = arguments.indexOf("-port");
	if (-1 == index)
	{
		cout << "arguments error!" << endl;
		return 0;
	}

	QString portname = arguments.at(index+1);

	index = arguments.indexOf("-frm");
	if (-1 == index)
	{
		cout << "arguments error" << endl;
		return 0;
	}
	QString frmname = arguments.at(index+1);


	CSerialportServerDoc* doc = new CSerialportServerDoc();
	if (!doc->parse(frmname))
	{
		cout << "parse frm file error!" << endl;
		cout << doc->error().toStdString() << endl;
		return 0;  // 出错直接退出
	}
	
// 	CCommunication* cmm = CCommunication::create(doc);
	CCommunicationThread* thread = new CCommunicationThread(portname, doc);
	thread->start();

	return app.exec();
}