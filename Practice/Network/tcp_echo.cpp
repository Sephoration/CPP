#include <iostream>
#include <string>
#include <cstring>

// TCP Echo 服务器/客户端练习 (POSIX socket)

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket close
#endif

const int PORT = 8888;
const int BUFFER_SIZE = 1024;

#ifdef _WIN32
class WSAInit {
public:
    WSAInit() {
        WSADATA wsa;
        WSAStartup(MAKEWORD(2, 2), &wsa);
    }
    ~WSAInit() { WSACleanup(); }
};
#endif

int runServer() {
#ifdef _WIN32
    WSAInit wsa;
#endif

    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET) {
        std::cerr << "创建 socket 失败" << std::endl;
        return 1;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(server, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cerr << "绑定端口失败" << std::endl;
        closesocket(server);
        return 1;
    }

    listen(server, 5);
    std::cout << "服务器监听 0.0.0.0:" << PORT << std::endl;

    sockaddr_in client{};
#ifdef _WIN32
    int clientLen = sizeof(client);
#else
    socklen_t clientLen = sizeof(client);
#endif

    SOCKET client_sock = accept(server, (sockaddr*)&client, &clientLen);
    if (client_sock == INVALID_SOCKET) {
        std::cerr << "接受连接失败" << std::endl;
        closesocket(server);
        return 1;
    }

    std::cout << "客户端已连接" << std::endl;
    char buffer[BUFFER_SIZE];

    while (true) {
        int bytes = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);
        if (bytes <= 0) break;
        buffer[bytes] = '\0';
        std::cout << "收到: " << buffer << std::endl;
        send(client_sock, buffer, bytes, 0);
    }

    closesocket(client_sock);
    closesocket(server);
    std::cout << "服务器关闭" << std::endl;
    return 0;
}

int runClient() {
#ifdef _WIN32
    WSAInit wsa;
#endif

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "创建 socket 失败" << std::endl;
        return 1;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cerr << "连接服务器失败" << std::endl;
        closesocket(sock);
        return 1;
    }

    std::cout << "已连接到服务器, 输入消息 (输入 quit 退出):" << std::endl;
    char buffer[BUFFER_SIZE];

    while (true) {
        std::cin.getline(buffer, BUFFER_SIZE);
        if (strcmp(buffer, "quit") == 0) break;

        send(sock, buffer, strlen(buffer), 0);
        int bytes = recv(sock, buffer, BUFFER_SIZE - 1, 0);
        if (bytes <= 0) break;
        buffer[bytes] = '\0';
        std::cout << "回声: " << buffer << std::endl;
    }

    closesocket(sock);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "client") == 0) {
        return runClient();
    }
    return runServer();
}
