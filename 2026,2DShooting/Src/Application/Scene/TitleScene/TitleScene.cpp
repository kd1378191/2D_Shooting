#include "TitleScene.h"

#include "../Scene.h"

void TitleScene::Init()
{
}

void TitleScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		Scene::GetInstance().SetNextScene(Scene::SceneType::Game);
	}
}

void TitleScene::Draw()
{
	//四角
	Math::Color color;
	color = { 1,0.5f,1,1 };//RGB
	SHADER.m_spriteShader.DrawBox(0, 0, 320, 180, &color, true);
}

void TitleScene::Release()
{
}
