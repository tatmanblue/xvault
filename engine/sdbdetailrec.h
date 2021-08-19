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
#ifndef _SDB_DETAIL_RECORD
#define _SDB_DETAIL_RECORD


/*
   CSBDDetailRec contains the information needed it identify and      
   access a file in a safety deposit box.

*/

class CSBDDetailRec : public CBaseRecord
{
private:
   int      nOriginalPathLen,
            nAssocCommandLen;

   char     szOriginalPath[MAX_FILE_LEN + 1];
   char     szAssocCommand[MAX_FILE_LEN + 1];

   long     lStartingPos,
            lSize;
           

public:
   CSBDDetailRec(void);
   CSBDDetailRec(const CSBDDetailRec &);
   virtual ~CSBDDetailRec(void) {};

   virtual void Initialize(void);


   long OriginalPathLen(void) const {return nOriginalPathLen;};
   long AssocCommandLen(void) const {return nAssocCommandLen;};

   const char *OriginalPath(void) const {return szOriginalPath;};
   void OriginalPath(const char *);
   const char *AssocCommand(void) const {return szAssocCommand;};
   void AssocCommand(const char *);

   long StartingPos(void) const {return lStartingPos;};
   void StartingPos(long);
   long Size(void) const {return lSize;};

   virtual CSBDDetailRec &operator=(const CSBDDetailRec &);
   virtual bool operator<(const CSBDDetailRec &) const;
   virtual bool operator==(const CSBDDetailRec &) const;

   friend std::ofstream & operator << (std::ofstream &, const CSBDDetailRec &);          
   friend std::ifstream & operator << (std::ifstream &, CSBDDetailRec &);       

};

class CCSBDFakeDetailRec : public CSBDDetailRec
{
public:
   CCSBDFakeDetailRec(void);
   virtual ~CCSBDFakeDetailRec(void) {};

   virtual void Initialize(void);
};

extern std::ofstream & operator << (std::ofstream &, const CSBDDetailRec &);          
extern std::ifstream & operator << (std::ifstream &, CSBDDetailRec &);          

#endif