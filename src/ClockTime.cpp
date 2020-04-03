#include "../include/ClockTime.h"

ClockTime::ClockTime(/* args */)
{
}

ClockTime::~ClockTime()
{
}

void ClockTime::GetTimeFromRTC()
{
    year = rtc.GetTime(YEAR);
    month = rtc.GetTime(MONTH);
    day = rtc.GetTime(DAY);
    hour = rtc.GetTime(HOUR);
    minute = rtc.GetTime(MINUTE);
    second = rtc.GetTime(SECOND);
}

void ClockTime::SetTimeToRTC()
{
    rtc.SetDateTime(year,month,day,hour,minute,second);
}

uint64_t ClockTime::GetNtpTimeStamp()
{
    int32_t result = (year - 1900) * 31536000;
    result += (month - 1) * 2592000;
    result += (day - 1) * 86400;
    result += hour * 3600;
    result += minute * 60;
    result += second;

    return result; // fraction is not supported

}

void ClockTime::SetTimeFromNTP(uint64_t timestamp)
{
    uint32_t stamp_sec = timestamp & 0xffffffff;
    uint32_t stamp_fraction = timestamp >> 32;

    year = ModTime(stamp_sec,31536000) + 1900;
    month = ModTime(stamp_sec,2592000) + 1;
    day = ModTime(stamp_sec,86400) +1;
    hour = ModTime(stamp_sec,3600);
    minute = ModTime(stamp_sec,60);
    second = stamp_sec;

    SetTimeToRTC();
}

int ClockTime::ModTime(uint32_t& time,uint32_t modulus)
{
    int result = time / modulus;
    time = time % modulus;
    return result;
}