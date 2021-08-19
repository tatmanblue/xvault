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
#ifndef _STARTUP_OPTIONS
#define _STARTUP_OPTIONS

class CStartupOptionsCmdLineParser;


class CStartupOptions
{
   public:

      typedef enum tagEStartupOptions
      {
         na,
		   open,    						   // uncompresses a file
         check,                        // checks for the existance of the file
		   add,   							   // adds a file to system
		   addupdate,  						// adds or updates
		   del,								   // removes
         execute                       // addipdate and then run associated program with it

      } EStartupOptions;

   private:
      char   szFileName[MAX_FILE_LEN + 1];
      char   szStartupPath[MAX_FILE_LEN + 1];


      EStartupOptions eOperation;

   public:
      CStartupOptions(void);
      virtual ~CStartupOptions(void);

      EStartupOptions OPERATION(void) const;
	   const char *FILENAME(void) const;
      const char *STARTPATH(void) const;

      friend CStartupOptionsCmdLineParser;

};

class CStartupOptionsCmdLineParser 
{
   public:
      static void Parse(CStartupOptions &, int, char *[]);
};


#endif