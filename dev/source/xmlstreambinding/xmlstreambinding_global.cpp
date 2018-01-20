#include "xmlstreambinding_global.h"

#include <QCoreApplication>

QString getTplFilePath()
{
	return QCoreApplication::applicationDirPath() + "/../config/xmlstreambinding/codetemplates/";
}
