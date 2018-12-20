#ifndef _AFC_EXPORT_H_
#define _AFC_EXPORT_H_

#ifdef  AFC_EXPORTS
#define AFCAPI __declspec(dllexport)
#else
#define AFCAPI __declspec(dllimport)
#endif
#pragma warning (disable:4786)
#pragma warning (disable:4251)

#endif//FILE
