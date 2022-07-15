#include "frmbaseset.h"
#include "ui_frmbaseset.h"
#include "qstandarditemmodel.h"
#include "combodelegate.h"
#include "unitpublic.h"
#include "unitprofile.h"
#include "qmessagebox.h"
#include "qdebug.h"

FrmBaseSet::FrmBaseSet(qint8 iindex,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmBaseSet)
{
    ui->setupUi(this);
    itag = iindex;      //注意下标

    this->setGeometry(0,0,parent->geometry().width(),parent->geometry().height());          //填充整个父窗口
    ui->gbledset->setGeometry(0,0,this->geometry().width(),ui->gbledset->height());     //LED设置选项窗口布局
    ui->tvtestitem1->setGeometry(0,ui->gbledset->height(),this->geometry().width()/2,(this->geometry().height()-ui->gbledset->height())/2);
    ui->tvtestitem2->setGeometry(this->geometry().width()/2,ui->gbledset->height(),this->geometry().width()/2,(this->geometry().height()-ui->gbledset->height())/2);
    ui->tvtestitem3->setGeometry(0,ui->tvtestitem1->geometry().height()+ui->gbledset->height(),this->geometry().width()/2,(this->geometry().height()-ui->gbledset->height())/2);
    ui->tvtestitem4->setGeometry(this->geometry().width()/2,ui->tvtestitem1->geometry().height()+ui->gbledset->height(),this->geometry().width()/2,(this->geometry().height()-ui->gbledset->height())/2);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);//设置子窗口属性

    tvDispInit(0,ui->tvtestitem1);   //初始化列表数据
    tvDispInit(1,ui->tvtestitem2);   //初始化列表数据
    tvDispInit(2,ui->tvtestitem3);   //初始化列表数据
    basesetdisp();//显示基本参数

  //  ui->spoptjifen->setVisible(false);      //隐藏，暂时不用
  //  ui->spoptyanshi->setVisible(false);
  //  ui->label_2->setVisible(false);
  //  ui->label_3->setVisible(false);

    QDoubleValidator*validator=new QDoubleValidator(0,999999,2,this);        //坐标值输入框，范围0-999999，2位小数
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->edtvf->setValidator(validator);
    ui->edtma->setValidator(validator);
    ui->edtvfmax->setValidator(validator);
    ui->edtvfmin->setValidator(validator);
}

FrmBaseSet::~FrmBaseSet()
{
    delete ui;
}

//tableview移动行数据
void FrmBaseSet::moveRow(QTableView *tableView, int currentRow, int toRow)
{
    if( currentRow == toRow ){
        return;
    }

    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(tableView->model());
    if (model == nullptr) {
        return;
    }

    int column = tableView->currentIndex().column();
    if(nullptr == model || currentRow < 0 || currentRow > model->rowCount()-1)
    {
        return ;
    }

    if( currentRow < toRow ){
        //下移需要判断最后一行，不移动
        if(currentRow == model->rowCount()-1)
        {
            return ;
        }
    }else{
        //上移需要判断是否第一行，不移动
        if(0 == currentRow)
        {
            return ;
        }
    }

    QList<QStandardItem *> listItem = model->takeRow(currentRow);
    model->insertRow(toRow,listItem);

    tableView->setCurrentIndex( model->index(toRow, column) );
    tableView->selectRow(toRow);
}

//数据列表显示初始化，定义列字段标题、列数量等
//不同的测试工位，取对应工位的测试设置参数进行初始化显示
void FrmBaseSet::tvDispInit(int led_index,QTableView* tvtestitem)
{
    QStandardItemModel *model = new QStandardItemModel();

    model->setColumnCount(13);  //列数量根据该工位选择的测试参数确定，比如VF/IR/IV/CIE_X/CIE_Y/CCT/Ra/WD/WP，表示有9个测试对象
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("晶片"));         //为什么用fromLocal8Bit会乱码，
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("项目"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("是否测试"));   //是否显示该列
    model->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("是否分级"));
    model->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("校准方式"));
    model->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("电压(V)"));
    model->setHeaderData(6,Qt::Horizontal,QString::fromUtf8("电流(mA)"));
    model->setHeaderData(7,Qt::Horizontal,QString::fromUtf8("良品上限"));
    model->setHeaderData(8,Qt::Horizontal,QString::fromUtf8("良品下限"));
    model->setHeaderData(9,Qt::Horizontal,QString::fromUtf8("延时(ms)"));
    model->setHeaderData(10,Qt::Horizontal,QString::fromUtf8("积分(ms)"));
    model->setHeaderData(11,Qt::Horizontal,QString::fromUtf8("量程"));
    model->setHeaderData(12,Qt::Horizontal,QString::fromUtf8("等外BIN"));

    tvtestitem->setModel(model);
    tvtestitem->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "color: black;"          //文字颜色
                                                     "font:bold 9pt;"      //字体大小
                                                     "padding-left: 2px;"
                                                     "border: 1px solid #6c6c6c;}");

    tvtestitem->setEditTriggers(QAbstractItemView::NoEditTriggers);  //不可编辑
    tvtestitem->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    tvtestitem->verticalHeader()->hide();
    //表头信息显示居左
    tvtestitem->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    tvtestitem->verticalHeader()->setDefaultSectionSize(18); //行高
        //设置列宽不可变
    //ui->tvtestdata->horizontalHeader()->setStretchLastSection(true); //设置最后一列填充整个表头
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //均分所有列，宽度

    //初始化列宽，因为列宽设置要在插入数据时才生效，所以先插入一行空记录，后面清空就好
    for(int i=0;i<model->columnCount();i++){
        model->setItem(0,i,new QStandardItem(""));
        if(i==4){
            tvtestitem->setColumnWidth(i,80);   //校准方式

        }else{
            tvtestitem->setColumnWidth(i,60);
        }
    }
    tvtestitem->model()->removeRows(0,1);    //删除这个空行

    //显示参数内容
    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate();
    tvtestitem->setEditTriggers(QAbstractItemView::AllEditTriggers);  //双击选中某个单元格时进入编辑状态
    tvtestitem->setSelectionBehavior(QAbstractItemView::SelectItems);//设置选中模式为选单元格
    for (int i=0;i<TESTITEM_COUNT;i++) {
        model->setItem(i,0,new QStandardItem(QString("晶%1").arg(led_index+1)));   //晶1,2,3
        model->setItem(i,1,new QStandardItem(lstTestItemName[i]));    //测试项目名称
        model->setItem(i,2,new QStandardItem(""));    //是否分级
        model->item(i,2)->setCheckable(true);
        if(unitprofile::testitempara[itag][led_index][i].test_enable){
            model->item(i,2)->setCheckState(Qt::Checked); //是否测试（显示）
        }else
        {
            model->item(i,2)->setCheckState(Qt::Unchecked);
        }
        model->setItem(i,3,new QStandardItem(""));    //是否分级
        model->item(i,3)->setCheckable(true);
        if(unitprofile::testitempara[itag][led_index][i].bin_enable){
            model->item(i,3)->setCheckState(Qt::Checked); //是否分级
        }else
        {
            model->item(i,3)->setCheckState(Qt::Unchecked); //是否分级
        }
        QStringList lstjiaozhun; //校准方式
        lstjiaozhun.append("0,不校准");
        lstjiaozhun.append("1,线性校准");
        lstjiaozhun.append("2,offset偏移");
        lstjiaozhun.append("3,多点拟合");
        ComboDelegate* comboeelegatejiaozhun = new ComboDelegate(lstjiaozhun);
        tvtestitem->setItemDelegateForColumn(4,comboeelegatejiaozhun);
        model->setItem(i,4,new QStandardItem(lstjiaozhun.at(unitprofile::testitempara[itag][led_index][i].verify_type)));         //校准方式
        model->setItem(i,5,new QStandardItem(QString("%1").arg(unitprofile::testitempara[itag][led_index][i].vf_val)));         //电压
        model->setItem(i,6,new QStandardItem(QString("%1").arg(unitprofile::testitempara[itag][led_index][i].if_val)));       //电流
        model->setItem(i,7,new QStandardItem(QString("%1").arg(unitprofile::testitempara[itag][led_index][i].ok_max)));      //良品上限
        model->setItem(i,8,new QStandardItem(QString("%1").arg(unitprofile::testitempara[itag][led_index][i].ok_min)));      //良品下限
        model->setItem(i,9,new QStandardItem(QString("%1").arg(unitprofile::testitempara[itag][led_index][i].time_delay)));         //延时
        if((lstTestItemName.at(i) == "VF")||(lstTestItemName.at(i) == "VFL")||(lstTestItemName.at(i) == "IR")||(lstTestItemName.at(i) == "IV")){
            model->item(i,9)->setData(QColor(255, 255, 255), Qt::BackgroundRole);   //VF/VFL/IR/IV 需要设置延时，其他不需要用灰色背景标识
        }else{
            model->item(i,9)->setData(QColor(200,200,200), Qt::BackgroundRole);
        }
        model->setItem(i,10,new QStandardItem(QString("%1").arg(unitprofile::testitempara[itag][led_index][i].time_opt)));         //光谱积分
        if(lstTestItemName.at(i) == "WD"){
            model->item(i,10)->setData(QColor(255, 255, 255), Qt::BackgroundRole);   //主波长表示光谱测试，需要设置积分时间，其他不需要设置用灰色背景标识
        }else{
            model->item(i,10)->setData(QColor(200,200,200), Qt::BackgroundRole);
        }
        QStringList lstliangcheng; //量程
        lstliangcheng.append("0");
        lstliangcheng.append("1");
        lstliangcheng.append("2");
        lstliangcheng.append("3");
        ComboDelegate* comboeelegateliangcheng = new ComboDelegate(lstliangcheng);
        tvtestitem->setItemDelegateForColumn(11,comboeelegateliangcheng);
        model->setItem(i,11,new QStandardItem(QString("%1").arg(unitprofile::testitempara[itag][led_index][i].range_iv)));         //亮度量程
        if(lstTestItemName.at(i) == "IV"){
            model->item(i,11)->setData(QColor(255, 255, 255), Qt::BackgroundRole);  //IV亮度有量程档位设置，其他不需要用灰色背景标识
        }else{
            model->item(i,11)->setData(QColor(200,200,200), Qt::BackgroundRole);
        }
        model->setItem(i,12,new QStandardItem(QString("%1").arg(unitprofile::testitempara[itag][led_index][i].bin_out))); //超出上下限的等外BIN号
    }
    tvtestitem->setItemDelegateForColumn(0,readOnlyDelegate); //只读，晶1、2、3
    tvtestitem->setItemDelegateForColumn(1,readOnlyDelegate); //只读，测试项目名称
    tvtestitem->setItemDelegateForColumn(2,readOnlyDelegate); //只读，是否测试（显示）
    tvtestitem->setItemDelegateForColumn(3,readOnlyDelegate); //只读，是否分级


}


//基本设置参数显示，从配置文件中查看当前参数并显示
void FrmBaseSet::basesetdisp()
{
    ui->cbledtype->setCurrentIndex(unitprofile::basesetpara[itag].led_type);    //led_type
    ui->spbinout->setValue(unitprofile::basesetpara[itag].binout_default);      //默认等外BIN

    ui->edtdelay->setValue(unitprofile::polpara[itag].time_delay);
    ui->edtvf->setText(QString::number(unitprofile::polpara[itag].vf));
    ui->edtma->setText(QString::number(unitprofile::polpara[itag].ma));
    ui->edtvfmax->setText(QString::number(unitprofile::polpara[itag].vfmax));
    ui->edtvfmin->setText(QString::number(unitprofile::polpara[itag].vfmin));
}

//保存参数设置
void FrmBaseSet::savebaseset(int iindex)
{
    if(iindex==itag){
        unitprofile::basesetpara[itag].led_type = ui->cbledtype->currentIndex();   //LED类型
        unitprofile::basesetpara[itag].binout_default = ui->spbinout->value();  //默认等外BIN

        unitprofile::polpara[itag].time_delay = ui->edtdelay->value();
        unitprofile::polpara[itag].vf = ui->edtvf->text().toFloat();
        unitprofile::polpara[itag].ma = ui->edtma->text().toFloat();
        unitprofile::polpara[itag].vfmax = ui->edtvfmax->text().toFloat();
        unitprofile::polpara[itag].vfmin = ui->edtvfmin->text().toFloat();

        for (int ledid=0;ledid<3;ledid++) {
            QStandardItemModel *model;
            if(ledid == 0){
                model = qobject_cast<QStandardItemModel*>(ui->tvtestitem1->model());
            }
            if(ledid == 1){
                model = qobject_cast<QStandardItemModel*>(ui->tvtestitem2->model());
            }
            if(ledid == 2){
                model = qobject_cast<QStandardItemModel*>(ui->tvtestitem3->model());
            }
            for (int i=0;i<model->rowCount();i++)
            {
                if(model->item(i,2)->checkState() == Qt::Checked)   //是否测试（显示）
                {
                    unitprofile::testitempara[itag][ledid][i].test_enable = true;
                }else{
                    unitprofile::testitempara[itag][ledid][i].test_enable = false;
                }
                if(model->item(i,3)->checkState() == Qt::Checked)   //是否分级
                {
                    unitprofile::testitempara[itag][ledid][i].bin_enable = true;
                }else{
                    unitprofile::testitempara[itag][ledid][i].bin_enable = false;
                }
                unitprofile::testitempara[itag][ledid][i].verify_type = model->data(model->index(i,4)).toString().left(1).toInt();   //校准方式,0-不校准，取第一个字符并转化为数字
                unitprofile::testitempara[itag][ledid][i].vf_val = model->data(model->index(i,5)).toDouble();    //电压
                unitprofile::testitempara[itag][ledid][i].if_val = model->data(model->index(i,6)).toDouble();    //电流
                unitprofile::testitempara[itag][ledid][i].ok_max = model->data(model->index(i,7)).toDouble();    //良品上限
                unitprofile::testitempara[itag][ledid][i].ok_min = model->data(model->index(i,8)).toDouble();    //良品下限
                unitprofile::testitempara[itag][ledid][i].time_delay = model->data(model->index(i,9)).toInt();   //测试延时
                unitprofile::testitempara[itag][ledid][i].time_opt = model->data(model->index(i,10)).toInt();    //光谱积分时间
                unitprofile::testitempara[itag][ledid][i].range_iv = model->data(model->index(i,11)).toInt();   //亮度量程
                unitprofile::testitempara[itag][ledid][i].bin_out = model->data(model->index(i,12)).toInt();   //等外bin号
            }
        }
        unitprofile::saveprofile(unitpublic::gscurprofile);
        emit updatebinpara(itag);       //通知分级参数设置刷新页面
        emit updatevfypara(itag);       //通知校准参数设置刷新页面
        emit updatetestdata(itag);      //通知主测试数据刷新页面
        QMessageBox::information(NULL,"提示","当前测试工位基本参数保存完成！");
    }
}
