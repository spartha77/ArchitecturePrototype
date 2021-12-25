/****************************************************************************
** Meta object code from reading C++ file 'bodyidentification.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../AdaptivePersonIdentification/bodyidentification.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bodyidentification.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_bodyidentification_t {
    QByteArrayData data[10];
    char stringdata0[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_bodyidentification_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_bodyidentification_t qt_meta_stringdata_bodyidentification = {
    {
QT_MOC_LITERAL(0, 0, 18), // "bodyidentification"
QT_MOC_LITERAL(1, 19, 22), // "on_modelDir_PB_clicked"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 21), // "on_dataDir_PB_clicked"
QT_MOC_LITERAL(4, 65, 28), // "on_personName_LE_textChanged"
QT_MOC_LITERAL(5, 94, 4), // "arg1"
QT_MOC_LITERAL(6, 99, 17), // "on_run_PB_clicked"
QT_MOC_LITERAL(7, 117, 13), // "run_PB_status"
QT_MOC_LITERAL(8, 131, 25), // "on_dataDir_LE_textChanged"
QT_MOC_LITERAL(9, 157, 26) // "on_modelDir_LE_textChanged"

    },
    "bodyidentification\0on_modelDir_PB_clicked\0"
    "\0on_dataDir_PB_clicked\0"
    "on_personName_LE_textChanged\0arg1\0"
    "on_run_PB_clicked\0run_PB_status\0"
    "on_dataDir_LE_textChanged\0"
    "on_modelDir_LE_textChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_bodyidentification[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    1,   51,    2, 0x08 /* Private */,
       6,    0,   54,    2, 0x08 /* Private */,
       7,    0,   55,    2, 0x08 /* Private */,
       8,    1,   56,    2, 0x08 /* Private */,
       9,    1,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void bodyidentification::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        bodyidentification *_t = static_cast<bodyidentification *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_modelDir_PB_clicked(); break;
        case 1: _t->on_dataDir_PB_clicked(); break;
        case 2: _t->on_personName_LE_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_run_PB_clicked(); break;
        case 4: _t->run_PB_status(); break;
        case 5: _t->on_dataDir_LE_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_modelDir_LE_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject bodyidentification::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_bodyidentification.data,
      qt_meta_data_bodyidentification,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *bodyidentification::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *bodyidentification::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_bodyidentification.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int bodyidentification::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
