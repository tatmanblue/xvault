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
#include "msfilemanagement.h"
#include "random.h"
#include <direct.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


bool CMSFileMgmt::DirExists(const char *pszTestDir)
{
   bool fExists = false;
   char szCurDir[MAX_FILE_LEN + 1];

   _getcwd(szCurDir, sizeof(szCurDir) - 1);
   if (0 == _chdir(pszTestDir))
   {
      fExists = true;
   }

   if (-1 == _chdir(szCurDir))
   {
      throw new CXVaultException();
   }

   return fExists;
}

int CMSFileMgmt::OpenFileWrite(const char *pszFile)
{
   int hFile = _open(pszFile, _O_RDWR | _O_CREAT, _S_IREAD | _S_IWRITE);

   if (-1 == hFile)
   {
      throw new CXVaultException();
   }

   return hFile;
}

int CMSFileMgmt::WriteFile(int hFile, const char *pszData, int nBytes)
{
   return _write(hFile, pszData, nBytes);
}

void CMSFileMgmt::CloseFile(int hFile)
{
   _close(hFile);
}

bool CMSFileMgmt::FileExists(const char *pszTestFile)
{
   bool fFileExists = false;
   int  hFile = 0;

   hFile = _open(pszTestFile, _O_RDONLY);
   if (-1 == hFile) //_O_CREAT | _O_EXCL))
   {
      if (EEXIST == errno)
         fFileExists = true;
   }
   else
   {
      // // temp until create is finish
      fFileExists = true;
      _close(hFile);
   }

   return fFileExists;
}

void CMSFileMgmt::CreateDir(const char *pszTestDir)
{
   char szCurDir[MAX_FILE_LEN + 1];

   _getcwd(szCurDir, sizeof(szCurDir) - 1);
   if (-1 == _chdir(pszTestDir))
   {
      //assume chdir failed because it did not exist
      if (-1 == _mkdir(pszTestDir))
      {
         if (EEXIST != errno)
         {
            throw new CXVaultException();
         }
      }
   }

   if (-1 == _chdir(szCurDir))
   {
      throw new CXVaultException();
   }

}

void CMSFileMgmt::DeleteDirRecursive(const char *pszDir)
{
   struct _finddata_t stFileInfo;
   char   szPath[MAX_FILE_LEN + 1];

   memset(szPath, 0, sizeof(szPath));
   // not a buffer overrun proof copy
   sprintf(szPath, "%s*.*", pszDir);

   long lFind = _findfirst(szPath, &stFileInfo);

   if (-1 != lFind)
   {
      int nFindNext = 0;

      while (0 == nFindNext)
      {
         if (((stFileInfo.attrib & _A_SUBDIR) && ('.' != stFileInfo.name[0])) ||
             (!(stFileInfo.attrib & _A_SUBDIR)))
         {           
            char   szNewPath[MAX_FILE_LEN + 1];

            memset(szNewPath, 0, sizeof(szNewPath));
            // not a buffer overrun proof copy
            sprintf(szNewPath, "%s%s", pszDir, stFileInfo.name);

            if ((stFileInfo.attrib & _A_RDONLY))
            {
               _chmod(szNewPath, _S_IREAD | _S_IWRITE);
            }

            if ((stFileInfo.attrib & _A_SUBDIR))
            {
               strncat(szNewPath, "\\", 1);
               DeleteDirRecursive(szNewPath);
               _rmdir(szNewPath);
            }
            else
            {
               DeleteFile(szNewPath);
            }
         }

         nFindNext = _findnext(lFind, &stFileInfo);
      }

      _findclose(lFind);
   }
}

void CMSFileMgmt::DeleteFile(const char *pszFile)
{
   // todo...
   int  nRewriteTotal = CRandomGenerator::GetIntRange(1, 6),          
        nRewriteCount = 0,
        hFile = 0;
   long lFileLength = 0L,
        lPosCounter = 0L;
   char chRandom = 0;

   while (nRewriteCount < nRewriteTotal)
   {
      if (-1 != (hFile = _open(pszFile, _O_RDWR | _O_CREAT, _S_IREAD | _S_IWRITE)))
      {
         lFileLength = _filelength(hFile);
         lPosCounter = 0L;

         while (lPosCounter < (lFileLength + CRandomGenerator::GetIntRange(50, 512)))
         {
            char szStr[4];

            memset(szStr, 0, sizeof(szStr));
            sprintf(szStr, "%c", (char) CRandomGenerator::GetIntRange(1, 255, false));
            
            _write(hFile, szStr, 1);
            _commit(hFile);
            _sleep(0);
            lPosCounter ++;
         }
         
         _close(hFile);
      }

      nRewriteCount ++;
   }

   if (-1 ==_unlink(pszFile))
   {
      printf("error deleting %s", pszFile);
   }
}

