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

#ifndef _VAULT_HEADER_RECORD
#define _VAULT_HEADER_RECORD

class CVaultManager;
class CVaultHeaderRec : public CBaseRecord
{
   // the "reserve" stuff is just crap, intended to confuse would be file watchers

   long  lLength;             // size of the header record
   int   nReserve1Size;
   long  lStartPos;           // where the header record begins at
   long  lActualRecords;      // number actually used
   long  lVaultManagerSize;   // size of vault.config total for everthing
   char *pszReserve1;
   int   nReserve2Size;
   long  lRecords;            // total available
   long  lReAllocAt;          // when this few are available alloc more
   char *pszReserve2;
   long  lReAllocAmt;         // how many to add to the total records


public:
   CVaultHeaderRec(void);
   virtual ~CVaultHeaderRec(void);
   CVaultHeaderRec(CVaultHeaderRec &);

   virtual void Initialize(void);

   friend CVaultManager;
   friend std::ofstream & operator << (std::ofstream &, const CVaultHeaderRec &);
   friend std::ifstream & operator >> (std::ifstream &, CVaultHeaderRec &);
   

};

extern std::ofstream & operator << (std::ofstream &, const CVaultHeaderRec &);
extern std::ifstream & operator >> (std::ifstream &, CVaultHeaderRec &);

#endif