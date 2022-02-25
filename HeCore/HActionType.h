/***************************************************************************************************
**      2018-06-19  HActionType 动作类型。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"

HE_BEGIN_NAMESPACE

using HActionType = long long;

#define     ACT_IDLE                                0x00000000
#define     ACT_EXIT                                0x00000001
#define     ACT_CHECK_DEVICE                        0x00000011
#define     ACT_UNLOCK_DEVICE                       0x00000012

#define     ACT_SET_INTEGRAL_TIME                   0x00010101
#define     ACT_SET_SPECTRUM_AVG_TIMES              0x00010102
#define     ACT_SET_SPECTRUM_SAMPLE_DELAY           0x00010103
#define     ACT_SET_RAM                             0x00010104
#define     ACT_SET_DATA                            0x00010105
#define     ACT_GET_INTEGRAL_TIME                   0x00010111
#define     ACT_GET_SPECTRUM                        0x00010112
#define     ACT_GET_SPECTRUM_ENERGY                 0x00010113
#define     ACT_GET_RAM                             0x00010114

#define     ACT_SET_OUTPUT_VOLTAGE                  0x00020101
#define     ACT_SET_OUTPUT_CURRENT                  0x00020102
#define     ACT_SET_OVER_VOLTAGE                    0x00020103
#define     ACT_SET_OVER_CURRENT                    0x00020104
#define     ACT_SET_SOURCE_MODE                     0x00020105
#define     ACT_SET_SOURCE_ADDR                     0x00020106
#define     ACT_SET_SOURCE_OPERATION                0x00020107
#define     ACT_SET_SOURCE_FORWARD                  0x00020108
#define     ACT_SET_SOURCE_REVERSE                  0x00020109
#define     ACT_SET_SOURCE_IO                       0x0002010A
#define     ACT_GET_SOURCE_STATE                    0x00020111
#define     ACT_GET_ELEC_DATA                       0x00020112

#define     ACT_SET_ELEC_MODULE                     0x00020201
#define     ACT_SET_GEARS_OUTPUT_VOLTAGE            0x00020202
#define     ACT_SET_GEARS_OUTPUT_CURRENT            0x00020203
#define     ACT_SET_GEARS_MEASURED_VOLTAGE          0x00020204
#define     ACT_SET_GEARS_MEASURED_CURRENT          0x00020205
#define     ACT_SET_GEARS_REVERSE_VOLTAGE           0x00020206
#define     ACT_SET_GEARS_REVERSE_CURRENT           0x00020207
#define     ACT_SET_REVERSE_VOLTAGE                 0x00020208
#define     ACT_GET_MEASURED_VOLTAGE                0x00020211
#define     ACT_GET_MEASURED_CURRENT                0x00020212
#define     ACT_GET_REVERSE_CURRENT                 0x00020213

#define     ACT_SET_LUMINOUS_MODULE                 0x00020301
#define     ACT_SET_LUMINOUS_TYPE                   0x00020302
#define     ACT_SET_LUMINOUS_GEARS                  0x00020303
#define     ACT_GET_LUMINOUS_DATA                   0x00020311

#define     ACT_RESET_STATE_TRIGGER                 0x00030101
#define     ACT_QUERY_STATE_TRIGGER                 0x00030111

#define     ACT_SET_MOTOR_LOCATION                  0x00030201
#define     ACT_RESET_MOTOR_LOCATION                0x00030202
#define     ACT_RESET_MOTOR_STATE                   0x00030203
#define     ACT_QUERY_MOTOR_STATE                   0x00030211

#define     ACT_SINGLE_TEST                         0x10000001
#define     ACT_GET_SPECTRUM_ELEC                   0x10000002

#define     ACT_QUERY_NEXT_TEST                     0xE0000001

#define     ACT_RESET_SPECTRUM                      0xF0000001
#define     ACT_RESET_LUMINOUS                      0xF0000002
#define     ACT_RESET_CHROMATISM                    0xF0000003
#define     ACT_RESET_ELEC                          0xF0000004
#define     ACT_RESET_GRADE                         0xF0000011
#define     ACT_RESET_ADJUST                        0xF0000012
#define     ACT_RESET_QUALITY                       0xF0000013
#define     ACT_RESET_LOCATION                      0xF0000014

//#define     ACT_REFRESH_USE_TIME                    0x00000012

//#define     ACT_GET_ANGULAR_DISTRIBUTION            0x000002C1

//#define     ACT_RESET_MOTOR                         0x00001101

//#define     ACT_SET_MOTOR_MODULE                    0x00000401
//#define     ACT_SET_MOTOR_DIRECTION                 0x00000402
//#define     ACT_SET_MOTOR_STEP                      0x00000403


//#define     ACT_GET_LAMPS_ELEC                      0x00008081

//#define     ACT_SET_TEMPERATURE_MODULE              0x00008201
//#define     ACT_SET_TEMPERATURE_TYPE                0x00008202
//#define     ACT_SET_TEMPERATURE_GEARS               0x00008203
//#define     ACT_SET_TEMPERATURE_CALIBRATE           0x00008204
//#define     ACT_GET_TEMPERATURE                     0x00008281
//#define     ACT_GET_TEMPERATURE_CALIBRATE           0x00008284

//#define     ACT_SEND_DATA                           0x00010111
//#define     ACT_RECEIVE_DATA                        0x00010191

//#define     ACT_SET_LED_NUM                         0x00010201
//#define     ACT_SET_LED_ADDRESS                     0x00010202

////#define     ACT_PLC_RESET_MOTOR                     0x00010301
////#define     ACT_PLC_SEND_DATA                       0x00010302
////#define     ACT_PLC_FLUSH_DELAY                     0x00010303
////#define     ACT_PLC_GET_FEEDBACK                    0x00010381
////#define     ACT_PLC_QUERY_STATE_TRIGGER             0x00010382
////#define     ACT_PLC_QUERY_STATE_MOTOR               0x00010383
////#define     ACT_PLC_QUERY_STATE_BLANKING            0x00010384

//////#define     ACT_COB_SET_CYLINDER                    0x00010401
//////#define     ACT_COB_SET_MOTOR_MODE                  0x00010411
//////#define     ACT_COB_SET_MOTOR_DATA                  0x00010412
//////#define     ACT_COB_RESET_MOTOR_POSITION            0x00010413
//////#define     ACT_COB_SET_MOTOR_POSITION              0x00010414
//////#define     ACT_COB_RESET_MOTOR_STEP                0x00010415
//////#define     ACT_COB_SET_MOTOR_STEP                  0x00010416
//////#define     ACT_COB_QUERY_STATE                     0x00010481

//#define     ACT_PULSE_TEST                          0x0F000181
//#define     ACT_GET_ELEC_LUMINOUS_SPECTRUM          0x0F000182
//#define     ACT_GET_LUMINOUS_SPECTRUM               0x0F000183

//////#define     ACT_SET_MOTOR_ANGULAR                   0x0F000201

//#define     ACT_RESET_JUDGMENT                      0xF0000003
//#define     ACT_RESET_CIRCUIT                       0xF0000004

HE_END_NAMESPACE
