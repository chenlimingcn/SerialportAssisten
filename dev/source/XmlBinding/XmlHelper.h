#ifndef XMLHELPER_H__
#define XMLHELPER_H__

#include <QString>

class CXmlHelper
{
public:
	static bool readCodetemplates(const QString& filename, QString& strCode);

	static bool writeCode(const QString& filename , const QString& strCode);
};
#endif // XMLHELPER_H__
