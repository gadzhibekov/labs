#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>
#include <QString>

class Processor : public QObject
{
    Q_OBJECT

public:
    explicit Processor(QObject* parent);

    Q_INVOKABLE QString q_encrypt(QString data);
    Q_INVOKABLE QString q_decrypt(QString data);
    Q_INVOKABLE void    to_clipboard(QString data);
    Q_INVOKABLE QString from_clipboard();
    Q_INVOKABLE QString get_random_key();
};

#endif // PROCESSOR_H