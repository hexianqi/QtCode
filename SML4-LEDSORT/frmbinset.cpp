#include "frmbinset.h"
#include "ui_frmbinset.h"
#include <qmessagebox.h>
#include "frmbinpara.h"
#include "qstandarditemmodel.h"
#include "unitpublic.h"
#include "unitprofile.h"
#include "qsqldatabase.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "qtooltip.h"
#include "QModelIndex"
#include "qdebug.h"
#include "qfiledialog.h"

FrmBinSet::FrmBinSet(qint8 iindex,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmBinSet)
{
    ui->setupUi(this);
    itag = iindex;

    this->setGeometry(0,0,parent->geometry().width(),parent->geometry().height());          //填充整个父窗口
    ui->btnset->setGeometry(20,10,80,60);
    ui->btnclear->setGeometry(120,10,80,60);
    ui->btnin->setGeometry(220,10,80,60);
    ui->btnout->setGeometry(320,10,80,60);
    ui->tvbinset->setGeometry(0,80,this->geometry().width(),this->geometry().height()-80);

    lstbinxypkg.clear();
    BindispInit();
    readbinsetpara();
}

FrmBinSet::~FrmBinSet()
{
    delete ui;
}

void FrmBinSet::on_btnset_clicked()
{   //分级设置
    FrmBinPara* frmbinpara = new FrmBinPara(unitpublic::gicurindex);
    frmbinpara->setAttribute(Qt::WA_DeleteOnClose);
    connect(frmbinpara,SIGNAL(tvbinparadisp(int)),this,SLOT(mtvbinparadisp(int)));
    frmbinpara->setModal(true);
    frmbinpara->show();
}

void FrmBinSet::on_btnclear_clicked()
{   //清空数据
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvbinset->model());
    for (int irow=3;irow<3+256;irow++) {
        for (int icol=1;icol<model->columnCount();icol++) {
            model->setData(model->index(irow,icol),"");    //清空数据
        }
    }
}

void FrmBinSet::on_btnin_clicked()
{   //导入xls，注意：excel文件的导入，对文件内容只是做了几个比较简单的格式化模板要求，比如行数及第260行的关键标志字符串xybinpara，其他比如xy分级的数值是否争取以及名称是否对应等到你都比较粗放
        //所以，使用该功能时要求用户必须严格按照模板文件改写内容再导入，包括比如参与分级参数的测试项发生改变后，导入变更前的excel文件可能会产生异常现象，建议在测试项变更之后先导出文件作为模板，再编辑后导入
    QString fileName = QFileDialog::getOpenFileName(this,"打开分级参数",".","逗号分隔符文件(*.csv)");
    if(!fileName.isNull()){
        QStringList lstsavefile;
        lstsavefile.clear();
        unitpublic::TxtToStringList(fileName,lstsavefile);  //读文本文件到qstringlist
        if((lstsavefile.count()>256+3+1)&&(lstsavefile.at(256+3)=="xybinpara")){    //注意文件格式模板，必须正确，且行数是从0开始
            QList<BinXyPkg> lstbinxypkgtemp;    //xy分级参数信息，临时存储
            QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvbinset->model());
            for (int irow=0;irow<lstsavefile.count();irow++) {
                if(irow<256+3){ //除xy分级参数以外的解析，包括晶片序号等。。。
                    QStringList lstbinsetpara = lstsavefile.at(irow).split(",");    //解析非xy分级参数行数据，以逗号作为分隔符
                    for (int icol=0;icol<lstbinsetpara.count();icol++) {
                        model->setData(model->index(irow,icol),lstbinsetpara.at(icol));     //导入非xy分级参数
                    }
                }else
                if(irow>256+3){ //开始xy分级参数解析
                    QStringList lstxybinpara = lstsavefile.at(irow).split(",");    //解析xy分级参数行数据，以逗号作为分隔符
                        if(lstxybinpara.count()==9){
                            BinXyPkg binxypkg;
                            binxypkg.name = lstxybinpara.at(0); //xybinname
                            binxypkg.pt0=QPointF(lstxybinpara.at(1).toDouble(),lstxybinpara.at(2).toDouble());
                            binxypkg.pt1=QPointF(lstxybinpara.at(3).toDouble(),lstxybinpara.at(4).toDouble());
                            binxypkg.pt2=QPointF(lstxybinpara.at(5).toDouble(),lstxybinpara.at(6).toDouble());
                            binxypkg.pt3=QPointF(lstxybinpara.at(7).toDouble(),lstxybinpara.at(8).toDouble());
                            lstbinxypkgtemp.append(binxypkg);
                        }else{
                            QMessageBox::information(NULL,"提示","文件导入失败，xy分级参数不争取！\n\r"+fileName);
                            return;
                        }
                }
                //else if(irow==256+3) continue;   //标志行，xybinpara，跳过
            }
            lstbinxypkg = lstbinxypkgtemp;      //分级参数更新
            QMessageBox::information(NULL,"提示","文件导入成功！\n\r"+fileName);
        }else
            QMessageBox::information(NULL,"提示","文件导入失败，文件格式不争取！\n\r"+fileName);
    }
}

void FrmBinSet::on_btnout_clicked()
{   //导出xls
    QString fileName = QFileDialog::getSaveFileName(this,"保存分级参数",".","逗号分隔符文件(*.csv)");
    if(!fileName.isNull()){
        //保存文件到excel逗号分隔符文件 *.csv
        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvbinset->model());
        QStringList lstsavefile;
        lstsavefile.clear();
        for (int irow=0;irow<model->rowCount();irow++) {
            QString srow="";    //每一行数据
            for (int icol=0;icol<model->columnCount();icol++) {
                srow = srow + QString(model->data(model->index(irow,icol)).toString())+",";     //逗号分隔符
            }
            lstsavefile.append(srow);
        }
        lstsavefile.append("xybinpara");  //增加一固定行，可以作为文件格式合法化判断标准，注意：该文件的格式为固定模板，即一共256+3行，前0-2行是标题头，第3行开始是数据，且一共256行（即256BIN），格式不可修改
        for(int i=0;i<lstbinxypkg.count();i++){//颜色参数保存在后面
            lstsavefile.append(QString("%1,%2,%3,%4,%5,%6,%7,%8,%9")
                               .arg(lstbinxypkg[i].name)
                               .arg(lstbinxypkg[i].pt0.x())
                               .arg(lstbinxypkg[i].pt0.y())
                               .arg(lstbinxypkg[i].pt1.x())
                               .arg(lstbinxypkg[i].pt1.y())
                               .arg(lstbinxypkg[i].pt2.x())
                               .arg(lstbinxypkg[i].pt2.y())
                               .arg(lstbinxypkg[i].pt3.x())
                               .arg(lstbinxypkg[i].pt3.y()));
        }
        if(unitpublic::StringListToTxt(fileName,lstsavefile)==1)
            QMessageBox::information(NULL,"提示","文件导出成功！\n\r"+fileName);
        else
            QMessageBox::information(NULL,"提示","文件导出失败！\n\r"+fileName);
   }

}

//初始化分BIN参数表
void FrmBinSet::BindispInit()
{
    QStandardItemModel *model = new QStandardItemModel();

    model->setColumnCount(3);  //列数量根据该工位选择的测试参数确定，比如VF/IR/IV/CIE_X/CIE_Y/CCT/Ra/WD/WP，表示有9个测试对象

    ui->tvbinset->setModel(model);

    //ui->tvbinset->setEditTriggers(QAbstractItemView::AllEditTriggers);  //双击选中某个单元格时进入编辑状态
    ui->tvbinset->setSelectionBehavior(QAbstractItemView::SelectItems);//设置选中模式为选单元格
    ui->tvbinset->verticalHeader()->hide();
    ui->tvbinset->horizontalHeader()->hide();
    ui->tvbinset->verticalHeader()->setDefaultSectionSize(18); //行高

    //初始化列宽，因为列宽设置要在插入数据时才生效，所以先插入一行空记录，后面清空就好
    //先添加3行数据，要合并单元格
    model->setItem(0,1,new QStandardItem("BIN名称"));
    model->setItem(0,2,new QStandardItem("备注"));
    model->setItem(1,1,new QStandardItem("BIN名称"));
    model->setItem(1,2,new QStandardItem("备注"));
    model->setItem(2,1,new QStandardItem("BIN名称"));
    model->setItem(2,2,new QStandardItem("备注"));

    for (int i=3;i<256+3;i++) {       //支持256 BIN
        model->setItem(i,0,new QStandardItem(QString::number(i-2)));
        ui->tvbinset->setColumnWidth(0,30);
        model->setItem(i,1,new QStandardItem(""));
        ui->tvbinset->setColumnWidth(1,150);
        model->setItem(i,2,new QStandardItem(""));
        ui->tvbinset->setColumnWidth(2,150);
    }
    ui->tvbinset->setSpan(0,0,3,1); //从第0行开始，合并第0列的3行1列
    ui->tvbinset->setSpan(0,1,3,1); //从第0行开始，合并第1列的3行1列
    ui->tvbinset->setSpan(0,2,3,1); //从第0行开始，合并第2列的3行1列
    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate();
    ui->tvbinset->setItemDelegateForRow(0,readOnlyDelegate);    //只读，最上面3行
    ui->tvbinset->setItemDelegateForRow(1,readOnlyDelegate);
    ui->tvbinset->setItemDelegateForRow(2,readOnlyDelegate);
    ui->tvbinset->setItemDelegateForColumn(0,readOnlyDelegate); //只读，0列，BIN号

    int icolbegin = 0;
    ibincount = 0;  //参与分级的参数数量，
    sfieldname = "bin_number,bin_name,bin_memo";    //分级参数查询字段名
    for (int i=0;i<LED_COUNT;i++) {
        icolbegin = model->columnCount();      //初始3列
        for (int k=0;k<TESTITEM_COUNT;k++) {
            if(unitprofile::testitempara[itag][i][k].bin_enable){   //测试项目参与分级，参与分级的项目必须也是测试项目，这个关系放在基本设置时进行管控
                if(lstTestItemName.at(k) == "CIE_x"){
                    model->setColumnCount(model->columnCount()+1);  //增加列数
                    model->setItem(0,model->columnCount()-1,new QStandardItem(QString("晶%1").arg(i+1)));
                    model->setItem(1,model->columnCount()-1,new QStandardItem("CIE_xy"));
                    model->setItem(2,model->columnCount()-1,new QStandardItem("CIE_xy"));
                    ui->tvbinset->setColumnWidth(model->columnCount()-1,60);
                    sfieldname = sfieldname + QString(",binxy%1_name").arg(i+1);    //xy分级参数相关字段
                    ibincount ++;
                }else
                if(lstTestItemName.at(k) == "CIE_y"){
                        //不做处理，上面CIE_x已经处理了
                }else
                {
                    model->setColumnCount(model->columnCount()+2);  //增加列数
                    model->setItem(0,model->columnCount()-2,new QStandardItem(QString("晶%1").arg(i+1)));
                    model->setItem(0,model->columnCount()-1,new QStandardItem(QString("晶%1").arg(i+1)));
                    model->setItem(1,model->columnCount()-2,new QStandardItem(lstTestItemName.at(k)));
                    model->setItem(1,model->columnCount()-1,new QStandardItem(lstTestItemName.at(k)));
                    model->setItem(2,model->columnCount()-2,new QStandardItem("Min"));
                    model->setItem(2,model->columnCount()-1,new QStandardItem("Max"));
                    ui->tvbinset->setColumnWidth(model->columnCount()-2,60);
                    ui->tvbinset->setColumnWidth(model->columnCount()-1,60);
                    ui->tvbinset->setSpan(1,model->columnCount()-2,1,2);        //合并 Min & Max 列
                    sfieldname = sfieldname + QString(",%1%2_MIN,%1%2_MAX").arg(lstTestItemName.at(k)).arg(i+1);    //其他参数对应的相关字段
                    ibincount ++;
                }
            }
        }
        //同一个晶片
        if(model->columnCount()>icolbegin)
            ui->tvbinset->setSpan(0,icolbegin,1,model->columnCount()-icolbegin);    //合并"晶1/2/3"列，即从第0行、第icolbegin列开始的1行model->columnCount()-icolbegin列
    }
    ui->tvbinset->setMouseTracking(true);   //开启鼠标捕获，悬停显示
}


//动态数组，排列组合
QList<QVector<Binsetpara>> FrmBinSet::getAllGroup(QList<QVector<Binsetpara>> val)
{
  int oriSize = val.size();

  QVector<int> tempIndexArr(oriSize);
  tempIndexArr[oriSize - 1] = -1;
  QVector<int> tempLengthArr(oriSize);
  for (int i = 0; i < oriSize; i++){
    tempLengthArr[i] = val[i].size();
  }

  QList<QVector<Binsetpara>> newList;
  bool completeFlag = false;
  while (!completeFlag){
    int changeIndex = val.size() - 1;
    bool isRightIndex = false;
    while (!isRightIndex){
      tempIndexArr[changeIndex] += 1;
      if (tempIndexArr[changeIndex] >= tempLengthArr[changeIndex]){
        if (changeIndex == 0){
          isRightIndex = true;
          completeFlag = true;
        }
        else{
          tempIndexArr[changeIndex--] = 0;
        }
      }
      else{
        isRightIndex = true;
      }
    }
    if (isRightIndex && !completeFlag){
      QVector<Binsetpara> pointVec;
      for (int i = 0; i != val.size(); i++){
        pointVec.push_back(val[i][tempIndexArr[i]]);
      }
      newList.push_back(pointVec);
    }
  }
  return newList;
}

//从临时分级参数设置窗口返回的消息，在当前页面显示临时分级参数的各种组合参数
void FrmBinSet::mtvbinparadisp(int iindex)
{
    if(iindex == itag){
        QSqlDatabase mydb;
        if(QSqlDatabase::contains("qt_sql_default_connection"))
          mydb = QSqlDatabase::database("qt_sql_default_connection");
        else
          mydb = QSqlDatabase::addDatabase("QSQLITE");
//        QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE","DISK");
        mydb.setDatabaseName(unitpublic::gscurprofile);    //连接指定的工程文件（*.db3）
        if (!mydb.open())
        {
            unitpublic::gpwritelog(QString("打开工程文件失败:%1").arg(mydb.lastError().text()));
            return;
        }
        else
        {
            //QList<Binpara> lstbinpara[TESTITEM_COUNT*LED_COUNT];      //最多可分级参数类型数量

            QList<QVector<Binsetpara>> lstbinpara;
      //      ibincount = 0;//在页面初始化时，已经根据基本参数设置中的参与分级数量计算获得
            for (int i=0;i<LED_COUNT;i++) {
                int iledindex = i;  //晶片序号
                for (int k=0;k<TESTITEM_COUNT;k++) {
                    if(unitprofile::testitempara[itag][i][k].bin_enable){   //测试项目参与分级
                        QSqlQuery mysql(mydb);
                        QString sitemname = lstTestItemName[k]; //参数名称
                        if(lstTestItemName.at(k) == "CIE_x"){
                            mysql.exec(QString("select bin_name,x0,y0,x1,y1,x2,y2,x3,y3 from binxypara_temp where station_id=%1 and led_index=%2 ").arg(itag).arg(iledindex));
                            if(mysql.next()){
                                QVector<Binsetpara> lstmvalue;
                                mysql.first();
                                mysql.previous();
                                lstbinxypkg.clear();
                                while(mysql.next()){   //结果集为空的，不加入sql列表
                                    Binsetpara pval;
                                    pval.xybinname = mysql.value(0).toString();
                                    pval.itemname = "CIE_xy";
                                    lstmvalue.append(pval);
                                    BinXyPkg binxypkg;
                                    binxypkg.name = mysql.value(0).toString();
                                    binxypkg.pt0 =  QPointF(mysql.value(1).toDouble(),mysql.value(2).toDouble());
                                    binxypkg.pt1 =  QPointF(mysql.value(3).toDouble(),mysql.value(4).toDouble());
                                    binxypkg.pt2 =  QPointF(mysql.value(5).toDouble(),mysql.value(6).toDouble());
                                    binxypkg.pt3 =  QPointF(mysql.value(7).toDouble(),mysql.value(8).toDouble());
                                    lstbinxypkg.append(binxypkg);
                                }
                                lstbinpara.append(lstmvalue);
       //                         ibincount ++ ;  //结果集不为空
                            }
                        }else
                        if(lstTestItemName.at(k) == "CIE_y"){
                                //不做处理，上面CIE_x已经处理了
                            continue;
                        }else
                        {
                            mysql.exec(QString("select min_value,max_value from binpara_temp where station_id=%1 and led_index=%2 and item_name='%3'").arg(itag).arg(iledindex).arg(sitemname));
                            if(mysql.next()){
                                QVector<Binsetpara> lstmvalue;
                                mysql.first();
                                mysql.previous();
                                while(mysql.next()){   //结果集为空的，不加入sql列表
                                    Binsetpara pval;
                                    pval.minvalue = mysql.value(0).toDouble();
                                    pval.maxvalue = mysql.value(1).toDouble();
                                    pval.xybinname = "";
                                    lstmvalue.append(pval);
                                }
                                lstbinpara.append(lstmvalue);
       //                         ibincount ++ ;  //结果集不为空
                            }
                        }
                    }
                }
            }
            QList<QVector<Binsetpara>> lstpara = getAllGroup(lstbinpara);      //排列组合，形成分级参数
            QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvbinset->model());
            for (int i=3;i<model->rowCount();i++) {
                for (int k=1;k<model->columnCount();k++) {
                    model->setData(model->index(i,k),"");       //初始化先清空数据
                }
            }
            for (int i=0;i<lstpara.count();i++) {
                int icol = 3;   //从第3列开始显示分级参数
                for (int k=0;k<ibincount;k++) {
                    if(lstpara.at(i).at(k).itemname == "CIE_xy"){
                        model->setData(model->index(i+3,icol),lstpara.at(i).at(k).xybinname);
                        icol++;
                    }else{
                        model->setData(model->index(i+3,icol),lstpara.at(i).at(k).minvalue);
                        icol++;
                        model->setData(model->index(i+3,icol),lstpara.at(i).at(k).maxvalue);
                        icol++;
                        }
                    }
                if(i>255){  //最多支持256BIN
                    break;
                }
            }
        }
        mydb.close();
   }
}

//通过色区分级name值获取该色区在列表中的序号
int FrmBinSet::getindexfrombinxypkg(QString name)
{
    int result = -1;
    for (int i=0;i<lstbinxypkg.count();i++) {
        if(lstbinxypkg.at(i).name == name){
            result = i;
        }
    }
    return result;  //不存在时返回 -1
}
//鼠标悬停后触发entered事件，处理提示信息
void FrmBinSet::on_tvbinset_entered(const QModelIndex &index)
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvbinset->model());
    if((model->data(model->index(2,index.column()))=="CIE_xy")&&(index.row()>2)){
        QString sledindex=model->data(model->index(0,index.column())).toString();
        int iledindex=0;
        if(sledindex.contains("1")) iledindex=LED_1;
        if(sledindex.contains("2")) iledindex=LED_2;
        if(sledindex.contains("3")) iledindex=LED_3;
        if(lstbinxypkg.count()>0){
            for (int i=0;i<lstbinxypkg.count();i++) {       //色区参数列表，包括R1/R2...等以及对应4坐标值
                if(lstbinxypkg.at(i).name == index.data().toString())
                    QToolTip::showText(QCursor::pos(),QString("%1,%2\r\n%3,%4\r\n%5,%6\r\n%7,%8")   //提示R1/R2...等分级参数名称对应的具体坐标值参数
                                       .arg(QString::number(lstbinxypkg.at(i).pt0.x(),'f',4)).arg(QString::number(lstbinxypkg.at(i).pt0.y(),'f',4))
                                       .arg(QString::number(lstbinxypkg.at(i).pt1.x(),'f',4)).arg(QString::number(lstbinxypkg.at(i).pt1.y(),'f',4))
                                       .arg(QString::number(lstbinxypkg.at(i).pt2.x(),'f',4)).arg(QString::number(lstbinxypkg.at(i).pt2.y(),'f',4))
                                       .arg(QString::number(lstbinxypkg.at(i).pt3.x(),'f',4)).arg(QString::number(lstbinxypkg.at(i).pt3.y(),'f',4)));
            }

        }else   //lstbinxypkg为空的时候，从表binset_para中查询色区提示信息，因为lstbinxypkg是从下一级分级参数设置传递过来的，但初始时是从binset_para分级参数表中获取的
        {
            QString binxyname = index.data().toString();    //色区名，如R1/R2。。。

            QSqlDatabase mydb;
            if(QSqlDatabase::contains("qt_sql_default_connection"))
              mydb = QSqlDatabase::database("qt_sql_default_connection");
            else
              mydb = QSqlDatabase::addDatabase("QSQLITE");
            mydb.setDatabaseName(unitpublic::gscurprofile);    //连接指定的工程文件（*.db3）
            if (!mydb.open())       //打开数据库失败       //数据库连接必须跟操作在一起，否则会提示错误
            {
                unitpublic::gpwritelog(QString("savebinset,打开工程文件失败:%1").arg(mydb.lastError().text()));
                return;
            }
            else
            {
                QSqlQuery mysql(mydb);
                QString ssql = QString("select x0_%1,y0_%1,x1_%1,y1_%1,x2_%1,y2_%1,x3_%1,y3_%1 from binset_para where station_id=%2 and binxy%1_name='%3'").arg(iledindex+1).arg(itag).arg(binxyname);
                qDebug() << ssql;
                mysql.exec(ssql);    //查询分级参数表
                QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvbinset->model());   //注意字段列表字符串sfieldname中包含了表结构、tableview显示列的顺序关系
                while (mysql.next()) {
                    QToolTip::showText(QCursor::pos(),QString("%1,%2\r\n%3,%4\r\n%5,%6\r\n%7,%8")   //提示R1/R2...等分级参数名称对应的具体坐标值参数
                                       .arg(QString::number(mysql.value(0).toDouble(),'f',4)).arg(QString::number(mysql.value(1).toDouble(),'f',4))
                                       .arg(QString::number(mysql.value(2).toDouble(),'f',4)).arg(QString::number(mysql.value(3).toDouble(),'f',4))
                                       .arg(QString::number(mysql.value(4).toDouble(),'f',4)).arg(QString::number(mysql.value(5).toDouble(),'f',4))
                                       .arg(QString::number(mysql.value(6).toDouble(),'f',4)).arg(QString::number(mysql.value(7).toDouble(),'f',4)));
                    break;
                }
            }
            mydb.close();
        }
    }
}

//保存分级参数设置，接收主窗口“保存文件”按钮信号
void FrmBinSet::savebinset(int iindex)
{
    if(iindex != itag) return;
    //1.遍历并获取当前分级参数
    QString ssql_field = "";    //表字段名称列表
    QString ssql_value = "";    //字段对应值列表
    int iledindex=0;
    QString sitemname="";
    QStringList lstsql;
    lstsql.clear();
    lstsql.append(QString("delete from binset_para where station_id=%1").arg(itag));    //先删除当前工位的分级参数
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvbinset->model());
    for (int irow=3;irow<256+3;irow++) {    //从第三行开始遍历，最多256BIN
        ssql_field = "station_id,bin_number,bin_name,bin_memo";
        ssql_value = QString("%1,%2,'%3','%4'")
                        .arg(itag)  //测试工位
                        .arg(model->data(model->index(irow,0)).toString())  //BIN号
                        .arg(model->data(model->index(irow,1)).toString())  //BIN名称
                        .arg(model->data(model->index(irow,2)).toString());  //BIN备注
        int icol=3;         //从第三列开始遍历
        for (int k=0;k<ibincount;k++) {
            if(model->data(model->index(0,icol)).toString().contains("1"))
                iledindex=LED_1;        //晶一
            if(model->data(model->index(0,icol)).toString().contains("2"))
                iledindex=LED_2;        //晶二
            if(model->data(model->index(0,icol)).toString().contains("3"))
                iledindex=LED_3;        //晶三
            sitemname = model->data(model->index(1,icol)).toString();   //分级参数名，VF/VFL/IV
            if(sitemname=="CIE_xy"){        //XY分级时，要插入binxy1_name值以及对应x0_1/y0_1。。。
                QString xybin_name = model->data(model->index(irow,icol)).toString().trimmed();   //xy分级色区名
                int xybinindex = getindexfrombinxypkg(xybin_name);
                if(xybinindex >= 0){ //xybin_name字符不存在则不处理，debug状态下竟然不报错，后来在release下调试才发现
                ssql_field = ssql_field + QString(",binxy%1_name,x0_%1,y0_%1,x1_%1,y1_%1,x2_%1,y2_%1,x3_%1,y3_%1").arg(iledindex+1);    //注意：晶片序号的关系
                ssql_value = ssql_value + QString(",'%1',%2,%3,%4,%5,%6,%7,%8,%9")
                                            .arg(xybin_name)       //R1/R2...色区名，注意：xybin_name在lstbinxypkg中不存在时的处理
                                            .arg(lstbinxypkg.at(xybinindex).pt0.x())  //保存色区对应的四坐标值
                                            .arg(lstbinxypkg.at(xybinindex).pt0.y())
                                            .arg(lstbinxypkg.at(xybinindex).pt1.x())
                                            .arg(lstbinxypkg.at(xybinindex).pt1.y())
                                            .arg(lstbinxypkg.at(xybinindex).pt2.x())
                                            .arg(lstbinxypkg.at(xybinindex).pt2.y())
                                            .arg(lstbinxypkg.at(xybinindex).pt3.x())
                                            .arg(lstbinxypkg.at(xybinindex).pt3.y());
                }
                icol++;     //CIE_xy分级只占用1列，即色区名称R1/R2。。。
            }else
            {               //其他参数分级，要插入_MIN/MAX即下限与上限值
                ssql_field = ssql_field + QString(",%1%2_MIN,%1%2_MAX").arg(sitemname).arg(iledindex+1);    //注意：晶片序号的关系
                ssql_value = ssql_value + QString(",%1,%2")
                                            .arg(model->data(model->index(irow,icol)).toString())
                                            .arg(model->data(model->index(irow,icol+1)).toString());
                icol++; //其他分级参数占2列，即MIN/MAX
                icol++;
            }
        }
        lstsql.append(QString("insert into binset_para (%1) values (%2)").arg(ssql_field).arg(ssql_value)); //保存分级参数，插入binset_para表
    }
    //2.分级参数存入数据表中
    QSqlDatabase mydb;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      mydb = QSqlDatabase::database("qt_sql_default_connection");
    else
      mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(unitpublic::gscurprofile);    //连接指定的工程文件（*.db3）
    if (!mydb.open())       //打开数据库失败       //数据库连接必须跟操作在一起，否则会提示错误
    {
        unitpublic::gpwritelog(QString("savebinset,打开工程文件失败:%1").arg(mydb.lastError().text()));
        return;
    }
    else
    {
        QSqlQuery mysql(mydb);
        for (int i=0;i<lstsql.count();i++) {
            mysql.exec(lstsql.at(i));    //插入分级参数
            qDebug() << lstsql.at(i);
        }
    }
    mydb.close();
//    unitpublic::testcmd[itag] = CMD_TEST_INIT;    //初始化导入参数
    unitpublic::filedb2memdb(itag);

    QMessageBox::information(NULL,"提示","当前测试工位分级参数保存完成！");
}

//从数据表 binset_para 中获取分级参数
void FrmBinSet::readbinsetpara()
{
    QSqlDatabase mydb;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      mydb = QSqlDatabase::database("qt_sql_default_connection");
    else
      mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(unitpublic::gscurprofile);    //连接指定的工程文件（*.db3）
    if (!mydb.open())       //打开数据库失败       //数据库连接必须跟操作在一起，否则会提示错误
    {
        unitpublic::gpwritelog(QString("savebinset,打开工程文件失败:%1").arg(mydb.lastError().text()));
        return;
    }
    else
    {
        QSqlQuery mysql(mydb);
        mysql.exec(QString("select %1 from binset_para where station_id=%2").arg(sfieldname).arg(itag));    //查询分级参数表
        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tvbinset->model());   //注意字段列表字符串sfieldname中包含了表结构、tableview显示列的顺序关系
        int irow=3;
        while (mysql.next()) {
            for (int icol=0;icol<model->columnCount();icol++) {
                model->setData(model->index(irow,icol),mysql.value(icol).toString());
            }
            irow++;
        }
        mysql.exec(QString("select distinct binxy1_name,x0_1,y0_1,x1_1,y1_1,x2_1,y2_1,x3_1,y3_1 from binset_para where station_id=%1").arg(itag));    //查询xy分级参数表
        while (mysql.next()) {
            BinXyPkg binxypkg;
            binxypkg.name = mysql.value(0).toString();
            binxypkg.pt0 =  QPointF(mysql.value(1).toDouble(),mysql.value(2).toDouble());
            binxypkg.pt1 =  QPointF(mysql.value(3).toDouble(),mysql.value(4).toDouble());
            binxypkg.pt2 =  QPointF(mysql.value(5).toDouble(),mysql.value(6).toDouble());
            binxypkg.pt3 =  QPointF(mysql.value(7).toDouble(),mysql.value(8).toDouble());
            lstbinxypkg.append(binxypkg);

        }
    }
    mydb.close();

}

void FrmBinSet::mupdatebinpara(int iindex)       //刷新参数，修改并保存基本参数后，需要重置分级参数
{
    if(iindex==itag)
    {
        lstbinxypkg.clear();
        BindispInit();
        readbinsetpara();
    }
}
