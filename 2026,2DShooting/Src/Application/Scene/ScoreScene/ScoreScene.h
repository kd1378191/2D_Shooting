#pragma once

//継承
#include"../BaseScene/BaseScene.h"

class ScoreScene : public BaseScene
{
public:
	ScoreScene() { Init(); }
	~ScoreScene() { Release(); }
	void Init()override;
	void Update()override;
	void Draw()override;


private:

	void Release()override;



};