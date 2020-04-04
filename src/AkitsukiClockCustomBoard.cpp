#include "../include/Display.h"
#include "../include/ClockTime.h"

Display display;
ClockTime _ctime;

void core0(void *param)
{
}

void setup()
{
    //xTaskCreatePinnedToCore(core0, "core0", 4096, NULL, 1, NULL, 0);
    Serial.begin(115200);

}

void loop()
{
    _ctime.GetTimeFromRTC();
    // Serial.print(_ctime.hour);
    // Serial.print(_ctime.minute);
    // Serial.println(_ctime.second);
    //display.SetSchematic(0, 3);
    display.SetSchematic(0, display.GetPacket(Hour, _ctime.hour / 10, false));
    display.SetSchematic(1, display.GetPacket(Hour, _ctime.hour % 10, false));
    display.SetSchematic(7, 0);
    display.SetSchematic(2, display.GetPacket(Min, _ctime.minute / 10, false));
    display.SetSchematic(3, display.GetPacket(Min, _ctime.minute % 10, false));
    display.SetSchematic(6, 63);
    display.SetSchematic(4, display.GetPacket(Sec, _ctime.second / 10, false));
    display.SetSchematic(5, display.GetPacket(Sec, _ctime.second % 10, false));
    display.ApplyDisplay();
}
