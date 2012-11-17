#pragma once

/////////////////////////////////////////////////////////////////////////////
// CxImage supported features
#define CXIMAGE_SUPPORT_ALPHA          1
#define CXIMAGE_SUPPORT_SELECTION      1
#define CXIMAGE_SUPPORT_TRANSFORMATION 1
#define CXIMAGE_SUPPORT_DSP            1
#define CXIMAGE_SUPPORT_LAYERS		   1
#define CXIMAGE_SUPPORT_INTERPOLATION  1

#define CXIMAGE_SUPPORT_DECODE	1
#define CXIMAGE_SUPPORT_ENCODE	1		//<vho><T.Peck>
#define	CXIMAGE_SUPPORT_WINDOWS 1
#define	CXIMAGE_SUPPORT_EXIF    1

/////////////////////////////////////////////////////////////////////////////
// CxImage supported formats
#define CXIMAGE_SUPPORT_BMP 1
#define CXIMAGE_SUPPORT_GIF 1
#define CXIMAGE_SUPPORT_JPG 1
#define CXIMAGE_SUPPORT_PNG	1
#define CXIMAGE_SUPPORT_ICO 1
#define CXIMAGE_SUPPORT_TIF 1
#define CXIMAGE_SUPPORT_TGA 1
#define CXIMAGE_SUPPORT_PCX 1
#define CXIMAGE_SUPPORT_WBMP 1
#define CXIMAGE_SUPPORT_WMF 1

// Jasper files
#define CXIMAGE_SUPPORT_JP2 0
#define CXIMAGE_SUPPORT_JPC 0
#define CXIMAGE_SUPPORT_PGX 0
#define CXIMAGE_SUPPORT_PNM 0
#define CXIMAGE_SUPPORT_RAS 0

#define CXIMAGE_SUPPORT_JBG 0		// GPL'd see ../jbig/copying.txt & ../jbig/patents.htm

#define CXIMAGE_SUPPORT_MNG 0
#define CXIMAGE_SUPPORT_SKA 1
#define CXIMAGE_SUPPORT_RAW 1
#define CXIMAGE_SUPPORT_PSD 1

/////////////////////////////////////////////////////////////////////////////
#define	CXIMAGE_MAX_MEMORY 268435456

#define CXIMAGE_DEFAULT_DPI 96

namespace CppImage
{
	static const char* CXIMAGE_ERR_NOFILE = "null file handler";
	static const char* CXIMAGE_ERR_NOIMAGE = "null image!!!";
}

#define CXIMAGE_SUPPORT_EXCEPTION_HANDLING 1
