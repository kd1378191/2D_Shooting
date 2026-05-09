#include "ClearScene.h"
#include "../Scene.h"

void ClearScene::Init()
{
}

void ClearScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		Scene::GetInstance().SetNextScene(Scene::SceneType::Score);
	}
}

void ClearScene::Draw()
{
	//丸
	Math::Color color;
	color = { 1,1,1,1 };//RGB
	SHADER.m_spriteShader.DrawCircle(0, 0, 100, &color, true);
}

void ClearScene::Release()
{
}
