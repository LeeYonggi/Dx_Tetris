#include "DXUT.h"
#include "TileEndState.h"
#include "Tile.h";


void TileEndState::TileUpdate(Tile * tile)
{
	tile->Resetborad();
	tile->Addblocks(tile->GetPoint(), 1);
	tile->operation();
	if (tile->WallBottomCollision())
	{
		delete tile->GetState();
		tile->SetState(new TileMoveState);
	}
	if (frame > 350)
	{
		if (tile->GetState())
			delete tile->GetState();
		tile->SetState(new EndCheckState);
	}
	frame += DXUTGetElapsedTime() * 300;
}

TileEndState::TileEndState()
{
	frame = 0;
}


TileEndState::~TileEndState()
{
}
