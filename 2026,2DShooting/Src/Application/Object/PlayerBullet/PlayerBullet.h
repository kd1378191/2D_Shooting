#pragma once

class PlayerBullet
{
public:

	PlayerBullet() { Init(); }
	~PlayerBullet() { Release(); }

	
	void Action();
	void Update();
	void Draw();

	void SetPlayerPos(Math::Vector2 m_PlayerPos) { m_playerPos = m_PlayerPos; }

private:
	void Init();
	void Release();


	static const int m_num = 10;
	const float m_speed = 3.0f;
	Math::Vector2 m_pos[m_num];
	Math::Matrix m_mat[m_num];
	KdTexture m_tex;
	int shotWait;
	
	Math::Vector2 m_playerPos;

	bool m_flg[m_num];

	const Math::Vector2 m_size = { 64,64 };
	float m_animCnt;

};
