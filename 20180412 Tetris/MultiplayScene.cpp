#include "DXUT.h"
#include "MultiplayScene.h"

#define SERV_IP "192.168.31.170"

void RecvThreadPoint(SOCKET param);

SOCKET SetTCPServer()
{
	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//家南 积己
	if (sock == INVALID_SOCKET)
		SCENEMANAGER->AddScene(new MainScene);

	SOCKADDR_IN servaddr = { 0 };//家南 林家
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(INPUTMANAGER->ip);
	servaddr.sin_port = htons(10200);

	int re = 0;
	if (connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
	{
		SCENEMANAGER->AddScene(new MainScene);
		return 0;
	}

	return sock;
}
void RecvThreadPoint(SOCKET param)
{
	SOCKET sock = param;

	SOCKADDR_IN cliaddr = { 0 };
	int len = sizeof(cliaddr);

	while (true)
	{
		if (recv(sock, INPUTMANAGER->msg, MAX_SIZE_LEN, 0) == SOCKET_ERROR)
		{
			int a = WSAGetLastError();
			break;
		}
	}
	closesocket(sock);
}

void MultiplayScene::Init()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	sock = SetTCPServer();
	m_thread = thread(([&]() { RecvThreadPoint(sock); }));

	tile = new Tile(PLAYER1, true);
	tile2 = new Tile(PLAYER2, true);
	tile->SetSock(sock);

	tile->Init();
	tile2->Init();
	tile->SetPlayer(tile2);
	tile2->SetPlayer(tile);
}

void MultiplayScene::Update()
{
	tile->Update();
	tile2->Update();
}

void MultiplayScene::Render()
{
	tile->Render();
	tile2->Render();
}

void MultiplayScene::Release()
{
	closesocket(sock);
	tile->Release();
	SAFE_DELETE(tile);
	tile2->Release();
	SAFE_DELETE(tile2);
}

MultiplayScene::MultiplayScene()
{
}


MultiplayScene::~MultiplayScene()
{
}
