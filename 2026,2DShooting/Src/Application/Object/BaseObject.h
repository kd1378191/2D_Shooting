#pragma once

//全てのゲーム内オブジェクトの基底クラス
class BaseObject
{
public:
	BaseObject() {}
	virtual~BaseObject() { Release(); }

	enum class ObjectType
	{
		None,	//何もなし
		Player,	//プレイヤー
		Enemy,	//エネミー
	};

	//派生先で挙動を変える(上書きする)関数は観客
	virtual void Update();
	virtual void Draw();
	virtual void Init();

	// Hit時の処理　※派生先で挙動を変える！
	virtual void OnHit() {}

	ObjectType GetObjType() { return m_objType; }
	Math::Vector3 GetPos() { return m_pos; }
	bool GetAliveFlg() { return m_aliveFlg; }

	//protected:
protected:

	KdTexture m_tex;//テクスチャ
	Math::Vector3 m_pos = {};//座標
	bool m_aliveFlg = true;//生存フラグ

	virtual void Release();


	//オブジェクトの種類
	ObjectType m_objType = ObjectType::None;


};