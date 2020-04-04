#include <Arduino.h>
#include <WiFiUdp.h>
#include <WiFi.h>
#include <IPAddress.h>

typedef struct NtpPacket
{
    int LI = 0; //2
    int VN = 0;
    int Mode = 0;
    int Stratum = 16;
    int POll = 0;
    int Precision = 0;
    uint32_t RootDelay = 0;
    uint32_t RootDispersion = 0;
    uint32_t ReferenceId = 0;
    uint64_t ReferenceTimestamp = 0;
    uint64_t OriginTimestamp = 0;
    uint64_t ReceiveTimestamp = 0;
    uint64_t TransmitTimestamp = 0;

    void ConvertFromBytes(byte *buffer);
    void ConvertToBytes(byte *buffer);
};

class NTP
{
private:
    
    WiFiUDP udp;
    

public:
    void SendPacket(IPAddress addr, int port, NtpPacket packet);
    NtpPacket RecievePacket();
    NTP(int localPort);
    ~NTP();
};
