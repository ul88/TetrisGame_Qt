#ifndef BLOCKS_H
#define BLOCKS_H

#include <QQuickPaintedItem>
#include<QList>
#include"Block.h"

class Blocks : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged FINAL)
    Q_PROPERTY(Block_Type blockType READ blockType WRITE setBlockType NOTIFY blockTypeChanged FINAL)
    QML_ELEMENT
public:
    friend class TetrisMap;
    friend class BlockCollision;
    Blocks(QQuickItem* parent = nullptr);
    enum Block_Type{
        BLOCK_TYPE_I=0,
        BLOCK_TYPE_L,
        BLOCK_TYPE_J,
        BLOCK_TYPE_O,
        BLOCK_TYPE_Z,
        BLOCK_TYPE_S,
        BLOCK_TYPE_T
    };
    Q_ENUM(Block_Type)

    void paint(QPainter* painter) override;

    QColor color() const {return m_color;}
    void setColor(const QColor& color);

    Block_Type blockType() const {return m_blockType;}
    void setBlockType(const Block_Type& blockType);

    void changeBlock();

public slots:
    void moveY(int direction);
    /*
        direction   0: 위
                    1: 아래
    */
    void moveX(int direction);
    /*
        direction   0: 왼쪽
                    1: 오른쪽
    */

    void spin(int direction);
    /*
        direction   0: 왼쪽
                    1: 오른쪽
    */
signals:
    void colorChanged();
    void blockTypeChanged();
private:
    QColor m_color;
    Block_Type m_blockType;
    QList<Block*> m_blocks;
    QPair<qreal, qreal> gridX;
    QPair<qreal, qreal> gridY;
};

#endif // BLOCKS_H
