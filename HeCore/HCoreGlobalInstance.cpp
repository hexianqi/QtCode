#include "HCoreGlobalInstance.h"
#include "HCore.h"
#include "HDataFormatInfo.h"
#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QPointF>
#include <QtCore/QRegularExpression>
#include <QtCore/QDebug>

HE_CORE_BEGIN_NAMESPACE

QHash<HLogType, QString>            hashLogCommand;
QHash<HActionType, QString>         hashActionComment;
QHash<HErrorType, QString>          hashErrorComment;
QHash<QString, HDataFormatInfo *>   hashDataFormatInfo;
QHash<QString, QString>             hashDataCaption;
QHash<QString, QSet<QString>>       hashMimeType;

char *HCore::toCommand(HLogType type)
{
    return hashLogCommand.value(type).toLatin1().data();
}

QString HCore::toComment(HActionType type)
{
    return hashActionComment.value(type);
}

QString HCore::toComment(HErrorType type)
{
    return hashErrorComment.value(type);
}

HDataFormatInfo *HCore::toFormatInfo(const QString &type)
{
    if (!hashDataFormatInfo.contains(type))
        hashDataFormatInfo.insert(type, new HDataFormatInfo(type));
    return hashDataFormatInfo.value(type);
}

QString HCore::toString(const QString &type, double value, char f)
{
    auto info = toFormatInfo(type);
    return QString().setNum(value, f, info->decimals());
}

QString HCore::toString(const QString &type, const QVariant &value)
{
    auto vt = value.type();
    if (vt == QVariant::PointF)
        return QString("%1, %2").arg(toString(type, value.toPointF().x()), toString(type, value.toPointF().y()));
    if (vt == QVariant::Point)
        return QString("%1, %2").arg(toString(type, value.toPoint().x()), toString(type, value.toPoint().y()));
    if (vt == QVariant::Double)
        return toString(type, value.toDouble());
    if (vt == QVariant::Int)
        return toString(type, value.toInt());
    if (vt == QVariant::LongLong)
        return toString(type, value.toLongLong());
    if (vt == QVariant::String)
        return value.toString();
    if (vt == QVariant::DateTime)
        return value.toDateTime().toString("yyyy-MM-dd hh:mm:ss");
    if (vt == QVariant::Date)
        return value.toDate().toString("yyyy-MM-dd");
    if (vt == QVariant::Time)
        return value.toTime().toString("hh:mm:ss");
    if (vt == QVariant::StringList)
        return value.toStringList().join(' ');
    if (vt == QVariant::List)
    {
        QStringList list;
        for (const auto &v : value.toList())
            list << toString(type, v);
        return list.join(" ");
    }
    return value.toString();
}

QStringList HCore::toString(const QString &type, QVector<double> value, char f)
{
    auto info = toFormatInfo(type);
    QStringList list;
    for (auto v : value)
        list << QString().setNum(v, f, info->decimals());
    return list;
}

QString HCore::toUnit(const QString &type)
{
    return toFormatInfo(type)->unit(false);
}

QString HCore::toCaption(const QString &type)
{
    return hashDataCaption.value(type, type.mid(1, type.size() - 2));
}

QStringList HCore::toCaption(QStringList type)
{
    QStringList list;
    for (const auto &t : type)
        list << toCaption(t);
    return list;
}

QString HCore::toCaptionUnit(const QString &type)
{
    auto caption = toCaption(type);
    auto unit = toUnit(type);
    if (!unit.isEmpty())
        caption += "(" + unit + ")";
    return caption;
}

QStringList HCore::toCaptionUnit(QStringList type)
{
    QStringList list;
    for (const auto &t : type)
        list << toCaptionUnit(t);
    return list;
}

QString HCore::fileNameFilter(const QString &name, const QList<QByteArray> &formats)
{
    QStringList list;

    for (const auto &ba : formats)
        list += ba;
    if (list.isEmpty())
        list << "*";
    else
        list.sort();
    return QString("%1 (*.").arg(name) + list.join(" *.") + ")";
}

QString HCore::fileNameFilter(const QString &name, const QStringList &mimeTypes)
{
    QSet<QString> formats;
    QStringList list;

    for (const auto &mimeType : mimeTypes)
        formats.unite(hashMimeType.value(mimeType));
    list = QStringList::fromSet(formats);
    if (list.isEmpty())
        list << "*";
    else
        list.sort();
    return QString("%1 (*.").arg(name) + list.join(" *.") + ")";
}

HCoreGlobalInstance *theInstance = HCoreGlobalInstance::instance();

HCoreGlobalInstance::HCoreGlobalInstance(QObject *parent) :
    QObject(parent)
{
    qInfo() << "Start Core Instance.";
    qRegisterMetaType<HLogType>("HLogType");
    qRegisterMetaType<HErrorType>("HErrorType");
    qRegisterMetaType<HActionType>("HActionType");
    initLogCommand();
    initActionComment();
    initErrorComment();
    initDataFormatInfo();
    initDataCaption();
    initMimeType();
}

HCoreGlobalInstance::~HCoreGlobalInstance()
{
    qDebug() << __func__;
}

void HCoreGlobalInstance::initLogCommand()
{
    hashLogCommand.clear();
    hashLogCommand.insert(Reset,        "\033[0m");
    hashLogCommand.insert(Bold,         "\033[1m");
    hashLogCommand.insert(Unbold,       "\033[2m");
    hashLogCommand.insert(ForeBlack,    "\033[30m");
    hashLogCommand.insert(ForeRed,      "\033[31m");
    hashLogCommand.insert(ForeGreen,    "\033[32m");
    hashLogCommand.insert(ForeYellow,   "\033[33m");
    hashLogCommand.insert(ForeBlue,     "\033[34m");
    hashLogCommand.insert(ForePurple,   "\033[35m");
    hashLogCommand.insert(ForeCyan,     "\033[36m");
    hashLogCommand.insert(ForeWhite,    "\033[37m");
    hashLogCommand.insert(BackBlack,    "\033[40m");
    hashLogCommand.insert(BackRed,      "\033[41m");
    hashLogCommand.insert(BackGreen,    "\033[42m");
    hashLogCommand.insert(BackYellow,   "\033[43m");
    hashLogCommand.insert(BackBlue,     "\033[44m");
    hashLogCommand.insert(BackPurple,   "\033[45m");
    hashLogCommand.insert(BackCyan,     "\033[46m");
    hashLogCommand.insert(BackWhite,    "\033[47m");
}

void HCoreGlobalInstance::initActionComment()
{
    hashActionComment.clear();
    hashActionComment.insert(ACT_IDLE,                          tr("空闲"));
    hashActionComment.insert(ACT_EXIT,                          tr("退出"));
    hashActionComment.insert(ACT_CHECK_DEVICE,                  tr("检查设备"));
    hashActionComment.insert(ACT_UNLOCK_DEVICE,                 tr("设备解锁"));
    // 光谱相关操作
    hashActionComment.insert(ACT_SET_INTEGRAL_TIME,             tr("设置积分时间"));
    hashActionComment.insert(ACT_SET_SPECTRUM_AVG_TIMES,        tr("设置光谱平均次数"));
    hashActionComment.insert(ACT_SET_SPECTRUM_SAMPLE_DELAY,     tr("设置光谱采样延时"));
    hashActionComment.insert(ACT_SET_RAM,                       tr("设置RAM数据"));
    hashActionComment.insert(ACT_SET_DATA,                      tr("设置数据"));
    hashActionComment.insert(ACT_GET_INTEGRAL_TIME,             tr("获取积分时间"));
    hashActionComment.insert(ACT_GET_SPECTRUM,                  tr("获取光谱数据"));
    hashActionComment.insert(ACT_GET_SPECTRUM_ENERGY,           tr("获取光谱能量数据"));
    hashActionComment.insert(ACT_GET_RAM,                       tr("获取RAM数据"));
    // 电相关操作
    hashActionComment.insert(ACT_SET_OUTPUT_VOLTAGE,            tr("设置输出电压"));
    hashActionComment.insert(ACT_SET_OUTPUT_CURRENT,            tr("设置输出电流"));
    hashActionComment.insert(ACT_SET_OVER_VOLTAGE,              tr("设置过电压"));
    hashActionComment.insert(ACT_SET_OVER_CURRENT,              tr("设置过电流"));
    hashActionComment.insert(ACT_SET_SOURCE_MODE,               tr("设置电源模式"));
    hashActionComment.insert(ACT_SET_SOURCE_ADDR,               tr("设置电源地址"));
    hashActionComment.insert(ACT_SET_SOURCE_OPERATION,          tr("设置电源操作"));
    hashActionComment.insert(ACT_SET_SOURCE_FORWARD,            tr("设置电源正向"));
    hashActionComment.insert(ACT_SET_SOURCE_REVERSE,            tr("设置电源反向"));
    hashActionComment.insert(ACT_SET_SOURCE_IO,                 tr("设置电源输入输出"));
    hashActionComment.insert(ACT_GET_SOURCE_STATE,              tr("获取电源状态"));
    hashActionComment.insert(ACT_GET_ELEC_DATA,                 tr("获取电数据"));
    hashActionComment.insert(ACT_SET_ELEC_MODULE,               tr("设置电模块"));
    hashActionComment.insert(ACT_SET_GEARS_OUTPUT_VOLTAGE,      tr("设置输出电压档位"));
    hashActionComment.insert(ACT_SET_GEARS_OUTPUT_CURRENT,      tr("设置输出电流档位"));
    hashActionComment.insert(ACT_SET_GEARS_MEASURED_VOLTAGE,    tr("设置实测电压档位"));
    hashActionComment.insert(ACT_SET_GEARS_MEASURED_CURRENT,    tr("设置实测电流档位"));
    hashActionComment.insert(ACT_SET_GEARS_REVERSE_VOLTAGE,     tr("设置反向电压档位"));
    hashActionComment.insert(ACT_SET_GEARS_REVERSE_CURRENT,     tr("设置反向漏流档位"));
    hashActionComment.insert(ACT_SET_REVERSE_VOLTAGE,           tr("设置反向电压"));
    hashActionComment.insert(ACT_GET_MEASURED_VOLTAGE,          tr("获取实测电压"));
    hashActionComment.insert(ACT_GET_MEASURED_CURRENT,          tr("获取实测电流"));
    hashActionComment.insert(ACT_GET_REVERSE_CURRENT,           tr("获取反向漏流"));
    // 光相关操作
    hashActionComment.insert(ACT_SET_LUMINOUS_MODULE,           tr("设置光模块"));
    hashActionComment.insert(ACT_SET_LUMINOUS_TYPE,             tr("设置光类型"));
    hashActionComment.insert(ACT_SET_LUMINOUS_GEARS,            tr("设置光档位"));
    hashActionComment.insert(ACT_GET_LUMINOUS_DATA,             tr("获取光数据"));
    // 状态操作
    hashActionComment.insert(ACT_RESET_STATE_TRIGGER,           tr("复位触发状态"));
    hashActionComment.insert(ACT_QUERY_STATE_TRIGGER,           tr("查询触发状态"));
    // 测试操作
    hashActionComment.insert(ACT_SINGLE_TEST,                   tr("单次测试"));
    hashActionComment.insert(ACT_GET_SPECTRUM_ELEC,             tr("获取光谱&电数据"));
    // 重置操作
    hashActionComment.insert(ACT_RESET_SPECTRUM,                tr("重新配置光谱数据"));
    hashActionComment.insert(ACT_RESET_ELEC,                    tr("重新配置电数据"));
    hashActionComment.insert(ACT_RESET_LUMINOUS,                tr("重新配置光数据"));
    hashActionComment.insert(ACT_RESET_GRADE,                   tr("重新配置分级数据"));
    hashActionComment.insert(ACT_RESET_ADJUST,                  tr("重新配置调整数据"));
    hashActionComment.insert(ACT_RESET_QUALITY,                 tr("重新配置品质数据"));
    hashActionComment.insert(ACT_RESET_CHROMATISM,              tr("重新配置色容差数据"));

//    hashActionComment.insert(ACT_REFRESH_USE_TIME,             QStringList() << tr("ACT_REFRESH_USE_TIME") << tr("刷新设备使用时间"));

//    hashActionComment.insert(ACT_SET_ELEC_MODULE,                QStringList() << tr("ACT_SET_ELEC_MODULE") << tr("设置电学参数模块"));
//    hashActionComment.insert(ACT_SET_ELEC_CODE,                  QStringList() << tr("ACT_SET_ELEC_CODE") << tr("设置开关编码"));
//    hashActionComment.insert(ACT_GET_ELEC,                       QStringList() << tr("ACT_GET_ELEC") << tr("获取电参数"));
//    hashActionComment.insert(ACT_GET_FEEDBACK_CURRENT,           QStringList() << tr("ACT_GET_FEEDBACK_CURRENT") << tr("获取回溯电流"));

//    hashActionComment.insert(ACT_GET_ANGULAR_DISTRIBUTION,       QStringList() << tr("ACT_GET_ANGULAR_DISTRIBUTION") << tr("获取角度分布数据"));

//    hashActionComment.insert(ACT_RESET_MOTOR,                    QStringList() << tr("ACT_RESET_MOTOR") << tr("电机复位"));

//    hashActionComment.insert(ACT_SET_LED_NUM,                    QStringList() << tr("ACT_SET_LED_NUM") << tr("设置LED编号"));
//    hashActionComment.insert(ACT_SET_LED_ADDRESS,                QStringList() << tr("ACT_SET_LED_ADDRESS") << tr("设置LED地址"));

//    hashActionComment.insert(ACT_SET_MOTOR_MODULE,           QStringList() << tr("ACT_SET_MOTOR_MODULE") << tr("设置电机模块"));
//    hashActionComment.insert(ACT_SET_MOTOR_DIRECTION,        QStringList() << tr("ACT_SET_MOTOR_DIRECTION") << tr("设置电机走步方向"));
//    hashActionComment.insert(ACT_SET_MOTOR_STEP,             QStringList() << tr("ACT_SET_MOTOR_STEP") << tr("设置电机走步"));

//    hashActionComment.insert(ACT_SET_TEMPERATURE_MODULE,     QStringList() << tr("ACT_SET_TEMPERATURE_MODULE") << tr("设置温度模块"));
//    hashActionComment.insert(ACT_SET_TEMPERATURE_TYPE,       QStringList() << tr("ACT_SET_TEMPERATURE_TYPE") << tr("设置温度类型"));
//    hashActionComment.insert(ACT_SET_TEMPERATURE_GEARS,      QStringList() << tr("ACT_SET_TEMPERATURE_GEARS") << tr("设置温度档位"));
//    hashActionComment.insert(ACT_SET_TEMPERATURE_CALIBRATE,  QStringList() << tr("ACT_SET_TEMPERATURE_CALIBRATE") << tr("设置温度校准数据"));
//    hashActionComment.insert(ACT_GET_TEMPERATURE,            QStringList() << tr("ACT_GET_TEMPERATURE") << tr("获取温度"));
//    hashActionComment.insert(ACT_GET_TEMPERATURE_CALIBRATE,  QStringList() << tr("ACT_GET_TEMPERATURE_CALIBRATE") << tr("获取温度校准数据"));

//    hashActionComment.insert(ACT_GET_LAMPS_ELEC,             QStringList() << tr("ACT_GET_LAMPS_ELEC") << tr("获取灯具电量参数"));

//    hashActionComment.insert(ACT_PLC_RESET_MOTOR,            QStringList() << tr("ACT_PLC_RESET_MOTOR") << tr("电机复位"));
//    hashActionComment.insert(ACT_PLC_SEND_DATA,              QStringList() << tr("ACT_PLC_SEND_DATA") << tr("发送数据"));
//    hashActionComment.insert(ACT_PLC_FLUSH_DELAY,            QStringList() << tr("ACT_PLC_FLUSH_DELAY") << tr("设置吹气延时"));
//    hashActionComment.insert(ACT_PLC_GET_FEEDBACK,           QStringList() << tr("ACT_PLC_GET_FEEDBACK") << tr("获取回溯数据"));
//    hashActionComment.insert(ACT_PLC_QUERY_STATE_TRIGGER,    QStringList() << tr("ACT_PLC_QUERY_STATE_TRIGGER") << tr("查询触发状态"));
//    hashActionComment.insert(ACT_PLC_QUERY_STATE_MOTOR,      QStringList() << tr("ACT_PLC_QUERY_STATE_MOTOR") << tr("查询电机状态"));
//    hashActionComment.insert(ACT_PLC_QUERY_STATE_BLANKING,   QStringList() << tr("ACT_PLC_QUERY_STATE_BLANKING") << tr("查询落料状态"));

//    hashActionComment.insert(ACT_COB_SET_CYLINDER,           QStringList() << tr("ACT_COB_SET_CYLINDER") << tr("气缸控制"));
//    hashActionComment.insert(ACT_COB_SET_MOTOR_MODE,         QStringList() << tr("ACT_COB_SET_MOTOR_MODE") << tr("设置电机模式"));
//    hashActionComment.insert(ACT_COB_SET_MOTOR_DATA,         QStringList() << tr("ACT_COB_SET_MOTOR_DATA") << tr("设置电机数据"));
//    hashActionComment.insert(ACT_COB_RESET_MOTOR_POSITION,   QStringList() << tr("ACT_COB_RESET_MOTOR_POSITION") << tr("电机复位"));
//    hashActionComment.insert(ACT_COB_SET_MOTOR_POSITION,     QStringList() << tr("ACT_COB_SET_MOTOR_POSITION") << tr("电机移动"));
//    hashActionComment.insert(ACT_COB_RESET_MOTOR_STEP,       QStringList() << tr("ACT_COB_RESET_MOTOR_STEP") << tr("电机复位"));
//    hashActionComment.insert(ACT_COB_SET_MOTOR_STEP,         QStringList() << tr("ACT_COB_SET_MOTOR_STEP") << tr("电机移动"));
//    hashActionComment.insert(ACT_COB_QUERY_STATE,            QStringList() << tr("ACT_COB_QUERY_STATE") << tr("查询状态"));

//    hashActionComment.insert(ACT_SET_MOTOR_ANGULAR,          QStringList() << tr("ACT_SET_MOTOR_ANGULAR") << tr("设置电机角度"));
}

void HCoreGlobalInstance::initErrorComment()
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
    hashErrorComment.insert(E_DEVICE_INVALID,                   tr("设备无效"));
    hashErrorComment.insert(E_DEVICE_NOT_FOUND,                 tr("设备找不到"));
    hashErrorComment.insert(E_DEVICE_ACTION_NOT_SUPPORT,        tr("设备不支持此命令"));
    hashErrorComment.insert(E_DEVICE_ACTION_PARAM_ERROR,        tr("设备命令参数错误"));
    hashErrorComment.insert(E_DEVICE_CHECKCODE_ERROR,           tr("设备校验码错误"));
    hashErrorComment.insert(E_DEVICE_DATA_SEND_ERROR,           tr("设备发送数据错误"));
    hashErrorComment.insert(E_DEVICE_DATA_RETURN_ERROR,         tr("设备返回数据错误"));
    hashErrorComment.insert(E_DEVICE_FEEDBACK_OK,               tr("设备反馈 - 成功"));
    hashErrorComment.insert(E_DEVICE_FEEDBACK_FORMAT_ERROR,     tr("设备反馈 - 格式错误"));
    hashErrorComment.insert(E_DEVICE_FEEDBACK_MODULE_NORESPONSE,tr("设备反馈 - 模块无应答"));
    hashErrorComment.insert(E_DEVICE_FEEDBACK_OVERFLOW,         tr("设备反馈 - 数据溢出"));
    hashErrorComment.insert(E_DEVICE_FEEDBACK_BUSY,             tr("设备反馈 - 模块繁忙"));
    hashErrorComment.insert(E_DEVICE_FEEDBACK_CHIP_NORESPONSE,  tr("设备反馈 - 芯片无响应"));
    hashErrorComment.insert(E_DEVICE_FEEDBACK_COMMAND_ERROR,    tr("设备反馈 - 命令错误"));
    hashErrorComment.insert(E_PROTOCOL_INVALID,                 tr("通讯协议无效"));
    hashErrorComment.insert(E_STRATEGY_ACTION_NOT_SUPPORT,      tr("策略不支持此命令"));
    hashErrorComment.insert(E_THREAD_NO_HANDLE,                 tr("线程无法处理"));
}

void HCoreGlobalInstance::initDataFormatInfo()
{
    hashDataFormatInfo.clear();
    hashDataFormatInfo.insert("",                               new HDataFormatInfo());
    hashDataFormatInfo.insert("[]",                             new HDataFormatInfo("[]"));
    // 光谱参数
    hashDataFormatInfo.insert("[标准色温]",                     new HDataFormatInfo("[标准色温]", "K", 2300, 4000, 2));
    hashDataFormatInfo.insert("[积分时间]",                     new HDataFormatInfo("[积分时间]", "ms", 1, 4000, 1));
    hashDataFormatInfo.insert("[光谱像元]",                     new HDataFormatInfo("[光谱像元]", 0, 2047));
    hashDataFormatInfo.insert("[光谱波长]",                     new HDataFormatInfo("[光谱波长]", "nm", 200, 1100, 1));
    hashDataFormatInfo.insert("[光谱波长间隔]",                 new HDataFormatInfo("[光谱波长间隔]", "nm", 0, 100, 1));
    hashDataFormatInfo.insert("[光谱采样等待时间]",             new HDataFormatInfo("[光谱采样等待时间]", 0, 1000));
    hashDataFormatInfo.insert("[光谱平均次数]",                 new HDataFormatInfo("[光谱平均次数]", 1, 32));
    hashDataFormatInfo.insert("[光谱采样延时]",                 new HDataFormatInfo("[光谱采样延时]", "ms", 0, 600));
    hashDataFormatInfo.insert("[光谱保留像元]",                 new HDataFormatInfo("[光谱保留像元]", 0, 2047));
    hashDataFormatInfo.insert("[光谱固定暗底]",                 new HDataFormatInfo("[光谱固定暗底]", 0, 9999.9, 1));
    hashDataFormatInfo.insert("[光谱左右暗底]",                 new HDataFormatInfo("[光谱左右暗底]", 0, 9999.9, 1));
    hashDataFormatInfo.insert("[光谱平滑帧数]",                 new HDataFormatInfo("[光谱平滑帧数]", 1, 100));
    hashDataFormatInfo.insert("[光谱平滑次数]",                 new HDataFormatInfo("[光谱平滑次数]", 0, 100));
    hashDataFormatInfo.insert("[光谱平滑范围]",                 new HDataFormatInfo("[光谱平滑范围]", 0, 100));
    hashDataFormatInfo.insert("[光谱拟合取样次数]",             new HDataFormatInfo("[光谱拟合取样次数]", 30, 500));
    hashDataFormatInfo.insert("[光谱拟合有效范围]",             new HDataFormatInfo("[光谱拟合有效范围]", 0, 65535));
    hashDataFormatInfo.insert("[光谱拟合多项式项数]",           new HDataFormatInfo("[光谱拟合多项式项数]", 2, 20));
    hashDataFormatInfo.insert("[标准光谱光通量]",               new HDataFormatInfo("[标准光谱光通量]", "lm", 0, 99999, 2, 100));
    hashDataFormatInfo.insert("[光谱光通量系数]",               new HDataFormatInfo("[光谱光通量系数]", 0, 99999999));
    // 光谱数据
    hashDataFormatInfo.insert("[光谱采样值]",                   new HDataFormatInfo("[光谱采样值]", 0.0, 65536.0, 1));
    hashDataFormatInfo.insert("[光谱采样比率]",                 new HDataFormatInfo("[光谱采样比率]",  "%", 0, 100, 1));
    hashDataFormatInfo.insert("[峰值波长]",                     new HDataFormatInfo("[峰值波长]", "nm", 200, 1100, 1));
    hashDataFormatInfo.insert("[峰值带宽]",                     new HDataFormatInfo("[峰值带宽]", "nm", 200, 1100, 1));
    hashDataFormatInfo.insert("[主波长]",                       new HDataFormatInfo("[主波长]", "nm", 360, 780, 1));
    hashDataFormatInfo.insert("[色纯度]",                       new HDataFormatInfo("[色纯度]", 0, 100, 3));
    hashDataFormatInfo.insert("[色温]",                         new HDataFormatInfo("[色温]", "K", 1400, 25000));
    hashDataFormatInfo.insert("[显色指数Ra]",                   new HDataFormatInfo("[显色指数Ra]", 0, 100, 2));
    hashDataFormatInfo.insert("[显色指数R9]",                   new HDataFormatInfo("[显色指数R9]", 0, 100, 2));
    hashDataFormatInfo.insert("[显色指数Rx]",                   new HDataFormatInfo("[显色指数Rx]", 0, 100, 1));
    hashDataFormatInfo.insert("[色坐标]",                       new HDataFormatInfo("[色坐标]", 0, 1, 4, 0.001));
    hashDataFormatInfo.insert("[色坐标uv]",                     new HDataFormatInfo("[色坐标uv]", 0, 1, 4, 0.001));
    hashDataFormatInfo.insert("[色坐标uvp]",                    new HDataFormatInfo("[色坐标uvp]", 0, 1, 4, 0.001));
    hashDataFormatInfo.insert("[色坐标x]",                      new HDataFormatInfo("[色坐标x]", 0, 1, 4, 0.001));
    hashDataFormatInfo.insert("[色坐标y]",                      new HDataFormatInfo("[色坐标y]", 0, 1, 4, 0.001));
    hashDataFormatInfo.insert("[色坐标u]",                      new HDataFormatInfo("[色坐标u]", 0, 1, 4, 0.001));
    hashDataFormatInfo.insert("[色坐标v]",                      new HDataFormatInfo("[色坐标v]", 0, 1, 4, 0.001));
    hashDataFormatInfo.insert("[色坐标up]",                     new HDataFormatInfo("[色坐标up]", 0, 1, 4, 0.001));
    hashDataFormatInfo.insert("[色坐标vp]",                     new HDataFormatInfo("[色坐标vp]", 0, 1, 4, 0.001));
    hashDataFormatInfo.insert("[Duv]",                          new HDataFormatInfo("[Duv]", 0, 0.5, 3, 0.01));
    hashDataFormatInfo.insert("[明视觉光通量]",                 new HDataFormatInfo("[明视觉光通量]", "lm", 0, 99999, 2, 1.0));
    hashDataFormatInfo.insert("[明视觉光效率]",                 new HDataFormatInfo("[明视觉光效率]", "lm/W", 0, 99999, 2, 1.0));
    hashDataFormatInfo.insert("[红色比]",                       new HDataFormatInfo("[红色比]", "%", 0, 100, 1));
    hashDataFormatInfo.insert("[蓝色比]",                       new HDataFormatInfo("[蓝色比]", "%", 0, 100, 1));
    hashDataFormatInfo.insert("[绿色比]",                       new HDataFormatInfo("[绿色比]", "%", 0, 100, 1));
    hashDataFormatInfo.insert("[光谱能量百分比]",               new HDataFormatInfo("[光谱能量百分比]", "%", 0, 100, 1));
    hashDataFormatInfo.insert("[光谱光通量]",                   new HDataFormatInfo("[光谱光通量]", "lm", 0, 99999, 2, 100));
    // 色容差参数
    hashDataFormatInfo.insert("[色容差]",                       new HDataFormatInfo("[色容差]", "SDCM", 0, 100, 1, 1));
    hashDataFormatInfo.insert("[参数G]",                        new HDataFormatInfo("[参数G]", 0, 1000000, 1));
    hashDataFormatInfo.insert("[旋转角]",                       new HDataFormatInfo("[旋转角]", "°", 0, 180, 1, 1));
    hashDataFormatInfo.insert("[轴A]",                          new HDataFormatInfo("[轴A]", 0, 1000000, 1));
    hashDataFormatInfo.insert("[轴B]",                          new HDataFormatInfo("[轴B]", 0, 1000000, 1));
    // 电参数
    hashDataFormatInfo.insert("[输出电压]",                     new HDataFormatInfo("[输出电压]", "V", 0, 400, 3));
    hashDataFormatInfo.insert("[输出电流]",                     new HDataFormatInfo("[输出电流]", "mA", 0, 5000, 3));
    hashDataFormatInfo.insert("[输出电流1]",                    new HDataFormatInfo("[输出电流1]", "mA", 0, 5000, 3));
    hashDataFormatInfo.insert("[输出电流2]",                    new HDataFormatInfo("[输出电流2]", "mA", 0, 5000, 3));
    hashDataFormatInfo.insert("[输出电流3]",                    new HDataFormatInfo("[输出电流3]", "mA", 0, 5000, 3));
    hashDataFormatInfo.insert("[反向电压]",                     new HDataFormatInfo("[反向电压]", "V", 0, 400, 3));
    hashDataFormatInfo.insert("[实测电压]",                     new HDataFormatInfo("[实测电压]", "V", 0, 400, 3));
    hashDataFormatInfo.insert("[实测电流]",                     new HDataFormatInfo("[实测电流]", "mA", 0, 5000, 3));
    hashDataFormatInfo.insert("[实测电流1]",                    new HDataFormatInfo("[实测电流1]", "mA", 0, 5000, 3));
    hashDataFormatInfo.insert("[实测电流2]",                    new HDataFormatInfo("[实测电流2]", "mA", 0, 5000, 3));
    hashDataFormatInfo.insert("[实测电流3]",                    new HDataFormatInfo("[实测电流3]", "mA", 0, 5000, 3));
    hashDataFormatInfo.insert("[反向漏流]",                     new HDataFormatInfo("[反向漏流]", "uA",0, 500, 3));
    hashDataFormatInfo.insert("[电功率]",                       new HDataFormatInfo("[电功率]", "W", 0, 500, 3));
    hashDataFormatInfo.insert("[电阻]",                         new HDataFormatInfo("[电阻]", "Ω", 0, 10, 3));
    hashDataFormatInfo.insert("[功率因数]",                     new HDataFormatInfo("[功率因数]", 0, 1, 3));
    // 光参数
    hashDataFormatInfo.insert("[光采样值]",                     new HDataFormatInfo("[光采样值]"));
    hashDataFormatInfo.insert("[光采样比率]",                   new HDataFormatInfo("[光采样比率]",  "%", 0, 100, 1));
    hashDataFormatInfo.insert("[光通量]",                       new HDataFormatInfo("[光通量]", "lm", 0, 99999, 2, 100));
    hashDataFormatInfo.insert("[光强度]",                       new HDataFormatInfo("[光强度]", "mcd", 0, 99999, 2, 100));
    hashDataFormatInfo.insert("[光亮度]",                       new HDataFormatInfo("[光亮度]", "cd/m<sup>2</sup>", 0, 99999, 2, 100));
    hashDataFormatInfo.insert("[光照度]",                       new HDataFormatInfo("[光照度]", "lx", 0, 99999, 2, 100));
    hashDataFormatInfo.insert("[光功率]",                       new HDataFormatInfo("[光功率]", "mW", 0, 99999, 2, 100));
    hashDataFormatInfo.insert("[光效率]",                       new HDataFormatInfo("[光效率]", "lm/W", 0, 99999, 2, 100));
    // 数据库参数
    hashDataFormatInfo.insert("[样品编号]",                     new HDataFormatInfo("[样品编号]", 0, 99999));
    hashDataFormatInfo.insert("[环境温度]",                     new HDataFormatInfo("[环境温度]", "℃", -100, 1000, 1));
    hashDataFormatInfo.insert("[环境湿度]",                     new HDataFormatInfo("[环境湿度]", "%", 0, 100, 1));
    // 分级参数
    hashDataFormatInfo.insert("[分级]",                         new HDataFormatInfo("[分级]", 0, 99999));
    hashDataFormatInfo.insert("[优先级]",                       new HDataFormatInfo("[优先级]", 1, 99999));
    hashDataFormatInfo.insert("[分级数]",                       new HDataFormatInfo("[分级数]", 0, 99999));
    hashDataFormatInfo.insert("[偏移量]",                       new HDataFormatInfo("[偏移量]", -0.5, 0.5, 4, 0.001));
    // 调整参数
    hashDataFormatInfo.insert("[调整比率]",                     new HDataFormatInfo("[调整比率]", "%", 10, 1000, 1));
    hashDataFormatInfo.insert("[自吸收系数]",                   new HDataFormatInfo("[自吸收系数]", 0, 100, 2));

//    //交流电参数
//    hashFormatInfo.insert(tr("[交流电压]"),                        FTypeInfo(tr("[交流电压]"), tr("V"), 0, 500, 2));
//    hashFormatInfo.insert(tr("[交流电流]"),                        FTypeInfo(tr("[交流电流]"), tr("A"), 0, 50, 3));

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

//    //电机参数
//    hashFormatInfo.insert(tr("[电机步进]"),              FTypeInfo(tr("[电机步进]"), 0, 65535));
//    //其他参数
//    hashFormatInfo.insert(tr("[ID]"),                              FTypeInfo(tr("[ID]"), 0, 65536));
//    hashFormatInfo.insert(tr("[总数]"),                            FTypeInfo(tr("[总数]"), 0, 65536));
//    hashFormatInfo.insert(tr("[分级]"),                            FTypeInfo(tr("[分级]"), 0, 65536));
//    hashFormatInfo.insert(tr("[合格]"),                            FTypeInfo(tr("[合格]"), 0, 100));
//    hashFormatInfo.insert(tr("[百分比]"),                          FTypeInfo(tr("[百分比]"), tr("%"), 0, 1000, 1));
//    hashFormatInfo.insert(tr("[良品率]"),                          FTypeInfo(tr("[良品率]"), tr("%"), 0, 1000, 1));
//    hashFormatInfo.insert(tr("[线路地址]"),                        FTypeInfo(tr("[线路地址]"), 0, 0xFFFFFFFF));
}

void HCoreGlobalInstance::initDataCaption()
{
    hashDataCaption.clear();
    hashDataCaption.insert("",                                  tr(""));
    hashDataCaption.insert("[]",                                tr(""));
    hashDataCaption.insert("[光谱像元]",                        tr("像元"));
    hashDataCaption.insert("[光谱波长]",                        tr("波长"));
    hashDataCaption.insert("[色坐标]",                          tr("色坐标xy"));
    hashDataCaption.insert("[色坐标up]",                        tr("色坐标u'"));
    hashDataCaption.insert("[色坐标vp]",                        tr("色坐标v'"));
    hashDataCaption.insert("[色坐标uvp]",                       tr("色坐标u'v'"));
    hashDataCaption.insert("[光谱光通量]",                      tr("光通量"));
    hashDataCaption.insert("[测试日期时间]",                    tr("测试时间"));

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

//    hashDataCaption.insert("[分级_别名]",                       tr("分级"));
}

void HCoreGlobalInstance::initMimeType()
{
    QRegularExpression sep("\\s+");
    QString fileName = QFile::exists("/etc/Mime.types") ? "/etc/Mime.types" : ":/dat/Mime.types";
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd())
    {
        auto line = in.readLine();
        auto parts = line.split(sep);
        if (parts.isEmpty())
            continue;
        hashMimeType[parts.at(0)].unite(QSet<QString>::fromList(parts.mid(1)));
    }
    file.close();
}

HE_CORE_END_NAMESPACE
