#ifndef CYUSB_H
#define CYUSB_H

extern "C"
{
	__declspec(dllexport) bool Open(int index = 0);
	__declspec(dllexport) bool Close();
	__declspec(dllexport) void SetTimeout(int value);
	__declspec(dllexport) int  ReadData(unsigned char* data,int size);
	__declspec(dllexport) int  WriteData(unsigned char* data,int size);
}

#endif
