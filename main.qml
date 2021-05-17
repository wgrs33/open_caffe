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
            currentIndex: 1
            anchors {
                top: header.bottom
                left: parent.left
                leftMargin: 250
                right: parent.right
                rightMargin: 250
                bottom: footer.top
            }
            Page {
                id: firstPage
                background: null
                contentItem: Text {
                    text: qsTr("firstPage")
                    color: "#f0f0f0"
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                }
            }
            Page {
                id: secondPage
                background: null
                contentItem: Text {
                    text: qsTr("secondPage")
                    color: "#f0f0f0"
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                }
            }
            Page {
                id: thirdPage
                background: null
                contentItem: Text {
                    text: qsTr("thirdPage")
                    color: "#f0f0f0"
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                }
            }
            Page {
                id: fourthPage
                background: null
                contentItem: Text {
                    text: qsTr("fourthPage")
                    color: "#f0f0f0"
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
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
