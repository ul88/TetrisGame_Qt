#ifndef BLOCKCOLLISION_H
#define BLOCKCOLLISION_H
#include"Blocks.h"
#include"TetrisMap.h"
#include<QList>

class BlockCollision
{
    QML_ELEMENT
public:
    BlockCollision();

    static bool isCollision(QList<Block*> pos);
    static bool isWallCollision(Blocks* blocks, QPair<qreal, qreal> gridPos);
    static bool isWallCollision(Block* block, QPair<qreal, qreal> gridPos);
    static bool isEndLine(QList<Block*> pos);
};

#endif // BLOCKCOLLISION_H
