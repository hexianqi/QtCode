#include "HVlcPlayer_p.h"
#include "ui_HVlcPlayer.h"
#include "HControlHelper.h"
#include "HFlatStyle.h"
#include "HVlcPlayerControl.h"
#include "HSoundWidget.h"
#include <QtWidgets/QFileDialog>
#include <QtCore/QDebug>

HE_CONTROL_BEGIN_NAMESPACE

HVlcPlayerPrivate::HVlcPlayerPrivate()
{
    fileFilter.append("Common media formats(");
    fileFilter.append("*.avi;*.wmv;*.wmp;*.wm;*.asf;");
    fileFilter.append("*.wma;*.wav;*.aif;*.aiff;*.aifc;*.mid;*.midi;");
    fileFilter.append("*.rm;*.ram;*.rmvb;*.rpm;*.ra;*.rt;*.smi;*.smil;*.scm;");
    fileFilter.append("*.mpg;*.mpeg;*.mpe;*.m1v;*.m2v;*.mpv2;*.mp2v;*.dat;*.mp4;*.m4v;*.m4p;*.m4b;*.ts;*.tp;*.tpr;*.pva;*.pss;*.wv;");
    fileFilter.append("*.mpa;*.mp2;*.m1a;*.m2a;*.m4a;*.aac;*.m2ts;*.evo;");
    fileFilter.append("*.vob;*.ac3;*.dts;");
    fileFilter.append("*.mp3;");
    fileFilter.append("*.mov;*.qt;*.mr;*.3gp;*.3gpp;*.3g2;*.3gp2;");
    fileFilter.append("*.swf;");
    fileFilter.append("*.au;*.ogm;*.ogg;*.flic;*.mkv;*.pmp;*.smk;*.dsm;*.dsv;*.dsa;*.dss;*.amr;");
    fileFilter.append("*.realpix;*.amv;*.acc);;");
    fileFilter.append("Windows Media Video(*.avi;*.wmv;*.wmp;*.wm;*.asf);;");
    fileFilter.append("Windows Media Audio(*.wma;*.wav;*.aif;*.aifc;*.aiff;*.mid;*.midi;*.rmi);;");
    fileFilter.append("Real(*.rm;*.ram;*.rmvb;*.rpm;*.ra;*.rt;*.rp;*.smi;*.smil;*.scm);;");
    fileFilter.append("MPEG Video(*.mpg;*.mpeg;*.mpe;*.m1v;*.m2v;*.mpv2;*.mp2v;*.dat;*.mp4;*.m4v;*.m4p;*.m4b;*.ts;*.tp;*.tpr;*.pva;*.pss;*.wv);;");
    fileFilter.append("MPEG Audio(*.mpa;*.mp2;*.m1a;*.m2a;*.m4a;*.aac;*.m2ts;*.evo);;");
    fileFilter.append("DVD(*.vob;*.ifo;*.ac3;*.dts);;");
    fileFilter.append("CD Tracks(*.cda);;");
    fileFilter.append("MP3(*.mp3);;");
    fileFilter.append("Quicktime(*.mov;*.qt;*.mr;*.3gp;*.3gpp;*.3g2;*.3gp2);;");
    fileFilter.append("Flash Files(*.flv;*.swf;*.f4v);;");
    fileFilter.append("Playlist(*.smpl;*.asx;*.m3u;*.pls;*.wvx;*.wax;*.wmx;*.mpcpl);;");
    fileFilter.append("Others(*.ivf;*.au;*.snd;*.ogm;*.ogg;*.fli;*.flc;*.flic;*.d2v;*.mkv;*.pmp;*.mka;*.smk;*.bik;*.ratdvd;*.roq;*.drc;*.dsm;*.dsv;*.dsa;*.dss;*.mpc;*.divx;*.vp6;*.ape;*.amr;*.flac;*.tta;*.csf);;");
    fileFilter.append("All Files(*.*)");
}

HVlcPlayer::HVlcPlayer(QWidget *parent) :
    QMainWindow(parent),
    d_ptr(new HVlcPlayerPrivate),
    ui(new Ui::HVlcPlayer)
{
    ui->setupUi(this);
    init();
}

HVlcPlayer::~HVlcPlayer()
{
    d_ptr->control->close();
    delete ui;
}

void HVlcPlayer::on_action_101_triggered(bool /*checked*/)
{
    auto fileName = QFileDialog::getOpenFileUrl(nullptr, tr("打开文件"), QUrl(), d_ptr->fileFilter);
    if (fileName.isEmpty())
        return;
    d_ptr->control->setUrl(fileName.toString());
    ui->pushButton_1->setEnabled(true);
}

void HVlcPlayer::init()
{
    auto sound = new HSoundWidget(true, false, this);
    d_ptr->style = new HFlatStyle(this);
    d_ptr->style->setStyle(ui->slider, 8, "#505050", "#1ABC9C", "#1ABC9C");
    d_ptr->control = new HVlcPlayerControl(this);
    d_ptr->control->setVideoWindow(ui->widget);
    ui->slider->setMaximum(1000);
    ui->horizontalLayout_2->addWidget(sound);

    connect(sound, &HSoundWidget::mutedChanged, d_ptr->control, &HVlcPlayerControl::setMute);
    connect(sound, &HSoundWidget::volumeChanged, d_ptr->control, &HVlcPlayerControl::setVolume);
    connect(ui->pushButton_1, &QPushButton::clicked, d_ptr->control, &HVlcPlayerControl::play);
    connect(ui->pushButton_2, &QPushButton::clicked, d_ptr->control, &HVlcPlayerControl::pause);
    connect(ui->pushButton_3, &QPushButton::clicked, d_ptr->control, &HVlcPlayerControl::stop);
    connect(d_ptr->control, &HVlcPlayerControl::mutedChanged, this, [=](bool b) { sound->setMuted(b); });
    connect(d_ptr->control, &HVlcPlayerControl::volumeChanged, this, [=](double value) { sound->setVolume(value * 100); });
    connect(d_ptr->control, &HVlcPlayerControl::positionChanged, this, [=](double value) { ui->slider->setValue(value * 1000); });
    connect(d_ptr->control, &HVlcPlayerControl::timeChanged, this, [=](qlonglong value) { ui->label_1->setText(HControlHelper::secsToTime(value/1000)); });
    connect(d_ptr->control, &HVlcPlayerControl::durationChanged, this, [=](qlonglong value) { ui->label_2->setText(HControlHelper::secsToTime(value/1000)); });
    connect(d_ptr->control, &HVlcPlayerControl::stateChanged, this, &HVlcPlayer::handleStateChanged);
}

void HVlcPlayer::handleStateChanged(int value)
{
    if (value == HVlcPlayerControl::Stopped)
    {
        ui->pushButton_1->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->slider->setEnabled(false);
        ui->slider->setValue(0);
        ui->label_1->setText(HControlHelper::secsToTime(0));
        return;
    }
    if (value == HVlcPlayerControl::Playing)
    {
        ui->pushButton_1->setEnabled(false);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->slider->setEnabled(true);
        return;
    }
    if (value == HVlcPlayerControl::Paused)
    {
        ui->pushButton_1->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(true);
        ui->slider->setEnabled(true);
        return;
    }
}

HE_CONTROL_END_NAMESPACE
