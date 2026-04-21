#pragma once

class Player
{
public:
	Player(){}
	~Player(){}

	void Init();
	void Update();
	void Draw();

	void SetTex(KdTexture* tex) { m_tex = tex; }


private:

	const float m_speed = 5.0f;
	Math::Vector2 m_pos;
	Math::Matrix m_mat;
	KdTexture* m_tex;
};