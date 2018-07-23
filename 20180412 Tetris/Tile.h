#pragma once

#define MAIN_SIZE_X 13
#define MAIN_SIZE_Y 24

enum PLAYER_SIDE
{
	PLAYER1,
	PLAYER2
};

class Tile
{
private:
	int blocks[7][4][4][4] = {
		{ { 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 },{ 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 },
		{ 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 },{ 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 } },
		{ { 0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0 },{ 0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0 },
		{ 0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0 },{ 0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0 } },
		{ { 0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0 },{ 0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0 },
		{ 0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0 },{ 0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0 } },
		{ { 0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0 },{ 0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0 },
		{ 0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0 },{ 0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0 } },
		{ { 0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0 },{ 0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0 },
		{ 0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0 },{ 0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0 } },
		{ { 0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0 },{ 0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0 },
		{ 0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0 },{ 0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0 } },
		{ { 0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0 },{ 0,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0 },
		{ 0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0 },{ 0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0 } }
	};
	int mainboard[MAIN_SIZE_Y][MAIN_SIZE_X];
	int memboard[MAIN_SIZE_Y][MAIN_SIZE_X];
	POINT point;
	POINT shadowpoint;
	float frame;
	int kind;
	int futurekind;
	int direction;
	BaseState *state;
	Tile *player;
	int side;
	bool multiplay;
	SOCKET sock;

public:
	void Init();
	void Update();
	void Render();
	void Release();

	bool WallLeftCollision();				//왼쪽 충돌처리
	bool WallRightCollision();				//오른쪽 충돌처리
	bool WallBottomCollision();				//아래 충돌처리
	void Resetborad();						//이전 데이터를 삭제해줌
	void Addblocks(POINT _point, int num);	//현재 블록을 판에 넣어줌
	void CreateLine();						//벽들을 세워줌
	void p1operation();						//player1 현재 블록 이동
	void p2operation();						//player2 현재 블록 이동
	void operation();						//현재 블록 이동
	void QuikDown(POINT _point);			//바로 하강
	void FrameCheck();						//블록 내려감
	void Clearboard_X(int num);				//X를 채웠을 경우
	void Clearboard();						//모든줄 검사
	void Setmemboard()						//현재 보드를 저장
	{ 
		memcpy(memboard, mainboard, sizeof(memboard)); 
		for (int i = 0; i < MAIN_SIZE_Y; i++)
		{
			for (int j = 0; j < MAIN_SIZE_X; j++)
			{
				if (memboard[i][j] == 1)
					memboard[i][j] = 3;
			}
		}
	} 
	void SetPlayer(Tile	*tile)
	{
		player = tile;
	}
	void SetState(BaseState *_state)
	{
		state = _state;
	}
	void SetBasic(POINT _point, int _kind)
	{
		point = _point;
		kind = futurekind;
		futurekind = _kind;
	}
	void SetPoint(POINT _point)
	{
		point = _point;
	}
	auto Getmainboard()
	{
		return mainboard;
	}
	void SetSock(SOCKET _sock)
	{
		sock = _sock;
	}
	POINT GetPoint() { return point; }
	BaseState *GetState() { return state; }

	Tile(PLAYER_SIDE _side, bool _multiplay)
	{
		futurekind = rand() % 7;
		side = _side;
		multiplay = _multiplay;
	}
	virtual ~Tile();
};

