#include <QCoreApplication>
#include <QDebug>
#include <QList>
#include <QString>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <iostream>
#include <cstring>
using namespace std;
#include <QDir>

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	// 参数处理
	QStringList arguments = app.arguments();
	if (arguments.size() != 5)	// 参数不够
	{
		cout << "less arguments." << endl;
		return 0;
	}
	int index = arguments.indexOf("-port"); //  -port后面跟着的是端口号

	QString portN = arguments.at(index+1);
	// 输出串口基本信息
	QSerialPortInfo portInfo(portN);
	cout << "serial port info " << portInfo.portName().toStdString() << endl;
	cout << "manufacturer:" << portInfo.manufacturer().toStdString() << endl;
	cout << "desc:" << portInfo.description().toStdString() << endl;
	cout << "vaild:" << portInfo.isValid() << endl;
	cout << "busy:" << portInfo.isBusy() << endl;
	cout << endl;

	// 打开串口
	QSerialPort serialport(portInfo.portName());
	if (!serialport.open(QIODevice::ReadWrite))
	{
		qDebug() << "serialport open fail" << portInfo.portName();
		return 0;
	}

	// 设置参数
	if (!serialport.setBaudRate(QSerialPort::Baud9600)) 
	{
		qDebug() << QString("setBaudRate err");
	}
	if (!serialport.setDataBits(QSerialPort::Data8))
	{
		qDebug() << QString("setDataBits err");

	}
	if (!serialport.setParity(QSerialPort::EvenParity))		// 偶校验
	{
		qDebug() << QString("setPari err");
	}
	if (!serialport.setStopBits((QSerialPort::OneStop)))
	{
		qDebug() << QString("setStopBits err");
	}
	if (!serialport.setFlowControl((QSerialPort::NoFlowControl))) 
	{
		qDebug() << QString("setFlowControl err");
	}

	serialport.waitForReadyRead(-1);
	QByteArray arr = serialport.readAll();
	unsigned int len = arr.size();
	char ch = 0;
	char str[8];
	for (int i=0; i<len; ++i)
	{
		ch = arr.at(i);
		sprintf(str, "%02X ", ch);
		cout << str;
	}

	cout << endl;

	return app.exec();
}
