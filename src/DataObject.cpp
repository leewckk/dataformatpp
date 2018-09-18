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
//

/// @File: DataObject.cpp
/// @brief:
/// @author:leewckk@126.com
/// @version:
/// @date:2018-09-14


#include "dataformats.h"
#include <string>
#include <iostream>
using namespace std;

#include "DataObject.h"

/// @brief:DataObject 
///
/// @author:leewckk@126.com
/// @date:2018-09-04
DataObject::DataObject():
  fBuffer(NULL),fBufferSize(0)
{
}


/// @brief:DataObject 
///
/// @param: obj
///
/// @author:leewckk@126.com
/// @date:2018-09-05
DataObject::DataObject(const DataObject& obj):
	fBuffer(NULL),fBufferSize(0)
{
	fBufferSize = obj.fBufferSize;
	if(fBufferSize > 0){
		fBuffer = (uint8_t*)malloc(fBufferSize);
		memcpy(fBuffer,obj.fBuffer,fBufferSize);;
	}
}

/// @brief:~DataObject 
///
/// @author:leewckk@126.com
/// @date:2018-09-04
DataObject::~DataObject()
{
  if(NULL != fBuffer) free(fBuffer);
}

/// @brief:load 
///
/// @param: path
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-04
int DataObject::load(string path)
{
  FILE* fp; 
  int retVal = 0;

  fp = fopen(path.c_str(),"rb");
  do 
  {
    if(NULL == fp) { retVal = -1; break;}
    fseek(fp,0,SEEK_END);
    fBufferSize = ftell(fp);
    
    if(0 == fBufferSize) { retVal = -1; break;}

		if(NULL != fBuffer) free(fBuffer);
    fBuffer = (uint8_t*)malloc(fBufferSize);

    if(NULL == fBuffer) { retVal = -1; break;}
    fseek(fp,0,SEEK_SET);
    fread(fBuffer,1,fBufferSize,fp);
  }while(0);

  if(NULL != fp) fclose(fp);
  return retVal;
}



/// @brief:save 
///
/// @param: path
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-04
int DataObject::save(string path)
{
  FILE* fp;
 
  if((NULL == fBuffer) || (0 == fBufferSize)) return -1;

  fp = fopen(path.c_str(),"wb");

  if(NULL == fp) return -1;
  fwrite(fBuffer,sizeof(uint8_t),fBufferSize,fp);
  fclose(fp); 
  return 0;
}


/// @brief:clear 
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
int DataObject::clear()
{
	fBufferSize = 0;
	if(NULL != fBuffer) 
	{
		free(fBuffer);
		fBuffer = NULL;
	}
	return 0;	
}

/// @brief:print 
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-04
int DataObject::print()
{
  if((NULL == fBuffer) || (0 == fBufferSize)) return -1;
  printf("%s\n",(char*)fBuffer);
  return 0;
}

/// @brief:operator= 
///
/// @param: request
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-05
DataObject& DataObject::operator=(const DataObject& obj)
{
  if(this->fBuffer != NULL) free(this->fBuffer);
  this->fBufferSize = obj.fBufferSize;
  
  if((NULL != obj.fBuffer) && (obj.fBufferSize != 0)){
    this->fBuffer = (uint8_t*)malloc(this->fBufferSize);
    memcpy(this->fBuffer,obj.fBuffer,obj.fBufferSize);
  }
  return *this;
}
  

