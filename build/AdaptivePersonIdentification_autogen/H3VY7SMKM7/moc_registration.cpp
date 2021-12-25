/****************************************************************************
** Meta object code from reading C++ file 'registration.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../AdaptivePersonIdentification/registration.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'registration.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_registration_t {
    QByteArrayData data[23];
    char stringdata0[468];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_registration_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_registration_t qt_meta_stringdata_registration = {
    {
QT_MOC_LITERAL(0, 0, 12), // "registration"
QT_MOC_LITERAL(1, 13, 13), // "imageReceived"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 22), // "on_modelDir_PB_clicked"
QT_MOC_LITERAL(4, 51, 21), // "on_dataDir_PB_clicked"
QT_MOC_LITERAL(5, 73, 22), // "on_imageDir_PB_clicked"
QT_MOC_LITERAL(6, 96, 17), // "on_run_PB_clicked"
QT_MOC_LITERAL(7, 114, 19), // "on_abort_pb_clicked"
QT_MOC_LITERAL(8, 134, 13), // "run_PB_status"
QT_MOC_LITERAL(9, 148, 28), // "on_personName_LE_textChanged"
QT_MOC_LITERAL(10, 177, 4), // "arg1"
QT_MOC_LITERAL(11, 182, 25), // "on_dataDir_LE_textChanged"
QT_MOC_LITERAL(12, 208, 26), // "on_modelDir_LE_textChanged"
QT_MOC_LITERAL(13, 235, 15), // "OnImageNotified"
QT_MOC_LITERAL(14, 251, 8), // "cv::Mat*"
QT_MOC_LITERAL(15, 260, 13), // "notifiedImage"
QT_MOC_LITERAL(16, 274, 24), // "GetImageNotifiedFunction"
QT_MOC_LITERAL(17, 299, 32), // "std::function<void(cv::Mat*mat)>"
QT_MOC_LITERAL(18, 332, 23), // "on_batchMode_RB_clicked"
QT_MOC_LITERAL(19, 356, 24), // "on_personName_RB_clicked"
QT_MOC_LITERAL(20, 381, 26), // "on_imageDir_LE_textChanged"
QT_MOC_LITERAL(21, 408, 26), // "on_liveRegister_RB_clicked"
QT_MOC_LITERAL(22, 435, 32) // "on_livePersonName_LE_textChanged"

    },
    "registration\0imageReceived\0\0"
    "on_modelDir_PB_clicked\0on_dataDir_PB_clicked\0"
    "on_imageDir_PB_clicked\0on_run_PB_clicked\0"
    "on_abort_pb_clicked\0run_PB_status\0"
    "on_personName_LE_textChanged\0arg1\0"
    "on_dataDir_LE_textChanged\0"
    "on_modelDir_LE_textChanged\0OnImageNotified\0"
    "cv::Mat*\0notifiedImage\0GetImageNotifiedFunction\0"
    "std::function<void(cv::Mat*mat)>\0"
    "on_batchMode_RB_clicked\0"
    "on_personName_RB_clicked\0"
    "on_imageDir_LE_textChanged\0"
    "on_liveRegister_RB_clicked\0"
    "on_livePersonName_LE_textChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_registration[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    0,  103,    2, 0x08 /* Private */,
       7,    0,  104,    2, 0x08 /* Private */,
       8,    0,  105,    2, 0x08 /* Private */,
       9,    1,  106,    2, 0x08 /* Private */,
      11,    1,  109,    2, 0x08 /* Private */,
      12,    1,  112,    2, 0x08 /* Private */,
      13,    1,  115,    2, 0x08 /* Private */,
      16,    0,  118,    2, 0x08 /* Private */,
      18,    0,  119,    2, 0x08 /* Private */,
      19,    0,  120,    2, 0x08 /* Private */,
      20,    1,  121,    2, 0x08 /* Private */,
      21,    0,  124,    2, 0x08 /* Private */,
      22,    1,  125,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, 0x80000000 | 14,   15,
    0x80000000 | 17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void registration::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        registration *_t = static_cast<registration *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->imageReceived(); break;
        case 1: _t->on_modelDir_PB_clicked(); break;
        case 2: _t->on_dataDir_PB_clicked(); break;
        case 3: _t->on_imageDir_PB_clicked(); break;
        case 4: _t->on_run_PB_clicked(); break;
        case 5: _t->on_abort_pb_clicked(); break;
        case 6: _t->run_PB_status(); break;
        case 7: _t->on_personName_LE_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->on_dataDir_LE_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->on_modelDir_LE_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->OnImageNotified((*reinterpret_cast< cv::Mat*(*)>(_a[1]))); break;
        case 11: { std::function<void(cv::Mat*mat)> _r = _t->GetImageNotifiedFunction();
            if (_a[0]) *reinterpret_cast< std::function<void(cv::Mat*mat)>*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->on_batchMode_RB_clicked(); break;
        case 13: _t->on_personName_RB_clicked(); break;
        case 14: _t->on_imageDir_LE_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->on_liveRegister_RB_clicked(); break;
        case 16: _t->on_livePersonName_LE_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (registration::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&registration::imageReceived)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject registration::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_registration.data,
      qt_meta_data_registration,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *registration::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *registration::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_registration.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int registration::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void registration::imageReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
