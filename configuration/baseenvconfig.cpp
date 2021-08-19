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
#include <stdio.h>
#include "baseenvconfig.h"


CBaseEnvConfig::CBaseEnvConfig()
{
   fInitialized = false;
   memset(szWorkingDir, 0, sizeof(szWorkingDir));
   memset(szTempDir, 0, sizeof(szTempDir));
}

// hmmm default here is dos specific....not good
void CBaseEnvConfig::SetDefaults()
{
   if (0 == strlen(szWorkingDir))
   {
      strncpy(szWorkingDir, "c:\\xvault\\", sizeof(szWorkingDir) - 1);
   }

   if (0 == strlen(szTempDir))
   {
      strncpy(szTempDir, "c:\\xvault\\temp\\", sizeof(szTempDir) - 1);
   }
}

/*void CBaseEnvConfig::SetInitialized()
{
  fInitialized = true;
}*/

const char *CBaseEnvConfig::WORKINGDIR() const
{
   return (const char *)szWorkingDir;
}

const char *CBaseEnvConfig::TEMPDIR() const
{
   return (const char *)szTempDir;
}

const bool CBaseEnvConfig::INITIALIZED() const
{
   return fInitialized;
}