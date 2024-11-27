#pragma once

#include "record_bean.h"

#include <sqlite3.h>
#include <vector>

class record_db {
    record_db();
    sqlite3 *db = nullptr;

public:
    ~record_db() { sqlite3_close(db); }
    static record_db *getInstance() {
        static record_db instance;
        return &instance;
    }
    void insert(const Record &record) const;
    [[nodiscard]] vector<Record> search(int page) const;
    void remove(int id) const;
    [[nodiscard]] int get_count() const;
};
