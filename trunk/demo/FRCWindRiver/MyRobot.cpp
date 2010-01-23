#include "WPILib.h"

#include <WebDMA/WebDMA.h>

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	Jaguar motor1;					// first motor
	Jaguar motor2;					// second motor
	
	WebDMA webdma;					// web server instance
	
	FloatProxy 	motor1speed;		// speed of first motor
	BoolProxy 	motor1enabled;		// control enabled
	
	FloatProxy 	motor2speed;		// speed of second motor
	BoolProxy	motor2enabled;		// control enabled for it
	
public:
	RobotDemo(void):
		motor1(1), 
		motor2(2)
	{
		GetWatchdog().SetExpiration(0.1);
		
		// motor control parameters:
		//      start: 0
		//      min: -1
		//      max: 1
		//      step value: 0.1 (this means the values of the proxy object
		//                       can be increased/decreased in steps of this
		//                       amount)
		
		motor1speed = webdma.CreateFloatProxy("Motor 1", "Speed",
						FloatProxyFlags().default_value(0.0F).minval(-1.0F).maxval(1.0F).step(0.1) );
		
		// enable motor 1 by default
		motor1enabled = webdma.CreateBoolProxy("Motor 1", "Enabled", true);
		
		
		motor2speed = webdma.CreateFloatProxy("Motor 2", "Speed",
						FloatProxyFlags().default_value(0.0F).minval(-1.0F).maxval(1.0F).step(0.1) );
		
		// disable motor 2 by default
		motor1enabled = webdma.CreateBoolProxy("Motor 2", "Enabled", true);
		
		
		// finally enable the web server (note: you can create proxies
		// after you've enabled the web server too)
		webdma.Enable("80", "/www");
	}

	void Autonomous(void)
	{
	}

	void OperatorControl(void)
	{
		GetWatchdog().SetEnabled(true);
		while (IsOperatorControl())
		{
			GetWatchdog().Feed();
		
			// if the user has motor 1 enabled, then set the value they want
			if (motor1enabled)
				motor1.Set(motor1speed);
			else
				motor1.Set(0);
		
			// if the user has motor 2 enabled, then set the value they want
			if (motor2enabled)
				motor2.Set(motor2speed);
			else
				motor2.Set(0);
			
			
			Wait(0.005);				// wait for a motor update time
		}
		
		// disable motors when leaving operator control mode
		// otherwise unexpected things may happen
		motor1.Set(0);
		motor2.Set(0);
	}
};

START_ROBOT_CLASS(RobotDemo);

