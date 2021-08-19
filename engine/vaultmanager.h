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
#ifndef _VAULT_MANAGER
#define _VAULT_MANAGER


/*

   CVaultManager (VM) is responsible for handling all access to and from
   the vault.

   The vault is the collection of files in a secure manner.  The vault
   uses "safety deposit boxes" (SDB) for safe keeping of the files.  The 
   VM and SDB each have a key which is required to open the contents.

   The VM key is generated.  The SDB key is user input.

   For Record keeping the VM keeps enough information on each SDB 
   that it can trigger through a series of challenges the SDB to 
   reveal additional information on how to access it.

   An SDB may contain none, one or more files. The maximum size of a single
   SDB is 2GB.  Files may span multiple SDBs.  


                                          The entire CSafetyBoxRecord has to be
                                          decrypted with the Vault Key before any of
                                          this data will make sense.

   CVaultListRecord                       CSafetyBoxRecord
   lUniqueId                 equals         lUniqueId after unencrypted with Vault Key
   nSDBNumber                equals         nSDBNumber   "   "     "   "   "   "
                                            szSDBKey     "   "     "   "   "   "
   szName                    equals         szName    after unencrypted with SDB Key
                                            szFullPath   "   "     "   "   "   "
                                            eType        "   "     "   "   "   "
                                            lSize        "   "     "   "   "   "
                                            lStartPos    "   "     "   "   "   "
   nNumberOf                 equals         nNumberOf    "   "     "   "   "   "
   nTotal                    equals         nTotal       "   "     "   "   "   "

*/

class CVaultHeaderRec;
class CVaultEntryRecord;
class CSDBManager;

class CVaultManager
{
   bool  fInitialized;

   CVaultHeaderRec      *pHeader;
   CSDBManager          *pSDBs[36];
   
   CDataArray<CVaultEntryRecord>         
                        *pVaultRecords;
   
   const CBaseEnvConfig *pConfig;

   void ValidateFileStructure(void);

   void LoadFromFile(void);
   void CreateVaultDatabase(void);
   char WhichSDB(void);
   long WhichVaultRec(void);

   public:
      CVaultManager(const CBaseEnvConfig *);
      ~CVaultManager(void);

      void Initialize(void);
      void Deinitialize(void);

      void Add(const char *, const char * = NULL);


};

#endif