/****************************************************************************
** Meta object code from reading C++ file 'FFmpegQTGUItest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../FFmpegQTGUItest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FFmpegQTGUItest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FFmpegQTGUItest_t {
    QByteArrayData data[11];
    char stringdata0[118];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FFmpegQTGUItest_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FFmpegQTGUItest_t qt_meta_stringdata_FFmpegQTGUItest = {
    {
QT_MOC_LITERAL(0, 0, 15), // "FFmpegQTGUItest"
QT_MOC_LITERAL(1, 16, 11), // "startdecode"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "newDMessage"
QT_MOC_LITERAL(4, 41, 10), // "OnOpenfile"
QT_MOC_LITERAL(5, 52, 6), // "OnPlay"
QT_MOC_LITERAL(6, 59, 11), // "handleAddDM"
QT_MOC_LITERAL(7, 71, 15), // "handleNewPacket"
QT_MOC_LITERAL(8, 87, 9), // "AVPacket*"
QT_MOC_LITERAL(9, 97, 5), // "frame"
QT_MOC_LITERAL(10, 103, 14) // "handleDMessage"

    },
    "FFmpegQTGUItest\0startdecode\0\0newDMessage\0"
    "OnOpenfile\0OnPlay\0handleAddDM\0"
    "handleNewPacket\0AVPacket*\0frame\0"
    "handleDMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FFmpegQTGUItest[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    1,   54,    2, 0x0a /* Public */,
      10,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,

       0        // eod
};

void FFmpegQTGUItest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FFmpegQTGUItest *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startdecode(); break;
        case 1: _t->newDMessage(); break;
        case 2: _t->OnOpenfile(); break;
        case 3: _t->OnPlay(); break;
        case 4: _t->handleAddDM(); break;
        case 5: _t->handleNewPacket((*reinterpret_cast< AVPacket*(*)>(_a[1]))); break;
        case 6: _t->handleDMessage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FFmpegQTGUItest::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FFmpegQTGUItest::startdecode)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FFmpegQTGUItest::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FFmpegQTGUItest::newDMessage)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FFmpegQTGUItest::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_FFmpegQTGUItest.data,
    qt_meta_data_FFmpegQTGUItest,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FFmpegQTGUItest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FFmpegQTGUItest::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FFmpegQTGUItest.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int FFmpegQTGUItest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void FFmpegQTGUItest::startdecode()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void FFmpegQTGUItest::newDMessage()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
