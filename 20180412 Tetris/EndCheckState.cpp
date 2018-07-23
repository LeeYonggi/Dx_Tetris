#include "DXUT.h"
#include "EndCheckState.h"
#include "Tile.h"


void EndCheckState::TileUpdate(Tile * tile)
{
	tile->Setmemboard();
	if (tile->GetPoint().y < 1)
	{

	}
	else
	{
		tile->SetBasic({5, 0}, rand() % 7);
		tile->Clearboard();
		if (tile->GetState())
			delete tile->GetState();
		tile->SetState(new TileMoveState);
	}
}

EndCheckState::EndCheckState()
{
}


EndCheckState::~EndCheckState()
{
}
