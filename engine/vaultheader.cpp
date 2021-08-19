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
#include "stdafx.h"
#include "vaultheader.h"

#include <iostream>  // Header for stream I/O.
#include <fstream> // Header for file I/O.
#include <iomanip> // Header for I/O manipulators.

#include "vaultmanager.h"

using namespace std;


std::ofstream & operator << (std::ofstream &rStream, const CVaultHeaderRec &rHeader)
{
   long lLongSize = sizeof(long);

   rStream.write((char *) &rHeader.lLength, sizeof(lLongSize)); 
   rStream.write((char *) &rHeader.nReserve1Size, sizeof(rHeader.nReserve1Size)); 
   rStream.write((char *) &rHeader.lStartPos, sizeof(lLongSize)); 
   rStream.write((char *) &rHeader.lActualRecords, sizeof(lLongSize)); 
   rStream.write((char *) &rHeader.lVaultManagerSize, sizeof(lLongSize)); 
   rStream.write(rHeader.pszReserve1, rHeader.nReserve1Size);
   rStream.write((char *) &rHeader.nReserve2Size, sizeof(rHeader.nReserve2Size)); 
   rStream.write((char *) &rHeader.lRecords, sizeof(lLongSize)); 
   rStream.write((char *) &rHeader.lReAllocAt, sizeof(lLongSize)); 
   rStream.write(rHeader.pszReserve2, rHeader.nReserve2Size);
   rStream.write((char *) &rHeader.lReAllocAmt, sizeof(lLongSize)); 
   rStream.flush();

   return rStream;
}

std::ifstream & operator >> (std::ifstream &rStream, CVaultHeaderRec &rHeader)
{

   long lLongSize = sizeof(long);

   rStream.read((char *) &rHeader.lLength, sizeof(lLongSize)); 
   rStream.read((char *) &rHeader.nReserve1Size, sizeof(rHeader.nReserve1Size)); 
   rStream.read((char *) &rHeader.lStartPos, sizeof(lLongSize)); 
   rStream.read((char *) &rHeader.lActualRecords, sizeof(lLongSize)); 
   rStream.read((char *) &rHeader.lVaultManagerSize, sizeof(lLongSize)); 
   rHeader.pszReserve1 = new char[rHeader.nReserve1Size];
   if (NULL == rHeader.pszReserve1)
   {
      throw new CXVaultException("NULL == rHeader.pszReserve1");
   }
   memset(rHeader.pszReserve1, 0, rHeader.nReserve1Size);
   rStream.read(rHeader.pszReserve1, rHeader.nReserve1Size);
   rStream.read((char *) &rHeader.nReserve2Size, sizeof(rHeader.nReserve2Size)); 
   rStream.read((char *) &rHeader.lRecords, sizeof(lLongSize)); 
   rStream.read((char *) &rHeader.lReAllocAt, sizeof(lLongSize)); 
   rHeader.pszReserve2 = new char[rHeader.nReserve2Size];
   if (NULL == rHeader.pszReserve2)
   {
      throw new CXVaultException("NULL == rHeader.pszReserve2");
   }

   memset(rHeader.pszReserve2, 0, rHeader.nReserve2Size);
   rStream.read(rHeader.pszReserve2, rHeader.nReserve2Size);
   rStream.read((char *) &rHeader.lReAllocAmt, sizeof(lLongSize)); 

   return rStream;
}

CVaultHeaderRec::CVaultHeaderRec(CVaultHeaderRec &rHeader)
{
   lActualRecords = rHeader.lActualRecords;
   lRecords = rHeader.lRecords;
   lReAllocAt = rHeader.lReAllocAt;
   lReAllocAmt = rHeader.lReAllocAmt;
   lStartPos = rHeader.lStartPos;
   lLength = rHeader.lLength;

   nReserve1Size = rHeader.nReserve1Size;
   pszReserve1 = new char[nReserve1Size];
   strncpy(pszReserve1, rHeader.pszReserve1, nReserve1Size);
   nReserve2Size = rHeader.nReserve2Size;
   pszReserve2 = new char[nReserve2Size];
   strncpy(pszReserve2, rHeader.pszReserve2, nReserve2Size);

}

CVaultHeaderRec::CVaultHeaderRec()
{

   
}

CVaultHeaderRec::~CVaultHeaderRec()
{
   if ((NULL != pszReserve1) && (0 != nReserve1Size))
      delete [] pszReserve1;

   if ((NULL != pszReserve2) && (0 != nReserve2Size))
      delete [] pszReserve2;



}

void CVaultHeaderRec::Initialize()
{

   lActualRecords = 0L;
   lRecords = 0L;
   lReAllocAt = 0L;
   lReAllocAmt = 0L;
   lStartPos = 0L;
   lLength = 0L;

   nReserve1Size = 0;
   pszReserve1 = NULL;
   nReserve2Size = 0;
   pszReserve2 = NULL;


}


