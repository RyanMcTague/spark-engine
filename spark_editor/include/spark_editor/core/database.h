#ifndef SPARK_ENGINE_DATABASE_H
#define SPARK_ENGINE_DATABASE_H
#include "spark_editor/base.h"
#include "SQLiteCpp/SQLiteCpp.h"

class Database{
private:
    SQLite::Database m_client;
    void Setup();
public:
    Database();
    ~Database();
};

#endif //SPARK_ENGINE_DATABASE_H
