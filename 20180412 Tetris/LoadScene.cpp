#include "DXUT.h"
#include "LoadScene.h"


void LoadScene::Init()
{
	IMAGEMANAGER->AddImage("next", L"./PNG/next.png");
	IMAGEMANAGER->AddImage("node1", L"./PNG/node1.png");
	IMAGEMANAGER->AddImage("node2", L"./PNG/node2.png");
	IMAGEMANAGER->AddImage("node3", L"./PNG/node3.png");
	IMAGEMANAGER->AddImage("main", L"./PNG/main.png");
	IMAGEMANAGER->AddImage("circle", L"./PNG/circle.png");
}

void LoadScene::Update()
{
	SCENEMANAGER->AddScene(new MainScene);
}

void LoadScene::Render()
{
}

void LoadScene::Release()
{
}

LoadScene::LoadScene()
{
}


LoadScene::~LoadScene()
{
}
