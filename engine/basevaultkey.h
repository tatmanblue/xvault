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
    along with Foobar; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    architected and written by 
    matt raffel of microobjects inc 2003
    mattr@microobjects.com


 ******************************************************************************
*/
#ifndef _BASE_VAULT_KEY
#define _BASE_VAULT_KEY



class CBaseVaultKey
{
   // todo...later on we should fragment this memory all over the place so
   // that someone could not just scan the memory and get this
   char  szEncryptedKey[50];

protected:
   virtual char *Encode(const char *);
   virtual const char *Get(void) const;

public:
   CBaseVaultKey(const char *pszUnencrypted = NULL);
   virtual ~CBaseVaultKey(void);

   virtual void AssignKey(const char *);

   virtual const char *Decode(void) const;

};




#endif