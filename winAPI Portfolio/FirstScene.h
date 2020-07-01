#pragma once

class FirstScene : public Scene
{
public:
	FirstScene();
	~FirstScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	
private:

};

