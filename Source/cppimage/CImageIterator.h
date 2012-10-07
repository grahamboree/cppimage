/*
 * File:	CImageIterator.h
 * Purpose:	Declaration of the Platform Independent Image Base Class
 * Author:	Alejandro Aguilar Sierra
 * Created:	1995
 * Copyright:	(c) 1995, Alejandro Aguilar Sierra <asierra(at)servidor(dot)unam(dot)mx>
 *
 * 07/08/2001 Davide Pizzolato - www.xdp.it
 * - removed slow loops
 * - added safe checks
 *
 * Permission is given by the author to freely redistribute and include
 * this code in any program as int32_t as this credit is given where due.
 *
 * COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, WITHOUT WARRANTY
 * OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES
 * THAT THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
 * OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE COVERED
 * CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT
 * THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY NECESSARY
 * SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF WARRANTY CONSTITUTES AN ESSENTIAL
 * PART OF THIS LICENSE. NO USE OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
 * THIS DISCLAIMER.
 *
 * Use at your own risk!
 * ==========================================================
 */

#pragma once

#include "CxImage.h"
#include "CxDefines.h"

//////////////////////////////////////////////////////////////////////////
class CImageIterator
{
	friend class CxImage;

protected:
	int32_t  Itx;
	int32_t  Ity;		// Counters
	int32_t  Stepx;
	int32_t  Stepy;
	uint8_t* IterImage;	//  Image pointer
	CxImage* mImage;

public:
	// Constructors
	CImageIterator();
	CImageIterator(CxImage *image);
	
	// Operators
	operator CxImage* ();

	// Iterators
	bool	ItOK();
	void	Reset();
	void	Upset();

	void	 GetRow(uint8_t* buf, int32_t n);
	uint8_t* GetRow();
	uint8_t* GetRow(int32_t n);
	void	 SetRow(uint8_t* buf, int32_t n);

	uint8_t GetByte();
	void	SetByte(uint8_t b);

	bool NextRow();
	bool PrevRow();

	bool NextByte();
	bool PrevByte();

	void GetSteps(int32_t* x, int32_t* y);
	void SetSteps(int32_t x, int32_t y = 0);

	bool NextStep();
	bool PrevStep();

	int32_t GetY();
	void 	SetY(int32_t y);	/* AD - for interlace */

	bool GetCol(uint8_t* outCol, uint32_t inColIndex);
	bool SetCol(uint8_t* inCol, uint32_t inColIndex);
};

//////////////////////////////////////////////////////////////////////////
inline void CImageIterator::SetByte(uint8_t b)
{
	IterImage[Itx] = b;
}

//////////////////////////////////////////////////////////////////////////
inline uint8_t CImageIterator::GetByte()
{
	return IterImage[Itx];
}

//////////////////////////////////////////////////////////////////////////
inline void CImageIterator::SetSteps(int32_t x, int32_t y)
{
	Stepx = x;
	Stepy = y;
}

//////////////////////////////////////////////////////////////////////////
inline void CImageIterator::GetSteps(int32_t* x, int32_t* y)
{
	*x = Stepx;
	*y = Stepy;
}

//////////////////////////////////////////////////////////////////////////
inline int32_t CImageIterator::GetY()
{
	return Ity;
}

//////////////////////////////////////////////////////////////////////////
inline CImageIterator::CImageIterator(void)
{
	mImage = NULL;
	IterImage = 0;
	Itx = 0;
	Ity = 0;
	Stepx = 0;
	Stepy = 0;
}

/////////////////////////////////////////////////////////////////////
inline CImageIterator::CImageIterator(CxImage* imageImpl)
: mImage(imageImpl)
{
	if (mImage != NULL)
		IterImage = mImage->GetBits();
	Itx = 0;
	Ity = 0;
	Stepx = 0;
	Stepy = 0;
}

/////////////////////////////////////////////////////////////////////
inline CImageIterator::operator CxImage* ()
{
	return mImage;
}

/////////////////////////////////////////////////////////////////////
inline bool CImageIterator::ItOK()
{
	return (mImage != NULL) && mImage->IsInside(Itx, Ity);
	/*
	if (mImage)
	{
		return mImage->IsInside(Itx, Ity);
	}
	else
	{
		return false;
	}*/
}

/////////////////////////////////////////////////////////////////////
inline void CImageIterator::Reset()
{
	if (mImage != NULL)
		IterImage = mImage->GetBits();
	else
		IterImage = 0;
	Itx = 0;
	Ity = 0;
}
/////////////////////////////////////////////////////////////////////
inline void CImageIterator::Upset()
{
	Itx = 0;
	Ity = mImage->GetHeight() - 1;
	IterImage = mImage->GetBits() + mImage->GetEffWidth() * (mImage->GetHeight() - 1);
}

/////////////////////////////////////////////////////////////////////
inline bool CImageIterator::NextRow()
{
	if (++Ity >= (int32_t)mImage->GetHeight())
		return 0;
	IterImage += mImage->GetEffWidth();
	return 1;
}

/////////////////////////////////////////////////////////////////////
inline bool CImageIterator::PrevRow()
{
	if (--Ity < 0)
		return false;
	IterImage -= mImage->GetEffWidth();
	return true;
}

//////////////////////////////////////////////////////////////////////////
/* AD - for interlace */
inline void CImageIterator::SetY(int32_t y)
{
	if ((y < 0) || (y > (int32_t)mImage->GetHeight()))
		return;
	Ity = y;
	IterImage = mImage->GetBits() + mImage->GetEffWidth()*y;
}

/////////////////////////////////////////////////////////////////////
inline void CImageIterator::SetRow(uint8_t *buf, int32_t n)
{
	if (n<0)
	{
		n = (int32_t)mImage->GetEffWidth();
	}
	else
	{
		n = min(n, (int32_t)mImage->GetEffWidth());
	}

	if ((IterImage!=NULL)&&(buf!=NULL)&&(n>0))
	{
		memcpy(IterImage,buf,n);
	}
}

/////////////////////////////////////////////////////////////////////
inline void CImageIterator::GetRow(uint8_t *buf, int32_t n)
{
	if ((IterImage!=NULL)&&(buf!=NULL)&&(n>0))
	{
		memcpy(buf,IterImage,min(n,(int32_t)mImage->GetEffWidth()));
	}
}

/////////////////////////////////////////////////////////////////////
inline uint8_t* CImageIterator::GetRow()
{
	return IterImage;
}

/////////////////////////////////////////////////////////////////////
inline uint8_t* CImageIterator::GetRow(int32_t n)
{
	SetY(n);
	return IterImage;
}

/////////////////////////////////////////////////////////////////////
inline bool CImageIterator::NextByte()
{
	if (++Itx < (int32_t)mImage->GetEffWidth())
	{
		return 1;
	}
	else
	{
		if (++Ity < (int32_t)mImage->GetHeight())
		{
			IterImage += mImage->GetEffWidth();
			Itx = 0;
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

/////////////////////////////////////////////////////////////////////
inline bool CImageIterator::PrevByte()
{
	if (--Itx >= 0)
	{
		return 1;
	}
	else
	{
		if (--Ity >= 0)
		{
			IterImage -= mImage->GetEffWidth();
			Itx = 0;
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

/////////////////////////////////////////////////////////////////////
inline bool CImageIterator::NextStep()
{
	Itx += Stepx;
	if (Itx < (int32_t)mImage->GetEffWidth())
	{
		return 1;
	}
	else
	{
		Ity += Stepy;
		if (Ity < (int32_t)mImage->GetHeight())
		{
			IterImage += mImage->GetEffWidth();
			Itx = 0;
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

/////////////////////////////////////////////////////////////////////
inline bool CImageIterator::PrevStep()
{
	Itx -= Stepx;
	if (Itx >= 0)
	{
		return 1;
	}
	else
	{       
		Ity -= Stepy;
		if (Ity >= 0 && Ity < (int32_t)mImage->GetHeight())
		{
			IterImage -= mImage->GetEffWidth();
			Itx = 0;
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

/////////////////////////////////////////////////////////////////////
inline bool CImageIterator::GetCol(uint8_t* outCol, uint32_t inColIndex)
{
	if ((outCol == NULL) ||
		(mImage->GetBpp() < 8) ||
		(inColIndex >= mImage->GetWidth()))
	{
		return 0;
	}
	uint32_t h = mImage->GetHeight();
	//uint32_t line = mImage->GetEffWidth();
	uint8_t bytes = (uint8_t)(mImage->GetBpp() >> 3);
	uint8_t* pSrc;
	for (uint32_t y = 0; y < h; y++)
	{
		pSrc = mImage->GetBits(y) + inColIndex * bytes;
		for (uint8_t w = 0; w < bytes; w++)
		{
			*outCol++=*pSrc++;
		}
	}
	return 1;
}

/////////////////////////////////////////////////////////////////////
inline bool CImageIterator::SetCol(uint8_t* inCol, uint32_t inColIndex)
{
	if ((inCol == 0) ||
		(mImage->GetBpp() < 8) ||
		(inColIndex >= mImage->GetWidth()))
	{
		return 0;
	}
	uint32_t h = mImage->GetHeight();
	//uint32_t line = mImage->GetEffWidth();
	uint8_t bytes = (uint8_t)(mImage->GetBpp() >> 3);
	uint8_t* pSrc;
	for (uint32_t y = 0; y < h; y++)
	{
		pSrc = mImage->GetBits(y) + inColIndex * bytes;
		for (uint8_t w = 0; w < bytes; w++)
		{
			*pSrc++=*inCol++;
		}
	}
	return 1;
}
