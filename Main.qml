import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 840
    visible: true
    title: qsTr("Hello World")

    TetrisMap{
        id: tetrisMap;

        Component.onCompleted:{
            blocksModel.append({})
        }

        onDownChanged:{
            blocksModel.append({})
        }
    }

    Grid {
        id: grid
        x:180
        y:150
        rows: 20
        columns: 10
        spacing: 0 // 칸 사이의 간격을 0으로 설정

        // 각 칸을 정의
        Repeater {
            model: 200 // 10x10 = 100칸

            Rectangle {
                width: 25
                height: 25
                color: "lightgray" // 칸의 색상
                border.color: "black" // 테두리 색상
                border.width: 1 // 테두리 두께
            }
        }
    }

    ListModel{
        id: blocksModel
    }

    Item{
        x:60
        y:50
        Rectangle{
            width:130
            height:75
            border.width: 3
            color:"gray"
        }
        Blocks{
            x:-60
            y: 10
            z: 1
            blockType: tetrisMap.hold

            Component.onCompleted:{
                if(tetrisMap.typeList[index] != Blocks.BLOCK_TYPE_I &&
                        tetrisMap.typeList[index] != Blocks.BLOCK_TYPE_O){
                    x = -45
                }
            }
        }
    }


    Repeater{
        model: 5
        Item{
            x: 490
            y: 130 + index*100
            Rectangle{
                width:130
                height:100
                color:"gray"
            }
            Blocks{
                x: -60
                y: 10
                blockType: tetrisMap.typeList[index]
                z:1

                Component.onCompleted:{
                    if(tetrisMap.typeList[index] != Blocks.BLOCK_TYPE_I &&
                            tetrisMap.typeList[index] != Blocks.BLOCK_TYPE_O){
                        x = -45
                    }
                }
            }

        }

    }

    Repeater{
        model: blocksModel

        Blocks{
            x:grid.x
            y:grid.y
            blockType: tetrisMap.down

            Component.onCompleted:{
                blockType = tetrisMap.down
                console.log("tetrisMap focus: ",tetrisMap.focus);
                tetrisMap.forceActiveFocus();
                tetrisMap.addBlockPos(this);
                console.log("completed succ", focus);
                console.log("tetrisMap focus: ",tetrisMap.focus);
            }
        }
    }

}
