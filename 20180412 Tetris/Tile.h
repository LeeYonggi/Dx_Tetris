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

	bool WallLeftCollision();				//���� �浹ó��
	bool WallRightCollision();				//������ �浹ó��
	bool WallBottomCollision();				//�Ʒ� �浹ó��
	void Resetborad();						//���� �����͸� ��������
	void Addblocks(POINT _point, int num);	//���� ����� �ǿ� �־���
	void CreateLine();						//������ ������
	void p1operation();						//player1 ���� ��� �̵�
	void p2operation();						//player2 ���� ��� �̵�
	void operation();						//���� ��� �̵�
	void QuikDown(POINT _point);			//�ٷ� �ϰ�
	void FrameCheck();						//��� ������
	void Clearboard_X(int num);				//X�� ä���� ���
	void Clearboard();						//����� �˻�
	void Setmemboard()						//���� ���带 ����
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

