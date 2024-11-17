#include "TetrisMap.h"
#include"BlockCollision.h"
#include<QTimer>
#include<QList>
#include<QMap>
#include<QQueue>
#include<QRandomGenerator>

TetrisMap::TetrisMap(QQuickItem* parent)
    : QQuickItem(parent)
{
    m_gridPos = {25*9, 25*19};

    setHold(Blocks::BLOCK_NONE);
    isHold = true;
    addTypeList();
    setDown(m_typeList.front());
    m_typeList.pop_front();
    emit typeListChanged();

    m_now = nullptr;
    setFocus(true);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&TetrisMap::downBlock));
    timer->setInterval(1000);
    timer->start();
}

void TetrisMap::setDown(Blocks::Block_Type down){
    m_down = down;
    emit downChanged();
}

void TetrisMap::setHold(Blocks::Block_Type hold){
    m_hold = hold;
    emit holdChanged();
}

void TetrisMap::addTypeList(){
    if(m_typeList.size() > 5) return;
    int visit[7] = {0,};
    for(int i=0;i<7;){
        int rand = QRandomGenerator::global()->bounded(7);
        if(visit[rand]) continue;
        visit[rand] = 1;
        i++;
        m_typeList.push_back((Blocks::Block_Type)rand);
    }
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

void TetrisMap::wallKick(int direction){
    switch(direction){
    case 0:
        break;
    case 1:
        break;
    }
}

void TetrisMap::keyPressEvent(QKeyEvent* event){
    if(m_now == nullptr) return;
    QList<Block*> temp;
    Blocks::Block_Type tempType;
    switch(event->key()){
    case Qt::Key_Left:
        qDebug()<<"move left";
        m_now->moveX(0);
        if(BlockCollision::isCollision(m_pos) || BlockCollision::isWallCollision(m_now, m_gridPos)){
            m_now->moveX(1);
        }
        break;
    case Qt::Key_Right:
        qDebug()<<"move right";
        m_now->moveX(1);
        if(BlockCollision::isCollision(m_pos) || BlockCollision::isWallCollision(m_now, m_gridPos)){
            m_now->moveX(0);
        }
        break;
    case Qt::Key_Down:
        qDebug()<<"move down";
        m_now->moveY(1);
        if(BlockCollision::isCollision(m_pos) || BlockCollision::isWallCollision(m_now, m_gridPos)){
            m_now->moveY(0);
        }
        break;
    case Qt::Key_Z:
        qDebug()<<"left spin";
        m_now->spin(0);
        if(BlockCollision::isCollision(m_pos) || BlockCollision::isWallCollision(m_now, m_gridPos)){
            m_now->spin(1);
        }
        break;
    case Qt::Key_X:
        qDebug()<<"right spin";
        m_now->spin(1);
        if(BlockCollision::isCollision(m_pos) || BlockCollision::isWallCollision(m_now, m_gridPos)){
            m_now->spin(0);
        }
        break;
    case Qt::Key_C:
        if(!isHold) break;
        if(m_hold == Blocks::BLOCK_NONE){
            for(auto i : m_pos){
                bool flag = false;
                for(auto j : m_now->m_blocks){
                    if(i == j){
                        flag = true;
                        break;
                    }
                }

                if(!flag){
                    temp.append(i);
                }
            }
            for(auto iter : m_now->m_blocks) delete iter;
            m_pos = temp;
            m_now = nullptr;
            isHold = false;
            setHold(m_down);
            addTypeList();
            setDown(m_typeList.front());
            m_typeList.pop_front();
            emit typeListChanged();
        }else{
            tempType = m_hold;
            isHold = false;
            setHold(m_down);
            m_now->setBlockType(tempType);
        }
        break;
    case Qt::Key_Space:
        qDebug()<<"hard drap";
        while(!BlockCollision::isCollision(m_pos) && !BlockCollision::isWallCollision(m_now, m_gridPos)){
            m_now->moveY(1);
        }
        m_now->moveY(0);

        deleteLine();
        isHold = true;
        addTypeList();
        setDown(m_typeList.front());
        m_typeList.pop_front();
        emit typeListChanged();
        if(BlockCollision::isEndLine(m_pos)) gameOver();
        timer->start(1000);
        break;
    }
    update();
}

void TetrisMap::downBlock(){
    if(m_now == nullptr) return;
    m_now->moveY(1);
    if(BlockCollision::isCollision(m_pos) || BlockCollision::isWallCollision(m_now, m_gridPos)){
        m_now->moveY(0);
        m_now = nullptr;
        deleteLine();
        isHold = true;
        addTypeList();
        setDown(m_typeList.front());
        m_typeList.pop_front();
        emit typeListChanged();
        if(BlockCollision::isEndLine(m_pos)) gameOver();
    }
}

void TetrisMap::deleteLine(){
    QMap<qreal, int> m;
    QList<Block*> line[21];
    for(auto iter : m_pos){
        m[iter->y()]++;
    }
    int maxLineLocation = 0;
    int cnt = 0;
    bool flag = false;
    QList<Block*> temp;
    for(auto iter : m_pos){
        if(m[iter->y()] == 10){
            maxLineLocation = std::max(maxLineLocation, (int)iter->y()/25);
            delete iter;
            flag = true;
            cnt++;
        }else{
            temp.append(iter);
        }
    }
    m_pos = temp;

    if(flag){
        for(auto iter : m_pos){
            line[(int)iter->y()/25].append(iter);
        }
        qDebug()<<"cnt: "<<cnt;
        for(int i=maxLineLocation-1;i>=0;i--){
            for(auto iter : line[i]){
                for(int j=0;j<cnt/10;j++){
                    iter->setY(iter->y()+25);
                    if(BlockCollision::isCollision(m_pos) || BlockCollision::isWallCollision(iter, m_gridPos)){
                        iter->setY(iter->y()-25);
                        break;
                    }
                }
            }
        }

    }
}

void TetrisMap::gameOver(){
    qDebug()<<"game over";
    timer->stop();
    setFocus(false);
}
