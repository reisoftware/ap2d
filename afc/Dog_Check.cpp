#include "stdafx.h"
#include "Dog_check.h"
#include "gsmh.h"
#include <windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

short int DogBytes, DogAddr;
unsigned long DogPassword,NewPassword;
unsigned long DogResult;
unsigned char DogCascade;
void * DogData;

namespace gelib{
	bool Dog_Check::is_exist()
		{
			DWORD dwStatus;
			dwStatus = DogCheck();
			if(dwStatus) 
					return false;
			return true;
		}
	bool Dog_Check::valid_dog()
		{
			if(!is_exist())
				return false;
			CHAR ReadData[12];
			DogAddr = 0;
			DogData = ReadData;
			DogBytes = 12;
			if(ReadDog())
				return false;
			if(ReadData[0]  != 0 ||
				ReadData[1] != 4 ||
				ReadData[2] != 1 ||
				ReadData[3] != 1 ||
				ReadData[4] != 8 ||
				ReadData[5] != 4 ||
				ReadData[6] != 7 ||
				ReadData[7] != 5 ||
				ReadData[8] != 3 ||
				ReadData[9] != 2 ||
				ReadData[10] != 0 ||
				ReadData[11] != 6 )
				return false;
			return true;
		}
}
