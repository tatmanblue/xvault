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
#ifndef _BASE_RECORD
#define _BASE_RECORD


//
// This class is nothing more than a place holder so that the
// container class can contain derived instances of this class
// via a common base class
//

class CBaseRecord
{

private:

   bool    fInUse;

protected:
   // the constructor is protected so that no one can create an instance of it
   // they must create an instance of a derived class

   CBaseRecord(void) {fInUse = false;};


public:
   virtual ~CBaseRecord(void){};

   virtual void InUse(bool fUse) { fInUse = fUse;};
   virtual bool InUse(void) const { return fInUse;} ;

   virtual void Initialize(void) = 0 {};
   virtual CBaseRecord& operator=(const CBaseRecord&) {return *this;};

   virtual bool operator<(const CBaseRecord &) const {return false;};

   virtual bool operator==(const CBaseRecord &) const {return false;};

};


#endif