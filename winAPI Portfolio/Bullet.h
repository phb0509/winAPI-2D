#pragma once

class Bullet
{
public:
	Bullet() {};
	virtual ~Bullet() {};

	bool GetActive() { return isActive; }
	void SetActive(bool _isActive) { isActive = _isActive; }

	virtual void Update() {};
	virtual void Render() {};

	virtual void SetBulletPosition(Vector2 position) {};

private:
	bool isActive = true;
};

