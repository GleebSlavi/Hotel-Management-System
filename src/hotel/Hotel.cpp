#include "Hotel.h";

const std::vector<Room>& Hotel::FindAvailableSuitableRooms(int beds, const Date& from, const Date& to) const {
    std::vector<Room> freeRooms;

    size_t roomsCount = _rooms.size();
    for (size_t i = 0; i < roomsCount; ++i) {
        if (_rooms[i].GetBeds() >= beds && _rooms[i].IsAvailableInInterval(from, to)) {
            freeRooms.push_back(_rooms[i]);
        }
    }
    
    return freeRooms;
}

void Hotel::AddRoom(const Room& room) {
    _rooms.push_back(room);
    _roomNumbers.push_back(room.GetRoomNumber());
}

const std::vector<int> Hotel::GetRoomNumbers() const {
    return _roomNumbers;
}

const std::vector<Room> Hotel::GetRooms() const {
    return _rooms;
}

void Hotel::CheckIn(int room, const Date& from, const Date& to, const std::string& note, int guests = -1) {
    size_t roomsCount = _rooms.size();
    for (size_t i = 0; i < roomsCount; ++i) {
        if (_rooms[i].GetRoomNumber() == room) {
            _rooms[i].CheckIn(from, to, note, guests);
            break;
        }
    }
}

bool Hotel::Availability(const Date& date) const {
    size_t count = 0;
    size_t roomsCount = _rooms.size();
    for (size_t i = 0; i < roomsCount; ++i) {
        if (_rooms[i].Availability(date)) {
            ++count;
            _rooms[i].PrintEmptyRoom();
        }
    }

    return count > 0;
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

bool Hotel::Report(const Date& from, const Date& to) const {
    size_t count = 0;
    size_t roomsCount = _rooms.size();
    for (size_t i = 0; i < roomsCount; ++i) {
        int daysUsed = _rooms[i].Report(from, to);
        if (daysUsed > 0) {
            ++count;
            std::cout << _rooms[i].GetRoomNumber() << ": " << daysUsed << "\n";
        }
    }

    return count > 0;
}

bool Hotel::Find(int beds, const Date& from, const Date& to) const {
    const std::vector<Room> freeRooms = FindAvailableSuitableRooms(beds, from, to);
    size_t roomsCount = freeRooms.size();
    if (roomsCount == 0) {
        return false;
    }

    Room foundRoom = freeRooms[0];
    for (size_t i = 1; i < roomsCount; ++i) {
        if (foundRoom.GetBeds() == beds) {
            break;
        }
        else if (foundRoom.GetBeds() > _rooms[i].GetBeds()) {
            foundRoom = _rooms[i];
        }
    }

    foundRoom.PrintEmptyRoom();
    return true;
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

std::ostream& operator<<(std::ostream& os, const Hotel& hotel) {
    const std::vector<Room> rooms = hotel.GetRooms();
    size_t roomsCount = rooms.size();

    for(size_t i = 0; i < roomsCount; ++i) {
        os << rooms[i] << "\n";
    }

    return os;
}

std::istream& operator>>(std::istream& is, Hotel& hotel) {
    std::string line;
    while(std::getline(is, line, '\n')) {
        std::stringstream ss(line);

        Room room;
        ss >> room;
    
        hotel.AddRoom(room);
    }

    return is;
}