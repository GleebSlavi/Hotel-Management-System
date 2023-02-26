#pragma once

#include <iostream>
#include <sstream>

#include "doctest.h"
#include "../src/Date.h"

TEST_CASE("Invalid date passed") {
    Date d(30, 2, 2023);

    CHECK(d.GetDay() == 1);
    CHECK(d.GetMonth() == 1);
    CHECK(d.GetYear() == 2023);

    d.SetDate(12, 56, 1001);

    CHECK(d.GetDay() == 1);
    CHECK(d.GetMonth() == 1);
    CHECK(d.GetYear() == 2023);
}

TEST_CASE("Default date") {
    Date d;

    CHECK(d.GetDay() == 1);
    CHECK(d.GetMonth() == 1);
    CHECK(d.GetYear() == 2023);

    d.SetDefaultDate();

    CHECK(d.GetDay() == 1);
    CHECK(d.GetMonth() == 1);
    CHECK(d.GetYear() == 2023);
}

TEST_CASE("Boolean predefine operators") {
    Date d1(15, 3, 2023);
    Date d2(21, 4, 2023);

    CHECK((d1 > d2) == false);
    CHECK((d1 < d2) == true);
    CHECK((d1 != d2) == true);

    d1.SetDate(21, 4, 2023);

    CHECK((d1 == d2) == true);
    CHECK((d1 != d2) == false);
}

TEST_CASE("To string") {
    Date d(15, 3, 2023);

    CHECK(d.ToString() == "2023-03-15");

    d.SetDefaultDate();

    CHECK(d.ToString() == "2023-01-01");
}

TEST_CASE("Date substraction") {
    Date d1(12, 6, 2023);
    Date d2(18, 12, 2023);

    CHECK((d1 - d2) == 189);
    CHECK((d2 - d1) == 189);
}

TEST_CASE("Date assignment") {
    Date d1(16, 9, 2023);

    CHECK(d1.GetDay() == 16);
    CHECK(d1.GetDay() == 9);
    CHECK(d1.GetYear() == 2023);

    Date d2(25, 1, 2028);
    d1 = d2;

    CHECK(d1.GetDay() == 25);
    CHECK(d1.GetDay() == 1);
    CHECK(d1.GetYear() == 2028);
}

TEST_CASE("Serialization") {
    Date d(15, 3, 2030);

    std::stringstream ss;
    ss << d;

    std::string date;
    ss >> date;

    CHECK(date == "2030-03-15");
}

TEST_CASE("Deserialization") {
    Date d;

    std::string date = "2024-05-02";
    std::stringstream ss;

    ss << date;
    ss >> d;

    CHECK(d.GetDay() == 2);
    CHECK(d.GetMonth() == 5);
    CHECK(d.GetYear() == 2024);
}