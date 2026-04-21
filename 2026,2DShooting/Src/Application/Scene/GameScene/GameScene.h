#pragma once

class Scene
{
private:

	// テクスチャ ・・・ 画像データ
	KdTexture charaTex;
	KdTexture enemyTex;
	KdTexture bulletTex;
	KdTexture expTex;
	KdTexture backTex;


	//プレイヤー(自機)の変数
	Math::Matrix charaMat;//行列...座標、回転、縮小を管理	
	float playerX;//自機のX座標
	float playerY;//自機のY座標
	float playerFlg;
	float playerAnimCnt;

	//敵
	static const int enemyNum = 10;//敵の数(書き換え不可能)
	Math::Matrix enemyMat[enemyNum];
	float enemyX[enemyNum];
	float enemyY[enemyNum];
	int enemyFlg[enemyNum];//敵の生存状態を管理(0,死亡　1,生存)

	//弾
	static const int bulletNum = 30;//弾の数(書き換え不可能)
	Math::Matrix bulletMat[bulletNum];
	float bulletX[bulletNum];
	float bulletY[bulletNum];
	float bulletFlg[bulletNum];
	float shotWait;

	//爆発
	static const int exNum = 10;
	Math::Matrix expMat[exNum];
	float expX[exNum];
	float expY[exNum];
	float expFlg[exNum];
	float expAnimCnt[exNum];

	//ボス
	Math::Matrix bossMat;
	float bossX;
	float bossY;
	int bossFlg;
	float bossSize;//拡大率
	float bossRadius;//半径
	int bossHp;//ボスのHP
	float bossAngle;//角度


	//背景
	Math::Matrix backMat1;
	Math::Matrix backMat2;
	float backY;

	//スコア
	int score;


public:

	// 初期設定
	void Init();

	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

	//関数宣言後「alt + Enter」でScene.cppに関数定義を作成

	//リセット
	void Reset();

	//爆発
	void Expiosion(float x, float y);

private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
