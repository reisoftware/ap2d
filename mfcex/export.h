#ifndef _MFCEX_EXPORT_H_
#define _MFCEX_EXPORT_H_

#ifdef  MFCEX_EXPORTS
#define AEXAPI __declspec(dllexport)
#else   
#define AEXAPI __declspec(dllimport)
#endif//API


#endif//FILE
