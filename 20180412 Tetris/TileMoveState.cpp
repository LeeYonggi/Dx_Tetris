#include "DXUT.h"
#include "TileMoveState.h"
#include "Tile.h";


void TileMoveState::TileUpdate(Tile * tile)
{
	tile->FrameCheck();
	tile->operation();
	tile->Resetborad();
	tile->QuikDown(tile->GetPoint());
	tile->Addblocks(tile->GetPoint(), 1);
	if (tile->WallBottomCollision() == false)
	{
		if (tile->GetState())
			delete tile->GetState();
		tile->SetState(new TileEndState);
	}
}

TileMoveState::TileMoveState()
{
}


TileMoveState::~TileMoveState()
{
}
