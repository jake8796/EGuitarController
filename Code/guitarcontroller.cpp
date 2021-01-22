#define DATA_LENGTH 1

#include "SerialPort.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <WinUser.h>

using namespace std;
const char* portName = "\\\\.\\COM13";
//Declare a global object
SerialPort* arduino;
string startBit;
string b1;

char receivedString[DATA_LENGTH];

int main(void)
{
	arduino = new SerialPort(portName);
	while (arduino->isConnected())
	{
		arduino->readSerialPort(receivedString, DATA_LENGTH);
		startBit = receivedString;


		if (startBit == "a")
		{
			arduino->readSerialPort(receivedString, DATA_LENGTH);
			b1 = receivedString;

			if (b1 == "0") {
				keybd_event(0x26, 0, 0, 0);
				printf("Up\n");
			}
			else { keybd_event(0x26, 0, KEYEVENTF_KEYUP, 0); }
			if (b1 == "3") {
				keybd_event(0x28, 0, 0, 0);
				printf("Down\n");
			}
			else { keybd_event(0x28, 0, KEYEVENTF_KEYUP, 0); }
			if (b1 == "2") {
				keybd_event(0x25, 0, 0, 0);
				printf("Left\n");
			}
			else { keybd_event(0x25, 0, KEYEVENTF_KEYUP, 0); }
			if (b1 == "1") {
				keybd_event(0x27, 0, 0, 0);
				printf("Right\n");
			}
			else { keybd_event(0x27, 0, KEYEVENTF_KEYUP, 0); }
			if (b1 == "4") {
				keybd_event(0x20, 0, 0, 0);
				printf("Space\n");
			}
			else { keybd_event(0x20, 0, KEYEVENTF_KEYUP, 0); }

		}
	}
}







