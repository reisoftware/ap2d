// md5.h: interface for the md5 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MD5_H__D12896A4_CCD6_4E02_B60A_FF8E4C8AFE85__INCLUDED_)
#define AFX_MD5_H__D12896A4_CCD6_4E02_B60A_FF8E4C8AFE85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#define SINGLE_ONE_BIT 0x80
#define BLOCK_SIZE 512
#define MOD_SIZE 448
#define APP_SIZE 64
#define BITS 8
// MD5 Chaining Variable
#define A 0x67452301UL
#define B 0xEFCDAB89UL
#define C 0x98BADCFEUL
#define D 0x10325476UL
// Creating own types
#ifdef UINT64
#undef UINT64
#endif
#ifdef UINT32
#undef UINT32
#endif
//typedef unsigned long long UINT64;
//typedef unsigned long UINT32;
typedef unsigned char UINT8;
typedef struct
{
	char * message;
	UINT64 length;
}STRING;
const UINT32 X[4][2] = {{0, 1}, {1, 5}, {5, 3}, {0, 7}};
// Constants for MD5 transform routine.
const UINT32 S[4][4] = {
	{ 7, 12, 17, 22 },
	{ 5, 9, 14, 20 },
	{ 4, 11, 16, 23 },
	{ 6, 10, 15, 21 }
};
// F, G, H and I are basic MD5 functions.
static UINT32 F( UINT32 X, UINT32 Y, UINT32 Z )
{
	return ( X & Y ) | ( ~X & Z );
}
static UINT32 G( UINT32 X, UINT32 Y, UINT32 Z )
{
	return ( X & Z ) | ( Y & ~Z );
}
static UINT32 H( UINT32 X, UINT32 Y, UINT32 Z )
{
	return X ^ Y ^ Z;
}
static UINT32 I( UINT32 X, UINT32 Y, UINT32 Z )
{
	return Y ^ ( X | ~Z );
}
// rotates x left s bits.
static UINT32 rotate_left( UINT32 x, UINT32 s )
{
	return ( x << s ) | ( x >> ( 32 - s ) );
}
// Pre-processin
UINT32 count_padding_bits ( UINT32 length );
STRING append_padding_bits ( char * argv );

void cal_hash_val(STRING r_string,UINT8 *r);




#endif // !defined(AFX_MD5_H__D12896A4_CCD6_4E02_B60A_FF8E4C8AFE85__INCLUDED_)
