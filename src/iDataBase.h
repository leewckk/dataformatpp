// Copyright (C) 
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// 
// 2018 - leewckk@126.com

/// @File: iDataBase.h
/// @brief:
/// @author:leewckk@126.com
/// @version:
/// @date:2018-09-14



#ifndef _IDATABASE_H
#define _IDATABASE_H

class iDataBase{
public:
	virtual ~iDataBase(){};
	virtual int Open() = 0;
	virtual int Open(string dbName) = 0;
	virtual int Close() = 0;
	virtual int Execute(xt_json *result,const char* fmt,...) = 0;
protected:
	char*				fDbName;
	int					fIsOpen;
};


#endif
