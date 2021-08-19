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
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
// This file is implemented for each build (win cmd, linux cmd, win GUI, KDE, etc....)
// it should include the files that are os specific
//

#pragma once


#include <iostream>
#include <tchar.h>

// os specific implementations
#include "windoze.h"

// common shared stuff
#include "exceptions.h"
#include "baseenvconfig.h"
#include "basefilemanagement.h"
#include "baserecord.h"
#include "dataarray.h"

// these functions will be unique for each OS and implemented in stdafx.cpp
// it should return a point to 
extern CBaseEnvConfig *GetEnvironmentConfiguration(void);
extern CBaseFileMgmt *GetFileManangement(void);


