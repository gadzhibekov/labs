#include "processor.h"
#include "cryptographer.h"

#include <QGuiApplication>
#include <QClipboard>

#include <iostream>
#include <random>
#include <string_view>

Processor::Processor(QObject* parent) : QObject(parent) {}

QString Processor::q_encrypt(QString data)
{
    return QString::fromStdString(Cryptographer::encrypt(data.toStdString()));
}

QString Processor::q_decrypt(QString data)
{
    return QString::fromStdString(Cryptographer::decrypt(data.toStdString()));
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
    static constexpr std::string_view kChars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

    thread_local std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<std::size_t> dist(0, kChars.size() - 1);
    std::string s;
    s.reserve(8);

    for (std::size_t i = 0; i < 8; ++i) 
    {
        s.push_back(kChars[dist(gen)]);
    }

    Cryptographer::key = s;

    return QString::fromStdString(s);
}