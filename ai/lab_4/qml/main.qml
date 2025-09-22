import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 300
    title: "Простая QML программа"

    Column {
        spacing: 20
        anchors.centerIn: parent

        Text {
            id: displayText
            text: "Добро пожаловать!"
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
        }

        Button {
            text: "Нажми меня"
            onClicked: {
                displayText.text = "Кнопка нажата!"
            }
        }
    }
}
