#include "NC_Client.h"

tcp_client* tcp_client::mSingleton = NULL;

tcp_client* tcp_client::getSingleton() {
  
  if(!mSingleton){
    mSingleton = new tcp_client();
  }
  
  return mSingleton;
}  // end getSingleton

tcp_client::tcp_client() {
    sock = -1;
    port = 0;
    
}
 
/**
    Connect to a host on a port number
*/
bool tcp_client::conn(int port) {
	/* WSAStartup() initializes
       the program to call winsock2.dll */
    WORD wVersionRequested;
    WSADATA wsaData;
    int wsaerr;
    wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0){
        printf("Server: The Winsock dll not found!");
        WSACleanup();
        return 0;
    } else {
        printf("Server: The Winsock2 dll found");
    }
    //create socket if it is not already created
    if(sock == -1)
    {
        //Create socket
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1){
            perror("Could not create socket");
        } else {
        printf("Socket created\n");
		}
    }
    else    {   /* OK , nothing */  }
     
  
     
    //plain ip address
    server.sin_addr.s_addr = inet_addr( "127.0.0.1" );
      
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
     
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
     
    printf("Connected\n");
    return true;
}
 
/**
    Send data to the connected host
*/
bool tcp_client::send_data(char *dataSend , int dataSize) {
    //Send some data
    if( send(sock , dataSend , dataSize  , 0) < 0)
    {
        printf("Send failed : \n");
        return false;
    }
    printf("Data send\n");
     
    return true;
}
 
/**
    Receive data from the connected host
*/
int tcp_client::receive(char *reply , int dataSize) {
  int bytesReceved; 
  //Check to see if there is a reply
  bytesReceved = recv(sock , reply , dataSize, 0);
  if( bytesReceved < 0) {
    printf("recv failed");
    return -1;
  }
  return bytesReceved;
}
 