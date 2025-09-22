#pragma once

#ifndef ICON_H
#define ICON_H

#include <QIcon>
#include <QString>

struct Icon : QIcon
{
    Icon() {}
    Icon(QString path);
    Icon(const char* path);
    ~Icon();

    QString get_path() { return this->path; }

private:
    QString path;
};

#endif // ICON_H