#include "CommunicationThread.h"

#include <QDateTime>

#include "Communication.h"
#include "Frame.h"
#include "FrameOutPut.h"
#include "Require.h"
#include "Response.h"

#include <iostream>
using namespace std;

CCommunicationThread::CCommunicationThread(const QString& portname, CSerialportServerDoc* doc, QObject* parent/* = 0 */)
	: QThread(parent)
{
	m_cmm = NULL;
	m_serialport = NULL;
	m_portname = portname;
	m_doc = doc;
}


CCommunicationThread::~CCommunicationThread()
{
}

bool CCommunicationThread::init()
{
	m_cmm = CCommunication::create(m_doc);
	m_serialport = new QSerialPort();
	m_serialport->moveToThread(this);
	m_serialport->setPortName(m_portname);
	if (!m_serialport->open(QIODevice::ReadWrite))
	{
		cout << "serial port open error!" << endl;
		return false;
	}

	// 设置参数
	if (!m_serialport->setBaudRate(9600)) 
	{
		cout << "setBaudRate err" << endl;
		return false;
	}
	if (!m_serialport->setDataBits(QSerialPort::Data8))
	{
		cout << "setDataBits err" << endl;
		return false;

	}
	if (!m_serialport->setParity(QSerialPort::EvenParity))
	{
		cout << "setPari err" << endl;
		return false;
	}
	if (!m_serialport->setStopBits((QSerialPort::OneStop)))
	{
		cout << "setStopBits err" << endl;
		return false;
	}
	if (!m_serialport->setFlowControl((QSerialPort::NoFlowControl))) 
	{
		cout << "setFlowControl err" << endl;
		return false;
	}

	m_buffArray = new QByteArray();
	return true;
}

void CCommunicationThread::run()
{
	// 初始化
	if (!init())
		return ;
	
	while (true)
	{
		if (m_serialport->waitForReadyRead(-1))
		{
			;
		}

		QByteArray arr = m_serialport->readAll();
		unsigned int len = arr.size();
		unsigned char* buff = (unsigned char*)arr.data(); // new unsigned char[len];
		if (0 != len)
		{
			cout << "\n" << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz ").toStdString() << "receive data:" << endl;
			CFrameOutPut::frameOuput(buff, len);
		}
		else // 读取了零字节，继续等待读取接下来的数据
		{
			continue;  
		}
		if (NULL == m_cmm)
		{
			cout << "communication handle is null!" << endl;
			continue;
		}
		
		m_buffArray->append(arr); // 把新接收到的数据追加到数据Buff中
		int total_len = m_buffArray->size(); // 当前数据的总长度
		unsigned char* total_buff = (unsigned char*)m_buffArray->data(); // 当前数据buff
		// 调试输出
#ifdef _DEBUG
		const char* str = "total:";
		CFrameOutPut::frameOuput((unsigned char*)str, strlen(str), 0);
		CFrameOutPut::frameOuput(total_buff, total_len);
#endif // _DEBUG
		int index = -1;
		CFrame* frame = m_cmm->getFrameByContent(total_buff, total_len, index);
		if (NULL == frame)
			continue;
		CResponse* response = frame->getResponse();
		if (NULL == response)
		{
			cout << "response handle is null!" << endl;
			continue;
		}
		// 拿到了子串，说明这之前的数据都已经可以移除
		CRequire* require = frame->getRequire();
		if (-1 != index && NULL != require)
			m_buffArray->remove(0, index+require->length());
		if (!response->write(m_serialport))
			cout << "response error" << endl;
	}

	exec();
}
