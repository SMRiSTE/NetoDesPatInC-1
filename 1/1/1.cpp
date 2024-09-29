#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class SqlSelectQueryBuilder {
public:
    SqlSelectQueryBuilder() : table_(""), has_columns_(false) {}

    SqlSelectQueryBuilder& AddColumn(const std::string& column) {
        has_columns_ = true;
        columns_.push_back(column);
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& table) {
        table_ = table;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& key, const std::string& value) {
        where_conditions_.push_back(key + "=" + value);
        return *this;
    }

    std::string BuildQuery() const {
        std::ostringstream query;

        query << "SELECT ";

        if (columns_.empty()) {
            query << "*";
        }
        else {
            query << Join(columns_, ", ");
        }

        if (!table_.empty()) {
            query << " FROM " << table_;
        }

        if (!where_conditions_.empty()) {
            query << " WHERE " << Join(where_conditions_, " AND ");
        }

        query << ";";  // Завершаем запрос

        return query.str();
    }

private:
    std::string table_;
    std::vector<std::string> columns_;
    std::vector<std::string> where_conditions_;
    bool has_columns_;

    std::string Join(const std::vector<std::string>& elements, const std::string& separator) const {
        std::ostringstream joined;
        for (size_t i = 0; i < elements.size(); ++i) {
            joined << elements[i];
            if (i < elements.size() - 1) {
                joined << separator;
            }
        }
        return joined.str();
    }
};

int main() {
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    std::string query = query_builder.BuildQuery();
    std::cout << query << std::endl;  // Вывод: SELECT name, phone FROM students WHERE id=42 AND name=John;

    return 0;
}