#include "HOpenGLDemoWidget_p.h"
#include "HOpenGLWidget.h"
#include "ui_HOpenGLDemoWidget.h"
#include <QtCore/QMultiHash>

HE_CONTROL_BEGIN_NAMESPACE

HOpenGLDemoWidget::HOpenGLDemoWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HOpenGLDemoWidgetPrivate),
    ui(new Ui::HOpenGLDemoWidget)
{
    ui->setupUi(this);
    init();
}

HOpenGLDemoWidget::HOpenGLDemoWidget(HOpenGLDemoWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

void HOpenGLDemoWidget::on_treeWidget_itemSelectionChanged()
{
    auto value = ui->treeWidget->currentItem()->data(0, Qt::UserRole).toString();
    d_ptr->widget->setDisplay(value);
}

HOpenGLDemoWidget::~HOpenGLDemoWidget()
{
    delete ui;
}

void HOpenGLDemoWidget::init()
{
    d_ptr->widget = new HOpenGLWidget;
    ui->splitter_1->addWidget(d_ptr->widget);
    ui->splitter_1->setStretchFactor(1, 10);
    ui->splitter_2->setStretchFactor(1, 10);
    ui->treeWidget->setStyleSheet("QTreeWidget::item { height:25px }");

    QMultiMap<QString, QStringList> map;
    map.insertMulti(tr("1.入门"), QStringList() << tr("1.三角形") << "Triangle");
    map.insertMulti(tr("1.入门"), QStringList() << tr("2.纹理") << "Texture");
    map.insertMulti(tr("1.入门"), QStringList() << tr("3.纹理混合") << "TextureBlend");
    map.insertMulti(tr("1.入门"), QStringList() << tr("4.坐标") << "CoordinateSystem");
    map.insertMulti(tr("2.光照"), QStringList() << tr("1.颜色") << "Color");
    map.insertMulti(tr("2.光照"), QStringList() << tr("2.基础光照") << "Light");
    map.insertMulti(tr("2.光照"), QStringList() << tr("3.光照材质") << "LightMaterials");
    map.insertMulti(tr("2.光照"), QStringList() << tr("4.光照贴图") << "LightMaps");
    map.insertMulti(tr("2.光照"), QStringList() << tr("5.1投光物 - 平行光源") << "LightCasterDirectional");
    map.insertMulti(tr("2.光照"), QStringList() << tr("5.2投光物 - 点光源") << "LightCasterPoint");
    map.insertMulti(tr("2.光照"), QStringList() << tr("5.3投光物 - 聚光源") << "LightCasterSpot");
    map.insertMulti(tr("2.光照"), QStringList() << tr("5.4投光物 - 多光源") << "LightCasterMulti");
    map.insertMulti(tr("3.模型"), QStringList() << tr("1.模型") << "Model");
    map.insertMulti(tr("4.高级"), QStringList() << tr("1.深度测试") << "Depth");
    map.insertMulti(tr("4.高级"), QStringList() << tr("2.模版测试") << "Stencil");
    map.insertMulti(tr("4.高级"), QStringList() << tr("3.混合") << "Blending");
    map.insertMulti(tr("4.高级"), QStringList() << tr("4.帧缓存") << "Framebuffer");
    map.insertMulti(tr("4.高级"), QStringList() << tr("5.立方体贴图") << "Cubemaps");
    map.insertMulti(tr("4.高级"), QStringList() << tr("6.Uniform缓冲对象") << "Ubo");
    map.insertMulti(tr("4.高级"), QStringList() << tr("7.1.几何着色器") << "GeometryHouse");
    map.insertMulti(tr("4.高级"), QStringList() << tr("7.2.几何着色器 - 爆破") << "GeometryExplode");
    map.insertMulti(tr("4.高级"), QStringList() << tr("7.3.几何着色器 - 法向量可视化 ") << "GeometryNormal");
    map.insertMulti(tr("4.高级"), QStringList() << tr("8.1.实例化") << "Instancing");
    map.insertMulti(tr("4.高级"), QStringList() << tr("8.2.实例化 - 小行星带") << "InstancingModel");
    map.insertMulti(tr("4.高级"), QStringList() << tr("9.抗锯齿") << "AntiAliasing");
    map.insertMulti(tr("5.高级光照"), QStringList() << tr("1.Blinn") << "LightBlinn");
    map.insertMulti(tr("5.高级光照"), QStringList() << tr("2.Gamma") << "LightGamma");
    map.insertMulti(tr("5.高级光照"), QStringList() << tr("3.1.阴影映射 - 深度") << "ShadowDepth");
    map.insertMulti(tr("5.高级光照"), QStringList() << tr("3.2.阴影映射 - 平行光源") << "ShadowMapping");
    map.insertMulti(tr("5.高级光照"), QStringList() << tr("3.2.阴影映射 - 点光源") << "ShadowPoint");
    map.insertMulti(tr("5.高级光照"), QStringList() << tr("4.法线贴图") << "NormalMapping");
    map.insertMulti(tr("5.高级光照"), QStringList() << tr("5.视差贴图") << "ParallaxMapping");
    map.insertMulti(tr("5.高级光照"), QStringList() << tr("6.HDR") << "HDR");
    map.insertMulti(tr("5.高级光照"), QStringList() << tr("7.Bloom") << "Bloom");
    map.insertMulti(tr("5.高级光照"), QStringList() << tr("8.延时着色") << "DeferredShading");
    map.insertMulti(tr("5.高级光照"), QStringList() << tr("9.SSAO") << "SSAO");
    map.insertMulti(tr("6.PBR"), QStringList() << tr("1.PBR") << "PBR");
    map.insertMulti(tr("6.PBR"), QStringList() << tr("2.PBR2") << "PBR2");
    map.insertMulti(tr("6.PBR"), QStringList() << tr("3.PBR3") << "PBR3");
    map.insertMulti(tr("6.PBR"), QStringList() << tr("4.PBR4") << "PBR4");
    map.insertMulti(tr("6.PBR"), QStringList() << tr("5.PBR5") << "PBR5");
    map.insertMulti(tr("6.PBR"), QStringList() << tr("6.PBR6") << "PBR6");
    map.insertMulti(tr("7.其他"), QStringList() << tr("1.文本") << "Text");

    for (auto key : map.uniqueKeys())
    {
        auto values = map.values(key);
        std::sort(values.begin(), values.end());
        auto item1 = new QTreeWidgetItem(ui->treeWidget->invisibleRootItem());
        item1->setText(0, key);
        item1->setData(0, Qt::UserRole, values.at(0).at(1));
        for (auto v : values)
        {
            auto item2 = new QTreeWidgetItem(item1);
            item2->setText(0, v.at(0));
            item2->setData(0, Qt::UserRole, v.at(1));
        }
    }
     ui->checkBox_1->setChecked(true);
     ui->checkBox_2->setChecked(true);
     connect(ui->checkBox_1, &QCheckBox::clicked, d_ptr->widget, &HOpenGLWidget::setLightPosLoop);
     connect(ui->checkBox_2, &QCheckBox::clicked, d_ptr->widget, &HOpenGLWidget::setLightColorLoop);
     connect(ui->checkBox_3, &QCheckBox::clicked, d_ptr->widget, &HOpenGLWidget::setLinearize);
     connect(ui->checkBox_4, &QCheckBox::clicked, d_ptr->widget, &HOpenGLWidget::setBlinn);
     connect(ui->checkBox_5, &QCheckBox::clicked, d_ptr->widget, &HOpenGLWidget::setGamma);
     connect(ui->checkBox_6, &QCheckBox::clicked, d_ptr->widget, &HOpenGLWidget::setShadows);
     connect(ui->checkBox_7, &QCheckBox::clicked, d_ptr->widget, &HOpenGLWidget::setHdr);
     connect(ui->checkBox_8, &QCheckBox::clicked, d_ptr->widget, &HOpenGLWidget::setBloom);
     connect(ui->horizontalSlider_1, &QSlider::valueChanged, this, [=](int value) { d_ptr->widget->setHeightScale(value * 0.001); });
     connect(ui->horizontalSlider_2, &QSlider::valueChanged, this, [=](int value) { d_ptr->widget->setExposure(value * 0.01); });
}

HE_CONTROL_END_NAMESPACE
