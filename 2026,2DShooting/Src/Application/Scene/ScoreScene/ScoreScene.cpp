#include "ScoreScene.h"

#include "../Scene.h"

void ScoreScene::Init()
{
}

void ScoreScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		Scene::GetInstance().SetNextScene(Scene::SceneType::Title);
	}
}

void ScoreScene::Draw()
{
	Math::Color color;
	color = { 1,1,1,1 };//RGB
	SHADER.m_spriteShader.DrawLine(0, 0, 1.0f, 1.0f, &color);
}

void ScoreScene::Release()
{
}
