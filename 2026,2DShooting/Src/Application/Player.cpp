#include "Player.h"

void Player::Init()
{
	m_pos = { 0,-100 };
}

void Player::Update()
{
	if (GetAsyncKeyState('W') & 0x8000) { m_pos.y += m_speed; }
	if (GetAsyncKeyState('S') & 0x8000) { m_pos.y -= m_speed; }
	if (GetAsyncKeyState('A') & 0x8000) { m_pos.x -= m_speed; }
	if (GetAsyncKeyState('D') & 0x8000) { m_pos.x += m_speed; }
	if (m_pos.x < -640 + 32) { m_pos.x = -640 + 32; }
	else if (m_pos.x > 640 - 32) { m_pos.x = 640 - 32; }
	if (m_pos.y < -360 + 32) { m_pos.y = -360 + 32; }
	else if (m_pos.y > 360 - 32) { m_pos.y = 360 - 32; }

	m_mat = Math::Matrix::CreateTranslation(m_pos.x,m_pos.y,1.0f);

}

void Player::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle{ 0,0,64,64 }, 1.0f);
}
