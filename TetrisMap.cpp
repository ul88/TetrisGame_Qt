#include "TetrisMap.h"
#include"BlockCollision.h"
#include<QTimer>
#include<QList>
#include<QMap>

TetrisMap::TetrisMap(QQuickItem* parent)
    : QQuickItem(parent)
{
    m_now = nullptr;
    setFocus(true);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&TetrisMap::downBlock));
    timer->start(100);
}

void TetrisMap::addBlockPos(Blocks* blocks){
    m_now = blocks;
    for(Block* iter : blocks->m_blocks){
        m_pos.append(iter);
    }

    qDebug()<<"현재 블럭:";
    for(auto iter : blocks->m_blocks){
        qDebug()<<iter;
    }

    qDebug()<<"블럭 위치:";
    for(auto iter : m_pos){
        qDebug()<<iter;
    }
}

void TetrisMap::keyPressEvent(QKeyEvent* event){
    if(m_now == nullptr) return;
    switch(event->key()){
    case Qt::Key_Left:
        qDebug()<<"move left";
        m_now->moveX(0);
        if(BlockCollision::isCollision(m_pos) || BlockCollision::isWallCollision(m_now)){
            m_now->moveX(1);
        }
        break;
    case Qt::Key_Right:
        qDebug()<<"move right";
        m_now->moveX(1);
        if(BlockCollision::isCollision(m_pos) || BlockCollision::isWallCollision(m_now)){
            m_now->moveX(0);
        }
        break;
    case Qt::Key_Z:
        qDebug()<<"left spin";
        m_now->spin(0);
        if(BlockCollision::isCollision(m_pos) || BlockCollision::isWallCollision(m_now)){
            m_now->spin(1);
        }
        break;
    case Qt::Key_X:
        qDebug()<<"right spin";
        m_now->spin(1);
        if(BlockCollision::isCollision(m_pos) || BlockCollision::isWallCollision(m_now)){
            m_now->spin(0);
        }
        break;
    }
    update();
}

void TetrisMap::downBlock(){
    if(m_now == nullptr) return;
    m_now->moveY(1);
    if(BlockCollision::isCollision(m_pos) || BlockCollision::isWallCollision(m_now)){
        m_now->moveY(0);
        for(int i=0;i<4;i++) m_now = nullptr;
        deleteLine();
    }
}

void TetrisMap::deleteLine(){

}
