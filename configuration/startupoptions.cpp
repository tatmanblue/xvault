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
#include "startupoptions.h"



void CStartupOptionsCmdLineParser::Parse(CStartupOptions &rOptions, int nArgCount, char *pszArgs[])
{
   if (2 >= nArgCount)
      throw new CCmdLineException();

   strncpy(rOptions.szStartupPath, pszArgs[0], sizeof(rOptions.szStartupPath) - 1);

   // the first argument must be a file name
   if (('-' == pszArgs[1][0]) ||
       ('/' == pszArgs[1][0]))
   {
      throw new CCmdLineException();
   }

   strncpy(rOptions.szFileName, pszArgs[1], sizeof(rOptions.szFileName) - 1);

   for (int count = 2; count < nArgCount; count ++)
   {
      if (('-' != pszArgs[count][0]) &&
         ('/'  != pszArgs[count][0]))
      {
         throw new CCmdLineException();
      }

      switch (pszArgs[count][1])
      {
         case 'a':
            rOptions.eOperation = CStartupOptions::add;
            break;
         case 'c':
            throw new CXVaultException();
            break;
         case 'd':
            rOptions.eOperation = CStartupOptions::del;
            break;
         case 'r':
            rOptions.eOperation = CStartupOptions::execute;
            break;
         case 'u':
            rOptions.eOperation = CStartupOptions::addupdate;
            break;
         case 'x':
            rOptions.eOperation = CStartupOptions::open;
            break;
         default:
            throw new CCmdLineException();
      }
   }

}

CStartupOptions::CStartupOptions()
{
	eOperation = CStartupOptions::open;
	memset(szFileName, 0, sizeof(szFileName));
}
       
CStartupOptions::~CStartupOptions()
{

}


CStartupOptions::EStartupOptions CStartupOptions::OPERATION() const
{
	return eOperation;
}

const char *CStartupOptions::FILENAME() const
{
	return (const char *) szFileName;
}

const char *CStartupOptions::STARTPATH() const
{
   return (const char *) szStartupPath;
}


