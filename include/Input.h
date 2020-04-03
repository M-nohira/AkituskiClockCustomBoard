#include <Arduino.h>

#define SW4 19
#define SW5 18
#define SW6 17
#define SW7 16

struct KEY
{
    bool sw4;
    bool sw5;
    bool sw6;
    bool sw7;
    bool sw4f;
    bool sw5f;
    bool sw6f;
    bool sw7f;
};

class Input
{
private:
    struct KEY keyStatus;
public:
    
    Input(/* args */);
    ~Input();

    
    struct KEY GetkeyState();
    float GetBrigtness();

};


