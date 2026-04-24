#pragma once

class Player;
class Enemy;

class GameScene
{
	public:
	GameScene(){}
	~GameScene() { Release(); }
	void Init();
	void Update();
	void Draw();
	

private:

	void Release();

	KdTexture playerTex;
	KdTexture enemyTex;
	KdTexture bulletTex;
	KdTexture expTex;
	KdTexture backTex;

	//背景
	Math::Matrix backMat1;
	Math::Matrix backMat2;
	float backY;

	Player* m_player;
	Enemy* m_enemy;

};