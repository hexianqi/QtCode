#include "frmbinpara.h"
#include "ui_frmbinpara.h"
#include "qmessagebox.h"
#include "qstandarditemmodel.h"
#include <qheaderview.h>
#include "frmbinauto.h"
#include "frmbinxy.h"
#include "unitprofile.h"
#include "qsqldatabase.h"
#include "qsqlerror.h"
#include "qsqlquery.h"

FrmBinPara::FrmBinPara(qint8 iindex,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmBinPara)
{
    ui->setupUi(this);
    itag = iindex;
    this->setGeometry(300,300,1200,600);          //显示位置
    this->setWindowTitle(QString("分BIN设置   %1#").arg(itag+1));

    tvbinparaInit();
    readbinparatemp();  //从临时表中获取分级参数
}

FrmBinPara::~FrmBinPara()
{
    delete ui;
}

void FrmBinPara::MyHeadersectionClicked(int logicalIndex)
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvbinpara->model());
    QString stype = model->verticalHeaderItem(logicalIndex)->text();    //当前行编辑的参数类型，如VF1\XY1等，方便在下一级分BIN界面区别是什么类型的参数

    if(stype.contains("CIE_xy")){   //xy坐标分级
        FrmBinxy* frmbinxy = new FrmBinxy(itag,stype);
        frmbinxy->setAttribute(Qt::WA_DeleteOnClose);
        frmbinxy->setModal(true);
        connect(frmbinxy,SIGNAL(tvbinparadispxy(int,QList<BinXyPkg>)),this,SLOT(tvbinparadispxy(int,QList<BinXyPkg>)));
        frmbinxy->irow = logicalIndex;  //行序号
        frmbinxy->show();
    }else
    {               //其他参数自动分级，VF/IV/TC/Ra等。。。
        FrmBinAuto* frmbinauto = new FrmBinAuto(itag,stype);
        frmbinauto->setAttribute(Qt::WA_DeleteOnClose);
        frmbinauto->setModal(true);
        connect(frmbinauto,SIGNAL(tvbinparadispvf(int,QList<BinVfPkg>)),this,SLOT(tvbinparadispvf(int,QList<BinVfPkg>)));
        frmbinauto->irow = logicalIndex;    //行序号
        frmbinauto->show();
    }
}

//分BIN参数编辑列表初始化
//行信息来源于产品测试项目中是否参与分BIN的设置
//需定义表头点击事件，
void FrmBinPara::tvbinparaInit()
{
    QStandardItemModel *model = new QStandardItemModel();

    model->setColumnCount(50);  //每个单项可分BIN数量，最大50个（可根据实际调整）
   // for (int i=0;i<5;i++) {
   //     model->setHeaderData(0,Qt::Horizontal,QString("%1").arg(i+1));         //为什么用fromLocal8Bit会乱码，
   // }

    ui->tvbinpara->setModel(model);
    ui->tvbinpara->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "color: black;"          //文字颜色
                                                     "font: 9pt;"      //字体大小
                                                     "padding-left: 2px;"
                                                     "border: 1px solid #6c6c6c;}");

    ui->tvbinpara->setEditTriggers(QAbstractItemView::AllEditTriggers);  //双击选中某个单元格时进入编辑状态
    ui->tvbinpara->setSelectionBehavior(QAbstractItemView::SelectItems);    //设置选中模式为选单元格

    ui->tvbinpara->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tvbinpara->verticalHeader()->setDefaultSectionSize(18); //行高
    ui->tvbinpara->verticalHeader()->setSectionsClickable(true);    //允许点击行标题头
    QHeaderView *headerView = ui->tvbinpara->verticalHeader();
    connect(headerView, &QHeaderView::sectionClicked, this, &FrmBinPara::MyHeadersectionClicked);   //定义行标题头点击事件
// void QHeaderView::sectionClicked(int logicalIndex);   //行表头鼠标点击事件信号原型，信号与槽函数连接，在MyHeadersectionClicked事件中处理对应事物
    int irow = 0;
    for (int i=0;i<LED_COUNT;i++) {
        for (int k=0;k<TESTITEM_COUNT;k++) {
            if(unitprofile::testitempara[itag][i][k].bin_enable){   //测试项目参与分级，参与分级的项目必须也是测试项目，这个关系放在基本设置时进行管控
                if(lstTestItemName.at(k) == "CIE_y"){
                    continue;       //y不处理，x已经处理过了
                };
                model->setItem(irow,0,new QStandardItem(""));  //设置列宽
                if(lstTestItemName.at(k) == "CIE_x"){
                    model->setHeaderData(irow,Qt::Vertical,QString("%1(%2)").arg("CIE_xy").arg(i+1));
                }else
                {
                    model->setHeaderData(irow,Qt::Vertical,QString("%1(%2)").arg(lstTestItemName[k]).arg(i+1));
                }
                irow ++;
            }
        }
    }
}

void FrmBinPara::resizeEvent(QResizeEvent *size)
{
    ui->tvbinpara->setGeometry(0,0,this->geometry().width(),this->geometry().height()-60);
    ui->btnok->setGeometry(10,this->geometry().height()-50,80,40);
    ui->btncancel->setGeometry(100,this->geometry().height()-50,80,40);
}

//槽函数，接收从frmbinxy窗口返回的xy分级参数
void FrmBinPara::tvbinparadispxy(int irow,QList<BinXyPkg> binxypkg)
{
    lstbinxypkg = binxypkg;     //将上级xy自动分级参数保存起来
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvbinpara->model());
    int k=0;
    for (int i=0;i<model->columnCount();i++) {
        if(i<binxypkg.count()){
            model->setItem(irow,k,new QStandardItem(binxypkg.at(k).name));
            k++;    //过滤NAME值为空的列表，即该行坐标点区域不参与分级
        }else
        {
            model->setItem(irow,i,new QStandardItem(""));
        }
    }
}
//槽函数，接收从frmbinauto窗口返回的分级参数
void FrmBinPara::tvbinparadispvf(int irow,QList<BinVfPkg> binvfpkg)
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvbinpara->model());
    int k=0;
    for (int i=0;i<model->columnCount();i++) {
        if(i<binvfpkg.count()){
            model->setItem(irow,k,new QStandardItem(QString("%1 - %2").arg(binvfpkg.at(k).fbegin).arg(binvfpkg.at(k).fend)));
            k++;    //过滤NAME值为空的列表，即该行坐标点区域不参与分级
        }else
        {
            model->setItem(irow,i,new QStandardItem(""));
        }
    }
}

void FrmBinPara::readbinparatemp() //读取分级参数临时表
{
    QString sitemname = "";
    int iledindex=0;
    QSqlDatabase mydb;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      mydb = QSqlDatabase::database("qt_sql_default_connection");
    else
      mydb = QSqlDatabase::addDatabase("QSQLITE");
//    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE","DISK");
    mydb.setDatabaseName(unitpublic::gscurprofile);    //连接指定的工程文件（*.db3）
    if (!mydb.open())       //打开数据库失败       //数据库连接必须跟操作在一起，否则会提示错误
    {
        unitpublic::gpwritelog(QString("readbinaotutemp,打开工程文件失败:%1").arg(mydb.lastError().text()));
        return;
    }
    else
    {
        QSqlQuery mysql(mydb);
        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvbinpara->model());
        lstbinxypkg.clear();
        for (int i=0;i<model->rowCount();i++) {
            QString stype = model->verticalHeaderItem(i)->text();    //当前行对应的参数类型，如VF1\XY1等，
            for (int k=0;k<TESTITEM_COUNT;k++) {
                if(stype.contains(lstTestItemName[k])){
                    sitemname = lstTestItemName[k];     //从stype中获取testitem，即分级参数名称
                    break;
                }
            }
            for (int k=0;k<LED_COUNT;k++) {
                if(stype.contains(QString::number(k+1))){
                    iledindex = k;      //获取晶片序号，0,1,2
                    break;
                }
            }
            if(sitemname=="CIE_x"){
                mysql.exec(QString("SELECT bin_name,x0,y0,x1,y1,x2,y2,x3,y3 FROM binxypara_temp where station_id=%1 and led_index=%2").arg(itag).arg(iledindex)); //查询xy自动分级参数临时表
                int icol = 0;
                while (mysql.next()) {      //查询该参数的临时分级参数
                    model->setData(model->index(i,icol),QString("%1").arg(mysql.value(0).toString()));  //xy自动分级参数，R1,R2...
                    icol ++;
                    BinXyPkg binxypkg;
                    binxypkg.name = mysql.value(0).toString();
                    binxypkg.pt0 = QPointF(mysql.value(1).toDouble(),mysql.value(2).toDouble());
                    binxypkg.pt1 = QPointF(mysql.value(3).toDouble(),mysql.value(4).toDouble());
                    binxypkg.pt2 = QPointF(mysql.value(5).toDouble(),mysql.value(6).toDouble());
                    binxypkg.pt3 = QPointF(mysql.value(7).toDouble(),mysql.value(8).toDouble());
                    lstbinxypkg.append(binxypkg);
                }
            }else
            if(sitemname=="CIE_y"){
                continue;
            }else
            {
                mysql.exec(QString("SELECT min_value,max_value FROM binpara_temp where station_id=%1 and led_index=%2 and item_name='%3'").arg(itag).arg(iledindex).arg(sitemname)); //查询自动分级参数临时表
                int icol = 0;
                while (mysql.next()) {      //查询该参数的临时分级参数
                    model->setData(model->index(i,icol),QString("%1 - %2").arg(mysql.value(0).toDouble()).arg(mysql.value(1).toDouble()));
                    icol ++;
                }
            }
        }
    }
    mydb.close();
}

//从单元格中获取分级参数，传入参数，ctext单元格字符串数据，返回minvalue和maxvalue
//非法字符串，则函数返回false
bool FrmBinPara::celltobinpara(QString ctext,double &minvalue,double &maxvalue)
{
    if(ctext == ""){
        return false;       //该单元格为空则返回false
    }
    if(!ctext.contains("-")){
        return false;   //字符串中必须包含字符 “-”，标准格式如3.0 - 3.3
    }
    QString s1=ctext.left(ctext.indexOf("-")-1).trimmed();    //获取前半部分字符串
    QString s2=ctext.right(ctext.length() - ctext.indexOf("-") -1 ).trimmed(); //后半部分的字符串
    if((s1=="")||(s2=="")){
        return false;       //前后半部分必须不为空
    }
    bool bok;
    double f1 = s1.toDouble(&bok);
    if(bok){
        minvalue = f1;
    }else{
        return false;
    }
    double f2 = s2.toDouble(&bok);
    if(bok){
        maxvalue = f2;
    }else{
        return false;
    }

}
//判断单元格xy分级参数是否合法
bool FrmBinPara::celltobinxypara(QString ctext,QPointF &xy0,QPointF &xy1,QPointF &xy2,QPointF &xy3)
{
    if(ctext == ""){
        return false;       //该单元格为空则返回false
    }
    bool result = false;
    for (int i=0;i<lstbinxypkg.count();i++) {
        if(lstbinxypkg.at(i).name == ctext){
            result = true;  //在列表中找到参数
            xy0 = lstbinxypkg.at(i).pt0;
            xy1 = lstbinxypkg.at(i).pt1;
            xy2 = lstbinxypkg.at(i).pt2;
            xy3 = lstbinxypkg.at(i).pt3;
            break;
        }
    }
    return result;
}

//保存分级参数临时表
bool FrmBinPara::savebinparatemp()
{
    QString sitemname = "";
    int iledindex=0;
    //1.遍历列表所有临时分级参数，并检查参数输入是否合法有效
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvbinpara->model());
    QStringList lstsqlxy;
    QStringList lstsqliv;
    lstsqlxy.clear();
    lstsqliv.clear();
    for (int i=0;i<model->rowCount();i++) {     //从第一行开始，或者当前分级参数
        QString stype = model->verticalHeaderItem(i)->text();    //当前行编辑的参数类型，如VF1\XY1等，方便在下一级分BIN界面区别是什么类型的参数
        for (int k=0;k<TESTITEM_COUNT;k++) {
            if(stype.contains(lstTestItemName[k])){
                sitemname = lstTestItemName[k];     //从stype中获取改行对应的testitem，即分级参数名称
                break;
            }
        }
        for (int k=0;k<LED_COUNT;k++) {
            if(stype.contains(QString::number(k+1))){
                iledindex = k;              //获取改行对应的晶片序号，0,1,2
                break;
            }
        }

        for (int k=0;k<model->columnCount();k++){
            if(sitemname=="CIE_x"){
                QPointF p0,p1,p2,p3;
                if(celltobinxypara(model->data(model->index(i,k)).toString().trimmed(),p0,p1,p2,p3)){   //判断单元格内容是否有效的浮点数
                    lstsqlxy.append(QString("insert into binxypara_temp (station_id,led_index,bin_name,x0,y0,x1,y1,x2,y2,x3,y3) values (%1,%2,'%3',%4,%5,%6,%7,%8,%9,%10,%11)")
                                  .arg(itag)       //工位序号
                                  .arg(iledindex)  //晶片序号
                                  .arg(model->data(model->index(i,k)).toString().trimmed())  //xy分BIN名
                                  .arg(p0.x())
                                  .arg(p0.y())
                                  .arg(p1.x())
                                  .arg(p1.y())
                                  .arg(p2.x())
                                  .arg(p2.y())
                                  .arg(p3.x())
                                  .arg(p3.y()));
                 }else{
                    if(k==0){QMessageBox::information(NULL,"提示",QString("CIE_xy分级数为0，请填入正确的xy分级参数！"));return false;}
                    model->setData(model->index(i,k),"");   //单元格内容无效，则清空
                    break;
                      //该行参数的第一列必须要有分级参数，否则提示“分级数为0，请填入正确的分级参数！”，同时跳出循环；该行从第二列开始后面只要有空或无效单元格，则当做后面的所有参数均无效
              }
            }else if(sitemname=="CIE_y")
            {
                continue;
            }else   //VF/IR/IV...
            {
                double dbegin;//获取该行该参数的分级临时参数
                double dend;
                if(celltobinpara(model->data(model->index(i,k)).toString().trimmed(),dbegin,dend)){   //判断单元格内容是否有效的浮点数
                    lstsqliv.append(QString("insert into binpara_temp (station_id,led_index,item_name,min_value,max_value) values (%1,%2,'%3',%4,%5)")
                                  .arg(itag)       //工位序号
                                  .arg(iledindex)  //晶片序号
                                  .arg(sitemname)  //参数名称
                                  .arg(dbegin)
                                  .arg(dend));
                 }else{
                    if(k==0){QMessageBox::information(NULL,"提示",QString("%1分级数为0，请填入正确的分级参数！").arg(sitemname));return false;}
                    model->setData(model->index(i,k),"");   //单元格内容无效，则清空
                    break;
                      //该行参数的第一列必须要有分级参数，否则提示“分级数为0，请填入正确的分级参数！”，同时跳出循环；该行从第二列开始后面只要有空或无效单元格，则当做后面的所有参数均无效
              }

            }
        }
    }

    //2.临时参数存入表中
    QSqlDatabase mydb;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      mydb = QSqlDatabase::database("qt_sql_default_connection");
    else
      mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(unitpublic::gscurprofile);    //连接指定的工程文件（*.db3）
    if (!mydb.open())       //打开数据库失败       //数据库连接必须跟操作在一起，否则会提示错误
    {
        unitpublic::gpwritelog(QString("savebinautotemp,打开工程文件失败:%1").arg(mydb.lastError().text()));
        return false;
    }
    else
    {
        QSqlQuery mysql(mydb);
        mysql.exec(QString("delete from binxypara_temp where station_id=%1").arg(itag));  //先删除该工位xy分级临时参数
        for (int i=0;i<lstsqlxy.count();i++) {    //集中处理数据库
            mysql.exec(lstsqlxy.at(i));
        }
        mysql.exec(QString("delete from binpara_temp where station_id=%1").arg(itag));  //先删除该工位所有临时参数
        for (int i=0;i<lstsqliv.count();i++) {    //集中处理数据库
            mysql.exec(lstsqliv.at(i));
        }
    }
    mydb.close();
    return true;
}

void FrmBinPara::on_btnok_clicked()
{//保存当前页面分级参数到临时表，binpara_temp
    ui->tvbinpara->selectRow(ui->tvbinpara->currentIndex().row()); //选择当前行，目的是移动输入焦点，让当前输入生效
    if(savebinparatemp()){
        emit tvbinparadisp(itag);   //在上一级窗口显示临时分级参数组合后的全部参数
        this->close();
    }
}

void FrmBinPara::on_btncancel_clicked()
{
    this->close();
}
