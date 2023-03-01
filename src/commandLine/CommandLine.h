#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

#include "../hotel/Hotel.h"

class CommandLine {
private:
    Hotel _hotel;
    std::string _fileName;

    bool IsOpened() const;
    bool IsValidRoomNumber(int) const;
    const std::string GetTodaysDate() const;

    void Open();
    void Close();
    void Save(const std::string&);
    void Help() const;

    void CheckIn();
    void Availability() const;
    void CheckOut();
    void Report() const;
    void Find() const;
public:
    void Run();
};