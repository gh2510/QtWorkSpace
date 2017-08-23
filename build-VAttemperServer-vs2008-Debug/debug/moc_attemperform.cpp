/****************************************************************************
** Meta object code from reading C++ file 'attemperform.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VAttemperServer/attemperform.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'attemperform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AttemperForm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      29,   13,   13,   13, 0x0a,
      50,   45,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AttemperForm[] = {
    "AttemperForm\0\0resbtn_click()\0"
    "exitbtn_click()\0text\0indexChanged(QString)\0"
};

void AttemperForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AttemperForm *_t = static_cast<AttemperForm *>(_o);
        switch (_id) {
        case 0: _t->resbtn_click(); break;
        case 1: _t->exitbtn_click(); break;
        case 2: _t->indexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AttemperForm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AttemperForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AttemperForm,
      qt_meta_data_AttemperForm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AttemperForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AttemperForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AttemperForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AttemperForm))
        return static_cast<void*>(const_cast< AttemperForm*>(this));
    return QWidget::qt_metacast(_clname);
}

int AttemperForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
