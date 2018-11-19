#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QtGui/QMainWindow>
 #include <QInputDialog>
#include <QtSql>
#include "constants.h"
#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_curve.h>
namespace Ui
{
    class testwindow;
}

class testwindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase db;
    QSqlQueryModel qwmodel;
    QSqlQueryModel qwsecmodel;
    itemtype item_type;
    graphtype graph_type;
    testwindow(QWidget *parent = 0);
    ~testwindow();
     QwtPlot * mainPlot;
    double potolok;
private:
    Ui::testwindow *ui;

private slots:
    void on_rttcycleButton_clicked();
    void on_actionConnect_triggered();
    void on_losteventButton_clicked();
    void on_eventButton_clicked();
    void on_rttavgButton_clicked();
    void on_rttnumButton_clicked();
    void on_rttintervalButton_clicked();
    void on_probecleanButton_clicked();
    void on_comborttagent_activated(QString );
    void on_rttcleanButton_clicked();
    void on_comboevagent_activated(QString );
    void on_eventcleanButton_clicked();
    void on_helpButton_clicked();
    void on_aboutButton_clicked();
    void on_probeButton_clicked();
    void on_targetButton_clicked();
    void on_eventypetButton_clicked();
    void on_agentButton_clicked();

};

#endif // TESTWINDOW_H
