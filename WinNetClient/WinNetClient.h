#pragma once
#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>  
#include <winsock2.h>



/**
    TCP Client class
*/
class tcp_client{
private:
    tcp_client();

	int sock;
    int port;
    struct sockaddr_in server;
	static tcp_client* mSingleton;
     
public:
	static tcp_client* getSingleton();
    
	bool conn(int);
    bool send_data(char *dataSend , int dataSize);
    int receive(char *reply , int dataSize);
};