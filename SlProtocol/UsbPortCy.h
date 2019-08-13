#pragma once

//#include <vector>
//#include <windows.h>
//
//using namespace std;
//
//class CUsbPortCy
//{
//public:
//	CUsbPortCy();
//	~CUsbPortCy();
//
//public:
//	bool open(int num);
//	bool close();
//	bool write(vector<unsigned char> data);
//	bool read(vector<unsigned char> &data);
//	bool write(unsigned char *data, int maxSize);
//	bool read(unsigned char *data, int maxSize);
//
//protected:
//	void loadDll();
//	void unloadDLL();
//
//protected:
//	bool _isConnected;
//	bool _isLoaded;
//	HINSTANCE _hdll;
//
//protected:
//	typedef bool(*FunOpen)(int);
//	typedef bool(*FunClose)();
//	typedef bool(*FunSetTimeout)(int);
//	typedef int(*FunReadData)(unsigned char *, int);
//	typedef int(*FunWriteData)(unsigned char *, int);
//
//	FunOpen Open;
//	FunClose Close;
//	FunSetTimeout SetTimeout;
//	FunReadData ReadData;
//	FunWriteData WriteData;
//};

#include <vector>

using namespace std;

class CUsbPortCy
{
public:
    CUsbPortCy();
    ~CUsbPortCy();

public:
    bool open(int num);
    bool close();
    bool write(vector<unsigned char> data);
    bool read(vector<unsigned char> &data);
    bool write(unsigned char *data, int maxSize);
    bool read(unsigned char *data, int maxSize);

protected:
    bool _isConnected;
};
