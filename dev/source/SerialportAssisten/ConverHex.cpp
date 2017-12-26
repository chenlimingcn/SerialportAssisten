#include "ConverHex.h"

#include <QStringList>

CConverHex::CConverHex(void)
{
}


CConverHex::~CConverHex(void)
{
}

QString CConverHex::toHexString(const QByteArray& arr)
{
	QString contents;
	int len = arr.size();
	unsigned char ch;
	for (int i=0; i< len; ++i)
	{
		ch = arr[i];
		QString tmp;
		contents += tmp.sprintf("%02X ", ch);
	}

	return contents;
}

QByteArray CConverHex::toHex(const QString& contents)
{
	QStringList list = contents.split(" ");		// 空格隔开
	int len = list.size();
	QByteArray arr;
	bool flag = false;
	char buff;

	for (int i=0; i< len; ++i)
	{
		QString str = list.at(i);
		for (int j=0; j<str.size(); j=j+2)
		{
			QString tmp = str.mid(j,2);
			buff = tmp.toInt(&flag, 16);
			if (!flag)	// 转化出错，则发送空的内容
			{
				arr.clear();
				return arr;
			}
			arr.append(&buff,1);
		}
	}

	return arr;
}
