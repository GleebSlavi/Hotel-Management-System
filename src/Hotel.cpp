#include "Hotel.h";

void Hotel::CheckIn(int room, const Date& from, const Date& to, const std::string& note, int guests = -1) {
    size_t roomsCount = _rooms.size();
    for (size_t i = 0; i < roomsCount; ++i) {
        if (_rooms[i].GetRoomNumber() == room) {
            _rooms[i].CheckIn(from, to, note, guests);
            break;
        }
    }
}

void Hotel::Availability(const Date& date) const {
    size_t roomsCount = _rooms.size();
    for (size_t i = 0; i < roomsCount; ++i) {
        if (_rooms[i].Availability(date)) {
            _rooms[i].PrintEmptyRoom();
        }
    }
}

void Hotel::CheckOut(int room) {
    size_t roomsCount = _rooms.size();
    for (size_t i = 0; i < roomsCount; ++i) {
        if (_rooms[i].GetRoomNumber() == room) {
            _rooms[i].CheckOut();
            break;
        }
    }
}

void Hotel::Report(const Date& from, const Date& to) const {
    size_t roomsCount = _rooms.size();
    for (size_t i = 0; i < roomsCount; ++i) {
        int daysUsed = _rooms[i].Report(from, to);
        if (daysUsed > 0) {
            std::cout << _rooms[i].GetRoomNumber() << ": " << daysUsed << "\n";
        }
    }
}

void Hotel::Unavailable(int room, const Date& from, const Date& to, const std::string& note) {
    size_t roomsCount = _rooms.size();
    for (size_t i = 0; i < roomsCount; ++i) {
        if (_rooms[i].GetRoomNumber() == room) {
            _rooms[i].Unavailable(from, to, note);
            break;
        }
    }
}