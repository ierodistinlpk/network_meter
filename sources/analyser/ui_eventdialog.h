/********************************************************************************
** Form generated from reading ui file 'eventdialog.ui'
**
** Created: Fri Jun 12 00:33:42 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_EVENTDIALOG_H
#define UI_EVENTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_eventDialog:public QDialog
{
    Q_OBJECT
public:
    Ui_eventDialog(QWidget *parent=0);
    QGridLayout *gridLayout_4;
    QFrame *frame_3;
    QGridLayout *gridLayout_3;
    QLineEdit *linetarget;
    QCheckBox *checkBoxtarget;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxadress;
    QLineEdit *lineadress;
    QFrame *frame_6;
    QGridLayout *gridLayout_6;
    QLineEdit *lineagent;
    QCheckBox *checkBoxagent;
    QFrame *frame_8;
    QGridLayout *gridLayout_8;
    QLineEdit *lineprobe;
    QCheckBox *checkBoxprobe;
    QFrame *frame_5;
    QGridLayout *gridLayout_5;
    QLineEdit *linesession;
    QCheckBox *checkBoxsession;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QDateTimeEdit *dateTimeEdit;
    QDateTimeEdit *dateTimeEdit_2;
    QCheckBox *checkBoxtime;
    QDialogButtonBox *eventbuttonBox;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QCheckBox *checkBoxcycle;
    QLineEdit *linecycle1;
    QLabel *label;
    QLineEdit *linecycle2;

    void setupUi(QDialog *eventDialog);


    void retranslateUi(QDialog *eventDialog)
    {
    eventDialog->setWindowTitle(QApplication::translate("eventDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    checkBoxtarget->setText(QApplication::translate("eventDialog", "target", 0, QApplication::UnicodeUTF8));
    checkBoxadress->setText(QApplication::translate("eventDialog", "adress", 0, QApplication::UnicodeUTF8));
    checkBoxagent->setText(QApplication::translate("eventDialog", "agent", 0, QApplication::UnicodeUTF8));
    checkBoxprobe->setText(QApplication::translate("eventDialog", "probe", 0, QApplication::UnicodeUTF8));
    checkBoxsession->setText(QApplication::translate("eventDialog", "session", 0, QApplication::UnicodeUTF8));
    checkBoxtime->setText(QApplication::translate("eventDialog", "time", 0, QApplication::UnicodeUTF8));
    checkBoxcycle->setText(QApplication::translate("eventDialog", "cycle", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("eventDialog", "To", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(eventDialog);
    } // retranslateUi
public slots:
    void on_buttonBox_accepted();
};

/*namespace Ui {
    class eventDialog: public Ui_eventDialog {};
} // namespace Ui*/

QT_END_NAMESPACE

#endif // UI_EVENTDIALOG_H
