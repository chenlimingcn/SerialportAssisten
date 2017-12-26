
#ifndef ESFRAMEWORK_GLOBAL_H__
#define ESFRAMEWORK_GLOBAL_H__

#include <qglobal.h>

#ifdef _WIN32
#define  ESFRAMEWORK_DECL_EXPORT __declspec(dllexport)
#define  ESFRAMEWORK_DECL_IMPORT __declspec(dllimport)
#else
#define  ESFRAMEWORK_DECL_EXPORT __attribute__((visibility("default")))
#define  ESFRAMEWORK_DECL_IMPORT __attribute__((visibility("default")))
#endif // _WIN32

#ifdef ESFRAMEWORK_LIB
#define ESFRAMEWORK_API  ESFRAMEWORK_DECL_EXPORT
#else
#define ESFRAMEWORK_API  ESFRAMEWORK_DECL_IMPORT
#endif // ESFRAMEWORK_LIB

#endif //  ESFRAMEWORK_GLOBAL_H__
