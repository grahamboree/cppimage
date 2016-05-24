//
//  CxMemFile.h
//  cppimage
//
//  Created by Graham Pentheny on 11/10/12.
//  Copyright (c) 2012 Graham Pentheny. All rights reserved.
//

#pragma once

#include "CxFile.h"

namespace CppImage
{
	//////////////////////////////////////////////////////////
	class DLL_EXP CxMemFile : public CxFile
	{
	public:
		CxMemFile(uint8_t* inBuffer = NULL, uint32_t inSize = 0);
		~CxMemFile();

		bool Open();
		uint8_t* GetBuffer(bool inbDetachBuffer = true);

		virtual bool Close();
		virtual size_t Read(void* inBuffer, size_t inSize, size_t inCount);
		virtual size_t Write(const void* buffer, size_t size, size_t count);
		virtual bool Seek(int32_t offset, int32_t origin);
		virtual int32_t Tell();
		virtual int32_t Size();
		virtual bool Flush();
		virtual bool Eof();
		virtual int32_t Error();
		virtual bool PutC(uint8_t c);
		virtual int32_t GetC();
		virtual char* GetS(char* string, int32_t n);
		virtual int32_t Scanf(const char* format, void* output);

	protected:
		bool Alloc(uint32_t nBytes);
		void Free();

		uint8_t* mBuffer;
		uint32_t mSize;
		bool     mbFreeOnClose;
		int32_t  mPosition;  //current position
		int32_t  mEdge;  //buffer size
		bool     mbEOF;
	};
}
