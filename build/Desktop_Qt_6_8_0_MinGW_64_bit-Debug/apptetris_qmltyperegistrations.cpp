/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#if __has_include(<Block.h>)
#  include <Block.h>
#endif
#if __has_include(<Blocks.h>)
#  include <Blocks.h>
#endif
#if __has_include(<TetrisMap.h>)
#  include <TetrisMap.h>
#endif


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_tetris()
{
    QT_WARNING_PUSH QT_WARNING_DISABLE_DEPRECATED
    qmlRegisterTypesAndRevisions<Block>("tetris", 1);
    qmlRegisterAnonymousType<QQuickItem, 254>("tetris", 1);
    qmlRegisterTypesAndRevisions<Blocks>("tetris", 1);
    QMetaType::fromType<Blocks::Block_Type>().id();
    qmlRegisterTypesAndRevisions<TetrisMap>("tetris", 1);
    QT_WARNING_POP
    qmlRegisterModule("tetris", 1, 0);
}

static const QQmlModuleRegistration tetrisRegistration("tetris", qml_register_types_tetris);
