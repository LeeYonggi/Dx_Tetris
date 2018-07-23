#pragma once
#include "BaseState.h"


class Tile;
class TileEndState :
	public BaseState
{
private:
	float frame;

public:
	void TileUpdate(Tile *tile) override;

	TileEndState();
	virtual ~TileEndState();
};

