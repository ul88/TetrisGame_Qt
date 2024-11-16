#include "BlockCollision.h"
#include<QSet>
BlockCollision::BlockCollision() {}

bool BlockCollision::isCollision(QList<Block*> pos){
    QSet<QPair<qreal,qreal>> cnt;

    for(auto iter : pos){
        if(cnt.find({iter->x(), iter->y()}) != cnt.end()) return true;
        cnt.insert({iter->x(), iter->y()});
    }
    return false;
}

bool BlockCollision::isWallCollision(Blocks* blocks){
    for(int i=0;i<4;i++){
        Block* now = blocks->m_blocks[i];
        if(now->x() < 0 || now->x() > blocks->gridX.second ||
            now->y() < 0 || now->y() > blocks->gridY.second) return true;
    }
    return false;
}

bool BlockCollision::isWallCollision(Block* block){

    Block* now = block;
    if(now->x() < 0 || now->x() > 25*9 ||
        now->y() < 0 || now->y() > 25*19) return true;

    return false;
}
