#include "GameScene.h"
#include "../Scene.h"
//各オブジェクトのヘッダ―をインクルード
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"

void GameScene::Init()
{
	// 画像の読み込み処理
	bulletTex.Load("Texture/bullet.png");
	expTex.Load("Texture/explosion.png");
	backTex.Load("Texture/back.png");

	// 初期化
	m_player = new Player();
	m_player->Init();
	m_enemy = new Enemy();
	m_enemy->Init();

}

void GameScene::Update()
{
	//更新処理
	m_player->Action();
	m_enemy->Action();

	backY -= 3;
	if (backY < -720)
	{
		backY = 0;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		Scene::GetInstance().SetNextScene(Scene::SceneType::Title);
	}
	
	//背景
	backMat1 = Math::Matrix::CreateTranslation(0, backY, 0);
	backMat2 = Math::Matrix::CreateTranslation(0, backY + 720, 0);

	//更新
	m_player->Update();
	m_enemy->Update();
}

void GameScene::Draw()
{

	//先に書いたものから描画される

	//背景の描画(1枚目)
	SHADER.m_spriteShader.SetMatrix(backMat1);
	SHADER.m_spriteShader.DrawTex(&backTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);

	//背景(2枚目)
	SHADER.m_spriteShader.SetMatrix(backMat2);
	SHADER.m_spriteShader.DrawTex(&backTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);

	//描画
	m_player->Draw();
	m_enemy->Draw();
}

void GameScene::Release()
{
	// 画像の解放処理
	bulletTex.Release();
	expTex.Release();
	backTex.Release();
}
