#ifndef DB_H
#define DB_H

#include <vector>
#include <string>

struct table_element
{
    std::string id, name, price, availability;
};

std::vector<table_element> get_products_table();
std::vector<table_element> get_visible_products_table();

#endif // DB_H