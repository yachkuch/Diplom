import QtQuick 2.15
import QtQuick.Controls 6.3

Item {
    id: item1
    RoundButton {
        id: roundButton
        visible: false
        text: "Наличие информации"
        anchors.fill: parent
        icon.cache: true
        font.pointSize: 17
        autoRepeatDelay: 299
        autoRepeat: false
        icon.color: "#c92222"
        antialiasing: true
        anchors.leftMargin: 77
        anchors.rightMargin: 96
        background: Color{
            color:"#c92222"
        }

        Connections {
            target: roundButton
            onClicked: item1.state = ""
        }
    }

}
