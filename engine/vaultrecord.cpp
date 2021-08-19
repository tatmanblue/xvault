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

#include "vaultmanager.h"
#include "vaultrecord.h"
#include "random.h"

using namespace std;


std::ofstream & operator << (std::ofstream &rStream, const CVaultEntryRecord &rRec)
{   

   rStream.write((char *) &rRec.lUniqueId, sizeof(rRec.lUniqueId));      

   // write all the bits not just up to the null (the c string)
   rStream.write((char *) rRec.szName, sizeof(rRec.szName));

   rStream.write((char *) &rRec.nSDBAsciiId, sizeof(rRec.nSDBAsciiId));
   rStream.write((char *) &rRec.nSDBNumber, sizeof(rRec.nSDBNumber));
   rStream.write((char *) &rRec.nNumberOf, sizeof(rRec.nNumberOf));
   rStream.write((char *) &rRec.nTotal, sizeof(rRec.nTotal));
   bool fLocalInUse = rRec.InUse();

   rStream.write((char *) &fLocalInUse, sizeof(fLocalInUse));
   rStream.flush();

   return rStream;
}

std::ifstream & operator >> (std::ifstream &rStream, CVaultEntryRecord &rRec)
{
   
   rStream.read((char *) &rRec.lUniqueId, sizeof(rRec.lUniqueId));         
   rStream.read((char *) rRec.szName, sizeof(rRec.szName));
   rStream.read((char *) &rRec.nSDBAsciiId, sizeof(rRec.nSDBAsciiId));
   rStream.read((char *) &rRec.nSDBNumber, sizeof(rRec.nSDBNumber));
   rStream.read((char *) &rRec.nNumberOf, sizeof(rRec.nNumberOf));
   rStream.read((char *) &rRec.nTotal, sizeof(rRec.nTotal));

   bool fLocalInUse = false;

   rStream.read((char *) &fLocalInUse, sizeof(fLocalInUse));

   rRec.InUse(fLocalInUse);

   return rStream;
}

CVaultEntryRecord::CVaultEntryRecord(const CVaultEntryRecord &rRec)
{
   lUniqueId = rRec.lUniqueId;      

   memset(szName, 0, sizeof(szName));
   strncpy(szName, rRec.szName, sizeof(szName));

   nSDBAsciiId = rRec.nSDBAsciiId;
   nSDBNumber = rRec.nSDBNumber;
   nNumberOf = rRec.nNumberOf;
   nTotal = rRec.nTotal;
}

void CVaultEntryRecord::Initialize()
{
   lUniqueId = CRandomGenerator::GetIntRange(823, 9312, true);

   memset(szName, 0, sizeof(szName));
   // 
   // CRandomGenerator::GetRandomData(sizeof(szName), szName);

   nSDBAsciiId = CRandomGenerator::GetIntRange(823, 9312);
   nSDBNumber = CRandomGenerator::GetIntRange(823, 9312);
   nNumberOf = CRandomGenerator::GetIntRange(823, 9312);
   nTotal = CRandomGenerator::GetIntRange(823, 9312);

}

CVaultEntryRecord &CVaultEntryRecord::operator=(const CVaultEntryRecord &rRec)
{
   if (this != &rRec)
   {

      lUniqueId = rRec.lUniqueId;

      memset(szName, 0, sizeof(szName));
      strncpy(szName, rRec.szName, sizeof(szName));

      nSDBAsciiId = rRec.nSDBAsciiId;
      nSDBNumber = rRec.nSDBNumber;
      nNumberOf = rRec.nNumberOf;
      nTotal = rRec.nTotal;
   }

   return *this;
}

bool CVaultEntryRecord::operator<(const CVaultEntryRecord &rRec) const
{

	return (lUniqueId < rRec.lUniqueId);
}

bool CVaultEntryRecord::operator==(const CVaultEntryRecord &rRec) const
{
	return (lUniqueId == rRec.lUniqueId);
}

void CVaultEntryRecord::Name(const char *pszFileName)
{
   if (NULL != pszFileName)
   {
      strncpy(szName, pszFileName, sizeof(szName));
   }
}
