#include "db.h"

#include <iostream>
#include <sqlite3.h>
#include <iomanip>

const char* insertDataSQL = 
                            "INSERT INTO products (name, price, availability, is_hide) VALUES "
                            "('AMD Ryzen 7 3700X', 25000, 'да', 1),"
                            "('NVidia RTX 2060 Super', 30000, 'да', 1),"
                            "('Intel Core i7 9700KF', 30000, 'нет', 1),"
                            "('NVidia RTX 2060 Super', 30000, 'нет', 1),"
                            "('Intel Core i7 9700KF', 30000, 'да', 1),"
                            "('Kingston Fury 16GB DDR4', 8000, 'нет', 1),"
                            "('Samsung 970 EVO Plus 1TB', 12000, 'да', 1),"
                            "('Seagate Barracuda 2TB', 5000, 'да', 1),"
                            "('ASUS ROG Strix B550-F', 15000, 'да', 1),"
                            "('be quiet! Dark Rock 4', 6000, 'нет', 1),"
                            "('Corsair RM750x', 11000, 'нет', 1),"
                            "('NZXT H510', 7000, 'нет', 1),"
                            "('AOC 24G2U', 18000, 'да', 1),"
                            "('AMD Ryzen 5 5600X', 22000, 'да', 1),"
                            "('NVidia RTX 3060 Ti', 45000, 'да', 0),"
                            "('AMD RX 5700 XT', 30000, 'нет', 0);";

std::vector<table_element> get_products_table() 
{
    std::vector<table_element> result;

    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;

    rc = sqlite3_open("data.db", &db);
    
    if (rc) 
    {
        std::cerr << "Ошибка открытия базы данных: " << sqlite3_errmsg(db) << std::endl;
    }

    const char* selectSQL = "SELECT * FROM products;";
    
    rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) 
    {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) 
    {
        result.push_back({std::to_string(sqlite3_column_int(stmt, 0)), 
                          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)), 
                          std::to_string(sqlite3_column_int(stmt, 2)), 
                          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3))});
    }

    if (rc != SQLITE_DONE) 
    {
        std::cerr << "Ошибка при выборке данных: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return result;
}

std::vector<table_element> get_visible_products_table() 
{
    std::vector<table_element> result;

    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;

    rc = sqlite3_open("data.db", &db);
    
    if (rc) 
    {
        std::cerr << "Ошибка открытия базы данных: " << sqlite3_errmsg(db) << std::endl;
    }

    const char* selectSQL = "SELECT * FROM products WHERE is_hide = 0;";
    
    rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) 
    {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) 
    {
        result.push_back({std::to_string(sqlite3_column_int(stmt, 0)), 
                          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)), 
                          std::to_string(sqlite3_column_int(stmt, 2)), 
                          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3))});
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return result;
}

[[nodiscard]] int create_db()
{
    sqlite3* db;
    char* errorMessage = nullptr;
    int rc;

    rc = sqlite3_open("data.db", &db);
    
    if (rc) 
    {
        std::cerr << "Ошибка открытия базы данных: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    } 
    else 
    {
        std::cout << "База данных успешно открыта!" << std::endl;
    }

    const char* createTableSQL = 
        "CREATE TABLE IF NOT EXISTS products ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "price INTEGER NOT NULL,"
        "availability TEXT NOT NULL,"
        "is_hide INTEGER NOT NULL"
        ");";

    rc = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errorMessage);
    
    if (rc != SQLITE_OK) 
    {
        std::cerr << "Ошибка создания таблицы: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        sqlite3_close(db);
        return 1;
    } 
    else 
    {
        std::cout << "Таблица успешно создана!" << std::endl;
    }

    rc = sqlite3_exec(db, insertDataSQL, nullptr, nullptr, &errorMessage);
    
    if (rc != SQLITE_OK) 
    {
        std::cerr << "Ошибка вставки данных: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        sqlite3_close(db);
        return 1;
    } 
    else 
    {
        std::cout << "Данные успешно добавлены!" << std::endl;
    }

    sqlite3_close(db);
    std::cout << "База данных data.db успешно создана!" << std::endl;

    return 0;
}

// int main()
// {
//     if (create_db() == 1)
//     {
//         return 1;
//     }

//     // get_products_table();

//     return 0;
// }