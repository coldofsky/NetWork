#include<iostream>
#include<stdio.h>
#include<Winsock2.h>
using namespace std;
int main()
{

    WORD wsa = MAKEWORD(2,2);
    char ip[16];
    cout << "Please input the IP:" << endl;
    cin >> ip;
    //这里声明了winsock的版本2.2
    //1.1版本只支持TCP/IP协议
    //2.0版本支持多协议。
    //2.0版有兼容性
    //任何使用1.1版的源代码、二进制文件、应用程序都可以不加修改地在2.0规范下使用
     WSADATA wsaData;
     //WSADATA结构体中主要包含了系统所支持的Winsock版本信息
     if(WSAStartup(wsa, &wsaData)!=0)
    {
        cout<<"初始化失败"<<endl;   //这进行初始化
        return 0;
    }
    SOCKET s_server = socket(AF_INET, SOCK_STREAM, 0);
    if(s_server==INVALID_SOCKET)
    {
        cout<<"socket创建失败"<<endl;
        return 0;
    }
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;   //IPV4协议
    server_addr.sin_port = htons(5050);     //服务器端口
    //这里有改动 写网络地址
    server_addr.sin_addr.S_un.S_addr = inet_addr(ip);
    if (connect(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "server connnet fail!!" << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "success!!" << endl;
	}
    char send_buf[200];
    char accept_buf[200];
    while(1)
    {

        cout<<"input your message:"<<endl;
        cout<<endl;
        cin>>send_buf;
        int res_len = send(s_server,send_buf,100,0);
        if(res_len<0)
        {
            cout<<"error"<<endl;
        }
        cout<<"发送成功,等待接受"<<endl;
       recv(s_server, accept_buf, 200, 0);
       cout<<"服务端消息"<<accept_buf<<endl;

        cout<<"接受成功"<<endl<<endl;

    }

    closesocket(s_server);
	//释放DLL资源
	WSACleanup();
	return 0;
}
