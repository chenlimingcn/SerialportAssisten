#ifndef CONVERHEX_H__
#define CONVERHEX_H__

#include <QByteArray>
#include <QString>

class CConverHex
{
public:
	CConverHex();
	~CConverHex();

	// �Ӷ�����ת�������磺EB 90 EB 90����ʽ��ʾ��ʮ�������ַ���
	static QString toHexString(const QByteArray& arr);

	// toHexString����
	static QByteArray toHex(const QString& contents);
};

#endif // CONVERHEX_H__
