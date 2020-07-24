#include "HControlDemoWidget_p.h"
#include "HFFmpegWidget.h"
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>

#include "HFFPlayerControl_old.h"
#include "HFFPlayerService.h"

HE_CONTROL_BEGIN_NAMESPACE

void HControlDemoWidget::addFFmpeg()
{
//    auto ffplay = new HFFPlayerControl(this);
    auto service = new HFFPlayerService(this);
    auto ffmpeg = new HFFmpegWidget;
    auto comboBox = new QComboBox;
    auto pushButton = new QPushButton("打开");
    auto layout = new QGridLayout;
    comboBox->addItem("media\\Titanic.ts");
    comboBox->addItem("rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov");
    comboBox->addItem("empty");
    layout->addWidget(ffmpeg, 0, 0, 1, 2);
    layout->addWidget(comboBox, 1, 0);
    layout->addWidget(pushButton, 1, 1);
    layout->setColumnStretch(0, 10);
    connect(pushButton, &QPushButton::clicked, this, [=]{
            if (pushButton->text() == "打开")
            {
                pushButton->setText("关闭");
                service->load(comboBox->currentText().trimmed());
                service->play();
//                ffplay->setUrl(comboBox->currentText().trimmed());
//                ffplay->play();
//                ffmpeg->setUrl(comboBox->currentText().trimmed());
//                ffmpeg->open();

            }
            else
            {
                pushButton->setText("打开");
//                ffmpeg->close();
            }
    });
    addTab(tr("FFmpeg"), tr("FFmpeg"), layout);
}

HE_CONTROL_END_NAMESPACE
