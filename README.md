
Socket，用来实现应用的通信，是应用非常广的一个api，今天就来揭开它的神秘面纱。


![总体流程图](http://upload-images.jianshu.io/upload_images/606862-3476e447d07b243a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



### 客户端
1. 引入头文件
	```
	#include <winsock2.h>
	```
	
2. 初始化socket的DLL

	```
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData
	```

3. 创建套接字

	```
	    SOCKET socket(int domain, int type, int protocol);
	```
- domain 是协议域，包括 
	    - AF_INET 对应 ipv4
	    - AF_INET6 对应 ipv6

- type 是连接类型

	  - SOCK_STREAM，提供面向连接的稳定数据传输，即TCP协议。
	  - SOCK_DGRAM，提供的是数据报(datagram)，使用UDP协议。
	  - protocol，一般设为0，内核会自动匹配。



4. 存储服务器信息

	客户端要去连接服务器，所以应该存储服务器的IP地址和端口号。
	
	这边已经在 netinet/in.h 帮我们实现了一个结构体 struct sockaddr_in 来存储服务器信息。作为函数参数时强制转换为sockaddr。
	```
	struct sockaddr_in {
	    short   sin_family;   // 必须为AF_INET,因为是IPv4;
	    unsigned short   sin_port;    // 存储port No
	    struct in_addr   sin_addr;    //存储IP地址
	    char             sin_zero[8];  
	};
	```

	网络的字节顺序为大端法，我们要想正确通信，就必须统一格式。
	
	那么什么是大小端呢？
	
	大端是高位字节存在低地址中，小端是低位字节存在低地址中。
	
	![](http://upload-images.jianshu.io/upload_images/606862-b9d4700d7bcf5e45.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
	
	因此如果本地端口格式是小端要转为大端。
	
	htons(PORT)就是将本机的字节序转化为网络的字节序。

5. 连接服务器

	```
	int connect(SOCKET sockfd, const struct sockaddr *serv_addr,socklen_t addrlen)
	```
- SOCKET sockfd，本地的socket
- const struct sockaddr *serv_addr， 将SOCKADDR_IN的对象转为 sockaddr 指针
- socklen_t address_len 就是sockaddr的大小

6. 收发消息

	```
	ssize_t send(SOCKET sockfd, const void *buf, size_t len, int flags)
	    
	ssize_t recv(SOCKET sockfd, void *buf, size_t len, int flags)
	
	```
	- SOCKET sockfd，本地的socket描述字
	- const void *buf，字符串指针，数据缓冲区
	- size_t len，接受的长度
	- int flags，通常从设为0

7. 断开

    ```
    int PASCAL FAR closesocket(SOCKET s);
    ```
    关闭套接字

### 服务器

1. 创建服务器套接字

2. 存储服务器信息

3. bind绑定

	将服务器套接字与服务器信息绑定在一起

	```
	int bind(SOCKET socket, const struct sockaddr* address, socklen_t address_len);
	```
	- SOCKET socket，服务器本地的socket
	- const struct sockaddr *address， 将SOCKADDR_IN的对象转为 sockaddr 指针
	- socklen_t address_len 就是sockaddr的大小

4. 监听


	```cpp
	int listen(SOCKET sockfd, int backlog)
	```
	listen()函数可以让套接字进入被动监听状态
	
	sockfd为需要进入监听状态的套接字，backlog 为请求队列的最大长度。
	
	所谓被动监听，是指当没有客户端请求时，套接字就会处于**睡眠**状态，只有当接收到客户端请求时，套接字才会被**唤醒**来响应请求。

5. accept

	用accept来接受客户端的请求，这时候会产生**一个新的套接字**，记重点，新的，之后的通信全部用这个新的套接字，原来的套接字还在监听客户端的请求。

	```cpp
	int accept(SOCKET sockfd, struct sockaddr *addr, socklen_t *addrlen)
	
	```
	- SOCKET sockfd，服务器本地的socket
	- struct sockaddr *addr，用于存储客户端的IP和端口号等
	- socklen_t address_len，描述addr的大小
	
	注意这边的accept是会阻塞的，那么什么是阻塞，就是如果没有接收到，那么我就会一直等在这边，比如我们刚学c语言的scanf函数的时候，它就会阻塞到那里等待用户输入。
	
	包括send和recv也是会阻塞的。

6. 新套接字用来收发信息
7. 关闭套接字

参考资料：

 [1.简单的聊天室实现（上）：通信-SOCKET](https://zhuanlan.zhihu.com/p/24475299)
 
 [2. TCP Socket Programming 學習筆記](https://zake7749.github.io/2015/03/17/SocketProgramming/)
 
 [3. 使用listen()和accept()函数](http://c.biancheng.net/cpp/html/3036.html)
 
 
