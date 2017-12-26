
#include <QRegExp>

#include "common_str.h"

#if defined(UNICODE) || defined(_UNICODE)


#ifdef _NATIVE_WCHAR_T_DEFINED
 QString get_qstring(std::wstring str)
 {
 	return QString::fromStdWString(str);
 }

QString get_qstring(const wchar_t* str)
{	
	return QString::fromStdWString(std::wstring(str));
#else


QString get_qstring(const unsigned short* str)
{

	return QString::fromUtf16(str, -1);
#endif
}


#else
QString get_qstring(std::string str)
{
	return QString::fromStdString(str)
}

#endif

QString get_qstring( const QString& str)
{
	return str;
}

QString get_qstring(const char* str)
{
	return QString::fromLocal8Bit(str);
}

QString get_string( const QDate& date )
{
	return date.toString("yyyy-MM-dd");
}

QString get_string( const QDateTime& date )
{
	return date.toString("yyyy-MM-dd hh-mm-ss.zzz");
}

QString get_string( const QTime& date )
{
	return date.toString("hh-mm-ss.zzz");
}

QString get_keyword( const QString& str )
{
	QString keyword = str.trimmed();
	// modified by chenliming at 2012年12月15日18时00分54秒
	// bug:每次都指数级增加下划线
// 	keyword = keyword.replace(QRegExp("[\\s]*"), "_");
// 	keyword = keyword.replace(QRegExp("[^a-zA-Z0-9_]*"), "_");
	keyword = keyword.replace(QRegExp("[\\s]+"), "_");
	keyword = keyword.replace(QRegExp("[^a-zA-Z0-9_]+"), "_");

	// added by chenliming at 2012年12月15日19时04分44秒
	// bug:替换后全变为空串了
// 	if (str.isEmpty())
// 		str = Q_STR("_");

	return keyword;
}
