#pragma once
#include <string>

class IExportable {
public:
    virtual ~IExportable() = default;
    virtual std::string toJSON() const = 0;
    virtual std::string toCSV() const = 0;
}; 