#include "CommandLine.h"

void CommandLine::Open() {
    std::fstream file(fileName, std::ios::out);

    if(!file.is_open()) {
        std::ofstream outfile(fileName);
        outfile.close();

        file.open(fileName, std::ios::out);
        if(!file.is_open()) {
            std::cout << "Failed to open or create file " << fileName << "\n";
            return;
        }
    }

    file >> hotel;
    file.close();
    std::cout << "Successfully opened file " << fileName << "\n";
}

void CommandLine::Close() {
    hotel.Clear();
    std::cout << "Successfully closed file " << fileName << "\n";
    fileName.clear();
}

void CommandLine::Save(const std::string& saveFile) {
    std::fstream file(saveFile, std::ios::in);

    if(!file.is_open()) {
        std::cout << "Failed to open file " << saveFile << "\n";
    }

    file << hotel;
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