#pragma once

#include <iostream>
#include <fstream>

#include "../hotel/Hotel.h"

class CommandLine {
private:
    Hotel hotel;
    std::string fileName;

public:
    void Open();
    void Close();
    void Save(const std::string&);
    void Help() const;
};