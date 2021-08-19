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
#include <iostream>  // Header for stream I/O.
#include <fstream> // Header for file I/O.
#include <iomanip> // Header for I/O manipulators.

#include "baseencryption.h"
#include "sdbdetailrec.h"

using namespace std;

std::ofstream & operator << (std::ofstream &rStream, const CSBDDetailRec &rRec)
{
   bool fLocalInUse = rRec.InUse();

   rStream.write((char *) &fLocalInUse, sizeof(fLocalInUse));
   rStream.write((char *) &rRec.nOriginalPathLen, sizeof(rRec.nOriginalPathLen));
   rStream.write((char *) &rRec.nAssocCommandLen, sizeof(rRec.nAssocCommandLen));
   rStream.write((char *) rRec.szOriginalPath, rRec.nOriginalPathLen);
   rStream.write((char *) rRec.szAssocCommand, rRec.nAssocCommandLen);
   rStream.write((char *) &rRec.lStartingPos, sizeof(rRec.lStartingPos));
   rStream.write((char *) &rRec.lSize, sizeof(rRec.lSize));

   return rStream;
}

std::ifstream & operator << (std::ifstream &rStream, CSBDDetailRec &rRec)
{
   bool fLocalInUse = false;
   rStream.read((char *) &fLocalInUse, sizeof(fLocalInUse));
   rRec.InUse(fLocalInUse);

   rStream.read((char *) &rRec.nOriginalPathLen, sizeof(rRec.nOriginalPathLen));
   rStream.read((char *) &rRec.nAssocCommandLen, sizeof(rRec.nAssocCommandLen));
   memset(rRec.szOriginalPath, 0, sizeof(rRec.szOriginalPath));
   rStream.read((char *) rRec.szOriginalPath, rRec.nOriginalPathLen);
   memset(rRec.szAssocCommand, 0, sizeof(rRec.szAssocCommand));
   rStream.read((char *) rRec.szAssocCommand, rRec.nAssocCommandLen);
   rStream.read((char *) &rRec.lStartingPos, sizeof(rRec.lStartingPos));
   rStream.read((char *) &rRec.lSize, sizeof(rRec.lSize));

   return rStream;
}

CSBDDetailRec::CSBDDetailRec() :
   nOriginalPathLen(0),
   nAssocCommandLen(0),
   lStartingPos(0L),
   lSize(0L)
{
   memset(szOriginalPath, 0, sizeof(szOriginalPath));
   memset(szAssocCommand, 0, sizeof(szAssocCommand));

}

CSBDDetailRec::CSBDDetailRec(const CSBDDetailRec &rRec)
{
   memset(szOriginalPath, 0, sizeof(szOriginalPath));
   memset(szAssocCommand, 0, sizeof(szAssocCommand));

   nOriginalPathLen = rRec.nOriginalPathLen;
   nAssocCommandLen = rRec.nAssocCommandLen;
   strncpy(szOriginalPath, rRec.szOriginalPath, sizeof(szOriginalPath));
   strncpy(szAssocCommand, rRec.szAssocCommand, sizeof(szAssocCommand));
   lStartingPos = rRec.lStartingPos;
   lSize = rRec.lSize;
}

void CSBDDetailRec::Initialize()
{
   nOriginalPathLen = 0;
   nAssocCommandLen = 0;
   lStartingPos = 0L;
   lSize = 0L;
   memset(szOriginalPath, 0, sizeof(szOriginalPath));
   memset(szAssocCommand, 0, sizeof(szAssocCommand));
}
   
void CSBDDetailRec::OriginalPath(const char *pszPath)
{
   if (NULL == pszPath)
   {
      throw new CXVaultException("NULL == pszPath");
   }

   strncpy(szOriginalPath, pszPath, sizeof(szOriginalPath) - 1);
   nOriginalPathLen = (int) strlen(szOriginalPath);
}
 
void CSBDDetailRec::AssocCommand(const char *pszPath)
{
   if (NULL == pszPath)
   {
      throw new CXVaultException("NULL == pszPath");
   }

   strncpy(szAssocCommand, pszPath, sizeof(szAssocCommand) - 1);
   nAssocCommandLen = (int) strlen(szAssocCommand);
}

void CSBDDetailRec::StartingPos(long lPos)
{
   lStartingPos = lPos;
}

CSBDDetailRec &CSBDDetailRec::operator=(const CSBDDetailRec &)
{
   return *this;
}

bool CSBDDetailRec::operator<(const CSBDDetailRec &) const
{
   bool fRet = false;

   return fRet;
}

bool CSBDDetailRec::operator==(const CSBDDetailRec &) const
{
   bool fRet = false;

   return fRet;
}




