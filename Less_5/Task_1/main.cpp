#include <iostream>
#include <pqxx/pqxx>
#include "SQL.h"

int main() {

    try {
        SQL dd;

        pqxx::connection c(
                "host=localhost "
                "port=5432 "
                "dbname=test2 "
                "user=userdb2 "
                "password=100"
        );
        std::cout << "Connection OK!" << std::endl;

        pqxx::work tx0{ c };
        dd.createTables(tx0);
        c.prepare ("insert_client", "INSERT INTO client(first_name, last_name, email) VALUES ($1, $2, $3)" );
        c.prepare ("insert_phone", "INSERT INTO phone(client_id, phone) VALUES ($1, $2)" );

        int key;
        while (true) {
            pqxx::work tx{ c };
            std::cout << std::endl;
            std::cout << "Выберите действие для работы с базой данных: " << std::endl;
            std::cout << "1 - Добавить нового пользователя" << std::endl;
            std::cout << "2 - Добавить номер телефона" << std::endl;
            std::cout << "3 - Редактирование данных" << std::endl;
            std::cout << "4 - Удаление номера телефона" << std::endl;
            std::cout << "5 - Удаление пользователя" << std::endl;
            std::cout << "6 - Поиск пользователя" << std::endl;
            std::cout << "7 - Выход" << std::endl;


            std::cin >> key;

            switch (key) {
                case 1:
                    dd.addNewClient(tx);
                    continue;
                case 2:
                    dd.addPhoneNumber(tx);
                    continue;
                case 3:
                    dd.changeClientData(tx);
                    continue;
                case 4:
                    dd.deleteClientPhone(tx);
                    continue;
                case 5:
                    dd.deleteClient(tx);
                    continue;
                case 6:
                    dd.searchClient(tx);
                    break;
                case 7:
                    return 0;
                default:
                    std::cout << "Некорректный ввод " << std::endl;
                    break;
            }
        }
    } catch (pqxx::sql_error e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
