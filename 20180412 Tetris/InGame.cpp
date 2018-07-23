#include "DXUT.h"
#include "InGame.h"


void InGame::Init()
{
	tile = new Tile(PLAYER1, false);
	tile2 = new Tile(PLAYER2, false);

	tile->Init();
	tile2->Init();
	tile->SetPlayer(tile2);
	tile2->SetPlayer(tile);
}

void InGame::Update()
{
	tile->Update();
	tile2->Update();
}

void InGame::Render()
{
	tile->Render();
	tile2->Render();
}

void InGame::Release()
{
	tile->Release();
	SAFE_DELETE(tile);
	tile2->Release();
	SAFE_DELETE(tile2);
}

InGame::InGame()
{
}


InGame::~InGame()
{
}
