#pragma once

class Tile;
class BaseState
{
public:
	virtual void TileUpdate(Tile *tile) = 0;

	BaseState();
	virtual ~BaseState();
};

