#pragma once

class DefaultGunBullet : public Bullet
{
public:
	DefaultGunBullet();
	~DefaultGunBullet();

	virtual void Update() override;
	virtual void Render() override;

	virtual void SetBulletPosition(Vector2 position) override { bullet_rect->center = position; };

private:
	Texture* bullet_texture;
	Rect* bullet_rect;
};

