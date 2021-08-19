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

#include "dataarray.h"
#include "vaultmanager.h"
#include "vaultheader.h"
#include "vaultrecord.h"
#include "sdbmanager.h"
#include "random.h"

using namespace std;


CVaultManager::CVaultManager(const CBaseEnvConfig *pCfg)
{
   pConfig = pCfg;
   if (NULL == pConfig)
      throw new CXVaultException("NULL == pConfig");

   pHeader = NULL;
   pVaultRecords = NULL;

   fInitialized = false;
}

CVaultManager::~CVaultManager()
{
   // not all compilers support the most recent ansi standards for
   // delete...assume worst case
   if (NULL != pHeader)
      delete pHeader;
  
   if (NULL != pVaultRecords)
      delete pVaultRecords;
   

   delete [] *pSDBs;

   pHeader = NULL;
   pConfig = NULL;         // this is not ours, dont delete it
}

void CVaultManager::Initialize()
{
   if (false == fInitialized)
   {
      for (int count=0; count < 36; count ++)
      {
         pSDBs[count] = NULL;
      }

      ValidateFileStructure();
      fInitialized = true;         
   }
}

void CVaultManager::LoadFromFile()
{
   if (NULL == pConfig)
   {
      throw new CXVaultException("NULL == pConfig");
   }

   //
   if (NULL != pHeader)
      delete pHeader;


   pHeader = new CVaultHeaderRec();
   if (NULL == pHeader)
   {
      throw new CXVaultException("NULL == pHeader");
   }

   pHeader->Initialize();

   if (NULL != pVaultRecords)
   {
      delete pVaultRecords;
      pVaultRecords = NULL;
   }

   pVaultRecords = new CDataArray<CVaultEntryRecord>;
   if (NULL == pVaultRecords)
   {
      throw new CXVaultException("NULL == pVaultRecords");
   }

   long lVLRSize = sizeof(CVaultEntryRecord) - 4;   // less vtable

   char  szWorking[MAX_FILE_LEN + 1];

   memset(szWorking, 0, sizeof(szWorking));
   strncpy(szWorking, pConfig->WORKINGDIR(), sizeof(szWorking));
   strncat(szWorking, "vault.config", sizeof(szWorking) - strlen("vault.config"));

   // go to the end of the file, read in the last 4 bytes
   // this tells us where the header is saved
   ifstream oFile(szWorking);  

   // read in CVaultEntryRecords until we get to the header
   long lStartPos = 0L;
   oFile.unsetf(ios::skipws);
   oFile.seekg(sizeof(lStartPos) * -1, ios::end);

   // read in the header position
   oFile.read((char *) &lStartPos, sizeof(lStartPos));

   long lBytesRead = 0L;

   // go to the begining of the file
   oFile.seekg(0, ios::beg);

   while (0 == oFile.eof())
   {
      if (lBytesRead == lStartPos)
      {
         pHeader = new CVaultHeaderRec();
         if (NULL == pHeader)
         {
            throw new CXVaultException("NULL == pHeader");
         }

         oFile >> *pHeader;
         
         lBytesRead += pHeader->lLength;
      }

      CVaultEntryRecord *pVaultRec= new CVaultEntryRecord();
      if (NULL == pVaultRec)
      {
         throw new CXVaultException("NULL == pVaultRec");
      }

      pVaultRec->Initialize();

      oFile >> *pVaultRec;
      pVaultRecords->Add(*pVaultRec);
      
      lBytesRead += lVLRSize;

   }

   // close the file 
   oFile.close();

   // some tests to make sure we actually read in the file
   if (NULL == pHeader)
   {
      throw new CXVaultException("NULL == pHeader");
   }

   
}

void CVaultManager::CreateVaultDatabase()
{
   if (NULL == pConfig)
   {
      throw new CXVaultException("NULL == pConfig");
   }

   CBaseFileMgmt  *pFileMgr = GetFileManangement();
   if (NULL == pFileMgr)
   {
      throw new CXVaultException("NULL == pFileMgr");
   }

   pHeader = new CVaultHeaderRec();
   if (NULL == pHeader)
   {
      throw new CXVaultException("NULL == pHeader");
   }

   pHeader->Initialize();

   if (NULL != pVaultRecords)
   {
      delete pVaultRecords;
      pVaultRecords = NULL;
   }

   pVaultRecords = new CDataArray<CVaultEntryRecord>;
   if (NULL == pVaultRecords)
   {
      throw new CXVaultException("NULL == pVaultRecords");
   }

   long lVLRSize = sizeof(CVaultEntryRecord) - 4;   // less vtable

   //
   // 1) Randomly determine how many CVaultEntryRecord records we will create in
   //    the file
   pHeader->lRecords = CRandomGenerator::GetIntRange(117, 562);
   pHeader->lReAllocAt = pHeader->lRecords - CRandomGenerator::GetIntRange(8, 14);
   pHeader->lReAllocAmt = CRandomGenerator::GetIntRange(18, 41);
   
   // 1a) Randomly create some bogus crap
   pHeader->nReserve1Size = CRandomGenerator::GetIntRange(18, 41);
   pHeader->pszReserve1 = new char[pHeader->nReserve1Size];
   CRandomGenerator::GetRandomData(pHeader->nReserve1Size, pHeader->pszReserve1);
   pHeader->nReserve2Size = CRandomGenerator::GetIntRange(21, 104);
   pHeader->pszReserve2 = new char[pHeader->nReserve2Size];
   CRandomGenerator::GetRandomData(pHeader->nReserve2Size, pHeader->pszReserve2);

   // 1c) Randomly determine where in the file the header information gets saved
   long lHeaderRecPos = CRandomGenerator::GetIntRange(4, (pHeader->lRecords - 3));
   pHeader->lStartPos = (lHeaderRecPos * lVLRSize);

   // 1d) determine the total length of the header
   pHeader->lLength = sizeof(CVaultHeaderRec) + pHeader->nReserve1Size + pHeader->nReserve2Size;

   // 1e) determine the total length of the initalize vault manager
   //     records plus header plus header position value
   pHeader->lVaultManagerSize = pHeader->lLength + (pHeader->lRecords * lVLRSize) + sizeof(pHeader->lStartPos);

   try
   {
      char  szWorking[MAX_FILE_LEN + 1];

      memset(szWorking, 0, sizeof(szWorking));
      strncpy(szWorking, pConfig->WORKINGDIR(), sizeof(szWorking));
      strncat(szWorking, "vault.config", sizeof(szWorking) - strlen("vault.config"));

      // 4) Create the file and fill it with "empty (initialized it their own way)" 
      //    CVaultEntryRecords.  When at the position to write the header, write the 
      //    header and then continue with the rest of the records

      ofstream oFile(szWorking, ios::out );  
      
      long lBytesWritten = 0L;
      for (long lcount = 0L; lcount < pHeader->lRecords; lcount ++)
      {

         // 4a) start writing CVaultEntryRecords
         if (lBytesWritten == pHeader->lStartPos)
         {
            // 4b) write the header         

            oFile << *pHeader;
            
            lBytesWritten += pHeader->lLength;
         }

         // 4c) finish writing CVaultEntryRecords 
         CVaultEntryRecord *pVaultRec = new CVaultEntryRecord();
         if (NULL == pVaultRec)
         {
            throw new CXVaultException("NULL == pVaultRec");
         }

         pVaultRec->Initialize();

         pVaultRecords->Add(*pVaultRec);

         oFile << *pVaultRec;
         
         lBytesWritten += lVLRSize;

      }
      
      // 5) write the position of the header information at the end of the file
      
      lBytesWritten += sizeof(pHeader->lStartPos);

	   int lLongSize = sizeof(lBytesWritten);
	   oFile.write((char *) &pHeader->lStartPos, lLongSize);
      oFile.flush();
      oFile.close();

      if (lBytesWritten != pHeader->lVaultManagerSize)
      {
         throw new CXVaultException("lBytesWritten != pHeader->lVaultManagerSize");
      }
   }
   catch(CXVaultException e)
   {
      throw e;
   }
}

void CVaultManager::ValidateFileStructure()
{
   CBaseFileMgmt  *pFileMgr = GetFileManangement();
   char  szWorkingDir[MAX_FILE_LEN + 1];

   if (NULL == pFileMgr)
   {
      throw new CXVaultException("NULL == pFileMgr");
   }

   // check to see if WorkingDir exists
   if (false == pFileMgr->DirExists(pConfig->WORKINGDIR()))
   {
      pFileMgr->CreateDir(pConfig->WORKINGDIR());

     // check to see if the "Dictionary" dirs exist under WorkingDir

      // 48 - 59
      // 97 - 122
      int   counter = 0;

      for (counter = 48; counter < 123; counter ++)
      {
         if (58 == counter)
         {
            counter = 97;
         }

         char  chDir = counter;

         memset(szWorkingDir, 0, sizeof(szWorkingDir));

         _snprintf(szWorkingDir, sizeof(szWorkingDir), "%s%c", pConfig->WORKINGDIR(), chDir);
      
         // check to see if the TempDir exists
         if (false == pFileMgr->DirExists(szWorkingDir))
         {
            pFileMgr->CreateDir(szWorkingDir);
         }
      }
   }

   // check to see if the TempDir exists
   if (false == pFileMgr->DirExists(pConfig->TEMPDIR()))
   {
      pFileMgr->CreateDir(pConfig->TEMPDIR());
   }

   memset(szWorkingDir, 0, sizeof(szWorkingDir));
   strncpy(szWorkingDir, pConfig->WORKINGDIR(), sizeof(szWorkingDir));
   strncat(szWorkingDir, "vault.config", sizeof(szWorkingDir) - strlen("vault.config"));

   // Check to see if the vault master file is present
   if (true == pFileMgr->FileExists(szWorkingDir))
   {
      LoadFromFile();
   }
   else
   {
      CreateVaultDatabase();
   }

}

void CVaultManager::Deinitialize()
{
   CBaseFileMgmt  *pFileMgr = GetFileManangement();
   if (NULL == pFileMgr)
   {
      throw new CXVaultException("NULL == pFileMgr");
   }

   pFileMgr->DeleteDirRecursive(pConfig->TEMPDIR());
}

// long CVaultManager::WhichVaultRec()
//       Randomly find a not in use Vault Record
//
long CVaultManager::WhichVaultRec()
{
   long lRet = -1;
   bool fHaveRec = false;

   if (NULL == pVaultRecords)
   {
      throw new CXVaultException("NULL == pVaultRecords");
   }

   if (NULL == pHeader)
   {
      throw new CXVaultException("NULL == pHeader");
   }

   while( false == fHaveRec)
   {

      lRet = CRandomGenerator::GetIntRange(0, pHeader->lRecords - 1);

      CVaultEntryRecord *pVaultRec = &(pVaultRecords->operator [](lRet));  // &(*pVaultRecords)[lRet];
            
      if (false == pVaultRec->InUse())
      {
         fHaveRec = true;
         break;
      }

   }

   if (false == fHaveRec)
   {
      throw new CXVaultException("false == fHaveRec");
   }

   return lRet;
}


// char CVaultManager::WhichSDB()
//      Randomly determine a valid SDB ID
//
char CVaultManager::WhichSDB()
{
   char chRet = 0;

   while (((48 > chRet) && (59 < chRet)) ||
          ((97 > chRet) && (122 < chRet)))
   {
      chRet = CRandomGenerator::GetIntRange(40, 140);
   }

   return chRet;
}

// void CVaultManager::Add(const char *pszFullFileName)
//      Adds a file into the vault
//
void CVaultManager::Add(const char *pszFullFileName, const char *pszAssocFileName)
{
   if (NULL == pszFullFileName)
   {
      throw new CXVaultException("NULL == pszFullFileName");
   }

   if (NULL == pHeader)
   {
      throw new CXVaultException("NULL == pHeader");
   }

   if (NULL == pVaultRecords)
   {
      throw new CXVaultException("NULL == pVaultRecords");
   }

   CVaultEntryRecord *pVaultRec = new CVaultEntryRecord();
   if (NULL == pVaultRec)
   {
      throw new CXVaultException("NULL == pVaultRec");
   }

   pVaultRec->Initialize();


   // validate that there are enough available records in the pVaultRecords
   // if not create more
   pHeader->lActualRecords;
   pHeader->lRecords; 
   pHeader->lReAllocAt;

   // randomly determine which record to update
   long lVaultRecId = WhichVaultRec();

   // add it...this time when it gets added a SDB file will get updated
   // determine which SDBmanager handles the file
   char chWhichSDB = WhichSDB();
   pVaultRec->SDBAsciiId(chWhichSDB);
   pVaultRec->Name(pszFullFileName);

   // randomly determine a few other SDBmanagers that can create "fake" records
   // the SDB manager
   int nFakeRecs = CRandomGenerator::GetIntRange(1, 4);
   char *pchFakeSDBs = new char[nFakeRecs];

   for (int counter = 0; counter < nFakeRecs; counter ++)
   {
      pchFakeSDBs[counter] = WhichSDB();
   }

   // the SDB is responsible for getting the file in and erasing it from the 
   // source

   
   delete [] pchFakeSDBs;
}