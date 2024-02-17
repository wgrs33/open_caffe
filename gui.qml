import QtQuick 2.4

Item {
    width: 400
    height: 400

    PathView {
        id: menu
        x: 10
        y: 40
        width: 780
        height: 320
        delegate: Column {
            spacing: 5
            Rectangle {
                width: 40
                height: 40
                color: colorCode
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                x: 5
                text: name
                anchors.horizontalCenter: parent.horizontalCenter
                font.bold: true
            }
        }
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }
        path: Path {
            PathQuad {
                x: 120
                y: 25
                controlX: 260
                controlY: 75
            }

            PathQuad {
                x: 120
                y: 100
                controlX: -20
                controlY: 75
            }
            startX: 120
            startY: 100
        }
    }

    Image {
        id: backgrd
        x: 0
        y: 0
        width: 800
        height: 480
        source: "resources/images/background2.png"
        fillMode: Image.PreserveAspectFit
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75;height:480;width:800}
}
##^##*/

