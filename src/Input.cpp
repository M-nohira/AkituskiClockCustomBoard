#include "../include/Input.h"

Input::Input(/* args */)
{
    for (int cnt = 16; cnt <= 19; cnt++)
        pinMode(cnt, INPUT);
}

Input::~Input()
{
}

struct KEY Input::GetkeyState()
{
    struct KEY key;
    key.sw4 = digitalRead(SW4) == 1 ? true : false;
    key.sw5 = digitalRead(SW5) == 1 ? true : false;
    key.sw6 = digitalRead(SW6) == 1 ? true : false;
    key.sw7 = digitalRead(SW7) == 1 ? true : false;

    if (key.sw4 & (keyStatus.sw4 != key.sw4))
        key.sw4f = true;
    if (key.sw5 & (keyStatus.sw5 != key.sw4))
        key.sw5f = true;
    if (key.sw6 & (keyStatus.sw6 != key.sw6))
        key.sw6f = true;
    if (key.sw7 & (keyStatus.sw7 != key.sw7))
        key.sw7f = true;
    keyStatus = key;
    return key;
}

//返り値は電圧
float Input::GetBrigtness()
{
    float value = analogRead(32) / 4096;
    return value * 3.3;
}
