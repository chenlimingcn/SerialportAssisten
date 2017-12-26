#ifndef XMLBASEDOC_H__
#define XMLBASEDOC_H__

#include <QString>
#include <QXmlStreamAttributes>

#include "XmlBase_global.h"

class XMLBASE_API CXmlBaseDoc
{
public:
	CXmlBaseDoc();
	virtual ~CXmlBaseDoc();

	virtual bool parse(const QString& filename) = 0;

	virtual QString error() const = 0;

protected:
	virtual void createElement(const QString& name, QXmlStreamAttributes attributes) = 0;
};
#endif // XMLBASEDOC_H__

