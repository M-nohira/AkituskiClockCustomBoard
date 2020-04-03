#include "../include/NTP.h"

NTP::NTP(int localPort)
{
    udp.begin(localPort);
}

NTP::~NTP()
{
    udp.stop();
}

void NTP::SendPacket(IPAddress addr, int port, NtpPacket packet)
{
    byte buffer[48];
    packet.ConvertToBytes(buffer);
    udp.beginPacket(addr, port);
    udp.write(buffer, sizeof(buffer));
    udp.endPacket();
}

NtpPacket NTP::RecievePacket()
{
    NtpPacket packet;
    byte buffer[48];
    if (!udp.available())
        return packet;
    udp.read(buffer, sizeof(buffer));
    udp.flush();
    packet.ConvertFromBytes(buffer);
    return packet;
}

void NtpPacket::ConvertFromBytes(byte *buffer)
{
    //NtpPacket packet;
    LI = (buffer[0] >> (8 - 2)) & 0b11;
    VN = (buffer[0] >> (8 - 5)) & 0b111;
    Mode = (buffer[0] >> (8 - 8)) & 0b111;
    Stratum = buffer[1];
    POll = buffer[2];
    Precision = buffer[3];

    for (int cnt = 0; cnt <= 3; cnt++)
    {
        RootDelay += buffer[4 + cnt] << (cnt + 1);
    }
    for (int cnt = 0; cnt <= 3; cnt++)
    {
        RootDispersion += buffer[8 + cnt] << (cnt + 1);
    }
    for (int cnt = 0; cnt <= 3; cnt++)
    {
        ReferenceId += buffer[12 + cnt] << (cnt + 1);
    }
    for (int cnt = 0; cnt <= 7; cnt++)
    {
        ReferenceTimestamp += buffer[16 + cnt] << (cnt + 1);
    }
    for (int cnt = 0; cnt <= 7; cnt++)
    {
        OriginTimestamp += buffer[24 + cnt] << (cnt + 1);
    }
    for (int cnt = 0; cnt <= 7; cnt++)
    {
        ReceiveTimestamp += buffer[32 + cnt] << (cnt + 1);
    }
    for (int cnt = 0; cnt <= 7; cnt++)
    {
        TransmitTimestamp += buffer[40 + cnt] << (cnt + 1);
    }

    //return packet;
}

void NtpPacket::ConvertToBytes(byte *buffer)
{
    buffer[0] = LI;
    buffer[0] = (buffer[0] << 3) + VN;
    buffer[0] = (buffer[0] << 3) + Mode;
    buffer[1] = Stratum;
    buffer[2] = POll;
    buffer[3] = Precision;

    for (int cnt = 0; cnt <= 3; cnt++)
    {
        buffer[4 + cnt] = RootDelay >> (8 * (3 - cnt));
    }
    for (int cnt = 0; cnt <= 3; cnt++)
    {
        buffer[8 + cnt] = RootDispersion >> (8 * (3 - cnt));
    }
    for (int cnt = 0; cnt <= 3; cnt++)
    {
        buffer[12 + cnt] = ReferenceId >> (8 * (3 - cnt));
    }
    for (int cnt = 0; cnt <= 7; cnt++)
    {
        buffer[16 + cnt] = ReferenceTimestamp >> (8 * (7 - cnt));
    }
    for (int cnt = 0; cnt <= 7; cnt++)
    {
        buffer[24 + cnt] = OriginTimestamp >> (8 * (7 - cnt));
    }
    for (int cnt = 0; cnt <= 7; cnt++)
    {
        buffer[32 + cnt] = ReceiveTimestamp >> (8 * (7 - cnt));
    }
    for (int cnt = 0; cnt <= 7; cnt++)
    {
        buffer[40 + cnt] = TransmitTimestamp >> (8 * (7 - cnt));
    }

    //return buffer;
}