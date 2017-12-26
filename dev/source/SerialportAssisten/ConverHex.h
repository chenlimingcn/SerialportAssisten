#ifndef CONVERHEX_H__
#define CONVERHEX_H__

#include <QByteArray>
#include <QString>

class CConverHex
{
public:
	CConverHex();
	~CConverHex();

	// 从二进制转换成形如：EB 90 EB 90的形式表示的十六进制字符串
	static QString toHexString(const QByteArray& arr);

	// toHexString反向
	static QByteArray toHex(const QString& contents);
};

#endif // CONVERHEX_H__
