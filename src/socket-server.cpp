#include <stdio.h>
#include <winsock2.h>  // WINSOCK.H 这个是 WINSOCK API 的头文件, WIN2K 以上支持 WINSOCK2,所以 可以用 WINSOCK2.H 

#pragma comment(lib, "WS2_32.lib") // Ws2_32.lib ( WINSOCK API 连接库文件).
#define BUF_SIZE 1024

// -----------------------------
int main(int argc, char* argv[])
{
    WSADATA wsaData; // WSAStartup就是为了向操作系统说明
    // 我们要用哪个库文件，让该库文件与当前的应用程序绑定，从而就可以调用该版本的socket的各种函数了。
    SOCKET  socketL;  // socket for listening
    SOCKET  socketC;  // socket for Communication
    SOCKADDR_IN serverAddr;
    int nRet = -1;
    char recvbuf[BUF_SIZE];

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("WSAStartup failed!\n");
        return 1;
    }

    socketL = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // 三个参数为协议族，类型，协议 ipv4 提供面向连接的稳定数据传输，即TCP协议。
    // 程序员把类型、ip地址、端口填充sockaddr_in结构体，然后强制转换成sockaddr，
    // 作为参数传递给系统调用函数

    serverAddr.sin_family      = AF_INET;
    serverAddr.sin_port        = htons(5678);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // 所有地址

    bind(socketL, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    listen(socketL, 5);

    socketC = accept(socketL, NULL, NULL);  // 从客户端获取的socket
    printf("\t\t\t这是服务端\n");
    
    if (socketC != INVALID_SOCKET)
    {
        nRet = recv(socketC, recvbuf, sizeof(recvbuf), 0);
        if (nRet > 0)
            printf("\n从客户端获取%s\n", recvbuf);
    }
	
    while(1)
    {
	printf("\n请输入给客户端的值\n");
	scanf("%s",recvbuf);
	send(socketC, recvbuf,sizeof(recvbuf), 0);  // 发送数据给客户端
	recv(socketC, recvbuf, sizeof(recvbuf), 0);
	printf("\n从客户端获取%s\n", recvbuf);
    }

    closesocket(socketC);
    closesocket(socketL);	
    WSACleanup();
    printf("请按回车键关闭");
    getchar();
    return 0;
}
