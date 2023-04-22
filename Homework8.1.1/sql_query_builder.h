#pragma once
#include <vector>
#include <iostream>
#include <map>

struct Event {
    std::string name;
    std::string column;
    std::vector<std::string> columns;
    std::string from;
    std::map<std::string, std::string> binding;
    std::string target;
    std::string source;
    std::vector<std::string> route;
};

class SqlSelectQueryBuilder
{
protected:
    Event event;
public:
    explicit SqlSelectQueryBuilder()
    {
        
    }

    Event BuildQuery() noexcept 
    {
        int count = 0;
        if (event.column.empty() && event.columns.empty())
        {
            event.column = "*";
            std::cout << "SELECT \"" << event.column << "\";" << std::endl;
        }
        else if (!event.column.empty() && event.columns.empty())
        {
            std::cout << "SELECT \"" << event.column << "\";" << std::endl;
        }
        else if (event.column.empty() && !event.columns.empty())
        {
            std::cout << "SELECT ";
            for (int i = 0; i < event.columns.size(); ++i)
            {
                if (i != 0)
                {
                    std::cout << ", ";
                }
                std::cout << "\"" << event.columns[i] << "\"";
            }
        }
        
        std::cout << "FROM \"" << event.from << "\";" << std::endl;
        std::cout << "WHERE ";
        for (auto& a : event.binding)
        {
            std::cout << "\"" << a.first << "\" = \"" << a.second << "\"";
            if (count >= 0 && count < event.binding.size() - 1)
            {
                std::cout << " AND ";
            }
            ++count;
        }
        std::cout << ";" << std::endl;
        return event;
    }

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept
    {
        event.columns = columns;
        return *this;
    }

    SqlSelectQueryBuilder& AddColumn(const std::string& column) noexcept 
    {
        event.column = column;
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& from) 
    {
        event.from = from;
        return *this;
    }
    SqlSelectQueryBuilder& AddWhere(const std::string& columnWhere, const std::string& isWhere) 
    {
        event.binding[columnWhere] = isWhere;
        return *this;
    }
};