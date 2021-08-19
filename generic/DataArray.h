/*
 ******************************************************************************
 This file is part of xvault.

    xvault is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    xvault is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with xVault; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    architected and written by 
    matt raffel of microobjects inc 2003
    mattr@microobjects.com

        copyright (c) 2003 by matt raffel unless noted otherwise


 ******************************************************************************
*/
#ifndef _CDATA_ARRAY_H
#define _CDATA_ARRAY_H

#include <stdlib.h>
#include <time.h>

const int g_nGrowBy = 64;
const int g_nSearchThreshold = 8;
const int g_nSortThreshold = 8;

class CBaseRecord;

template <class CBaseRecord> class CDataArray
{
	int m_nSize;
	int m_nStoreSize;
	CBaseRecord* m_pData;
	int m_nSort;

protected:
	int m_nGrowBy;

public:

	CDataArray();
	CDataArray(const CBaseRecord* pData, const int nSize, const int nGrowBy = g_nGrowBy);
	virtual ~CDataArray();
	int Locate(const CBaseRecord& tData) const;
	int Find(const CBaseRecord& tData) const;
	void SetSize(const int nSize, const int nGrowBy = g_nGrowBy);
	int GetSize() const;
	CBaseRecord* GetDataPtr() const;
	const CBaseRecord& operator()(const int nIndex) const;
	CBaseRecord& operator[](const int nIndex);
	int Add(const CBaseRecord& tData);
	int Insert(const int nIndex, const CBaseRecord& tData);
	int Remove(const int nIndex);
	int SetAt(const int nIndex, const CBaseRecord& tData);
	void Push(const CBaseRecord& tData);
	CBaseRecord Pop();
	int GetSort() const { return m_nSort; }
	void SetSort(int nSort);
	virtual void Sort(const int nSort = 1);
	virtual void SortIndex(int* pIndex, const int nSort = 1) const;
};

#include "DataArray.inl"

#endif
