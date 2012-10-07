
#pragma once

#include "CxFile.h"
//#include <TCHAR.h>

class DLL_EXP CxIOFile : public CxFile
{
public:
	CxIOFile(FILE* fp = NULL);

	~CxIOFile();

	bool Open(const TCHAR * filename, const TCHAR * mode);
	virtual bool Close();
	virtual size_t	Read(void *buffer, size_t size, size_t count);
	virtual size_t	Write(const void *buffer, size_t size, size_t count);
	virtual bool Seek(int32_t offset, int32_t origin);
	virtual int32_t Tell();
	virtual int32_t	Size();
	virtual bool	Flush();
	virtual bool	Eof();
	virtual int32_t	Error();
	virtual bool PutC(uint8_t c);
	virtual int32_t	GetC();
	virtual char *	GetS(char *string, int32_t n);
	virtual int32_t	Scanf(const char *format, void* output);
protected:
	FILE *m_fp;
	bool m_bCloseFile;
};

//////////////////////////////////////////////////////////
inline CxIOFile::CxIOFile(FILE* fp)
{
	m_fp = fp;
	m_bCloseFile = (bool)(fp==0);
}

//////////////////////////////////////////////////////////
inline CxIOFile::~CxIOFile()
{
	Close();
}

//////////////////////////////////////////////////////////
inline bool CxIOFile::Open(const TCHAR * filename, const TCHAR * mode)
{
	if (m_fp) return false;	// Can't re-open without closing first

	//m_fp = _tfopen(filename, mode);
	m_fp = fopen(filename, mode);
	if (!m_fp) return false;

	m_bCloseFile = true;

	return true;
}

//////////////////////////////////////////////////////////
inline bool CxIOFile::Close()
{
	int32_t iErr = 0;
	if ( (m_fp) && (m_bCloseFile) ){ 
		iErr = fclose(m_fp);
		m_fp = NULL;
	}
	return (bool)(iErr==0);
}

//////////////////////////////////////////////////////////
inline size_t CxIOFile::Read(void *buffer, size_t size, size_t count)
{
	if (!m_fp) return 0;
	return fread(buffer, size, count, m_fp);
}

//////////////////////////////////////////////////////////
inline size_t CxIOFile::Write(const void *buffer, size_t size, size_t count)
{
	if (!m_fp) return 0;
	return fwrite(buffer, size, count, m_fp);
}

//////////////////////////////////////////////////////////
inline bool CxIOFile::Seek(int32_t offset, int32_t origin)
{
	if (!m_fp) return false;
	return (bool)(fseek(m_fp, offset, origin) == 0);
}

//////////////////////////////////////////////////////////
inline int32_t CxIOFile::Tell()
{
	if (!m_fp) return 0;
	return static_cast<int32_t>(ftell(m_fp));
}

//////////////////////////////////////////////////////////
inline int32_t CxIOFile::Size()
{
	if (!m_fp) return -1;
	int32_t pos;
	int32_t size;
	pos = static_cast<int32_t>(ftell(m_fp));
	fseek(m_fp, 0, SEEK_END);
	size = static_cast<int32_t>(ftell(m_fp));
	fseek(m_fp, pos,SEEK_SET);
	return size;
}

//////////////////////////////////////////////////////////
inline bool CxIOFile::Flush()
{
	if (!m_fp) return false;
	return (bool)(fflush(m_fp) == 0);
}

//////////////////////////////////////////////////////////
inline bool CxIOFile::Eof()
{
	if (!m_fp) return true;
	return (bool)(feof(m_fp) != 0);
}

//////////////////////////////////////////////////////////
inline int32_t CxIOFile::Error()
{
	if (!m_fp) return -1;
	return ferror(m_fp);
}

//////////////////////////////////////////////////////////
inline bool CxIOFile::PutC(uint8_t c)
{
	if (!m_fp) return false;
	return (bool)(fputc(c, m_fp) == c);
}

//////////////////////////////////////////////////////////
inline int32_t CxIOFile::GetC()
{
	if (!m_fp) return EOF;
	return getc(m_fp);
}

//////////////////////////////////////////////////////////
inline char* CxIOFile::GetS(char *string, int32_t n)
{
	if (!m_fp) return NULL;
	return fgets(string,n,m_fp);
}

//////////////////////////////////////////////////////////
inline int32_t	CxIOFile::Scanf(const char *format, void* output)
{
	if (!m_fp) return EOF;
	return fscanf(m_fp, format, output);
}

