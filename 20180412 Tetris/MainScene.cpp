#include "DXUT.h"
#include "MainScene.h"


void MainScene::Init()
{
	game_state = PLAY;
	point = {9, 6};
}

void MainScene::Update()
{
	switch (game_state)
	{
	case MainScene::PLAY:
		if (INPUTMANAGER->IsKeyDown(VK_SPACE))
			SCENEMANAGER->AddScene(new InGame);
		point = { 150, 200 };
		break;
	case MainScene::MULTIPLAY:
		if (INPUTMANAGER->IsKeyDown(VK_SPACE))
			SCENEMANAGER->AddScene(new MultiplayScene);
		point = { 150, 240 };
		break;
	case MainScene::EXIT:
		if (INPUTMANAGER->IsKeyDown(VK_SPACE))
			exit(0);
		point = { 150, 280 };
		break;
	default:
		break;
	}
	if (INPUTMANAGER->IsKeyDown(VK_DOWN) && game_state < 2)
		game_state++;
	if (INPUTMANAGER->IsKeyDown(VK_UP) && game_state > 0)
		game_state--;
}

void MainScene::Render()
{
	int x = 15, y = 3;
	IMAGEMANAGER->DrawImage("main", { SCREEN_X * 0.5, SCREEN_Y * 0.5 });
	IMAGEMANAGER->DrawImage("circle", { (float)point.x, (float)point.y }, 0.1);
}

void MainScene::Release()
{
}

MainScene::MainScene()
{
	game_state = PLAY;
	point = { 9, 6 };
}


MainScene::~MainScene()
{
}
