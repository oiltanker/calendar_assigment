#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int wdStart = 2; // 1800-01-01 was Wednesday

bool isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

const char* wdStrMap[7] {
    "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"
};

const char* monStrMap[12] {
    "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
};

const int monDayMap[12] {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

int main() {
    int inYear;
    cout << "Enter year to print the calendar for (any year in [1800, ...) range):\n";
    bool firstEntry = true;
    do {
        if (!firstEntry) cout << std::format("{} is not a valid year, provide a year in [1800, ...) range\n", inYear);
        cin >> inYear;
        firstEntry = false;
    } while (inYear < 1800);
    
    int daysPast = 0;
    for (int y = 1800; y != inYear; y++) {
        daysPast += isLeap(y) ? 366 : 365; // leap years shift week day for the next year
    }

    int y = inYear, wd = (wdStart + daysPast) % 7;
    cout << std::format("\n{} is a {} year and {}-01-01 is {}\n", y, (isLeap(y) ? "leap" : "regular"), y, wdStrMap[wd]);

    string wdTitle;
    for (int twd = 0; twd < 7; twd++) wdTitle += std::format(" {}", wdStrMap[twd]);
    wdTitle += '\n';

    cout << setfill(' ');
    for (int m = 0; m < 12; m++) {
        int days = monDayMap[m];
        if (isLeap(y) && m == 1) days++;
        auto monTitle = std::format("-- {} {} --", monStrMap[m], y);
        cout << "\n " << string((wdTitle.length() - 1 - monTitle.length()) / 2, ' ') << monTitle << '\n';
        cout << wdTitle;
        for (int mWd = 0; mWd < wd; mWd++) cout << "    ";
        for (int d = 1; d <= days; d++, wd = (wd + 1) % 7) {
            if (d != 1 && wd == 0) cout << '\n';
            cout << setw(4) << d;
        }
        cout << '\n';
    }

    return 0;
}
