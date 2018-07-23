#pragma once
#include "SceneManager.h"


class MultiplayScene :
	public BaseScene
{
private:
	SOCKET sock;
	Tile *tile;
	Tile *tile2;
	thread m_thread;

public:
	void Init();
	void Update();
	void Render();
	void Release();

	MultiplayScene();
	virtual ~MultiplayScene();
};

