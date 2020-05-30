#include <bits/stdc++.h>
#include <Winsock2.h>
#define DATA_BUFFER 1024
int _tmain(int argc, char * argv[]) {
	WSADATA wsaData;
	SOCKET sClient;
	int iPort = 5050;
	int iLen;
	char buf[DATA_BUFFER];
	struct sockaddr_in ser;
	if(argc<2) {
		printf("Usage: client [server IP address]\n");
		return -1;
	}
memset(buf,0,sizeof(buf));
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		printf("Failed to load Winsock.\n");
		return -1;
	}
	ser.sin_family = AF_INET;
	ser.sin_port = htons(iPort);
	ser.sin_addr.s_addr = inet_addr(argv[1]);
	sClient = socket(AF_INET,SOCK_STREAM,0);
	if(sClient == INVALID_SOCKET)
	{
		printf("socket() Failed: %d\n",WSAGetLastError());
		return -1;
	}
if(connect(sClient,(struct sockaddr *)&ser,sizeof(ser)) == INVALID_SOCKET) {
		printf("connect() Failed: %d\n",WSAGetLastError());
		return -1;
	}
	else{
		iLen = recv(sClient,buf,sizeof(buf),0);
		if(iLen == 0)
			return -1;
		else if(iLen == SOCKET_ERROR){
			printf("recv() Failed: %d\n",WSAGetLastError());
			return -1;
		}
		else
			printf("recv() data from server: %s\n",buf);
	}
	closesocket(sClient);
	WSACleanup();
	return 0;
}
