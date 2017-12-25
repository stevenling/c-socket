//客户端发送数据

#include <stdio.h>

#include <winsock2.h>

#pragma comment(lib, "WS2_32.lib")
#define BUF_SIZE 1024
int main(int argc, char* argv[])
{
	WSADATA wsaData;

    SOCKADDR_IN serverAddr; //服务器地址

    SOCKET socketC, socketM;

    char sendbuf[BUF_SIZE] = "";   //发送的数据

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
	printf("\t\t\t这是客户端");
	char recvbuf[BUF_SIZE];
	while(true)
	{
		printf("\n请输入要发送给服务端的值\n");
		scanf("%s",sendbuf);
		send(socketC, sendbuf,sizeof(sendbuf), 0);//发送数据给服务端
		recv(socketC, recvbuf, sizeof(recvbuf), 0);//获取从服务器发来的值
		printf("从服务器获取的\n%s\n", recvbuf);
		//break;
	//	}
	}
    closesocket(socketC);
    WSACleanup();
	printf("请按回车键关闭");
	getchar();
	return 0;
}
