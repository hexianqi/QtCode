#include "HAppContext_p.h"
#include "HCore.h"
#include "HDataFormatInfo.h"
#include <QVariant>
#include <QPointF>
#include <QDateTime>
#include <QCoreApplication>
#include <QSettings>
#include <QFile>
#include <QSet>
#include <QTextStream>

HE_CORE_BEGIN_NAMESPACE

QHash<HActionType, QString>         hashActionComment;
QHash<HErrorType, QString>          hashErrorComment;
QHash<QString, HDataFormatInfo*>    hashDataFormatInfo;
QHash<QString, QString>             hashDataCaption;
QHash<QString, QSet<QString>>       hashMimeType;

//std::shared_ptr<HAppContext> hApp = std::shared_ptr<HAppContext>(HAppContext::instance());

QString toComment(HActionType type)
{
    return hashActionComment.value(type);
}

QString toComment(HErrorType type)
{
    return hashErrorComment.value(type);
}

HDataFormatInfo *toFormatInfo(QString type)
{
    if (!hashDataFormatInfo.contains(type))
        return new HDataFormatInfo();
    return hashDataFormatInfo.value(type);
}

QString toString(QString type, double value, char f)
{
    auto info = toFormatInfo(type);
    return QString().setNum(value, f, info->decimals());
}

QString toString(QString type, QVariant value)
{
    QString str;
    if (value.type() == QVariant::PointF)
        str = QString("(%1, %2)").arg(toString(type, value.toPointF().x())).arg(toString(type, value.toPointF().y()));
    if (value.type() == QVariant::Point)
        str = QString("(%1, %2)").arg(toString(type, value.toPoint().x())).arg(toString(type, value.toPoint().y()));
    if (value.type() == QVariant::Double)
        str = toString(type, value.toDouble());
    if (value.type() == QVariant::Int)
        str = toString(type, value.toInt());
    if (value.type() == QVariant::LongLong)
        str = toString(type, value.toLongLong());
    if (value.type() == QVariant::String)
        str = value.toString();
    if (value.type() == QVariant::DateTime)
        str = value.toDateTime().toString("yyyy-MM-dd hh:mm:ss");
    if (value.type() == QVariant::Date)
        str = value.toDate().toString("yyyy-MM-dd");
    if (value.type() == QVariant::Time)
        str = value.toTime().toString("hh:mm:ss");
    return str;
}

QString toUnit(QString type)
{
    return toFormatInfo(type)->unit(false);
}

QString toCaption(QString type)
{
    return hashDataCaption.value(type, type.mid(1, type.size()-2));
}

QStringList toCaption(QStringList types)
{
    QStringList list;
    for (auto type : types)
        list << toCaption(type);
    return list;
}

QString toCaptionUnit(QString type)
{
    auto caption = toCaption(type);
    auto unit = toUnit(type);
    if (!unit.isEmpty())
        caption += "(" + unit + ")";
    return caption;
}

QStringList toCaptionUnit(QStringList types)
{
    QStringList list;
    for (auto type : types)
        list << toCaptionUnit(type);
    return list;
}

QString filenameFilter(const QString &name, const QList<QByteArray> formats)
{
    QStringList list;

    for (auto ba : formats)
        list += ba;
    if (list.isEmpty())
        list << "*";
    else
        list.sort();
    return QString("%1 (*.").arg(name) + list.join(" *.") + ")";
}

QString filenameFilter(const QString &name, const QStringList &mimeTypes)
{
    QSet<QString> formats;
    QStringList list;

    for (auto mimeType : mimeTypes)
        formats.unite(hashMimeType.value(mimeType));
    list = QStringList::fromSet(formats);
    if (list.isEmpty())
        list << "*";
    else
        list.sort();
    return QString("%1 (*.").arg(name) + list.join(" *.") + ")";
}

HAppContext::HAppContext()
    : d_ptr(new HAppContextPrivate)
{
    QCoreApplication::addLibraryPath("./plugins");
    qRegisterMetaType<HErrorType>("HErrorType");
    qRegisterMetaType<HActionType>("HActionType");
    initActionComment();
    initErrorComment();
    initDataFormatInfo();
    initDataCaption();
    readMimeType();
    setSetting("Ini\\Settings.ini");
}

HAppContext::HAppContext(HAppContextPrivate &p)
    : d_ptr(&p)
{
    // 可能需要同样的初始化
}

HAppContext::~HAppContext()
{
}

std::shared_ptr<QSettings> HAppContext::createSettings()
{
    auto fileName = getContextValue<QString>("SettingsFileName");
    return std::make_shared<QSettings>(fileName, QSettings::IniFormat);
}

void HAppContext::setSetting(QString fileName)
{
    setContextValue("SettingsFileName", fileName);
}

template<class T>
T HAppContext::getContextValue(QString key)
{
    Q_D(HAppContext);
    if (!d->contextValue.contains(key))
        return T();
    return d->contextValue[key].value<T>();
}

template<class T>
T HAppContext::getContextPointer(QString key)
{
    Q_D(HAppContext);
    if (!d->contextPointer.contains(key))
        return nullptr;
    return dynamic_cast<T>(d->contextPointer[key]);
}

void HAppContext::setContextValue(QString key, QVariant value)
{
    Q_D(HAppContext);
    d->contextValue[key] = value;
}

void HAppContext::setContextPointer(QString key, QObject *value)
{
    Q_D(HAppContext);
    d->contextPointer[key] = value;
}

void HAppContext::initActionComment()
{
    hashActionComment.clear();
    hashActionComment.insert(ACT_IDLE,                          tr("空闲"));
    hashActionComment.insert(ACT_EXIT,                          tr("退出"));
    hashActionComment.insert(ACT_UNLOCK_DEVICE,                 tr("设备解锁"));
    hashActionComment.insert(ACT_CHECK_DEVICE,                  tr("检查设备"));
//    hashActionComment.insert(ACT_REFRESH_USE_TIME,             QStringList() << tr("ACT_REFRESH_USE_TIME") << tr("刷新设备使用时间"));

//    hashActionComment.insert(ACT_SET_ELEC_MODULE,                QStringList() << tr("ACT_SET_ELEC_MODULE") << tr("设置电学参数模块"));
//    hashActionComment.insert(ACT_SET_SOURCE_MODE,                QStringList() << tr("ACT_SET_SOURCE_MODE") << tr("设置电源模式"));
//    hashActionComment.insert(ACT_SET_SOURCE_VOLTAGE,             QStringList() << tr("ACT_SET_SOURCE_VOLTAGE") << tr("设置电源电压"));
//    hashActionComment.insert(ACT_SET_FORWARD_CURRENT_GEARS,      QStringList() << tr("ACT_SET_FORWARD_CURRENT_GEARS") << tr("设置电流档位"));
//    hashActionComment.insert(ACT_SET_FORWARD_CURRENT,            QStringList() << tr("ACT_SET_FORWARD_CURRENT") << tr("设置正向电流"));
//    hashActionComment.insert(ACT_SET_REVERSE_VOLTAGE,            QStringList() << tr("ACT_SET_REVERSE_VOLTAGE") << tr("设置反向电压"));
//    hashActionComment.insert(ACT_SET_FORWARD_CURRENT2,           QStringList() << tr("ACT_SET_FORWARD_CURRENT2") << tr("设置正向电流"));
//    hashActionComment.insert(ACT_SET_FORWARD_CURRENT_CODE1,      QStringList() << tr("ACT_SET_FORWARD_CURRENT_CODE1") << tr("设置正向电流"));
//    hashActionComment.insert(ACT_SET_FORWARD_CURRENT_CODE2,      QStringList() << tr("ACT_SET_FORWARD_CURRENT_CODE2") << tr("设置正向电流"));
//    hashActionComment.insert(ACT_SET_ELEC_CODE,                  QStringList() << tr("ACT_SET_ELEC_CODE") << tr("设置开关编码"));
//    hashActionComment.insert(ACT_GET_ELEC,                       QStringList() << tr("ACT_GET_ELEC") << tr("获取电参数"));
//    hashActionComment.insert(ACT_GET_FORWARD_VOLTAGE,            QStringList() << tr("ACT_GET_FORWARD_VOLTAGE") << tr("获取正向电压"));
//    hashActionComment.insert(ACT_GET_REVERSE_CURRENT,            QStringList() << tr("ACT_GET_REVERSE_CURRENT") << tr("获取反向漏流"));
//    hashActionComment.insert(ACT_GET_FEEDBACK_CURRENT,           QStringList() << tr("ACT_GET_FEEDBACK_CURRENT") << tr("获取回溯电流"));

//    hashActionComment.insert(ACT_SET_LUMINOUS_MODULE,            QStringList() << tr("ACT_SET_LUMINOUS_MODULE") << tr("设置光度参数模块"));
//    hashActionComment.insert(ACT_SET_LUMINOUS_TYPE,              QStringList() << tr("ACT_SET_LUMINOUS_TYPE") << tr("设置光度类型"));
//    hashActionComment.insert(ACT_SET_LUMINOUS_GEARS,             QStringList() << tr("ACT_SET_LUMINOUS_GEARS") << tr("设置光度档位"));
//    hashActionComment.insert(ACT_GET_LUMINOUS,                   QStringList() << tr("ACT_GET_LUMINOUS") << tr("获取光度数据"));
//    hashActionComment.insert(ACT_GET_ANGULAR_DISTRIBUTION,       QStringList() << tr("ACT_GET_ANGULAR_DISTRIBUTION") << tr("获取角度分布数据"));

//    hashActionComment.insert(ACT_SET_INTEGRAL_TIME,              QStringList() << tr("ACT_SET_INTEGRAL_TIME") << tr("设置积分时间"));
//    hashActionComment.insert(ACT_SET_MACHINE_AVG_TIMES,          QStringList() << tr("ACT_SET_MACHINE_AVG_TIMES") << tr("设置光谱下位机平均次数"));
//    hashActionComment.insert(ACT_SET_SPECTRUM_SAMPLE_DELAY,      QStringList() << tr("ACT_SET_SPECTRUM_SAMPLE_DELAY") << tr("设置光谱采样延时"));
//    hashActionComment.insert(ACT_GET_INTEGRAL_TIME,              QStringList() << tr("ACT_GET_INTEGRAL_TIME") << tr("获取积分时间"));
//    hashActionComment.insert(ACT_GET_SPECTRUM,                   QStringList() << tr("ACT_GET_SPECTRUM") << tr("获取光谱数据"));

//    hashActionComment.insert(ACT_RESET_MOTOR,                    QStringList() << tr("ACT_RESET_MOTOR") << tr("电机复位"));

//    hashActionComment.insert(ACT_RESET_STATE_TRIGGER,            QStringList() << tr("ACT_RESET_STATE_TRIGGER") << tr("复位触发状态"));
//    hashActionComment.insert(ACT_QUERY_STATE_TRIGGER,            QStringList() << tr("ACT_QUERY_STATE_TRIGGER") << tr("查询触发状态"));

//    hashActionComment.insert(ACT_SET_LED_NUM,                    QStringList() << tr("ACT_SET_LED_NUM") << tr("设置LED编号"));
//    hashActionComment.insert(ACT_SET_LED_ADDRESS,                QStringList() << tr("ACT_SET_LED_ADDRESS") << tr("设置LED地址"));

////    hashActionComment.insert(ACT_SET_MOTOR_MODULE,           QStringList() << tr("ACT_SET_MOTOR_MODULE") << tr("设置电机模块"));
////    hashActionComment.insert(ACT_SET_MOTOR_DIRECTION,        QStringList() << tr("ACT_SET_MOTOR_DIRECTION") << tr("设置电机走步方向"));
////    hashActionComment.insert(ACT_SET_MOTOR_STEP,             QStringList() << tr("ACT_SET_MOTOR_STEP") << tr("设置电机走步"));

////    hashActionComment.insert(ACT_SET_TEMPERATURE_MODULE,     QStringList() << tr("ACT_SET_TEMPERATURE_MODULE") << tr("设置温度模块"));
////    hashActionComment.insert(ACT_SET_TEMPERATURE_TYPE,       QStringList() << tr("ACT_SET_TEMPERATURE_TYPE") << tr("设置温度类型"));
////    hashActionComment.insert(ACT_SET_TEMPERATURE_GEARS,      QStringList() << tr("ACT_SET_TEMPERATURE_GEARS") << tr("设置温度档位"));
////    hashActionComment.insert(ACT_SET_TEMPERATURE_CALIBRATE,  QStringList() << tr("ACT_SET_TEMPERATURE_CALIBRATE") << tr("设置温度校准数据"));
////    hashActionComment.insert(ACT_GET_TEMPERATURE,            QStringList() << tr("ACT_GET_TEMPERATURE") << tr("获取温度"));
////    hashActionComment.insert(ACT_GET_TEMPERATURE_CALIBRATE,  QStringList() << tr("ACT_GET_TEMPERATURE_CALIBRATE") << tr("获取温度校准数据"));

////    hashActionComment.insert(ACT_GET_LAMPS_ELEC,             QStringList() << tr("ACT_GET_LAMPS_ELEC") << tr("获取灯具电量参数"));



////    hashActionComment.insert(ACT_PLC_RESET_MOTOR,            QStringList() << tr("ACT_PLC_RESET_MOTOR") << tr("电机复位"));
////    hashActionComment.insert(ACT_PLC_SEND_DATA,              QStringList() << tr("ACT_PLC_SEND_DATA") << tr("发送数据"));
////    hashActionComment.insert(ACT_PLC_FLUSH_DELAY,            QStringList() << tr("ACT_PLC_FLUSH_DELAY") << tr("设置吹气延时"));
////    hashActionComment.insert(ACT_PLC_GET_FEEDBACK,           QStringList() << tr("ACT_PLC_GET_FEEDBACK") << tr("获取回溯数据"));
////    hashActionComment.insert(ACT_PLC_QUERY_STATE_TRIGGER,    QStringList() << tr("ACT_PLC_QUERY_STATE_TRIGGER") << tr("查询触发状态"));
////    hashActionComment.insert(ACT_PLC_QUERY_STATE_MOTOR,      QStringList() << tr("ACT_PLC_QUERY_STATE_MOTOR") << tr("查询电机状态"));
////    hashActionComment.insert(ACT_PLC_QUERY_STATE_BLANKING,   QStringList() << tr("ACT_PLC_QUERY_STATE_BLANKING") << tr("查询落料状态"));

////    hashActionComment.insert(ACT_COB_SET_CYLINDER,           QStringList() << tr("ACT_COB_SET_CYLINDER") << tr("气缸控制"));
////    hashActionComment.insert(ACT_COB_SET_MOTOR_MODE,         QStringList() << tr("ACT_COB_SET_MOTOR_MODE") << tr("设置电机模式"));
////    hashActionComment.insert(ACT_COB_SET_MOTOR_DATA,         QStringList() << tr("ACT_COB_SET_MOTOR_DATA") << tr("设置电机数据"));
////    hashActionComment.insert(ACT_COB_RESET_MOTOR_POSITION,   QStringList() << tr("ACT_COB_RESET_MOTOR_POSITION") << tr("电机复位"));
////    hashActionComment.insert(ACT_COB_SET_MOTOR_POSITION,     QStringList() << tr("ACT_COB_SET_MOTOR_POSITION") << tr("电机移动"));
////    hashActionComment.insert(ACT_COB_RESET_MOTOR_STEP,       QStringList() << tr("ACT_COB_RESET_MOTOR_STEP") << tr("电机复位"));
////    hashActionComment.insert(ACT_COB_SET_MOTOR_STEP,         QStringList() << tr("ACT_COB_SET_MOTOR_STEP") << tr("电机移动"));
////    hashActionComment.insert(ACT_COB_QUERY_STATE,            QStringList() << tr("ACT_COB_QUERY_STATE") << tr("查询状态"));

////
////    hashActionComment.insert(ACT_SET_MOTOR_ANGULAR,          QStringList() << tr("ACT_SET_MOTOR_ANGULAR") << tr("设置电机角度"));

//    hashActionComment.insert(ACT_PULSE_TEST,                     QStringList() << tr("ACT_PULSE_TEST") << tr("快速测试"));
//    hashActionComment.insert(ACT_GET_ELEC_LUMINOUS_SPECTRUM,     QStringList() << tr("ACT_GET_ELEC_LUMINOUS_SPECTRUM") << tr("获取光色电数据"));
//    hashActionComment.insert(ACT_GET_LUMINOUS_SPECTRUM,          QStringList() << tr("ACT_GET_LUMINOUS_SPECTRUM") << tr("获取光色数据"));

//    hashActionComment.insert(ACT_RESET_GRADE,                    QStringList() << tr("ACT_RESET_GRADE") << tr("重新设置分级"));
//    hashActionComment.insert(ACT_RESET_SPECTRUM,                 QStringList() << tr("ACT_RESET_SPECTRUM") << tr("重新设置光谱波长范围"));
//    hashActionComment.insert(ACT_RESET_JUDGMENT,                 QStringList() << tr("ACT_RESET_JUDGMENT") << tr("重新设置合格判定"));
//    hashActionComment.insert(ACT_RESET_CIRCUIT,                  QStringList() << tr("ACT_RESET_CIRCUIT") << tr("重新设置线路配置"));
}

void HAppContext::initErrorComment()
{
    hashErrorComment.clear();
    hashErrorComment.insert(E_OK,                               tr("成功"));
    hashErrorComment.insert(E_PORT_INVALID,                     tr("端口无效"));
    hashErrorComment.insert(E_PORT_NO_DLL,                      tr("找不到驱动"));
    hashErrorComment.insert(E_PORT_INVALID_HANDLE,              tr("端口句柄无效"));
    hashErrorComment.insert(E_PORT_OPENED,                      tr("端口已经打开"));
    hashErrorComment.insert(E_PORT_CLOSED,                      tr("端口已经关闭"));
    hashErrorComment.insert(E_PORT_WRITE_DATA_LESS,             tr("发送数据太少"));
    hashErrorComment.insert(E_PORT_WRITE_FAILED,                tr("发送数据失败"));
    hashErrorComment.insert(E_PORT_READ_DATA_LESS,              tr("接收数据太少"));
    hashErrorComment.insert(E_PORT_READ_FAILED,                 tr("接收数据失败"));
    hashErrorComment.insert(E_DEVICE_NO_FOUND,                  tr("找不到设备"));
    hashErrorComment.insert(E_DEVICE_CHECKCODE_ERROR,           tr("设备校验码错误"));
    hashErrorComment.insert(E_DEVICE_RETURN_DATA_ERROR,         tr("设备返回数据错误"));
    hashErrorComment.insert(E_DEVICE_FEEDBACK_OK,               tr("设备反馈 - 成功"));
    hashErrorComment.insert(E_DEVICE_FEEDBACK_FORMAT_ERROR,     tr("设备反馈 - 格式错误"));
    hashErrorComment.insert(E_DEVICE_FEEDBACK_MODULE_NORESPONSE,tr("设备反馈 - 模块无应答"));
    hashErrorComment.insert(E_DEVICE_FEEDBACK_OVERFLOW,         tr("设备反馈 - 数据溢出"));
    hashErrorComment.insert(E_DEVICE_FEEDBACK_BUSY,             tr("设备反馈 - 模块繁忙"));
    hashErrorComment.insert(E_DEVICE_FEEDBACK_CHIP_NORESPONSE,  tr("设备反馈 - 芯片无响应"));
    hashErrorComment.insert(E_DEVICE_FEEDBACK_COMMAND_ERROR,    tr("设备反馈 - 命令错误"));


    hashErrorComment.insert(E_PROTOCOL_INVALID,                 tr("通讯协议无效"));
    hashErrorComment.insert(E_PROTOCOL_STRATEGY_INVALID,        tr("通讯策略无效"));
    hashErrorComment.insert(E_PROTOCOL_STRATEGY_ERROR,          tr("通讯策略错误"));
    hashErrorComment.insert(E_MODEL_NO_PROTOCOL_STRATEGY,       tr("找不到通讯策略"));



//    hashErrorComment.insert(E_PORT_CHECKCODE_ERROR,             tr("校验码错误"));
//    hashErrorComment.insert(E_PORT_RETURN_DATA_ERROR,           tr("返回数据错误"));
//    hashErrorComment.insert(E_RETURN_STATUS_OK,                 tr("返回状态正确"));
//    hashErrorComment.insert(E_RETURN_STATUS_FORMAT_ERROR,       tr("返回状态错误"));
//    hashErrorComment.insert(E_RETURN_STATUS_MODULE_NORESPONSE,  tr("模块无应答"));
//    hashErrorComment.insert(E_RETURN_STATUS_OVERFLOW,           tr("数据溢出"));
//    hashErrorComment.insert(E_RETURN_STATUS_BUSY,               tr("模块繁忙"));
//    hashErrorComment.insert(E_RETURN_STATUS_CHIP_NORESPONSE,    tr("芯片无响应"));
//    hashErrorComment.insert(E_RETURN_STATUS_COMMAND_ERROR,      tr("命令错误"));

//    hashErrorComment.insert(E_DEVICE_LOCKED,                    tr("设备锁定"));
//    hashErrorComment.insert(E_DEVICE_UNMATCH,                   tr("设备不匹配"));
//    hashErrorComment.insert(E_DEVICE_UNMATCH_ID,                tr("设备识别码不匹配"));
//    hashErrorComment.insert(E_DEVICE_UNMATCH_VERSION,           tr("设备版本号不匹配"));
//    hashErrorComment.insert(E_DEVICE_MODULE_ERROR,              tr("设备模块异常"));
//    hashErrorComment.insert(E_DEVICE_MAPPED_ERROR,              tr("设备映射表异常"));
//    hashErrorComment.insert(E_DEVICE_MAPPED_NO_KEY,             tr("找不到对应的模块通道映射"));
//
//    hashErrorComment.insert(E_PROCESS_NO_FOUND,                 tr("找不到相应的进程"));
//    hashErrorComment.insert(E_PROCESS_NO_ACT,                   tr("找不到相应的动作处理"));
//    hashErrorComment.insert(E_SEND_WRONG_DATA,                  tr("发送错误数据"));
//    hashErrorComment.insert(E_FILE_UNMATCH,                     tr("文件不匹配"));
}

void HAppContext::initDataFormatInfo()
{
    hashDataFormatInfo.clear();
    hashDataFormatInfo.insert("",                               new HDataFormatInfo());
    hashDataFormatInfo.insert("[]",                             new HDataFormatInfo("[]"));
    hashDataFormatInfo.insert("[_Fi]",                          new HDataFormatInfo("[_Fi]", 0, 65535));
//    //电参数
//    hashFormatInfo.insert(tr("[电源电压_Fi]"),                     FTypeInfo(tr("[电源电压_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[反向电压_Fi]"),                     FTypeInfo(tr("[反向电压_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[正向电流_Fi]"),                     FTypeInfo(tr("[正向电流_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[正向电流_1_Fi]"),                   FTypeInfo(tr("[正向电流_1_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[正向电流_2_Fi]"),                   FTypeInfo(tr("[正向电流_2_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[正向电流_3_Fi]"),                   FTypeInfo(tr("[正向电流_3_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[正向电流_L2_1_Fi]"),                FTypeInfo(tr("[正向电流_L2_1_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[正向电流_L2_2_Fi]"),                FTypeInfo(tr("[正向电流_L2_2_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[正向电流_L2_3_Fi]"),                FTypeInfo(tr("[正向电流_L2_3_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[正向电流_L2_4_Fi]"),                FTypeInfo(tr("[正向电流_L2_4_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[正向电压_Fi]"),                     FTypeInfo(tr("[正向电压_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[反向漏流_Fi]"),                     FTypeInfo(tr("[反向漏流_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[回溯电流_Fi]"),                     FTypeInfo(tr("[回溯电流_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[回溯电流_1_Fi]"),                   FTypeInfo(tr("[回溯电流_1_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[回溯电流_2_Fi]"),                   FTypeInfo(tr("[回溯电流_2_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[回溯电流_3_Fi]"),                   FTypeInfo(tr("[回溯电流_1_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[电源电压_Re]"),                     FTypeInfo(tr("[电源电压_Re]"), tr("V"), 0, 400, 3));
//    hashFormatInfo.insert(tr("[反向电压_Re]"),                     FTypeInfo(tr("[反向电压_Re]"), tr("V"), 0, 400, 3));
//    hashFormatInfo.insert(tr("[正向电流_Re]"),                     FTypeInfo(tr("[正向电流_Re]"), tr("mA"), 0, 5000, 3));
//    hashFormatInfo.insert(tr("[正向电流_1_Re]"),                   FTypeInfo(tr("[正向电流_1_Re]"), tr("uA"), 0, 5000, 3));
//    hashFormatInfo.insert(tr("[正向电流_2_Re]"),                   FTypeInfo(tr("[正向电流_2_Re]"), tr("mA"), 0, 5000, 3));
//    hashFormatInfo.insert(tr("[正向电流_3_Re]"),                   FTypeInfo(tr("[正向电流_3_Re]"), tr("mA"), 0, 5000, 3));
//    hashFormatInfo.insert(tr("[正向电流_L2_1_Re]"),                FTypeInfo(tr("[正向电流_L2_1_Re]"), tr("mA"), 0, 5000, 3));
//    hashFormatInfo.insert(tr("[正向电流_L2_2_Re]"),                FTypeInfo(tr("[正向电流_L2_2_Re]"), tr("mA"), 0, 5000, 3));
//    hashFormatInfo.insert(tr("[正向电流_L2_3_Re]"),                FTypeInfo(tr("[正向电流_L2_3_Re]"), tr("mA"), 0, 5000, 3));
//    hashFormatInfo.insert(tr("[正向电流_L2_4_Re]"),                FTypeInfo(tr("[正向电流_L2_4_Re]"), tr("mA"), 0, 5000, 3));
//    hashFormatInfo.insert(tr("[正向电压_Re]"),                     FTypeInfo(tr("[正向电压_Re]"), tr("V"), 0, 400, 3));
//    hashFormatInfo.insert(tr("[反向漏流_Re]"),                     FTypeInfo(tr("[反向漏流_Re]"), tr("uA"),0, 500, 3));
//    hashFormatInfo.insert(tr("[回溯电流_Re]"),                     FTypeInfo(tr("[回溯电流_Re]"), tr("mA"), 0, 5000, 3));
//    hashFormatInfo.insert(tr("[回溯电流_1_Re]"),                   FTypeInfo(tr("[回溯电流_1_Re]"), tr("uA"), 0, 5000, 3));
//    hashFormatInfo.insert(tr("[回溯电流_2_Re]"),                   FTypeInfo(tr("[回溯电流_2_Re]"), tr("mA"), 0, 5000, 3));
//    hashFormatInfo.insert(tr("[回溯电流_3_Re]"),                   FTypeInfo(tr("[回溯电流_3_Re]"), tr("mA"), 0, 5000, 3));
//    hashFormatInfo.insert(tr("[电源电压]"),                        FTypeInfo(tr("[电源电压]"), tr("V"), 0, 400, 2));
//    hashFormatInfo.insert(tr("[反向电压]"),                        FTypeInfo(tr("[反向电压]"), tr("V"), 0, 400, 2));
//    hashFormatInfo.insert(tr("[正向电流]"),                        FTypeInfo(tr("[正向电流]"), tr("mA"), 0, 5000, 2));
//    hashFormatInfo.insert(tr("[正向电流_1]"),                      FTypeInfo(tr("[正向电流_1]"), tr("uA"), 0, 5000, 2));
//    hashFormatInfo.insert(tr("[正向电流_2]"),                      FTypeInfo(tr("[正向电流_2]"), tr("mA"), 0, 5000, 2));
//    hashFormatInfo.insert(tr("[正向电流_3]"),                      FTypeInfo(tr("[正向电流_3]"), tr("mA"), 0, 5000, 2));
//    hashFormatInfo.insert(tr("[正向电流_L2_1]"),                   FTypeInfo(tr("[正向电流_L2_1]"), tr("mA"), 0, 5000, 2));
//    hashFormatInfo.insert(tr("[正向电流_L2_2]"),                   FTypeInfo(tr("[正向电流_L2_2]"), tr("mA"), 0, 5000, 2));
//    hashFormatInfo.insert(tr("[正向电流_L2_3]"),                   FTypeInfo(tr("[正向电流_L2_3]"), tr("mA"), 0, 5000, 2));
//    hashFormatInfo.insert(tr("[正向电流_L2_4]"),                   FTypeInfo(tr("[正向电流_L2_4]"), tr("mA"), 0, 5000, 2));
//    hashFormatInfo.insert(tr("[正向电压]"),                        FTypeInfo(tr("[正向电压]"), tr("V"), 0, 400, 2));
//    hashFormatInfo.insert(tr("[反向漏流]"),                        FTypeInfo(tr("[反向漏流]"), tr("uA"),0, 500, 2));
//    hashFormatInfo.insert(tr("[回溯电流]"),                        FTypeInfo(tr("[回溯电流]"), tr("mA"), 0, 5000, 2));
//    hashFormatInfo.insert(tr("[回溯电流_1]"),                      FTypeInfo(tr("[回溯电流_1]"), tr("uA"), 0, 5000, 2));
//    hashFormatInfo.insert(tr("[回溯电流_2]"),                      FTypeInfo(tr("[回溯电流_2]"), tr("mA"), 0, 5000, 2));
//    hashFormatInfo.insert(tr("[回溯电流_3]"),                      FTypeInfo(tr("[回溯电流_3]"), tr("mA"), 0, 5000, 2));
//    hashFormatInfo.insert(tr("[电功率]"),                          FTypeInfo(tr("[电功率]"), tr("W"), 0, 500, 2));
//    hashFormatInfo.insert(tr("[电阻]"),                            FTypeInfo(tr("[电阻]"), tr("Ω"), 0, 10, 3));
//    //交流电参数
//    hashFormatInfo.insert(tr("[交流电压]"),                        FTypeInfo(tr("[交流电压]"), tr("V"), 0, 500, 2));
//    hashFormatInfo.insert(tr("[交流电流]"),                        FTypeInfo(tr("[交流电流]"), tr("A"), 0, 50, 3));
//    hashFormatInfo.insert(tr("[功率因数]"),                        FTypeInfo(tr("[功率因数]"), tr(""), 0, 1, 3));
//    //光度参数
//    hashFormatInfo.insert(tr("[光强度_Fi]"),                       FTypeInfo(tr("[光强度_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[光通量_Fi]"),                       FTypeInfo(tr("[光通量_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[光亮度_Fi]"),                       FTypeInfo(tr("[光亮度_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[光照度_Fi]"),                       FTypeInfo(tr("[光照度_Fi]"), 0, 65535));
//    hashFormatInfo.insert(tr("[光强度_Re]"),                       FTypeInfo(tr("[光强度_Re]"), tr("mcd"), 0, 99999, 3, 100));
//    hashFormatInfo.insert(tr("[光通量_Re]"),                       FTypeInfo(tr("[光通量_Re]"), tr("lm"), 0, 99999, 3, 100));
//    hashFormatInfo.insert(tr("[光亮度_Re]"),                       FTypeInfo(tr("[光亮度_Re]"), tr("cd/m<sup>2</sup>"), 0, 99999, 3, 100));
//    hashFormatInfo.insert(tr("[光照度_Re]"),                       FTypeInfo(tr("[光照度_Re]"), tr("lx"), 0, 99999, 3, 100));
//    hashFormatInfo.insert(tr("[光强度]"),                          FTypeInfo(tr("[光强度]"), tr("mcd"), 0, 99999, 2, 100));
//    hashFormatInfo.insert(tr("[光通量]"),                          FTypeInfo(tr("[光通量]"), tr("lm"), 0, 99999, 2, 100));
//    hashFormatInfo.insert(tr("[光亮度]"),                          FTypeInfo(tr("[光亮度]"), tr("cd/m<sup>2</sup>"), 0, 99999, 2, 100));
//    hashFormatInfo.insert(tr("[光照度]"),                          FTypeInfo(tr("[光照度]"), tr("lx"), 0, 99999, 2, 100));
//    hashFormatInfo.insert(tr("[光功率]"),                          FTypeInfo(tr("[光功率]"), tr("mW"), 0, 99999, 2, 100));
//    hashFormatInfo.insert(tr("[光效]"),                            FTypeInfo(tr("[光效]]"), tr("lm/W"), 0, 99999, 2, 100));
//    //光强角度分布参数
//    hashFormatInfo.insert(tr("[角度]"),                            FTypeInfo(tr("[角度]"), tr("°"), 0, 360, 1));
//    hashFormatInfo.insert(tr("[最大光强度]"),                      FTypeInfo(tr("[最大光强度]"), tr("mcd"), 0, 99999, 2, 100));
//    hashFormatInfo.insert(tr("[法相光强度]"),                      FTypeInfo(tr("[法相光强度]"), tr("mcd"), 0, 99999, 2, 100));
//    hashFormatInfo.insert(tr("[最大光强度角]"),                    FTypeInfo(tr("[最大光强度角]"), tr("°"), 0, 360, 1));
//    hashFormatInfo.insert(tr("[半光强度夹角]"),                    FTypeInfo(tr("[半光强度夹角]"), tr("°"), 0, 360, 1));
//    hashFormatInfo.insert(tr("[1/5光强度夹角]"),                   FTypeInfo(tr("[1/5光强度夹角]"), tr("°"), 0, 360, 1));
//    hashFormatInfo.insert(tr("[左半光强度角]"),                    FTypeInfo(tr("[左半光强度角]"), tr("°"), 0, 360, 1));
//    hashFormatInfo.insert(tr("[右半光强度角]"),                    FTypeInfo(tr("[右半光强度角]"), tr("°"), 0, 360, 1));
//    hashFormatInfo.insert(tr("[左1/5光强度角]"),                   FTypeInfo(tr("[左1/5光强度角]"), tr("°"), 0, 360, 1));
//    hashFormatInfo.insert(tr("[右1/5光强度角]"),                   FTypeInfo(tr("[右1/5光强度角]"), tr("°"), 0, 360, 1));
//    hashFormatInfo.insert(tr("[理论光通量]"),                      FTypeInfo(tr("[理论光通量]"), tr("lm"), 0, 99999, 2, 100));
//    //光谱测试参数
//    hashFormatInfo.insert(tr("[积分时间]"),                        FTypeInfo(tr("[积分时间]"), tr("ms"), 1, 5000, 1));
//    //光谱能量参数
//    hashFormatInfo.insert(tr("[波长]"),                            FTypeInfo(tr("[波长]"), tr("nm"), 300, 1100, 1));
//    hashFormatInfo.insert(tr("[峰值波长]"),                        FTypeInfo(tr("[峰值波长]"), tr("nm"), 300, 1100, 1));
//    hashFormatInfo.insert(tr("[峰值带宽]"),                        FTypeInfo(tr("[峰值带宽]"), tr("nm"), 300, 1100, 1));
//    hashFormatInfo.insert(tr("[主波长]"),                          FTypeInfo(tr("[主波长]"), tr("nm"), 360, 780, 1));
//    hashFormatInfo.insert(tr("[色纯度]"),                          FTypeInfo(tr("[色纯度]"), tr(""), 0, 100, 3));
//    hashFormatInfo.insert(tr("[色温]"),                            FTypeInfo(tr("[色温]"), tr("K"), 1400, 25000));
//    hashFormatInfo.insert(tr("[显色指数]"),                        FTypeInfo(tr("[显色指数]"), 0, 100, 2));
//    hashFormatInfo.insert(tr("[显色指数Rx]"),                      FTypeInfo(tr("[显色指数Rx]"), 0, 100, 1));
//    hashFormatInfo.insert(tr("[色坐标]"),                          FTypeInfo(tr("[色坐标]"), 0, 1, 4, 0.001));
//    hashFormatInfo.insert(tr("[色坐标uv]"),                        FTypeInfo(tr("[色坐标uv]"), 0, 1, 4, 0.001));
//    hashFormatInfo.insert(tr("[色坐标uvp]"),                       FTypeInfo(tr("[色坐标uvp]"), 0, 1, 4, 0.001));
//    hashFormatInfo.insert(tr("[色坐标x]"),                         FTypeInfo(tr("[色坐标x]"), 0, 1, 4, 0.001));
//    hashFormatInfo.insert(tr("[色坐标y]"),                         FTypeInfo(tr("[色坐标y]"), 0, 1, 4, 0.001));
//    hashFormatInfo.insert(tr("[色坐标u]"),                         FTypeInfo(tr("[色坐标u]"), 0, 1, 4, 0.001));
//    hashFormatInfo.insert(tr("[色坐标v]"),                         FTypeInfo(tr("[色坐标v]"), 0, 1, 4, 0.001));
//    hashFormatInfo.insert(tr("[色坐标up]"),                        FTypeInfo(tr("[色坐标up]"), 0, 1, 4, 0.001));
//    hashFormatInfo.insert(tr("[色坐标vp]"),                        FTypeInfo(tr("[色坐标vp]"), 0, 1, 4, 0.001));
//    hashFormatInfo.insert(tr("[Duv]"),                             FTypeInfo(tr("[Duv]"), 0, 0.5, 3, 0.01));
//    hashFormatInfo.insert(tr("[红色比]"),                          FTypeInfo(tr("[红色比]"), tr("%"), 0, 100, 1));
//    hashFormatInfo.insert(tr("[蓝色比]"),                          FTypeInfo(tr("[蓝色比]"), tr("%"), 0, 100, 1));
//    hashFormatInfo.insert(tr("[绿色比]"),                          FTypeInfo(tr("[绿色比]"), tr("%"), 0, 100, 1));
//    hashFormatInfo.insert(tr("[光谱光通量]"),                      FTypeInfo(tr("[光谱光通量]"), tr("lm"), 0, 99999, 2, 100));
//    hashFormatInfo.insert(tr("[色容差]"),                          FTypeInfo(tr("[色容差]"), tr("SDCM"), 0, 100, 1, 1));

//    //光谱设置参数
//    hashFormatInfo.insert(tr("[像元位置]"),                        FTypeInfo(tr("[像元位置]"), 0, 2047));
//    hashFormatInfo.insert(tr("[波长范围]"),                        FTypeInfo(tr("[波长范围]"), tr("nm"), 300, 1100, 1));
//    hashFormatInfo.insert(tr("[波长间隔]"),                        FTypeInfo(tr("[波长间隔]"), tr("nm"), 0, 100, 1));
//    hashFormatInfo.insert(tr("[光谱采样]"),                        FTypeInfo(tr("[光谱采样]"), 0, 65536.0, 1));
//    hashFormatInfo.insert(tr("[固定暗底]"),                        FTypeInfo(tr("[固定暗底]"), 0, 9999.9, 1));
//    hashFormatInfo.insert(tr("[左右暗底]"),                        FTypeInfo(tr("[左右暗底]"), 0, 9999.9, 1));
//    hashFormatInfo.insert(tr("[平滑次数]"),                        FTypeInfo(tr("[平滑次数]"), 0, 100));
//    hashFormatInfo.insert(tr("[平滑范围]"),                        FTypeInfo(tr("[平滑范围]"), 0, 100));
//    hashFormatInfo.insert(tr("[平滑帧数]"),                        FTypeInfo(tr("[平滑帧数]"), 1, 100));
//    hashFormatInfo.insert(tr("[机器平均次数]"),                    FTypeInfo(tr("[机器平均次数]"), 1, 8));
//    hashFormatInfo.insert(tr("[快速采样延时]"),                    FTypeInfo(tr("[快速采样延时]"), 0, 600));
//    hashFormatInfo.insert(tr("[循环采样间隔]"),                    FTypeInfo(tr("[循环采样间隔]"), 0, 20000));
//    hashFormatInfo.insert(tr("[标准色温]"),                        FTypeInfo(tr("[标准色温]"), tr("K"), 2300, 4000, 2));
//    hashFormatInfo.insert(tr("[拟合_多项式次数]"),                 FTypeInfo(tr("[拟合_多项式次数]"), 2, 20));
//    hashFormatInfo.insert(tr("[拟合_取样次数]"),                   FTypeInfo(tr("[拟合_取样次数]"), 2, 500));
//    hashFormatInfo.insert(tr("[偏移量]"),                          FTypeInfo(tr("[偏移量]"), -0.5, 0.5, 4, 0.001));
////    //电机参数
////    hashFormatInfo.insert(tr("[电机步进]"),              FTypeInfo(tr("[电机步进]"), 0, 65535));

////    hashFormatInfo.insert(tr("[温度]"),                  FTypeInfo(tr("[温度]"), tr("℃"), -100, 1000, 1));
//    //数据库参数
//    hashFormatInfo.insert(tr("[样品编号]"),                        FTypeInfo(tr("[样品编号]"), 0, 99999));
//    hashFormatInfo.insert(tr("[环境温度]"),                        FTypeInfo(tr("[环境温度]"), tr("℃"), -100, 1000, 1));
//    hashFormatInfo.insert(tr("[环境湿度]"),                        FTypeInfo(tr("[环境湿度]"), tr("%"), 0, 100, 1));
//    //其他参数
//    hashFormatInfo.insert(tr("[ID]"),                              FTypeInfo(tr("[ID]"), 0, 65536));
//    hashFormatInfo.insert(tr("[总数]"),                            FTypeInfo(tr("[总数]"), 0, 65536));
//    hashFormatInfo.insert(tr("[分级]"),                            FTypeInfo(tr("[分级]"), 0, 65536));
//    hashFormatInfo.insert(tr("[合格]"),                            FTypeInfo(tr("[合格]"), 0, 100));
//    hashFormatInfo.insert(tr("[百分比]"),                          FTypeInfo(tr("[百分比]"), tr("%"), 0, 1000, 1));
//    hashFormatInfo.insert(tr("[良品率]"),                          FTypeInfo(tr("[良品率]"), tr("%"), 0, 1000, 1));
//    hashFormatInfo.insert(tr("[校正百分比]"),                      FTypeInfo(tr("[校正百分比]"), tr("%"), 10, 1000, 1));
    //    hashFormatInfo.insert(tr("[线路地址]"),                        FTypeInfo(tr("[线路地址]"), 0, 0xFFFFFFFF));
}

void HAppContext::initDataCaption()
{
    hashDataCaption.clear();
    hashDataCaption.insert("",                                  tr(""));
    hashDataCaption.insert("[]",                                tr(" "));
    hashDataCaption.insert("[_Fi]",                             tr("_虚拟"));
//    hashDataCaption.insert("[正向电流_1]",                      tr("正向电流(微)"));
//    hashDataCaption.insert("[正向电流_2]",                      tr("正向电流(小)"));
//    hashDataCaption.insert("[正向电流_3]",                      tr("正向电流(大)"));
//    hashDataCaption.insert("[回溯电流_1]",                      tr("回溯电流(微)"));
//    hashDataCaption.insert("[回溯电流_2]",                      tr("回溯电流(小)"));
//    hashDataCaption.insert("[回溯电流_3]",                      tr("回溯电流(大)"));
//    hashDataCaption.insert("[正向电流_L2_1]",                   tr("正向电流(1路)"));
//    hashDataCaption.insert("[正向电流_L2_2]",                   tr("正向电流(2路)"));
//    hashDataCaption.insert("[正向电流_L2_3]",                   tr("正向电流(3路)"));
//    hashDataCaption.insert("[正向电流_L2_4]",                   tr("正向电流(4路)"));
//    hashDataCaption.insert("[色坐标]",                          tr("色坐标xy"));
//    hashDataCaption.insert("[色坐标up]",                        tr("色坐标u'"));
//    hashDataCaption.insert("[色坐标vp]",                        tr("色坐标v'"));
//    hashDataCaption.insert("[色坐标uvp]",                       tr("色坐标u'v'"));
//    hashDataCaption.insert("[光谱光通量]",                      tr("光通量"));
//    hashDataCaption.insert("[测试日期时间]",                    tr("测试时间"));
//    hashDataCaption.insert("[分级_别名]",                       tr("分级"));
}

void HAppContext::readMimeType()
{
    QRegExp whitespace("\\s+");
    QString fileName = QFile::exists("/etc/Mime.types") ? "/etc/Mime.types" : ":/dat/Mime.types";
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd())
    {
        auto line = in.readLine();
        auto parts = line.split(whitespace);
        if (parts.isEmpty())
            continue;
        hashMimeType[parts.at(0)].unite(QSet<QString>::fromList(parts.mid(1)));
    }
    file.close();
}

HE_CORE_END_NAMESPACE
