#ifndef TETRISMAP_H
#define TETRISMAP_H

#include <QQuickItem>
#include"Blocks.h"
#include"Block.h"

class TetrisMap : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    TetrisMap(QQuickItem* parent = nullptr);

public slots:
    void keyPressEvent(QKeyEvent* event) override;
    void addBlockPos(Blocks* blocks);
    void deleteLine();
    void downBlock();
signals:

private:
    QList<Block*> m_pos;
    Blocks* m_now;
    QTimer* timer;
};

#endif // TETRISMAP_H
