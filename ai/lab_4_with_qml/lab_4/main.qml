import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window
{
    width: 640
    height: 480
    visible: true
    title: qsTr("Лаба4 (Виноградов Алексей)")

    property var questions:
    [
        {
            "question": "К какой группе продуктов питания относится данный продукт?",
            "answers": [
                "Мясо и мясопродукты",
                "Рыба и рыбопродукты",
                "Яйца",
                "Молоко и молочные продукты",
                "Хлеб и хлебобулочные изделия, крупы, макаронные изделия"
            ],
            "value_of_answers": [
                "Говядина",
                "Лосось",
                "Куриное яйцо",
                "Творог",
                "Ржаной хлеб"
            ]
        },
        {
            "question": "Продукт является натуральным или содержит добавки?",
            "answers": [
                "Натуральный",
                "С добавками"
            ],
            "value_of_answers": [
                "Свежие овощи",
                "Консервированные продукты"
            ]
        },
        {
            "question": "Какой способ термической обработки применён к продукту?",
            "answers": [
                "Сырая",
                "Приготовленная"
            ],
            "value_of_answers": [
                "Фрукты",
                "Рыба на гриле"
            ]
        }
    ]

    property int    currentQuestionIndex:   0
    property int    selectedAnswerIndex:    -1
    property var    selectedAnswers:        []
    property string mostFrequentElement:    ""
    property bool   isSurveyCompleted:      false

    Column
    {
        anchors.centerIn: parent
        spacing: 20

        Text
        {
            id: questionText
            text: isSurveyCompleted ? "Опрос завершен" : questions[currentQuestionIndex].question
            font.pixelSize: 24
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Column
        {
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter
            visible: !isSurveyCompleted

            Repeater
            {
                model: questions[currentQuestionIndex].answers.length
                Row
                {
                    spacing: 10
                    RadioButton
                    {
                        id: radioButton
                        checked: index === selectedAnswerIndex
                        onClicked: selectedAnswerIndex = index
                    }

                    Text
                    {
                        text: questions[currentQuestionIndex].answers[index]
                        font.pixelSize: 18
                        anchors.verticalCenter: radioButton.verticalCenter
                    }
                }
            }
        }

        Row {
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter

            Button
            {
                text: "Начать заново"
                width: 100
                height: 50

                onClicked:
                {
                    currentQuestionIndex = 0
                    selectedAnswerIndex = -1
                    selectedAnswers = []
                    mostFrequentElement = ""
                    isSurveyCompleted = false
                }
            }

            Button
            {
                text: "Назад"
                width: 100
                height: 50
                onClicked:
                {
                    if (currentQuestionIndex > 0)
                    {
                        selectedAnswers.pop()
                        currentQuestionIndex--
                        selectedAnswerIndex = -1
                    }
                    else
                    {
                        console.log("Это первый вопрос")
                    }
                }
            }

            Button {
                text: "Далее"
                width: 100
                height: 50
                onClicked:
                {
                    if (isSurveyCompleted)
                    {
                        console.log("Опрос завершен")
                    }
                    else
                    {
                        if (selectedAnswerIndex !== -1)
                        {
                            var selectedValue = questions[currentQuestionIndex].value_of_answers[selectedAnswerIndex]
                            selectedAnswers.push(selectedValue)
                        }

                        if (currentQuestionIndex < questions.length - 1)
                        {
                            currentQuestionIndex++
                            selectedAnswerIndex = -1
                        }
                        else
                        {
                            // Анализ массива выбранных ответов
                            mostFrequentElement = findMostFrequent(selectedAnswers)
                            console.log("Ваш выбор:", mostFrequentElement)
                            console.log("Все выбранные ответы:", selectedAnswers)
                            isSurveyCompleted = true
                        }
                    }
                }
            }

            Button
            {
                text: "Выход"
                width: 100
                height: 50
                onClicked: Qt.quit()
            }
        }

        // Текст для отображения самого частого элемента
        Text
        {
            id: resultText
            text: mostFrequentElement ? "Ваш выбор: " + mostFrequentElement : ""
            font.pixelSize: 18
            anchors.horizontalCenter: parent.horizontalCenter
            visible: isSurveyCompleted
        }
    }

    function findMostFrequent(array)
    {
        var counts = {}
        var maxCount = 0
        var mostFrequentElement = null

        for (var i = 0; i < array.length; i++)
        {
            var element = array[i]
            if (counts[element])
            {
                counts[element]++
            }
            else
            {
                counts[element] = 1
            }

            if (counts[element] > maxCount)
            {
                maxCount = counts[element]
                mostFrequentElement = element
            }
        }

        return mostFrequentElement
    }
}
