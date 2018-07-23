#pragma once
#include "BaseState.h"

class Tile;
class EndCheckState :
	public BaseState
{
public:
	void TileUpdate(Tile *tile) override;

	EndCheckState();
	virtual ~EndCheckState();
};

