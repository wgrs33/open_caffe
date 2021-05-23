import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
//import com.company.ttext 1.0

ApplicationWindow {
    id: app
    width: 800
    height: 480
    visible: true
    title: qsTr("Coffee Machine")
    background: Image {
        source: "qrc:///resources/images/background2.png"
    }

    Connections {
        target: TestText
        function onTextChanged(newText) {
            test.text = newText
        }
    }

    Text {
        anchors.centerIn: parent
        id: test
        text: ""
        font.family: "Courier"
        font.pointSize: 16
        color: "white"
        visible: false
    }

    Column {
        anchors.fill: parent
        ToolBar {
            id: head
            background: null
            height: 50
            anchors {
                left: parent.left
                right: parent.right
            }
            RowLayout {
                anchors {
                    top: parent.top
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                ToolButton {
                    contentItem: Text {
                        text: qsTr("<")
                        // font: control.font
                        opacity: enabled ? 1.0 : 0.3
                        color: "#f0f0f0"
                    }
                    background: null
                    onClicked: header_text.text = "No yolo"
                }
                Label {
                    id: header_text
                    text: "Title"
                    elide: Label.ElideRight
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                    color: "#f0f0f0"
                }
                ToolButton {
                    contentItem: Text {
                        text: qsTr("⋮")
                        // font: control.font
                        opacity: enabled ? 1.0 : 0.3
                        color: "#f0f0f0"
                    }
                    background: null
                    onClicked: header_text.text = "Yolo"
                }
            }
        }

        SwipeView {
            id: swipeView
            currentIndex: 0
            height: (parent.height - head.height - footer.height)
            anchors {
                left: parent.left
                right: parent.right
            }

            Page {
                id: firstPage
                background: null
                height: 150
                anchors {
                    top: parent.top
                    topMargin: (100 + head.height)
                }
                contentItem: Row {
                    height: parent.height
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    
                    InterractiveImage {
                        width: 200
                        height: 150
                        image.source: "qrc:///resources/images/Icons/Ristretto.png"
                        text.text: qsTr("Ristretto")
                        text.color: "#f0f0f0"
                        text.height: 25
                        onClicked: {
                            header_text.text = text.text
                        }
                    }

                    InterractiveImage {
                        width: 200
                        height: 150
                        image.source: "qrc:///resources/images/Icons/Espresso.png"
                        text.text: qsTr("Espresso")
                        text.color: "#f0f0f0"
                        text.height: 25
                        onClicked: {
                            header_text.text = text.text
                            // console.log("Swipe height: ", swipeView.height)
                            // console.log("Swipe width: ", swipeView.width)
                            // console.log("Swipe x: ", swipeView.x)
                            // console.log("Swipe y: ", swipeView.y)
                            // console.log("Swipe parent: ", swipeView.parent)
                            // console.log("Swipe parent.y: ", swipeView.parent.y)
                            // console.log("firstPage height: ", firstPage.height)
                            // console.log("firstPage width: ", firstPage.width)
                            // console.log("firstPage x: ", firstPage.x)
                            // console.log("firstPage y: ", firstPage.y)
                            // console.log("firstPage parent: ", firstPage.parent)
                            // console.log("firstPage parent.y: ", firstPage.parent.y)
                        }
                    }

                    InterractiveImage {
                        width: 200
                        height: 150
                        image.source: "qrc:///resources/images/Icons/Espresso_Intenso.png"
                        text.text: qsTr("Espresso Intenso")
                        text.color: "#f0f0f0"
                        text.height: 25
                        onClicked: {
                            header_text.text = text.text
                        }
                    }

                    InterractiveImage {
                        width: 200
                        height: 150
                        image.source: "qrc:///resources/images/Icons/Espresso_Lungo.png"
                        text.text: qsTr("Espresso Lungo")
                        text.color: "#f0f0f0"
                        text.height: 25
                        onClicked: {
                            header_text.text = text.text
                        }
                    }
                }
            }
            
            Page {
                id: secondPage
                background: null
                height: 150
                anchors {
                    top: parent.top
                    topMargin: (100 + head.height)
                }
                contentItem: Row {
                    height: parent.height
                    anchors {
                        left: parent.left
                        right: parent.right
                    }

                    InterractiveImage {
                        width: 200
                        height: 150
                        image.source: "qrc:///resources/images/Icons/Espresso_Macchiato.png"
                        text.text: qsTr("Espresso Macchiato")
                        text.color: "#f0f0f0"
                        text.height: 25
                        onClicked: {
                            header_text.text = text.text
                        }
                    }

                    InterractiveImage {
                        width: 200
                        height: 150
                        image.source: "qrc:///resources/images/Icons/Cappuccino.png"
                        text.text: qsTr("Cappuccino")
                        text.color: "#f0f0f0"
                        text.height: 25
                        onClicked: {
                            header_text.text = text.text
                        }
                    }
                    
                    InterractiveImage {
                        width: 200
                        height: 150
                        image.source: "qrc:///resources/images/Icons/Macchiato.png"
                        text.text: qsTr("Macchiato")
                        text.color: "#f0f0f0"
                        text.height: 25
                        onClicked: {
                            header_text.text = text.text
                        }
                    }

                    InterractiveImage {
                        width: 200
                        height: 150
                        image.source: "qrc:///resources/images/Icons/Flat_White.png"
                        text.text: qsTr("Flat White")
                        text.color: "#f0f0f0"
                        text.height: 25
                        onClicked: {
                            header_text.text = text.text
                        }
                    }
                }
            }

            Page {
                id: thirdPage
                background: null
                height: 150
                anchors {
                    top: parent.top
                    topMargin: (100 + head.height)
                }
                contentItem: Row {
                    height: parent.height
                    anchors {
                        left: parent.left
                        right: parent.right
                    }

                    InterractiveImage {
                        width: 200
                        height: 150
                        image.source: "qrc:///resources/images/Icons/CoffeeLong.png"
                        text.text: qsTr("Coffee Long")
                        text.color: "#f0f0f0"
                        text.height: 25
                        onClicked: {
                            header_text.text = text.text
                        }
                    }

                    InterractiveImage {
                        width: 200
                        height: 150
                        image.source: "qrc:///resources/images/Icons/Americano.png"
                        text.text: qsTr("Americano")
                        text.color: "#f0f0f0"
                        text.height: 25
                        onClicked: {
                            header_text.text = text.text
                        }
                    }

                    InterractiveImage {
                        width: 200
                        height: 150
                        image.source: "qrc:///resources/images/Icons/CaffeCrema.png"
                        text.text: qsTr("Caffe Crema")
                        text.color: "#f0f0f0"
                        text.height: 25
                        onClicked: {
                            header_text.text = text.text
                        }
                    }

                    InterractiveImage {
                        width: 200
                        height: 150
                        image.source: "qrc:///resources/images/Icons/favorites.png"
                        image.sourceSize.width: 100
                        image.sourceSize.height: 100
                        text.text: qsTr("Favorites")
                        text.color: "#f0f0f0"
                        text.height: 25
                        onClicked: {
                            header_text.text = text.text
                        }
                    }
                }
            }

            Page {
                id: fourthPage
                background: null
                height: 150
                anchors {
                    top: parent.top
                    topMargin: (100 + head.height)
                }
                contentItem: Row {
                    height: parent.height
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    InterractiveImage {
                        width: 200
                        height: 150
                        image.source: "qrc:///resources/images/Icons/settings.png"
                        image.sourceSize.width: 100
                        image.sourceSize.height: 100
                        text.text: qsTr("Settings")
                        text.color: "#f0f0f0"
                        text.height: 25
                        onClicked: {
                            header_text.text = text.text
                        }
                    }
                }
            }
        }

        ToolBar {
            id: footer
            background: null
            height: 50
            anchors {
                left: parent.left
                right: parent.right
            }
            RowLayout {
                anchors.fill: parent
                Label {
                    id: footer_text
                    text: "25C cloudy"
                    elide: Label.ElideRight
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                    color: "#f0f0f0"
                }
            }
        }
    }
}
