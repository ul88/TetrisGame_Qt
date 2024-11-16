#include "Blocks.h"
#include"TetrisMap.h"
#include<QPainter>
#include<QQueue>

Blocks::Blocks(QQuickItem* parent)
    :   QQuickPaintedItem(parent),
    m_color(color()),
    m_blockType(blockType())
{
    gridX = {0, 25*9};
    gridY = {0, 25*19};
    for(int i=0;i<4;i++){
        QPointer<Block> block = new Block(this);
        block->setColor(m_color);
        m_blocks.append(block);
    }
}

void Blocks::setColor(const QColor& color){
    m_color = color;
    for(int i=0;i<4;i++){
        m_blocks[i]->setColor(m_color);
    }
    emit colorChanged();
}

void Blocks::setBlockType(const Block_Type& blockType){
    m_blockType = blockType;
    changeBlock();
    emit blockTypeChanged();
}

void Blocks::paint(QPainter* painter){
    for (Block* block : m_blocks) {
        block->paint(painter);
    }
}

void Blocks::moveX(int direction){
    switch(direction){
    case 0:
        for(int i=0;i<4;i++){
            m_blocks[i]->setX(m_blocks[i]->x()-25);
        }
        break;
    case 1:
        for(int i=0;i<4;i++){
            m_blocks[i]->setX(m_blocks[i]->x()+25);
        }
        break;
    }
    update();
}

void Blocks::moveY(int direction){
    switch(direction){
    case 0:
        for(int i=0;i<4;i++){
            m_blocks[i]->setY(m_blocks[i]->y()-25);
        }
        break;
    case 1:
        for(int i=0;i<4;i++){
            m_blocks[i]->setY(m_blocks[i]->y()+25);
        }
        break;
    }
    update();
}

void Blocks::spin(int direction){
    qreal centerX=m_blocks[1]->x(), centerY=m_blocks[1]->y();

    switch(direction){
    case 0:
        for(auto iter : m_blocks){
            qreal tempX = (iter->y() - centerY) + centerX, tempY = -(iter->x() - centerX) + centerY;

            iter->setX(tempX);
            iter->setY(tempY);
            qDebug()<<iter;
        }
        break;
    case 1:
        for(auto iter : m_blocks){
            qreal tempX = -(iter->y() - centerY) + centerX, tempY = (iter->x() - centerX) + centerY;

            iter->setX(tempX);
            iter->setY(tempY);
            qDebug()<<iter;
        }
        break;
    }
    update();
}

void Blocks::changeBlock(){
    qDebug()<<"change succ";
    switch(m_blockType){
    case BLOCK_TYPE_I:
        //x
        m_blocks[0]->setX(0);
        m_blocks[1]->setX(25);
        m_blocks[2]->setX(50);
        m_blocks[3]->setX(75);
        //y
        m_blocks[0]->setY(0);
        m_blocks[1]->setY(0);
        m_blocks[2]->setY(0);
        m_blocks[3]->setY(0);

        setColor("aqua");
        break;
    case BLOCK_TYPE_J:
        //x
        m_blocks[0]->setX(0);
        m_blocks[1]->setX(0);
        m_blocks[2]->setX(25);
        m_blocks[3]->setX(50);
        //y
        m_blocks[0]->setY(0);
        m_blocks[1]->setY(25);
        m_blocks[2]->setY(25);
        m_blocks[3]->setY(25);

        setColor("blue");
        break;
    case Blocks::BLOCK_TYPE_L:
        //x
        m_blocks[0]->setX(0);
        m_blocks[1]->setX(25);
        m_blocks[2]->setX(50);
        m_blocks[3]->setX(50);

        //y
        m_blocks[0]->setY(25);
        m_blocks[1]->setY(25);
        m_blocks[2]->setY(25);
        m_blocks[3]->setY(0);

        setColor("orange");
        break;
    case BLOCK_TYPE_O:
        //x
        m_blocks[0]->setX(25);
        m_blocks[1]->setX(25);
        m_blocks[2]->setX(50);
        m_blocks[3]->setX(50);

        //y
        m_blocks[0]->setY(0);
        m_blocks[1]->setY(25);
        m_blocks[2]->setY(0);
        m_blocks[3]->setY(25);

        setColor("yellow");
        break;
    case BLOCK_TYPE_S:
        //x
        m_blocks[0]->setX(0);
        m_blocks[1]->setX(25);
        m_blocks[2]->setX(25);
        m_blocks[3]->setX(50);

        //y
        m_blocks[0]->setY(25);
        m_blocks[1]->setY(25);
        m_blocks[2]->setY(0);
        m_blocks[3]->setY(0);

        setColor("green");
        break;
    case BLOCK_TYPE_T:
        //x
        m_blocks[0]->setX(0);
        m_blocks[1]->setX(25);
        m_blocks[2]->setX(50);
        m_blocks[3]->setX(25);

        //y
        m_blocks[0]->setY(25);
        m_blocks[1]->setY(25);
        m_blocks[2]->setY(25);
        m_blocks[3]->setY(0);

        setColor("purple");
        break;
    case BLOCK_TYPE_Z:
        //x
        m_blocks[0]->setX(0);
        m_blocks[1]->setX(25);
        m_blocks[2]->setX(25);
        m_blocks[3]->setX(50);

        //y
        m_blocks[0]->setY(0);
        m_blocks[1]->setY(0);
        m_blocks[2]->setY(25);
        m_blocks[3]->setY(25);

        setColor("red");
        break;
    default:
        break;
    }

    for(int i=0;i<4;i++){
        m_blocks[i]->setX(m_blocks[i]->x()+25*3);
    }
}
