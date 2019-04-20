/****************************************************************************
** Meta object code from reading C++ file 'config.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../untitled/config.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'config.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Config_t {
    QByteArrayData data[7];
    char stringdata0[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Config_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Config_t qt_meta_stringdata_Config = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Config"
QT_MOC_LITERAL(1, 7, 7), // "sigBaud"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 7), // "sigPort"
QT_MOC_LITERAL(4, 24, 3), // "ini"
QT_MOC_LITERAL(5, 28, 15), // "Map_To_JsonFile"
QT_MOC_LITERAL(6, 44, 15) // "JsonFile_To_Map"

    },
    "Config\0sigBaud\0\0sigPort\0ini\0Map_To_JsonFile\0"
    "JsonFile_To_Map"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Config[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   45,    2, 0x0a /* Public */,
       5,    0,   46,    2, 0x0a /* Public */,
       6,    0,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    1,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Config::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Config *_t = static_cast<Config *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigBaud((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sigPort((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ini(); break;
        case 3: _t->Map_To_JsonFile(); break;
        case 4: _t->JsonFile_To_Map(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Config::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Config::sigBaud)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Config::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Config::sigPort)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Config::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Config.data,
      qt_meta_data_Config,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Config::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Config::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Config.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Config::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Config::sigBaud(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Config::sigPort(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
