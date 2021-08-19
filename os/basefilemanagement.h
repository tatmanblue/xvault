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
#ifndef _BASE_FILE_MANANGEMENT
#define _BASE_FILE_MANANGEMENT


//because microsoft has a problem implementing ansi standard file and directory
//management functions, this class will act as a base class that
//implements the functions
class CBaseFileMgmt
{

protected:
   // the constructor is protected so that no one can create an instance of it
   // they must create an instance of a derived class

   CBaseFileMgmt(void) {};

public:
   
   virtual ~CBaseFileMgmt(void) {};

   virtual bool DirExists(const char *) = 0;
   virtual bool FileExists(const char *) = 0;
   virtual void CreateDir(const char *) = 0;

   virtual void DeleteDirRecursive(const char *) = 0;
   virtual void DeleteFile(const char *) = 0;

   virtual int OpenFileWrite(const char *) = 0;
   virtual void CloseFile(int) = 0;
   virtual int WriteFile(int, const char *, int) = 0;
};

#endif