#include <string>
#include <iostream>

class Date
{
    private:
        int day, month, year;
    public:
        Date(int day_, int month_, int year_): day{day_}, month{month_}, year{year_} {}
        Date() = default;

        // zaprzyjaźniona funkcja
        friend std::ostream& operator<<(std::ostream& os, const Date& d)
        {
            os << d.day << "." << d.month << "." << d.year;
            return os;
        }
        friend std::istream& operator>>(std::istream& is, Date& d)
        {
            char dots[2];
            is >> d.day >> dots[0] >> d.month >> dots[1] >> d.year;
            return is;
        }
};