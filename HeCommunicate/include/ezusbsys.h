#ifndef _EZUSBSYS_H
#define _EZUSBSYS_H
#if __GNUC__ >=3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define EZUSB_IOCTL_INDEX  0x0800
#define IOCTL_EZUSB_GET_PIPE_INFO                   CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_GET_DEVICE_DESCRIPTOR           CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0801, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_GET_CONFIGURATION_DESCRIPTOR    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0802, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_BULK_OR_INTERRUPT_WRITE         CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0803, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_BULK_OR_INTERRUPT_READ          CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0804, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_VENDOR_REQUEST                  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0805, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_GET_CURRENT_CONFIG              CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0806, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_ANCHOR_DOWNLOAD                 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0807, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_RESET                           CTL_CODE(FILE_DEVICE_UNKNOWN, 0x080C, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_RESETPIPE                       CTL_CODE(FILE_DEVICE_UNKNOWN, 0x080D, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_ABORTPIPE                       CTL_CODE(FILE_DEVICE_UNKNOWN, 0x080F, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_SETINTERFACE                    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0810, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_GET_STRING_DESCRIPTOR           CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0811, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_BULK_READ                       CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0813, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_BULK_WRITE                      CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0814, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_GET_CURRENT_FRAME_NUMBER        CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0815, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_VENDOR_OR_CLASS_REQUEST         CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0816, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_GET_LAST_ERROR                  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0817, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_ISO_READ                        CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0819, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_ISO_WRITE                       CTL_CODE(FILE_DEVICE_UNKNOWN, 0x081A, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
//#define IOCTL_EZUSB_ANCHOR_DOWNLOAD                 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x081B, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_GET_DRIVER_VERSION              CTL_CODE(FILE_DEVICE_UNKNOWN, 0x081D, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_START_ISO_STREAM                CTL_CODE(FILE_DEVICE_UNKNOWN, 0x081E, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_STOP_ISO_STREAM                 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x081F, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_READ_ISO_BUFFER                 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0820, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_EZUSB_SET_FEATURE                     CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0821, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define MAX_DRIVER_NAME         64
#define DEVICE_DESCRIPTOR_SIZE  32
#define MAX_ITEMS_IN_LB         256
#define MAX_BUFFER_SIZE         512

enum UsbPipeTypes
{
    UPT_Control,
    UPT_Isochronous,
    UPT_Bulk,
    UPT_Interrupt
};

struct UsbPipeInfo
{
    unsigned short  nMaximumPacketSize;     // Maximum packet size for this pipe
    unsigned char   cEndpointAddress;       // 8 bit USB endpoint address (includes direction) taken from endpoint descriptor
    unsigned char   cInterval;              // Polling interval in ms if interrupt pipe
    UsbPipeTypes    pipeType;               // PipeType identifies type of transfer valid for this pipe
    void *          pHandle;
    unsigned long   nMaximumTransferSize;   // Maximum size for a single request in bytes.
    unsigned long   nPipeFlags;
};

struct UsbInterfaceInfo
{
    unsigned short  nLength;
    unsigned char   cInterfaceNumber;
    unsigned char   cAlternateSetting;
    unsigned char   cClass;
    unsigned char   cSubClass;
    unsigned char   cProtocol;
    unsigned char   cReserved;
    void *          pHandle;
    unsigned long   nNumberOfPipes;
    UsbPipeInfo     Pipes[1];
};

#ifdef __cplusplus
}
#endif
#endif
