#include "../main.h"
#include "Scene.h"
//各シーンのヘッダ―をインクルード
#include"TitleScene/TitleScene.h"
#include"GameScene/GameScene.h"
#include"GameOverScene/GameOverScene.h"
#include"ClearScene/ClearScene.h"
#include"ScoreScene/ScoreScene.h"

void Scene::Draw2D()
{
	//先に書いたものから描画される
	m_currentScene->Draw();
}

void Scene::PreUpdate()
{
	//シーン切替
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}
}

//1秒間に60回のペースで繰り返される(60fps)
void Scene::Update()
{
	//シーン切替の処理
	PreUpdate();
	m_currentScene->Update();

}

//最初の1フレームで実行される
void Scene::Init()//ここはゲーム開始したとき最初に一度だけ実行される
{
	ChangeScene(m_currentSceneType);
}

//最後の1フレームで実行される
void Scene::Release()
{
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}

void Scene::ChangeScene(SceneType _sceneType)
{
	//次のシーンを作成
	switch (_sceneType)
	{
	case SceneType::Title:
		m_currentScene = std::make_shared<TitleScene>();
		break;

	case SceneType::Game:
		m_currentScene = std::make_shared<GameScene>();
		break;

	case SceneType::GameOver:
		m_currentScene = std::make_shared<GameOverScene>();
		break;

	case SceneType::Clear:
		m_currentScene = std::make_shared<ClearScene>();
		break;
	case SceneType::Score:
		m_currentScene = std::make_shared<ScoreScene>();
		break;

	}

	//フラグを更新
	m_currentSceneType = _sceneType;
}

//void Scene::Reset()
//{
//	//リセット
//	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
//	{
//		//自機
//		playerFlg = 1;
//		playerX = 0;
//		playerY = -200;
//
//		//敵
//		for (int e = 0;e < enemyNum;e++) {
//			enemyFlg[e] = 1;
//			enemyX[e] = rand() % rand() % (1280 + 1 - 64) - (640 - 32);
//			enemyY[e] = 360 + 32;
//		}
//
//		score = 0;
//	}
//
//}

//void Scene::Expiosion(float x, float y)
//{
//
//	//爆発発生!
//	for (int ex = 0;ex < exNum;ex++) {
//		if (expFlg[ex] == 0) {
//			expFlg[ex] = 1;
//			expX[ex] = x;
//			expY[ex] = y;
//			expAnimCnt[ex] = 0;//アニメーション１コマ目から
//
//			//1つだけ生成
//			break;
//		}
//	}
//
//}
