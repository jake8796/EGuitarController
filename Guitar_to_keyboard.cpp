#define DATA_LENGTH 1

#include "SerialPort.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <WinUser.h>

using namespace std;
const char* portName = "\\\\.\\COM13";
string startInput;
//Declare a global object
SerialPort* arduino;
string justRead;
string b1, b2, b5, b6;
POINT mouse;

char receivedString[DATA_LENGTH];

int main(void)
{
	cout << "please type start and press enter to begin program" << endl;
	cin >> startInput;
	if (startInput == "start")
	{
		arduino = new SerialPort(portName);
		while (arduino->isConnected())
		{
			arduino->readSerialPort(receivedString, DATA_LENGTH);
			justRead = receivedString;


			if (justRead == "a")
			{
				arduino->readSerialPort(receivedString, DATA_LENGTH);//reading b1 (left stick -> shift)
				b1 = receivedString;
				cout << b1 << ends;
				if(b1 == "1") keybd_event(0x26, 0, 0, 0); 
				if(b1 == "0") keybd_event(0x26, 0, KEYEVENTF_KEYUP, 0); 

				arduino->readSerialPort(receivedString, DATA_LENGTH);//reading b2 (right stick -> middle mouse)
				b2 = receivedString;
				cout << b2 << ends;
				if (b2 == "1") { keybd_event(0x28, 0, 0, 0); }
				if (b2 == "0") { keybd_event(0x28, 0, KEYEVENTF_KEYUP, 0); }
			}



			if (justRead == "b")
			{
				arduino->readSerialPort(receivedString, DATA_LENGTH);//reading b5 (right button on left side -> E)
				b5 = receivedString;
				cout << b5 << ends;
				if (b5 == "1") { keybd_event(0x25, 0, 0, 0); }
				if (b5 == "0") { keybd_event(0x25, 0, KEYEVENTF_KEYUP, 0); }

				arduino->readSerialPort(receivedString, DATA_LENGTH);//reading b6 (left button on left side -> Q)
				b6 = receivedString;
				cout << b6 << ends;
				if (b6 == "1") { keybd_event(0x27, 0, 0, 0); }
				if (b6 == "0") { keybd_event(0x27, 0, KEYEVENTF_KEYUP, 0); }

			}

			cout << "" << endl;


		}

	}

}





