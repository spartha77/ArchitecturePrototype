/****************************************************************************
** Meta object code from reading C++ file 'facedetection.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../AdaptivePersonIdentification/facedetection.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'facedetection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_facedetection_t {
    QByteArrayData data[10];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_facedetection_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_facedetection_t qt_meta_stringdata_facedetection = {
    {
QT_MOC_LITERAL(0, 0, 13), // "facedetection"
QT_MOC_LITERAL(1, 14, 22), // "on_modelDir_PB_clicked"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 21), // "on_dataDir_PB_clicked"
QT_MOC_LITERAL(4, 60, 28), // "on_personName_LE_textChanged"
QT_MOC_LITERAL(5, 89, 4), // "arg1"
QT_MOC_LITERAL(6, 94, 17), // "on_run_PB_clicked"
QT_MOC_LITERAL(7, 112, 13), // "run_PB_status"
QT_MOC_LITERAL(8, 126, 25), // "on_dataDir_LE_textChanged"
QT_MOC_LITERAL(9, 152, 26) // "on_modelDir_LE_textChanged"

    },
    "facedetection\0on_modelDir_PB_clicked\0"
    "\0on_dataDir_PB_clicked\0"
    "on_personName_LE_textChanged\0arg1\0"
    "on_run_PB_clicked\0run_PB_status\0"
    "on_dataDir_LE_textChanged\0"
    "on_modelDir_LE_textChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_facedetection[] = {

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

void facedetection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        facedetection *_t = static_cast<facedetection *>(_o);
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

const QMetaObject facedetection::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_facedetection.data,
      qt_meta_data_facedetection,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *facedetection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *facedetection::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_facedetection.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int facedetection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
