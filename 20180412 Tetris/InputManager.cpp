#include "DXUT.h"
#include "InputManager.h"

void InputManager::Init()
{
	memset(nowKey, false, sizeof(nowKey));
	memset(pastKey, false, sizeof(pastKey));

}

void InputManager::Update()
{
	memcpy(pastKey, nowKey, sizeof(nowKey));

	for (int i = 0; i < KEY_MAX; i++)
		nowKey[i] = GetAsyncKeyState(i) & 0x8000;
}

InputManager::InputManager()
{
	Init();
}
