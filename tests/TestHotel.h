#pragma once

#include <iostream>
#include <sstream>

#include "doctest.h"
#include "../src/hotel/Hotel.h"

TEST_CASE("Add room") {
    Room room;

    Hotel hotel;
    hotel.AddRoom(room);

    CHECK(hotel.GetRooms()[0].GetBeds() == 0);
    CHECK(hotel.GetRooms()[0].GetRoomNumber() == 101);
    CHECK(hotel.GetRoomNumbers()[0] == 101);
}

TEST_CASE("Clear hotel") {
    Room room;

    Hotel hotel;
    hotel.AddRoom(room);

    CHECK(hotel.GetRooms().empty() == false);
    CHECK(hotel.GetRoomNumbers().empty() == false);

    hotel.Clear();

    CHECK(hotel.GetRooms().empty() == true);
    CHECK(hotel.GetRoomNumbers().empty() == true);
}

TEST_CASE("Checkin") {
    Room room(5);

    Hotel hotel;
    hotel.AddRoom(room);

    hotel.CheckIn(101, Date(15, 3, 2023), Date(18, 3, 2023), "Ivanovi");

    CHECK(hotel.GetRooms()[0].GetAvailability() == false);
    CHECK(hotel.GetRooms()[0].GetAccomodation().ToString() == "2023-03-15");
    CHECK(hotel.GetRooms()[0].GetDeparture().ToString() == "2023-03-18");
    CHECK(hotel.GetRooms()[0].GetNote() == "Ivanovi");
}

TEST_CASE("Availability") {
    Room room(5);

    Hotel hotel;
    hotel.AddRoom(room);

    CHECK(hotel.Availability(Date(15, 3, 2023)) == true);

    hotel.CheckIn(101, Date(15, 3, 2023), Date(18, 3, 2023), "Ivanovi");
    
    CHECK(hotel.Availability(Date(16, 3, 2023)) == false);
}

TEST_CASE("Checkout") {
    Room room(5);

    Hotel hotel;
    hotel.AddRoom(room);

    hotel.CheckIn(101, Date(15, 3, 2023), Date(18, 3, 2023), "Ivanovi");
    hotel.CheckOut(101);

    CHECK(hotel.GetRooms()[0].GetAvailability() == true);
}

TEST_CASE("Report") {
    Room room(5);

    Hotel hotel;
    hotel.AddRoom(room);

    CHECK(hotel.Report(Date(10, 3, 2023), Date(21, 8, 2023)) == false);

    hotel.CheckIn(101, Date(15, 3, 2023), Date(18, 3, 2023), "Ivanovi");

    CHECK(hotel.Report(Date(10, 3, 2023), Date(21, 8, 2023)) == true);
}

TEST_CASE("Find") {
    Room room(5);

    Hotel hotel;
    hotel.AddRoom(room);

    CHECK(hotel.Find(5, Date(15, 3, 2023), Date(18, 3, 2023)) == true);

    hotel.CheckIn(101, Date(15, 3, 2023), Date(18, 3, 2023), "Ivanovi");

    CHECK(hotel.Find(5, Date(15, 3, 2023), Date(18, 3, 2023)) == false);
}

TEST_CASE("Unavailable") {
    Room room(5);

    Hotel hotel;
    hotel.AddRoom(room);

    hotel.Unavailable(101, Date(15, 3, 2023), Date(18, 3, 2023), "Under construction");

    CHECK(hotel.GetRooms()[0].GetAvailability() == false);
    CHECK(hotel.GetRooms()[0].GetAccomodation().ToString() == "2023-03-15");
    CHECK(hotel.GetRooms()[0].GetDeparture().ToString() == "2023-03-18");
    CHECK(hotel.GetRooms()[0].GetNote() == "Under construction");
}