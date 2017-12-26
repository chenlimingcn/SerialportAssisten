#include "Response.h"

#include <QDateTime>
#include <QDebug>
#include <QString>
#include <QStringList>

#include <iostream>
using namespace std;

#include <time.h>

#include "ResponseTag.h"
#include "FrameOutPut.h"

CResponse::CResponse(int len)
	: m_len(len)
{
	m_buff = new unsigned char[len];
}


CResponse::~CResponse(void)
{
	delete[] m_buff;
}

CResponse* CResponse::create( CResponseTag* responseTag )
{
	if (NULL == responseTag)
		return NULL;

	QString value = responseTag->getValue();
	value = value.trimmed();
	QStringList list = value.split(" ");
	int len = list.size();
	CResponse* response = new CResponse(len);

	for (int i=0; i<len; ++i)
	{
		QString tmp = list.at(i);
		bool flag = false;
		if (2 != tmp.size())
		{
			cout << "response data format error!" << endl;
			return NULL;
		}
		response->m_buff[i] = tmp.toInt(&flag, 16);
		if (!flag)
		{
			delete response;
			return NULL;
		}
	}

	return response;
}

bool CResponse::write( QIODevice* iodev )
{
	if (NULL == iodev || !iodev->isWritable())
		return false;
	if (m_len != iodev->write((char*)m_buff, m_len))
		return false;
	cout << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz ").toStdString() << "response data: " << endl;
	CFrameOutPut::frameOuput(m_buff,m_len);
	return true;
}
