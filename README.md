# 深入浅出 Socket

Socket，用来实现应用的通信，是应用非常广的一个 api，今天就来揭开它的神秘面纱。

![总体流程图](http://upload-images.jianshu.io/upload_images/606862-3476e447d07b243a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## 1. 客户端

### 1.1 引入头文件

```cpp
#include <winsock2.h>
```

### 1.2 初始化 socket 的 DLL

```cpp
WSADATA wsaData;
WSAStartup(MAKEWORD(2, 2), &wsaData
```

### 1.3 创建套接字

```cpp
 SOCKET socket(int domain, int type, int protocol);
```

- domain 是协议域，包括 - AF_INET 对应 ipv4 - AF_INET6 对应 ipv6

- type 是连接类型
  - SOCK_STREAM，提供面向连接的稳定数据传输，即 TCP 协议。
  - SOCK_DGRAM，提供的是数据报 (datagram)，使用 UDP 协议。
  - protocol，一般设为 0，内核会自动匹配。

### 1.4 存储服务器信息

客户端要去连接服务器，所以应该存储服务器的 IP 地址和端口号。

这边已经在 netinet/in.h 帮我们实现了一个结构体 struct sockaddr_in 来存储服务器信息。作为函数参数时强制转换为 sockaddr。

```cpp
struct sockaddr_in
{
    short   sin_family;   		 // 必须为AF_INET,因为是IPv4;
    unsigned short   sin_port;   // 存储port No
    struct in_addr   sin_addr;   //存储IP地址
    char   sin_zero[8];
};
```

网络的字节顺序为大端法，我们要想正确通信，就必须统一格式。

那么什么是大小端呢？

大端是高位字节存在低地址中，小端是低位字节存在低地址中。

![](http://upload-images.jianshu.io/upload_images/606862-b9d4700d7bcf5e45.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

因此如果本地端口格式是小端要转为大端。

htons(PORT) 就是将本机的字节序转化为网络的字节序。

### 1.5 连接服务器

```cpp
int connect(SOCKET sockfd, const struct sockaddr *serv_addr,socklen_t addrlen)
```

- SOCKET sockfd，本地的 socket
- const struct sockaddr \*serv_addr， 将 SOCKADDR_IN 的对象转为 sockaddr 指针
- socklen_t address_len 就是 sockaddr 的大小

### 1.6 收发消息

```cpp
ssize_t send(SOCKET sockfd, const void *buf, size_t len, int flags)
ssize_t recv(SOCKET sockfd, void *buf, size_t len, int flags)
```

- SOCKET sockfd，本地的 socket 描述字
- const void \*buf，字符串指针，数据缓冲区
- size_t len，接受的长度
- int flags，通常从设为 0

### 1.7 断开

```cpp
int PASCAL FAR closesocket(SOCKET s);
```

关闭套接字

## 2. 服务器

### 2.1 创建服务器套接字

### 2.2 存储服务器信息

### 2.3 bind 绑定

将服务器套接字与服务器信息绑定在一起

```cpp
int bind(SOCKET socket, const struct sockaddr* address, socklen_t address_len);
```

- SOCKET socket，服务器本地的 socket
- const struct sockaddr \*address， 将 SOCKADDR_IN 的对象转为 sockaddr 指针
- socklen_t address_len 就是 sockaddr 的大小

### 2.4 监听

```cpp
int listen(SOCKET sockfd, int backlog)
```

listen() 函数可以让套接字进入被动监听状态

sockfd 为需要进入监听状态的套接字，backlog 为请求队列的最大长度。

所谓被动监听，是指当没有客户端请求时，套接字就会处于**睡眠**状态，只有当接收到客户端请求时，套接字才会被**唤醒**来响应请求。

### 2.5 accept

用 accept 来接受客户端的请求，这时候会产生**一个新的套接字**，记重点，新的，之后的通信全部用这个新的套接字，原来的套接字还在监听客户端的请求。

```cpp
int accept(SOCKET sockfd, struct sockaddr *addr, socklen_t *addrlen)
```

- SOCKET sockfd，服务器本地的 socket
- struct sockaddr \*addr，用于存储客户端的 IP 和端口号等
- socklen_t address_len，描述 addr 的大小

注意这边的 accept 是会阻塞的，那么什么是阻塞，就是如果没有接收到，那么我就会一直等在这边，比如我们刚学 c 语言的 scanf 函数的时候，它就会阻塞到那里等待用户输入。

包括 send 和 recv 也是会阻塞的。

### 2.6 新套接字用来收发信息

### 2.7 关闭套接字

## 参考资料：

- [简单的聊天室实现（上）：通信-SOCKET](https://zhuanlan.zhihu.com/p/24475299)

- [TCP Socket Programming 學習筆記](https://zake7749.github.io/2015/03/17/SocketProgramming/)

- [使用 listen()和 accept()函数](http://c.biancheng.net/cpp/html/3036.html)
