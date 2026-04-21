#pragma once

class Enemy
{
public:

	Enemy() {}
	~Enemy() {}
	void Init();
	void Action();
	void Update();
	void Draw();
	void SetTex(KdTexture* tex) { m_tex = tex; }

private:
	const float m_speed = 3.0f;
	Math::Vector2 m_pos;
	Math::Matrix m_mat;
	KdTexture* m_tex;

	const Math::Vector2 m_size = { 64,64 };
	float m_animCnt;
};
