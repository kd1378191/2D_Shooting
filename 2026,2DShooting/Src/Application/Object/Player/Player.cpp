#include "Player.h"
#include"../PlayerBullet/PlayerBullet.h"

void Player::Init()
{
	m_bullet = new PlayerBullet;
	// 画像の読み込み処理
	m_tex.Load("Texture/player.png");
	// 初期位置の設定
	m_pos = { 0,-100 };
}

void Player::Action()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000) { m_pos.y += m_speed; }
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { m_pos.y -= m_speed; }
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { m_pos.x -= m_speed; }
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { m_pos.x += m_speed; }
	if (m_pos.x < -640 + 32) { m_pos.x = -640 + 32; }
	else if (m_pos.x > 640 - 32) { m_pos.x = 640 - 32; }
	if (m_pos.y < -360 + 32) { m_pos.y = -360 + 32; }
	else if (m_pos.y > 360 - 32) { m_pos.y = 360 - 32; }

	//当たり判定　プレイヤー VS 敵

	m_bullet->SetPlayerPos(m_pos);
	m_bullet->Action();
}

void Player::Update()
{
	m_mat = Math::Matrix::CreateTranslation(m_pos.x,m_pos.y,1.0f);
	m_bullet->Update();
}

void Player::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle{ 0,0,64,64 }, 1.0f);
	m_bullet->Draw();
}

void Player::Release()
{
	// 画像の解放処理
	m_tex.Release();
}
