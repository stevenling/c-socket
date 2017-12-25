#include <stdio.h>
#include <winsock2.h>  //WINSOCK.H(�����WINSOCK API��ͷ�ļ�,WIN2K����֧��WINSOCK2,���� 
					   //������WINSOCK2.H); 

#pragma comment(lib, "WS2_32.lib")//Ws2_32.lib(WINSOCK API���ӿ��ļ�).

#define BUF_SIZE 1024

int main(int argc, char* argv[])
{
	WSADATA wsaData; //WSAStartup����Ϊ�������ϵͳ˵��
	//����Ҫ���ĸ����ļ����øÿ��ļ��뵱ǰ��Ӧ�ó���󶨣��Ӷ��Ϳ��Ե��øð汾��socket�ĸ��ֺ����ˡ�
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
	//��������ΪЭ���壬���ͣ�Э�� ipv4 �ṩ�������ӵ��ȶ����ݴ��䣬��TCPЭ�顣

	//����Ա�����͡�ip��ַ���˿����sockaddr_in�ṹ�壬Ȼ��ǿ��ת����sockaddr��
	//��Ϊ�������ݸ�ϵͳ���ú���

    serverAddr.sin_family      = AF_INET;
    serverAddr.sin_port        = htons(5678);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); //���е�ַ

    bind(socketL, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

    listen(socketL, 5);

    socketC = accept(socketL, NULL, NULL);//�ӿͻ��˻�ȡ��socket
	printf("\t\t\t���Ƿ����\n");
    if (socketC != INVALID_SOCKET)
    {
        nRet = recv(socketC, recvbuf, sizeof(recvbuf), 0);
        if (nRet > 0)
            printf("\n�ӿͻ��˻�ȡ%s\n", recvbuf);

    }
	//printf("%s ", recvbuf);
	
	while(1)
	{
		printf("\n��������ͻ��˵�ֵ\n");
		scanf("%s",recvbuf);
		send(socketC, recvbuf,sizeof(recvbuf), 0);//�������ݸ��ͻ���
		recv(socketC, recvbuf, sizeof(recvbuf), 0);
		printf("\n�ӿͻ��˻�ȡ%s\n", recvbuf);
	}


    closesocket(socketC);
    closesocket(socketL);	
    WSACleanup();

	printf("�밴�س����ر�");
	getchar();
	return 0;
}
