import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0

ApplicationWindow 
{
    id: rootWindow
    width: 1200
    height: 770
    minimumWidth: 1200
    minimumHeight: 770
    maximumWidth: 1200
    maximumHeight: 770
    visible: true
    title: "Лаботароная работа 1"
    flags: Qt.Tool

    property int drag_start_x:  0
    property int drag_start_y:  0
    property string result:     ""

    Button 
    {
        id: encrypt_btn
        width: 200
        height: 50
        x: 990
        y: 710
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
        y: 710
        text: "Расшифровать"
        visible: false
        
        onClicked: 
        {
            result = process_helper.q_decrypt(input.text)
            output.text = result
        }
    }

    Button 
    {
        id: encrypt_btn_switch
        width: 200
        height: 50
        x: 395
        y: 10
        text: "Режим шифрование"
        
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
        y: 10
        text: "Режим расшифрование"
        
        onClicked: 
        {
            encrypt_btn.visible = false
            decrypt_btn.visible = true
        }
    }

    Button 
    {
        id: copy_btn
        width: 200
        height: 50
        x: 780
        y: 710
        text: "Скопировать результат"
        
        onClicked: 
        {
            process_helper.to_clipboard(output.text)
            output.text = ""
        }
    }

    Button 
    {
        id: get_new_random_key_btn
        width: 200
        height: 50
        x: 570
        y: 710
        text: "Сгенерировать новый ключ"
        
        onClicked: 
        {
            key.text = "Ключ шифрования " + process_helper.get_random_key()
            output.text = ""
            input.text = ""
        }
    }
    
    Text
    {
        id: key
        text: "Ключ шифрования " + process_helper.get_random_key()
        height: 50
        x: 10
        y: 720
        font.pixelSize: 20
    }

    TextEdit 
    {
        id: input
        color: "black"
        width: 585
        height: 630
        x: 10
        y: 70
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
        width: 585
        height: 630
        x: 605
        y: 70
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