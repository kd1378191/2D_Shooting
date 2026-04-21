#include "GameScene.h"
#include "Player.h"

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

	// テクスチャセット
	m_player->SetTex(&playerTex);
}

void GameScene::Update()
{
	//更新
	m_player->Update();
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
