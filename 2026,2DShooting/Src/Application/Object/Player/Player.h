#pragma once

class Player
{
public:

	Player(){}
	~Player(){ Release(); }

	void Init();
	void Action();
	void Update();
	void Draw();

private:

	void Release();

	const float m_speed = 5.0f;
	Math::Vector2 m_pos;
	Math::Matrix m_mat;
	KdTexture m_tex;
};