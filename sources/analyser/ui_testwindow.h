/********************************************************************************
** Form generated from reading ui file 'testwindow.ui'
**
** Created: Thu Jun 25 00:01:49 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TESTWINDOW_H
#define UI_TESTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testwindow
{
public:
    QAction *actionConnect;
    QAction *actionExit;
    QAction *actionManual;
    QAction *actionAbout;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_4;
    QPushButton *exitButton;
    QLabel *label;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QTableView *tableView;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QGraphicsView *graphicsView;
    QPushButton *helpButton;
    QPushButton *aboutButton;
    QTabWidget *tabWidget_ctl;
    QWidget *lists;
    QVBoxLayout *verticalLayout_2;
    QPushButton *agentButton;
    QPushButton *targetButton;
    QPushButton *eventypetButton;
    QWidget *probes;
    QGridLayout *gridLayout_5;
    QLabel *label_2;
    QLineEdit *lineEditpragent;
    QPushButton *probeButton;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QPushButton *probecleanButton;
    QWidget *events;
    QGridLayout *gridLayout_6;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_11;
    QComboBox *comboevtype;
    QComboBox *comboevagent;
    QComboBox *comboevprobe;
    QFrame *frame_2;
    QGridLayout *gridLayout_8;
    QLineEdit *lineevcyc1;
    QLineEdit *lineevcyc2;
    QLabel *label_9;
    QLabel *label_10;
    QFrame *frame;
    QGridLayout *gridLayout_7;
    QDateTimeEdit *dateevnt1;
    QDateTimeEdit *dateevent2;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEditeventinterval;
    QLabel *label_12;
    QLabel *label_8;
    QLabel *label_27;
    QComboBox *comboevadr;
    QGridLayout *gridLayout_10;
    QPushButton *losteventButton;
    QPushButton *eventcleanButton;
    QPushButton *eventButton;
    QCheckBox *checkBox;
    QWidget *results;
    QGridLayout *gridLayout_14;
    QLabel *label_16;
    QLabel *label_19;
    QFrame *frame_3;
    QGridLayout *gridLayout_12;
    QLabel *label_20;
    QLabel *label_21;
    QLineEdit *linerttcyc1;
    QLineEdit *linerttcyc2;
    QFrame *frame_5;
    QGridLayout *gridLayout_13;
    QLabel *label_24;
    QLineEdit *linerttstep;
    QLabel *label_22;
    QLabel *label_23;
    QDateTimeEdit *datertt1;
    QDateTimeEdit *datertt2;
    QLabel *label_25;
    QGridLayout *gridLayout_15;
    QPushButton *rttavgButton;
    QPushButton *rttintervalButton;
    QPushButton *rttcleanButton;
    QPushButton *rttcycleButton;
    QPushButton *rttnumButton;
    QSpacerItem *verticalSpacer_4;
    QComboBox *comborttagent;
    QComboBox *comborttprobe;
    QLabel *label_26;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuHgfhf;
    QMenu *menuHelp;

    void setupUi(QMainWindow *testwindow)
    {
    if (testwindow->objectName().isEmpty())
        testwindow->setObjectName(QString::fromUtf8("testwindow"));
    testwindow->resize(1024, 768);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(testwindow->sizePolicy().hasHeightForWidth());
    testwindow->setSizePolicy(sizePolicy);
    testwindow->setMinimumSize(QSize(1024, 768));
    QFont font;
    font.setPointSize(14);
    font.setBold(true);
    font.setWeight(75);
    testwindow->setFont(font);
    testwindow->setContextMenuPolicy(Qt::DefaultContextMenu);
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8("../../../../../../usr/share/icons/crystalsvg/16x16/apps/xload.png")), QIcon::Normal, QIcon::Off);
    testwindow->setWindowIcon(icon);
    actionConnect = new QAction(testwindow);
    actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
    actionExit = new QAction(testwindow);
    actionExit->setObjectName(QString::fromUtf8("actionExit"));
    actionManual = new QAction(testwindow);
    actionManual->setObjectName(QString::fromUtf8("actionManual"));
    actionAbout = new QAction(testwindow);
    actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
    centralWidget = new QWidget(testwindow);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    gridLayout = new QGridLayout(centralWidget);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout_4 = new QGridLayout();
    gridLayout_4->setSpacing(6);
    gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
    exitButton = new QPushButton(centralWidget);
    exitButton->setObjectName(QString::fromUtf8("exitButton"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(exitButton->sizePolicy().hasHeightForWidth());
    exitButton->setSizePolicy(sizePolicy1);
    exitButton->setCheckable(false);
    exitButton->setFlat(false);

    gridLayout_4->addWidget(exitButton, 3, 0, 1, 1);

    label = new QLabel(centralWidget);
    label->setObjectName(QString::fromUtf8("label"));
    sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
    label->setSizePolicy(sizePolicy);
    label->setMinimumSize(QSize(150, 0));
    label->setMaximumSize(QSize(16777215, 720));
    label->setBaseSize(QSize(200, 600));
    label->setFrameShape(QFrame::Panel);
    label->setFrameShadow(QFrame::Sunken);
    label->setTextFormat(Qt::PlainText);
    label->setScaledContents(true);
    label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
    label->setWordWrap(true);
    label->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

    gridLayout_4->addWidget(label, 2, 2, 1, 1);

    tabWidget = new QTabWidget(centralWidget);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
    tabWidget->setSizePolicy(sizePolicy2);
    tabWidget->setMinimumSize(QSize(420, 0));
    tabWidget->setBaseSize(QSize(460, 0));
    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    gridLayout_3 = new QGridLayout(tab);
    gridLayout_3->setSpacing(6);
    gridLayout_3->setMargin(11);
    gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
    tableView = new QTableView(tab);
    tableView->setObjectName(QString::fromUtf8("tableView"));
    QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
    tableView->setSizePolicy(sizePolicy3);
    tableView->setMinimumSize(QSize(0, 0));
    tableView->setBaseSize(QSize(0, 0));
    tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    tableView->setDragDropOverwriteMode(false);
    tableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    gridLayout_3->addWidget(tableView, 0, 0, 1, 1);

    tabWidget->addTab(tab, QString());
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    gridLayout_2 = new QGridLayout(tab_2);
    gridLayout_2->setSpacing(6);
    gridLayout_2->setMargin(11);
    gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
    graphicsView = new QGraphicsView(tab_2);
    graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
    QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Expanding);
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
    graphicsView->setSizePolicy(sizePolicy4);

    gridLayout_2->addWidget(graphicsView, 0, 0, 1, 1);

    tabWidget->addTab(tab_2, QString());

    gridLayout_4->addWidget(tabWidget, 2, 4, 1, 1);

    helpButton = new QPushButton(centralWidget);
    helpButton->setObjectName(QString::fromUtf8("helpButton"));

    gridLayout_4->addWidget(helpButton, 3, 4, 1, 1);

    aboutButton = new QPushButton(centralWidget);
    aboutButton->setObjectName(QString::fromUtf8("aboutButton"));

    gridLayout_4->addWidget(aboutButton, 3, 2, 1, 1);

    tabWidget_ctl = new QTabWidget(centralWidget);
    tabWidget_ctl->setObjectName(QString::fromUtf8("tabWidget_ctl"));
    sizePolicy4.setHeightForWidth(tabWidget_ctl->sizePolicy().hasHeightForWidth());
    tabWidget_ctl->setSizePolicy(sizePolicy4);
    tabWidget_ctl->setMinimumSize(QSize(310, 0));
    tabWidget_ctl->setMaximumSize(QSize(330, 16777215));
    tabWidget_ctl->setBaseSize(QSize(330, 0));
    lists = new QWidget();
    lists->setObjectName(QString::fromUtf8("lists"));
    verticalLayout_2 = new QVBoxLayout(lists);
    verticalLayout_2->setSpacing(6);
    verticalLayout_2->setMargin(11);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    agentButton = new QPushButton(lists);
    agentButton->setObjectName(QString::fromUtf8("agentButton"));
    agentButton->setFont(font);

    verticalLayout_2->addWidget(agentButton);

    targetButton = new QPushButton(lists);
    targetButton->setObjectName(QString::fromUtf8("targetButton"));
    targetButton->setFont(font);

    verticalLayout_2->addWidget(targetButton);

    eventypetButton = new QPushButton(lists);
    eventypetButton->setObjectName(QString::fromUtf8("eventypetButton"));
    eventypetButton->setFont(font);

    verticalLayout_2->addWidget(eventypetButton);

    tabWidget_ctl->addTab(lists, QString());
    probes = new QWidget();
    probes->setObjectName(QString::fromUtf8("probes"));
    gridLayout_5 = new QGridLayout(probes);
    gridLayout_5->setSpacing(6);
    gridLayout_5->setMargin(11);
    gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
    label_2 = new QLabel(probes);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setEnabled(true);
    QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Minimum);
    sizePolicy5.setHorizontalStretch(0);
    sizePolicy5.setVerticalStretch(0);
    sizePolicy5.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
    label_2->setSizePolicy(sizePolicy5);
    label_2->setFont(font);
    label_2->setFrameShape(QFrame::NoFrame);
    label_2->setFrameShadow(QFrame::Plain);
    label_2->setTextFormat(Qt::PlainText);
    label_2->setScaledContents(true);
    label_2->setAlignment(Qt::AlignCenter);
    label_2->setWordWrap(false);
    label_2->setIndent(0);
    label_2->setTextInteractionFlags(Qt::NoTextInteraction);

    gridLayout_5->addWidget(label_2, 0, 0, 1, 1);

    lineEditpragent = new QLineEdit(probes);
    lineEditpragent->setObjectName(QString::fromUtf8("lineEditpragent"));

    gridLayout_5->addWidget(lineEditpragent, 3, 0, 1, 1);

    probeButton = new QPushButton(probes);
    probeButton->setObjectName(QString::fromUtf8("probeButton"));
    probeButton->setFont(font);

    gridLayout_5->addWidget(probeButton, 5, 0, 1, 1);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout_5->addItem(verticalSpacer, 2, 0, 1, 1);

    verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout_5->addItem(verticalSpacer_2, 4, 0, 1, 1);

    verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout_5->addItem(verticalSpacer_3, 7, 0, 1, 1);

    probecleanButton = new QPushButton(probes);
    probecleanButton->setObjectName(QString::fromUtf8("probecleanButton"));

    gridLayout_5->addWidget(probecleanButton, 6, 0, 1, 1);

    tabWidget_ctl->addTab(probes, QString());
    events = new QWidget();
    events->setObjectName(QString::fromUtf8("events"));
    gridLayout_6 = new QGridLayout(events);
    gridLayout_6->setSpacing(6);
    gridLayout_6->setMargin(11);
    gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
    label_7 = new QLabel(events);
    label_7->setObjectName(QString::fromUtf8("label_7"));
    QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy6.setHorizontalStretch(0);
    sizePolicy6.setVerticalStretch(0);
    sizePolicy6.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
    label_7->setSizePolicy(sizePolicy6);

    gridLayout_6->addWidget(label_7, 5, 0, 1, 1);

    label_6 = new QLabel(events);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    sizePolicy6.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
    label_6->setSizePolicy(sizePolicy6);

    gridLayout_6->addWidget(label_6, 3, 0, 1, 1);

    label_11 = new QLabel(events);
    label_11->setObjectName(QString::fromUtf8("label_11"));
    sizePolicy6.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
    label_11->setSizePolicy(sizePolicy6);

    gridLayout_6->addWidget(label_11, 0, 0, 1, 1);

    comboevtype = new QComboBox(events);
    comboevtype->setObjectName(QString::fromUtf8("comboevtype"));
    sizePolicy1.setHeightForWidth(comboevtype->sizePolicy().hasHeightForWidth());
    comboevtype->setSizePolicy(sizePolicy1);

    gridLayout_6->addWidget(comboevtype, 1, 0, 1, 1);

    comboevagent = new QComboBox(events);
    comboevagent->setObjectName(QString::fromUtf8("comboevagent"));
    sizePolicy1.setHeightForWidth(comboevagent->sizePolicy().hasHeightForWidth());
    comboevagent->setSizePolicy(sizePolicy1);

    gridLayout_6->addWidget(comboevagent, 4, 0, 1, 1);

    comboevprobe = new QComboBox(events);
    comboevprobe->setObjectName(QString::fromUtf8("comboevprobe"));
    sizePolicy1.setHeightForWidth(comboevprobe->sizePolicy().hasHeightForWidth());
    comboevprobe->setSizePolicy(sizePolicy1);

    gridLayout_6->addWidget(comboevprobe, 6, 0, 1, 1);

    frame_2 = new QFrame(events);
    frame_2->setObjectName(QString::fromUtf8("frame_2"));
    sizePolicy6.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
    frame_2->setSizePolicy(sizePolicy6);
    frame_2->setFrameShape(QFrame::StyledPanel);
    frame_2->setFrameShadow(QFrame::Raised);
    gridLayout_8 = new QGridLayout(frame_2);
    gridLayout_8->setSpacing(6);
    gridLayout_8->setMargin(11);
    gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
    lineevcyc1 = new QLineEdit(frame_2);
    lineevcyc1->setObjectName(QString::fromUtf8("lineevcyc1"));

    gridLayout_8->addWidget(lineevcyc1, 1, 1, 1, 1);

    lineevcyc2 = new QLineEdit(frame_2);
    lineevcyc2->setObjectName(QString::fromUtf8("lineevcyc2"));

    gridLayout_8->addWidget(lineevcyc2, 1, 3, 1, 1);

    label_9 = new QLabel(frame_2);
    label_9->setObjectName(QString::fromUtf8("label_9"));

    gridLayout_8->addWidget(label_9, 1, 0, 1, 1);

    label_10 = new QLabel(frame_2);
    label_10->setObjectName(QString::fromUtf8("label_10"));

    gridLayout_8->addWidget(label_10, 1, 2, 1, 1);


    gridLayout_6->addWidget(frame_2, 10, 0, 1, 1);

    frame = new QFrame(events);
    frame->setObjectName(QString::fromUtf8("frame"));
    sizePolicy6.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
    frame->setSizePolicy(sizePolicy6);
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    gridLayout_7 = new QGridLayout(frame);
    gridLayout_7->setSpacing(6);
    gridLayout_7->setMargin(11);
    gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
    dateevnt1 = new QDateTimeEdit(frame);
    dateevnt1->setObjectName(QString::fromUtf8("dateevnt1"));
    QFont font1;
    font1.setPointSize(12);
    font1.setBold(false);
    font1.setWeight(50);
    dateevnt1->setFont(font1);

    gridLayout_7->addWidget(dateevnt1, 4, 0, 1, 1);

    dateevent2 = new QDateTimeEdit(frame);
    dateevent2->setObjectName(QString::fromUtf8("dateevent2"));
    dateevent2->setFont(font1);

    gridLayout_7->addWidget(dateevent2, 4, 1, 1, 1);

    label_4 = new QLabel(frame);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    gridLayout_7->addWidget(label_4, 2, 0, 1, 1);

    label_5 = new QLabel(frame);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    gridLayout_7->addWidget(label_5, 2, 1, 1, 1);

    lineEditeventinterval = new QLineEdit(frame);
    lineEditeventinterval->setObjectName(QString::fromUtf8("lineEditeventinterval"));

    gridLayout_7->addWidget(lineEditeventinterval, 0, 1, 1, 1);

    label_12 = new QLabel(frame);
    label_12->setObjectName(QString::fromUtf8("label_12"));

    gridLayout_7->addWidget(label_12, 0, 0, 1, 1);


    gridLayout_6->addWidget(frame, 11, 0, 1, 1);

    label_8 = new QLabel(events);
    label_8->setObjectName(QString::fromUtf8("label_8"));
    sizePolicy6.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
    label_8->setSizePolicy(sizePolicy6);

    gridLayout_6->addWidget(label_8, 9, 0, 1, 1);

    label_27 = new QLabel(events);
    label_27->setObjectName(QString::fromUtf8("label_27"));

    gridLayout_6->addWidget(label_27, 7, 0, 1, 1);

    comboevadr = new QComboBox(events);
    comboevadr->setObjectName(QString::fromUtf8("comboevadr"));

    gridLayout_6->addWidget(comboevadr, 8, 0, 1, 1);

    gridLayout_10 = new QGridLayout();
    gridLayout_10->setSpacing(6);
    gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
    losteventButton = new QPushButton(events);
    losteventButton->setObjectName(QString::fromUtf8("losteventButton"));
    losteventButton->setMinimumSize(QSize(40, 0));

    gridLayout_10->addWidget(losteventButton, 0, 0, 1, 1);

    eventcleanButton = new QPushButton(events);
    eventcleanButton->setObjectName(QString::fromUtf8("eventcleanButton"));
    sizePolicy1.setHeightForWidth(eventcleanButton->sizePolicy().hasHeightForWidth());
    eventcleanButton->setSizePolicy(sizePolicy1);
    eventcleanButton->setMinimumSize(QSize(40, 0));

    gridLayout_10->addWidget(eventcleanButton, 1, 0, 1, 1);

    eventButton = new QPushButton(events);
    eventButton->setObjectName(QString::fromUtf8("eventButton"));
    eventButton->setMinimumSize(QSize(40, 0));

    gridLayout_10->addWidget(eventButton, 0, 1, 1, 1);

    checkBox = new QCheckBox(events);
    checkBox->setObjectName(QString::fromUtf8("checkBox"));

    gridLayout_10->addWidget(checkBox, 1, 1, 1, 1);


    gridLayout_6->addLayout(gridLayout_10, 12, 0, 1, 1);

    tabWidget_ctl->addTab(events, QString());
    results = new QWidget();
    results->setObjectName(QString::fromUtf8("results"));
    gridLayout_14 = new QGridLayout(results);
    gridLayout_14->setSpacing(6);
    gridLayout_14->setMargin(11);
    gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
    label_16 = new QLabel(results);
    label_16->setObjectName(QString::fromUtf8("label_16"));

    gridLayout_14->addWidget(label_16, 0, 0, 1, 2);

    label_19 = new QLabel(results);
    label_19->setObjectName(QString::fromUtf8("label_19"));

    gridLayout_14->addWidget(label_19, 3, 0, 1, 2);

    frame_3 = new QFrame(results);
    frame_3->setObjectName(QString::fromUtf8("frame_3"));
    QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy7.setHorizontalStretch(0);
    sizePolicy7.setVerticalStretch(0);
    sizePolicy7.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
    frame_3->setSizePolicy(sizePolicy7);
    frame_3->setFrameShape(QFrame::StyledPanel);
    frame_3->setFrameShadow(QFrame::Raised);
    gridLayout_12 = new QGridLayout(frame_3);
    gridLayout_12->setSpacing(6);
    gridLayout_12->setMargin(11);
    gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
    label_20 = new QLabel(frame_3);
    label_20->setObjectName(QString::fromUtf8("label_20"));

    gridLayout_12->addWidget(label_20, 0, 0, 1, 1);

    label_21 = new QLabel(frame_3);
    label_21->setObjectName(QString::fromUtf8("label_21"));

    gridLayout_12->addWidget(label_21, 0, 1, 1, 1);

    linerttcyc1 = new QLineEdit(frame_3);
    linerttcyc1->setObjectName(QString::fromUtf8("linerttcyc1"));

    gridLayout_12->addWidget(linerttcyc1, 1, 0, 1, 1);

    linerttcyc2 = new QLineEdit(frame_3);
    linerttcyc2->setObjectName(QString::fromUtf8("linerttcyc2"));

    gridLayout_12->addWidget(linerttcyc2, 1, 1, 1, 1);


    gridLayout_14->addWidget(frame_3, 6, 0, 1, 1);

    frame_5 = new QFrame(results);
    frame_5->setObjectName(QString::fromUtf8("frame_5"));
    sizePolicy6.setHeightForWidth(frame_5->sizePolicy().hasHeightForWidth());
    frame_5->setSizePolicy(sizePolicy6);
    frame_5->setFrameShape(QFrame::StyledPanel);
    frame_5->setFrameShadow(QFrame::Raised);
    gridLayout_13 = new QGridLayout(frame_5);
    gridLayout_13->setSpacing(6);
    gridLayout_13->setMargin(11);
    gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
    label_24 = new QLabel(frame_5);
    label_24->setObjectName(QString::fromUtf8("label_24"));
    QSizePolicy sizePolicy8(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy8.setHorizontalStretch(0);
    sizePolicy8.setVerticalStretch(0);
    sizePolicy8.setHeightForWidth(label_24->sizePolicy().hasHeightForWidth());
    label_24->setSizePolicy(sizePolicy8);

    gridLayout_13->addWidget(label_24, 0, 0, 1, 1);

    linerttstep = new QLineEdit(frame_5);
    linerttstep->setObjectName(QString::fromUtf8("linerttstep"));
    QSizePolicy sizePolicy9(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy9.setHorizontalStretch(0);
    sizePolicy9.setVerticalStretch(0);
    sizePolicy9.setHeightForWidth(linerttstep->sizePolicy().hasHeightForWidth());
    linerttstep->setSizePolicy(sizePolicy9);

    gridLayout_13->addWidget(linerttstep, 0, 1, 1, 1);

    label_22 = new QLabel(frame_5);
    label_22->setObjectName(QString::fromUtf8("label_22"));
    sizePolicy8.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
    label_22->setSizePolicy(sizePolicy8);

    gridLayout_13->addWidget(label_22, 1, 0, 1, 1);

    label_23 = new QLabel(frame_5);
    label_23->setObjectName(QString::fromUtf8("label_23"));
    sizePolicy8.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
    label_23->setSizePolicy(sizePolicy8);

    gridLayout_13->addWidget(label_23, 1, 1, 1, 1);

    datertt1 = new QDateTimeEdit(frame_5);
    datertt1->setObjectName(QString::fromUtf8("datertt1"));
    sizePolicy9.setHeightForWidth(datertt1->sizePolicy().hasHeightForWidth());
    datertt1->setSizePolicy(sizePolicy9);
    datertt1->setFont(font1);

    gridLayout_13->addWidget(datertt1, 2, 0, 1, 1);

    datertt2 = new QDateTimeEdit(frame_5);
    datertt2->setObjectName(QString::fromUtf8("datertt2"));
    sizePolicy9.setHeightForWidth(datertt2->sizePolicy().hasHeightForWidth());
    datertt2->setSizePolicy(sizePolicy9);
    datertt2->setFont(font1);

    gridLayout_13->addWidget(datertt2, 2, 1, 1, 1);


    gridLayout_14->addWidget(frame_5, 8, 0, 1, 1);

    label_25 = new QLabel(results);
    label_25->setObjectName(QString::fromUtf8("label_25"));
    sizePolicy6.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
    label_25->setSizePolicy(sizePolicy6);

    gridLayout_14->addWidget(label_25, 7, 0, 1, 1);

    gridLayout_15 = new QGridLayout();
    gridLayout_15->setSpacing(6);
    gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
    rttavgButton = new QPushButton(results);
    rttavgButton->setObjectName(QString::fromUtf8("rttavgButton"));

    gridLayout_15->addWidget(rttavgButton, 2, 0, 1, 1);

    rttintervalButton = new QPushButton(results);
    rttintervalButton->setObjectName(QString::fromUtf8("rttintervalButton"));

    gridLayout_15->addWidget(rttintervalButton, 2, 1, 1, 1);

    rttcleanButton = new QPushButton(results);
    rttcleanButton->setObjectName(QString::fromUtf8("rttcleanButton"));

    gridLayout_15->addWidget(rttcleanButton, 3, 0, 1, 1);

    rttcycleButton = new QPushButton(results);
    rttcycleButton->setObjectName(QString::fromUtf8("rttcycleButton"));

    gridLayout_15->addWidget(rttcycleButton, 1, 1, 1, 1);

    rttnumButton = new QPushButton(results);
    rttnumButton->setObjectName(QString::fromUtf8("rttnumButton"));

    gridLayout_15->addWidget(rttnumButton, 1, 0, 1, 1);


    gridLayout_14->addLayout(gridLayout_15, 10, 0, 1, 2);

    verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout_14->addItem(verticalSpacer_4, 9, 0, 1, 1);

    comborttagent = new QComboBox(results);
    comborttagent->setObjectName(QString::fromUtf8("comborttagent"));

    gridLayout_14->addWidget(comborttagent, 1, 0, 1, 1);

    comborttprobe = new QComboBox(results);
    comborttprobe->setObjectName(QString::fromUtf8("comborttprobe"));

    gridLayout_14->addWidget(comborttprobe, 4, 0, 1, 1);

    label_26 = new QLabel(results);
    label_26->setObjectName(QString::fromUtf8("label_26"));

    gridLayout_14->addWidget(label_26, 5, 0, 1, 1);

    tabWidget_ctl->addTab(results, QString());

    gridLayout_4->addWidget(tabWidget_ctl, 2, 0, 1, 1);


    gridLayout->addLayout(gridLayout_4, 0, 1, 1, 1);

    testwindow->setCentralWidget(centralWidget);
    statusBar = new QStatusBar(testwindow);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    testwindow->setStatusBar(statusBar);
    menuBar = new QMenuBar(testwindow);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 1024, 28));
    menuHgfhf = new QMenu(menuBar);
    menuHgfhf->setObjectName(QString::fromUtf8("menuHgfhf"));
    menuHelp = new QMenu(menuBar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    testwindow->setMenuBar(menuBar);

    menuBar->addAction(menuHgfhf->menuAction());
    menuBar->addAction(menuHelp->menuAction());
    menuHgfhf->addAction(actionConnect);
    menuHgfhf->addAction(actionExit);
    menuHelp->addAction(actionManual);
    menuHelp->addAction(actionAbout);

    retranslateUi(testwindow);
    QObject::connect(exitButton, SIGNAL(clicked()), testwindow, SLOT(close()));
    QObject::connect(actionExit, SIGNAL(activated()), testwindow, SLOT(close()));
    QObject::connect(actionAbout, SIGNAL(activated()), aboutButton, SLOT(click()));
    QObject::connect(actionManual, SIGNAL(activated()), helpButton, SLOT(click()));

    tabWidget->setCurrentIndex(1);
    tabWidget_ctl->setCurrentIndex(3);


    QMetaObject::connectSlotsByName(testwindow);
    } // setupUi

    void retranslateUi(QMainWindow *testwindow)
    {
    testwindow->setWindowTitle(QApplication::translate("testwindow", "DB Viewer", 0, QApplication::UnicodeUTF8));
    actionConnect->setText(QApplication::translate("testwindow", "connect...", 0, QApplication::UnicodeUTF8));
    actionExit->setText(QApplication::translate("testwindow", "exit", 0, QApplication::UnicodeUTF8));
    actionManual->setText(QApplication::translate("testwindow", "manual...", 0, QApplication::UnicodeUTF8));
    actionAbout->setText(QApplication::translate("testwindow", "about...", 0, QApplication::UnicodeUTF8));
    exitButton->setText(QApplication::translate("testwindow", "exit", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("testwindow", "INFO:", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("testwindow", "data table", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("testwindow", "graphics", 0, QApplication::UnicodeUTF8));
    helpButton->setText(QApplication::translate("testwindow", "help", 0, QApplication::UnicodeUTF8));
    aboutButton->setText(QApplication::translate("testwindow", "about", 0, QApplication::UnicodeUTF8));
    agentButton->setText(QApplication::translate("testwindow", "Agents", 0, QApplication::UnicodeUTF8));
    targetButton->setText(QApplication::translate("testwindow", "targets", 0, QApplication::UnicodeUTF8));
    eventypetButton->setText(QApplication::translate("testwindow", "event types", 0, QApplication::UnicodeUTF8));
    tabWidget_ctl->setTabText(tabWidget_ctl->indexOf(lists), QApplication::translate("testwindow", "data lists", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("testwindow", "input agent name\n"
"or leave empty", 0, QApplication::UnicodeUTF8));
    probeButton->setText(QApplication::translate("testwindow", "show", 0, QApplication::UnicodeUTF8));
    probecleanButton->setText(QApplication::translate("testwindow", "clear", 0, QApplication::UnicodeUTF8));
    tabWidget_ctl->setTabText(tabWidget_ctl->indexOf(probes), QApplication::translate("testwindow", "probes", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("testwindow", "probe:", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("testwindow", "agent:", 0, QApplication::UnicodeUTF8));
    label_11->setText(QApplication::translate("testwindow", "type:", 0, QApplication::UnicodeUTF8));
    lineevcyc1->setText(QApplication::translate("testwindow", "0", 0, QApplication::UnicodeUTF8));
    lineevcyc2->setText(QApplication::translate("testwindow", "0", 0, QApplication::UnicodeUTF8));
    label_9->setText(QApplication::translate("testwindow", "from:", 0, QApplication::UnicodeUTF8));
    label_10->setText(QApplication::translate("testwindow", "to:", 0, QApplication::UnicodeUTF8));
    dateevnt1->setDisplayFormat(QApplication::translate("testwindow", "dd.MM.yy H:mm:ss", 0, QApplication::UnicodeUTF8));
    dateevent2->setDisplayFormat(QApplication::translate("testwindow", "dd.MM.yy H:mm:ss", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("testwindow", "from:", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("testwindow", "to:", 0, QApplication::UnicodeUTF8));
    lineEditeventinterval->setText(QApplication::translate("testwindow", "0", 0, QApplication::UnicodeUTF8));
    label_12->setText(QApplication::translate("testwindow", "timestep, s:", 0, QApplication::UnicodeUTF8));
    label_8->setText(QApplication::translate("testwindow", "cycles:", 0, QApplication::UnicodeUTF8));
    label_27->setText(QApplication::translate("testwindow", "event source:", 0, QApplication::UnicodeUTF8));
    losteventButton->setText(QApplication::translate("testwindow", "lost responces", 0, QApplication::UnicodeUTF8));
    eventcleanButton->setText(QApplication::translate("testwindow", "clear", 0, QApplication::UnicodeUTF8));
    eventButton->setText(QApplication::translate("testwindow", "events", 0, QApplication::UnicodeUTF8));
    checkBox->setText(QApplication::translate("testwindow", "distribution", 0, QApplication::UnicodeUTF8));
    tabWidget_ctl->setTabText(tabWidget_ctl->indexOf(events), QApplication::translate("testwindow", "events", 0, QApplication::UnicodeUTF8));
    label_16->setText(QApplication::translate("testwindow", "agent:", 0, QApplication::UnicodeUTF8));
    label_19->setText(QApplication::translate("testwindow", "probe:", 0, QApplication::UnicodeUTF8));
    label_20->setText(QApplication::translate("testwindow", "from:", 0, QApplication::UnicodeUTF8));
    label_21->setText(QApplication::translate("testwindow", "to:", 0, QApplication::UnicodeUTF8));
    linerttcyc1->setText(QApplication::translate("testwindow", "0", 0, QApplication::UnicodeUTF8));
    linerttcyc2->setText(QApplication::translate("testwindow", "0", 0, QApplication::UnicodeUTF8));
    label_24->setText(QApplication::translate("testwindow", "step, seconds:", 0, QApplication::UnicodeUTF8));
    linerttstep->setText(QApplication::translate("testwindow", "0", 0, QApplication::UnicodeUTF8));
    label_22->setText(QApplication::translate("testwindow", "from:", 0, QApplication::UnicodeUTF8));
    label_23->setText(QApplication::translate("testwindow", "to:", 0, QApplication::UnicodeUTF8));
    datertt1->setDisplayFormat(QApplication::translate("testwindow", "dd.MM.yy H:mm:ss", 0, QApplication::UnicodeUTF8));
    datertt2->setDisplayFormat(QApplication::translate("testwindow", "dd.MM.yy H:mm:ss", 0, QApplication::UnicodeUTF8));
    label_25->setText(QApplication::translate("testwindow", "time", 0, QApplication::UnicodeUTF8));
    rttavgButton->setText(QApplication::translate("testwindow", "distribution", 0, QApplication::UnicodeUTF8));
    rttintervalButton->setText(QApplication::translate("testwindow", "by time intervals", 0, QApplication::UnicodeUTF8));
    rttcleanButton->setText(QApplication::translate("testwindow", "reset", 0, QApplication::UnicodeUTF8));
    rttcycleButton->setText(QApplication::translate("testwindow", "by cycles", 0, QApplication::UnicodeUTF8));
    rttnumButton->setText(QApplication::translate("testwindow", "by numbers", 0, QApplication::UnicodeUTF8));
    label_26->setText(QApplication::translate("testwindow", "cycles:", 0, QApplication::UnicodeUTF8));
    tabWidget_ctl->setTabText(tabWidget_ctl->indexOf(results), QApplication::translate("testwindow", "response", 0, QApplication::UnicodeUTF8));
    menuHgfhf->setTitle(QApplication::translate("testwindow", "main", 0, QApplication::UnicodeUTF8));
    menuHelp->setTitle(QApplication::translate("testwindow", "help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class testwindow: public Ui_testwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTWINDOW_H
