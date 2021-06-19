// InterractiveImage.qml
import QtQuick 2.12

Item {
    id: root

    property int padding: 20
    property alias image: column.image
    property alias text: column.caption
    signal clicked()

    Column {
        id: column
        property alias image: rec.image
        property alias caption: text

        anchors.fill: parent

        Rectangle {
            property alias image: img
            id: rec
            anchors {
                left: parent.left
                right: parent.right
            }
            height: parent.height - text.height
            color: "transparent"
            // border.color: "red"
            Image {
                id: img
                anchors {
                    left: parent.left
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                }
                fillMode: Image.PreserveAspectFit
            }
        }

        Text {
            id: text
            anchors {
                left: parent.left
                right: parent.right
            }
            font.bold: true
            color: "white"
            height: 15
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    MouseArea {
        id: touchArea
        anchors.fill: parent
        anchors {
            topMargin: root.padding
            leftMargin: root.padding
            rightMargin: root.padding
            bottomMargin: root.padding
        }
        pressAndHoldInterval: 3000
        onClicked: {
            root.clicked()
            // console.log("Clicked!")
            // console.log("x: ", root.x)
            // console.log("y: ", root.y)
            // console.log("touchArea.x: ", touchArea.x)
            // console.log("touchArea.y: ", touchArea.y)
        }
    }
}