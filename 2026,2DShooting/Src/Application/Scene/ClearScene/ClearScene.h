#pragma once

//継承
#include"../BaseScene/BaseScene.h"

class ClearScene : public BaseScene
{
public:
	ClearScene() { Init(); }
	~ClearScene() { Release(); }
	void Init()override;
	void Update()override;
	void Draw()override;


private:

	void Release()override;



};