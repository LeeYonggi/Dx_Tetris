#pragma once
#include "BaseState.h"
class Tile;
class TileMoveState :
	public BaseState
{
public:
	void TileUpdate(Tile *tile) override;

	TileMoveState();
	virtual ~TileMoveState();
};

