#ifndef SERIALPORTINFO_H__
#define SERIALPORTINFO_H__

#include <QSerialPort>

// �����ؼ����ݵĵĸ���
class CSerialPortInfo
{
public:
	CSerialPortInfo(QSerialPort* serialport = NULL);
	virtual ~CSerialPortInfo();

// 	void setSerialPortData(QSerialPort* serialport);

protected:
	QSerialPort* m_serialport;		// �˿�����
};

#endif // SERIALPORTINFO_H__
