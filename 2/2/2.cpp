#include <iostream>
#include <string>
#include <vector>
#include<map>
#include <sstream>

class SqlSelectQueryBuilder {
public:
    SqlSelectQueryBuilder() : table_(""), has_columns_(false) {}

    SqlSelectQueryBuilder& AddColumn(const std::vector<std::string>& colums) {
        has_columns_ = true;
        for (int i = 0; i < colums.size(); i++) {
            columns_.push_back(colums[i]);
        }
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& table) {
        table_ = table;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) {
        for (std::map<std::string, std::string>::const_iterator it = kv.begin(); it != kv.end(); ++it) {
            where_conditions_.push_back(it->first + "=" + it->second);
        }
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

        query << ";";

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
    std::vector<std::string> vec = { "name","phone","email", "city"};
    std::map<std::string, std::string> map = { {"id","42"}, {"name", "John"} };

    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn(vec);
    query_builder.AddFrom("students");
    query_builder.AddWhere(map);

    std::string query = query_builder.BuildQuery();
    std::cout << query << std::endl;

    return 0;
}