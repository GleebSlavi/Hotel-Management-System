#pragma once

#include <iostream>
#include <string>

class Date {
private:
    int _day;
    int _month;
    int _year;

    bool IsValidDay(int, int, int) const;
    bool IsLeapYear(int) const;
    int GetDaysInMonth(int, int) const;
    int ToDays() const;
public:
    Date();
    Date(int, int, int);

    void SetDefaultDate();
    void SetDate(int, int, int);

    int GetDay() const;
    int GetMonth() const;
    int GetYear() const;

    Date& operator=(const Date&);
    bool operator==(const Date&) const;
    bool operator!=(const Date&) const;
    bool operator>(const Date&) const;
    bool operator<(const Date&) const;
    bool operator>=(const Date&) const;
    bool operator<=(const Date&) const;
    int operator-(const Date&) const;

    bool IsValidDate(int, int, int) const;
    const std::string& ToString() const;

    friend std::ostream& operator<<(std::ostream&, const Date&);
    friend std::istream& operator>>(std::istream&, Date&);
};