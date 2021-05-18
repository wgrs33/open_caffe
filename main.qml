import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
//import com.company.ttext 1.0

ApplicationWindow {
    width: 800
    height: 480
    visible: true
    title: qsTr("Coffee Machine")
    background: Image {
        source: "qrc:///resources/images/background2.png"
    }

//    TestText {
//        id: label
//    }
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

    Page {
        anchors.fill: parent
        background: null
        header: ToolBar {
            id: header
            background: null
            RowLayout {
                anchors.fill: parent
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

        contentItem: SwipeView {
            id: swipeView
            currentIndex: 0
            anchors {
                top: header.bottom
                left: parent.left
                right: parent.right
                bottom: footer.top
            }
            Page {
                id: firstPage
                background: null
                contentItem: RowLayout {
                    ColumnLayout {
                        width: 200
                        height: 200
                        Layout.alignment: Qt.AlignVCenter
                        Image {
                            fillMode: Image.PreserveAspectFit
                            source: "qrc:///resources/images/Icons/Espresso.png"
                            sourceSize.width: parent.width
                        }
                        Text {
                            id: espresso
                            height: 35
                            text: qsTr("Espresso")
                            color: "#f0f0f0"
                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: 25
                            horizontalAlignment: Text.AlignHCenter
                        }
                        MouseArea {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            onClicked: {
                                header_text.text = espresso.text
                            }
                        }
                    }

                    ColumnLayout {
                        width: 200
                        Layout.alignment: Qt.AlignVCenter
                        Image {
                            fillMode: Image.PreserveAspectFit
                            source: "qrc:///resources/images/Icons/Espresso_Intenso.png"
                            sourceSize.width: parent.width
                        }
                        Text {
                            text: qsTr("Espresso Intenso")
                            color: "#f0f0f0"
                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: 25
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }

                    ColumnLayout {
                        width: 200
                        Layout.alignment: Qt.AlignVCenter
                        Image {
                            fillMode: Image.PreserveAspectFit
                            source: "qrc:///resources/images/Icons/Espresso_Lungo.png"
                            sourceSize.width: parent.width
                        }
                        Text {
                            height: 35
                            text: qsTr("Espresso Lungo")
                            color: "#f0f0f0"
                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: 25
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                    
                    ColumnLayout {
                        width: 200
                        Layout.alignment: Qt.AlignVCenter
                        Image {
                            fillMode: Image.PreserveAspectFit
                            source: "qrc:///resources/images/Icons/Espresso_Macchiato.png"
                            sourceSize.width: parent.width
                        }
                        Text {
                            height: 35
                            text: qsTr("Espresso Macchiato")
                            color: "#f0f0f0"
                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: 25
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                }
            }
            
            Page {
                id: secondPage
                background: null
                contentItem: RowLayout {
                    ColumnLayout {
                        width: 200
                        Layout.alignment: Qt.AlignVCenter
                        Image {
                            fillMode: Image.PreserveAspectFit
                            source: "qrc:///resources/images/Icons/Americano.png"
                            sourceSize.width: parent.width
                        }
                        Text {
                            height: 35
                            text: qsTr("Americano")
                            color: "#f0f0f0"
                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: 25
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }

                    ColumnLayout {
                        width: 200
                        Layout.alignment: Qt.AlignVCenter
                        Image {
                            fillMode: Image.PreserveAspectFit
                            source: "qrc:///resources/images/Icons/CaffeCrema.png"
                            sourceSize.width: parent.width
                        }
                        Text {
                            text: qsTr("Caffe Crema")
                            color: "#f0f0f0"
                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: 25
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }

                    ColumnLayout {
                        width: 200
                        Layout.alignment: Qt.AlignVCenter
                        Image {
                            fillMode: Image.PreserveAspectFit
                            source: "qrc:///resources/images/Icons/CoffeeLong.png"
                            sourceSize.width: parent.width
                        }
                        Text {
                            height: 35
                            text: qsTr("Coffee Long")
                            color: "#f0f0f0"
                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: 25
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                    
                    ColumnLayout {
                        width: 200
                        Layout.alignment: Qt.AlignVCenter
                        Image {
                            fillMode: Image.PreserveAspectFit
                            source: "qrc:///resources/images/Icons/Cappuccino.png"
                            sourceSize.width: parent.width
                        }
                        Text {
                            height: 35
                            text: qsTr("Cappuccino")
                            color: "#f0f0f0"
                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: 25
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                }
            }

            Page {
                id: thirdPage
                background: null
                contentItem: RowLayout {
                    ColumnLayout {
                        width: 200
                        Layout.alignment: Qt.AlignVCenter
                        Image {
                            fillMode: Image.PreserveAspectFit
                            source: "qrc:///resources/images/Icons/Flat_White.png"
                            sourceSize.width: parent.width
                        }
                        Text {
                            height: 35
                            text: qsTr("Flat White")
                            color: "#f0f0f0"
                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: 25
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }

                    ColumnLayout {
                        width: 200
                        Layout.alignment: Qt.AlignVCenter
                        Image {
                            fillMode: Image.PreserveAspectFit
                            source: "qrc:///resources/images/Icons/Ristretto.png"
                            sourceSize.width: parent.width
                        }
                        Text {
                            text: qsTr("Ristretto")
                            color: "#f0f0f0"
                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: 25
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }

                    ColumnLayout {
                        width: 200
                        Layout.alignment: Qt.AlignVCenter
                        Image {
                            fillMode: Image.PreserveAspectFit
                            source: "qrc:///resources/images/Icons/Macchiato.png"
                            sourceSize.width: parent.width
                        }
                        Text {
                            height: 35
                            text: qsTr("Macchiato")
                            color: "#f0f0f0"
                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: 25
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                    
                    ColumnLayout {
                        width: 200
                        Layout.alignment: Qt.AlignVCenter
                        Image {
                            fillMode: Image.PreserveAspectFit
                            source: "qrc:///resources/images/Icons/favorites.png"
                            sourceSize.width: parent.width - 75
                            horizontalAlignment: Qt.AlignHCenter
                            // sourceSize.height: parent.height
                        }
                        Text {
                            height: 35
                            text: qsTr("Favorite")
                            color: "#f0f0f0"
                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: 25
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                }
            }

            Page {
                id: fourthPage
                background: null
                contentItem: RowLayout {
                    ColumnLayout {
                        width: 200
                        Layout.alignment: Qt.AlignVCenter
                        Image {
                            fillMode: Image.PreserveAspectFit
                            source: "qrc:///resources/images/Icons/settings.png"
                            sourceSize.width: parent.width - 75
                            horizontalAlignment: Qt.AlignHCenter
                        }
                        Text {
                            height: 35
                            text: qsTr("Settings")
                            color: "#f0f0f0"
                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: 25
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                }
            }
        }

        footer:  ToolBar {
            id: footer
            background: null
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
