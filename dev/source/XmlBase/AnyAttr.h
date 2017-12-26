#ifndef ANYATTR_H__
#define ANYATTR_H__

#include <QString>

#include "XmlBase_global.h"

class XMLBASE_API CAnyAttr
{
public:
	CAnyAttr();
	CAnyAttr(QString attrName, QString attrValue);
	~CAnyAttr();

public:
	QString m_attrName;
	QString m_attrValue;
};
#endif // ANYATTR_H__
