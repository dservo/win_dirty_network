#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <string.h>
#include <string>   
#include <stdio.h>
#include <winsock2.h>

typedef struct _lightSetDatum {
      unsigned char Board;
	  unsigned char Port;
	  unsigned char Value;
} lightSetDatum;

class CallbackInterface
{
public:
  
    virtual int netCallbackFunc(lightSetDatum *dataum) = 0;


};

class tcp_server: public CallbackInterface{

public:
    tcp_server(int);
    virtual ~tcp_server();
    int start_listening();
	

protected:
    int port;
    SOCKET serverSocket; // Server Socket
    SOCKET clientSocket; // Client Socket

private:
    int acceptedConections();
	int tcp_server::receive(char *reply, int dataSize);
	bool sendData(char *dataSend);

    int netCallbackFunc(lightSetDatum *datum);  
	void Capture();
	

};



