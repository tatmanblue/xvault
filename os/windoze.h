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
#ifndef _OS_SPECIFIC_DEFINES
#define _OS_SPECIFIC_DEFINES

//
// This file defines stuff that is OS specific.  For each OS there will
// be another one of these files (such as linux.h).  The project will
// include the appropriate file.

#ifndef TRUE
#define TRUE true
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef FALSE
#define FALSE false
#endif

#ifndef MAX_FILE_LEN
#define MAX_FILE_LEN	255
#endif

#endif