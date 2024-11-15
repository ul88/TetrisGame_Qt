#include "Block.h"
#include<QPainter>
#include<QKeyEvent>

Block::Block(QQuickItem* parent)
    :   QQuickPaintedItem(parent),
    m_color(color())
{
    setWidth(25);
    setHeight(25);
}

void Block::setColor(const QColor& color){
    m_color = color;
    emit colorChanged();
}

void Block::paint(QPainter* painter){
    painter->setBrush(m_color);
    painter->drawRect(0, 0, width(), height());
    update();
}
