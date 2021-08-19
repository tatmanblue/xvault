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
#ifndef _SINGLE_FILE
#define _SINGLE_FILE


class CSingleFile
{
   char  szFileName[MAX_FILE_LEN + 1];
   char  szAssocProgram[MAX_FILE_LEN + 1];
   long  lFileSize,
         lFileNameLen,              // doent need to be a long but it aint going to hurt anything
         lAssocProgLen;             // doent need to be a long but it aint going to hurt anything


   public:
      CSingleFile(void);
      virtual ~CSingleFile(void) {};

      inline const char *FILENAME(void) const;
      inline const char *ASSOCPROG(void) const;
      inline long SIZE(void) const;

};

#endif