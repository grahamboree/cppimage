//
//  CxIOFile.h
//  cppimage
//
//  Created by Graham Pentheny on 11/10/12.
//  Copyright (c) 2012 Graham Pentheny. All rights reserved.
//

#pragma once

#include "CxFile.h"
//#include <TCHAR.h>

namespace CppImage 
{
	class DLL_EXP CxIOFile : public CxFile
	{
	public:
		CxIOFile(FILE* inFilePointer = NULL);
		~CxIOFile();

		bool 			Open(const TCHAR* inFilename, const TCHAR* inMode);
		virtual bool 	Close();
		virtual size_t	Read(void* buffer, size_t size, size_t count);
		virtual size_t	Write(const void *buffer, size_t size, size_t count);
		virtual bool 	Seek(int32_t offset, int32_t origin);
		virtual int32_t Tell();
		virtual int32_t	Size();
		virtual bool	Flush();
		virtual bool	Eof();
		virtual int32_t	Error();
		virtual bool 	PutC(uint8_t c);
		virtual int32_t	GetC();
		virtual char *	GetS(char* string, int32_t n);
		virtual int32_t	Scanf(const char* format, void* output);
	protected:
		FILE* mFilePointer;
		bool mbCloseFile;
	};
}

namespace CppImage  
{
	//////////////////////////////////////////////////////////
	inline CxIOFile::CxIOFile(FILE* inFilePointer)
	{
		mFilePointer = inFilePointer;
		mbCloseFile = (inFilePointer == NULL);
	}

	//////////////////////////////////////////////////////////
	inline CxIOFile::~CxIOFile()
	{
		Close();
	}

	//////////////////////////////////////////////////////////
	inline bool CxIOFile::Open(const TCHAR * inFilename, const TCHAR * inMode)
	{
		if (mFilePointer != NULL)
			return false; // Can't re-open without closing first

		//mFilePointer = _tfopen(inFilename, inMode);
		mFilePointer = fopen(inFilename, inMode);
		if (!mFilePointer)
			return false;

		mbCloseFile = true;

		return true;
	}

	//////////////////////////////////////////////////////////
	inline bool CxIOFile::Close()
	{
		int32_t error = 0;
		if (mFilePointer != NULL && mbCloseFile)
		{ 
			error = fclose(mFilePointer);
			mFilePointer = NULL;
		}
		return (error == 0);
	}

	//////////////////////////////////////////////////////////
	inline size_t CxIOFile::Read(void* buffer, size_t size, size_t count)
	{
		if (!mFilePointer) return 0;
		return fread(buffer, size, count, mFilePointer);
	}

	//////////////////////////////////////////////////////////
	inline size_t CxIOFile::Write(const void* buffer, size_t size, size_t count)
	{
		if (!mFilePointer) return 0;
		return fwrite(buffer, size, count, mFilePointer);
	}

	//////////////////////////////////////////////////////////
	inline bool CxIOFile::Seek(int32_t offset, int32_t origin)
	{
		if (!mFilePointer) return false;
		return (fseek(mFilePointer, offset, origin) == 0);
	}

	//////////////////////////////////////////////////////////
	inline int32_t CxIOFile::Tell()
	{
		if (!mFilePointer) return 0;
		return static_cast<int32_t>(ftell(mFilePointer));
	}

	//////////////////////////////////////////////////////////
	inline int32_t CxIOFile::Size()
	{
		if (!mFilePointer) return -1;
		int32_t pos;
		int32_t size;
		pos = static_cast<int32_t>(ftell(mFilePointer));
		fseek(mFilePointer, 0, SEEK_END);
		size = static_cast<int32_t>(ftell(mFilePointer));
		fseek(mFilePointer, pos, SEEK_SET);
		return size;
	}

	//////////////////////////////////////////////////////////
	inline bool CxIOFile::Flush()
	{
		if (!mFilePointer) return false;
		return (fflush(mFilePointer) == 0);
	}

	//////////////////////////////////////////////////////////
	inline bool CxIOFile::Eof()
	{
		if (!mFilePointer) return true;
		return (feof(mFilePointer) != 0);
	}

	//////////////////////////////////////////////////////////
	inline int32_t CxIOFile::Error()
	{
		if (!mFilePointer) return -1;
		return ferror(mFilePointer);
	}

	//////////////////////////////////////////////////////////
	inline bool CxIOFile::PutC(uint8_t c)
	{
		if (!mFilePointer) return false;
		return (fputc(c, mFilePointer) == c);
	}

	//////////////////////////////////////////////////////////
	inline int32_t CxIOFile::GetC()
	{
		if (!mFilePointer) return EOF;
		return getc(mFilePointer);
	}

	//////////////////////////////////////////////////////////
	inline char* CxIOFile::GetS(char *string, int32_t n)
	{
		if (!mFilePointer) return NULL;
		return fgets(string,n,mFilePointer);
	}

	//////////////////////////////////////////////////////////
	inline int32_t	CxIOFile::Scanf(const char *format, void* output)
	{
		if (!mFilePointer) return EOF;
		return fscanf(mFilePointer, format, output);
	}
}
