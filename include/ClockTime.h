
#include "../include/DS3234.h"

class ClockTime
{
private:
    DS3234 rtc;

    int ModTime(uint32_t &time, uint32_t modulus);

public:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    ClockTime(/* args */);
    ~ClockTime();

    void GetTimeFromRTC();
    //Set to RTC by internal Time
    void SetTimeToRTC();

    uint64_t GetNtpTimeStamp();
    void SetTimeFromNTP(uint64_t timestamp);


};
