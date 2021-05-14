import QtQuick 2.12
import QtQuick.Controls 2.12
import com.company.ttext 1.0

ApplicationWindow {
    width: 800
    height: 480
    visible: true
    title: qsTr("Coffee Machine")
    background: Image {
        source: "qrc:///resources/images/background2.png"
    }

    TestText {
        id: label
    }

    Text {
        anchors.centerIn: parent
        id: test
        text: label.text
        font.family: "Courier"
        font.pointSize: 16
        color: "white"
    }
}
