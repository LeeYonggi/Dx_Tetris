#pragma once
#include "Singleton.h"

class BaseScene
{
public:
	virtual void Init()		PURE;
	virtual void Update()	PURE;
	virtual void Render()	PURE;
	virtual void Release()	PURE;
};

class SceneManager :
	public Singleton<SceneManager>
{
private:
	vector<BaseScene*> v_Scenes;
	int pastScene;
	int updateScene;

public:
	void AddScene(BaseScene *scene);
	void Update();
	void Render();
	void Release();

	SceneManager();
	virtual ~SceneManager();
};

#define SCENEMANAGER SceneManager::GetSingleton()