#include "GameScene.h"
#include "../Scene.h"
//使うものをinclude
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"

void GameScene::Init()
{
	// 画像のロード
	bulletTex.Load("Texture/bullet.png");
	expTex.Load("Texture/explosion.png");
	backTex.Load("Texture/back.png");

	//初期化
	m_player = new Player();
	m_player->Init();
	m_enemy = new Enemy[m_enemyNum];
	for (int i = 0; i < m_enemyNum; i++)
	{
		m_enemy[i].Init();
	}

}

void GameScene::Update()
{
	//プレイヤー
	m_player->Action();
	//エネミー
	for (int i = 0; i < m_enemyNum; i++)
	{
		m_enemy[i].Action();
	}
	//背景
	backY -= 3;
	if (backY < -720)
	{
		backY = 0;
	}
	//シーン切り替え
	if (GetAsyncKeyState('1') & 0x8000)
	{
		Scene::GetInstance().SetNextScene(Scene::SceneType::GameOver);
	}
	if (GetAsyncKeyState('2') & 0x8000)
	{
		Scene::GetInstance().SetNextScene(Scene::SceneType::Clear);
	}

	//背景の行列
	backMat1 = Math::Matrix::CreateTranslation(0, backY, 0);
	backMat2 = Math::Matrix::CreateTranslation(0, backY + 720, 0);

	//行列
	m_player->Update();
	for (int i = 0; i < m_enemyNum; i++)
	{
		m_enemy[i].Update();
	}
}

void GameScene::Draw()
{


	//背景1
	SHADER.m_spriteShader.SetMatrix(backMat1);
	SHADER.m_spriteShader.DrawTex(&backTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);

	//背景2
	SHADER.m_spriteShader.SetMatrix(backMat2);
	SHADER.m_spriteShader.DrawTex(&backTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);

	//描画
	m_player->Draw();
	for (int i = 0; i < m_enemyNum; i++)
	{
		m_enemy[i].Draw();
	}
}

void GameScene::Release()
{
	//解放
	bulletTex.Release();
	expTex.Release();
	backTex.Release();
}
