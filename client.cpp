//�ͻ��˷�������

#include <stdio.h>

#include <winsock2.h>

#pragma comment(lib, "WS2_32.lib")
#define BUF_SIZE 1024
int main(int argc, char* argv[])
{
	WSADATA wsaData;

    SOCKADDR_IN serverAddr; //��������ַ

    SOCKET socketC, socketM;

    char sendbuf[BUF_SIZE] = "";   //���͵�����

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("WSAStartup failed!\n");
        return 1;
    }
    socketC = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5678);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(socketC, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	printf("\t\t\t���ǿͻ���");
	char recvbuf[BUF_SIZE];
	while(true)
	{
		printf("\n������Ҫ���͸�����˵�ֵ\n");
		scanf("%s",sendbuf);
		send(socketC, sendbuf,sizeof(sendbuf), 0);//�������ݸ������
		recv(socketC, recvbuf, sizeof(recvbuf), 0);//��ȡ�ӷ�����������ֵ
		printf("�ӷ�������ȡ��\n%s\n", recvbuf);
		//break;
	//	}
	}
    closesocket(socketC);
    WSACleanup();
	printf("�밴�س����ر�");
	getchar();
	return 0;
}
