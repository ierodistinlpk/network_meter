#include "testwindow.h"
#include "ui_testwindow.h"
#include "QInputDialog"
 #include <QComboBox>
#include <QVector>
#include <sstream>
#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_curve.h>
#include <qwt-qt4/qwt_interval_data.h>
#include <qwt-qt4/qwt_painter.h>
#include <qwt-qt4/qwt_scale_map.h>
#include <QMessageBox>
#include "histogram_item.h"
#include "points_item.h"
testwindow::testwindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::testwindow)
{
    ui->setupUi(this);
    db=QSqlDatabase::addDatabase("QPSQL");
    potolok=0;
    ///моя секция. заводим значеиня виджетов
    mainPlot = new QwtPlot(QwtText("graphics"), ui->graphicsView);
    mainPlot->clear();
    mainPlot->resize(ui->graphicsView->width()-230,ui->graphicsView->height());
    mainPlot->show();
}

testwindow::~testwindow()
{
    delete ui;
}

void testwindow::on_agentButton_clicked()
{
    item_type = Agents;
    db.open();
    QSqlQuery qwery;
    qwmodel.setQuery("select name from agent",db);
    ui->tableView->setModel(&qwmodel);
    db.close();
}

void testwindow::on_eventypetButton_clicked()
{
    item_type = EventTypes;
    db.open();
    QSqlQuery qwery;
    qwmodel.setQuery("select * from event_type",db);
    ui->tableView->setModel(&qwmodel);
    db.close();
}

void testwindow::on_targetButton_clicked()
{
    item_type = Targets;
    db.open();
    QSqlQuery qwery;
    qwmodel.setQuery("select * from target",db);
    ui->tableView->setModel(&qwmodel);
    db.close();
}

void testwindow::on_probeButton_clicked()
{
    item_type = Probes;
    bool bOk;
    QString qwery="select * from probe ";
    QString agname=ui->lineEditpragent->text();
    if(bOk)
    {
    db.open();
    if(!agname.isEmpty())
        qwery=qwery+" where name='"+agname+"'";
    qwmodel.setQuery(qwery,db);
    ui->tableView->setModel(&qwmodel);
    db.close();
    }

}

void testwindow::on_aboutButton_clicked()
{
    QMessageBox::information(0,"about","Statistic Analyzer for network testing module. \n This program created by Michael Kartashov aka IERO. \n June, 2009");
}

void testwindow::on_helpButton_clicked()
{
    QMessageBox::information(0,"help","Please, view readme file");
}

void testwindow::on_eventcleanButton_clicked()
{
///заполняем ангенты
    ui->comboevagent->clear();
    item_type = Agents;
    db.open();
    QString sqlstr="select name from agent";
    qwsecmodel.setQuery(sqlstr,db);
    for (int i=0;i<qwsecmodel.rowCount();i++)
    {
        ui->comboevagent->insertItem(i,qwsecmodel.record(i).value("name").toString(),QVariant(qwsecmodel.record(i).value("name").toString()));
    }
    ui->comboevagent->insertItem(0,"all",QVariant("all"));
    ui->comboevagent->setCurrentIndex(0);
    /// заполняем зонды
    ui->comboevprobe->clear();
    sqlstr="select \"ID_PROBE\" from probe ";
    qwsecmodel.setQuery(sqlstr,db);
    for (int i=0;i<qwsecmodel.rowCount();i++)
    {
        ui->comboevprobe->insertItem(i,qwsecmodel.record(i).value("ID_PROBE").toString(),QVariant(qwsecmodel.record(i).value("ID_PROBE").toString()));
    }
    ui->comboevprobe->insertItem(0,"all",QVariant("-1"));
    ui->comboevprobe->setCurrentIndex(0);
    ///запиливаем типы ошибок
    ui->comboevtype->clear();
    sqlstr="select * from event_type order by is_err, code";
    qwsecmodel.setQuery(sqlstr,db);
    for (int i=0;i<qwsecmodel.rowCount();i++)
    {
        ui->comboevtype->insertItem(i,qwsecmodel.record(i).value("name").toString(),QVariant(qwmodel.record(i).value("id_type").toString()));
    }
    ui->comboevtype->insertItem(0,"all",QVariant("-1"));
    ui->comboevtype->setCurrentIndex(0);
    ui->comboevadr->clear();
    sqlstr="select distinct adress from event order by adress";
    qwsecmodel.setQuery(sqlstr,db);
    for (int i=0;i<qwsecmodel.rowCount();i++)
    {
        ui->comboevadr->insertItem(i,qwsecmodel.record(i).value("adress").toString(),QVariant(qwmodel.record(i).value("adress").toString()));
    }
    ui->comboevadr->insertItem(0,"all",QVariant("-1"));
    ui->comboevadr->setCurrentIndex(0);

    ///выставляем поля:
    ui->lineevcyc1->setText("0");
    ui->lineevcyc2->setText("0");
    ui->lineEditeventinterval->setText("0");
    ///выставляем время
     sqlstr="select max(timestmp) from result";
    qwsecmodel.setQuery(sqlstr,db);
    ui->dateevent2->setDateTime(qwsecmodel.record(0).value(0).toDateTime());
    ///минимум из БД
     sqlstr="select min(timestmp) from result";
    qwsecmodel.setQuery(sqlstr,db);
    ui->dateevnt1->setDateTime(qwsecmodel.record(0).value(0).toDateTime());
    db.close();
}

void testwindow::on_comboevagent_activated(QString )
{
    ui->comboevprobe->clear();
    db.open();
    QString sqlstr="select \"ID_PROBE\" from probe ";
    if(ui->comboevagent->currentText()!="all")
        sqlstr+=" where name='"+ui->comboevagent->currentText()+"'";
    QSqlQuery qwery(sqlstr,db);
    qwsecmodel.setQuery(qwery);
    for (int i=0;i<qwsecmodel.rowCount();i++)
    {
        ui->comboevprobe->insertItem(i,qwsecmodel.record(i).value("ID_PROBE").toString());
    }
    ui->comboevprobe->insertItem(0,"all",QVariant("-1"));
    ui->comboevprobe->setCurrentIndex(0);
    db.close();
}

void testwindow::on_rttcleanButton_clicked()
{
    ///заполняем ангенты
    ui->comborttagent->clear();
    item_type = Agents;
    db.open();
    QSqlQuery qwery("select name from agent",db);
    qwsecmodel.setQuery(qwery);
    for (int i=0;i<qwsecmodel.rowCount();i++)
    {
        ui->comborttagent->insertItem(i,qwsecmodel.record(i).value("name").toString());
    }
    ui->comborttagent->insertItem(0,"all",QVariant("all"));
    ui->comborttagent->setCurrentIndex(0);
    /// заполняем зонды
    ui->comborttprobe->clear();
    QString sqlstr="select \"ID_PROBE\" from probe ";
    qwery.exec(sqlstr);
    qwsecmodel.setQuery(qwery);
    for (int i=0;i<qwsecmodel.rowCount();i++)
    {
        ui->comborttprobe->insertItem(i,qwsecmodel.record(i).value("ID_PROBE").toString());
    }
    ui->comborttprobe->insertItem(0,"all",QVariant("-1"));
    ui->comborttprobe->setCurrentIndex(0);
    ///выставляем поля:
    ui->linerttcyc1->setText("0");
    ui->linerttcyc2->setText("0");
    ui->linerttstep->setText("0");
    ///выставляем время

    ///минимум из БД
     sqlstr="select min(timestmp) from result";
    qwery.exec(sqlstr);
    qwsecmodel.setQuery(qwery);
    ui->datertt1->setDateTime(qwsecmodel.record(0).value(0).toDateTime());
    sqlstr="select max(timestmp) from result";
    qwery.exec(sqlstr);
    qwsecmodel.setQuery(qwery);
    ui->datertt2->setDateTime(qwsecmodel.record(0).value(0).toDateTime());
    db.close();
}

void testwindow::on_comborttagent_activated(QString )
{
    ui->comborttprobe->clear();
    db.open();
    QString sqlstr="select \"ID_PROBE\" from probe ";
    if(ui->comborttagent->currentText()!="all")
        sqlstr+=" where name='"+ui->comborttagent->currentText()+"'";
    QSqlQuery qwery(sqlstr,db);
    qwsecmodel.setQuery(qwery);
    for (int i=0;i<qwsecmodel.rowCount();i++)
    {
        ui->comborttprobe->insertItem(i,qwsecmodel.record(i).value("ID_PROBE").toString());
    }
    ui->comborttprobe->insertItem(0,"all",QVariant("-1"));
    ui->comborttprobe->setCurrentIndex(0);
    db.close();
}

void testwindow::on_probecleanButton_clicked()
{
    ui->lineEditpragent->clear();
}

void testwindow::on_rttintervalButton_clicked()
{
    item_type = Results;
    if(ui->linerttstep->text()!="0")
    {
        QString qwery="select cycle, rtt, timestmp, id_probe from result_node join (result join probe on result.\"ID_PROBE\"=probe.\"ID_PROBE\")on( result.\"ID_PROBE\"=result_node.id_probe and cycle=cycle_num and id_session=\"ID_SESSION\")  where rtt>0 and timestmp between '";
        qwery+=ui->datertt1->dateTime().toString("dd.MM.yyyy hh:mm:ss") + "' and '" + ui->datertt2->dateTime().toString("dd.MM.yyyy hh:mm:ss")+"'";
        if(ui->comborttagent->currentText()!="all")
            qwery+=" and name = '"+ui->comborttagent->currentText()+"' ";
        if(ui->comborttprobe->currentText()!="all")
            qwery+=" and id_probe = " + ui->comborttprobe->currentText();
        if(ui->linerttcyc2->text()!="0")
            qwery+=" and cycle between "+ui->linerttcyc1->text()+" and " + ui->linerttcyc2->text();
        qwery+="order by timestmp, id_probe, cycle";
        db.open();
        qwmodel.setQuery(qwery,db);
        ui->tableView->setModel(&qwmodel);
        db.close();
        ///расчет статистики по величинам
            int starttime=ui->datertt1->dateTime().toTime_t();
            int step = ui->linerttstep->text().toInt(NULL);
            int counts=abs(ui->datertt2->dateTime().toTime_t()-starttime)/step+1;                      ;
            int currentindex,currentval;
            QVector<double> Averages(counts);
            QVector<double> Mins(counts);
            QVector<double> Maxs(counts);
            QVector<double> Tops(counts);
            QVector<double> Bots(counts);
            QVector<double> Deviats(counts);
            QVector<double> Counts(counts);
            potolok=0;
            Deviats.fill(0);
            Averages.fill(0);
            Maxs.fill(0);
            Counts.fill(0);
            Mins.fill(10000000);
            int total=qwmodel.rowCount();
            for (int i=0;i<total;i++)
            {
                currentindex=(qwmodel.record(i).value("timestmp").toDateTime().toTime_t()-starttime)/step;
                if (currentindex>=counts)
                    continue;
                currentval=qwmodel.record(i).value("rtt").toDouble(NULL)/1000;
                Counts[currentindex]++;
                if(Maxs[currentindex]<currentval)
                    Maxs[currentindex]=currentval;
                if(Mins[currentindex]>currentval)
                    Mins[currentindex]=currentval;
            }
            for (int i=0;i<total;i++)
            {
                currentindex=(qwmodel.record(i).value("timestmp").toDateTime().toTime_t()-starttime)/step;
                if (currentindex>=counts)
                    continue;
                currentval=qwmodel.record(i).value("rtt").toDouble(NULL)/1000;
                Averages[currentindex]+=currentval/Counts[currentindex];
                Deviats[currentindex]+=currentval*(currentval/ Counts[currentindex]);
            }
            QVector<QwtDoubleInterval> dTime(counts); //массив по X
            for(int j=0;j<counts;j++)
            {                             ///считаем массив иксов
                dTime[j]=QwtDoubleInterval(j*step,j*step+1);
                if(Counts[j])
                {
                    Deviats[j]-=Averages[j]*Averages[j];
                    Deviats[j]=sqrt(Deviats[j]);
                    Tops[j]=Averages[j]+ Deviats[j];
                    Bots[j]=qMax(Averages[j]-Deviats[j],Mins[j]);
                    if(potolok<Maxs[j])
                        potolok=Maxs[j];
                }
                else
                {
                    Averages[j]=Deviats[j]=Tops[j]=Bots[j]=Maxs[j]=Mins[j]=0;
                }
            }
            std::ostringstream strsrm("");
            strsrm<<"INFO: "<<"\n total: "<<total<<"\n averages:";
            for(int j=0;j<counts;j++)
                strsrm<<" \n "<<Averages[j];
            ui->label->setText(QString(strsrm.str().c_str()));
            mainPlot->clear();
            mainPlot->resize(ui->graphicsView->width()-130,ui->graphicsView->height());
            PointsItem * pointsmax = new PointsItem("rtt intervals");
            pointsmax->setData(QwtIntervalData(dTime,Maxs));
            pointsmax->setColor(Qt::red);
            pointsmax->attach(mainPlot);
            PointsItem * pointsmin = new PointsItem("rtt intervals");
            pointsmin->setData(QwtIntervalData(dTime,Mins));
            pointsmin->setColor(Qt::red);
            pointsmin->attach(mainPlot);

            PointsItem * pointstop = new PointsItem("rtt intervals");
            pointstop->setData(QwtIntervalData(dTime,Tops));
            pointstop->setColor(Qt::darkCyan);
            pointstop->attach(mainPlot);
            PointsItem * pointsbot = new PointsItem("rtt intervals");
            pointsbot->setData(QwtIntervalData(dTime,Bots));
            pointsbot->setColor(Qt::darkCyan);
            pointsbot->attach(mainPlot);
            PointsItem * pointsavg = new PointsItem("rtt intervals");
            pointsavg->setData(QwtIntervalData(dTime,Averages));
            pointsavg->setColor(Qt::green);
            pointsavg->attach(mainPlot);
                       // finally, refresh the plot
            mainPlot->setTitle("distribution rtt in time");
            mainPlot->setAxisTitle(QwtPlot::yLeft, "rtt, milliseconds");
            mainPlot->setAxisTitle(QwtPlot::xBottom, "timeline");
            mainPlot->setAxisScale(QwtPlot::xBottom,dTime[0].minValue(),dTime[dTime.count()-1].maxValue()+1);
            mainPlot->setAxisScale(QwtPlot::yLeft,0,potolok+1);
            mainPlot->replot();
            delete pointsmax;
            delete pointsmin;
            delete pointsavg;
            delete pointstop;
            delete pointsbot;

    }
    else
    {
        QMessageBox::warning(0,"wrong parameter","step not specified.\n request not runned.",QMessageBox::StandardButton(),QMessageBox::StandardButton());
        return;
    }
}

void testwindow::on_rttnumButton_clicked()
{
    item_type = Results;
     QString qwery="select  cycle, number, rtt, timestmp, \"SIZE\" from result_node join (result join probe on result.\"ID_PROBE\"=probe.\"ID_PROBE\")on( result.\"ID_PROBE\"=result_node.id_probe and cycle=cycle_num and id_session=\"ID_SESSION\")  where rtt>0 and timestmp between '";
    qwery+=ui->datertt1->dateTime().toString("dd.MM.yyyy hh:mm:ss") + "' and '" + ui->datertt2->dateTime().toString("dd.MM.yyyy hh:mm:ss")+"'";
 /*   if(ui->comborttagent->currentText()!="all")
        qwery+=" and name = '"+ui->comborttagent->currentText()+"' ";*/
    if(ui->comborttprobe->currentText()!="all")
        qwery+=" and id_probe = " + ui->comborttprobe->currentText();
    else
    {
        QMessageBox::warning(0,"wrong parameter","probe not specified.\n request not runned.",QMessageBox::StandardButton(),QMessageBox::StandardButton());
        return;
    }
    if(ui->linerttcyc2->text()!="0")
        qwery+=" and cycle between "+ui->linerttcyc1->text()+" and " + ui->linerttcyc2->text();
    qwery+="order by number, cycle";
    db.open();
    qwmodel.setQuery(qwery,db);
    //qwmodel.record().value("timestmp").QDateTime::toString("dd.MM.yy H:mm:ss");
    ui->tableView->setModel(&qwmodel);
    qwery="select \"P_COUNT\" from probe where \"ID_PROBE\"=";
    qwery+=ui->comborttprobe->currentText();
    qwsecmodel.setQuery(qwery,db);
    ///расчет статистики по величинам
        int numbers=qwsecmodel.record(0).value(0).toInt(NULL);
        int currentindex=0,currentval=0;
        QVector<double> Averages(numbers);
        QVector<double> Mins(numbers);
        QVector<double> Maxs(numbers);
        QVector<double> Deviats(numbers);
        QVector<int> Counts(numbers);
         QVector<QwtDoubleInterval> dNums(numbers); //массив по X
         QVector<double> Tops(numbers);
         QVector<double> Bots(numbers);
         potolok=0;
        Deviats.fill(0);
        Averages.fill(0);
        Maxs.fill(0);
        Counts.fill(0);
        Mins.fill(10000000);
        int total=qwmodel.rowCount();
        for (int i=0;i<total;i++)
        {
            currentindex=qwmodel.record(i).value("number").toInt(NULL);
           if (currentindex>=numbers)
                    continue;
            currentval=qwmodel.record(i).value("rtt").toDouble(NULL)/1000;
            Counts[currentindex]++;
            if(Maxs[currentindex]<currentval)
                Maxs[currentindex]=currentval;
            if(Mins[currentindex]>currentval)
                Mins[currentindex]=currentval;
        } 
        for (int i=0;i<total;i++)
        {
            currentindex=qwmodel.record(i).value("number").toInt(NULL);
            if (currentindex>=numbers)
                    continue;
            if (Counts[currentindex])
            {
                currentval=qwmodel.record(i).value("rtt").toDouble(NULL)/1000; //с переводом в милисекунды
                Averages[currentindex]+=currentval/(double)Counts[currentindex];
                Deviats[currentindex]+=currentval*(currentval/(double)Counts[currentindex]);
            }

        }
        for(int j=0;j<numbers;j++)
        {
            dNums[j]=QwtDoubleInterval(j,j);
            if(Counts[j])
            {
                Deviats[j]-=Averages[j]*Averages[j];
                Deviats[j]=sqrt(Deviats[j]);
                Tops[j]=Averages[j]+Deviats[j];
                Bots[j]=qMax(Averages[j]-Deviats[j],Mins[j]);
                if(potolok<Maxs[j])
                        potolok=Maxs[j];
            }
            else
            {
                 Averages[j]=Deviats[j]=Tops[j]=Bots[j]=Maxs[j]=Mins[j]=0;
            }
        }
        std::ostringstream strsrm("");
        strsrm<<"INFO: "<<"\n total: "<<total<<"\n averages: ";
        for(int j=0;j<numbers;j++)
                strsrm<<" \n "<<Averages[j];
        ui->label->setText(QString(strsrm.str().c_str()));


            mainPlot->clear();
            mainPlot->resize(ui->graphicsView->width()-130,ui->graphicsView->height());
            PointsItem * pointstop = new PointsItem("rtt time");
            pointstop->setData(QwtIntervalData(dNums,Tops));
            pointstop->setColor(Qt::darkCyan);
            pointstop->attach(mainPlot);

            PointsItem * pointsbot = new PointsItem("rtt time");
            pointsbot->setData(QwtIntervalData(dNums,Bots));
            pointsbot->setColor(Qt::darkCyan);
            pointsbot->attach(mainPlot);

            PointsItem * pointsmax = new PointsItem("rtt time");
            pointsmax->setData(QwtIntervalData(dNums,Maxs));
            pointsmax->setColor(Qt::red);
            pointsmax->attach(mainPlot);

            PointsItem * pointsmin = new PointsItem("rtt time");
            pointsmin->setData(QwtIntervalData(dNums,Mins));
            pointsmin->setColor(Qt::red);
            pointsmin->attach(mainPlot);

            PointsItem * pointsavg = new PointsItem("rtt time");
            pointsavg->setData(QwtIntervalData(dNums,Averages));
            pointsavg->setColor(Qt::green);
            pointsavg->attach(mainPlot);
                       // finally, refresh the plot
            mainPlot->setTitle("probe rtt time");
            mainPlot->setAxisTitle(QwtPlot::yLeft, "rtt, milliseconds");
            mainPlot->setAxisTitle(QwtPlot::xBottom, "request number");
            mainPlot->setAxisScale(QwtPlot::xBottom,dNums[0].minValue(),dNums[dNums.count()-1].maxValue()+1);
            mainPlot->setAxisScale(QwtPlot::yLeft,0,potolok+1);
            mainPlot->replot();
            delete pointsmax;
            delete pointsavg;
            delete pointsmin;
            delete pointstop;
            delete pointsbot;
    db.close();
}

void testwindow::on_rttavgButton_clicked()
{
    item_type = Results;
     QString qwery="select name, id_probe, cycle, number, rtt, timestmp, \"SIZE\" from result_node join (result join probe on result.\"ID_PROBE\"=probe.\"ID_PROBE\")on( result.\"ID_PROBE\"=result_node.id_probe and cycle=cycle_num and id_session=\"ID_SESSION\")  where rtt>0 and timestmp between '";
    qwery+=ui->datertt1->dateTime().toString("dd.MM.yyyy hh:mm:ss") + "' and '" + ui->datertt2->dateTime().toString("dd.MM.yyyy hh:mm:ss")+"'";
    if(ui->comborttagent->currentText()!="all")
        qwery+=" and name = '"+ui->comborttagent->currentText()+"' ";
    if(ui->comborttprobe->currentText()!="all")
        qwery+=" and id_probe = " + ui->comborttprobe->currentText();
    if(ui->linerttcyc2->text()!="0")
        qwery+=" and cycle between "+ui->linerttcyc1->text()+" and " + ui->linerttcyc2->text();
    qwery+="order by name, id_probe, cycle, number";
//    QMessageBox::information(0,"",qwery,QMessageBox::StandardButton(),QMessageBox::StandardButton());
    db.open();
    qwmodel.setQuery(qwery,db);
    ui->tableView->setModel(&qwmodel);
    ///расчет статистики по величинам
    //считать для всех скопом.
        int total=qwmodel.rowCount();
        double Expected=0;
        double Deviation=0;
        double min=1000000,max=0,temp;
        min=max=qwmodel.record(0).value("rtt").toInt(NULL)/1000;
        QVector<int> tmp(total);
        for (int i=0;i<total;i++)
        {
            tmp[i]=qwmodel.record(i).value("rtt").toInt(NULL);
            temp=tmp[i]/1000.0;
            Expected+=temp/(double)total;
            Deviation+=temp*(temp/(double)total);
            if(min>temp)
                min=temp;
            if(max<temp)
                max=temp;
        }
        db.close();
        Deviation-=Expected*Expected;
        Deviation=sqrt(Deviation);
        std::ostringstream strsrm("");
        strsrm<<"INFO: "<<"\n total: "<<total<<"\n Expected \n value: "<<Expected<<" \n Deviation: \n "<<Deviation<<"\n Max: \n "<<max<<"\n Min: \n "<<min;
        ui->label->setText(QString(strsrm.str().c_str()));
        QVector<double> counts((max-min)+1);
        counts.fill(0);
        QwtArray<QwtDoubleInterval> intervals((max-min)+1);
        for(int j=0;j<counts.size();j++)
        {
            intervals[j] = QwtDoubleInterval(min+j, min+j+1);
            for (int i=0;i<total;i++)
                if(tmp[i]/1000==min+j)
                   counts[j]++;
        }
        potolok=0;
        for (int i=0;i<counts.size();i++)
            if(potolok<counts[i])
                potolok=counts[i];
    /*РИСУЕМ ВСЕ*/
            mainPlot->clear();
            mainPlot->resize(ui->graphicsView->width()-130,ui->graphicsView->height());
            HistogramItem * histogram= new HistogramItem("rtt frequency distribution");
            histogram->setColor(Qt::green);
            histogram->setData(QwtIntervalData(intervals, counts));
            histogram->attach(mainPlot);
            mainPlot->setAxisScale(QwtPlot::xBottom,0,100,10);
            mainPlot->setTitle("result distribution");
            mainPlot->setAxisTitle(QwtPlot::xBottom, "round trip time, milliseconds");
            mainPlot->setAxisTitle(QwtPlot::yLeft, "frequency");
            mainPlot->setAxisScale(QwtPlot::xBottom,intervals[0].minValue()-1,intervals[intervals.count()-1].maxValue()+1);
           mainPlot->setAxisScale(QwtPlot::yLeft,0,potolok+1);
            mainPlot->replot();
            delete histogram;
}

void testwindow::on_eventButton_clicked()
{
    item_type = Events;

    QString qwery="select event_type.\"name\" , count(*)as \"count\", id_probe, timestp from event join (result join probe on result.\"ID_PROBE\"=probe.\"ID_PROBE\") on ( result.\"ID_PROBE\"=event.id_probe and cycle_num=cycle and id_session=\"ID_SESSION\")  join event_type on event_type.id_type=event.id_type where timestmp between '";
    qwery+=ui->dateevnt1->dateTime().toString("dd.MM.yyyy hh:mm:ss") + "' and '" + ui->dateevent2->dateTime().toString("dd.MM.yyyy hh:mm:ss")+"'";
    if(ui->comboevagent->currentText()!="all")
        qwery+=" and name = '"+ui->comboevagent->currentText()+"' ";
    if(ui->comboevprobe->currentText()!="all")
        qwery+=" and id_probe = " + ui->comboevprobe->currentText();
    if(ui->comboevadr->currentText()!="all")
        qwery+=" and adress = '" + ui->comboevadr->currentText()+"' ";
    if(ui->comboevtype->currentText()!="all")
        qwery+=" and event_type.\"name\" = '" + ui->comboevtype->currentText()+"' ";
    if(ui->lineevcyc2->text()!="0")
        qwery+=" and cycle between "+ui->lineevcyc1->text()+" and " + ui->lineevcyc2->text();
    qwery+=" group by id_probe, cycle_num, timestp, event_type.\"name\"  order by timestp";
 //   QMessageBox::information(0,"",qwery,QMessageBox::StandardButton(),QMessageBox::StandardButton());
    db.open();
    qwmodel.setQuery(qwery,db);
    ui->tableView->setModel(&qwmodel);
    ///расчет статистики по величинам
    if (ui->lineEditeventinterval->text()!="0")
    {

    ///расчет статистики по величинам
        int starttime=ui->dateevnt1->dateTime().toTime_t();
        int step = ui->lineEditeventinterval->text().toInt(NULL);
        int counts=abs(ui->dateevent2->dateTime().toTime_t()-starttime)/step+1;
        int currentindex,currentval;
        int total=0;
        int tmin=1000000,tmax=0;
        float Expected=0, Deviated=0;
        QVector<int> totals(counts);
        totals.fill(0);
        int rows=qwmodel.rowCount();
         std::ostringstream s("");
         s<<rows;
        for (int i=0;i<rows;i++)
        {
            currentindex=(qwmodel.record(i).value("timestp").toDateTime().toTime_t()-starttime)/step;
            currentval=qwmodel.record(i).value("count").toInt(NULL);
            totals[currentindex]+=currentval;
        }
        for (int j=0;j<counts;j++)
        {
            total+=totals[j];
            Expected+=(double)totals[j]/(double)counts;
            Deviated+=(double)totals[j]*(double)totals[j]/(double)counts;
            if(tmin>totals[j])
                tmin=totals[j];
            if(tmax<totals[j])
                tmax=totals[j];
        }
        Deviated-=Expected*Expected;
        Deviated=sqrt(Deviated);
        std::ostringstream strsrm("");
        strsrm<<"INFO: "<<"\n total: "<<total<<" \n Expexted: "<<Expected<<" \n Deviation: "<<Deviated;
        ui->label->setText(QString(strsrm.str().c_str()));
/*РИСУЕМ ВСЕ*/
        if(ui->checkBox->isChecked())
        {
         int  totcnt=(tmax-tmin)/10+1;
        QwtArray<QwtDoubleInterval> intervals(totcnt);
        QwtArray<double> values(totcnt);
        values.fill(0);
            for(int j=0;j<totcnt;j++)
             {
                intervals[j] = QwtDoubleInterval(tmin+10*j+1, tmin+10*j + 10);
                for(int k=0;k<counts;k++)
                    if((totals[k]-tmin)/10==j+tmin)
                        values[j]+=1;
            }
            potolok=0;
            for(int j=0;j<values.size();j++)
                if(potolok<values[j])
                   potolok=values[j];
            mainPlot->clear();
            mainPlot->resize(ui->graphicsView->width()-130,ui->graphicsView->height());
            HistogramItem * histogram= new HistogramItem("hist1");
                histogram->setColor(Qt::red);
              //  histogram->setXAxis(5);
            histogram->setData(QwtIntervalData(intervals, values));
            histogram->attach(mainPlot);
            mainPlot->setTitle("events frequency");
            mainPlot->setAxisTitle(QwtPlot::xBottom, "events in time count");
            mainPlot->setAxisTitle(QwtPlot::yLeft, "frequency");
            mainPlot->setAxisScale(QwtPlot::xBottom,intervals[0].minValue()-1,intervals[intervals.count()-1].maxValue()+1);
            mainPlot->setAxisScale(QwtPlot::yLeft,0,potolok+1);
            mainPlot->replot();
            delete histogram;
        }
        else
        {
 // рисуем временно-зависимую структуру

            QVector<double> Counts(counts);
            Counts.fill(0);
            int total=qwmodel.rowCount();
            for (int i=0;i<total;i++)
            {
                currentindex=(qwmodel.record(i).value("timestp").toDateTime().toTime_t()-starttime)/step;
                Counts[currentindex]++;
            }
            potolok=0;
            for(int j=0;j<Counts.size();j++)
                if(potolok<Counts[j])
                   potolok=Counts[j];
            QVector<QwtDoubleInterval> dTime(counts); //массив по X
            for(int j=0;j<counts;j++)
            {                             ///считаем массив иксов
                dTime[j]=QwtDoubleInterval(j*step,j*step+1);
            }
            std::ostringstream strsrm("");
            strsrm<<"INFO: "<<"\n total: "<<total<<"\n averages: \n";
            for(int j=0;j<counts;j++)
                strsrm<<" \n "<<Counts[j];
            ui->label->setText(QString(strsrm.str().c_str()));
            mainPlot->clear();
            PointsItem * pointscount = new PointsItem("counts");
            pointscount->setData(QwtIntervalData(dTime,Counts));
            pointscount->setColor(Qt::red);
            pointscount->attach(mainPlot);

                       // finally, refresh the plot
            mainPlot->setTitle("distribution events in time");
            mainPlot->setAxisTitle(QwtPlot::yLeft, "count");
            mainPlot->setAxisTitle(QwtPlot::xBottom, "timeline");
            mainPlot->setAxisScale(QwtPlot::xBottom,dTime[0].minValue(),dTime[dTime.count()-1].maxValue()+1);
            mainPlot->setAxisScale(QwtPlot::yLeft,0,potolok+1);
            mainPlot->replot();
            delete pointscount;
        }
    }
    else
    {
        //считать для всех скопом.
        int total=0;
        for (int i=0;i<qwmodel.rowCount();i++)
        {
          total+=qwmodel.record(i).value("count").toInt(NULL);
        }
        std::ostringstream strsrm("");
        strsrm<<"INFO: "<<"\n total: "<<total<<" \n";
        ui->label->setText(QString(strsrm.str().c_str()));
        mainPlot->clear();
        mainPlot->replot();
    }
    db.close();
}

void testwindow::on_losteventButton_clicked()
{

    item_type = Losted;
    QString qwery="select count(*) as \"count\", id_probe, timestmp from result_node join (result join probe on result.\"ID_PROBE\"=probe.\"ID_PROBE\")on( result.\"ID_PROBE\"=result_node.id_probe and cycle=cycle_num and id_session=\"ID_SESSION\")  where rtt=0 and timestmp between '";
    qwery+=ui->dateevnt1->dateTime().toString("dd.MM.yyyy hh:mm:ss") + "' and '" + ui->dateevent2->dateTime().toString("dd.MM.yyyy hh:mm:ss")+"'";
    //    QMessageBox::information(0,"",qwery,QMessageBox::StandardButton(),QMessageBox::StandardButton());
    if(ui->comboevagent->currentText()!="all")
        qwery+=" and name = '"+ui->comboevagent->currentText()+"' ";
    if(ui->comboevprobe->currentText()!="all")
        qwery+=" and id_probe = " + ui->comboevprobe->currentText();
    if(ui->lineevcyc2->text()!="0")
        qwery+=" and cycle between "+ui->lineevcyc1->text()+" and " + ui->lineevcyc2->text();
    qwery+=" group by id_probe, cycle, timestmp, \"name\" order by timestmp";
    db.open();
    qwmodel.setQuery(qwery,db);
    ui->tableView->setModel(&qwmodel);
    db.close();
            // расчет статистики
    if (ui->lineEditeventinterval->text()!="0")
    {
        int starttime=ui->dateevnt1->dateTime().toTime_t();
        int step = ui->lineEditeventinterval->text().toInt(NULL);
        int counts=abs(ui->dateevent2->dateTime().toTime_t()-starttime)/step+1;
        int currentindex,currentval;
        int total=0;
          int tmin=1000000,tmax=0;
        float Expected=0, Deviated=0;
        QVector<int> totals(counts);
        totals.fill(0);
        int rows=qwmodel.rowCount();
         std::ostringstream s("");
         s<<rows;
        for (int i=0;i<rows;i++)
        {
            currentindex=(qwmodel.record(i).value("timestmp").toDateTime().toTime_t()-starttime)/step;
            currentval=qwmodel.record(i).value("count").toInt(NULL);
            totals[currentindex]+=currentval;
        }
        for (int j=0;j<counts;j++)
        {
            total+=totals[j]/counts;
            Expected+=(double)totals[j]/(double)counts;
            Deviated+=totals[j]*(totals[j]/counts);
            if(tmin>totals[j])
                tmin=totals[j];
            if(tmax<totals[j])
                tmax=totals[j];
        }
        Deviated-=Expected*Expected;
        Deviated=sqrt(Deviated);
        std::ostringstream strsrm("");
        strsrm<<"INFO: "<<"\n total: "<<total<<" \n Expexted: "<<Expected<<" \n Deviation: "<<Deviated;
        ui->label->setText(QString(strsrm.str().c_str()));
           /*РИСУЕМ ВСЕ*/
        if(ui->checkBox->isChecked())
        {
         int  totcnt=(tmax-tmin)/10+1;
        QwtArray<QwtDoubleInterval> intervals(totcnt);
        QwtArray<double> values(totcnt);
        values.fill(0);
            for(int j=0;j<totcnt;j++)
             {
                intervals[j] = QwtDoubleInterval(tmin+10*j+1, tmin+10*j + 10);
                for(int k=0;k<counts;k++)
                    if((totals[k]-tmin)/10==j+tmin)
                        values[j]+=1;
            }
            potolok=0;
            for(int j=0;j<values.size();j++)
                if(potolok<values[j])
                   potolok=values[j];
            mainPlot->clear();
            mainPlot->resize(ui->graphicsView->width()-130,ui->graphicsView->height());
            HistogramItem * histogram= new HistogramItem("hist1");
            histogram->setColor(Qt::darkRed);
            mainPlot->setTitle("lost requests frequency");
            histogram->setData(QwtIntervalData(intervals, values));
            histogram->attach(mainPlot);
            mainPlot->setAxisTitle(QwtPlot::xBottom, "lost in time count");
            mainPlot->setAxisTitle(QwtPlot::yLeft, "frequency");
            mainPlot->setAxisScale(QwtPlot::xBottom,intervals[0].minValue()-1,intervals[intervals.count()-1].maxValue()+1);
           mainPlot->setAxisScale(QwtPlot::yLeft,0,potolok+1);
            mainPlot->replot();
            delete histogram;
        }
        else
        {
           // рисуем временно-зависимую структуру

            QVector<double> Counts(counts);
            Counts.fill(0);
            int total=qwmodel.rowCount();
            for (int i=0;i<total;i++)
            {
                currentindex=(qwmodel.record(i).value("timestmp").toDateTime().toTime_t()-starttime)/step;
                Counts[currentindex]++;

            }
            potolok=0;
            for(int j=0;j<Counts.size();j++)
                if(potolok<Counts[j])
                   potolok=Counts[j];
            QVector<QwtDoubleInterval> dTime(counts); //массив по X
            for(int j=0;j<counts;j++)
            {                             ///считаем массив иксов
                dTime[j]=QwtDoubleInterval(j*step,j*step+1);
            }
            std::ostringstream strsrm("");
            strsrm<<"INFO: "<<"\n total: "<<total<<"\n averages: \n";
            for(int j=0;j<counts;j++)
                strsrm<<" \n "<<Counts[j];
            ui->label->setText(QString(strsrm.str().c_str()));
            mainPlot->clear();
            PointsItem * pointscount = new PointsItem("counts");
            pointscount->setData(QwtIntervalData(dTime,Counts));
            pointscount->setColor(Qt::darkRed);
            pointscount->attach(mainPlot);

                       // finally, refresh the plot
            mainPlot->setTitle("distribution lost packets in time");
            mainPlot->setAxisTitle(QwtPlot::yLeft, "count");
            mainPlot->setAxisTitle(QwtPlot::xBottom, "timeline");
            mainPlot->setAxisScale(QwtPlot::xBottom,dTime[0].minValue(),dTime[dTime.count()-1].maxValue()+1);
            mainPlot->setAxisScale(QwtPlot::yLeft,0,potolok+1);
            mainPlot->replot();
            delete pointscount;

        }
    }
    else
    {
        //считать для всех скопом.
        int total=0;
        for (int i=0;i<qwmodel.rowCount();i++)
        {
        total+=qwmodel.record(i).value("count").toInt(NULL);
        }
        std::ostringstream strsrm("");
        strsrm<<"INFO: "<<"\n total: "<<total<<" \n";
        ui->label->setText(QString(strsrm.str().c_str()));
        mainPlot->clear();
        mainPlot->replot();
    }



}

void testwindow::on_actionConnect_triggered()
{
    bool ok=false;
    QString dbname=QInputDialog::getText(0,"input DB name","input DB name",QLineEdit::Normal,"",&ok);
    if(ok)
    {
        db.setDatabaseName(dbname);
        db.setHostName("localhost");
        db.setUserName("iero");
        db.setPassword("birmingem");
        db.open();
    QString sqlstr="select name from agent";
    qwsecmodel.setQuery(sqlstr,db);
    for (int i=0;i<qwsecmodel.rowCount();i++)
    {
        ui->comboevagent->insertItem(i,qwsecmodel.record(i).value("name").toString());
        ui->comborttagent->insertItem(i,qwsecmodel.record(i).value("name").toString());
    }
    ui->comboevagent->insertItem(0,"all",QVariant("all"));
    ui->comboevagent->setCurrentIndex(0);
    ui->comborttagent->insertItem(0,"all",QVariant("all"));
    ui->comborttagent->setCurrentIndex(0);
    /// заполняем зонды
    sqlstr="select \"ID_PROBE\" from probe ";
    qwsecmodel.setQuery(sqlstr,db);
    for (int i=0;i<qwsecmodel.rowCount();i++)
    {
        ui->comboevprobe->insertItem(i,qwsecmodel.record(i).value("ID_PROBE").toString());
        ui->comborttprobe->insertItem(i,qwsecmodel.record(i).value("ID_PROBE").toString());
    }
    ui->comboevprobe->insertItem(0,"all",QVariant("-1"));
    ui->comboevprobe->setCurrentIndex(0);
    ui->comborttprobe->insertItem(0,"all",QVariant("-1"));
    ui->comborttprobe->setCurrentIndex(0);
    ///запиливаем типы ошибок
    sqlstr="select * from event_type order by is_err, code";
    qwsecmodel.setQuery(sqlstr,db);
    for (int i=0;i<qwsecmodel.rowCount();i++)
    {
        ui->comboevtype->insertItem(i,qwsecmodel.record(i).value("name").toString(),QVariant(qwsecmodel.record(i).value("id_type").toString()));
    }
    ui->comboevtype->insertItem(0,"all",QVariant("-1"));
    ui->comboevtype->setCurrentIndex(0);
    sqlstr="select distinct adress from event order by adress";
    qwsecmodel.setQuery(sqlstr,db);
    for (int i=0;i<qwsecmodel.rowCount();i++)
    {
        ui->comboevadr->insertItem(i,qwsecmodel.record(i).value("adress").toString(),QVariant(qwmodel.record(i).value("adress").toString()));
    }
    ui->comboevadr->insertItem(0,"all",QVariant("-1"));
    ui->comboevadr->setCurrentIndex(0);
    ///выставляем время
    sqlstr="select max(timestmp) from result";
    qwsecmodel.setQuery(sqlstr,db);
    ui->datertt2->setDateTime(qwsecmodel.record(0).value(0).toDateTime());
    ui->dateevent2->setDateTime(qwsecmodel.record(0).value(0).toDateTime());
    ///минимум из БД
     sqlstr="select min(timestmp) from result";
    qwsecmodel.setQuery(sqlstr, db);
    ui->dateevnt1->setDateTime(qwsecmodel.record(0).value(0).toDateTime());
    ui->datertt1->setDateTime(qwsecmodel.record(0).value(0).toDateTime());
    db.close();
    /*вроде завели*/
    }
}

void testwindow::on_rttcycleButton_clicked()
{
        item_type = Results;
    if(ui->comborttprobe->currentText()!="all")
    {
            QString qwerry;
            qwerry="select min(cycle) as min, max(cycle) as max from result where \"ID_PROBE\"="+ui->comborttprobe->currentText();
            if(ui->linerttcyc2->text()!="0")
                qwerry+=" and cycle between "+ui->linerttcyc1->text()+" and " + ui->linerttcyc2->text();
            //QMessageBox::information(0,"",qwerry,QMessageBox::StandardButton(),QMessageBox::StandardButton());
            db.open();
            qwsecmodel.setQuery(qwerry,db);
            int maxnumber = qwsecmodel.record(0).value("max").toInt(NULL);
            int minnumber = qwsecmodel.record(0).value("min").toInt(NULL);
            std::ostringstream qwery("");
            qwery<<"select cycle_num, min(rtt) as min, avg(rtt) as aver, max(rtt) as max from result_node join result on( result.\"ID_PROBE\"=result_node.id_probe and cycle=cycle_num and id_session=\"ID_SESSION\")  where rtt>0 and timestmp between '";
            qwery<<ui->datertt1->dateTime().toString("dd.MM.yyyy hh:mm:ss").toStdString() << "' and '" << ui->datertt2->dateTime().toString("dd.MM.yyyy hh:mm:ss").toStdString()<<"'";
            qwery<<" and id_probe = " << ui->comborttprobe->currentText().toStdString();
            if(ui->linerttcyc2->text()!="0")
                qwery<<" and cycle_num between "<< minnumber<< " and "<<maxnumber;
            qwery<<" group by cycle_num order by cycle_num";
            qwmodel.setQuery(qwery.str().c_str(),db);
            ui->tableView->setModel(&qwmodel);
            db.close();
        ///расчет статистики по величинам
            int counts=qwmodel.rowCount();
            QVector<double> Averages(counts);
            QVector<double> Mins(counts);
            QVector<double> Maxs(counts);
            QVector<int> Cycles(counts);
            double maxE=0, maxD=0, avgE=0, avgD=0, minE=0,minD=0;
            potolok=0;
            for (int i=0;i<counts;i++)
            {
                Averages[i]=qwmodel.record(i).value("aver").toDouble(NULL)/1000;
                Mins[i]=qwmodel.record(i).value("min").toDouble(NULL)/1000;
                Maxs[i]=qwmodel.record(i).value("max").toDouble(NULL)/1000;
                if(potolok<Maxs[i])
                    potolok=Maxs[i];
                Cycles[i]=qwmodel.record(i).value("cycle_num").toInt(NULL);
            }
            QVector<QwtDoubleInterval> dTime(counts); //массив по X
            for(int j=0;j<counts;j++)
            {                             ///считаем массив иксов
                dTime[j]=QwtDoubleInterval(Cycles[j],Cycles[j]);
            }
            for(int j=0;j<counts;j++)
            {
                maxE+=Maxs[j]/(double)counts;
                maxD+=Maxs[j]*(Maxs[j]/(double)counts);
                avgE+=Averages[j]/(double)counts;
                avgD+=Averages[j]*(Averages[j]/(double)counts);
                minE+=Mins[j]/(double)counts;
                minD+=Mins[j]*(Mins[j]/(double)counts);
            }
            maxD=sqrt(maxD-maxE*maxE);
            avgD=sqrt(avgD-avgE*avgE);
            minD=sqrt(minD-minE*minE);
            std::ostringstream strsrm("");
            strsrm<<"INFO: "<<"\n total: "<<counts;
            strsrm<<"\n Maximun:"<<maxE<<" dev "<<maxD;
            strsrm<<"\n Average:"<<avgE<<" dev "<<avgD;
            strsrm<<"\n Minimum:"<<minE<<" dev "<<minD;
            ui->label->setText(QString(strsrm.str().c_str()));
            mainPlot->clear();
            mainPlot->resize(ui->graphicsView->width()-130,ui->graphicsView->height());
            PointsItem * pointsmax = new PointsItem("rtt intervals");
            pointsmax->setData(QwtIntervalData(dTime,Maxs));
            pointsmax->setColor(Qt::red);
            pointsmax->attach(mainPlot);
            PointsItem * pointsmin = new PointsItem("rtt intervals");
            pointsmin->setData(QwtIntervalData(dTime,Mins));
            pointsmin->setColor(Qt::red);
            pointsmin->attach(mainPlot);
            PointsItem * pointsavg = new PointsItem("rtt intervals");
            pointsavg->setData(QwtIntervalData(dTime,Averages));
            pointsavg->setColor(Qt::green);
            pointsavg->attach(mainPlot);
                       // finally, refresh the plot
            mainPlot->setTitle("distribution rtt in cycles");
            mainPlot->setAxisTitle(QwtPlot::yLeft, "rtt, milliseconds");
            mainPlot->setAxisTitle(QwtPlot::xBottom, "cycle numbers");
            mainPlot->setAxisScale(QwtPlot::xBottom,dTime[0].minValue(),dTime[dTime.count()-1].maxValue()+1);
            mainPlot->setAxisScale(QwtPlot::yLeft,0,potolok+1);
            mainPlot->replot();
            delete pointsmax;
            delete pointsmin;
            delete pointsavg;

    }
    else
    {
        QMessageBox::warning(0,"wrong parameter","probe not specified.\n request not runned.",QMessageBox::StandardButton(),QMessageBox::StandardButton());
        return;
    }
}
