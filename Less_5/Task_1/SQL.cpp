//
// Created by developer on 22.08.2024.
//

#include "SQL.h"
#include <iostream>

void SQL::createTables(pqxx::work &tx) {
    tx.exec("CREATE TABLE IF NOT EXISTS client ("
            "client_id SERIAL PRIMARY KEY, "
            "first_name VARCHAR(80) NOT NULL, "
            "last_name VARCHAR(80) NOT NULL, "
            "email VARCHAR(80)); "
            "CREATE TABLE IF NOT EXISTS phone ("
            "phone_id SERIAL PRIMARY KEY, "
            "client_id INTEGER NOT NULL references client(client_id), "
            "phone VARCHAR(40));");
    tx.commit();
}

void SQL::addNewClient(pqxx::work &tx) {
    std::string firstName, lastName, email;
    std::cout << "Введите имя: " << std::endl;
    std::cin >> firstName;
    std::cout << "Введите фамилию: " << std::endl;
    std::cin >> lastName;
    std::cout << "Введите почту: " << std::endl;
    std::cin >> email;
    tx.exec_prepared("insert_client", firstName, lastName, email);
    tx.commit();
}

int SQL::getIdByName(pqxx::work &tx) {
    std::string firstName, lastName;
    std::cout << "Введите имя пользователя: " << std::endl;
    std::cin >> firstName;
    std::cout << "Введите фамилию пользователя: " << std::endl;
    std::cin >> lastName;

    auto count = tx.query_value <int> ("SELECT COUNT(*) FROM client WHERE "
                                       "first_name = '" + tx.esc(firstName) + "' AND "
                                                                              "last_name = '" + tx.esc(lastName) + "'" );

    if (count != 0) {
        auto queryResult = tx.query <int> (
                "SELECT client_id FROM client WHERE "
                "first_name = '" + tx.esc(firstName) + "' AND "
                                                       "last_name = '" + tx.esc(lastName) + "'" );
        for (auto [id] : queryResult)
            return id;
    }
    else {
        std::cout << "В базе данных нет клиента с такими данными" << std::endl;
        return -1;
    }
}

void SQL::addPhoneNumber(pqxx::work &tx) {
    std::string phoneNumber;
    int id = getIdByName(tx);
    if (id != -1) {
        std::cout << "Введите номер телефона: " << std::endl;
        std::cin >> phoneNumber;

        tx.exec_prepared("insert_phone", id, phoneNumber);
        tx.commit();
    } else return;
}

void SQL::getDataById(pqxx::work& tx, int id) {
    std::string sid = std::to_string(id);

    auto clientData = tx.query<std::string, std::string, std::string>(
            "SELECT first_name, last_name, email FROM client WHERE client_id = '" + sid + "';");


    for (auto[fn, ln, em] : clientData) {
        std::cout << fn << " " << ln << " " << em << std::endl;
    }
    auto clientPhones = tx.query<std::string>(
            "SELECT phone FROM phone WHERE client_id = '" + sid + "'");
    for (auto[ph] : clientPhones) {
        std::cout << ph << std::endl;
    }
    std::cout << std::endl;
}

void SQL::changeClientData(pqxx::work& tx) {
    std::string newFirstName, newLastName, newEmail, newPhone;
    int id = getIdByName(tx);
    if (id != -1) {
        std::string sid = std::to_string(id);
        getDataById(tx, id);

        int k;
        std::cout << "Какие данные хотите изменить?" << std::endl;
        std::cout << "1) Имя" << std::endl;
        std::cout << "2) Фамилия" << std::endl;
        std::cout << "3) Почта" << std::endl;
        std::cout << "4) Номер телефона" << std::endl;
        std::cin >> k;
        switch (k) {
            case 1:
                std::cout << "Введите имя: ";
                std::cin >> newFirstName;
                tx.exec("UPDATE client SET first_name = ('" + tx.esc(newFirstName) + "') WHERE client_id = '" + sid +
                        "'");
                tx.commit();
                break;
            case 2:
                std::cout << "Введите фамилию: ";
                std::cin >> newLastName;
                tx.exec("UPDATE client SET last_name = ('" + tx.esc(newLastName) + "') WHERE client_id = '" + sid +
                        "'");
                tx.commit();
                break;
            case 3:
                std::cout << "Введите почту: ";
                std::cin >> newEmail;
                tx.exec("UPDATE client SET email = ('" + tx.esc(newEmail) + "') WHERE client_id = '" + sid + "'");
                tx.commit();
                break;
            case 4:
                std::cout << "Введите номер телефона: ";
                std::cin >> newPhone;
                tx.exec("UPDATE phone SET phone = ('" + tx.esc(newPhone) + "') WHERE client_id = '" + sid + "'");
                tx.commit();
                break;
            default:
                std::cout << "Некорректный ввод " << std::endl;
                break;
        }
    } else return;
}

void SQL::deleteClientPhone(pqxx::work& tx) {
        std::string id = std::to_string(getIdByName(tx));
        tx.exec("DELETE FROM phone WHERE client_id = '" + id + "'");
        tx.commit();

}

void SQL::deleteClient(pqxx::work& tx) {
    std::string id = std::to_string(getIdByName(tx));
    tx.exec("DELETE FROM phone WHERE client_id = '" + id + "'");
    tx.exec("DELETE FROM client WHERE client_id = '" + id + "'");
    tx.commit();

}

void SQL::searchClient(pqxx::work& tx) {
    std::string value;
    std::cout << "Введите имя, фамилию, почту или номер телефона: " << std::endl;
    std::cin >> value;
    auto count = tx.query_value<int>("SELECT COUNT(*) FROM client WHERE "
                                     "first_name = '" + tx.esc(value) + "' OR "
                                                                        "last_name = '" + tx.esc(value) + "' OR "
                                                                                                          "email = '" +
                                     tx.esc(value) + "' ");

    if (count != 0) {
        auto queryId = tx.query<int>(
                "SELECT client_id FROM client WHERE "
                "first_name = '" + tx.esc(value) + "' OR "
                                                   "last_name = '" + tx.esc(value) + "' OR "
                                                                                     "email = '" + tx.esc(value) +
                "' ");
        for (auto[id] : queryId) {
            getDataById(tx, id);
        }
    } else {
        auto count2 = tx.query_value<int>(
                "SELECT COUNT(*) FROM phone WHERE phone = '" + tx.esc(value) + "' ");
        if (count2 != 0) {
            auto queryId = tx.query<int>(
                    "SELECT client_id FROM phone WHERE "
                    "phone = '" + tx.esc(value) + "' ");
            for (auto[id] : queryId)
                getDataById(tx, id);
        } else {
            std::cout << "В базе данных нет клиента с такими данными" << std::endl;
        }
    }
}
