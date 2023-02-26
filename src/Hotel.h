#pragma once

#include <vector>;

#include "Room.h";

class Hotel {
private:
    std::vector<Room> _rooms;

public:
    void CheckIn(int, const Date&, const Date&, const std::string&, int);
    void Availability(const Date&) const;
    void CheckOut(int);
    void Report(const Date&, const Date&) const;
    void Find(int, const Date&, const Date&) const;
    void VIPFind(int, const Date&, const Date&);
    void Unavailable(int, const Date&, const Date&, const std::string&);
};