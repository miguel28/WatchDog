#include "USBInterfaceClass.h"

USBInterface::USBInterface()
{
	HIDisOpen = false;
	Error = false;
	DeviceHandle = NULL;
	Devs = NULL;
	CurDev = NULL;
	CleanBufferOUT();
	CleanBufferIN();
}
USBInterface::~USBInterface()
{
	HIDClose();
}

void USBInterface::EnumerateHIDs()
{
    Devs = hid_enumerate(0x0, 0x0);
	CurDev = Devs;	
	while (CurDev) {
		printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls",
			CurDev->vendor_id, CurDev->product_id, CurDev->path, CurDev->serial_number);
		printf("\n");
		printf("  Manufacturer: %ls\n", CurDev->manufacturer_string);
		printf("  Product:      %ls\n", CurDev->product_string);
		printf("\n");
		CurDev = CurDev->next;
	}
	hid_free_enumeration(Devs);     
}

void USBInterface::HIDOpen(const unsigned short VendorID, const unsigned short ProductID)
{
    if(!HIDisOpen)
    {
        DeviceHandle = hid_open(VendorID, ProductID, NULL);
		vendorID = VendorID;
		productID = ProductID;
        if(DeviceHandle)HIDisOpen= true;
    }
}

void USBInterface::HIDReOpen()
{
	if(HIDisOpen)
		HIDClose();
	DeviceHandle = hid_open(vendorID, productID, NULL);
	if(DeviceHandle)
	{
		HIDisOpen=true;
		Error = false;
	}
}


void USBInterface::HIDDescription()
{
    if(HIDisOpen)
    {
        hid_get_manufacturer_string(DeviceHandle, wstr, MAX_STR);
        printf("Manufacturer String: %ls\n", wstr);
        hid_get_product_string(DeviceHandle, wstr, MAX_STR);
        printf("Product String: %ls\n", wstr);
        hid_get_serial_number_string(DeviceHandle, wstr, MAX_STR);
        printf("Serial String: %ls\n", wstr);
    }
}

void USBInterface::HIDClose()
{
     if(HIDisOpen)
     {
        hid_close(DeviceHandle);
        hid_set_nonblocking(DeviceHandle,1);
        HIDisOpen= false;    
     }
}

void USBInterface::CleanBufferOUT()
{
    int i;
	for(i=0; i<65; i++)BufferOUT[i]=0x00;     
}

void USBInterface::CleanBufferIN()
{
    int i;
	for(i=0; i<65; i++)BufferIN[i]=0x00;     
}

int USBInterface::SendBuffer()
{
    int Result;
	if(HIDisOpen)
	{
        BufferOUT[0]=0x00;
		Result = hid_write(DeviceHandle, BufferOUT, 65);
	}
    else Result = -1;
	
	if(Result <0) Error = true;
	else Error = false;
	
	return Result;
}

int USBInterface::ReciveBuffer()
{
    int Result;
	
	CleanBufferIN();
	if(HIDisOpen && !Error)
    {
        //Result = hid_read_timeout(DeviceHandle, BufferIN, 65,1);
        Result = hid_read(DeviceHandle, BufferIN, 65);
    }
    else Result = -1;
	
	if(Result < 0) Error = true;
	else Error = false;
	
	return Result;
}

void USBInterface::SetByte(unsigned short Position, unsigned char Data)
{
	if(HIDisOpen && Position <= 65)
    {
        BufferOUT[Position+1]=Data;
    }
    else return;
}

unsigned char USBInterface::GetByte(unsigned short Position)
{
    if(HIDisOpen && Position <= 65)
    {
        return BufferIN[Position];
    }
    else return 0x00;
}

int USBInterface::SendOutputPort(const unsigned char Value)
{
    if(HIDisOpen)
    {
        CleanBufferOUT();
        BufferOUT[1]=Value;
        return SendBuffer();
    }
    else return -1;
}

unsigned char USBInterface::GetInputBuffer()
{
    CleanBufferIN();
    ReciveBuffer();
    if(HIDisOpen)
    {
        return BufferIN[0];
    }
    else return 1;
}

void USBInterface::PrintBufferIN()
{
    int i;
	for (i = 0; i < 65; i++)
		printf("Data[%d]: %d\n", i, BufferIN[i]);
}

void USBInterface::PrintBufferIN(int Position)
{
	printf("Data[%d]: %d\n", Position, BufferIN[Position]);
}
