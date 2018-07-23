#pragma once
#include "Singleton.h"
class TimeManager :
	public Singleton<TimeManager>
{
private:
	double lastTime;
	double nowTime;
public:
	void SetNowTime() { nowTime = timeGetTime(); }
	void SetLastTime() { lastTime = timeGetTime(); }
	float GetDeltaTime() { return nowTime - lastTime; }

	TimeManager();
	virtual ~TimeManager();
};

#define TIMEMANAGER TimeManager::GetSingleton()