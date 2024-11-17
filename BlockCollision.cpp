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

bool BlockCollision::isWallCollision(Blocks* blocks, QPair<qreal, qreal> gridPos){
    for(int i=0;i<4;i++){
        Block* now = blocks->m_blocks[i];
        if(now->x() < 0 || now->x() > gridPos.first ||
            now->y() < 0 || now->y() > gridPos.second) return true;
    }
    return false;
}

bool BlockCollision::isWallCollision(Block* block, QPair<qreal, qreal> gridPos){

    Block* now = block;
    if(now->x() < 0 || now->x() > gridPos.first ||
        now->y() < 0 || now->y() > gridPos.second) return true;

    return false;
}

bool BlockCollision::isEndLine(QList<Block*> pos){
    for(auto iter : pos){
        if(iter->y() < 0) return true;
    }
    return false;
}
