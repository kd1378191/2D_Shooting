#pragma once

//継承
#include"../BaseScene/BaseScene.h"

class TitleScene : public BaseScene
{
public:
	TitleScene() { Init(); }
	~TitleScene() { Release(); }
	void Init()override;
	void Update()override;
	void Draw()override;


private:

	void Release()override;



};