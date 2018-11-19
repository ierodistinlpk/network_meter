/****************************************************************************
** Meta object code from reading C++ file 'testwindow.h'
**
** Created: Thu Jun 25 00:01:55 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "testwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_testwindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      40,   11,   11,   11, 0x08,
      69,   11,   11,   11, 0x08,
      98,   11,   11,   11, 0x08,
     123,   11,   11,   11, 0x08,
     149,   11,   11,   11, 0x08,
     175,   11,   11,   11, 0x08,
     206,   11,   11,   11, 0x08,
     236,   11,   11,   11, 0x08,
     272,   11,   11,   11, 0x08,
     300,   11,   11,   11, 0x08,
     335,   11,   11,   11, 0x08,
     365,   11,   11,   11, 0x08,
     389,   11,   11,   11, 0x08,
     414,   11,   11,   11, 0x08,
     439,   11,   11,   11, 0x08,
     465,   11,   11,   11, 0x08,
     494,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_testwindow[] = {
    "testwindow\0\0on_rttcycleButton_clicked()\0"
    "on_actionConnect_triggered()\0"
    "on_losteventButton_clicked()\0"
    "on_eventButton_clicked()\0"
    "on_rttavgButton_clicked()\0"
    "on_rttnumButton_clicked()\0"
    "on_rttintervalButton_clicked()\0"
    "on_probecleanButton_clicked()\0"
    "on_comborttagent_activated(QString)\0"
    "on_rttcleanButton_clicked()\0"
    "on_comboevagent_activated(QString)\0"
    "on_eventcleanButton_clicked()\0"
    "on_helpButton_clicked()\0"
    "on_aboutButton_clicked()\0"
    "on_probeButton_clicked()\0"
    "on_targetButton_clicked()\0"
    "on_eventypetButton_clicked()\0"
    "on_agentButton_clicked()\0"
};

const QMetaObject testwindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_testwindow,
      qt_meta_data_testwindow, 0 }
};

const QMetaObject *testwindow::metaObject() const
{
    return &staticMetaObject;
}

void *testwindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_testwindow))
        return static_cast<void*>(const_cast< testwindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int testwindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_rttcycleButton_clicked(); break;
        case 1: on_actionConnect_triggered(); break;
        case 2: on_losteventButton_clicked(); break;
        case 3: on_eventButton_clicked(); break;
        case 4: on_rttavgButton_clicked(); break;
        case 5: on_rttnumButton_clicked(); break;
        case 6: on_rttintervalButton_clicked(); break;
        case 7: on_probecleanButton_clicked(); break;
        case 8: on_comborttagent_activated((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: on_rttcleanButton_clicked(); break;
        case 10: on_comboevagent_activated((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: on_eventcleanButton_clicked(); break;
        case 12: on_helpButton_clicked(); break;
        case 13: on_aboutButton_clicked(); break;
        case 14: on_probeButton_clicked(); break;
        case 15: on_targetButton_clicked(); break;
        case 16: on_eventypetButton_clicked(); break;
        case 17: on_agentButton_clicked(); break;
        }
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
