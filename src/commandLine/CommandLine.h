#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

#include "../hotel/Hotel.h"

class CommandLine {
private:
    Hotel _hotel;
    std::string _fileName;

    bool IsOpened() const;
    bool IsValidRoomNumber(int) const;
    const std::string GetTodaysDate() const;
public:
    void Open();
    void Close();
    void Save(const std::string&);
    void Help() const;

    void CheckIn();
    void Availability() const;
    void CheckOut();
    void Report() const;
    void Find() const;

    void Run();
};