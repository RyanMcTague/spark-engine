#include "spark_editor/core/database.h"
#define WithSQLDatabase(path) SQLite::Database(path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)

#ifndef SPARK_DATABASE
#define DATABASE_PATH ":memory:"
#endif //SPARK_DATABASE


Database::Database(): m_client(WithSQLDatabase(":memory:")) {
    Setup();
}
Database::~Database() = default;


void Database::Setup() {
    m_client.exec(R"(
        PRAGMA foreign_keys = ON;

        CREATE TABLE IF NOT EXISTS tile_sheets(
            id VARCHAR PRIMARY KEY NOT NULL,
            name VARCHAR NOT NULL,
            path VARCHAR NOT NULL,
            width INTEGER NOT NULL,
            height INTEGER NOT NULL,
            tilesize_x INTEGER NOT NULL,
            tilesize_y INTEGER NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        );

        CREATE UNIQUE INDEX IF NOT EXISTS idx_unique_name_on_tile_sheets ON tile_sheets(name);

        CREATE TABLE IF NOT EXISTS tiles(
            id VARCHAR PRIMARY KEY NOT NULL,
            tile_sheet_id INTEGER NOT NULL,
            x INTEGER NOT NULL,
            y INTEGER NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (tile_sheet_id)
                REFERENCES tile_sheets (id)
        );
    )");
}