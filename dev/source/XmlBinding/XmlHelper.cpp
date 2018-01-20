#include "XmlHelper.h"

#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

#include <iostream>
using namespace std;

bool CXmlHelper::readCodetemplates( const QString& filename, QString& strCode )
{
// 	QString abFilename = QCoreApplication::applicationDirPath() + "/../config/xmlbinding/codetemplates/" + filename;

	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly|QFile::Text))
	{
		cout <<  "template file " << filename.toStdString() << " read error!" << endl;
		file.close();
		return false;
	}

	QTextStream in(&file);
	in.setCodec("UTF-8");
	strCode = in.readAll();
	file.close();

	return true;
}

bool CXmlHelper::writeCode( const QString& filename , const QString& strCode )
{
	QFile codeFile(filename);
	if (!codeFile.open(QIODevice::WriteOnly | QFile::Text))
	{
		cout << "write "+filename.toStdString()+".h"+" error!" << endl;
		codeFile.close();
		return false;
	}
	QTextStream out(&codeFile);
	out.setCodec("ANSI");
	out << strCode;
	out.flush();
	codeFile.close();

	return true;
}
