#include "Date.h"

bool Date::IsLeapYear(int year) const {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

int Date::GetDaysInMonth(int month, int year) const {
    switch(month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12: return 31;
        case 4:
        case 6:
        case 9:
        case 11: return 30;
        case 2: return IsLeapYear(year) ? 29 : 28;
        default: return -1;
    }
}

bool Date::IsValidDay(int day, int month, int year) const {
    return day >= 1 && day <= GetDaysInMonth(month, year);
}

int Date::ToDays() const {
    long long days = 0;

    for (size_t year = 2023; year < _year; ++year) {
        days += IsLeapYear(year) ? 366 : 365;
    }

    for (size_t month = 1; month < _month; ++month) {
        days += GetDaysInMonth(month, _year);
    }

    return days + _day - 1;
}

void Date::SetDefaultDate() {
    _day = 1;
    _month = 1;
    _year = 2023;
}

void Date::SetDate(int day, int month, int year) {
    if (IsValidDate(day, month, year)) {
        _day = day;
        _month = month;
        _year = year;
    } else {
        SetDefaultDate();
    }
}

Date::Date() {
    SetDefaultDate();
}

Date::Date(int day, int month, int year) {
    SetDate(day, month, year);
}

int Date::GetDay() const {
    return _day;
}

int Date::GetMonth() const {
    return _month;
}

int Date::GetYear() const {
    return _year;
}

Date& Date::operator=(const Date& other) {
    if (this != &other) {
        _day = other._day;
        _month = other._month;
        _year = other._year;
    }

    return *this;
}

bool Date::operator==(const Date& other) const {
    return _day == other._day && _month == other._month && _year == other._year;
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

bool Date::operator<(const Date& other) const {
    return (_year < other._year ||
        (_year == other._year && _month < other._month) ||
        (_year == other._year && _month == other._month && _day < other._day));
}

bool Date::operator>(const Date& other) const {
    return !(*this < other || *this == other);
}

bool Date::operator<=(const Date& other) const {
    return !(*this > other);
}

bool Date::operator>=(const Date& other) const {
    return !(*this < other);
}

int Date::operator-(const Date& other) const {
    const Date& earlierDate = (*this < other) ? *this : other;
    const Date& laterDate = (*this < other) ? other : *this;

    return laterDate.ToDays() - earlierDate.ToDays();
}

bool Date::IsValidDate(int day, int month, int year) const{
    return year >= 2023 && (month >= 1 && month <= 12) && IsValidDay(day, month, year);
}

const std::string& Date::ToString() const {
    std::string date = std::to_string(_year) + "-";
    date += ((_month >= 1 && _month <= 9) ? "0" : "") + std::to_string(_month) + "-";
    date += ((_day >= 1 && _day <= 9) ? "0" : "") + std::to_string(_day);

    return date;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.ToString();
    return os;
}

std::istream& operator>>(std::istream& is, Date& date) {
    char dashOne, dashTwo;
    int day, month, year;

    is >> year >> dashOne >> month >> dashTwo >> day;

    if (!is || dashOne != '-' || dashTwo != '-' || !date.IsValidDate(day, month, year)) {
        date.SetDefaultDate();
        is.clear();
    } else {
        date.SetDate(day, month, year);
    }

    return is;
}