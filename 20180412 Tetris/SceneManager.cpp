#include "DXUT.h"
#include "SceneManager.h"


void SceneManager::AddScene(BaseScene * scene)
{
	v_Scenes.push_back(scene);
	updateScene = v_Scenes.size() - 1;
}

void SceneManager::Update()
{
	if (pastScene != updateScene)
	{
		if (pastScene != -1)
			v_Scenes[pastScene]->Release();
		v_Scenes[updateScene]->Init();
		v_Scenes[updateScene]->Update();
		pastScene = updateScene;
		return;
	}
	v_Scenes[updateScene]->Update();
}

void SceneManager::Render()
{
	v_Scenes[pastScene]->Render();
}

void SceneManager::Release()
{
	for (auto iter : v_Scenes)
	{
		if (iter)
			iter->Release();
		SAFE_DELETE(iter);
	}
	v_Scenes.clear();
}

SceneManager::SceneManager()
{
	pastScene = -1;
	updateScene = 0;
}


SceneManager::~SceneManager()
{
	Release();
}
