#pragma once

//継承
#include"../BaseScene/BaseScene.h"

class GameOverScene : public BaseScene
{
public:
	GameOverScene() { Init(); }
	~GameOverScene() { Release(); }
	void Init()override;
	void Update()override;
	void Draw()override;


private:

	void Release()override;



};