import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 840
    visible: true
    title: qsTr("Hello World")

    TetrisMap{
        id: tetrisMap;
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

    Button{
        id: button
        width: 50
        height: 50

        onClicked: {
            console.log("click");
            blocksModel.append({})
        }
    }


    ListModel{
        id: blocksModel
    }

    Repeater{
        model: blocksModel

        Blocks{
            x:grid.x
            y:grid.y
            blockType: Blocks.BLOCK_TYPE_L

            Component.onCompleted:{
                console.log("tetrisMap focus: ",tetrisMap.focus);
                tetrisMap.forceActiveFocus();
                tetrisMap.addBlockPos(this);
                console.log("completed succ", focus);
                console.log("tetrisMap focus: ",tetrisMap.focus);
            }
        }
    }

}
