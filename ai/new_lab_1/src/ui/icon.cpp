#include "icon.h"

Icon::Icon(QString path) : QIcon(path), path(path)      {}

Icon::Icon(const char* path) : QIcon(QString::fromStdString(std::string(path))), 
path(QString::fromStdString(std::string(path))) {}

Icon::~Icon()                                           {}