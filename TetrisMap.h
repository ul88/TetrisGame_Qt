#ifndef TETRISMAP_H
#define TETRISMAP_H

#include <QQuickItem>
#include<QQueue>
#include"Blocks.h"
#include"Block.h"

class TetrisMap : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(Blocks::Block_Type down READ down WRITE setDown NOTIFY downChanged FINAL)
    Q_PROPERTY(Blocks::Block_Type hold READ hold WRITE setHold NOTIFY holdChanged FINAL)
    Q_PROPERTY(QList<Blocks::Block_Type> typeList READ typeList NOTIFY typeListChanged FINAL)
    QML_ELEMENT
public:
    TetrisMap(QQuickItem* parent = nullptr);

    Blocks::Block_Type down() const {return m_down;}
    void setDown(Blocks::Block_Type down);

    Blocks::Block_Type hold() const {return m_hold;}
    void setHold(Blocks::Block_Type hold);

    QList<Blocks::Block_Type> typeList() const {return m_typeList;}

    void addTypeList();

    void wallKick(int direction);
    /*
        direction   0: 왼쪽
                    1: 오른쪽
    */

    void gameOver();
public slots:
    void keyPressEvent(QKeyEvent* event) override;
    void addBlockPos(Blocks* blocks);
    void deleteLine();
    void downBlock();
signals:
    void downChanged();
    void holdChanged();
    void typeListChanged();
private:
    Blocks::Block_Type m_down;
    QList<Block*> m_pos;
    QList<Blocks::Block_Type> m_typeList;
    Blocks* m_now;
    QTimer* timer;
    Blocks::Block_Type m_hold;
    bool isHold;
    QPair<qreal, qreal> m_gridPos; //first: x의 끝 좌표, second: y의 끝 좌표
};

#endif // TETRISMAP_H
