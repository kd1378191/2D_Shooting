#pragma once

class BaseScene;	

class Scene
{
public:

	enum SceneType
	{
		Title,
		Game,
		GameOver,
		Clear,
	};

	void SetNextScene(SceneType _nextScene)
	{
		m_nextSceneType = _nextScene;
	}

	SceneType GetCurrentScene() const
	{
		return m_currentSceneType;
	}

	//更新前の処理
	void PreUpdate();

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

	//リセット
	//void Reset();
	//爆発
	//void Expiosion(float x, float y);



private:

	void ChangeScene(SceneType _sceneType);

	std::shared_ptr<BaseScene> m_currentScene;

	//どのシーンにいるかを管理するフラグ変数
	SceneType m_currentSceneType = SceneType::Title;
	SceneType m_nextSceneType = m_currentSceneType;

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
