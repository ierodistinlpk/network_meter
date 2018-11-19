#include <QtGui>
#include <QDialog>
#include "ui_eventdialog.h"
//using namespace Ui;
Ui_eventDialog::Ui_eventDialog(QWidget *parent)
    : QDialog(parent,Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    setupUi(this);
QObject::connect( eventbuttonBox, SIGNAL(clicked()), this, SLOT(on_buttonBox_accepted));
}

//void Ui_eventDialog::on_acceptBox_clicked()
//{}
void Ui_eventDialog::on_buttonBox_accepted()
{
    this->close();
}

void Ui_eventDialog::setupUi(QDialog *eventDialog)
    {
    if (eventDialog->objectName().isEmpty())
        eventDialog->setObjectName(QString::fromUtf8("eventDialog"));
    eventDialog->resize(351, 435);
    gridLayout_4 = new QGridLayout(eventDialog);
    gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
    frame_3 = new QFrame(eventDialog);
    frame_3->setObjectName(QString::fromUtf8("frame_3"));
    frame_3->setFrameShape(QFrame::StyledPanel);
    frame_3->setFrameShadow(QFrame::Raised);
    gridLayout_3 = new QGridLayout(frame_3);
    gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
    linetarget = new QLineEdit(frame_3);
    linetarget->setObjectName(QString::fromUtf8("linetarget"));

    gridLayout_3->addWidget(linetarget, 0, 1, 1, 1);

    checkBoxtarget = new QCheckBox(frame_3);
    checkBoxtarget->setObjectName(QString::fromUtf8("checkBoxtarget"));

    gridLayout_3->addWidget(checkBoxtarget, 0, 0, 1, 1);


    gridLayout_4->addWidget(frame_3, 0, 0, 1, 1);

    frame_4 = new QFrame(eventDialog);
    frame_4->setObjectName(QString::fromUtf8("frame_4"));
    frame_4->setFrameShape(QFrame::StyledPanel);
    frame_4->setFrameShadow(QFrame::Raised);
    horizontalLayout = new QHBoxLayout(frame_4);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    checkBoxadress = new QCheckBox(frame_4);
    checkBoxadress->setObjectName(QString::fromUtf8("checkBoxadress"));

    horizontalLayout->addWidget(checkBoxadress);

    lineadress = new QLineEdit(frame_4);
    lineadress->setObjectName(QString::fromUtf8("lineadress"));

    horizontalLayout->addWidget(lineadress);


    gridLayout_4->addWidget(frame_4, 1, 0, 1, 1);

    frame_6 = new QFrame(eventDialog);
    frame_6->setObjectName(QString::fromUtf8("frame_6"));
    frame_6->setFrameShape(QFrame::StyledPanel);
    frame_6->setFrameShadow(QFrame::Raised);
    gridLayout_6 = new QGridLayout(frame_6);
    gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
    lineagent = new QLineEdit(frame_6);
    lineagent->setObjectName(QString::fromUtf8("lineagent"));

    gridLayout_6->addWidget(lineagent, 0, 1, 1, 1);

    checkBoxagent = new QCheckBox(frame_6);
    checkBoxagent->setObjectName(QString::fromUtf8("checkBoxagent"));

    gridLayout_6->addWidget(checkBoxagent, 0, 0, 1, 1);


    gridLayout_4->addWidget(frame_6, 2, 0, 1, 1);

    frame_8 = new QFrame(eventDialog);
    frame_8->setObjectName(QString::fromUtf8("frame_8"));
    frame_8->setFrameShape(QFrame::StyledPanel);
    frame_8->setFrameShadow(QFrame::Raised);
    gridLayout_8 = new QGridLayout(frame_8);
    gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
    lineprobe = new QLineEdit(frame_8);
    lineprobe->setObjectName(QString::fromUtf8("lineprobe"));

    gridLayout_8->addWidget(lineprobe, 0, 1, 1, 1);

    checkBoxprobe = new QCheckBox(frame_8);
    checkBoxprobe->setObjectName(QString::fromUtf8("checkBoxprobe"));

    gridLayout_8->addWidget(checkBoxprobe, 0, 0, 1, 1);


    gridLayout_4->addWidget(frame_8, 3, 0, 1, 1);

    frame_5 = new QFrame(eventDialog);
    frame_5->setObjectName(QString::fromUtf8("frame_5"));
    frame_5->setFrameShape(QFrame::StyledPanel);
    frame_5->setFrameShadow(QFrame::Raised);
    gridLayout_5 = new QGridLayout(frame_5);
    gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
    linesession = new QLineEdit(frame_5);
    linesession->setObjectName(QString::fromUtf8("linesession"));

    gridLayout_5->addWidget(linesession, 0, 1, 1, 1);

    checkBoxsession = new QCheckBox(frame_5);
    checkBoxsession->setObjectName(QString::fromUtf8("checkBoxsession"));

    gridLayout_5->addWidget(checkBoxsession, 0, 0, 1, 1);


    gridLayout_4->addWidget(frame_5, 5, 0, 1, 1);

    frame_2 = new QFrame(eventDialog);
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

    checkBoxtime = new QCheckBox(frame_2);
    checkBoxtime->setObjectName(QString::fromUtf8("checkBoxtime"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(checkBoxtime->sizePolicy().hasHeightForWidth());
    checkBoxtime->setSizePolicy(sizePolicy1);

    gridLayout->addWidget(checkBoxtime, 1, 0, 1, 1);


    gridLayout_4->addWidget(frame_2, 6, 0, 1, 2);

    eventbuttonBox = new QDialogButtonBox(eventDialog);
    eventbuttonBox->setObjectName(QString::fromUtf8("eventbuttonBox"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(eventbuttonBox->sizePolicy().hasHeightForWidth());
    eventbuttonBox->setSizePolicy(sizePolicy2);
    eventbuttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Yes);
    eventbuttonBox->setCenterButtons(false);

    gridLayout_4->addWidget(eventbuttonBox, 7, 0, 1, 1);

    frame = new QFrame(eventDialog);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    gridLayout_2 = new QGridLayout(frame);
    gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
    checkBoxcycle = new QCheckBox(frame);
    checkBoxcycle->setObjectName(QString::fromUtf8("checkBoxcycle"));
    sizePolicy.setHeightForWidth(checkBoxcycle->sizePolicy().hasHeightForWidth());
    checkBoxcycle->setSizePolicy(sizePolicy);

    gridLayout_2->addWidget(checkBoxcycle, 0, 0, 1, 1);

    linecycle1 = new QLineEdit(frame);
    linecycle1->setObjectName(QString::fromUtf8("linecycle1"));
    sizePolicy.setHeightForWidth(linecycle1->sizePolicy().hasHeightForWidth());
    linecycle1->setSizePolicy(sizePolicy);

    gridLayout_2->addWidget(linecycle1, 0, 1, 1, 1);

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

    gridLayout_2->addWidget(label, 0, 2, 1, 1);

    linecycle2 = new QLineEdit(frame);
    linecycle2->setObjectName(QString::fromUtf8("linecycle2"));
    sizePolicy1.setHeightForWidth(linecycle2->sizePolicy().hasHeightForWidth());
    linecycle2->setSizePolicy(sizePolicy1);

    gridLayout_2->addWidget(linecycle2, 0, 3, 1, 1);


    gridLayout_4->addWidget(frame, 4, 0, 1, 1);


    retranslateUi(eventDialog);

    QMetaObject::connectSlotsByName(eventDialog);
    } // setupUi
