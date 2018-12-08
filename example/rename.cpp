/**
	* File Name: example/rename.cpp
	* Author: liwenchao
	* Mail: liwenchao@megvii.com
	* Created Time: 2018-12-08 11:49:50
	* Copyright (C) Face++ 2018 - 2088. All right recerved.
  * 
  * history
  *   1.Date          : 2018-12-08 11:49:50
  *     Author        : liwenchao
  *     Modification  : Create file.
  **/

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
/// @date:2018-12-08
int main(int argc, char** argv)
{
  JsonObject obj0,obj1,sub0,sub1;
  
  obj0.add("aaa",1);
  obj0.add("bbb",2);
  sub0.add("aaa",1);
  sub0.add("ccc",3);
  
  obj0.add("sub0",&sub0);

  for(int i = 0; i < 5; i++)
  {
    sub1.add("aaa",3);
    sub1.add("kkk",9);
    obj1.append(sub1);
  }
  obj0.add("sub1",&obj1);

  cout<<"before: ";
  cout<<obj0<<endl;

  cout<<"after: ";
  obj0.rename("aaa","AAA");
  obj0.rename("sub0.aaa","AAA");
  obj0.renamearray("sub1","aaa","AAA");
  cout<<obj0<<endl;
  return 0;
}









