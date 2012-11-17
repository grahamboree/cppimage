//
//  CxFile.h
//  cppimage
//
//  Created by Graham Pentheny on 11/10/12.
//  Copyright (c) 2012 Graham Pentheny. All rights reserved.
//

#pragma once

#if defined (WIN32) || defined (_WIN32_WCE)
#	include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>

#include "CxDefines.h"

namespace CppImage 
{
	//////////////////////////////////////////////////////////////////////////
	class CxFile
	{
	public:
		CxFile() {}
		virtual ~CxFile() {}

		virtual bool	Close() = 0;
		virtual bool	Eof()   = 0;
		virtual int32_t	Error() = 0;
		virtual bool	Flush() = 0;
		virtual int32_t	GetC()  = 0;
		virtual char*	GetS(char* string, int32_t n) = 0;
		virtual bool	PutC(uint8_t c);
		virtual size_t	Read(void* buffer, size_t size, size_t count) = 0;
		virtual int32_t	Scanf(const char* format, void* output) = 0;
		virtual bool	Seek(int32_t offset, int32_t origin) = 0;
		virtual int32_t	Size() = 0;
		virtual int32_t	Tell() = 0;
		virtual size_t	Write(const void* buffer, size_t size, size_t count) = 0;
	private:
		// Disabled copy constructor and assignment operator.
		CxFile(const CxFile&);
		CxFile& operator=(const CxFile&);
	};
}

namespace CppImage 
{
	//////////////////////////////////////////////////////////////////////////
	inline bool	CxFile::PutC(uint8_t c)
	{
		// Default implementation
		size_t nWrote = Write(&c, 1, 1);
		return (nWrote == 1);
	}
}
