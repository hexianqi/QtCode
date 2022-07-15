#include "frmverify.h"
#include "ui_frmverify.h"
#include "qstandarditemmodel.h"
#include "unitpublic.h"
#include "unitprofile.h"
#include "qmenu.h"
#include "qsqlquery.h"
#include "qdebug.h"
#include "windows.h"
#include "qmessagebox.h"
#include "float.h"
#include "qsqlerror.h"

Frmverify::Frmverify(qint8 iindex,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Frmverify)
{
    ui->setupUi(this);
    itag = iindex;
    this->setGeometry(0,0,parent->geometry().width(),parent->geometry().height());          //填充整个父窗口
    ui->btndaoru->setGeometry(20,10,80,60);
    ui->btnjisuan->setGeometry(120,10,80,60);
    ui->tvfset->setGeometry(0,80,this->geometry().width(),this->geometry().height()-80);

    tvfinit();
}

Frmverify::~Frmverify()
{
    delete ui;
}

//校准参数列表显示初始化
void Frmverify::tvfinit()
{
    QStandardItemModel *model = new QStandardItemModel();

    model->setColumnCount(1);  //校准方式

    ui->tvfset->setModel(model);

    //ui->tvbinset->setEditTriggers(QAbstractItemView::AllEditTriggers);  //双击选中某个单元格时进入编辑状态
    ui->tvfset->setSelectionBehavior(QAbstractItemView::SelectItems);//设置选中模式为选单元格
    ui->tvfset->verticalHeader()->hide();
    ui->tvfset->horizontalHeader()->hide();
    ui->tvfset->verticalHeader()->setDefaultSectionSize(18); //行高

    //初始化列宽，因为列宽设置要在插入数据时才生效，所以先插入一行空记录，后面清空就好
    //先添加3行数据，要合并单元格

    for (int i=3;i<19+3;i++) {       //拟合校准最多支持10组数据，KB只需要2组，offset只需要1组
        if(i<13)
            model->setItem(i,0,new QStandardItem(QString::number(i-2)));    //序号
        else{
            switch (i) {
            case 13:{       //空行
                model->setItem(i,0,new QStandardItem(""));
                break;
            }
            case 14:{
                model->setItem(i,0,new QStandardItem("校准方式"));
                break;
            }
            case 15:{
                model->setItem(i,0,new QStandardItem("offset"));
                break;
            }
            case 16:{       //k系数
                model->setItem(i,0,new QStandardItem("k"));
                break;
            }
            case 17:{       //b系数
                model->setItem(i,0,new QStandardItem("b"));
                break;
            }
            case 18:{       //n1,拟合polyfit系数1
                model->setItem(i,0,new QStandardItem("n1"));
                break;
            }
            case 19:{       //n2,拟合polyfit系数2
                model->setItem(i,0,new QStandardItem("n2"));
                break;
            }
            case 20:{       //n3,拟合polyfit系数3
                model->setItem(i,0,new QStandardItem("n3"));
                break;
            }

            }
        }
        ui->tvfset->setColumnWidth(0,60);
    }

    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate();
    ui->tvfset->setItemDelegateForRow(0,readOnlyDelegate);    //只读，最上面3行
    ui->tvfset->setItemDelegateForRow(1,readOnlyDelegate);
    ui->tvfset->setItemDelegateForRow(2,readOnlyDelegate);
    ui->tvfset->setItemDelegateForColumn(0,readOnlyDelegate); //只读，0列，BIN号

    int icolbegin = 0;
    ibincount = 0;  //参与分级的参数数量，
    for (int i=0;i<LED_COUNT;i++) {
        icolbegin = model->columnCount();      //初始3列
        for (int k=0;k<TESTITEM_COUNT;k++) {
            if(unitprofile::testitempara[itag][i][k].verify_type>0){   //测试项目需要校准
                model->setColumnCount(model->columnCount()+2);  //增加列数
                model->setItem(0,model->columnCount()-2,new QStandardItem(QString("晶%1").arg(i+1)));
                model->setItem(0,model->columnCount()-1,new QStandardItem(QString("晶%1").arg(i+1)));
                model->setItem(1,model->columnCount()-2,new QStandardItem(lstTestItemName.at(k)));
                model->setItem(1,model->columnCount()-1,new QStandardItem(lstTestItemName.at(k)));
                model->setItem(2,model->columnCount()-2,new QStandardItem("实测值"));
                model->setItem(2,model->columnCount()-1,new QStandardItem("标准值"));
                ui->tvfset->setSpan(1,model->columnCount()-2,1,2);        //合并实测值、标准值
                ui->tvfset->setSpan(14,model->columnCount()-2,1,2);        //合并校准方式
                for (int m=3;m<21;m++) {    //增加行数据
                    model->setItem(m,model->columnCount()-2,new QStandardItem(""));
                    model->setItem(m,model->columnCount()-1,new QStandardItem(""));
                }
                double val_k=1;
                double val_b=0;
                double offset = 0;
                double n1=0;
                double n2=1;
                double n3=0;

                QSqlDatabase mydb;
                if(QSqlDatabase::contains("qt_sql_default_connection"))
                   mydb = QSqlDatabase::database("qt_sql_default_connection");
                else
                   mydb = QSqlDatabase::addDatabase("QSQLITE");
                mydb.setDatabaseName(unitpublic::gscurprofile);    //连接指定的工程文件（*.db3）
                if (!mydb.open())       //打开数据库失败       //数据库连接必须跟操作在一起，否则会提示错误
                {
                   unitpublic::gpwritelog(QString("tvfinit,打开工程文件失败:%1").arg(mydb.lastError().text()));
                   return;
                }
                else
                {
                   QSqlQuery mysql(mydb);
                   QString ssql = QString("select val_k,val_b,val_offset,val_n1,val_n2,val_n3 from verify_para where station_id=%1 and led_index=%2 and item_name=%3").arg(itag).arg(i).arg(lstTestItemName.at(k));
                   mysql.exec(ssql);       //查询当前参数的校准系数
                   if(mysql.next()){
                       val_k=mysql.value(0).toDouble();
                       val_b=mysql.value(1).toDouble();
                       offset=mysql.value(2).toDouble();
                       n1 = mysql.value(3).toDouble();
                       n2 = mysql.value(4).toDouble();
                       n3 = mysql.value(5).toDouble();
                   }
                   mydb.close();
                }
                switch (unitprofile::testitempara[itag][i][k].verify_type) {
                case 2:{        //offset
                     model->setData(model->index(14,model->columnCount()-2),"偏移量offset");
                     model->setData(model->index(14,model->columnCount()-1),"偏移量offset");
                     model->item(15,model->columnCount()-2)->setData(QColor(255, 255, 0), Qt::BackgroundRole);   //系数单元格黄色显示
                     model->setData(model->index(15,model->columnCount()-2),QString::number(offset,'f',4));
                     break;
                 }
                 case 1:{        //k,b
                     model->setData(model->index(14,model->columnCount()-2),"线性kb值");
                     model->setData(model->index(14,model->columnCount()-1),"线性kb值");
                     model->item(16,model->columnCount()-2)->setData(QColor(255, 255, 0), Qt::BackgroundRole);   //系数单元格黄色显示
                     model->item(17,model->columnCount()-2)->setData(QColor(255, 255, 0), Qt::BackgroundRole);   //系数单元格黄色显示
                     model->setData(model->index(16,model->columnCount()-2),QString::number(val_k,'f',4));
                     model->setData(model->index(17,model->columnCount()-2),QString::number(val_b,'f',4));
                     break;
                 }
                 case 3:{        //polyfit
                     model->setData(model->index(14,model->columnCount()-2),"多项拟合polyfit");
                     model->setData(model->index(14,model->columnCount()-1),"多项拟合polyfit");
                     model->item(18,model->columnCount()-2)->setData(QColor(255, 255, 0), Qt::BackgroundRole);   //系数单元格黄色显示
                     model->item(19,model->columnCount()-2)->setData(QColor(255, 255, 0), Qt::BackgroundRole);   //系数单元格黄色显示
                     model->item(20,model->columnCount()-2)->setData(QColor(255, 255, 0), Qt::BackgroundRole);   //系数单元格黄色显示
                     model->setData(model->index(18,model->columnCount()-2),QString::number(n1,'f',4));
                     model->setData(model->index(19,model->columnCount()-2),QString::number(n2,'f',4));
                     model->setData(model->index(20,model->columnCount()-2),QString::number(n3,'f',4));
                     break;
                 }
                 }
                ui->tvfset->setColumnWidth(model->columnCount()-2,60);
                ui->tvfset->setColumnWidth(model->columnCount()-1,60);
                ibincount ++;
            }
        }
        //同一个晶片
        if(model->columnCount()>icolbegin)
            ui->tvfset->setSpan(0,icolbegin,1,model->columnCount()-icolbegin);    //合并"晶1/2/3"列，即从第0行、第icolbegin列开始的1行model->columnCount()-icolbegin列
    }
    for (int i=0;i<model->columnCount();i++) {
        model->setItem(13,i,new QStandardItem(""));  //增加一空行,作为测试数据与最值统计数据的分隔
        model->item(13,i)->setData(QColor(80, 100, 80), Qt::BackgroundRole);
    }
    ui->tvfset->setSpan(13,0,1,model->columnCount()); //合并空行

    //添加右键菜单
    ui->tvfset->setContextMenuPolicy(Qt::CustomContextMenu);
    m_menu = new QMenu(ui->tvfset);
    actClear = new QAction();
    actClear->setText("清除");
    m_menu->addAction(actClear);
    connect(actClear,SIGNAL(triggered()),this,SLOT(slot_clear()));
//    m_menu->addAction("清除", this, SLOT(slot_clear()));    //菜单：清除，
}

//鼠标右键“清除”选中的单元格
void Frmverify::slot_clear()
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvfset->model());
    QModelIndexList list = ui->tvfset->selectionModel()->selectedIndexes();     //获取选中的单元格列表
    for (int i=0;i<list.count();i++) {
        model->setData(list.at(i),"");  //依次将选中的单元格内容清空
    }
}
//收到基本参数页面保存数据的消息后，刷新校准页面
void Frmverify::mupdatevfypara(int iindex)
{
    if(itag == iindex){
        tvfinit();
    }
}

void Frmverify::on_btndaoru_clicked()
{//从测试主界面，导入最新测试的实测数据，最多10条
    //直接从mysql中取最近10分钟内的最新测试的10条结果数据
    QString ssql = "select id ";
    for (int i=0;i<LED_COUNT;i++) {
        for (int k=0;k<TESTITEM_COUNT;k++) {
            if(unitprofile::testitempara[itag][i][k].verify_type>0){   //测试项目需要校准
                ssql = ssql + QString(",%1%2").arg(lstTestItemName.at(k)).arg(i+1); //VF1,IV1,VF2...
            }
        }
    }
    ssql = ssql + QString(" from testdata where dtime>=DATE_SUB(NOW(),INTERVAL 15 MINUTE) and station_id=%1 order by id desc limit 10 ").arg(itag);  //倒序，15分钟内最近10条
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvfset->model());
    QSqlQuery mysql(unitpublic::dbmysql);
    qDebug() << ssql;
    mysql.exec(ssql);       //查询测试流水数据
    int irow = 3;   //从第3行开始显示实测值
    while (mysql.next()) {
        for (int icol=1;icol<model->columnCount();icol++) {     //从第1列开始，注意mysql查询出来的字段对应关系同tableview的列序号是一致的，都来自于lstTestItemName
            if((icol % 2)>0)
                model->setData(model->index(irow,icol),QString::number(mysql.value(icol/2 + 1).toDouble(),'f',3));   //value(0)是 id 值
        }
        irow ++;
    }
}

//右键菜单事件
void Frmverify::on_tvfset_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->tvfset->indexAt(pos);
    if(index.isValid()){
        actClear->setEnabled(true);
    }else
    {
        actClear->setEnabled(false);
    }
    m_menu->exec(QCursor::pos());   //弹出菜单
}

void Frmverify::on_btnjisuan_clicked()
{   //计算系数
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvfset->model());
    int icol=1;     //第1列开始，标准值、实测值。。。
    for (int i=0;i<LED_COUNT;i++) {
        for (int k=0;k<TESTITEM_COUNT;k++) {
            switch (unitprofile::testitempara[itag][i][k].verify_type){   //测试项目需要校准
            case 0:{
                break;      //不校准
            }
            case 1:{        //kb线性校准,y=kx+b
                //取前2行(3、4)的实测值、标准值参与计算
                double sc1 = model->data(model->index(3,icol)).toDouble();   //第3行，实测值
                double sc2 = model->data(model->index(4,icol)).toDouble();   //第4行，实测值
                QString ssc1 = model->data(model->index(3,icol)).toString().trimmed();   //实测值
                QString ssc2 = model->data(model->index(4,icol)).toString().trimmed();   //实测值
                icol++;
                double bz1 = model->data(model->index(3,icol)).toDouble();   //第3行，标准值
                double bz2 = model->data(model->index(4,icol)).toDouble();   //第4行，标准值
                QString sbz1 = model->data(model->index(3,icol)).toString().trimmed();   //标准值
                QString sbz2 = model->data(model->index(4,icol)).toString().trimmed();   //标准值
                icol++;
                double k=1;
                double b=0;
                if(unitpublic::regExpCheck(VALID_REAL,ssc1) && unitpublic::regExpCheck(VALID_REAL,ssc2)
                        && unitpublic::regExpCheck(VALID_REAL,sbz1) && unitpublic::regExpCheck(VALID_REAL,sbz2))
                {       //2组4个浮点数都必须为有效的浮点数
                    k=(bz2-bz1)/(sc2-sc1);
                    b=bz1 - k * sc1;
                    if(_isnan(k)||(_finite(k))) k=1;        //出现最大或最小浮点数时，K=1,b=0
                    if(_isnan(b)||(_finite(b))) b=0;
                }
                model->setData(model->index(16,icol-2),QString::number(k,'f',4));  //显示K,B系数
                model->setData(model->index(17,icol-2),QString::number(b,'f',4));
                break;
            }
            case 2:{        //offset校准
                //取最前1行的实测值、标准值参与计算
                double sc1 = model->data(model->index(3,icol)).toDouble();   //第3行，实测值
                QString ssc = model->data(model->index(3,icol)).toString().trimmed();   //实测值
                icol++;
                double bz1 = model->data(model->index(3,icol)).toDouble();   //第3行，标准值
                QString sbz = model->data(model->index(3,icol)).toString().trimmed();   //标准值
                icol++;
                double offset = 0;
                if(unitpublic::regExpCheck(VALID_REAL,ssc) && unitpublic::regExpCheck(VALID_REAL,sbz))
                    offset = bz1 - sc1 ;     //计算偏移量系数
                model->setData(model->index(15,icol-2),QString::number(offset,'f',4));  //显示K,B系数
                break;
            }
            case 3:{        //多项拟合polyfit
                //取最前n行(n>=4)的实测值、标准值参与计算
                bool bvalid = true;
                PolyXy ployxy;
                int mcount=0;
                for (int m=0;m<10;m++){
                    ployxy.x[m] = model->data(model->index(m+3,icol)).toDouble(); //实测值
                    if(!unitpublic::regExpCheck(VALID_REAL,model->data(model->index(m+3,icol)).toString().trimmed())){
                        bvalid = false;
                        break;
                    }
                    if(ployxy.x[m]>0) mcount++; else break;     //0则退出
                }
                icol++;
                int ncount=0;
                for (int m=0;m<10;m++){
                    ployxy.y[m] = model->data(model->index(m+3,icol)).toDouble(); //标准值 ,注意，实测值跟标准值的数量要保持一致
                    if(!unitpublic::regExpCheck(VALID_REAL,model->data(model->index(m+3,icol)).toString().trimmed())){
                        bvalid = false;
                        break;
                    }
                    if(ployxy.y[m]>0) ncount++; else break;     //0则退出
                }
                if(((mcount<4)&&(mcount>0)) || ((ncount<4) &&(ncount>0))){
                    QMessageBox::information(NULL,"提示","有效的多项拟合标准值和实测值必须不少于4组！");
                    return;
                }
                icol++;
                double n1=0;
                double n2=1;
                double n3=0;
                if(bvalid){
                    HINSTANCE hdll;
                    hdll = LoadLibrary("polyfit.dll");  //要在pro中加DEFINES-= UNICODE，否则会报LPCWSTR错误
                    if(hdll != NULL){
                        Polyfit *polyfit = (Polyfit*)GetProcAddress(hdll,"polyfit");
                        if(polyfit(mcount,3,&ployxy)==0){
                            n1=ployxy.beta[0];
                            n2=ployxy.beta[1];
                            n3=ployxy.beta[2];
                        }
                    }
                }
                model->setData(model->index(18,icol-2),QString::number(n1,'f',4));  //显示n1,n2,n3系数
                model->setData(model->index(19,icol-2),QString::number(n2,'f',4));
                model->setData(model->index(20,icol-2),QString::number(n3,'f',4));
                break;
            }
            }
        }
    }

}

//槽函数，保存数据时接收信号
void Frmverify::msavevfyset(int iindex)
{
    if(itag == iindex){ //保存校准参数
        QStringList lstsql;
        lstsql.clear();
        lstsql.append(QString("delete from verify_para where station_id=%1 ").arg(itag));       //先删除本工位所有校准参数
        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvfset->model());
        int icol = 1;
        for (int i=0;i<LED_COUNT;i++) {
            for (int k=0;k<TESTITEM_COUNT;k++) {
                double val_k=1;
                double val_b=0;
                double offset = 0;
                double n1=0;
                double n2=1;
                double n3=0;
                switch (unitprofile::testitempara[itag][i][k].verify_type) {
                case 0:{            //不校准
                    continue;
                    break;
                }
                case 1:{    //kb校准
                    val_k = model->data(model->index(16,icol)).toDouble();
                    val_b = model->data(model->index(17,icol)).toDouble();
                    break;
                }
                case 2:{
                    offset = model->data(model->index(15,icol)).toDouble();
                    break;
                }
                case 3:{
                    n1 = model->data(model->index(18,icol)).toDouble();
                    n2 = model->data(model->index(19,icol)).toDouble();
                    n3 = model->data(model->index(20,icol)).toDouble();
                    break;
                }
                }   //测试项目需要校准
                QString s1 = QString("insert into verify_para (station_id,led_index,item_name,val_k,val_b,val_offset,val_n1,val_n2,val_n3) values (%1,%2,'%3',%4,%5,%6,%7,%8,%9)")
                            .arg(itag)
                            .arg(i)
                            .arg(lstTestItemName.at(k))
                            .arg(val_k)
                            .arg(val_b)
                            .arg(offset)
                            .arg(n1)
                            .arg(n2)
                            .arg(n3);
                lstsql.append(s1);
                icol++;
                icol++;
            }
        }

        QSqlDatabase mydb;
        if(QSqlDatabase::contains("qt_sql_default_connection"))
           mydb = QSqlDatabase::database("qt_sql_default_connection");
        else
           mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName(unitpublic::gscurprofile);    //连接指定的工程文件（*.db3）
        if (!mydb.open())       //打开数据库失败       //数据库连接必须跟操作在一起，否则会提示错误
        {
           unitpublic::gpwritelog(QString("tvfinit,打开工程文件失败:%1").arg(mydb.lastError().text()));
           return;
        }
        else
        {
           QSqlQuery mysql(mydb);
           mydb.transaction();
           for(int i=0;i<lstsql.count();i++){
               mysql.exec(lstsql.at(i));
               qDebug() << lstsql.at(i);
           }
           mydb.commit();
           mydb.close();
        }
//        unitpublic::testcmd[itag] = CMD_TEST_INIT;    //初始化导入参数
        unitpublic::filedb2memdb(itag);
        QMessageBox::information(NULL,"提示","校准参数保存成功并生效！");
    }
}
