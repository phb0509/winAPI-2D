#pragma once


class SceneManager
{
private:
	SceneManager();
	~SceneManager();

public:
	static SceneManager* Get()
	{
		static SceneManager instance;
		return &instance;
	}

	void Update();
	void Render(HDC hdc);

	Scene* Add(string key, Scene* scene);

	void ChangeScene(string key);

private:
	map<string, Scene*> scenes;
	Scene* curScene;
};