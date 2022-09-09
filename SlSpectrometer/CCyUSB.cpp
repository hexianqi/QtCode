#include "CCyUSB.h"

#ifdef Q_CC_MSVC
CCyUSB::CCyUSB()
{
    _timeout = 1000;
    //  GUID guid = {0xAE18AA61, 0x7F6A, 0x11D4, 0x97, 0xDD, 0x00, 0x01, 0x02, 0x29, 0xB9, 0x58};
    //	m_pUSBDev = new CCyUSBDevice(NULL, guid);
    _device = new CCyUSBDevice(NULL);
    _readEpt = nullptr;
    _writeEpt = nullptr;
    _outOverlapped.hEvent  = CreateEvent(NULL, false, false, "CYUSB_OUT");
    _inOverlapped.hEvent   = CreateEvent(NULL, false, false, "CYUSB_IN");
}

CCyUSB::~CCyUSB()
{
    CloseHandle(_outOverlapped.hEvent);
    CloseHandle(_inOverlapped.hEvent);
    _device->Close();
    if (_readEpt)
        delete _readEpt;
    if (_writeEpt)
        delete _writeEpt;
    if (_outContext)
        delete _outContext;
    if (_inContext)
        delete _inContext;
    delete _device;
}

bool CCyUSB::open(int index)
{
    int i;
    bool out, in, bulk;

    if (index >= _device->DeviceCount())
        return false;

    if (!_device->Open(index))
        return false;

    for (i = 1; i < _device->EndPointCount(); i++)
    {
        out = _device->EndPoints[i]->Address == 0x02;
        in = _device->EndPoints[i]->Address == 0x86;
        bulk = _device->EndPoints[i]->Attributes == 2;
        if (bulk && in)
        {
            _readEpt = (CCyBulkEndPoint *)_device->EndPoints[i];
            _readEpt->SetXferSize(5120);
        }
        if (bulk && out)
        {
            _writeEpt = (CCyBulkEndPoint *)_device->EndPoints[i];
            _writeEpt->SetXferSize(512);
        }
    }
    return true;
}

bool CCyUSB::close()
{
    _device->Close();
    return true;
}

void CCyUSB::setTimeout(int value)
{
    _timeout = value;
}

int CCyUSB::read(unsigned char *data, int length)
{
    if (_readEpt == 0)
        return 0;

    long longLen = length;
    _readEpt->TimeOut = _timeout;
    if (!_readEpt->XferData(data, longLen))
        return 0;
    return longLen;
}

int CCyUSB::write(unsigned char *data, int length)
{
    if (_writeEpt == 0)
        return 0;

    long longLen = length;

    _writeEpt->TimeOut = _timeout;
    if (!_writeEpt->XferData(data, longLen))
        return 0;
    return longLen;
}

bool CCyUSB::sn(wchar_t *data, int length)
{
    if (!_device->IsOpen())
        return false;
    for (int i = 0; i < USB_STRING_MAXLEN && i < length; i++)
        data[i] = _device->SerialNumber[i];
    return true;
}

bool CCyUSB::transport(unsigned char *downData, long downLength, unsigned char *upData, long upLength)
{
    if (_readEpt == nullptr || _writeEpt == nullptr)
        return false;

    _outContext = _writeEpt->BeginDataXfer(downData, downLength, &_outOverlapped);
    _writeEpt->WaitForXfer(&_outOverlapped, 100);
    _writeEpt->FinishDataXfer(downData, downLength, &_outOverlapped, _outContext);

    _inContext = _readEpt->BeginDataXfer(upData, upLength, &_inOverlapped);
    _readEpt->WaitForXfer(&_inOverlapped, 100);
    _readEpt->FinishDataXfer(upData, upLength, &_inOverlapped, _inContext);
    return true;
}

bool CCyUSB::writeX(unsigned char *downData, long downLength, unsigned char *upData, long upLength)
{
    if (_readEpt == 0 || _writeEpt == 0)
        return false;

    _outContext = _writeEpt->BeginDataXfer(downData, downLength, &_outOverlapped);
    _writeEpt->WaitForXfer(&_outOverlapped, 100);
    if (!_writeEpt->FinishDataXfer(downData, downLength, &_outOverlapped, _outContext))
        return false;
    _inContext = _readEpt->BeginDataXfer(upData, upLength, &_inOverlapped);
    return true;
}

bool CCyUSB::readX(unsigned char* data, long length)
{
    //_readEpt->WaitForXfer(&_inOverlapped, 100);
    return _readEpt->FinishDataXfer(data, length, &_inOverlapped, _inContext);
}

bool CCyUSB::isReadyX()
{
    //return WaitForSingleObject(_inOverlapped.hEvent, 0)== WAIT_OBJECT_0;
    return _readEpt->WaitForXfer(&_inOverlapped, 0);
}
#endif
