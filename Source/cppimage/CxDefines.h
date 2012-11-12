#pragma once

#include "CxConfig.h"

#if /*defined(_AFXDLL)||*/ defined(_USRDLL)
#	define DLL_EXP __declspec(dllexport)
#elif defined(_MSC_VER) && (_MSC_VER < 1200)
#	define DLL_EXP __declspec(dllimport)
#else
#	define DLL_EXP
#endif

#if CXIMAGE_SUPPORT_EXCEPTION_HANDLING
#	 define cx_try try
#	 define cx_throw(message) throw(message)
#	 define cx_catch catch (const char *message)
#else
#	 define cx_try bool cx_error = false;
#	 define cx_throw(message) { cx_error = true; if (strcmp(message, "")) strncpy(info.szLastError, message, 255); goto cx_error_catch; }
#	 define cx_catch cx_error_catch: char message[] = ""; if (cx_error)
#endif

#if CXIMAGE_SUPPORT_JP2 || CXIMAGE_SUPPORT_JPC || CXIMAGE_SUPPORT_PGX || CXIMAGE_SUPPORT_PNM || CXIMAGE_SUPPORT_RAS
#	define CXIMAGE_SUPPORT_JASPER 1
#else
#	define CXIMAGE_SUPPORT_JASPER 0
#endif

#if CXIMAGE_SUPPORT_DSP
#	undef CXIMAGE_SUPPORT_TRANSFORMATION
#	define CXIMAGE_SUPPORT_TRANSFORMATION 1
#endif

#if CXIMAGE_SUPPORT_TRANSFORMATION || CXIMAGE_SUPPORT_TIF || CXIMAGE_SUPPORT_TGA || CXIMAGE_SUPPORT_BMP || CXIMAGE_SUPPORT_WINDOWS
#	define CXIMAGE_SUPPORT_BASICTRANSFORMATIONS 1
#endif

#if CXIMAGE_SUPPORT_DSP || CXIMAGE_SUPPORT_TRANSFORMATION
#	undef CXIMAGE_SUPPORT_INTERPOLATION
#	define CXIMAGE_SUPPORT_INTERPOLATION 1
#endif

#if (CXIMAGE_SUPPORT_DECODE == 0)
#	undef CXIMAGE_SUPPORT_EXIF
#	define CXIMAGE_SUPPORT_EXIF 0
#endif

#if defined (_WIN32_WCE)
#	undef CXIMAGE_SUPPORT_WMF
#	define CXIMAGE_SUPPORT_WMF 0
#endif

#if !defined(WIN32) && !defined(_WIN32_WCE)
#	undef CXIMAGE_SUPPORT_WINDOWS
#	define CXIMAGE_SUPPORT_WINDOWS 0
#endif

#ifndef min
#	define min(a,b) (((a) < (b)) ? (a) : (b))
#	define MIN(a,b) (((a) < (b)) ? (a) : (b))
//template<typename T>
//inline static T min(const T& a, const T& b) { return (a < b) ? a : b; }
#endif

#ifndef max
#	define max(a,b) (((a) > (b)) ? (a) : (b))
#	define MAX(a,b) (((a) > (b)) ? (a) : (b))
//template<typename T>
//inline static T max(const T& a, const T& b) { return (a > b) ? a : b; }
#endif

static const float PI = 3.141592653589793f;

/*#ifndef PI
#	define PI 3.141592653589793f
#endif*/

#if defined(WIN32) || defined(_WIN32_WCE)
#	include <windows.h>
#	include <tchar.h>
#endif

#include <stdio.h>
#include <math.h>

#ifdef __BORLANDC__
#	ifndef _COMPLEX_DEFINED
struct _complex
{
	double x;
	double y;
};
#	endif // ndef _COMPLEX_DEFINED

#	define _cabs(c) sqrt(c.x * c.x + c.y * c.y)
#endif // def __BORLANDC__

#if defined(WIN32) || defined(_WIN32_WCE)
#	include "stdint.h"
#endif

#if !defined(WIN32) && !defined(_WIN32_WCE)
#	include <stdint.h>
#	include <stdlib.h>
#	include <string.h>
#	include <ctype.h>

typedef uint32_t		COLORREF;
typedef void*			HANDLE;
typedef void*      		HRGN;
typedef unsigned char	BYTE;

/*
#	ifndef BOOL
#		define	BOOL bool
#	endif

#	ifndef TRUE
#		define	TRUE true
#	endif

#	ifndef FALSE
#		define	FALSE false
#	endif
*/

#	ifndef TCHAR
#		define TCHAR char
#		define _T
#	endif

struct Rect
{
	int32_t left;
	int32_t top;
	int32_t right;
	int32_t bottom;
};

struct Point
{
	int32_t x;
	int32_t y;
};

struct RGBQuad
{
	uint8_t rgbBlue;
	uint8_t rgbGreen;
	uint8_t rgbRed;
	uint8_t rgbReserved;
};

#	pragma pack(1)

struct BitmapInfoHeader
{
	uint32_t biSize;
	int32_t  biWidth;
	int32_t  biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	int32_t  biXPelsPerMeter;
	int32_t  biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
};

struct BitmapFileHeader
{
	uint16_t bfType;
	uint32_t bfSize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBits;
};

struct BitmapCoreHeader
{
	uint32_t bcSize;
	uint16_t bcWidth;
	uint16_t bcHeight;
	uint16_t bcPlanes;
	uint16_t bcBitCount;
};

struct RGBTriple
{
	uint8_t rgbtBlue;
	uint8_t rgbtGreen;
	uint8_t rgbtRed;
};

#	pragma pack()

#	define BI_RGB        0L
#	define BI_RLE8       1L
#	define BI_RLE4       2L
#	define BI_BITFIELDS  3L

#	define GetRValue(rgb)      ((uint8_t)(rgb))
#	define GetGValue(rgb)      ((uint8_t)(((uint16_t)(rgb)) >> 8))
#	define GetBValue(rgb)      ((uint8_t)((rgb) >> 16))
//#	define MACRO_RGB(r,g,b)          ((COLORREF)(((uint8_t)(r) | ((uint16_t)((uint8_t)(g)) << 8)) | (((uint32_t)(uint8_t)(b)) << 16)))
#	define RGB(r,g,b)          ((COLORREF)(((uint8_t)(r) | ((uint16_t)((uint8_t)(g)) << 8)) | (((uint32_t)(uint8_t)(b)) << 16)))
#if 0
template <typename T1, typename T2, typename T3>
inline COLORREF RGB(T1 r, T2 g, T2 b)
{
	/*
	return (COLORREF) ( (uint8_t) r << 16 |
						(uint8_t) g <<  8 |
						(uint8_t) b);
						*/

	return (COLORREF) ( (uint8_t) r |
						(uint8_t) g << 8 |
						(uint8_t) b << 16);
	//return (COLORREF)(((uint8_t)r | ((uint16_t)((uint8_t)g) << 8)) | ((uint32_t) ((uint8_t)b)) << 16);
}
#endif

#	ifndef _COMPLEX_DEFINED

struct _complex
{
	double x;
	double y;
};

#	endif // ndef _COMPLEX_DEFINED

#	define _cabs(c) sqrt(c.x*c.x+c.y*c.y)

#endif // !defined(WIN32) && !defined(_WIN32_WCE)

