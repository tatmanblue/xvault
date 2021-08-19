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
#ifndef _DATA_ARRAY_IMPLMENATION_INLINE
#define _DATA_ARRAY_IMPLMENATION_INLINE
#include "stdafx.h"

#include "dataarray.h"

#define XYSWAP(x,y) {int nXYSwap=x;x=y;y=nXYSwap;}

template <class CBaseRecord>
CDataArray<CBaseRecord>::CDataArray()
{
	m_nSize = m_nStoreSize = 0;
	m_nGrowBy = g_nGrowBy;
	m_pData = (CBaseRecord*)0;
	m_nSort = 0;
};

template <class CBaseRecord>
CDataArray<CBaseRecord>::CDataArray(const CBaseRecord* pData, const int nSize, const int nGrowBy)
{
	m_nSize = m_nStoreSize = 0;
	m_nGrowBy = nGrowBy;
	m_pData = (CBaseRecord*)0;
	m_nSort = 0;
	SetSize(nSize,nGrowBy);
	for(int i=0;i<m_nSize;i++) m_pData[i] = pData[i];
}

template <class CBaseRecord>
CDataArray<CBaseRecord>::~CDataArray()
{
	delete []m_pData;
};

template <class CBaseRecord>
void CDataArray<CBaseRecord>::SetSort(const int nSort)
{
	if(nSort!=m_nSort) Sort(nSort);
}

template <class CBaseRecord>
void CDataArray<CBaseRecord>::SetSize(const int nSize, const int nGrowBy)
{
	if(nSize<0||nGrowBy<=0) return;
	
	if(nSize>m_nSize) m_nSort = 0;

	m_nGrowBy = nGrowBy;

	if(nSize>(m_nSize-m_nGrowBy)&&nSize<=m_nStoreSize)
	{
		m_nSize = nSize;
		return;
	}

	int nCount = nSize>m_nSize?m_nSize:nSize;
	m_nSize = nSize;	
	m_nStoreSize = 0;
	while(m_nStoreSize<m_nSize) m_nStoreSize += m_nGrowBy;
	
	CBaseRecord* pData = new CBaseRecord[m_nStoreSize];
	for(int i=0; i<nCount; i++) 
      pData[i] = m_pData[i];

	delete []m_pData;
	m_pData = pData;
};

template <class CBaseRecord> 
int CDataArray<CBaseRecord>::GetSize() const
{
	return m_nSize;
}

template <class CBaseRecord>
CBaseRecord* CDataArray<CBaseRecord>::GetDataPtr() const
{
	return m_pData;
}

template <class CBaseRecord>
int CDataArray<CBaseRecord>::Add(const CBaseRecord& tData)
{
	int nSort = m_nSort;
	int nIndex = Locate(tData);
	Insert(nIndex, tData);
	m_nSort = nSort;
	return nIndex;
}

template <class CBaseRecord>
int CDataArray<CBaseRecord>::Locate(const CBaseRecord& tData) const
{
	int nIndex = -1;
	int nMin, nMax, nMid;
	if(m_nSort==0||m_nSize==0) nIndex = m_nSize;
	else 
	{
		nMin = 0;
		nMax = m_nSize-1;
		while(nMax-nMin>1)
		{
			nMid = (nMax+nMin)/2;
			if(m_nSort>0)
			{
				if(tData<m_pData[nMid]) nMax = nMid;
				else nMin = nMid;
			}
			else
			{
				if(m_pData[nMid]<tData) nMax = nMid;
				else nMin = nMid;
			}
		}
		if(m_nSort>0)
		{
			if(tData<m_pData[nMin]) nIndex = nMin;
			else if(tData<m_pData[nMax]) nIndex = nMax;
			else nIndex = nMax+1;
		}
		else
		{
			if(m_pData[nMin]<tData) nIndex = nMin;
			else if(m_pData[nMax]<tData) nIndex = nMax;
			else nIndex = nMax+1;
		}
	}
	return nIndex;
}

template <class CBaseRecord>
int CDataArray<CBaseRecord>::Find(const CBaseRecord& tData) const
{
	if(m_nSort==0||m_nSize< g_nSearchThreshold)
	{
		for(int i=0;i<m_nSize;i++)
		{
			if(m_pData[i]==tData) return i;
		}
		return -1;
	}
	if(m_pData[0]==tData)
	{
		return 0;
	}
	else if(m_pData[m_nSize-1]==tData)
	{
		return m_nSize-1;
	}
	int nMid, nMin = 0, nMax = m_nSize-1;
	while(nMax-nMin>1)
	{
		nMid = (nMax+nMin)/2;
		if(m_pData[nMid]==tData)
		{
			return nMid;
		}
		if(m_nSort>0)
		{
			if(m_pData[nMid]<tData) nMin = nMid;
			else nMax = nMid;
		}
		else
		{
			if(tData<m_pData[nMid]) nMin = nMid;
			else nMax = nMid;
		}
	}
	return -1;
}

template <class CBaseRecord>
int CDataArray<CBaseRecord>::Insert(const int nIndex, const CBaseRecord& tData)
{
	if(nIndex<0||nIndex>m_nSize) 
	{
		return -1;
	}
	m_nSort = 0;
	int nSegmentSize = m_nSize-nIndex;
	SetSize(m_nSize+1,m_nGrowBy);
	if(nSegmentSize>0)
	{
		for(int i=nSegmentSize-1;i>=0;i--)
		{
			m_pData[i+nIndex+1] = m_pData[i+nIndex];
		}
	}
	m_pData[nIndex] = tData;
	return nIndex;
}

template <class CBaseRecord>
int CDataArray<CBaseRecord>::Remove(const int nIndex)
{
	if(nIndex<0||nIndex>=m_nSize)
	{
		return -1;
	}
	int nSegmentSize = m_nSize-nIndex-1;
	if(nSegmentSize>0)
	{
		for(int i=0;i<nSegmentSize;i++)
		{
			m_pData[nIndex+i] = m_pData[nIndex+i+1];
		}
	}
	m_nSize--;
	return m_nSize;
}

template <class CBaseRecord>
int CDataArray<CBaseRecord>::SetAt(const int nIndex, const CBaseRecord& tData)
{
	if(nIndex<0||nIndex>=m_nSize)
	{
		return -1;
	}
	m_nSort = 0;
	m_pData[nIndex] = tData;
	return nIndex;
}
	
template <class CBaseRecord>
void CDataArray<CBaseRecord>::Push(const CBaseRecord& tData)
{
	m_nSort = 0;
	Add(tData);
}

template <class CBaseRecord>
CBaseRecord CDataArray<CBaseRecord>::Pop()
{
	m_nSize--;
	return m_pData[m_nSize];
}
	
template <class CBaseRecord>
const CBaseRecord& CDataArray<CBaseRecord>::operator()(const int nIndex) const
{
	return m_pData[nIndex];
}

template <class CBaseRecord>
CBaseRecord& CDataArray<CBaseRecord>::operator[](const int nIndex)
{
	return m_pData[nIndex];
}

template <class CBaseRecord>
void CDataArray<CBaseRecord>::Sort(const int nSort)
{
	if(nSort>0&&m_nSort>0||nSort<0&&m_nSort<0||nSort==0)
	{
		return;
	}
	CBaseRecord* pData = new CBaseRecord[m_nStoreSize];
	int* pIndex = new int[m_nSize];
	for(int i=0;i<m_nSize;i++) pIndex[i] = i;	
	SortIndex(pIndex, nSort);
	for(int j=0;j<m_nSize;j++) pData[j] = m_pData[pIndex[j]];
	delete []pIndex;
	delete []m_pData;
	m_pData = pData;
	m_nSort = nSort;
}

	
template <class CBaseRecord>
void CDataArray<CBaseRecord>::SortIndex(int* pIndex, const int nSort) const
{
	if(m_nSize==0||nSort==0) 
	{
		return;
	}
	
	int i,j,k;
	int nMin, nMax;
	int nTemp1, nTemp2;
	CDataArray<int> theStack;	
	int* pRefIndex = new int[m_nSize];
	for(i=0;i<m_nSize;i++) pRefIndex[i] = i;
	
	theStack.Push(0);
	theStack.Push(m_nSize-1);

	while(theStack.GetSize()>0)
	{
		nMax = theStack.Pop();
		nMin = theStack.Pop();
		if(nMax-nMin < g_nSortThreshold)
		{
			for(i=nMin+1;i<=nMax;i++)
			{
				nTemp1 = pIndex[i];
				nTemp2 = pRefIndex[i];	
				j = i-1;
				if(nSort>0)
				{
					while(j>=nMin&&(m_pData[nTemp1]<m_pData[pIndex[j]]||pRefIndex[j]>nTemp2&&m_pData[pIndex[j]]==m_pData[nTemp1])) j--;
				}
				else
				{
					while(j>=nMin&&(m_pData[pIndex[j]]<m_pData[nTemp1]||pRefIndex[j]>nTemp2&&m_pData[pIndex[j]]==m_pData[nTemp1])) j--;
				}
				if(j+1<i)
				{
					for(k=i;k>j+1;k--)
					{
						pIndex[k] = pIndex[k-1];
						pRefIndex[k] = pRefIndex[k-1];
					}
					pIndex[j+1] = nTemp1;
					pRefIndex[j+1] = nTemp2;
				}
			}
		}
		else
		{
			static bool bInit = true;
			if(bInit)
			{
				bInit = false;
				srand(time(NULL));
			}

			i = nMin + (rand()% (nMax - nMin )) + 1; 

			XYSWAP(pIndex[nMin],pIndex[i]);
			XYSWAP(pRefIndex[nMin],pRefIndex[i]);
			if(nSort>0)
			{
				if(m_pData[pIndex[nMin]]<m_pData[pIndex[nMin+1]]||pRefIndex[nMin+1]>pRefIndex[nMin]&&m_pData[pIndex[nMin+1]]==m_pData[pIndex[nMin]]) 
				{
					XYSWAP(pIndex[nMin+1],pIndex[nMin]);
					XYSWAP(pRefIndex[nMin+1],pRefIndex[nMin]);
				}
				if(m_pData[pIndex[nMax]]<m_pData[pIndex[nMin]]||pRefIndex[nMin]>pRefIndex[nMax]&&m_pData[pIndex[nMin]]==m_pData[pIndex[nMax]]) 
				{
					XYSWAP(pIndex[nMax],pIndex[nMin]);
					XYSWAP(pRefIndex[nMax],pRefIndex[nMin]);
				}
				if(m_pData[pIndex[nMin]]<m_pData[pIndex[nMin+1]]||pRefIndex[nMin+1]>pRefIndex[nMin]&&m_pData[pIndex[nMin+1]]==m_pData[pIndex[nMin]]) 
				{
					XYSWAP(pIndex[nMin+1],pIndex[nMin]);
					XYSWAP(pRefIndex[nMin+1],pRefIndex[nMin]);
				}
			}
			else
			{
				if(m_pData[pIndex[nMin+1]]<m_pData[pIndex[nMin]]||pRefIndex[nMin+1]>pRefIndex[nMin]&&m_pData[pIndex[nMin+1]]==m_pData[pIndex[nMin]]) 
				{
					XYSWAP(pIndex[nMin+1],pIndex[nMin]);
					XYSWAP(pRefIndex[nMin+1],pRefIndex[nMin]);
				}
				if(m_pData[pIndex[nMin]]<m_pData[pIndex[nMax]]||pRefIndex[nMin]>pRefIndex[nMax]&&m_pData[pIndex[nMin]]==m_pData[pIndex[nMax]]) 
				{
					XYSWAP(pIndex[nMax],pIndex[nMin]);
					XYSWAP(pRefIndex[nMax],pRefIndex[nMin]);
				}
				if(m_pData[pIndex[nMin+1]]<m_pData[pIndex[nMin]]||pRefIndex[nMin+1]>pRefIndex[nMin]&&m_pData[pIndex[nMin+1]]==m_pData[pIndex[nMin]]) 
				{
					XYSWAP(pIndex[nMin+1],pIndex[nMin]);
					XYSWAP(pRefIndex[nMin+1],pRefIndex[nMin]);
				}
			}
			i = nMin+1;
			j = nMax;	
			while(1)
			{
				if(nSort>0)
				{
					while
					(
						m_pData[pIndex[i]]<m_pData[pIndex[nMin]]||
						pRefIndex[i]<pRefIndex[nMin]&&m_pData[pIndex[i]]==m_pData[pIndex[nMin]]
					) i++;
					while
					(
						m_pData[pIndex[nMin]]<m_pData[pIndex[j]]||
						pRefIndex[nMin]<pRefIndex[j]&&m_pData[pIndex[nMin]]==m_pData[pIndex[j]]
					) j--;
				}
				else
				{
					while
					(
						m_pData[pIndex[nMin]]<m_pData[pIndex[i]]||
						pRefIndex[i]<pRefIndex[nMin]&&m_pData[pIndex[i]]==m_pData[pIndex[nMin]]
					) i++;
					while
					(
						m_pData[pIndex[j]]<m_pData[pIndex[nMin]]||
						pRefIndex[nMin]<pRefIndex[j]&&m_pData[pIndex[nMin]]==m_pData[pIndex[j]]
					) j--;
				}
				if(i>j)
				{
					XYSWAP(pIndex[j],pIndex[nMin]);
					XYSWAP(pRefIndex[j],pRefIndex[nMin]);
					break;
				}
				XYSWAP(pIndex[i],pIndex[j]);
				XYSWAP(pRefIndex[i],pRefIndex[j]);
			}
			if(nMin<j-1)
			{
				theStack.Add(nMin);
				theStack.Add(j-1);
			}
			if(j+1<nMax)
			{
				theStack.Add(j+1);
				theStack.Add(nMax);
			}
		}
	}
	delete []pRefIndex;
}

#endif


