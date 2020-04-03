#include "../include/Display.h"


Display::Display(/* args */)
{
}
Display::~Display()
{
}

byte Display::GetPacket(PacketType type, int segment, bool dp)
{
    if (type >= Hour)
        return SEGMENT[segment] + (dp == true ? 0b1 : 0b0);

    return segment; // 0b上下
}

void Display::SetSchematic(int index, byte segCode)
{
    dateSchematic[index] = segCode;
}

void Display::SendPacket(uint16_t packet)
{
    shiftOut(SER, SRCLK, MSBFIRST, packet >> 8);
    shiftOut(SER, SRCLK, MSBFIRST, packet);
}

void Display::ApplyDisplay()
{
    for (int cnt = 0; cnt <= 8; cnt++)
    {
        uint16_t packet = (0x01 << (cnt + 8)) + dateSchematic[cnt];
        SendPacket(packet);

        digitalWrite(RCLK, 1);
        delay(1);
        digitalWrite(RCLK, 0);
        delay(1);
        digitalWrite(RCLK, 1);
    }
}