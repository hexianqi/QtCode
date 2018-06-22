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
    E_THREAD_NO_HANDLE              = 0X0401,

//    E_PROTOCOL_STRATEGY_ERROR,
//    E_DEVICE_MAPPED_NO_KEY,
//    E_MODEL_NO_PROTOCOL_STRATEGY,
//    E_PORT_CHECKCODE_ERROR,
//    E_PORT_RETURN_DATA_ERROR,
//    E_RETURN_STATUS_OK              = 0x0200,
//    E_RETURN_STATUS_FORMAT_ERROR,
//    E_RETURN_STATUS_MODULE_NORESPONSE,
//    E_RETURN_STATUS_OVERFLOW,
//    E_RETURN_STATUS_BUSY,
//    E_RETURN_STATUS_CHIP_NORESPONSE,
//    E_RETURN_STATUS_COMMAND_ERROR,
//
//    E_DEVICE_LOCKED                 = 0x1002,
//    E_DEVICE_UNMATCH                = 0x1011,
//    E_DEVICE_UNMATCH_ID,
//    E_DEVICE_UNMATCH_VERSION,
//    E_DEVICE_MODULE_ERROR           = 0x1101,
//    E_DEVICE_MAPPED_ERROR           = 0x1201,
//    E_DEVICE_MAPPED_NO_KEY,

//    E_PROCESS_NO_FOUND              = 0x2101,
//    E_PROCESS_NO_ACT,
//    E_SEND_WRONG_DATA               = 0x3001,
//    E_FILE_UNMATCH                  = 0x4001
};

HE_CORE_END_NAMESPACE

#endif // HERRORTYPE_H
