#pragma once
class InGame :
	public BaseScene
{
private:
	Tile *tile;
	Tile *tile2;

public:
	void Init();
	void Update();
	void Render();
	void Release();

	InGame();
	virtual ~InGame();
};

