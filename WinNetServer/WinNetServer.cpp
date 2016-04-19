#include "NC_Server.h"

tcp_server::tcp_server(int port) {
  tcp_server::port = port;
}

tcp_server::~tcp_server(){
}

int tcp_server::start_listening() {
  // WSAStartup() initializes the program to call winsock2.dll
  WORD versionRequested;
  WSADATA wsaData;
  int wsaError;
  versionRequested = MAKEWORD(2, 2);
  wsaError = WSAStartup(versionRequested, &wsaData);
  if (wsaError != 0) {
    printf("Server: The Winsock dll not found!");
    WSACleanup();
    return 0;
  }
  else{
    printf("Server: The Winsock2 dll found");
  }
  // create server socket
  serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(serverSocket == INVALID_SOCKET) {
    printf("Server: Error initializing socket!");
    WSACleanup();
    return 0;
  }

  // set up socket information
  sockaddr_in service;
  service.sin_family = AF_INET;
  service.sin_port = htons(port);
  service.sin_addr.s_addr = inet_addr("127.0.0.1");

  // bind infromation struc to socet
  if(bind(serverSocket,(SOCKADDR*)&service,sizeof(service))==SOCKET_ERROR) {
    printf("\nServer: Error binding socket to port");
    WSACleanup();
    return 0;
  }

  // wait for connections
  if(listen(serverSocket,10)==SOCKET_ERROR) {
    printf("\nlisten(): Error listening on socket %d.", WSAGetLastError());
  }
  else{
    printf("\nServer: Waiting for connections...");
  }
  printf("\nServer: Waiting for a client to connect...");
  acceptedConections();
  return 0;
} // end start_listening

int tcp_server::acceptedConections() {
  sockaddr_in from;
  int fromlen=sizeof(from);
  clientSocket = accept(serverSocket,(SOCKADDR*)&from,&fromlen);

  Capture(); // handle incoming data from conection

  printf("\nclient has closed"); // clear conection and wait for a new one 
  closesocket(serverSocket);
  WSACleanup();
  start_listening();
  return 0;
}

int tcp_server::receive(char *reply , int dataSize) {
  int bytesReceved; 
  //Check to see if there is a reply
  bytesReceved = recv(clientSocket , reply , dataSize , 0);
  if( bytesReceved < 0) {
    printf("recv failed");
    return -1;
  }
  return bytesReceved;
}

bool tcp_server::sendData(char *dataSend) {
  if(send(serverSocket , dataSend , sizeof(dataSend)  , 0) < 0) {
    printf("Send failed : \n");
    return false;
  }
  printf("Data send\n");
  return true;
}

int tcp_server::netCallbackFunc(lightSetDatum *datum)  { 
  char temp[32];
  memset(temp, 0x00, 32);
  
  sprintf(temp,"{%d%d%03d}", datum->Board , datum->Port , datum->Value );

  send(clientSocket,temp,strlen(temp),0);
  return 1; 
}


void tcp_server::Capture(){

}