#pragma once

#include <vector>;
#include <sstream>

#include "Room.h";

class Hotel {
private:
    std::vector<Room> _rooms;
    std::vector<int> _roomNumbers;

    const std::vector<Room>& FindAvailableSuitableRooms(int, const Date&, const Date&) const;
public:
    void AddRoom(const Room&);

    const std::vector<int> GetRoomNumbers() const;
    const std::vector<Room> GetRooms() const;

    void CheckIn(int, const Date&, const Date&, const std::string&, int);
    bool Availability(const Date&) const;
    void CheckOut(int);
    bool Report(const Date&, const Date&) const;
    bool Find(int, const Date&, const Date&) const;
    void Unavailable(int, const Date&, const Date&, const std::string&);

    friend std::ostream& operator<<(std::ostream&, const Hotel&);
    friend std::istream& operator>>(std::istream&, Hotel&);
};