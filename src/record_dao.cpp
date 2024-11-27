#include "record_dao.h"

#include <iostream>

using namespace std;

record_db::record_db() {
    if (sqlite3_open("db/record_data.db", &db)) {
        cerr << "Open database failed: " << sqlite3_errmsg(db) << endl;
        exit(1);
    }
    const string sql = R"(
        CREATE TABLE IF NOT EXISTS record_data (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            time INTEGER NOT NULL
        );)";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void record_db::insert(const Record &record) const {
    const string sql = "INSERT INTO record_data (name, time) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, record.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, record.time);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

vector<Record> record_db::search(const int page) const {
    const string sql = "SELECT id, name, time FROM record_data ORDER BY time LIMIT 5 OFFSET ?;";
    vector<Record> results;
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, page * 5);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Record result = {};
        if (sqlite3_column_type(stmt, 0) != SQLITE_NULL)
            result.id = sqlite3_column_int(stmt, 0);
        if (sqlite3_column_type(stmt, 1) != SQLITE_NULL)
            result.name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        if (sqlite3_column_type(stmt, 2) != SQLITE_NULL)
            result.time = sqlite3_column_int(stmt, 2);
        results.emplace_back(result);
    }
    sqlite3_finalize(stmt);
    return results;
}

void record_db::remove(const int id) const {
    const string sql = "DELETE FROM record_data WHERE id = ?;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

int record_db::get_count() const {
    const string sql = "SELECT COUNT(*) FROM record_data;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_step(stmt);
    const int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}
