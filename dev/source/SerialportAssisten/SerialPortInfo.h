#ifndef SERIALPORTINFO_H__
#define SERIALPORTINFO_H__

#include <QSerialPort>

// 各个控件数据的的父类
class CSerialPortInfo
{
public:
	CSerialPortInfo(QSerialPort* serialport = NULL);
	virtual ~CSerialPortInfo();

// 	void setSerialPortData(QSerialPort* serialport);

protected:
	QSerialPort* m_serialport;		// 端口数据
};

#endif // SERIALPORTINFO_H__
