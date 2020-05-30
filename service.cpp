#include <bits/stdc++.h>
#include <winsock2.h>
using namespace std;

#define DEFAULT_PORT 5050
int main()
{
    int iport = DEFAULT_PORT;
    WSADATA wsaData;
    SOCKET sListen, sAccept;
    int iLen;
    int iSend;
    char buf[] = "I am a server";
    struct sockaddr_in ser, cli;
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		printf("Failed to load Winsock.\n");
		return -1;
	}
    sListen = socket(AF_INET, SOCK_STREAM, 0);
    if (sListen == INVALID_SOCKET){
        cout << "socket() Failed" << WSAGetLastError() << endl;
        return -1;
    }
    ser.sin_family = AF_INET;
    ser.sin_port = htons(iport);
    ser.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sListen, (LPSOCKADDR) & ser, sizeof((ser))) == SOCKET_ERROR){
        cout << "bind() Failed:" << WSAGetLastError() << endl;
        return -1;
    }
    if (listen(sListen, 5) == SOCKET_ERROR){
        cout << "bind() Failed:" << WSAGetLastError() << endl;
        return -1;
    }
    iLen = sizeof(cli);
    while(1){
        sAccept = accept(sListen, (struct sockaddr *) &cli, &iLen);
        if (sAccept == INVALID_SOCKET){
            printf("accept() Failed: %d\n",WSAGetLastError());
			return -1;
        }
        printf("Accepted client IP:[%s],port:[%d]\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
        iSend = send(sAccept,buf,sizeof(buf),0);
		if(iSend == SOCKET_ERROR) {
			printf("send() Failed: %d\n",WSAGetLastError());
			break;
		}
		else if(iSend == 0) {
			break;
		}
		else {
			printf("send() byte: %d\n",iSend);
		}
		closesocket(sAccept);
	}
	closesocket(sListen);
	WSACleanup();
	return 0;
}
