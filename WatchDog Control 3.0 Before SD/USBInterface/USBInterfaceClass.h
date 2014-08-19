/*
USB Class Interface
Version 1.1
Miguel Inc.
*/
#include <iostream>
#include <stdio.h>
#include "hidapi.h"

#define MAX_STR 255


class USBInterface
{
public:
	unsigned char BufferOUT[65];
	unsigned char BufferIN[65];
	bool HIDisOpen;
	bool Error;
	
	USBInterface();
	~USBInterface();
	
	void EnumerateHIDs(); // List All HID Devices conected in the computer
	void HIDOpen(const unsigned short VendorID, const unsigned short ProductID); // Open Specific HID device to work
	void HIDReOpen();
	void HIDDescription();
	void HIDClose(); // Close the device of work
      
	int SendBuffer(); // Send BufferOUT to the HID
	int ReciveBuffer();
	
	void CleanBufferOUT();
	void CleanBufferIN();
	void PrintBufferIN();
	void PrintBufferIN(int Position); 
	
	void SetByte(unsigned short Position, unsigned char Data);
	unsigned char GetByte(unsigned short Position);
	int SendOutputPort(const unsigned char Value);
	unsigned char GetInputBuffer();

private:
	hid_device *DeviceHandle;
	wchar_t wstr[MAX_STR];
	struct hid_device_info *Devs, *CurDev;
	unsigned short vendorID;
	unsigned short productID;
};
