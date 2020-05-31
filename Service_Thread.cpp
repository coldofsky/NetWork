#include <bits/stdc++.h>
#include <winsock2.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
using namespace std;

int DEFAULT_PORT = 5050;
static void Usage(char *proc)
{
    printf("%s[local_ip], [local_port]\n", proc);
}

int startup(char *_ip, int _port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket");
        return 1;
    }
    struct sockaddr_in local; //��ʼ��Э���ַ
    local.sin_family = AF_INET;
    local.sin_port = htons(_port);
    local.sin_addr.s_addr = inet_addr(_ip);
    //���׽��ֺ�tcp����󶨣������ip��ַ��
    if (bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0)
    {
        perror("bind");
        exit(3);
    }
    //��������׽��֣�����ָ���˿ڣ��ڶ���������ʾ�����Ŷ����ӵ�������
    if (listen(sock, 5) < 0)
    {
        perror("listen");
    }
    return sock;
}
//argv[]ָ�����飬ָ���������
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        return 2;
    }
    int listen_sock = startup(argv[1], atoi(argv[2]));
    printf("sock:%d\n", listen_sock);
    //��Ҫ���ӽ��̵��ӽ���ȥ�ṩ����
    //�����̼�������
    char buf[1024];
    while (1)
    {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int newsock = accept(listen_sock, (struct sockaddr *)&client, &len);
        if (newsock < 0)
        {
            perror("accept");
            continue;
        }
        //�������е�����ת��Ϊ�����û����Կ���������
        printf("get a new client %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        pid_t id = fork();
        if (id < 0)
        {
            perror("fork");
            close(newsock);
            return 1;
        }
        else if (id == 0)
        {                       //��Ϊ�ӽ��̻�̳и����̵��ļ������������ӽ���ֻ��Ҫnewsock
            close(listen_sock); //�ӽ��̹رռ����׽���
            if (id > 0)
            {
                exit(0); //�ӽ��̳䵱�����̽�ɫ���������Ƴ��󣬻ᵼ���ӽ��̳�Ϊ�¶�����
            }
            //���ӽ��̵��ӽ���ȥ����д
            while (1)
            {
                int s = read(newsock, buf, sizeof(buf) - 1);
                if (s > 0)
                {
                    buf[s] = 0;
                    printf("client# %s\n", buf);
                    write(newsock, buf, strlen(buf));
                }
                else if (s == 0)
                {
                    printf("client quit\n");
                }
                else
                {
                    break;
                }
            }
            close(newsock);
            exit(1);
        }
        else
        {
            //������,ֻ�������
            close(newsock);
            waitpid(id, NULL, 0);
        }
    }
    close(listen_sock);
    return 0;
}
