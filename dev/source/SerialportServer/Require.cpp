#include "Require.h"

#include <QString>
#include <QStringList>
#include <cstring>

#include "FrameOutPut.h"
#include "RequireTag.h"

CRequire::CRequire(int len)
	: m_len(len)
{
	m_buff = new unsigned char[len];
}


CRequire::~CRequire(void)
{
	delete[] m_buff;
}

CRequire* CRequire::create(CRequireTag* requireTag)
{
	if (NULL == requireTag)
		return NULL;

	QString value = requireTag->getValue();
	value = value.trimmed();
	QStringList list = value.split(" ");
	int len = list.size();
	CRequire* require = new CRequire(len);
	
	for (int i=0; i<len; ++i)
	{
		QString tmp = list.at(i);
		bool flag = false;
		if (2 != tmp.size())
			return NULL;
		require->m_buff[i] = tmp.toInt(&flag,16);
		if (!flag)
		{
			delete require;
			return NULL;
		}
	}

	return require;
}

void CRequire::setBuff(unsigned char* buff)
{
	memcpy(m_buff, buff, m_len);
}

bool CRequire::compare( unsigned char* buff, int len, int& index )
{
	if (len < m_len)
		return false;
	
	for (int i=0; i<=len-m_len; ++i)
	{
		if (0 == memcmp(&buff[i], m_buff, m_len))
		{
			// µ÷ÊÔÊä³ö
#ifdef _DEBUG
			char* str = "memcmp:";
			CFrameOutPut::frameOuput((unsigned char*)str,strlen(str), 0);
			CFrameOutPut::frameOuput(&buff[i],m_len);
			CFrameOutPut::frameOuput(m_buff, m_len);
#endif // _DEBUG
			index = i;
			return true;
		}
	}

	return false;
}
