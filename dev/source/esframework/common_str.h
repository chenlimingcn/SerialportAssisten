// FILE common_str.h
//
//  创建日期 : 12-12-06
// 	作    者 : WangLu
//	Copyright (C) 2012 上海积成电子系统有限公司.
//  摘    要 : 
//
//
#ifndef __COMMON_STR_H__
#define __COMMON_STR_H__
#include <QString>
#include <QDate>
#include <QDateTime>
#include <QTime>
#include "esframework_global.h"

ESFRAMEWORK_API QString get_qstring(const char* str);

ESFRAMEWORK_API QString get_qstring( const QString& str);

#if defined(UNICODE) || defined(_UNICODE)

#ifdef _NATIVE_WCHAR_T_DEFINED
// QString get_qstring(const wchar_t* str){ return get_qstring((const unsigned short*)str); }
ESFRAMEWORK_API QString get_qstring(std::wstring str);
#endif 
ESFRAMEWORK_API QString get_qstring(const unsigned short* str);


#else
ESFRAMEWORK_API QString get_qstring(std::string str);
#endif

ESFRAMEWORK_API QString get_string(const QDate& date);

ESFRAMEWORK_API QString  get_string(const QDateTime& date);

ESFRAMEWORK_API QString get_string(const QTime& date);

#define NUMBER_2_QSTRING_DEFINE(type) \
inline QString get_qstring(type val) \
{ \
	return QString::number(val); \
}

NUMBER_2_QSTRING_DEFINE(int)
NUMBER_2_QSTRING_DEFINE(uint)
NUMBER_2_QSTRING_DEFINE(long)
NUMBER_2_QSTRING_DEFINE(ulong)
NUMBER_2_QSTRING_DEFINE(qlonglong)
NUMBER_2_QSTRING_DEFINE(qulonglong)

NUMBER_2_QSTRING_DEFINE(double)

#define Q_STR(x) get_qstring(x)

//从一个字符串生成可用于标记元素的keyword
ESFRAMEWORK_API  QString get_keyword(const QString& str);

#define K_STR(x) get_keyword(x)

#ifndef _T

#	if defined(UNICODE) || defined(_UNICODE)

#		define _T(x) L##x

#	else

#		define _T(x) ##x

#	endif

#endif

#endif
