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
/// @File: DataObject.h
/// @brief:
/// @author:leewckk@126.com
/// @version:
/// @date:2018-09-14

#ifndef _DATAOBJECT_H
#define _DATAOBJECT_H


class DataObject {
public:
	DataObject();
	DataObject(const DataObject& obj);
	virtual ~DataObject();
	virtual int load(string path);
	virtual int save(string path);
	virtual DataObject* dup() = 0;
	virtual int parse(const char* s, const int size) = 0;

	virtual int add(string key,string val) = 0;
	virtual int add(string key,int val) = 0;
	virtual int add(string key,double val) = 0;
//	virtual int add(string key,DataObject* val) = 0;
	
	virtual int get(string key, string& val) = 0;
	virtual int get(string key, int& val) = 0;
	virtual int get(string key, double& val) = 0;
//	virtual DataObject* get(string key) = 0;
	virtual int print() = 0;
	virtual int clear() = 0;
	virtual char* to_string() = 0;
	virtual int to_bin(uint8_t *buffer, int& length) = 0;
	virtual DataObject& operator=(const DataObject& request); 
protected:
	uint8_t*		fBuffer;
	uint32_t		fBufferSize;
};

#endif
