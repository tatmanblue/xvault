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
#ifndef _MS_FILE_MANAGEMENT
#define _MS_FILE_MANAGEMENT

class CMSFileMgmt : public CBaseFileMgmt
{
public:
   CMSFileMgmt(void) {};
   virtual ~CMSFileMgmt(void) {};

   virtual bool DirExists(const char *);
   virtual bool FileExists(const char *);
   virtual void CreateDir(const char *);

   virtual void DeleteDirRecursive(const char *);
   virtual void DeleteFile(const char *);

   virtual int OpenFileWrite(const char *);
   virtual void CloseFile(int);
   virtual int WriteFile(int, const char *, int);
};


#endif