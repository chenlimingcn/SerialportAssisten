#include "XmlBinding_global.h"

#include <QCoreApplication>

QString getTplFilePath()
{
	return QCoreApplication::applicationDirPath() + "/../config/codetemplates/";
}
