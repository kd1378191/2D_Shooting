#pragma once

class Player;

class GameScene
{
	public:
	GameScene(){}
	~GameScene(){}
	void Init();
	void Update();
	void Draw();
	void Release();

private:

	KdTexture playerTex;
	KdTexture enemyTex;
	KdTexture bulletTex;
	KdTexture expTex;
	KdTexture backTex;

	Player* m_player;

};