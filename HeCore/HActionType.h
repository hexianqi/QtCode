/***************************************************************************************************
**      2018-06-19  HActionType 动作类型。
***************************************************************************************************/

#ifndef HACTIONTYPE_H
#define HACTIONTYPE_H

#include "HCoreGlobal.h"

HE_CORE_BEGIN_NAMESPACE

using HActionType = long long;

#define     ACT_IDLE                                0x00000000
#define     ACT_EXIT                                0x00000001
#define     ACT_UNLOCK_DEVICE                       0x00000011
#define     ACT_CHECK_DEVICE                        0x00000080

#define     ACT_SET_INTEGRAL_TIME                   0x00010101
#define     ACT_SET_SPECTRUM_AVG_TIMES              0x00010102
#define     ACT_SET_SPECTRUM_SAMPLE_DELAY           0x00010103
#define     ACT_GET_INTEGRAL_TIME                   0x00010181
#define     ACT_GET_SPECTRUM                        0x00010182

#define     ACT_RESET_SPECTRUM                      0xF0000001

////#define     ACT_REFRESH_USE_TIME                    0x00000012

//#define     ACT_SET_ELEC_MODULE                     0x00000101
//#define     ACT_SET_SOURCE_MODE                     0x00000102
//#define     ACT_SET_SOURCE_VOLTAGE                  0x00000103
//#define     ACT_SET_FORWARD_CURRENT_GEARS           0x00000104
//#define     ACT_SET_FORWARD_CURRENT                 0x00000105
//#define     ACT_SET_REVERSE_VOLTAGE                 0x00000106
//#define     ACT_SET_FORWARD_CURRENT2                0x00000111
//#define     ACT_SET_FORWARD_CURRENT_CODE1           0x00000112
//#define     ACT_SET_FORWARD_CURRENT_CODE2           0x00000113
//#define     ACT_SET_ELEC_CODE                       0x00000107
//#define     ACT_GET_ELEC                            0x00000181
//#define     ACT_GET_FORWARD_VOLTAGE                 0x00000182
//#define     ACT_GET_REVERSE_CURRENT                 0x00000183
//#define     ACT_GET_FEEDBACK_CURRENT                0x00000184

//#define     ACT_SET_LUMINOUS_MODULE                 0x00000201
//#define     ACT_SET_LUMINOUS_TYPE                   0x00000202
//#define     ACT_SET_LUMINOUS_GEARS                  0x00000203
//#define     ACT_GET_LUMINOUS                        0x00000281
//#define     ACT_GET_ANGULAR_DISTRIBUTION            0x000002C1



//#define     ACT_RESET_MOTOR                         0x00001101

//////#define     ACT_SET_MOTOR_MODULE                    0x00000401
//////#define     ACT_SET_MOTOR_DIRECTION                 0x00000402
//////#define     ACT_SET_MOTOR_STEP                      0x00000403


//////#define     ACT_GET_LAMPS_ELEC                      0x00008081

//////#define     ACT_SET_TEMPERATURE_MODULE              0x00008201
//////#define     ACT_SET_TEMPERATURE_TYPE                0x00008202
//////#define     ACT_SET_TEMPERATURE_GEARS               0x00008203
//////#define     ACT_SET_TEMPERATURE_CALIBRATE           0x00008204
//////#define     ACT_GET_TEMPERATURE                     0x00008281
//////#define     ACT_GET_TEMPERATURE_CALIBRATE           0x00008284

////
//////#define     ACT_SEND_DATA                           0x00010111

//////#define     ACT_RECEIVE_DATA                        0x00010191

//#define     ACT_RESET_STATE_TRIGGER                 0x00010101
//#define     ACT_QUERY_STATE_TRIGGER                 0x00010181

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


//#define     ACT_RESET_GRADE                         0xF0000001
//
//#define     ACT_RESET_JUDGMENT                      0xF0000003
//#define     ACT_RESET_CIRCUIT                       0xF0000004

HE_CORE_END_NAMESPACE

#endif // HACTIONTYPE_H
