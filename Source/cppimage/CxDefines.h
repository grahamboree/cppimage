#pragma once

#include <algorithm>

#if defined(WIN32) || defined(_WIN32_WCE)
#	include <windows.h>
#	include <tchar.h>
#else
#	include <stdint.h>
#	include <stdlib.h>
#	include <string.h>
#	include <ctype.h>
#endif

#include "CxConfig.h"

#include <stdio.h>
#include <math.h>

#if defined(WIN32) || defined(_WIN32_WCE)
#	include "stdint.h"
#endif

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

namespace CppImage
{
//#	define min(a,b) (((a) < (b)) ? (a) : (b))
//#	define MIN(a,b) (((a) < (b)) ? (a) : (b))
//template<typename T>
//inline static T min(const T& a, const T& b) { return (a < b) ? a : b; }
//#	define min std::min
	
//#	define max(a,b) (((a) > (b)) ? (a) : (b))
//#	define MAX(a,b) (((a) > (b)) ? (a) : (b))
//template<typename T>
//inline static T max(const T& a, const T& b) { return (a > b) ? a : b; }
	using namespace std;

	static const float PI = 3.141592653589793f;
	
	static const long int BI_RGB		= 0L;
	static const long int BI_RLE8		= 1L;
	static const long int BI_RLE4		= 2L;
	static const long int BI_BITFIELDS	= 3L;

	typedef void*			HANDLE;
	typedef void*      		HRGN;
	typedef unsigned char	BYTE;

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

#	pragma pack(push, 1)
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
#	pragma pack(pop)


#ifdef CPPIMAGE_TESTING
#	define MACRO_GetRValue(rgb)      ((uint8_t)(rgb))
#	define MACRO_GetGValue(rgb)      ((uint8_t)(((uint16_t)(rgb)) >> 8))
#	define MACRO_GetBValue(rgb)      ((uint8_t)((rgb) >> 16))
	
#	define MACRO_RGB(r,g,b)          ((COLORREF)(((uint8_t)(r) | ((uint16_t)((uint8_t)(g)) << 8)) | (((uint32_t)(uint8_t)(b)) << 16)))
	
//#	define RGB2GRAY(r,g,b) (((b)*114 + (g)*587 + (r)*299)/1000)
#	define MACRO_RGB2GRAY(r,g,b) (((b)*117 + (g)*601 + (r)*306) >> 10)
#endif

#if 1
	//////////////////////////////////////////////////////////////////////////
	class COLORREF
	{
	public:
		inline COLORREF(uint8_t r, uint8_t g, uint8_t b)
		: mValue(static_cast<uint32_t>(r) << 0 |
				 static_cast<uint32_t>(g) << 8 |
				 static_cast<uint32_t>(b) << 16)
		{}
		
		inline COLORREF(uint32_t rgb) : mValue(rgb) {}
		
		inline uint8_t GetRValue() const { return static_cast<uint8_t>(mValue); }
		inline uint8_t GetGValue() const { return static_cast<uint8_t>(mValue >> 8); }
		inline uint8_t GetBValue() const { return static_cast<uint8_t>(mValue >> 16); }
		
		inline operator uint8_t() { return static_cast<uint8_t>(mValue); }
		inline operator uint16_t() { return static_cast<uint16_t>(mValue); }
		inline operator uint32_t() { return mValue; }
		inline bool operator==(const COLORREF& color) { return color.mValue == mValue; }
		inline uint32_t operator >>(int inShift) const { return mValue >> inShift; }
		inline uint32_t operator <<(int inShift) const { return mValue << inShift; }
	private:
		uint32_t mValue;
	};
	
	// For compatibility..
	static inline COLORREF RGB(uint8_t r, uint8_t g, uint8_t b) { return COLORREF(r, g, b); }
	static inline uint8_t GetRValue(COLORREF rgb) { return rgb.GetRValue(); }
	static inline uint8_t GetGValue(COLORREF rgb) { return rgb.GetGValue(); }
	static inline uint8_t GetBValue(COLORREF rgb) { return rgb.GetBValue(); }
	
#else
	typedef uint32_t COLORREF;
	
	static inline uint8_t GetRValue(COLORREF rgb) { return static_cast<uint8_t>(rgb); }
	static inline uint8_t GetGValue(COLORREF rgb) { return static_cast<uint16_t>(rgb) >> 8; }
	static inline uint8_t GetBValue(COLORREF rgb) { return static_cast<uint8_t>(rgb >> 16); }

	static inline COLORREF RGB(uint8_t r, uint8_t g, uint8_t b)
	{
		return static_cast<COLORREF>(static_cast<uint32_t>(r) << 0 |
									 static_cast<uint32_t>(g) << 8 |
									 static_cast<uint32_t>(b) << 16);
	}
#endif
	
	//////////////////////////////////////////////////////////////////////////
	template<typename T>
	inline T RGB2GRAY(const T r, const T g, const T b)
	{
		return (b * 117 + g * 601 + r * 306) >> 10;
	}
	
#if 1
	//////////////////////////////////////////////////////////////////////////
	class Complex
	{
	public:
		inline Complex(double inX, double inY) : mX(inX), mY(inY) {}
		inline double Abs() const { return sqrt(mX * mX + mY * mY); }
	private:
		double mX;
		double mY;
	};
	
	// Compatibility...
	typedef Complex _complex;
	static inline double _cabs(const _complex& c) { return c.Abs(); }
#else
	struct _complex
	{
		double x;
		double y;
	};
#	ifdef CPPIMAGE_TESTING
#		define MACRO__cabs(c) sqrt(c.x*c.x+c.y*c.y)
#	endif
	static inline double _cabs(const _complex& c) { return sqrt(c.x * c.x + c.y * c.y); }
#endif
}

using namespace CppImage;

