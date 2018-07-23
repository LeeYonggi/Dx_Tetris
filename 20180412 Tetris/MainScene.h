#pragma once
#include "SceneManager.h"
class MainScene :
	public BaseScene
{
private:
	enum GAME_STATE
	{
		PLAY,
		MULTIPLAY,
		EXIT
	};
	int game_state;
	POINT point;
public:
	void Init();
	void Update();
	void Render();
	void Release();

	MainScene();
	virtual ~MainScene();
};

