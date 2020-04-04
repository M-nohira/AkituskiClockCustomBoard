
#include "../include/DS3234.h"
#include "../include/NTP.h"

class ClockTime
{
private:
    DS3234 rtc;

    int ModTime(uint32_t &time, uint32_t modulus);
    uint32_t GetSeconds(uint64_t stamp);
public:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    ClockTime();
    ~ClockTime();

    void GetTimeFromRTC();
    //Set to RTC by internal Time
    void SetTimeToRTC();

    uint64_t GetNtpTimeStamp();
    void SetTimeFromNTP(uint64_t timestamp);
    void SyncRtcToNtp(NTP ntp);

};
