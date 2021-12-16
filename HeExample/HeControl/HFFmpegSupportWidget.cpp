#include "HFFmpegSupportWidget_p.h"
#include "HFFmpeg.h"
#include "HFFmpegUtil.h"
#include "HePlugin/HEntireTableWidget.h"
#include <QtCore/QTimer>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QGridLayout>

HE_BEGIN_NAMESPACE

HFFmpegSupportWidget::HFFmpegSupportWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HFFmpegSupportWidgetPrivate)
{
    init();
    QTimer::singleShot(10, this, &HFFmpegSupportWidget::showInfo);
}

HFFmpegSupportWidget::~HFFmpegSupportWidget()
{
}

void HFFmpegSupportWidget::init()
{
    auto types = QStringList() << tr("协议") << tr("输入封装格式") << tr("输出封装格式")
                               << tr("视频解码器") << tr("音频解码器") << tr("其他解码器")
                               << tr("滤镜") << tr("BSF");
    QList<QStringList> headers;
    headers.append(QStringList() << tr("名称") << tr("类型"));
    headers.append(QStringList() << tr("简称") << tr("全称") << tr("扩展名") << tr("私有数据大小"));
    headers.append(QStringList() << tr("简称") << tr("全称") << tr("扩展名") << tr("私有数据大小"));
    headers.append(QStringList() << tr("简称") << tr("全称") << tr("支持帧率") << tr("支持像素格式") << tr("私有数据大小"));
    headers.append(QStringList() << tr("简称") << tr("全称") << tr("支持采样率") << tr("支持采样格式") << tr("私有数据大小"));
    headers.append(QStringList() << tr("简称") << tr("全称") << tr("私有数据大小"));
    headers.append(QStringList() << tr("名称") << tr("描述") << tr("私有数据大小"));
    headers.append(QStringList() << tr("名称") << tr("私有数据大小"));
    auto layout = new QGridLayout(this);
    auto tabWidget = new QTabWidget();
    for (int i = 0; i < types.size(); i++)
    {
        auto widget = new HEntireTableWidget();
        widget->setHorizontalHeaderLabels(headers.at(i));
        widget->setSelectionBehavior(QAbstractItemView::SelectRows);
        widget->setSortingEnabled(true);
        widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tabWidget->addTab(widget, types.at(i));
        d_ptr->tableWidgets << widget;
    }
    layout->addWidget(tabWidget);
}

void HFFmpegSupportWidget::showInfo()
{
    showProtocol();
    showInputFormat();
    showOutputFormat();
    showCodec();
    showFilter();
    showBSF();
    for (auto widget : d_ptr->tableWidgets)
        widget->resizeRowsToContents();
}

void HFFmpegSupportWidget::showProtocol()
{
    auto protocol0 = HFFmpegUtil::getProtocol(0).toSet();
    auto protocol1 = HFFmpegUtil::getProtocol(1).toSet();
    auto protocol2 = protocol0 & protocol1;
    protocol0 -= protocol2;
    protocol1 -= protocol2;
    for (auto v : protocol0)
        d_ptr->tableWidgets.at(0)->insertRow(0, QStringList() << v << tr("输出"));
    for (auto v : protocol1)
        d_ptr->tableWidgets.at(0)->insertRow(0, QStringList() << v << tr("输入"));
    for (auto v : protocol2)
        d_ptr->tableWidgets.at(0)->insertRow(0, QStringList() << v << tr("输入|输出"));
}

void HFFmpegSupportWidget::showInputFormat()
{
    for (auto v : HFFmpegUtil::getInputFormat())
        d_ptr->tableWidgets.at(1)->insertRow(0, QStringList() << v->name << v->long_name << v->extensions << QString::number(v->priv_data_size));
}

void HFFmpegSupportWidget::showOutputFormat()
{
    for (auto v : HFFmpegUtil::getOutputFormat())
        d_ptr->tableWidgets.at(2)->insertRow(0, QStringList() << v->name << v->long_name << v->extensions << QString::number(v->priv_data_size));
}

void HFFmpegSupportWidget::showCodec()
{
    for (auto v : HFFmpegUtil::getCodec())
    {
        if (v->type == AVMEDIA_TYPE_VIDEO)
        {
            QString rate = v->supported_framerates == nullptr ? "Any" : QString::number(1.0 * v->supported_framerates->num / v->supported_framerates->den);
            QString format = "Unknown";
            if (v->pix_fmts != nullptr)
            {
                QStringList list;
                for (auto i = v->pix_fmts; *i != -1; i++)
                    list << av_get_pix_fmt_name(*i);
                format = list.join(';');
            }
            d_ptr->tableWidgets.at(3)->insertRow(0, QStringList() << v->name << v->long_name << rate << format << QString::number(v->priv_data_size));
        }
        else if (v->type == AVMEDIA_TYPE_AUDIO)
        {
            QString rate = "Unknown";
            QString format = "Unknown";
            if (v->supported_samplerates != nullptr)
            {
                QStringList list;
                for (auto i = v->supported_samplerates; *i != 0; i++)
                    list << QString::number(*i);
                rate = list.join(';');
            }
            if (v->sample_fmts != nullptr)
            {
                QStringList list;
                for (auto i = v->sample_fmts; *i != -1; i++)
                    list << av_get_sample_fmt_name(*i);
                format = list.join(';');
            }
            d_ptr->tableWidgets.at(4)->insertRow(0, QStringList() << v->name << v->long_name << rate << format << QString::number(v->priv_data_size));
        }
        else
            d_ptr->tableWidgets.at(5)->insertRow(0, QStringList() << v->name << v->long_name << QString::number(v->priv_data_size));
    }
}

void HFFmpegSupportWidget::showFilter()
{
    for (auto v : HFFmpegUtil::getFilter())
        d_ptr->tableWidgets.at(6)->insertRow(0, QStringList() << v->name << v->description << QString::number(v->priv_size));

}

void HFFmpegSupportWidget::showBSF()
{
    for (auto v : HFFmpegUtil::getBSF())
        d_ptr->tableWidgets.at(7)->insertRow(0, QStringList() << v->name << QString::number(v->priv_data_size));
}

HE_END_NAMESPACE
