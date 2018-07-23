#include "DXUT.h"
#include "Tile.h"

#define COLLISION_CHECK 2
#define NODE_SCALE 1


void Tile::Init()
{
	memset(mainboard, 0, sizeof(mainboard));
	memset(memboard, 0, sizeof(memboard));

	CreateLine();
	point = { 5, 0 };
	kind = futurekind;
	futurekind = rand() % 7;
	frame = 0;
	direction = 0;
	state = new TileMoveState;
	shadowpoint = { 0, 0 };
}
bool Tile::WallLeftCollision() //왼쪽 충돌처리
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (mainboard[i + point.y][j + point.x] == 1)
				if (mainboard[i + point.y][j + point.x - 1] > COLLISION_CHECK)
					return false;
		}
	return true;
}
bool Tile::WallRightCollision() //오른쪽 충돌처리
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (mainboard[i + point.y][j + point.x] == 1)
				if (mainboard[i + point.y][j + point.x + 1] > COLLISION_CHECK)
					return false;
		}
	return true;
}
bool Tile::WallBottomCollision() //아래 충돌처리
{
	for(int i = 0; i < 4; i ++)
		for (int j = 0; j < 4; j++)
		{
			if(mainboard[i + point.y][j + point.x] == 1)
				if (mainboard[i + point.y + 1][j + point.x] > COLLISION_CHECK)
					return false;
		}
	return true;
}
void Tile::Resetborad() //이전 데이터를 삭제해줌
{
	for (int i = 0; i < MAIN_SIZE_Y; i++)
	{
		for (int j = 0; j < MAIN_SIZE_X; j++)
		{
			mainboard[i][j] = 0;
		}
	}
	CreateLine();
}

void Tile::Addblocks(POINT _point, int num) //현재 블록을 판에 넣어줌
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (blocks[kind][direction][i][j] == 1)
				mainboard[i + _point.y][j + _point.x] = num;
		}
	}
}

void Tile::CreateLine() //벽들을 세워줌
{
	memcpy(mainboard, memboard, sizeof(memboard));
	for (int i = 0; i < MAIN_SIZE_Y; i++)
	{
		mainboard[i][0] = 4;
		mainboard[i][MAIN_SIZE_X - 1] = 4;
	}
	for (int i = 0; i < MAIN_SIZE_X; i++)
	{
		mainboard[MAIN_SIZE_Y - 1][i] = 4;
	}
}

void Tile::p1operation() //p1현재 블록 이동
{
	if (INPUTMANAGER->IsKeyDown(0x41) && WallLeftCollision())
	{
		point.x--;
	}
	if (INPUTMANAGER->IsKeyDown(0x44) && WallRightCollision())
	{
		point.x++;
	}
	if (INPUTMANAGER->IsKeyDown(0x57))
	{
		direction++;
		for (int j = 0; j < 4; j++)
		{
			if (point.x + j >= MAIN_SIZE_X - 1)
				point.x--;
			if (point.x <= 1)
				point.x++;
		}
	}
	if (INPUTMANAGER->IsKeyDown(0x53))
	{
		point = shadowpoint;
	}
	if (direction > 3)
		direction = 0;
}

void Tile::p2operation() //p2현재 블록 이동
{
	if (multiplay == true) return;
	if (INPUTMANAGER->IsKeyDown(VK_LEFT) && WallLeftCollision())
	{
		point.x--;
	}
	if (INPUTMANAGER->IsKeyDown(VK_RIGHT) && WallRightCollision())
	{
		point.x++;
	}
	if (INPUTMANAGER->IsKeyDown(VK_UP))
	{
		direction++;
		for (int j = 0; j < 4; j++)
		{
			if (point.x + j >= MAIN_SIZE_X - 1)
				point.x--;
			if (point.x <= 1)
				point.x++;
		}
	}
	if (INPUTMANAGER->IsKeyDown(VK_DOWN))
	{
		point = shadowpoint;
	}
	if (direction > 3)
		direction = 0;
}

void Tile::operation()//현재 블록 이동
{
	switch (side)
	{
	case PLAYER1:
		p1operation();
		break;
	case PLAYER2:
		p2operation();
		break;
	default:
		break;
	}
}

void Tile::QuikDown(POINT _point) //바로 하강
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (mainboard[y + _point.y][x + _point.x] == 0 &&
				blocks[kind][direction][y][x] == 1)
			{
				mainboard[y + _point.y][x + _point.x] = 2;
			}
		}
	}
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (mainboard[y + _point.y][x + _point.x] == 2 ||
				mainboard[y + _point.y][x + _point.x] == 1)
			{
				if (mainboard[y + _point.y + 1][x + _point.x] > COLLISION_CHECK)
				{
					shadowpoint = _point;
					return;
				}
			}
		}
	}
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (mainboard[y + _point.y][x + _point.x] == 2)
				mainboard[y + _point.y][x + _point.x] = 0;
		}
	}
	QuikDown({_point.x, _point.y + 1});
}
void Tile::FrameCheck() //블록 내려감
{
	if (frame > 350)
	{
		point.y += 1;
		frame = 0;
		if (multiplay == true && side == PLAYER_SIDE::PLAYER1)
		{
			char msg[MAX_SIZE_LEN];
			int num = 0;
			for (int i = 0; i < MAIN_SIZE_Y; i++)
			{
				for (int j = 0; j < MAIN_SIZE_X; j++)
				{
					sprintf(&msg[num], "%d", mainboard[i][j]);
					num++;
				}
			}
			send(sock, msg, sizeof(msg), 0); //송신
		}
	}
	frame += DXUTGetElapsedTime() * 300;
}


void Tile::Clearboard_X(int num)
{
	for (int j = 1; j < MAIN_SIZE_X - 1; j++)
	{
		if (memboard[num][j] != 3)
			return;
	}
	for (int j = 1; j < MAIN_SIZE_X - 1; j++)
	{
		memboard[num][j] = 0;
	}
	for (int i = num; i > 0; i--)
	{
		for (int j = 1; j < MAIN_SIZE_X - 1; j++)
		{
			memboard[i][j] = memboard[i - 1][j];
		}
	}
	int random = rand() % (MAIN_SIZE_X - 1) + 1;
	for (int i = 0; i < MAIN_SIZE_Y - 2; i++)
	{
		for (int j = 1; j < MAIN_SIZE_X - 1; j++)
		{
			player->memboard[i][j] = player->memboard[i + 1][j];
		}
	}
	for (int j = 1; j < MAIN_SIZE_X - 1; j++)
	{
		if(j != random)
			player->memboard[MAIN_SIZE_Y - 2][j] = 3;
		else
			player->memboard[MAIN_SIZE_Y - 2][j] = 0;
	}
	player->SetPoint({ player->GetPoint().x, player->GetPoint().y - 1});
}


void Tile::Clearboard()
{
	for (int i = 1; i < MAIN_SIZE_Y - 1; i++)
	{
		Clearboard_X(i);
	}
}


void Tile::Update()
{
	if (side == PLAYER_SIDE::PLAYER2 && multiplay == true)
	{
		int num = 0;
		for (int i = 0; i < MAIN_SIZE_Y; i++)
		{
			for (int j = 0; j < MAIN_SIZE_X; j++)
			{
				mainboard[i][j] = INPUTMANAGER->msg[num] - 48;
				num++;
			}
		}
	}
	else
		state->TileUpdate(this);
}

void Tile::Render() //타일 그리기
{
	DWORD dw;   //좌표를 저장하기 위한 구조채를 선언.
	D3DXVECTOR2 CursorPosition = { 0, 0 };

	string str;
	for (int i = 0; i < MAIN_SIZE_Y; i++)
	{
		for (int j = 0; j < MAIN_SIZE_X; j++)
		{
			float basicpos = (14 + NODE_SCALE);
			CursorPosition = { (float)side * (float)((SCREEN_X * 0.3) + (SCREEN_X * 0.3) + 50) + basicpos +(float)j * basicpos,
				basicpos + (float)i * (14 + NODE_SCALE) };
			if (mainboard[i][j] == 4)
			{
				IMAGEMANAGER->DrawImage("node1", { CursorPosition.x, CursorPosition.y }, NODE_SCALE);
			}
			else if (mainboard[i][j] == 1 || mainboard[i][j] == 3)
			{
				IMAGEMANAGER->DrawImage("node2", { CursorPosition.x, CursorPosition.y }, NODE_SCALE);
			}
			else if (mainboard[i][j] == 2)
			{
				IMAGEMANAGER->DrawImage("node3", { CursorPosition.x, CursorPosition.y }, NODE_SCALE);
			}
			else
			{

			}
		}
	}
	int x = SCREEN_X * 0.5, y = 200;
	if (side == 0)
		y = 100;
	if (side == 1)
		y = SCREEN_Y - 200;
	IMAGEMANAGER->DrawImage("next", { (float)x, (float)y }, 0.5);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (blocks[futurekind][0][i][j] == 1)
				IMAGEMANAGER->DrawImage("node3", {(float)x + (float)(j * 14 * NODE_SCALE), (float)y + (float)(i * 14 * NODE_SCALE) }, NODE_SCALE);
		}
	}
}


void Tile::Release()
{
	delete state;
}


Tile::~Tile()
{

}
