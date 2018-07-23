#include "DXUT.h"
#include "MainProc.h"
#include <fstream>


void MainProc::Init()
{
	srand(time(NULL));
	ifstream file("./data/ipport.txt");

	file.getline(INPUTMANAGER->ip, 100);

	SCENEMANAGER->AddScene(new LoadScene);
}

void MainProc::Update()
{
	SCENEMANAGER->Update();
	INPUTMANAGER->Update();
}

void MainProc::Render()
{
	IMAGEMANAGER->sprite->Begin(D3DXSPRITE_ALPHABLEND);
	
	SCENEMANAGER->Render();

	IMAGEMANAGER->sprite->End();
}

void MainProc::Release()
{
	SCENEMANAGER->Release();
	INPUTMANAGER->ReleaseSingleton();
	TIMEMANAGER->ReleaseSingleton();
	IMAGEMANAGER->ReleaseSingleton();
}

MainProc::MainProc()
{
	activeTurn = true;
}


MainProc::~MainProc()
{
}
