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
}

void TitleScene::Release()
{
}
