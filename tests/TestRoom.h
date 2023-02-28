#pragma once

#include <iostream>
#include <sstream>

#include "doctest.h"
#include "../src/hotel/Room.h"

TEST_CASE("Create available room") {
    Room roomOne(5);

    CHECK(roomOne.GetAvailability() == true);
    CHECK(roomOne.GetRoomNumber() == 101);
    CHECK(roomOne.GetBeds() == 5);
    CHECK(roomOne.GetGuests() == 0);
    CHECK(roomOne.GetNote() == "");
    CHECK(roomOne.GetDeparture().ToString() == "2023-01-01");
    CHECK(roomOne.GetAccomodation().ToString() == "2023-01-01");

    Room roomTwo;

    CHECK(roomOne.GetAvailability() == true);
    CHECK(roomOne.GetRoomNumber() == 102);
    CHECK(roomOne.GetBeds() == 0);
    CHECK(roomOne.GetGuests() == 0);
    CHECK(roomOne.GetNote() == "");
    CHECK(roomOne.GetDeparture().ToString() == "2023-01-01");
    CHECK(roomOne.GetAccomodation().ToString() == "2023-01-01");
}

TEST_CASE("Create occupied room") {
    Date from(15, 3, 2023), to(21, 4, 2023);
    std::string note = "The Simpsons";

    Room room(4, 2, from, to, note);

    CHECK(room.GetAvailability() == false);
    CHECK(room.GetRoomNumber() == 101);
    CHECK(room.GetBeds() == 4);
    CHECK(room.GetGuests() == 2);
    CHECK(room.GetNote() == "The Simpsons");
    CHECK(room.GetDeparture().ToString() == "2023-04-21");
    CHECK(room.GetAccomodation().ToString() == "2023-03-15");
}

TEST_CASE("Room assignment") {
    Room roomOne;

    CHECK(roomOne.GetAvailability() == true);
    CHECK(roomOne.GetRoomNumber() == 101);
    CHECK(roomOne.GetBeds() == 0);
    CHECK(roomOne.GetGuests() == 0);
    CHECK(roomOne.GetNote() == "");
    CHECK(roomOne.GetDeparture().ToString() == "2023-01-01");
    CHECK(roomOne.GetAccomodation().ToString() == "2023-01-01");


    Date from(15, 3, 2023), to(21, 4, 2023);
    std::string note = "The Simpsons";

    Room roomTwo(4, 2, from, to, note);
    roomOne = roomTwo;

    CHECK(roomOne.GetAvailability() == false);
    CHECK(roomOne.GetRoomNumber() == 102);
    CHECK(roomOne.GetBeds() == 4);
    CHECK(roomOne.GetGuests() == 2);
    CHECK(roomOne.GetNote() == "The Simpsons");
    CHECK(roomOne.GetDeparture().ToString() == "2023-04-21");
    CHECK(roomOne.GetAccomodation().ToString() == "2023-03-15");
}

TEST_CASE("Checkin room") {
    Room room(3);

    CHECK(room.GetAvailability() == true);
    CHECK(room.GetBeds() == 3);
    CHECK(room.GetGuests() == 0);
    CHECK(room.GetNote() == "");
    CHECK(room.GetDeparture().ToString() == "2023-01-01");
    CHECK(room.GetAccomodation().ToString() == "2023-01-01");

    Date from(15, 3, 2023), to(21, 4, 2023);
    std::string note = "The Simpsons";

    room.CheckIn(from, to, note);

    CHECK(room.GetAvailability() == false);
    CHECK(room.GetBeds() == 3);
    CHECK(room.GetGuests() == 3);
    CHECK(room.GetNote() == "The Simpsons");
    CHECK(room.GetDeparture().ToString() == "2023-01-01");
    CHECK(room.GetAccomodation().ToString() == "2023-01-01");
}

TEST_CASE("Is room available on a date") {
   Room roomOne;

   CHECK(roomOne.Availability(Date(15,3,2023)) == true);

   Room roomTwo(2, 2, Date(15, 3, 2023), Date(18, 3, 2023), "");

   CHECK(roomTwo.Availability(Date(17, 3, 2023)) == false);
}

TEST_CASE("Checkout room") {
    Date from(15, 3, 2023), to(21, 4, 2023);
    std::string note = "The Simpsons";

    Room room(4, 2, from, to, note);

    CHECK(room.GetAvailability() == false);
    CHECK(room.GetBeds() == 4);
    CHECK(room.GetGuests() == 2);
    CHECK(room.GetNote() == "The Simpsons");
    CHECK(room.GetDeparture().ToString() == "2023-04-21");
    CHECK(room.GetAccomodation().ToString() == "2023-03-15");

    room.CheckOut();

    CHECK(room.GetAvailability() == false);
    CHECK(room.GetBeds() == 4);
    CHECK(room.GetGuests() == 0);
    CHECK(room.GetNote() == "");
    CHECK(room.GetDeparture().ToString() == "2023-01-01");
    CHECK(room.GetAccomodation().ToString() == "2023-01-01");
}

TEST_CASE("Days a room is used in interval") {
    Date from(15, 3, 2023), to(21, 4, 2023);
    Room room(4, 2, from, to, "");

    CHECK(room.Report(Date(25, 3, 2023), Date(25, 4, 2023)) == 27);
    CHECK(room.Report(Date(28, 6, 2023), Date(29, 12, 2023)) == 0);
}

TEST_CASE("Unavailable room") {
    Room room(7);

    room.Unavailable(Date(12, 2, 2023), Date(17,2, 2023), "Under construction");

    CHECK(room.GetAvailability() == false);
    CHECK(room.GetGuests() == 0);
    CHECK(room.GetNote() == "Under construction");
}

TEST_CASE("Is room available in interval") {
    Room room(2, 2, Date(15, 3, 2023), Date(18, 3, 2023), "");

    CHECK(room.IsAvailableInInterval(Date(20, 3, 2023), Date(24, 3, 2023)) == true);
    CHECK(room.IsAvailableInInterval(Date(15, 3, 2023), Date(24, 3, 2023)) == false);
    CHECK(room.IsAvailableInInterval(Date(12, 3, 2023), Date(16, 3, 2023)) == false);
    CHECK(room.IsAvailableInInterval(Date(16, 3, 2023), Date(17, 3, 2023)) == false);
}

TEST_CASE("Serialization") {
    Room r(2, 2, Date(15, 3, 2023), Date(18, 3, 2023), "The Simpsons");

    std::stringstream ss;
    ss << r;

    std::string room;
    ss >> room;

    CHECK(room == "O,2,2,2023-03-15,2023-03-18,The Simpsons");
}

TEST_CASE("Deserialization") {
    Room r;
    
    std::string room = "O,2,2,2023-03-15,2023-03-18,The Simpsons";
    std::stringstream ss;

    ss << room;
    ss >> r;

    CHECK(r.GetRoomNumber() == 101);
    CHECK(r.GetBeds() == 2);
    CHECK(r.GetGuests() == 2);
    CHECK(r.GetAvailability() == false);
    CHECK(r.GetAccomodation().ToString() == "2023-03-15");
    CHECK(r.GetDeparture().ToString() == "2023-03-18");
    CHECK(r.GetNote() == "The Simpsons");
}