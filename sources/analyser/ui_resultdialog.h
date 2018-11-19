/********************************************************************************
** Form generated from reading ui file 'resultdialog.ui'
**
** Created: Fri Jun 12 00:16:33 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_RESULTDIALOG_H
#define UI_RESULTDIALOG_H

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

class Ui_Dialog
{
public:
    QGridLayout *gridLayout_7;
    QFrame *frame_3;
    QGridLayout *gridLayout_3;
    QLineEdit *lineEdit_3;
    QCheckBox *checkBox_4;
    QFrame *frame_4;
    QGridLayout *gridLayout_4;
    QLineEdit *lineEdit_4;
    QCheckBox *checkBox_6;
    QFrame *frame_6;
    QGridLayout *gridLayout_6;
    QLineEdit *lineEdit_8;
    QCheckBox *checkBox_8;
    QFrame *frame_5;
    QGridLayout *gridLayout_5;
    QLineEdit *lineEdit_7;
    QCheckBox *checkBox_7;
    QDialogButtonBox *buttonBox;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QDateTimeEdit *dateTimeEdit;
    QDateTimeEdit *dateTimeEdit_2;
    QCheckBox *checkBox_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox_5;
    QLineEdit *lineEdit_5;
    QLabel *label;
    QLineEdit *lineEdit_6;

    void setupUi(QDialog *Dialog)
    {
    if (Dialog->objectName().isEmpty())
        Dialog->setObjectName(QString::fromUtf8("Dialog"));
    Dialog->resize(345, 380);
    gridLayout_7 = new QGridLayout(Dialog);
    gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
    frame_3 = new QFrame(Dialog);
    frame_3->setObjectName(QString::fromUtf8("frame_3"));
    frame_3->setFrameShape(QFrame::StyledPanel);
    frame_3->setFrameShadow(QFrame::Raised);
    gridLayout_3 = new QGridLayout(frame_3);
    gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
    lineEdit_3 = new QLineEdit(frame_3);
    lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

    gridLayout_3->addWidget(lineEdit_3, 0, 1, 1, 1);

    checkBox_4 = new QCheckBox(frame_3);
    checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

    gridLayout_3->addWidget(checkBox_4, 0, 0, 1, 1);


    gridLayout_7->addWidget(frame_3, 0, 0, 1, 1);

    frame_4 = new QFrame(Dialog);
    frame_4->setObjectName(QString::fromUtf8("frame_4"));
    frame_4->setFrameShape(QFrame::StyledPanel);
    frame_4->setFrameShadow(QFrame::Raised);
    gridLayout_4 = new QGridLayout(frame_4);
    gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
    lineEdit_4 = new QLineEdit(frame_4);
    lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

    gridLayout_4->addWidget(lineEdit_4, 0, 1, 1, 1);

    checkBox_6 = new QCheckBox(frame_4);
    checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));

    gridLayout_4->addWidget(checkBox_6, 0, 0, 1, 1);


    gridLayout_7->addWidget(frame_4, 1, 0, 1, 1);

    frame_6 = new QFrame(Dialog);
    frame_6->setObjectName(QString::fromUtf8("frame_6"));
    frame_6->setFrameShape(QFrame::StyledPanel);
    frame_6->setFrameShadow(QFrame::Raised);
    gridLayout_6 = new QGridLayout(frame_6);
    gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
    lineEdit_8 = new QLineEdit(frame_6);
    lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));

    gridLayout_6->addWidget(lineEdit_8, 0, 1, 1, 1);

    checkBox_8 = new QCheckBox(frame_6);
    checkBox_8->setObjectName(QString::fromUtf8("checkBox_8"));

    gridLayout_6->addWidget(checkBox_8, 0, 0, 1, 1);


    gridLayout_7->addWidget(frame_6, 2, 0, 1, 1);

    frame_5 = new QFrame(Dialog);
    frame_5->setObjectName(QString::fromUtf8("frame_5"));
    frame_5->setFrameShape(QFrame::StyledPanel);
    frame_5->setFrameShadow(QFrame::Raised);
    gridLayout_5 = new QGridLayout(frame_5);
    gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
    lineEdit_7 = new QLineEdit(frame_5);
    lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));

    gridLayout_5->addWidget(lineEdit_7, 0, 1, 1, 1);

    checkBox_7 = new QCheckBox(frame_5);
    checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));

    gridLayout_5->addWidget(checkBox_7, 0, 0, 1, 1);


    gridLayout_7->addWidget(frame_5, 4, 0, 1, 1);

    buttonBox = new QDialogButtonBox(Dialog);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Yes);

    gridLayout_7->addWidget(buttonBox, 7, 0, 1, 1);

    frame_2 = new QFrame(Dialog);
    frame_2->setObjectName(QString::fromUtf8("frame_2"));
    frame_2->setFrameShape(QFrame::StyledPanel);
    frame_2->setFrameShadow(QFrame::Raised);
    gridLayout = new QGridLayout(frame_2);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    dateTimeEdit = new QDateTimeEdit(frame_2);
    dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(dateTimeEdit->sizePolicy().hasHeightForWidth());
    dateTimeEdit->setSizePolicy(sizePolicy);

    gridLayout->addWidget(dateTimeEdit, 1, 1, 1, 1);

    dateTimeEdit_2 = new QDateTimeEdit(frame_2);
    dateTimeEdit_2->setObjectName(QString::fromUtf8("dateTimeEdit_2"));
    sizePolicy.setHeightForWidth(dateTimeEdit_2->sizePolicy().hasHeightForWidth());
    dateTimeEdit_2->setSizePolicy(sizePolicy);

    gridLayout->addWidget(dateTimeEdit_2, 1, 2, 1, 1);

    checkBox_2 = new QCheckBox(frame_2);
    checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(checkBox_2->sizePolicy().hasHeightForWidth());
    checkBox_2->setSizePolicy(sizePolicy1);

    gridLayout->addWidget(checkBox_2, 1, 0, 1, 1);


    gridLayout_7->addWidget(frame_2, 6, 0, 1, 1);

    frame = new QFrame(Dialog);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    horizontalLayout = new QHBoxLayout(frame);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    checkBox_5 = new QCheckBox(frame);
    checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(checkBox_5->sizePolicy().hasHeightForWidth());
    checkBox_5->setSizePolicy(sizePolicy2);

    horizontalLayout->addWidget(checkBox_5);

    lineEdit_5 = new QLineEdit(frame);
    lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
    sizePolicy.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
    lineEdit_5->setSizePolicy(sizePolicy);

    horizontalLayout->addWidget(lineEdit_5);

    label = new QLabel(frame);
    label->setObjectName(QString::fromUtf8("label"));
    QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
    label->setSizePolicy(sizePolicy3);
    QFont font;
    font.setBold(true);
    font.setWeight(75);
    label->setFont(font);

    horizontalLayout->addWidget(label);

    lineEdit_6 = new QLineEdit(frame);
    lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
    sizePolicy1.setHeightForWidth(lineEdit_6->sizePolicy().hasHeightForWidth());
    lineEdit_6->setSizePolicy(sizePolicy1);

    horizontalLayout->addWidget(lineEdit_6);


    gridLayout_7->addWidget(frame, 3, 0, 1, 1);


    retranslateUi(Dialog);

    QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
    Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
    checkBox_4->setText(QApplication::translate("Dialog", "target", 0, QApplication::UnicodeUTF8));
    checkBox_6->setText(QApplication::translate("Dialog", "agent", 0, QApplication::UnicodeUTF8));
    checkBox_8->setText(QApplication::translate("Dialog", "probe", 0, QApplication::UnicodeUTF8));
    checkBox_7->setText(QApplication::translate("Dialog", "session", 0, QApplication::UnicodeUTF8));
    checkBox_2->setText(QApplication::translate("Dialog", "time", 0, QApplication::UnicodeUTF8));
    checkBox_5->setText(QApplication::translate("Dialog", "cycle", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("Dialog", "To", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Dialog);
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTDIALOG_H
