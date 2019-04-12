/***************************************************************************************************
**      2018-06-19  HErrorType 错误类型。
***************************************************************************************************/

#ifndef HERRORTYPE_H
#define HERRORTYPE_H

#include "HCoreGlobal.h"

HE_CORE_BEGIN_NAMESPACE

enum HErrorType
{
    E_OK                            = 0x0000,
    E_PORT_INVALID                  = 0x0101,
    E_PORT_NO_DLL,
    E_PORT_INVALID_HANDLE,
    E_PORT_OPENED,
    E_PORT_CLOSED,
    E_PORT_WRITE_DATA_LESS,
    E_PORT_WRITE_FAILED,
    E_PORT_READ_DATA_LESS,
    E_PORT_READ_FAILED,
    E_DEVICE_INVALID                = 0x0201,
    E_DEVICE_NO_FOUND,
    E_DEVICE_ACTION_ERROR,
    E_DEVICE_CHECKCODE_ERROR,
    E_DEVICE_RETURN_DATA_ERROR,
    E_DEVICE_FEEDBACK_OK,
    E_DEVICE_FEEDBACK_FORMAT_ERROR,
    E_DEVICE_FEEDBACK_MODULE_NORESPONSE,
    E_DEVICE_FEEDBACK_OVERFLOW,
    E_DEVICE_FEEDBACK_BUSY,
    E_DEVICE_FEEDBACK_CHIP_NORESPONSE,
    E_DEVICE_FEEDBACK_COMMAND_ERROR,
    E_PROTOCOL_INVALID              = 0x0301,
    E_THREAD_NO_HANDLE              = 0x0401,
};

HE_CORE_END_NAMESPACE

#endif // HERRORTYPE_H
