#include "frmbinauto.h"
#include "ui_frmbinauto.h"
#include "unitpublic.h"
#include "qmessagebox.h"
#include "qsqldatabase.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "unitprofile.h"

FrmBinAuto::FrmBinAuto(qint8 iindex,QString stp,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmBinAuto)
{
    ui->setupUi(this);
    itag = iindex;
    stype = stp;        //分级参数类型，从上级窗口传入，如 VF(1)、IV(1)等，即字符串中包含了测试参数名称以及LED晶片序号
    for (int i=0;i<TESTITEM_COUNT;i++) {
        if(stp.contains(lstTestItemName[i])){
            sitemname = lstTestItemName[i];     //从stp中获取testitem，即分级参数名称
            break;
        }
    }
    for (int i=0;i<LED_COUNT;i++) {
        if(stp.contains(QString::number(i+1))){
            iledindex = i;      //获取晶片序号，0,1,2
            break;
        }
    }
    this->setGeometry(500,400,250,280);          //显示位置
    this->setWindowTitle(QString("自动分级（%1）   %2#").arg(stype).arg(itag+1));
    QDoubleValidator*validator=new QDoubleValidator(0,999999,2,this);        //坐标值输入框，范围0-999999，四位小数
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->edtbegin->setValidator(validator);
    ui->edtstep->setValidator(validator);
    readbinaotutemp();
}

FrmBinAuto::~FrmBinAuto()
{
    delete ui;
}

void FrmBinAuto::on_toolButton_clicked()
{   //返回设置
    if((ui->edtbegin->text().trimmed() == "") || (ui->edtstep->text().trimmed() == "")){
        QMessageBox::information(NULL,"提示","起始值或步长必须为有效的浮点数！");
        return;
    }
    QList<BinVfPkg> lstbinvfpkg;
    BinVfPkg binvfpkg;
    double dstart=ui->edtbegin->text().toDouble();  //起始值
    double dstep =ui->edtstep->text().toDouble();    //步长
    for (int i=0;i<ui->spcount->value();i++) {
        binvfpkg.name=QString("%1%2").arg(sitemname).arg(iledindex+1);
        if(ui->rbcha->isChecked()){         //公差
            binvfpkg.fbegin = dstart;
            dstart = dstart + dstep;
            binvfpkg.fend = dstart;
        }else
            if(ui->rbbi->isChecked()){      //公比
                binvfpkg.fbegin = dstart;
                dstart = dstart * dstep;
                binvfpkg.fend = dstart;
            }
        lstbinvfpkg.append(binvfpkg);
    }
   emit tvbinparadispvf(irow, lstbinvfpkg);    //显示在上一级窗口(frmbinpara)
   savebinautotemp();
   this->close();
}

void FrmBinAuto::on_toolButton_2_clicked()
{
    this->close();
}

void FrmBinAuto::readbinaotutemp() //读取自动分级临时表参数
{
    QSqlDatabase mydb;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      mydb = QSqlDatabase::database("qt_sql_default_connection");
    else
      mydb = QSqlDatabase::addDatabase("QSQLITE");
//    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(unitpublic::gscurprofile);    //连接指定的工程文件（*.db3）
    if (!mydb.open())       //打开数据库失败       //数据库连接必须跟操作在一起，否则会提示错误
    {
        unitpublic::gpwritelog(QString("readbinaotutemp,打开工程文件失败:%1").arg(mydb.lastError().text()));
        return;
    }
    else
    {
        QSqlQuery mysql(mydb);
        if(!mysql.exec(QString("SELECT start_value,step_value,step_count,step_type FROM binauto_temp where station_id=%1 and led_index=%2 and item_name='%3'").arg(itag).arg(iledindex).arg(sitemname))) //查询自动分级参数临时表
        {
            unitpublic::gpwritelog(QString("查询自动分级参数临时表 binauto_temp 失败:%1").arg(mydb.lastError().text()));
        }
        else
        {
            while (mysql.next()) {  //mysql.value 对应序号同查询列表字段顺序
                ui->edtbegin->setText(mysql.value(0).toString());   //起始值
                ui->edtstep->setText(mysql.value(1).toString());        //步长
                ui->spcount->setValue(mysql.value(2).toInt());      //级数
                if(mysql.value(3).toInt()==1){
                    ui->rbcha->setChecked(true);    //等差
                }else
                {
                    ui->rbbi->setChecked(true);     //等比
                }
            }
        }
    }
    mydb.close();
}

//保存自动分级临时表参数
void FrmBinAuto::savebinautotemp()
{
    int istep_type=0;
    if(ui->rbcha->isChecked()){
        istep_type = 1; //等差
    }else
    {
        istep_type = 2;
    }
    QSqlDatabase mydb;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      mydb = QSqlDatabase::database("qt_sql_default_connection");
    else
      mydb = QSqlDatabase::addDatabase("QSQLITE");
//    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(unitpublic::gscurprofile);    //连接指定的工程文件（*.db3）
    if (!mydb.open())       //打开数据库失败       //数据库连接必须跟操作在一起，否则会提示错误
    {
        unitpublic::gpwritelog(QString("savebinautotemp,打开工程文件失败:%1").arg(mydb.lastError().text()));
        return;
    }
    else
    {
        QSqlQuery mysql(mydb);
        mysql.exec(QString("delete from binauto_temp where station_id=%1 and led_index=%2 and item_name='%3'").arg(itag).arg(iledindex).arg(sitemname));
        mysql.exec(QString("insert into binauto_temp (station_id,led_index,item_name,start_value,step_value,step_count,step_type) values (%1,%2,'%3',%4,%5,%6,%7)")
                   .arg(itag)
                   .arg(iledindex)
                   .arg(sitemname)
                   .arg(ui->edtbegin->text())
                   .arg(ui->edtstep->text())
                   .arg(ui->spcount->value())
                   .arg(istep_type));
    }
    mydb.close();
}
