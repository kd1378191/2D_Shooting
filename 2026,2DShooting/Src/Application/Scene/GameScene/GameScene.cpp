#include "GameScene.h"
#include "Player.h"
#include "Enemy.h"

void GameScene::Init()
{
	// 画像の読み込み処理
	playerTex.Load("Texture/player.png");
	enemyTex.Load("Texture/enemy.png");
	bulletTex.Load("Texture/bullet.png");
	expTex.Load("Texture/explosion.png");
	backTex.Load("Texture/back.png");
	// 初期化
	m_player = new Player();
	m_player->Init();
	m_enemy = new Enemy();
	m_enemy->Init();

	// テクスチャセット
	m_player->SetTex(&playerTex);
	m_enemy->SetTex(&enemyTex);
}

void GameScene::Update()
{
	//更新処理
	m_player->Action();
	m_enemy->Action();

	//更新
	m_player->Update();
	m_enemy->Update();
}

void GameScene::Draw()
{
	//描画
	m_player->Draw();
}

void GameScene::Release()
{
	// 画像の解放処理
	playerTex.Release();
	enemyTex.Release();
	bulletTex.Release();
	expTex.Release();
	backTex.Release();
}
