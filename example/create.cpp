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
/// @File: create.cpp
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
	JsonObject obj0, obj1,obj2,obj3;
	string strVal;
	int intVal;
	double dbVal;
  cJSON* root;

	obj0.add("string0","value0");
	obj0.add("int0",0);
	obj0.add("double0",3.1415926);

	obj2.add("substring","stringval0");
	obj2.add("subdouble",9.8);

	obj0.add("sub",&obj2);

	obj1 = obj0;
	cout<<obj1<<endl;

	obj1.get("string0",strVal);
	cout<<"string0 = "<<strVal<<endl;

	obj1.get("int0",intVal);
	cout<<"int0 = "<<intVal<<endl;
	
	obj1.get("double0",dbVal);
	cout<<"double0 = "<<dbVal<<endl;
	
	obj1.get("sub.subdouble",dbVal);
	cout<<"sub.subdouble = "<<dbVal<<endl;
	
	obj1.get("sub.substring",strVal);
	cout<<"sub.substring = "<<strVal<<endl;

	obj1.save("./obj1.json");

  root = obj1.to_json();
  obj3 = root;

  cout << "obj3";
  cout << obj3 << endl;
	return 0;
}

















