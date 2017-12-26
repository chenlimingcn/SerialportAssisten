#include "SerialPortInfo.h"


CSerialPortInfo::CSerialPortInfo(QSerialPort* serialport/* = NULL*/)
	: m_serialport(serialport)
{
}


CSerialPortInfo::~CSerialPortInfo()
{
}

// void CSerialPortInfo::setSerialPortData(QSerialPort* serialport)
// {
// 	m_serialport = serialport;
// }

