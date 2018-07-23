// 20180523TetrisServ.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#define PORT_NUM	10200
#define BLOG_SIZE	5
#define MAX_MSG_LEN 350

void Error_handling(const char *str)
{
	fputs(str, stderr);
	fputc('\n', stderr);

	exit(1);
}
SOCKET SetTCPServer(short pnum, int blog);
void EventLoop(SOCKET sock);

int main()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		Error_handling("WSAStartup() error!");
	SOCKET serv_sock = SetTCPServer(PORT_NUM, BLOG_SIZE);

	EventLoop(serv_sock);
    return 0;
}

SOCKET SetTCPServer(short pnum, int blog)
{
	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
		Error_handling("socket() error!");

	SOCKADDR_IN servaddr = { 0 };
	servaddr.sin_family = AF_INET;
	servaddr.sin_port	= htons(PORT_NUM);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 

	if (bind(sock, (SOCKADDR*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR)
		Error_handling("bind() error!");

	if (listen(sock, blog) == SOCKET_ERROR)
		Error_handling("listen() error!");

	return sock;
}
SOCKET sock_base[FD_SETSIZE];
HANDLE hev_base[FD_SETSIZE];

int cnt = 0;

HANDLE AddNetworkEvent(SOCKET sock, long net_event);
void AcceptProc(int index);
void ReadProc(int index);
void CloseProc(int index);

void EventLoop(SOCKET sock)
{
	AddNetworkEvent(sock, FD_ACCEPT);

	//std::thread subthread;
	while (true)
	{
		int index = WSAWaitForMultipleEvents(cnt, hev_base, false, INFINITE, false);
		WSANETWORKEVENTS net_event;
		WSAEnumNetworkEvents(sock_base[index], hev_base[index], &net_event);
		switch (net_event.lNetworkEvents)
		{
		case FD_ACCEPT: 
			AcceptProc(index);
			break;
		case FD_READ:	
			ReadProc(index);
			break;
		case FD_CLOSE:  
			CloseProc(index);
			break;
		default:
			break;
		}
	}
}

 HANDLE AddNetworkEvent(SOCKET sock, long net_event)
{
	HANDLE hev = WSACreateEvent();

	sock_base[cnt] = sock;
	hev_base[cnt] = hev;

	cnt++;

	WSAEventSelect(sock, hev, net_event);

	return hev;
}
 void AcceptProc(int index)
{
	SOCKADDR_IN clnt_addr = {0};
	SOCKET clnt_sock;
	int clnt_size = sizeof(clnt_addr);

	clnt_sock = accept(sock_base[0], (SOCKADDR*)&clnt_addr, &clnt_size);
	if (clnt_sock == INVALID_SOCKET)
		Error_handling("clntaccept() error!");
	if (cnt == FD_SETSIZE)
	{
		std::cout << "방이 꽉차서 " << inet_ntoa(clnt_addr.sin_addr) << ": " << ntohs(clnt_addr.sin_port)
			<< "입장하지 못하였음" << std::endl;
		closesocket(clnt_sock);
		return;
	}
	AddNetworkEvent(clnt_sock, FD_READ | FD_CLOSE);
	std::cout << inet_ntoa(clnt_addr.sin_addr) << ": " << ntohs(clnt_addr.sin_port) << "입장" << std::endl;
}

void ReadProc(int index)
{
	char msg[1000];
	recv(sock_base[index], msg, strlen(msg), 0);

	SOCKADDR_IN clnt_addr = { 0 };
	int clnt_size = sizeof(clnt_addr);
	getpeername(sock_base[index], (SOCKADDR *)&clnt_addr, &clnt_size);
	
	if(index == 1)
		send(sock_base[2], msg, strlen(msg), 0);
	else
		send(sock_base[1], msg, strlen(msg), 0);
}

void CloseProc(int index)
{
	SOCKADDR_IN clnt_addr = {0};
	int clnt_size = sizeof(clnt_addr);

	getpeername(sock_base[index], (SOCKADDR*)&clnt_addr, &clnt_size);
	std::cout << "[" << inet_ntoa(clnt_addr.sin_addr) << ": " << ntohs(clnt_addr.sin_port) << "]" << "님이 나가셨습니다." << std::endl;

	closesocket(sock_base[index]);
	WSACloseEvent(hev_base[index]);

	cnt--;
	sock_base[index] = {0};
	hev_base[index] = {0};

	char msg[MAX_MSG_LEN];
	sprintf(msg, "[%s: %d]님이 나가셨습니다.\n", inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));
	for (int i = 0; i < cnt; i++)
	{
		send(sock_base[i], msg, strlen(msg), 0);
	}
}
