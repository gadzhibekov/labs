#include "processor.h"
#include "cryptographer.h"

#include <QGuiApplication>
#include <QClipboard>

#include <iostream>
#include <cstdlib>

Processor::Processor(QObject* parent) : QObject(parent) {}

QString Processor::q_encrypt(QString data)
{
    std::string result = "";
    std::vector<double> encrypted = Cryptographer::encrypt(data.toStdString());

    for (double val : encrypted) 
    {
        result += std::to_string(val);
        result += " ";
    }

    return QString::fromStdString(result);
}

QString Processor::q_decrypt(QString data)
{
    std::string std_data = data.toStdString();
    std::string current_str = "";
    std::vector<double> data_set;

    for (int i = 0; i < std_data.size(); ++i)
    {
        if (std_data[i] == ' ')
        {
            try 
            {
                data_set.push_back(std::stod(current_str));
                current_str = "";
            } 
            catch (...) 
            {
                std::cerr << "Попытка рашифровать незашифрованные данные" << std::endl;
            }
        }
        else
        {
            current_str += std_data[i];
        }
    }

    return QString::fromStdString(Cryptographer::decrypt(data_set));
}

void Processor::to_clipboard(QString data)
{
	QGuiApplication::clipboard()->setText(data);
}

QString Processor::from_clipboard()
{
	return QGuiApplication::clipboard()->text();
}

QString Processor::get_random_key()
{   
    int result = std::rand() % 100 + 1;

    Cryptographer::key = result;

    return QString::number(result);
}