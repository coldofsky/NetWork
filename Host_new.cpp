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
    //����������winsock�İ汾2.2
    //1.1�汾ֻ֧��TCP/IPЭ��
    //2.0�汾֧�ֶ�Э�顣
    //2.0���м�����
    //�κ�ʹ��1.1���Դ���롢�������ļ���Ӧ�ó��򶼿��Բ����޸ĵ���2.0�淶��ʹ��
     WSADATA wsaData;
     //WSADATA�ṹ������Ҫ������ϵͳ��֧�ֵ�Winsock�汾��Ϣ
     if(WSAStartup(wsa, &wsaData)!=0)
    {
        cout<<"��ʼ��ʧ��"<<endl;   //����г�ʼ��
        return 0;
    }
    SOCKET s_server = socket(AF_INET, SOCK_STREAM, 0);
    if(s_server==INVALID_SOCKET)
    {
        cout<<"socket����ʧ��"<<endl;
        return 0;
    }
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;   //IPV4Э��
    server_addr.sin_port = htons(5050);     //�������˿�
    //�����иĶ� д�����ַ
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
        cout<<"���ͳɹ�,�ȴ�����"<<endl;
       recv(s_server, accept_buf, 200, 0);
       cout<<"�������Ϣ"<<accept_buf<<endl;

        cout<<"���ܳɹ�"<<endl<<endl;

    }

    closesocket(s_server);
	//�ͷ�DLL��Դ
	WSACleanup();
	return 0;
}
