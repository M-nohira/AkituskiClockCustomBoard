#include "../include/Display.h"

Display display;

void core0(void *param)
{

}

void setup()
{
    xTaskCreatePinnedToCore(core0,"core0",4096,NULL,1,NULL,0);
}

void loop()
{
    //temperatureRead()温度取得　セルシウス
    display.SetSchematic(0,display.GetPacket(MilCode,3,false));
    display.SetSchematic(0,display.GetPacket(Hour,3,false));
    display.SetSchematic(0,display.GetPacket(Hour,3,false));
    display.SetSchematic(0,display.GetPacket(HourDot,3,false));
    display.SetSchematic(0,display.GetPacket(Min,3,false));
    display.SetSchematic(0,display.GetPacket(Min,3,false));
    display.SetSchematic(0,display.GetPacket(MinDot,3,false));
    display.SetSchematic(0,display.GetPacket(Sec,3,false));
    display.SetSchematic(0,display.GetPacket(Sec,3,false));
    display.ApplyDisplay();

}

