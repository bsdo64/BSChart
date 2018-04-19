import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Window 2.2

Window {
    id: window
    visible: true
    minimumWidth: 640
    height: 480
    title: qsTr("Flat Style")

    RowLayout {
        Button {
            id: button1
            text: "Ok"

        }
        Button {
            id: button2
            text: "안녕하세요"
            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 200
                color: button2.down ? "#d6d6d6" : "#f6f6f6"
                border.color: "#26282a"
                border.width: 1
                radius: 4
            }

        }
    }
}
