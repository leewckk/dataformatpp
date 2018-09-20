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

/// @File: JsonObject.cpp
/// @brief:
/// @author:leewckk@126.com
/// @version:
/// @date:2018-09-14


#include "dataformats.h"
#include <string>
#include <iostream>
using namespace std;

#include "JsonObject.h"

/// @brief:JsonObject 
///
/// @param: ):
///
/// @author:leewckk@126.com
/// @date:2018-09-14
JsonObject::JsonObject():
	fJson(NULL)
{
}


/// @brief:JsonObject 
///
/// @param: obj):
///
/// @author:leewckk@126.com
/// @date:2018-09-14
JsonObject::JsonObject(const JsonObject& obj):
	fJson(NULL)
{
	fJson = cJSON_Duplicate(obj.fJson,1);	
}

/// @brief:~JsonObject 
///
/// @author:leewckk@126.com
/// @date:2018-09-04
JsonObject::~JsonObject()
{
	if(NULL != fJson) cJSON_Delete(fJson);
}


/// @brief:load 
///
/// @param: path
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-14
int JsonObject::load(string path)
{
	if(DataObject::load(path) != 0) return -1;

	if(NULL != fJson) cJSON_Delete(fJson);
	fJson = cJSON_Parse((const char*)fBuffer);

	if(NULL == fJson) return -1;
	return 0;
}


/// @brief:save 
///
/// @param: path
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-14
int JsonObject::save(string path)
{
	char* s = cJSON_Print(fJson);
	if(NULL == s) return -1;

	fBufferSize = strlen(s);
	if(NULL != fBuffer) free(fBuffer);

	fBuffer = (uint8_t*)malloc(fBufferSize);

	if(NULL != fBuffer){
		memcpy(fBuffer,s,fBufferSize);		
	}
	free(s);
	DataObject::save(path);
	return 0;
}

/// @brief:clear 
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
int JsonObject::clear()
{
	if(NULL != fJson)
	{
		cJSON_Delete(fJson);
		fJson = NULL;
	}
	return DataObject::clear();
}

/// @brief:dup 
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-04
DataObject* JsonObject::dup()
{
	if(NULL == fJson) return NULL;
	
	JsonObject* obj = new JsonObject();
	obj->fBufferSize = fBufferSize;
	if(fBufferSize > 0){
		obj->fBuffer = (uint8_t*)malloc(fBufferSize);
		memcpy(obj->fBuffer,fBuffer,fBufferSize);
	}
	obj->fJson = cJSON_Duplicate(fJson,1);
	return obj;
}

/// @brief:clone 
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-07
JsonObject JsonObject::clone()
{
	JsonObject obj;

	obj.fBufferSize = fBufferSize;
	if(fBufferSize > 0){
		obj.fBuffer = (uint8_t*)malloc(fBufferSize);
		memcpy(obj.fBuffer,fBuffer,fBufferSize);
	}
	obj.fJson = cJSON_Duplicate(fJson,1);
	return obj;
}

/// @brief:parse 
///
/// @param: s
/// @param: size
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-04
int JsonObject::parse(const char* s, const int size)
{
	if((NULL == s) || (size == 0)) return -1;

	if(NULL != fJson) cJSON_Delete(fJson);
	fJson = cJSON_Parse(s);
	return (NULL == fJson);
}


/// @brief:parse 
///
/// @param: root
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-04
int JsonObject::parse(cJSON* root)
{
	if(root == NULL) return -1;
	if(NULL != fJson) cJSON_Delete(fJson);

	fJson = cJSON_Duplicate(root,1);
	return (NULL == fJson);
}


/// @brief:add 
///
/// @param: key
/// @param: val
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
int JsonObject::add(string key,string val)
{
	cJSON* root = new_sub(key);
	if(NULL == root) return -1;

	root->type = cJSON_String;
	if(NULL != root->valuestring) free(root->valuestring);
	root->valuestring = strdup(val.c_str());
	return 0;
}
	


/// @brief:add 
///
/// @param: key
/// @param: val
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-14
int JsonObject::add(string key,int val)
{
	cJSON* root = new_sub(key);
	if(NULL == root) return -1;

	root->type = cJSON_Number;
	if(NULL != root->valuestring){
		free(root->valuestring);
		root->valuestring = NULL;
	} 
	root->valueint = val;
	root->valuedouble = val;
	return 0;
}


/// @brief:add 
///
/// @param: key
/// @param: val
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
int JsonObject::add(string key,double val)
{
	cJSON* root = new_sub(key);
	if(NULL == root) return -1;

	root->type = cJSON_Number;
	if(NULL != root->valuestring){
		free(root->valuestring);
		root->valuestring = NULL;
	} 
	root->valueint = val;
	root->valuedouble = val;
	return 0;
}


/// @brief:add 
///
/// @param: key
/// @param: val
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
int JsonObject::add(string key,JsonObject* val)
{
	cJSON* root = new_sub(fJson,key,cJSON_Duplicate(val->fJson,1));
	return (root == NULL);
}

/// @brief:get 
///
/// @param: key
/// @param: val
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-04
int JsonObject::get(string key, string& val)
{
	if(NULL == fJson) return -1;

	cJSON* obj = sub(key);
	if(NULL == obj) return -1;

	if(obj->type != cJSON_String){
		return -1;
	}
	val = obj->valuestring;
	return 0;
}

/// @brief:get 
///
/// @param: key
/// @param: val
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-04
int JsonObject::get(string key, int& val)
{
	if(NULL == fJson) return -1;

	cJSON* obj = sub(key);
	if(NULL == obj) return -1;

	if(obj->type == cJSON_Number){
	  val = obj->valueint;
		return 0;
	}else if(obj->type == cJSON_String){
    if(NULL != obj->valuestring){
      val = atoi(obj->valuestring);
    }
  }
	return 0;
}
	


/// @brief:get 
///
/// @param: key
/// @param: val
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-04
int JsonObject::get(string key, double& val)
{
	if(NULL == fJson) return -1;

	cJSON* obj = sub(key);
	if(NULL == obj) return -1;

	if(obj->type == cJSON_Number){
	  val = obj->valuedouble;
		return 0;
	}else if(obj->type == cJSON_String){
    if(NULL == obj->valuestring){
      val = atof(obj->valuestring);
    }
  }
	return 0;
}


/// @brief:get 
///
/// @param: key
/// @param: val
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-04
JsonObject JsonObject::get(string key)
{
	JsonObject obj;
	cJSON* root = sub(key);
	obj.parse(root);
	return obj;
}


/// @brief:get 
///
/// @param: key
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-07
JsonObject JsonObject::get(int idx)
{
	JsonObject obj;
	cJSON* root = sub(idx);
	obj.parse(root);
	return obj;
}

/// @brief:print 
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-04
int JsonObject::print()
{
	char* s;
	if(NULL == fJson) return -1;
	s = cJSON_Print(fJson);
	cout<<s<<endl;
	free(s);
	return 0;
}



/// @brief:print 
///
/// @param: sub
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
int JsonObject::print(string sub)
{
	JsonObject obj = get(sub);
	return obj.print();
}

/// @brief:print 
///
/// @param: idx
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-07
int JsonObject::print(int idx)
{
	JsonObject obj = get(idx);
	return obj.print();
}


/// @brief:to_string 
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-04
char* JsonObject::to_string()
{
	char* s;
	if(NULL == fJson) return NULL;
	s = cJSON_Print(fJson);
	return s;
}

/// @brief:to_string 
///
/// @param: str
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-20
int JsonObject::to_string(string &str)
{
  char* s = to_string(); 
  if(NULL != s){
    str = s;
    free(s);
  }
  return 0;
}


/// @brief:to_json 
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-18
cJSON* JsonObject::to_json()
{
  cJSON* root; 
  if(NULL == fJson) return NULL;
  root = cJSON_Duplicate(fJson,1);
  return root;
}

/// @brief:to_bin 
///
/// @param: buffer
/// @param: length
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-04
int JsonObject::to_bin(uint8_t *buffer, int& length)
{
	return 0;
}

/// @brief:sub 
///
/// @param: idx
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-07
cJSON* JsonObject::sub(int idx)
{
	if((NULL == fJson) || (fJson->type != cJSON_Array)) return NULL;
	if(cJSON_GetArraySize(fJson) <= idx) return NULL;
	return cJSON_GetArrayItem(fJson,idx);
}

/// @brief:sub 
///
/// @param: key
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
cJSON* JsonObject::sub(string key)
{
#if 0	
	string::size_type pos;
	if(("" == key)||(NULL == fJson)) return NULL;

	pos = key.find(".");
	// check sub string exist
	if(pos == key.npos){
		cJSON* obj = cJSON_GetObjectItem(fJson,key.c_str());
		return obj;
	}else{
		string substr = key.substr(pos + 1);
		return sub(substr);
	}
#endif 
	return sub(fJson,key);
}


/// @brief:sub 
///
/// @param: root
/// @param: key
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-18
cJSON* JsonObject::sub(cJSON* root, string key)
{
	cJSON* subObj;
	string::size_type pos;
	if(("" == key)||(NULL == root)) return NULL;

	pos = key.find(".");
	// check sub string exist
	if(pos == key.npos){
		cJSON* obj = cJSON_GetObjectItem(root,key.c_str());
		return obj;
	}else{
		string subKey = key.substr(0,pos);
		string substr = key.substr(pos + 1);
		subObj = cJSON_GetObjectItem(root,subKey.c_str());
		return sub(subObj,substr);
	}	
}


/// @brief:new_sub 
///
/// @param: key
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
cJSON* JsonObject::new_sub(string key)
{
	if(fJson == NULL) fJson = cJSON_CreateObject();
	return new_sub(fJson,key);
}

/// @brief:new_sub 
///
/// @param: root
/// @param: key
/// @param: sub
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
cJSON* JsonObject::new_sub(cJSON* root,string key,cJSON* subobj)
{
	cJSON* subJson;
	string substr,leftstr,substr2;
	string::size_type pos;
	if(("" == key)) return NULL;

	if(NULL == root){
		root = cJSON_CreateObject();
		if(fJson != NULL) cJSON_Delete(fJson);
		fJson = root;
	} 
	leftstr = key;
	
	do
	{
		pos = leftstr.find(".");
		if(pos == leftstr.npos){
			substr = leftstr;
			
			subJson = cJSON_GetObjectItem(root,substr.c_str());
			if(NULL != subJson){
				cJSON_Delete(subJson);
			}
			subJson = subobj;//cJSON_CreateObject();
			cJSON_AddItemToObject(root,substr.c_str(),subJson);
			break;
		}
		else
		{
			substr = leftstr.substr(0,pos);
			subJson = cJSON_GetObjectItem(root,substr.c_str());
			if(NULL == subJson){
				subJson = cJSON_CreateObject();
				cJSON_AddItemToObject(root,substr.c_str(),subJson);
			}
		}
		substr2 = leftstr.substr(pos + 1);
		leftstr = substr2;
		root = subJson;
	}while(1);
	return subJson;	
}

/// @brief:new_sub 
///
/// @param: key
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
cJSON* JsonObject::new_sub(cJSON* root,string key)
{
	cJSON* subJson;
	string substr,leftstr,substr2;
	string::size_type pos;
	if(("" == key)) return NULL;

	if(NULL == root) root = cJSON_CreateObject();
	leftstr = key;
	do{
		pos = leftstr.find(".");
		if(pos == leftstr.npos){
			substr = leftstr;
		}else substr = leftstr.substr(0,pos);

		subJson = cJSON_GetObjectItem(root,substr.c_str());
		if(NULL == subJson){
			subJson = cJSON_CreateObject();
			cJSON_AddItemToObject(root,substr.c_str(),subJson);
		}

		if(pos == leftstr.npos){
			break;
		}
		substr2 = leftstr.substr(pos + 1);
		leftstr = substr2;
		root = subJson;
	}while(1);
	return subJson;	
}


/// @brief:is_array 
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
int JsonObject::is_array()
{
	if(NULL == fJson) return -1;
	if(fJson->type != cJSON_Array) return 0;
	return 1;
}


/// @brief:size_array 
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
int JsonObject::size_array()
{
	if((NULL == fJson) || (fJson->type != cJSON_Array)) return -1;
	return cJSON_GetArraySize(fJson);
}


/// @brief:append 
///
/// @param: obj
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
int JsonObject::append(cJSON* obj)
{
	if((NULL == obj)) return -1;

	if(NULL == fJson){
		fJson = cJSON_CreateArray();
	}

	if((obj->type != cJSON_Object) ||(fJson->type != cJSON_Array)){
		cJSON_Delete(obj);
		return -1;
	}
	cJSON_AddItemToArray(fJson,obj);
	return 0;
}
	


/// @brief:append 
///
/// @param: obj
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-07
int JsonObject::append(JsonObject& obj)
{
	if(NULL == obj.fJson) return -1;
	return append(cJSON_Duplicate(obj.fJson,1));	
}

/// @brief:append 
///
/// @param: obj
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
int JsonObject::append(JsonObject* obj)
{
	if((NULL == obj)||(obj->fJson)) return -1;
	return append(cJSON_Duplicate(obj->fJson,1));
}


/// @brief:detach an object from json array
///
/// @param: idx
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
int JsonObject::remove(int idx)
{
	if((NULL == fJson) || (fJson->type != cJSON_Array)) return -1;
	if(cJSON_GetArraySize(fJson) <= idx) return -1;
	cJSON_DeleteItemFromArray(fJson,idx);
	return 0;
}
	

/// @brief:remove an object from root
///
/// @param: key
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
int JsonObject::remove(string key)
{
	if((NULL == fJson) || (fJson->type != cJSON_Object)) return -1;
	cJSON_DeleteItemFromObject(fJson,key.c_str());
	return 0;
}



/// @brief:detach 
/// detach an object from json array
/// @param: idx
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-07
cJSON* JsonObject::detach(int idx)
{
	if((NULL == fJson) || (fJson->type != cJSON_Array)) return NULL;
	if(cJSON_GetArraySize(fJson) <= idx) return NULL;
	return cJSON_DetachItemFromArray(fJson,idx);
}



/// @brief:detach 
/// detach an object from json object
///
/// @param: key
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-07
cJSON* JsonObject::detach(string key)
{
	if((NULL == fJson) || (fJson->type != cJSON_Object)) return NULL;
	return cJSON_DetachItemFromObject(fJson,key.c_str());
}

/// @brief:operator= 
///
/// @param: obj
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
JsonObject& JsonObject::operator=(const JsonObject& obj)
{
	if(NULL != this->fJson) cJSON_Delete(this->fJson);
	if(NULL != obj.fJson){
		this->fJson = cJSON_Duplicate(obj.fJson,1);
	}
	return *this;
}

/// @brief:operator= 
///
/// @param: obj
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-18
JsonObject& JsonObject::operator=(cJSON* obj)
{
	if(NULL == obj) return *this;
	this->clear();
	this->parse(obj);
	cJSON_Delete(obj);
	return *this;
}


/// @brief:operator= 
///
/// @param: jsonstring
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-20
JsonObject& JsonObject::operator=(string jsonstring)
{
  this->clear();
  this->parse(jsonstring.c_str(),jsonstring.length());
  return *this;
}

#if 0
/// @brief:operator[] 
///
/// @param: i
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-20
JsonObject& JsonObject::operator[](int i)
{
  if(i >= size_array()) return *this[0];
}
#endif 

/// @brief:operator<< 
///
/// @param: output
/// @param: obj
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
ostream& operator<<(ostream &output, const JsonObject& obj)
{
	if(NULL != obj.fJson){
		char* s = cJSON_Print(obj.fJson);
		if(NULL != s){
			output<<s;
			free(s);
		}	
	}
	return output;
}



/// @brief:Dump 
///
/// @param: comment
/// @param: root
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-13
int JsonObject::Dump(string comment,cJSON* root)
{
	char* s;
	if(NULL == root) return -1;

	s = cJSON_Print(root);
	if(NULL != s){
		cout<<comment<<":"<<s<<endl;
		free(s);
	}
	return 0;
}



