#ifndef XMLBASE_GLOBAL_H__
#define XMLBASE_GLOBAL_H__

#ifdef _WIN32
#define XMLBASE_DECL_EXPORT __declspec(dllexport)
#define XMLBASE_DECL_IMPORT __declspec(dllimport)
#else
#define XMLBASE_DECL_EXPORT __attribute__((visibility("default")))
#define XMLBASE_DECL_IMPORT __attribute__((visibility("default")))
#endif // _WIN32

#ifdef XMLBASE_LIB
#define XMLBASE_API XMLBASE_DECL_EXPORT
#else
#define XMLBASE_API XMLBASE_DECL_IMPORT
#endif // XMLBASE_LIB

#endif // XMLBASE_GLOBAL_H__
