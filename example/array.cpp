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
  JsonObject config,channelConfig;
  
  for(int i = 0; i < 6; i++){
    channelConfig.add("channel",i);
    channelConfig.add("ip","tcp://192.168.199.1");
    channelConfig.add("port",4000 + i*10);

#if 0  //// configCamera.json   
    channelConfig.add("channel",i);
    channelConfig.add("device","/dev/video0");
    channelConfig.add("usbport","/sys/bus/usb/devices/1-1/1-1.1/1-1.1:1.0/");
    
   /*  channelConfig.add("channel",i); */
    // channelConfig.add("hardware",i + 1);
    // channelConfig.add("tty","/dev/ttyS0");
    // channelConfig.add("startMap",3 - i);
    // channelConfig.add("endMap",4*i);
    // channelConfig.add("maxMap",4);
    // channelConfig.add("bps",500000);
    // channelConfig.add("channelBPS",115200);
    // channelConfig.add("ZMQPort",9800 + i * 10);
    // channelConfig.add("ZMQCenter",5810);
#endif 
    config.append(channelConfig);
    
    /*     channelConfig.add("channel",i); */
    // channelConfig.add("workspace","/opt/var/media");
    // channelConfig.add("fps",30);
    // channelConfig.add("idle",1000);
    // channelConfig.add("recordtype",0);
    // channelConfig.add("showwindow",0);
    // channelConfig.add("captureWidth",4608);
    // channelConfig.add("captureHeight",3456);
    // channelConfig.add("recordWidth",1920);
    // channelConfig.add("recordHeight",1080);
    // channelConfig.add("detector",1);
    /* config.append(channelConfig); */
  }

  cout<<config<<endl;
  config.save("configSharedEth.json");
///  config.save("configCamera.json");
//  config.save("configCOMExt.json");
#if 0
  JsonObject arr,sub;
	JsonObject int_arr,double_arr,string_arr;
	int i;
	int intval;
	double dbval;
	string strval;
	char cval[128];

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

	for(i = 0; i < 5; i++){
		dbval = i*3.14;
		memset(cval,0,sizeof(cval));
		sprintf(cval,"%f",dbval);
		strval = cval;
		int_arr.append(i);
		double_arr.append(dbval);
		string_arr.append(strval);
	}

	cout<<"int array: "<<int_arr<<endl;
	cout<<"double array: "<<double_arr<<endl;
	cout<<"string array: "<<string_arr<<endl;

	int_arr.get(3,intval);
	double_arr.get(2,dbval);
	string_arr.get(1,strval);

	cout<<"int[3]: "<<intval<<endl;
	cout<<"double[2]: "<<dbval<<endl;
	cout<<"string[1]: "<<strval<<endl<<endl;

	string_arr.get(2,dbval);
	cout<<"string[2]: "<<dbval<<endl<<endl;
	
	double_arr.get(3,strval);
	cout<<"double[3]: "<<strval<<endl<<endl;

	int_arr.get(4,strval);
	cout<<"int[4]: "<<strval<<endl<<endl;
#endif 	
	return 0;
}












