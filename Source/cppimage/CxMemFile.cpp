//
//  CxMemFile.h
//  cppimage
//
//  Created by Graham Pentheny on 11/10/12.
//  Copyright (c) 2012 Graham Pentheny. All rights reserved.
//

#include "CxMemfile.h"

namespace CppImage
{
	//////////////////////////////////////////////////////////
	CxMemFile::CxMemFile(uint8_t* inBuffer, uint32_t inSize)
	{
		mBuffer = inBuffer;
		mPosition = 0;
		mSize = inSize;
		mEdge = inSize;
		mbFreeOnClose = (bool)(inBuffer == 0);
		mbEOF = false;
	}

	//////////////////////////////////////////////////////////
	CxMemFile::~CxMemFile()
	{
		Close();
	}

	//////////////////////////////////////////////////////////
	bool CxMemFile::Close()
	{
		if ((mBuffer) && (mbFreeOnClose))
		{
			free(mBuffer);
			mBuffer = NULL;
			mSize = 0;
		}
		return true;
	}

	//////////////////////////////////////////////////////////
	bool CxMemFile::Open()
	{
		if (mBuffer)
			return false;	// Can't re-open without closing first

		mPosition = 0;
		mSize = 0;
		mEdge = 0;
		mBuffer = (uint8_t*)malloc(1);
		mbFreeOnClose = true;

		return (mBuffer != 0);
	}

	//////////////////////////////////////////////////////////
	uint8_t* CxMemFile::GetBuffer(bool inbDetachBuffer)
	{
		//can only detach, avoid inadvertantly attaching to
		// memory that may not be ours [Jason De Arte]
		if (inbDetachBuffer)
			mbFreeOnClose = false;
		return mBuffer;
	}

	//////////////////////////////////////////////////////////
	size_t CxMemFile::Read(void* inBuffer, size_t inSize, size_t inCount)
	{
		if (inBuffer == NULL)
			return 0;

		if (mBuffer == NULL)
			return 0;

		if (mPosition >= (int32_t)mSize)
		{
			mbEOF = true;
			return 0;
		}

		int32_t nCount = (int32_t)(inCount * inSize);
		if (nCount == 0)
		{
			return 0;
		}

		int32_t nRead;
		if (mPosition + nCount > (int32_t)mSize)
		{
			mbEOF = true;
			nRead = (mSize - mPosition);
		}
		else
		{
			nRead = nCount;
		}

		memcpy(inBuffer, mBuffer + mPosition, nRead);
		mPosition += nRead;

		return (size_t)(nRead / inSize);
	}

	//////////////////////////////////////////////////////////
	size_t CxMemFile::Write(const void *buffer, size_t size, size_t count)
	{
		mbEOF = false;
		if (mBuffer == NULL)
			return 0;
		if (buffer == NULL)
			return 0;

		int32_t nCount = (int32_t)(count*size);
		if (nCount == 0)
			return 0;

		if ((mPosition + nCount > mEdge) && !Alloc(mPosition + nCount))
			return false;

		memcpy(mBuffer + mPosition, buffer, nCount);

		mPosition += nCount;

		if (mPosition > (int32_t)mSize)
			mSize = mPosition;
		
		return count;
	}

	//////////////////////////////////////////////////////////
	bool CxMemFile::Seek(int32_t offset, int32_t origin)
	{
		mbEOF = false;
		if (mBuffer == NULL)
			return false;
		int32_t lNewPos = mPosition;

		if (origin == SEEK_SET)
			lNewPos = offset;
		else if (origin == SEEK_CUR)
			lNewPos += offset;
		else if (origin == SEEK_END)
			lNewPos = mSize + offset;
		else
			return false;

		if (lNewPos < 0)
			lNewPos = 0;

		mPosition = lNewPos;
		return true;
	}

	//////////////////////////////////////////////////////////
	int32_t CxMemFile::Tell()
	{
		if (mBuffer == NULL)
			return -1;
		return mPosition;
	}

	//////////////////////////////////////////////////////////
	int32_t CxMemFile::Size()
	{
		if (mBuffer == NULL)
			return -1;
		return mSize;
	}

	//////////////////////////////////////////////////////////
	bool CxMemFile::Flush()
	{
		if (mBuffer == NULL)
			return false;
		return true;
	}

	//////////////////////////////////////////////////////////
	bool CxMemFile::Eof()
	{
		if (mBuffer == NULL)
			return true;
		return mbEOF;
	}

	//////////////////////////////////////////////////////////
	int32_t CxMemFile::Error()
	{
		if (mBuffer == NULL)
			return -1;
		return (mPosition > (int32_t)mSize);
	}

	//////////////////////////////////////////////////////////
	bool CxMemFile::PutC(uint8_t c)
	{
		mbEOF = false;
		if (mBuffer == nullptr) return false;

		if (mPosition >= mEdge && !Alloc(mPosition + 1))
			return false;

		mBuffer[mPosition++] = c;

		if (mPosition > (int32_t)mSize)
			mSize = mPosition;
		
		return true;
	}

	//////////////////////////////////////////////////////////
	int32_t CxMemFile::GetC()
	{
		if (mBuffer == NULL || mPosition >= (int32_t)mSize)
		{
			mbEOF = true;
			return EOF;
		}
		return *(uint8_t*)((uint8_t*)mBuffer + mPosition++);
	}

	//////////////////////////////////////////////////////////
	char* CxMemFile::GetS(char *string, int32_t n)
	{
		n--;
		int32_t c,i=0;
		while (i<n)
		{
			c = GetC();
			if (c == EOF)
				return 0;
			string[i++] = (char)c;
			if (c == '\n')
			{
				break;
			}
		}
		string[i] = 0;
		return string;
	}

	//////////////////////////////////////////////////////////
	int32_t	CxMemFile::Scanf(const char *format, void* output)
	{
		return 0;
	}

	//////////////////////////////////////////////////////////
	bool CxMemFile::Alloc(uint32_t dwNewLen)
	{
		if (dwNewLen > (uint32_t)mEdge)
		{
			// find new buffer size
			uint32_t dwNewBufferSize = (uint32_t)(((dwNewLen >> 16) + 1) << 16);

			// allocate new buffer
			if (mBuffer == NULL)
				mBuffer = (uint8_t*)malloc(dwNewBufferSize);
			else
				mBuffer = (uint8_t*)realloc(mBuffer, dwNewBufferSize);

			// I own this buffer now (caller knows nothing about it)
			mbFreeOnClose = true;

			mEdge = dwNewBufferSize;
		}
		return (mBuffer != 0);
	}

	//////////////////////////////////////////////////////////
	void CxMemFile::Free()
	{
		Close();
	}
}
