#ifndef ABSTRACTXMLCORE_H__
#define ABSTRACTXMLCORE_H__

#include <QObject>

class CAbstractXmlCode
	: public QObject
{
public:
	CAbstractXmlCode(QObject* parent = 0);
	~CAbstractXmlCode();

	virtual bool build() = 0;
};
#endif // ABSTRACTXMLCORE_H__
