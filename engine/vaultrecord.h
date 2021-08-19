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
#ifndef _VAULT_RECORD_RECORD
#define _VAULT_RECORD_RECORD

// class CVaultManager;

/*
   Part of the Vault master record list
   used to find individal file locations (saftey deposit boxes)

*/
class CVaultManager;
class CVaultEntryRecord : public CBaseRecord
{

private:
   long  lUniqueId;

      
   char  szName[MAX_FILE_LEN + 1];

   int   nSDBAsciiId;                  // ASCII value of the subdir (if the subdir is 'a' then the value is 97
   int   nSDBNumber;                   // there may be more than 1 SBD in a subdir, index to which one
   int   nNumberOf;
   int   nTotal;


public:

   CVaultEntryRecord(void) {};
   CVaultEntryRecord(const CVaultEntryRecord &);
   virtual ~CVaultEntryRecord(void) {};

   virtual void Initialize(void);

	virtual CVaultEntryRecord& operator=(const CVaultEntryRecord &);

	virtual bool operator<(const CVaultEntryRecord &) const;

	virtual bool operator==(const CVaultEntryRecord &) const;

   void Name(const char *);
   const char *Name(void) const { return szName;};

   void SDBAsciiId(int nId) { nSDBAsciiId = nId;};
   int SDBAsciiId(void) const { return SDBAsciiId;};
   void SDBNumber(int nNum) { nSDBNumber = nNum;};
   int SDBNumber(void) const { return nSDBNumber;};
   void NumberOf(int nNum) { nNumberOf = nNum;};
   int NumberOf(void) const { return nNumberOf;};
   void Total(int nTot) { nTotal = nTotal;};
   int Total(void) const { return nTotal;};

   friend CVaultManager;
   friend std::ofstream & operator << (std::ofstream &, const CVaultEntryRecord &);          
   friend std::ifstream & operator >> (std::ifstream &, CVaultEntryRecord &);
          
};

extern std::ofstream & operator << (std::ofstream &, const CVaultEntryRecord &);
extern std::ifstream & operator >> (std::ifstream &, CVaultEntryRecord &);

#endif


