#pragma once
class MainProc
{
private:
	bool activeTurn;
	COORD size;
	SMALL_RECT rect;
	HANDLE hBuffer[2];
	bool nScreenIndex;


public:
	void Init();
	void Update();
	void Render();
	void Release();
	bool GetActiveTurn() { return activeTurn; }

	MainProc();
	virtual ~MainProc();
};

