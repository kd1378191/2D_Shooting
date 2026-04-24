#include "Enemy.h"

void Enemy::Init()
{
	m_animCnt = 0.0f;
	m_pos.x = (rand() % 1280) - 640;
	m_pos.y = 360 + 32+ (rand() % 360);
}

void Enemy::Action()
{
	m_pos.y -= m_speed;
	if (m_pos.y <= -360 - 32)
	{
		m_pos.y = 360 + 32;
		m_pos.x = (rand() % 1280) - 640;
	}

	m_animCnt += 0.1f;

}

void Enemy::Update()
{

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 1.0f);

}

void Enemy::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle{ 0,0,64,64 }, 1.0f);
}
