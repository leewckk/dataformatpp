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
/// @File: array.cpp
/// @brief:
/// @author:leewckk@126.com
/// @version:1.0
/// @date:2018-09-18


#include <iostream>
using namespace std;

#include "dataformats.h"
#include "JsonObject.h"


/// @brief:main 
///
/// @param: argc
/// @param: argv
///
/// @return 
///
/// @author:leewckk@126.com
/// @date:2018-09-18
int main(int argc, char** argv)
{
	JsonObject arr,sub;
	int i;

	for(i = 0; i < 16; i++)
	{
		sub.add("stringVal","string");
		sub.add("intVal",i);
		sub.add("doubleVal",i*3.14);
		arr.append(sub);
	}

	cout <<arr<<endl;

	for(i = 0; i < 8; i++){
		sub = arr.detach(0+i);
		cout<<"Detach:" << sub<<endl;
	}
	cout<<"After detach: "<<arr<<endl;
	return 0;
}









