#include "Room.h"

int Room::_roomNumber = 100;

void Room::SetRoom(int beds, const Date& from, const Date& to, 
    const std::string& note, bool isAvailable = true, int guests = 0) {
    _beds = beds;
    _guests = guests;
    _accomodation = from;
    _departure = to;
    _note = note;
    _isAvailable = isAvailable;
}

Room::Room(int beds = 0) {
    ++_roomNumber;
    _beds = beds;
    _guests = 0;
    _isAvailable = true;
}

Room::Room(int beds, int guests, const Date& from, 
    const Date& to, const std::string& note) {
    ++_roomNumber;
    SetRoom(beds, from, to, note, false, guests);
}

Room& Room::operator=(const Room& other) {
    if (this != &other) {
        _roomNumber = other._roomNumber;
        SetRoom(other._beds, other._accomodation, other._departure,
            other._note, other._isAvailable, other._guests);
    }

    return *this;
}

int Room::GetRoomNumber() const {
    return _roomNumber;
}

int Room::GetBeds() const {
    return _beds;
}

int Room::GetGuests() const {
    return _guests;
}

const Date& Room::GetAccomodation() const {
    return _accomodation;
}

const Date& Room::GetDeparture() const {
    return _departure;
}

const bool Room::GetAvailability() const {
    return _isAvailable;
}

const std::string& Room::GetNote() const {
    return _note;
}

void Room::CheckIn(const Date& from, const Date& to,
    const std::string& note, int guests = -1) {
    int guestsCount = guests == -1 ? _beds : guests;
    SetRoom(_beds, from, to, _note, false, guestsCount);
}

bool Room::Availability(const Date& date) const {
    return _isAvailable && !(_accomodation <= date && _departure >= date);
}

void Room::CheckOut() {
    _guests = 0;
    _isAvailable = true;
    _accomodation.SetDefaultDate();
    _departure.SetDefaultDate();
    _note.clear();
}

int Room::Report(const Date& from, const Date& to) const {
    if (_departure <= from || _accomodation >= to) {
        return 0;
    }

    Date startDate = (_accomodation > from) ? _accomodation : from;
    Date endDate = (_departure < to) ? _departure : to;

    return (endDate - startDate) + 1;
}

void Room::Unavailable(const Date& from, const Date& to, const std::string& note) {
    SetRoom(_beds, from, to, _note, false);
}

void Room::PrintEmptyRoom() const {
    std::cout << "\n--------------------------------------------------------------"
              << "\nRoom number: " << _roomNumber
              << "\nBeds: " << _beds
              << "\n--------------------------------------------------------------\n";
}

std::ostream& operator<<(std::ostream& os, const Room& room) {
    os <<(room.GetAvailability() ? 'F' : 'O')
       << room.GetBeds() << ","
       << room.GetGuests() << ","
       << room.GetAccomodation() << ","
       << room.GetDeparture() << ","
       << (!room.GetNote().empty() ? "," + room.GetNote() : "");

    return os;
}

std::istream& operator>>(std::istream& is, Room& room) {
    char comma;
    int beds, guests;
    bool isAvailable;
    Date from, to;
    std::string note;

    is >> comma;
    isAvailable = comma == 'F' ? true : false;

    if (isAvailable) {
        is >> comma >> beds;
        room.SetRoom(beds, from, to, note);
    } else {
        is >> comma >> beds >> comma
           >> guests >> comma
           >> from >> comma
           >> to >> comma;

        if (is.peek() == ',') {
            is.get();
            std::getline(is, note, '\n');
        }
        room.SetRoom(beds, from, to, note, false, guests);
    }

    return is;
}