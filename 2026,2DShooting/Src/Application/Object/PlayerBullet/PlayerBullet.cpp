#include "PlayerBullet.h"

void PlayerBullet::Action()
{
	//	//スペースキーを押して弾発射
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		for (int bu = 0;bu < m_num;bu++) {
			//待機時間が0の場合
			if (shotWait == 0) {
			
				if (!m_flg[bu]) {
					//弾を表示
					m_flg[bu] = true;

					//弾の座標を自機の座標にセット
					m_pos[bu] = m_playerPos;


					shotWait = 10;//待機時間が10フレーム
					break;//1発「発射状態」にしたら繰り返しを抜ける
				}
			}
		}
	}
	//弾の発射待機時間
	shotWait--;
	if (shotWait < 0) {
		shotWait = 0;
	}

	for (int bu = 0;bu < m_num;bu++) {
		if (m_flg[bu])
		{
			//弾発射後の処理
			m_pos[bu].y += 15;
		}
	}
	//弾が画面から出たら未発射状態にする
	for (int bu = 0;bu < m_num;bu++) 
	{
		if (m_pos[bu].x < -640- m_size.x || m_pos[bu].x > 640+ m_size.x || m_pos[bu].y < -360- m_size.y || m_pos[bu].y > 360+ m_size.y)
		{
			m_flg[bu] = false;
		}
	}
}

void PlayerBullet::Update()
{
	for (int bu = 0;bu < m_num;bu++)
	{
		if (m_pos[bu].x > -640 - m_size.x || m_pos[bu].x < 640 + m_size.x || m_pos[bu].y > -360 - m_size.y || m_pos[bu].y < 360 + m_size.y)
		{
			m_mat[bu] = Math::Matrix::CreateTranslation(m_pos[bu].x, m_pos[bu].y, 1.0f);
		}
	}
}

void PlayerBullet::Draw()
{
	for (int bu = 0;bu < m_num;bu++) {
		if (m_flg[bu])
		{
			SHADER.m_spriteShader.SetMatrix(m_mat[bu]);
			SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle{ 0,0,16,16 }, 1.0f);
		}
	}

}

void PlayerBullet::Init()
{
	m_tex.Load("Texture/bullet.png");
	for (int bu = 0;bu < m_num;bu++)
	{
		m_flg[bu] = false;
	}

}

void PlayerBullet::Release()
{
	m_tex.Release();
}
