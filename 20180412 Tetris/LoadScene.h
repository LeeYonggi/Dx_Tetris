#pragma once
#include "SceneManager.h"
class LoadScene :
	public BaseScene
{
public:
	void Init();
	void Update();
	void Render();
	void Release();

	LoadScene();
	virtual ~LoadScene();
};

