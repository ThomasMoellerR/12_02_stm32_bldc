/****************************************************************************
** Meta object code from reading C++ file 'ser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../untitled/ser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Ser_t {
    QByteArrayData data[10];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Ser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Ser_t qt_meta_stringdata_Ser = {
    {
QT_MOC_LITERAL(0, 0, 3), // "Ser"
QT_MOC_LITERAL(1, 4, 10), // "Rec_Output"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 6), // "output"
QT_MOC_LITERAL(4, 23, 10), // "Snd_Output"
QT_MOC_LITERAL(5, 34, 9), // "Rec_Input"
QT_MOC_LITERAL(6, 44, 5), // "input"
QT_MOC_LITERAL(7, 50, 9), // "Snd_Input"
QT_MOC_LITERAL(8, 60, 9), // "Debug_HEX"
QT_MOC_LITERAL(9, 70, 11) // "Debug_ASCII"

    },
    "Ser\0Rec_Output\0\0output\0Snd_Output\0"
    "Rec_Input\0input\0Snd_Input\0Debug_HEX\0"
    "Debug_ASCII"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   50,    2, 0x0a /* Public */,
       7,    1,   53,    2, 0x0a /* Public */,
       8,    1,   56,    2, 0x0a /* Public */,
       9,    1,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::QByteArray,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void, QMetaType::QByteArray,    6,

       0        // eod
};

void Ser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Ser *_t = static_cast<Ser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Rec_Output((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->Snd_Output((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->Rec_Input((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->Snd_Input((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->Debug_HEX((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 5: _t->Debug_ASCII((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Ser::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Ser::Rec_Output)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Ser::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Ser::Snd_Output)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Ser::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Ser.data,
      qt_meta_data_Ser,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Ser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Ser.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Ser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Ser::Rec_Output(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Ser::Snd_Output(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
