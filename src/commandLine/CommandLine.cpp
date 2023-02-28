#include "CommandLine.h"

bool CommandLine::IsOpened() const {
    if (_fileName.empty()) {
        std::cout << "Please open a file first!\n";
        return false;
    }
    return true;
}

bool CommandLine::IsValidRoomNumber(int roomNumber) const {
    const std::vector<int> roomNumbers = _hotel.GetRoomNumbers();

    size_t roomsCount = roomNumbers.size();
    for(size_t i = 0; i < roomsCount; ++i) {
        if (roomNumber == roomNumbers[i]) {
            return true;
        }
    }

    return false;
}


void CommandLine::Open() {
    std::fstream file(_fileName, std::ios::out);

    if(!file.is_open()) {
        std::ofstream outfile(_fileName);
        outfile.close();

        file.open(_fileName, std::ios::out);
        if(!file.is_open()) {
            std::cout << "Failed to open or create file " << _fileName << "\n";
            _fileName.clear();
            return;
        }
    }

    _hotel.Clear();
    file >> _hotel;
    file.close();
    std::cout << "Successfully opened file " << _fileName << "\n";
}

void CommandLine::Close() {
    _hotel.Clear();
    std::cout << "Successfully closed file " << _fileName << "\n";
    _fileName.clear();
}

void CommandLine::Save(const std::string& saveFile) {
    std::fstream file(saveFile, std::ios::in);

    if(!file.is_open()) {
        std::cout << "Failed to open file " << saveFile << "\n";
    }

    file << _hotel;
    file.close();
    std::cout << "Successfully saved " << saveFile << "\n";
}

void CommandLine::Help() const {
    std::cout << "The following commands are supported:\n"
              << "open <file>                                             opens <file>\n"
              << "close                                                   closes the currently opened file\n"
              << "save                                                    saves the currently opened file\n"
              << "saveas <file>                                           saves the currently opened file in <file>\n"
              << "help                                                    print commands information\n"
              << "exit                                                    exits the program\n"
              << "checkin <room> <from> <to> <note> [<guests>]            registers a room with number <room> from date <from> to date <to> and adds note <note>, if optional parameter <guests> is not inputed it equals the beds in the room\n"           
              << "availability [<date>]                                   shows a list of all available rooms on date <date>, if <date> is not inputed it uses today's date\n"
              << "checkout <room>                                         leaves occupied room with number <room>\n"
              << "report <from> <to>                                      shows a list, that for every used room in the interval <from>-<to>, shows how many days a room was used\n"
              << "find <beds> <from> <to>                                 finds a suitable free room in the interval <from>-<to> with at least <beds> beds\n"
              << "unavailable <room> <from> <to> <note>                   declares a room with number <room> from date <from> to date <to> for temporarly unavailable and adds note <note>, the room is not used for guests\n";
}

void CommandLine::CheckIn() {
    int room;
    std::cin >> room;

    if (!IsValidRoomNumber(room)) {
        std::cout << "Please enter a valid room number!\n";
        return;
    }

    Date from, to;
    std::cin >> from >> to;

    if (from >= to) {
        std::cout << "Please enter valid dates!\n";
        return;
    }

    std::string note;
    std::cin >> note;

    int guests = -1;
    std::cin >> std::ws;
    if (std::cin.peek() != EOF) {
        std::cin >> guests;
        if (std::cin.fail()) {
            std::cout << "Please enter valid guests!\n";
            std::cin.clear();
            return;
        }
    }

    _hotel.CheckIn(room, from, to, note, guests);
    std::cout << "Successfully checked in room " << room << "\n";
}

void CommandLine::Availability() const {
    std::cin >> std::ws;

    Date date;
    if (std::cin.peek() != EOF) {
        std::cin >> date;
    } else {

    }

    if (!_hotel.Availability(date)) {
        std::cout << "There are no available rooms on " << date << "\n";
    }
}

void CommandLine::CheckOut() {
    int room;
    std::cin >> room;

    if (!IsValidRoomNumber(room)) {
        std::cout << "Please enter valid room number!\n";
        return;
    }

    _hotel.CheckOut(room);
    std::cout << "Successfully checked out room " << room << "\n";
}

void CommandLine::Report() const {
    Date from, to;

    std::cin >> from >> to;
    if (from >= to) {
        std::cout << "Please enter valid dates!\n";
        return;
    }

    if (!_hotel.Report(from, to)) {
        std::cout << "No rooms are used for these dates.\n";
    }
}

void CommandLine::Find() const {
    int beds;
    Date from, to;

    std::cin >> beds;
    if (beds <= 0) {
        std::cout << "Please enter valid beds!\n";
        return;
    }

    std::cin >> from >> to;
    if (from >= to) {
        std::cout << "Please enter valid dates!\n";
        return;
    }

    if (!_hotel.Find(beds, from, to)) {
        std::cout << "There are no free suitable rooms for these dates.\n";
    }
}

void CommandLine::Run() {
    std::string command;
    while(true) {
        std::cin >> command;

        if (command == "open") {
            std::cin >> _fileName;
            Open();
        } else if (command == "close") {
            if (IsOpened()) {
                Close();
            }
        } else if (command == "save") {
            if (IsOpened()) {
                Save(_fileName);
            }
        } else if (command == "saveas") {
            if (IsOpened()) {
                std::string otherFile;
                std::cin >> otherFile;

                Save(otherFile);
            }
        } else if (command == "help") {
            Help();
        } else if (command == "checkin") {
            if (IsOpened()) {
                CheckIn();
            }
        } else if (command == "availability") {
            if (IsOpened()) {
                Availability();
            }
        } else if (command == "checkout") {
            if (IsOpened()) {
                CheckOut();
            }
        } else if (command == "report") {
            if (IsOpened()) {
                Report();
            }
        } else if (command == "find") {
            if (IsOpened()) {
                Find();
            }
        } else if (command == "exit") {
            std::cout << "Exiting the program...\n";
            return;
        } else {
            std::cout << "Invalid command! Please try again!\n";
        }
    }
}