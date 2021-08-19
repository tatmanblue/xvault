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
#include "random.h"
#include <stdlib.h>
#include <time.h>


int CRandomGenerator::GetIntLen(int nVal)
{
   char szInt[25];

   memset(szInt, 0, sizeof(szInt));
   sprintf(szInt, "%d", nVal);

   return (int) strlen(szInt);
}

void CRandomGenerator::GetRandomData(int nBytes, char *pszData)
{
   for (int counter = 0; counter < nBytes; counter ++)
   {
      char chRandom = (char) CRandomGenerator::GetIntRange(1, 255, false);
      *pszData = chRandom;
      pszData ++;
   }
}

int CRandomGenerator::GetIntRange(int nLow, int nHigh, bool fReseed)
{
   int nRet = nLow - 1,
       nLowLen = CRandomGenerator::GetIntLen(nLow),
       nHiLen = CRandomGenerator::GetIntLen(nHigh);
   char szInt[25],
       *pPos = NULL;

   if (nLow > nHigh)
   {
      throw new CXVaultException("nLow > nHigh");
   }  

   if (true == fReseed)
   {
      srand((unsigned) time(NULL));
   }

   for (int counter = 0; counter < 399; counter ++)
   {
      memset(szInt, 0, sizeof(szInt));
      sprintf(szInt, "%d", rand());
      pPos = &szInt[strlen(szInt) - nHiLen];

      int nRand = atoi(pPos);
      if ((nRand >= nLow) && (nRand <= nHigh))
      {
         nRet = nRand;
         break;
      }
   }

   if (nRet == (nLow - 1))
   {
      throw new CXVaultException();
   }

   return nRet;
}