import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0

ApplicationWindow 
{
    id: rootWindow
    width: 1200
    height: 800
    visible: true
    flags: Qt.FramelessWindowHint | Qt.Tool

    property int drag_start_x:  0
    property int drag_start_y:  0
    property string result:     ""

    Button 
    {
        id: encrypt_btn
        width: 200
        height: 50
        x: 990
        y: 740
        text: "Шифровать"
        visible: true
        
        onClicked: 
        {
            result = process_helper.q_encrypt(input.text)
            output.text = result
        }
    }

    Button 
    {
        id: decrypt_btn
        width: 200
        height: 50
        x: 990
        y: 740
        text: "Расшифровать"
        visible: false
        
        onClicked: 
        {
            console.log("Расшифровать")
        }
    }

    Button 
    {
        id: encrypt_btn_switch
        width: 200
        height: 50
        x: 395
        y: 40
        text: "Шифровать"
        
        onClicked: 
        {
            encrypt_btn.visible = true
            decrypt_btn.visible = false
        }
    }
    
    Button 
    {
        id: decrypt_btn_switch
        width: 200
        height: 50
        x: 602
        y: 40
        text: "Расшифровать"
        
        onClicked: 
        {
            encrypt_btn.visible = false
            decrypt_btn.visible = true
        }
    }

    Button 
    {
        id: exit_btn
        width: 25
        height: 25
        x: 1170
        y: 5
        text: "x"
        font.pixelSize: 20
        
        onClicked: 
        {
            console.log("Выход")
        }

        Rectangle 
        {
            anchors.fill: parent
            color: "black"
            z: -1
        }
    }

    Button 
    {
        id: copy_btn
        width: 200
        height: 50
        x: 780
        y: 740
        text: "Скопировать результат"
        
        onClicked: 
        {
            process_helper.to_clipboard(output.text)
        }
    }

    Text
    {
        id: title
        text: "Лабораторная работа 1"
        height: 25
        x: 500
        y: 0
        font.pixelSize: 20
    }
    
    Text
    {
        id: key
        text: "Ключ шифрования 42"
        height: 50
        x: 10
        y: 750
        font.pixelSize: 20
    }

    TextEdit 
    {
        id: input
        color: "black"
        width: 585
        height: 630
        x: 10
        y: 100
        wrapMode: TextEdit.Wrap
        selectByMouse: true
        font.pixelSize: 20
        
        Rectangle 
        {
            anchors.fill: parent
            color: "gray"
            z: -1
        }
    }

    TextEdit 
    {
        id: output
        color: "black"
        text: "Здесь будет результат"
        width: 585
        height: 630
        x: 605
        y: 100
        wrapMode: TextEdit.Wrap
        selectByMouse: true
        font.pixelSize: 20
        readOnly: true
        
        Rectangle 
        {
            anchors.fill: parent
            color: "gray"
            z: -1
        }
    }
}