#pragma once

//全てのシーンの親クラス(基底クラス)

class BaseScene
{
public:
	BaseScene() { Init(); }
	virtual ~BaseScene() {}

	//virtual = 仮想関数・・・上書きを前提とする関数
	//純粋仮想関数・・・絶対に上書きしなければならない関数
	//virtual void Init() = 0;	//=0をつけると純粋仮想関数になる。純粋仮想関数は必ず子クラスでオーバーライドする必要がある。
	//virtualは絶対にいる

	virtual void Init();
	virtual void Update();
	//2D描画の場合
	virtual void Draw();
	virtual void Release();

private:

	KdTexture m_tex;
	KdTexture m_texS;

	float m_alpha = 1.0f;
	float m_addAlpha = 0.01f;

};