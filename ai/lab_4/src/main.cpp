#include "../data/data.h"
#include "item.h"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>


#include <QGuiApplication>
#include <QQmlApplicationEngine>


string most_frequent_element(const SVector& vec)
{
    std::unordered_map<std::string, int> count_map;

    for (const auto& str : vec)
    {
        count_map[str]++;
    }

    string most_frequent;
    int max_count = 0;
    
    for (const auto& pair : count_map) 
    {
        if (pair.second > max_count) 
        {
            max_count = pair.second;
            most_frequent = pair.first;
        }
    }

    return most_frequent;
}

void fill(std::vector<Item>& items)
{
    for (int i = 0; i < items_vector.size(); ++i)
    {
        items.push_back(Item(
            items_vector[i].second.first,
            items_vector[i].second.second,
            items_vector[i].first,
            "",
            (size_t) i + 1
        ));
    }
}

int main(int argc, char** argv) 
{
    // std::vector<Item> items;

    // fill(items);

    // SVector languages;

    // for (int i = 0; i < items.size(); ++i)
    // {
    //     std::cout << items[i].get_question() << std::endl;
    //     int _r, _cin;

    //     for (int j = 0; j < items[i].get_answers().size(); ++j)
    //     {
    //         std::cout << j + 1 << ") " << items[i].get_answers()[j] << std::endl;
    //         _r = j + 1;
    //     }

    //     std::cout << "Выберите от 1 до " << _r << ": ";
    //     std::cin >> _cin;

    //     if (1 <= _cin && _cin <= _r)
    //     {
    //         std::cout << items[i].get_value_of_answers()[_cin - 1] << std::endl;
    //         languages.push_back(items[i].get_value_of_answers()[_cin - 1]);
    //     }

    //     std::cout << "\n\n";
    // }

    // std::cout << "Ваш выбор: " << most_frequent_element(languages) << std::endl;


    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();


}