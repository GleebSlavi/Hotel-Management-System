#pragma once

#include <vector>;

#include "Room.h";

class Hotel {
private:
    std::vector<Room> _rooms;

    const std::vector<Room> FindAvailableSuitableRooms(int, const Date&, const Date&) const;
public:
    void CheckIn(int, const Date&, const Date&, const std::string&, int);
    bool Availability(const Date&) const;
    void CheckOut(int);
    bool Report(const Date&, const Date&) const;
    bool Find(int, const Date&, const Date&) const;
    void Unavailable(int, const Date&, const Date&, const std::string&);

    void loadHotel(const std::string&);
    void safeHotel(const std::string&);
};