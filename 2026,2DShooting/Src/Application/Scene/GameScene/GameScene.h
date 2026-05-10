#pragma once

//継承
#include"../BaseScene/BaseScene.h"

class Player;
class Enemy;

class GameScene : public BaseScene
{
public:
	GameScene() { Init(); }
	~GameScene() { Release(); }
	void Init()override;
	void Update()override;
	void Draw()override;


private:

	void Release()override;


	KdTexture bulletTex;
	KdTexture expTex;
	KdTexture backTex;

	//背景
	Math::Matrix backMat1;
	Math::Matrix backMat2;
	float backY;

	Player* m_player;
	Enemy* m_enemy;
	static const int m_enemyNum = 5;



};