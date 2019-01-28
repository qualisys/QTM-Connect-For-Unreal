#ifndef NETWORK_H
#define NETWORK_H

#include <winsock2.h>
#define  WIN32_LEAN_AND_MEAN


class COutput;

class CNetwork
{
public:
    CNetwork();
    ~CNetwork();
    bool  Connect(const char* pServerAddr, unsigned short nPort);
    void  Disconnect();
    bool  Connected();
    bool  CreateUDPSocket(unsigned short &nUDPPort, bool bBroadcast = false);
    int   Receive(char* rtDataBuff, int nDataBufSize, bool bHeader, int nTimeout, unsigned int *ipAddr = NULL);
    bool  Send(const char* pSendBuf, int nSize);
    bool  SendUDPBroadcast(const char* pSendBuf, int nSize, short nPort, unsigned int nFilterAddr = 0);
    char* GetErrorString();
    int   GetError() const;
    bool  IsLocalAddress(unsigned int nAddr) const;
    unsigned short GetUdpServerPort();
    unsigned short GetUdpBroadcastServerPort();

private:
    bool InitWinsock();
    void SetErrorString();
    unsigned short GetUdpServerPort(SOCKET nSocket);

private:
    COutput*   mpoOutput;
    SOCKET     mhSocket;
    SOCKET     mhUDPSocket;
    SOCKET     mhUDPBroadcastSocket;
    char       maErrorStr[256];
    unsigned long      mnLastError;
};


#endif