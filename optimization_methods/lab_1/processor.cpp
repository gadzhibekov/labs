#include "processor.h"
#include "cryptographer.h"

#include <QGuiApplication>
#include <QClipboard>

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
    return (QString)"";
}

void Processor::to_clipboard(QString data)
{
	QGuiApplication::clipboard()->setText(data);
}

QString Processor::from_clipboard()
{
	return QGuiApplication::clipboard()->text();
}