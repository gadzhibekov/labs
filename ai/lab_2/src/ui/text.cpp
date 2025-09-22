#include "text.h"

#include <QPixmap>

Text::Text(QString text, QWidget* parent) : QLabel(parent)
{
    set_text(text);
}

Text::~Text()
{
    ;
}

void Text::set_text(QString text)
{
    this->setText(text);
    this->text = text;
}

QString Text::get_text()
{
    return text;
}

void Text::set_text_size(int size)
{
    QFont font = this->font();
    font.setPointSize(size); 
    this->setFont(font);
}

void Text::set_icon(const QString& path, int size)
{
    QPixmap pixmap(path);
    this->setPixmap(pixmap);
    this->setFixedSize(pixmap.size());
    
    QPixmap scaledPixmap = pixmap.scaled(size, size, Qt::KeepAspectRatio);
    this->setPixmap(scaledPixmap);
    this->resize(scaledPixmap.size());
}