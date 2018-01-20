#ifndef XMLGLOBALCODE_H__
#define XMLGLOBALCODE_H__

#include <QDomDocument>
#include <QList>

#include "XmlCodeBase.h"

class CXmlGlobalCode : public CXmlCodeBase
{
public:
	CXmlGlobalCode();
	~CXmlGlobalCode();

	virtual bool readfile(const QString& filename);

	virtual bool build();

	// virtual QString outPath() const;

protected:
	void generateExportfile();

	QString templateDir();
};

#endif // XMLGLOBALCODE_H__
