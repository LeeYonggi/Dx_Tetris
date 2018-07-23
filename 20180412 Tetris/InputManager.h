#pragma once
#define KEY_MAX 256
#define MAX_SIZE_LEN 350

class InputManager :
	public Singleton<InputManager>
{
private:
	bool nowKey[KEY_MAX];
	bool pastKey[KEY_MAX];

public:
	char msg[MAX_SIZE_LEN];
	char ip[100];
	void Init();
	void Update();
	bool IsKeyDown(int i) { return (pastKey[i] == false && nowKey[i] == true) ? true : false; }
	bool IsKeyHold(int i) { return (pastKey[i] == true && nowKey[i] == true) ? true : false; }
	bool IsKeyUp(int i)	  { return (pastKey[i] == true && nowKey[i] == false) ? true : false; }
	
	InputManager();
	virtual ~InputManager() { }
};

#define INPUTMANAGER InputManager::GetSingleton()