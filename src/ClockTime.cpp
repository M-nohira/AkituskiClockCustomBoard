#include "../include/ClockTime.h"

ClockTime::ClockTime()
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
    // for(int i = 0; i<= 6; i++) 
    // {
    //     delayMicroseconds(100);
    //     Serial.println(rtc.GetTime((TimeType)i));
    // }
}

void ClockTime::SetTimeToRTC()
{
    rtc.SetDateTime(year, month, day, hour, minute, second);
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

    uint32_t stamp_sec = GetSeconds(timestamp);

    year = ModTime(stamp_sec, 31536000) + 1900;
    month = ModTime(stamp_sec, 2592000) + 1;
    day = ModTime(stamp_sec, 86400) + 1;
    hour = ModTime(stamp_sec, 3600);
    minute = ModTime(stamp_sec, 60);
    second = stamp_sec;
}

int ClockTime::ModTime(uint32_t &time, uint32_t modulus)
{
    int result = time / modulus;
    time = time % modulus;
    return result;
}

void ClockTime::SyncRtcToNtp(NTP ntp)
{
    //動くかわからん
    GetTimeFromRTC();
    NtpPacket packet;
    uint64_t t1 = GetNtpTimeStamp();
    packet.VN = 4;
    packet.Mode = 3; //client
    packet.TransmitTimestamp = t1;
    ntp.SendPacket(IPAddress(192, 168, 10, 2), 123, packet);
    NtpPacket result = ntp.RecievePacket();
    if (result.Mode = !4) //client Packet is abort
        return;
    GetTimeFromRTC();
    uint64_t t3 = GetNtpTimeStamp();
    int theta = ((GetSeconds(result.ReceiveTimestamp) - GetSeconds(result.OriginTimestamp)) - (GetSeconds(result.TransmitTimestamp) - GetSeconds(t3))) / 2;
    t3 += theta;
    SetTimeFromNTP(t3);
    SetTimeToRTC();
}

uint32_t GetSeconds(uint64_t stamp)
{
    return 
    stamp & 0xffffffff;
}