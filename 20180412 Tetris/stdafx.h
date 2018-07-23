#pragma once


#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h>
#include <time.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

#include <stdlib.h>
#include <string.h>
#pragma comment(lib,"ws2_32")

#include <thread>

//framework
#include "Singleton.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "ImageManager.h"
#include "InputManager.h"


//custom
#include "BaseState.h"
#include "TileMoveState.h"
#include "TileEndState.h"
#include "EndCheckState.h"
#include "Tile.h"
#include "LoadScene.h"
#include "MainScene.h"
#include "MultiplayScene.h"
#include "InGame.h"
#include "MainProc.h"


#define DEVICE DXUTGetD3D9Device()
#define SCREEN_X 640
#define SCREEN_Y 480