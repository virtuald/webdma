
#include <stdio.h>

#include <WebDMA/WebDMA.h>

#ifdef _MSC_VER
	#include <windows.h>
#else
	#include <unistd.h>
#endif

int main()
{
	IntProxy i1 = WebDMA::CreateIntProxy("Integers", "i1", 
					IntProxyFlags().default_value(5).minval(0).maxval(10).step(1) );
	IntProxy i2 = WebDMA::CreateIntProxy("Integers", "i2",
					IntProxyFlags().default_value(6).minval(0).maxval(10).step(1));
	IntProxy i3 = WebDMA::CreateIntProxy("Integers", "i1 + i2", 
					IntProxyFlags().default_value(11).readonly());

	FloatProxy f1 = WebDMA::CreateFloatProxy("Floats", "f1", 
					FloatProxyFlags().default_value(7).minval(-10).maxval(10).step(1) );
	FloatProxy f2 = WebDMA::CreateFloatProxy("Floats", "f2",
					FloatProxyFlags().default_value(.3F).minval(-1).maxval(1).step(.01F));
	FloatProxy f3 = WebDMA::CreateFloatProxy("Floats", "f1 + f2",
					FloatProxyFlags().default_value(7.3F).readonly());

	DoubleProxy d1 = WebDMA::CreateDoubleProxy("Doubles", "d1",
					DoubleProxyFlags().default_value(10).minval(-180).maxval(180).step(1));
	DoubleProxy d2 = WebDMA::CreateDoubleProxy("Doubles", "d2",
					DoubleProxyFlags().default_value(0).minval(-180).maxval(180).step(1));
	DoubleProxy d3 = WebDMA::CreateDoubleProxy("Doubles", "d1 + d2",
					DoubleProxyFlags().default_value(10).readonly());
	
	BoolProxy stayOn = WebDMA::CreateBoolProxy("Controls", "Turn server off", true);
	
	BoolProxy doCount = WebDMA::CreateBoolProxy("Controls", "Do counting", true);
	
	IntProxy count = WebDMA::CreateIntProxy("Controls", "counter", 
					IntProxyFlags().default_value(0).readonly() );
	
	WebDMA::Enable("8080", "../www");
	
	while (stayOn)
	{
		i3 = i1 + i2;
		f3 = f1 + f2;
		d3 = d1 + d2;
		
		if (doCount)
			count = count + 1;
	
		printf("%5d %5.2f %5.2f %d\r", (int)i3, (float)f3, (double)d3, (int)count);
	
#ifdef _MSC_VER
		Sleep(100);
#else
		usleep(10000);
#endif
	}

	return true;
	
}
