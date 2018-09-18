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
/// @File: test_load.cpp
/// @brief:
/// @author:leewckk@126.com
/// @version:1.0
/// @date:2018-09-17


#include <iostream>
using namespace std;

#include "dataformats.h"
#include "JsonObject.h"


static const char ussage[] = "\n\
    load json object from file, by typing: load $filename\n";

/// @brief:main 
///
/// @param: argc
/// @param: argv
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-17
int main(int argc ,char** argv)
{
  JsonObject object;
  if(argc < 2){
    cout<<ussage<<endl;
    exit(0);
  }

  if(NULL != argv[1])
  {
    object.load(argv[1]);
    cout<<object<<endl;
  }
  return 0;
}
