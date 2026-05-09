#include "GameOverScene.h"
#include "../Scene.h"

void GameOverScene::Init()
{
}

void GameOverScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		Scene::GetInstance().SetNextScene(Scene::SceneType::Score);
	}
}

void GameOverScene::Draw()
{
	//点
	Math::Color color;
	color = { 1,0,0,1 };
	SHADER.m_spriteShader.DrawTriangle(0, 0, 100, 100, 200, 0, &color, true);
}

void GameOverScene::Release()
{
}
