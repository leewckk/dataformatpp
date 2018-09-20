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

/// @File: JsonObject.h
/// @brief:
/// @author:leewckk@126.com
/// @version:
/// @date:2018-09-14


#ifndef _JSONOBJECT_H
#define _JSONOBJECT_H

#include "DataObject.h"

class JsonObject : public DataObject
{
public:
	JsonObject();
	JsonObject(const JsonObject& obj);
	~JsonObject();
	
	virtual DataObject* dup();
	virtual int load(string path);
	virtual int save(string path);
	virtual int clear();
	virtual int parse(const char* s, const int size);
	virtual int parse(cJSON* root);
	virtual JsonObject clone();

	// JSON array operation
  virtual int is_empty(){ return (fJson == NULL);  }
	virtual int is_array();
	virtual int size_array();
	virtual int append(cJSON* obj);							//add an json object to json array
	virtual int append(JsonObject* obj);				//add an json object to json array
	virtual int append(JsonObject& obj);				//add an json object to json array
	virtual cJSON* detach(int idx);							//detach an object from json array, the detach node should freed by user
	virtual cJSON* detach(string key);					//detach an object from json object, the detach node should free by user
	virtual int remove(int idx);								//remove an object from root
	virtual int remove(string key);							//remove an object from root
	
	virtual int add(string key,string val);
	virtual int add(string key,int val);
	virtual int add(string key,double val);
	virtual int add(string key,JsonObject* val);
	
	virtual int get(string key, string& val);
	virtual int get(string key, int& val);
	virtual int get(string key, double& val);
	virtual JsonObject get(string key);
	virtual JsonObject get(int idx);

	virtual cJSON* sub(int idx);
	virtual cJSON* sub(string key);
	virtual cJSON* sub(cJSON* root, string key);
	virtual cJSON* new_sub(cJSON* root,string key,cJSON* sub);
	virtual cJSON* new_sub(cJSON* root,string key);
	virtual cJSON* new_sub(string key);
	virtual int print();
	virtual int print(string sub);
	virtual int print(int idx);
	virtual char* to_string();
	virtual int to_string(string &str);
  virtual cJSON* to_json();
	static int Dump(string comment,cJSON* root);
	virtual int to_bin(uint8_t *buffer, int& length);
	virtual JsonObject& operator=(const JsonObject& obj); 
	virtual JsonObject& operator=(cJSON* obj);
  virtual JsonObject& operator=(string jsonstring);
//  virtual JsonObject& operator[](int i);
	friend ostream& operator<<(ostream &output, const JsonObject& obj);
protected:
	cJSON*			fJson;
};


#endif
