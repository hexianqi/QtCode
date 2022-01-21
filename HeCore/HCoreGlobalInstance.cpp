#include "HCoreGlobalInstance.h"
#include "HCore.h"
#include "HDataFormatInfo.h"
#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QPointF>
#include <QtCore/QRegularExpression>
#include <QtCore/QDebug>

HE_BEGIN_NAMESPACE

QHash<HLogType, QString>            hashLogCommand;
QHash<HActionType, QString>         hashActionComment;
QHash<HErrorType, QString>          hashErrorComment;
QHash<QString, HDataFormatInfo *>   hashDataFormatInfo;
QHash<QString, QString>             hashDataCaption;
QHash<QString, QStringList>         hashDataGroup;
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
    if (value.canConvert<QVariantList>())
    {
        QStringList list;
        auto iterable = value.value<QSequentialIterable>();
        for (const auto &v : iterable)
            list << toString(type, v);
        return list.join(" ");
    }
    if (value.canConvert<QVariantMap>())
    {
        QStringList list;
        auto iterable = value.value<QAssociativeIterable>();
        for (auto it = iterable.begin(); it != iterable.end(); ++it)
        {
            auto key = it.key().toString();
            list << toCaption(key) + ":" + toString(key, it.value());
        }
        return "{" + list.join(",") + "}";
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

QStringList HCore::toCaptionUnit(const QStringList &type)
{
    QStringList list;
    for (const auto &t : type)
        list << toCaptionUnit(t);
    return list;
}

QStringList HCore::membership(const QString &name)
{
    return hashDataGroup.value(name);
}

QStringList HCore::membership(const QStringList &name)
{
    QStringList list;
    for (const auto &t : name)
        list << hashDataGroup.value(t);
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

void HCoreGlobalInstance::init()
{
    if (_initialized)
        return;
    initLogCommand();
    initActionComment();
    initErrorComment();
    initDataFormatInfo();
    initDataCaption();
    initDataGroup();
    initMimeType();
    _initialized = true;
}

HCoreGlobalInstance::HCoreGlobalInstance(QObject *parent) :
    QObject(parent)
{
    qInfo() << "Start Core Instance.";
    qRegisterMetaType<HLogType>("HLogType");
    qRegisterMetaType<HErrorType>("HErrorType");
    qRegisterMetaType<HActionType>("HActionType");
}

HCoreGlobalInstance::~HCoreGlobalInstance()
{
    qInfo() << __func__;
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
    hashDataFormatInfo.insert("[百分比]",                       new HDataFormatInfo("[百分比]", "%", 0, 100, 1));
    // 光谱参数
    hashDataFormatInfo.insert("[标准色温]",                     new HDataFormatInfo("[标准色温]", "K", 2300, 4000, 2));
    hashDataFormatInfo.insert("[积分时间]",                     new HDataFormatInfo("[积分时间]", "ms", 1, 4000, 1));
    hashDataFormatInfo.insert("[光谱像元]",                     new HDataFormatInfo("[光谱像元]", 0, 2047));
    hashDataFormatInfo.insert("[光谱波长]",                     new HDataFormatInfo("[光谱波长]", "nm", 200, 1100, 1));
    hashDataFormatInfo.insert("[光谱波长间隔]",                 new HDataFormatInfo("[光谱波长间隔]", "nm", 0, 100, 1));
    hashDataFormatInfo.insert("[光谱采样等待时间]",             new HDataFormatInfo("[光谱采样等待时间]", 0, 1000));
    hashDataFormatInfo.insert("[光谱平均次数]",                 new HDataFormatInfo("[光谱平均次数]", 1, 32));
    hashDataFormatInfo.insert("[光谱采样延时]",                 new HDataFormatInfo("[光谱采样延时]", "ms", 0, 10000));
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
    hashDataFormatInfo.insert("[光谱采样比率]",                 hashDataFormatInfo.value("[百分比]"));
    hashDataFormatInfo.insert("[峰值波长]",                     new HDataFormatInfo("[峰值波长]", "nm", 200, 1100, 1));
    hashDataFormatInfo.insert("[峰值带宽]",                     new HDataFormatInfo("[峰值带宽]", "nm", 200, 1100, 1));
    hashDataFormatInfo.insert("[主波长]",                       new HDataFormatInfo("[主波长]", "nm", 360, 780, 1));
    hashDataFormatInfo.insert("[色纯度]",                       new HDataFormatInfo("[色纯度]", 0, 100, 3));
    hashDataFormatInfo.insert("[色温]",                         new HDataFormatInfo("[色温]", "K", 1400, 25000));
    hashDataFormatInfo.insert("[显色指数Ra]",                   new HDataFormatInfo("[显色指数Ra]", 0, 100, 2));
    hashDataFormatInfo.insert("[显色指数R9]",                   new HDataFormatInfo("[显色指数R9]", 0, 100, 2));
    hashDataFormatInfo.insert("[显色指数Rx]",                   new HDataFormatInfo("[显色指数Rx]", 0, 100, 1));
    hashDataFormatInfo.insert("[色坐标]",                       new HDataFormatInfo("[色坐标]", 0, 1, 4, 0.001));
    hashDataFormatInfo.insert("[色坐标uv]",                     hashDataFormatInfo.value("[色坐标]"));
    hashDataFormatInfo.insert("[色坐标uvp]",                    hashDataFormatInfo.value("[色坐标]"));
    hashDataFormatInfo.insert("[色坐标x]",                      hashDataFormatInfo.value("[色坐标]"));
    hashDataFormatInfo.insert("[色坐标y]",                      hashDataFormatInfo.value("[色坐标]"));
    hashDataFormatInfo.insert("[色坐标u]",                      hashDataFormatInfo.value("[色坐标]"));
    hashDataFormatInfo.insert("[色坐标v]",                      hashDataFormatInfo.value("[色坐标]"));
    hashDataFormatInfo.insert("[色坐标up]",                     hashDataFormatInfo.value("[色坐标]"));
    hashDataFormatInfo.insert("[色坐标vp]",                     hashDataFormatInfo.value("[色坐标]"));
    hashDataFormatInfo.insert("[Duv]",                          new HDataFormatInfo("[Duv]", 0, 0.5, 3, 0.01));
    hashDataFormatInfo.insert("[明视觉光通量]",                 new HDataFormatInfo("[明视觉光通量]", "lm", 0, 99999, 2, 1.0));
    hashDataFormatInfo.insert("[明视觉光效率]",                 new HDataFormatInfo("[明视觉光效率]", "lm/W", 0, 99999, 2, 1.0));
    hashDataFormatInfo.insert("[光谱光通量]",                   new HDataFormatInfo("[光谱光通量]", "lm", 0, 99999, 2, 100));
    hashDataFormatInfo.insert("[红色比]",                       hashDataFormatInfo.value("[百分比]"));
    hashDataFormatInfo.insert("[蓝色比]",                       hashDataFormatInfo.value("[百分比]"));
    hashDataFormatInfo.insert("[绿色比]",                       hashDataFormatInfo.value("[百分比]"));
    hashDataFormatInfo.insert("[光谱能量百分比]",               hashDataFormatInfo.value("[百分比]"));
    // 色容差参数
    hashDataFormatInfo.insert("[色容差]",                       new HDataFormatInfo("[色容差]", "SDCM", 0, 100, 1, 1));
    hashDataFormatInfo.insert("[参数G]",                        new HDataFormatInfo("[参数G]", -1000000, 1000000, 1));
    hashDataFormatInfo.insert("[旋转角]",                       new HDataFormatInfo("[旋转角]", "°", 0, 180, 1, 1));
    hashDataFormatInfo.insert("[轴A]",                          new HDataFormatInfo("[轴A]", 0, 1000000, 1));
    hashDataFormatInfo.insert("[轴B]",                          new HDataFormatInfo("[轴B]", 0, 1000000, 1));
    // 电参数
    hashDataFormatInfo.insert("[电压]",                         new HDataFormatInfo("[电压]", "V", 0, 400, 3));
    hashDataFormatInfo.insert("[电流]",                         new HDataFormatInfo("[电流]", "mA", 0, 5000, 3));
    hashDataFormatInfo.insert("[电功率]",                       new HDataFormatInfo("[电功率]", "W", 0, 500, 3));
    hashDataFormatInfo.insert("[电阻]",                         new HDataFormatInfo("[电阻]", "Ω", 0, 10, 3));
    hashDataFormatInfo.insert("[反向漏流]",                     new HDataFormatInfo("[反向漏流]", "uA",0, 500, 3));
    hashDataFormatInfo.insert("[输出电压]",                     hashDataFormatInfo.value("[电压]"));
    hashDataFormatInfo.insert("[输出电流]",                     hashDataFormatInfo.value("[电流]"));
    hashDataFormatInfo.insert("[输出电流1]",                    hashDataFormatInfo.value("[电流]"));
    hashDataFormatInfo.insert("[输出电流2]",                    hashDataFormatInfo.value("[电流]"));
    hashDataFormatInfo.insert("[输出电流3]",                    hashDataFormatInfo.value("[电流]"));
    hashDataFormatInfo.insert("[反向电压]",                     hashDataFormatInfo.value("[电压]"));
    hashDataFormatInfo.insert("[实测电压]",                     hashDataFormatInfo.value("[电压]"));
    hashDataFormatInfo.insert("[实测电流]",                     hashDataFormatInfo.value("[电流]"));
    hashDataFormatInfo.insert("[实测电流1]",                    hashDataFormatInfo.value("[电流]"));
    hashDataFormatInfo.insert("[实测电流2]",                    hashDataFormatInfo.value("[电流]"));
    hashDataFormatInfo.insert("[实测电流3]",                    hashDataFormatInfo.value("[电流]"));
    // 交流电参数
    hashDataFormatInfo.insert("[交流电压]",                     new HDataFormatInfo("[交流电压]", "V", 0, 500, 2));
    hashDataFormatInfo.insert("[交流电流]",                     new HDataFormatInfo("[交流电流]", "A", 0, 50, 3));
    hashDataFormatInfo.insert("[交流电功率]",                   hashDataFormatInfo.value("[电功率]"));
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
    // 光合
    hashDataFormatInfo.insert("[光量子]",                       new HDataFormatInfo("[光量子]", "umol/s", 0, 99999, 5));
    hashDataFormatInfo.insert("[光量子(380-780)]",              hashDataFormatInfo.value("[光量子]"));
    hashDataFormatInfo.insert("[光量子(400-700)]",              hashDataFormatInfo.value("[光量子]"));
    hashDataFormatInfo.insert("[光量子(700-800)]",              hashDataFormatInfo.value("[光量子]"));
    hashDataFormatInfo.insert("[光合光量子通量]",               new HDataFormatInfo("[光合光量子通量]", "umol/s", 0, 99999, 5));
    hashDataFormatInfo.insert("[光合有效辐射通量]",             new HDataFormatInfo("[光合有效辐射通量]", "mW", 0, 99999, 3));
    hashDataFormatInfo.insert("[光合光子通量效率]",             new HDataFormatInfo("[光合光子通量效率]", "umol/s/W", 0, 99999, 3));
    hashDataFormatInfo.insert("[荧光效能]",                     new HDataFormatInfo("[荧光效能]", "", 0, 99999, 3));
    hashDataFormatInfo.insert("[荧光蓝光比]",                   new HDataFormatInfo("[荧光蓝光比]", "", 0, 99999, 3));
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
    // 测试参数
    hashDataFormatInfo.insert("[测试时间]",                     new HDataFormatInfo("[测试时间]", "ms", 200, 30000, 1));
    hashDataFormatInfo.insert("[测试间隔]",                     new HDataFormatInfo("[测试间隔]", "s", 1, 3600, 1));
    // TM30
    hashDataFormatInfo.insert("[TM30_Rf]",                      new HDataFormatInfo("[TM30_Rf]", 0, 100, 1));
    hashDataFormatInfo.insert("[TM30_Rg]",                      new HDataFormatInfo("[TM30_Rg]", 0, 100, 1));
    hashDataFormatInfo.insert("[TM30_Rfi]",                     hashDataFormatInfo.value("[TM30_Rf]"));
    hashDataFormatInfo.insert("[TM30_hj_Rf]",                   hashDataFormatInfo.value("[TM30_Rf]"));
    hashDataFormatInfo.insert("[TM30_hj_Rcs]",                  new HDataFormatInfo("[TM30_hj_Rcs]", -50, 50, 1));
    hashDataFormatInfo.insert("[TM30_hj_Rhs]",                  new HDataFormatInfo("[TM30_hj_Rhs]", -0.5, 0.5, 3));
    hashDataFormatInfo.insert("[TM30_hj_at]",                   new HDataFormatInfo("[TM30_hj_at]", -40, 40, 2));
    hashDataFormatInfo.insert("[TM30_hj_bt]",                   hashDataFormatInfo.value("[TM30_hj_at]"));
    hashDataFormatInfo.insert("[TM30_hj_ar]",                   hashDataFormatInfo.value("[TM30_hj_at]"));
    hashDataFormatInfo.insert("[TM30_hj_br]",                   hashDataFormatInfo.value("[TM30_hj_at]"));
    hashDataFormatInfo.insert("[TM30_hj_atn]",                  new HDataFormatInfo("[TM30_hj_atn]", -150, 150, 2));
    hashDataFormatInfo.insert("[TM30_hj_btn]",                  hashDataFormatInfo.value("[TM30_hj_atn]"));
    hashDataFormatInfo.insert("[TM30_hj_arn]",                  hashDataFormatInfo.value("[TM30_hj_atn]"));
    hashDataFormatInfo.insert("[TM30_hj_brn]",                  hashDataFormatInfo.value("[TM30_hj_atn]"));


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
    hashDataCaption.insert("",                      tr(""));
    hashDataCaption.insert("[]",                    tr(""));

    hashDataCaption.insert("[光谱像元]",            tr("像元"));
    hashDataCaption.insert("[光谱波长]",            tr("波长"));

    hashDataCaption.insert("[峰值波长]",            tr("峰值波长"));
    hashDataCaption.insert("[峰值带宽]",            tr("峰值带宽"));
    hashDataCaption.insert("[主波长]",              tr("主波长"));
    hashDataCaption.insert("[色纯度]",              tr("色纯度"));
    hashDataCaption.insert("[色温]",                tr("色温"));
    hashDataCaption.insert("[显色指数Ra]",          tr("显色指数Ra"));
    hashDataCaption.insert("[显色指数R9]",          tr("显色指数R9"));
    hashDataCaption.insert("[显色指数Rx]",          tr("显色指数Rx"));
    hashDataCaption.insert("[色坐标]",              tr("色坐标"));
    hashDataCaption.insert("[色坐标uv]",            tr("色坐标uv"));
    hashDataCaption.insert("[色坐标uvp]",           tr("色坐标uvp"));
    hashDataCaption.insert("[色坐标x]",             tr("色坐标x"));
    hashDataCaption.insert("[色坐标y]",             tr("色坐标y"));
    hashDataCaption.insert("[色坐标u]",             tr("色坐标u"));
    hashDataCaption.insert("[色坐标v]",             tr("色坐标v"));
    hashDataCaption.insert("[色坐标up]",            tr("色坐标up"));
    hashDataCaption.insert("[色坐标vp]",            tr("色坐标vp"));
    hashDataCaption.insert("[Duv]",                 tr("Duv"));
    hashDataCaption.insert("[红色比]",              tr("红色比"));
    hashDataCaption.insert("[蓝色比]",              tr("蓝色比"));
    hashDataCaption.insert("[绿色比]",              tr("绿色比"));
    hashDataCaption.insert("[光谱能量百分比]",      tr("光谱能量百分比"));
    hashDataCaption.insert("[光谱光通量]",          tr("光通量"));

    hashDataCaption.insert("[色容差]",              tr("色容差"));

    hashDataCaption.insert("[输出电压]",            tr("输出电压"));
    hashDataCaption.insert("[输出电流]",            tr("输出电流"));
    hashDataCaption.insert("[反向电压]",            tr("反向电压"));
    hashDataCaption.insert("[实测电压]",            tr("实测电压"));
    hashDataCaption.insert("[实测电流]",            tr("实测电流"));
    hashDataCaption.insert("[反向漏流]",            tr("反向漏流"));
    hashDataCaption.insert("[电功率]",              tr("电功率"));
    hashDataCaption.insert("[交流电压]",            tr("交流电压"));
    hashDataCaption.insert("[交流电流]",            tr("交流电流"));
    hashDataCaption.insert("[交流电功率]",          tr("交流电功率"));
    hashDataCaption.insert("[功率因数]",            tr("功率因数"));

    hashDataCaption.insert("[光通量]",              tr("光通量"));
    hashDataCaption.insert("[光强度]",              tr("光强度"));
    hashDataCaption.insert("[光亮度]",              tr("光亮度"));
    hashDataCaption.insert("[光照度]",              tr("光照度"));
    hashDataCaption.insert("[光功率]",              tr("光功率"));
    hashDataCaption.insert("[光效率]",              tr("光效率"));

    hashDataCaption.insert("[光量子]",              tr("光量子"));
    hashDataCaption.insert("[光量子(380-780)]",     tr("光量子(380-780nm)"));
    hashDataCaption.insert("[光量子(400-700)]",     tr("光量子(400-700nm)"));
    hashDataCaption.insert("[光量子(700-800)]",     tr("光量子(700-800nm)"));
    hashDataCaption.insert("[光合光量子通量]",      tr("光合光量子通量"));
    hashDataCaption.insert("[光合有效辐射通量]",    tr("光合有效辐射通量"));
    hashDataCaption.insert("[光合光子通量效率]",    tr("光合光子通量效率"));
    hashDataCaption.insert("[荧光效能]",            tr("荧光效能"));
    hashDataCaption.insert("[荧光蓝光比]",          tr("荧光蓝光比"));

    hashDataCaption.insert("[测试日期时间]",        tr("测试时间"));
    hashDataCaption.insert("[测试日期]",            tr("测试日期"));
    hashDataCaption.insert("[测试时间]",            tr("测试时间"));
    hashDataCaption.insert("[测量日期时间]",        tr("测量时间"));
    hashDataCaption.insert("[测量日期]",            tr("测量日期"));
    hashDataCaption.insert("[测量时间]",            tr("测量时间"));
    hashDataCaption.insert("[制造厂商]",            tr("制造厂商"));
    hashDataCaption.insert("[产品型号]",            tr("产品型号"));
    hashDataCaption.insert("[产品名称]",            tr("产品名称"));
    hashDataCaption.insert("[测试单位]",            tr("测试单位"));
    hashDataCaption.insert("[测试员]",              tr("测试员"));
    hashDataCaption.insert("[备注]",                tr("备注"));
    hashDataCaption.insert("[样品编号]",            tr("样品编号"));
    hashDataCaption.insert("[环境温度]",            tr("环境温度"));
    hashDataCaption.insert("[环境湿度]",            tr("环境湿度"));
    hashDataCaption.insert("[分级]",                tr("分级"));

    hashDataCaption.insert("[TM30_Rf]",             tr("Rf"));
    hashDataCaption.insert("[TM30_Rg]",             tr("Rg"));
    hashDataCaption.insert("[TM30_Rfi]",            tr("Rfi"));
    hashDataCaption.insert("[TM30_hj_Rf]",          tr("hj_Rf"));
    hashDataCaption.insert("[TM30_hj_Rcs]",         tr("hj_Rcs"));
    hashDataCaption.insert("[TM30_hj_Rhs]",         tr("hj_Rhs"));
    hashDataCaption.insert("[TM30_hj_at]",          tr("hj_at"));
    hashDataCaption.insert("[TM30_hj_bt]",          tr("hj_bt"));
    hashDataCaption.insert("[TM30_hj_ar]",          tr("hj_ar"));
    hashDataCaption.insert("[TM30_hj_br]",          tr("hj_br"));
    hashDataCaption.insert("[TM30_hj_atn]",         tr("hj_atn"));
    hashDataCaption.insert("[TM30_hj_btn]",         tr("hj_btn"));
    hashDataCaption.insert("[TM30_hj_arn]",         tr("hj_arn"));
    hashDataCaption.insert("[TM30_hj_brn]",         tr("hj_brn"));
}

void HCoreGlobalInstance::initDataGroup()
{
    hashDataGroup.insert("|产品信息|",      QStringList() << "[制造厂商]" << "[产品名称]" << "[产品型号]"  << "[样品编号]" << "[测试单位]" << "[测试员]" << "[备注]");
    hashDataGroup.insert("|产品信息2|",     QStringList() << "[制造厂商]" << "[产品名称]" << "[产品型号]"  << "[样品编号]" << "[测试单位]" << "[测试员]");
    hashDataGroup.insert("|环境信息|",      QStringList() << "[环境温度]" << "[环境湿度]");
    hashDataGroup.insert("|时间信息|",      QStringList() << "[测量日期时间]");
    hashDataGroup.insert("|时间信息2|",     QStringList() << "[测量日期]" << "[测量时间]");
    hashDataGroup.insert("|光谱信息|",      QStringList() << "[峰值波长]" << "[峰值带宽]" << "[主波长]"
                                                          << "[色坐标]" << "[色坐标x]" << "[色坐标y]" << "[色坐标uv]" << "[色坐标u]" << "[色坐标v]" << "[色坐标uvp]" << "[色坐标up]" << "[色坐标vp]"
                                                          << "[色温]" << "[色纯度]" << "[Duv]" << "[光谱光通量]"
                                                          << "[红色比]" << "[绿色比]" << "[蓝色比]"
                                                          << "[显色指数Ra]" << "[显色指数R9]" << "[显色指数Rx]"
                                                          << "[光谱能量曲线]" << "[光谱反射曲线]");
    hashDataGroup.insert("|光谱信息2|",     QStringList() << "[峰值波长]" << "[峰值带宽]" << "[主波长]"
                                                          << "[色坐标]" << "[色坐标x]" << "[色坐标y]" << "[色坐标uvp]" << "[色坐标up]" << "[色坐标vp]"
                                                          << "[色温]" << "[色纯度]" << "[Duv]" << "[光谱光通量]"
                                                          << "[红色比]" << "[绿色比]" << "[蓝色比]"
                                                          << "[显色指数Ra]" << "[显色指数R9]" << "[显色指数Rx]"
                                                          << "[光谱能量曲线]" << "[光谱反射曲线]");
    hashDataGroup.insert("|光谱信息3|",     QStringList() << "[峰值波长]" << "[峰值带宽]" << "[主波长]"
                                                          << "[色坐标]" << "[色坐标x]" << "[色坐标y]" << "[色坐标uvp]" << "[色坐标up]" << "[色坐标vp]"
                                                          << "[色温]" << "[色纯度]" << "[Duv]" << "[光谱光通量]"
                                                          << "[红色比]" << "[绿色比]" << "[蓝色比]"
                                                          << "[显色指数Ra]" << "[显色指数R9]" << "[显色指数Rx]");
    hashDataGroup.insert("|光度信息|",      QStringList() << "[光通量]" << "[光功率]" << "[光效率]");
    hashDataGroup.insert("|光度信息2|",     QStringList() << "[光功率]" << "[光效率]");
    hashDataGroup.insert("|光合信息|",      QStringList() << "[光量子(380-780)]" << "[光量子(400-700)]" << "[光量子(700-800)]"
                                                          << "[光合光量子通量]" << "[光合有效辐射通量]" << "[光合光子通量效率]"
                                                          << "[荧光效能]" << "[荧光蓝光比]");
    hashDataGroup.insert("|色容差信息|",    QStringList() << "[色容差标准]" << "[色容差]");
    hashDataGroup.insert("|色容差信息2|",   QStringList() << "[色容差]");
    hashDataGroup.insert("|TM30信息|",      QStringList() << "[TM30_Rf]" << "[TM30_Rg]" << "[TM30_Rfi]"
                                                          << "[TM30_hj_Rf]" << "[TM30_hj_Rcs]" << "[TM30_hj_Rhs]"
                                                          << "[TM30_hj_at]" << "[TM30_hj_bt]" << "[TM30_hj_ar]" << "[TM30_hj_br]"
                                                          << "[TM30_hj_atn]" << "[TM30_hj_btn]" << "[TM30_hj_arn]" << "[TM30_hj_brn]");
    hashDataGroup.insert("|直流电信息|",    QStringList() << "[输出电压]" << "[实测电压]" << "[输出电流]" << "[实测电流]" << "[反向电压]" << "[反向漏流]" << "[电功率]");
    hashDataGroup.insert("|直流电信息2|",   QStringList() << "[输出电压]" << "[实测电压]" << "[输出电流]" << "[实测电流]" << "[电功率]");
    hashDataGroup.insert("|交流电信息|",    QStringList() << "[交流电压]" << "[交流电流]" << "[交流电功率]" << "[功率因数]");
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

HE_END_NAMESPACE
