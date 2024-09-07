#ifndef TASK_1_SQL_H
#define TASK_1_SQL_H
#include <pqxx/pqxx>

class SQL {
public:
    void createTables (pqxx::work& tx);
    void addNewClient(pqxx::work& tx);
    int getIdByName(pqxx::work& tx);
    void addPhoneNumber(pqxx::work& tx);
    void getDataById(pqxx::work& tx, int id);
    void changeClientData(pqxx::work& tx);
    void deleteClientPhone(pqxx::work& tx);
    void deleteClient(pqxx::work& tx);
    void searchClient(pqxx::work& tx);

};


#endif //TASK_1_SQL_H
