#include <Arduino.h>

#define SRCLK 25
#define SER 26
#define RCLK 22

enum PacketType
{
    MilCode,
    HourDot,
    MinDot,

    Hour,
    Min,
    Sec,
};

class Display
{
private:
    //この頭悪いの何とかしないと
    const byte PM = 0b00000001;
    const byte AM = 0b00000010;
    const byte HD = 0b00001100;
    const byte MD = 0b00110000;
    const byte ALRAM = 0b00000001;

    byte SEGMENT[20] =
        {
            //12345678
            0b00111111, //0
            0b00000110, //1
            0b01011011, //2
            0b01001111, //3
            0b01100110, //4
            0b01101101, //5
            0b01111101, //6
            0b00100111, //7
            0b01111111, //8
            0b01101111, //9
            0b01110111, //A 10
            0b01111100, //b 11
            0b00111001, //C 12
            0b01011110, //d 13
            0b01111001, //E 14
            0b01110001, //F 15
            0b01110110, //H 16
            0b00011111, //J 17
            0b01000000, //- 18
            0b01011000, //small C 19
    };

    void SendPacket(uint16_t packet);
    byte dateSchematic[9];

public:
    
    Display(/* args */);
    ~Display();

    byte GetPacket(PacketType type, int segment, bool dp);

    void ApplyDisplay();
    
    void SetSchematic(int index, byte packet);
};

