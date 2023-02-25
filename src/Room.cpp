#include "Room.h"

int Room::_roomNumber = 100;

Room::Room(int beds) {
    ++_roomNumber;
    _beds = beds;
    _guests = 0;
    _isAvailable = true;
}

Room::Room(int beds, int guests, const Date& accomodation, 
    const Date& departure, const std::string& note) {
    ++_roomNumber;
    _beds = beds;
    _guests = guests;
    _accomodation = accomodation;
    _departure = departure;
    _note = note;
    _isAvailable = false;
}

Room& Room::operator=(const Room& other) {
    if (this != &other) {
        _roomNumber = other._roomNumber;
        _beds = other._beds;
        _guests = other._guests;
        _accomodation = other._accomodation;
        _departure = other._departure;
        _isAvailable = other._isAvailable;
        _note = other._note;
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

void Room::CheckIn(const Date& accomodation, const Date& departure,
    const std::string& note, int guests = -1) {
    _accomodation = accomodation;
    _departure = departure;
    _note = note;
    _isAvailable = false;
    _guests = guests == -1 ? _beds : guests;
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

void Room::Unavailable(const Date& accomodation, const Date& departure, const std::string& note) {
    _accomodation = accomodation;
    _departure = departure;
    _note = note;
    _isAvailable = false;
    _guests = 0;
}

std::ostream& operator<<(std::ostream& os, const Room& room) {
    os << room.GetBeds() << ","
       << room.GetGuests() << ","
       << room.GetAccomodation() << ","
       << room.GetDeparture() << ","
       << (room.GetAvailability() ? 'F' : 'O')
       << (!room.GetNote().empty() ? "," + room.GetNote() : "");

    return os;
}

std::istream& operator>>(std::istream& is, Room& room) {
    char comma;
    int beds, guests;
    Date accomodation, departure;
    bool isAvailable;
    std::string note;

    is >> beds >> comma
       >> guests >> comma
       >> accomodation >> comma
       >> departure >> comma >> comma;

    isAvailable = comma == 'F' ? true : false;

    if (is.peek() == ',') {
        is.get();
        is >> note;
    }

    Room other_room(beds, guests, accomodation, departure, note);
    room = other_room;

    return is;
}