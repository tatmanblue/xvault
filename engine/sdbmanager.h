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
#ifndef _SDB_MANAGER
#define _SDB_MANAGER


/*
   CSDBManager handles the knowledge for opening a given safety deposit box (which
   may have part of 1, 1 or more files.  CSDBManager uses collection of CSBDDetailRecs
   to know what it contains, once the appropriate keys have been given.


*/

class CSBDDetailRec;

class CSDBManager
{
private:

   bool                  fIsInitialized;

   char                  chSDBId;

   CDataArray<CSBDDetailRec>         
                        *pSDBRecords;


public:
   CSDBManager(void);
   CSDBManager(const char);
   ~CSDBManager(void);

   void Add(const char *);
   void AddFake(void);

   const char SDBId(void) const { return chSDBId;};
   void SDBId(const char chId) { chSDBId = chId;};


};


#endif;