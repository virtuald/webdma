
#include <WebDMA/WebDMA.h>

#ifdef _MSC_VER

	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
	#include <windows.h>
#else
	#include <stdio.h>
	#include <unistd.h>
#endif




bool DoWebDMA()
{
	WebDMA webdma("8080", "../../www");

	IntProxy i1 = webdma.CreateIntProxy("Integers", "i1", 
					IntProxyFlags().default_value(5).minval(0).maxval(10).step(1) );
	IntProxy i2 = webdma.CreateIntProxy("Integers", "i2",
					IntProxyFlags().default_value(6).minval(0).maxval(10).step(1));
	IntProxy i3 = webdma.CreateIntProxy("Integers", "i1 + i2", 
					IntProxyFlags().default_value(11).readonly());

	FloatProxy f1 = webdma.CreateFloatProxy("Floats", "f1", 
					FloatProxyFlags().default_value(7).minval(-10).maxval(10).step(1) );
	FloatProxy f2 = webdma.CreateFloatProxy("Floats", "f2",
					FloatProxyFlags().default_value(.3F).minval(-1).maxval(1).step(.01F));
	FloatProxy f3 = webdma.CreateFloatProxy("Floats", "f1 + f2",
					FloatProxyFlags().default_value(7.3F).readonly());

	DoubleProxy d1 = webdma.CreateDoubleProxy("Doubles", "d1",
					DoubleProxyFlags().default_value(10).minval(-180).maxval(180).step(1));
	DoubleProxy d2 = webdma.CreateDoubleProxy("Doubles", "d2",
					DoubleProxyFlags().default_value(0).minval(-180).maxval(180).step(1));
	DoubleProxy d3 = webdma.CreateDoubleProxy("Doubles", "d1 + d2",
					DoubleProxyFlags().default_value(10).readonly());
	
	BoolProxy stayOn = webdma.CreateBoolProxy("Controls", "Turn server off", true);
	
	BoolProxy doCount = webdma.CreateBoolProxy("Controls", "Do counting", true);
	
	BoolProxy restart = webdma.CreateBoolProxy("Controls", "Restart server after off", false );
	
	bool newstuff_enabled = false;
	BoolProxy newStuff = webdma.CreateBoolProxy("Controls", "Create a new set of proxy objects", false );
	
	IntProxy count = webdma.CreateIntProxy("Controls", "counter", 
					IntProxyFlags().default_value(0).readonly() );
	
	webdma.Enable();
	
	while (stayOn)
	{
		i3 = i1 + i2;
		f3 = f1 + f2;
		d3 = d1 + d2;
		
		if (doCount)
			count = count + 1;
	
		printf("%5d %5.2f %5.2f %d\r", (int)i3, (float)f3, (double)d3, (int)count);
		
		if (newStuff && !newstuff_enabled)
		{					
			webdma.CreateIntProxy("New Category", "integer", 
				IntProxyFlags().default_value(11).readonly());

			webdma.CreateFloatProxy("New Category", "float", 
				FloatProxyFlags().default_value(7).minval(-10).maxval(10).step(1) );
		
			webdma.CreateDoubleProxy("New Category", "double",
				DoubleProxyFlags().default_value(10).minval(-180).maxval(180).step(1));
					
			webdma.CreateBoolProxy("New Category", "bool", true);
			
			newstuff_enabled = true;
		}
		
		
	
#ifdef _MSC_VER
		Sleep(100);
#else
		usleep(10000);
#endif
	}
	
	return restart;
}


int main()
{
#ifdef _MSC_VER
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	while( DoWebDMA() );

	return true;
	
}
