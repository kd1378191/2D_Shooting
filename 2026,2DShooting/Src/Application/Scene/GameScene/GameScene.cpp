#include "main.h"
#include "Scene.h"

//半角数字を使用して書く
//コメントは前にスラッシュ２つ

//①Init 最初の1フレームで実行される
//②Update 1秒間に60回のペースで実行される
//③Draw 1秒間に60回のペースで実行される
//②と③を繰り返し実行される
//④Release 最後の1フレームで実行される

//1秒間に60回のペースで繰り返される(60fps)
void Scene::Draw2D()
{
	//先に書いたものから描画される

	//背景の描画(1枚目)
	SHADER.m_spriteShader.SetMatrix(backMat1);
	SHADER.m_spriteShader.DrawTex(&backTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);

	//背景(2枚目)
	SHADER.m_spriteShader.SetMatrix(backMat2);
	SHADER.m_spriteShader.DrawTex(&backTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);

	//自機の描画
	if (playerFlg == 1) 
	{
		//①移動行列のセット
		SHADER.m_spriteShader.SetMatrix(charaMat);
		//②描画！
		SHADER.m_spriteShader.DrawTex(&charaTex, Math::Rectangle{ (int)playerAnimCnt * 64,0,64,64 }, 1.0f);
	}

	//敵
	for (int e = 0;e < enemyNum;e++) 
	{
		if (enemyFlg[e] == 1)
		{
			SHADER.m_spriteShader.SetMatrix(enemyMat[e]);
			SHADER.m_spriteShader.DrawTex(&enemyTex, Math::Rectangle{ 0,0,64,64 }, 1.0f);
		}
	}
	//弾
	for (int bu = 0;bu < bulletNum;bu++) {
		if (bulletFlg[bu] == 1)
		{
			SHADER.m_spriteShader.SetMatrix(bulletMat[bu]);
			SHADER.m_spriteShader.DrawTex(&bulletTex, Math::Rectangle{ 0,0,16,16 }, 1.0f);
		}
	}

	//爆発
	for (int ex = 0;ex < exNum;ex++) {
		if (expFlg[ex] == 1) {
			SHADER.m_spriteShader.SetMatrix(expMat[ex]);
			SHADER.m_spriteShader.DrawTex(&expTex, Math::Rectangle{ (int)expAnimCnt[ex] * 64,0,64,64 }, 1.0f);
		}
	}

	//ボス
	if (bossFlg == 1) {
		SHADER.m_spriteShader.SetMatrix(bossMat);
		SHADER.m_spriteShader.DrawTex(&enemyTex, Math::Rectangle{ 0,0,64,64 }, 1.0f);
	}

	//この下にDrawStringを書く(↑にDrawTex)==================================================
	//1文字列の格納用の配列作成
	char text[200];

	//②" "内の文字列をtextに格納
	sprintf_s(text, sizeof(text), "Score:%d", score);

	//③textの中身を描画
	SHADER.m_spriteShader.DrawString(-640, 360, text, Math::Vector4(1, 1, 0, 1));

	//ゲームオーバーの表示
	if (playerFlg == 0) {
		SHADER.m_spriteShader.DrawString(0, 0, "GAME OVER", Math::Vector4(1, 0, 0, 1));
	}
	
	// 文字列表示
	//SHADER.m_spriteShader.DrawString(0, 0, "KOUBEDENSHI", Math::Vector4(1, 1, 0, 1));

}

//1秒間に60回のペースで繰り返される(60fps)
void Scene::Update()
{
	if (playerFlg == 1)
	{
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			playerX += 5;//playerX=playerX+1と同じ意味！
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			playerX -= 5;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			playerY += 5;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			playerY -= 5;
		}
		//X=-640～640 Y=-360～360
		//両端、上下判定の処理
		if (playerX > 640 - 32)
		{
			playerX = 640 - 32;
		}
		if (playerX < -640 + 32)
		{
			playerX = -640 + 32;
		}
		if (playerY > 360 - 32)
		{
			playerY = 360 - 32;
		}
		if (playerY < -360 + 32)
		{
			playerY = -360 + 32;
		}

		//スペースキーを押して弾発射
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			//待機時間が0の場合
			if (shotWait == 0) {


				for (int bu = 0;bu < bulletNum;bu++) {
					if (bulletFlg[bu] == 0) {
						//弾を表示
						bulletFlg[bu] = 1;

						//弾の座標を自機の座標にセット
						bulletX[bu] = playerX;
						bulletY[bu] = playerY;


						shotWait = 10;//待機時間が10フレーム
						break;//1発「発射状態」にしたら繰り返しを抜ける
					}
				}
			}
		}
		//自機のアニメーション
		playerAnimCnt += 0.1f;
		if (playerAnimCnt >= 4) {
			playerAnimCnt = 0;
		}
	}

	//敵
	for (int e = 0;e < enemyNum;e++)
	{
		if (enemyFlg[e] == 1)//敵が生きていたら
		{
			enemyY[e] -= 3;
			//下端に到達したら上から再出現
			if (enemyY[e] < -360 - 32)
			{
				enemyY[e] = 360 + 34;
			}

			if (playerFlg == 1)
			{
				//自機との当たり判定

				float a = enemyX[e] - playerX; //底辺(X座標の差で求める)
				float b = enemyY[e] - playerY; //高さ(Y座標の差で求める)
				float c = sqrt(a * a + b * b); //斜辺(sqrt → ルート√)


				//自機と敵が当たっていたら(半径+半径)
				if (c < 36 + 36)
				{
					//敵を倒す
					enemyFlg[e] = 0;

					//自機死亡
					playerFlg = 0;

					//爆発
					Expiosion(playerX, playerY);
				}
			}
		}
	}

	//敵を２％の確率で復活させる
	if (rand() % 100 + 1 <= 2) {
		for (int e = 0;e < enemyNum;e++) {

			if (enemyFlg[e] == 0) {
				//1体だけの復活
				enemyFlg[e] = 1;
				enemyX[e] = rand() % (1280 + 1 - 64) - (640 - 32);
				enemyY[e] = 360 + 32;
				break;
			}
		}
	}

	for (int bu = 0;bu < bulletNum;bu++) {
		if (bulletFlg[bu] == 1)
		{
			//弾発射後の処理
			bulletY[bu] += 15;
			for (int e = 0;e < enemyNum;e++)
			{
				if (enemyFlg[e] == 1)//敵が生きていたら
				{
					//敵と弾の当たり判定
					float a = enemyX[e] - bulletX[bu]; //底辺(X座標の差で求める)
					float b = enemyY[e] - bulletY[bu]; //高さ(Y座標の差で求める)
					float c = sqrt(a * a + b * b); //斜辺(sqrt → ルート√)


					//弾と敵が当たっていたら(半径+半径)
					if (c < 36 + 8)
					{
						//敵を倒す
						enemyFlg[e] = 0;

						//弾を消す
						bulletFlg[bu] = 0;

						//スコア加算
						score += 100;

						//爆発発生！
						Expiosion(enemyX[e], enemyY[e]);//発生させる座標を引数で渡す

						break;//弾が未発射状態になったので敵の繰り返しを抜ける
					}
				}
			}

			//ボスと弾の当たり判定
			if (bossFlg == 1) {
				//距離判定
				float a = bossX - bulletX[bu]; 
				float b = bossY - bulletY[bu]; 
				float c = sqrt(a * a + b * b);

				if (c < bossRadius + 8) {
					//ボスHPを-1する
					bossHp -= 1;
					//爆発エフェクト発生(弾の座標に)
					Expiosion(bulletX[bu], bulletY[bu]);
					//弾未発射状態に
					bulletFlg[bu] = 0;
				}
			}

		}
	}

	//弾の発射待機時間
	shotWait--;
	if (shotWait < 0) {
		shotWait = 0;
	}

	//爆発アニメーション
	for (int ex = 0;ex < exNum;ex++) {
		if (expFlg[ex] == 1) {
			expAnimCnt[ex] += 0.45f;//アニメーションを次のコマへ進める
			//アニメーション終了のチェック
			if (expAnimCnt[ex] >= 8) {
					expFlg[ex] = 0;
			}
		}
	}

	//弾が画面から出たら未発射状態にする
	for (int bu = 0;bu < bulletNum;bu++) {
		if (bulletY[bu] > 360 + 8)
		{
			bulletFlg[bu] = 0;
		}
	}

	//Enterでリセット
	Reset();

	//背景のスクロール処理
	backY -= 3;
	if (backY < -720)
	{
		backY = 0;
	}

	//ボス
	if (score >= 50 && bossHp > 0) {
		bossFlg = 1;
	}
	if (bossFlg == 1) {
		bossY -= 2;

		if (bossY<-360-bossRadius) {
			bossY = 360-36;
		}

		//回転させる
		bossAngle += 1;
		if (bossAngle >= 360) {
			bossAngle -= 360;
		}

		if (bossHp <= 0) {
		//ボスを倒す
			bossFlg = 0;
		//ボスの座標に爆発
			Expiosion(bossX, bossY);
		//スコア1000加算
			score += 1000;
		}
	}




	//↓Updateの最後に行列作成↓↓
	//背景
	backMat1 = Math::Matrix::CreateTranslation(0, backY, 0);
	backMat2 = Math::Matrix::CreateTranslation(0, backY + 720, 0);

	//自機
	charaMat = Math::Matrix::CreateTranslation(playerX, playerY, 0);

	//敵
	for (int e = 0;e < enemyNum;e++)
	{
		enemyMat[e] = Math::Matrix::CreateTranslation(enemyX[e], enemyY[e], 0);
	}

	//弾
	for (int bu = 0;bu < bulletNum;bu++) {
		bulletMat[bu] = Math::Matrix::CreateTranslation(bulletX[bu], bulletY[bu], 0);
	}

	//爆発
	for (int ex = 0;ex < exNum;ex++) {
		expMat[ex] = Math::Matrix::CreateTranslation(expX[ex], expY[ex], 0);
	}

	//ボス
	Math::Matrix trans = Math::Matrix::CreateTranslation(bossX, bossY, 0);//移動

	Math::Matrix scale = Math::Matrix::CreateScale(bossSize, bossSize, 0);//拡縮

	Math::Matrix rotate= Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(bossAngle));//回転

	bossMat = scale * rotate * trans;//拡縮 * 回転 * 移動 
	//bossMat = scale * trans;//拡縮 * 移動　の順番!
}

//最初の1フレームで実行される
void Scene::Init()//ここはゲーム開始したとき最初に一度だけ実行される
{
	//乱数の初期化(＊必ずInitに1度だけ書く)
	srand(time(0));
	// 画像の読み込み処理
	charaTex.Load("Texture/player.png");
	enemyTex.Load("Texture/enemy.png");
	bulletTex.Load("Texture/bullet.png");
	expTex.Load("Texture/explosion.png");
	backTex.Load("Texture/back.png");
	
	//自機の初期化処理
	playerX = 0;
	playerY = -200;
	playerFlg = 1;

	//敵の初期化
	for (int e = 0;e < enemyNum;e++) 
	{
		enemyX[e] = rand() % (1280 + 1 - 64) - (640 - 32);//-608～608
		enemyY[e] = 360 + 32;
		enemyFlg[e] = 1;
	}

	//弾
	for (int bu = 0;bu < bulletNum;bu++) {
		bulletFlg[bu] = 0;
	}

	score = 0;

	//爆発
	for (int ex = 0;ex < exNum;ex++) {
		expX[ex] = 0;
		expY[ex] = 0;
		expFlg[ex] = 0;
	}

	//ボス
	bossX = 0;
	bossY = 360 + 32;
	bossFlg = 0;
	bossSize = 1.5;
	bossRadius = 32 * bossSize;//拡大率を考慮して求める
	bossHp = 10;
	bossAngle = 0;

}

//最後の1フレームで実行される
void Scene::Release()
{
	// 画像の解放処理
	charaTex.Release();
	enemyTex.Release();
	bulletTex.Release();
	expTex.Release();
	backTex.Release();
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}

void Scene::Reset()
{
	//リセット
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		//自機
		playerFlg = 1;
		playerX = 0;
		playerY = -200;

		//敵
		for (int e = 0;e < enemyNum;e++) {
			enemyFlg[e] = 1;
			enemyX[e] = rand() % rand() % (1280 + 1 - 64) - (640 - 32);
			enemyY[e] = 360 + 32;
		}

		score = 0;
	}

}

void Scene::Expiosion(float x, float y)
{

	//爆発発生!
	for (int ex = 0;ex < exNum;ex++) {
		if (expFlg[ex] == 0) {
			expFlg[ex] = 1;
			expX[ex] = x;
			expY[ex] = y;
			expAnimCnt[ex] = 0;//アニメーション１コマ目から

			//1つだけ生成
			break;
		}
	}

}
