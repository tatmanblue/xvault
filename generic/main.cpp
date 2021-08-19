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
#include "startupoptions.h"
#include "baseenvconfig.h"
#include "vaultmanager.h"
#include "random.h"

void printCmdLineHelp(void)
{
	printf("xVault copyright(c) matt raffel 2003\r\n");
	printf("Usage: xvault filename [-acdrux]\r\n");
	printf("\t\t -a add the file, errors it if already exists\r\n");
   printf("\t\t -c checks to see if the file exists\r\n");
	printf("\t\t -d deletes the file from the vault\r\n");
   printf("\t\t -r runs an associated command with the file extracted\r\n");
   printf("\t\t    to a temp location.  If the file does not exist in the\r\n");
   printf("\t\t    vault, it will be added after the command completes.\r\n");
	printf("\t\t -u updates the file, if it does not exist it adds it\r\n");
   printf("\t\t -x extracts the file\r\n");

}


// this main is shared for all command line versions of xvault
int xVaultMain(int argc, _TCHAR* argv[])
{
	bool	fCmdLineOk = true;
	CStartupOptions
			oOptions;

	// parse the cmdline	
	// 
   try
   {
      CStartupOptionsCmdLineParser::Parse(oOptions, argc, argv);
      fCmdLineOk = true;

      printf("processing '%s'\r\n", oOptions.FILENAME());
      
      CStartupOptions::EStartupOptions eExecute = oOptions.OPERATION();      
            
      CBaseEnvConfig *pEnvironment = GetEnvironmentConfiguration();

      CVaultManager  oVault(pEnvironment);

      oVault.Initialize();

      switch (eExecute)
      {
         case CStartupOptions::add:
            oVault.Add(oOptions.FILENAME());
            break;
         default:
            throw new CXVaultException();
            break;
      }


      oVault.Deinitialize();
      delete pEnvironment;

   }
   catch(CCmdLineException *e)
   {
      printf("invalid command line\r\n");
      fCmdLineOk = false;
      delete e;
   }
   catch (CXVaultException *e)
   {
      printf("exception caused xvault to terminate.  More information may be listed below\r\n");
      printf("%s\r\n", e->Message());
      delete e;
   }

	if (false == fCmdLineOk)
	{
		printCmdLineHelp();
	}


   return 0;
}