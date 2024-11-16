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
    static bool isWallCollision(Blocks* blocks);
    static bool isWallCollision(Block* block);
};

#endif // BLOCKCOLLISION_H
