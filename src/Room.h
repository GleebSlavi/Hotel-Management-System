#pragma once

#include <iostream>
#include "Date.h"

class Room {
private:
    static int _roomNumber;
    int _beds;
    int _guests;
    Date _accomodation;
    Date _departure;
    bool _isAvailable;
    std::string _note;

    void SetRoom(int, const Date&, const Date&, const std::string&, bool, int);
public:
    Room(int);
    Room(int, int, const Date&, const Date&, const std::string&);

    Room& operator=(const Room&);

    int GetRoomNumber() const;
    int GetBeds() const;
    int GetGuests() const;
    const Date& GetAccomodation() const;
    const Date& GetDeparture() const;
    const bool GetAvailability() const;
    const std::string& GetNote() const;

    void CheckIn(const Date&, const Date&, const std::string&, int guests = -1);
    bool Availability(const Date&) const;
    void CheckOut();
    int Report(const Date&, const Date&) const;
    void Unavailable(const Date&, const Date&, const std::string&);

    void PrintEmptyRoom() const;

    friend std::ostream& operator<<(std::ostream&, const Room&);
    friend std::istream& operator>>(std::istream&, Room&);
};