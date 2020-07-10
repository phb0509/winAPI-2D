// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <ctime>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <functional>

#include <Ole2.h>
#include <gdiplus.h>

#pragma comment(lib, "Gdiplus.lib")
//
//#include "inc/fmod.hpp"
//#pragma comment(lib, "lib/x64/fmod_vc.lib")

using namespace std;


#define WIN_START_X 0
#define WIN_START_Y 0

#define WIN_WIDTH 400
#define WIN_HEIGHT 400
#define CENTER_X WIN_WIDTH * 0.5
#define CENTER_Y WIN_HEIGHT * 0.5

#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0)
#define BLUE RGB(0, 0, 255)
#define MAGENTA RGB(255, 0, 255)
#define YELLOW RGB(255, 255, 0)
#define CYAN RGB(0, 255, 255)
#define WHITE RGB(255, 255, 255)
#define BLACK RGB(0, 0, 0)
#define BG_TOP GM->GetNormalBackGround().collision_rect->Top()




//#define LERP(s, e, t) (s*(1 - t) + e*t)
#define LERP(s, e, t) (s + (e - s)*t)
#define PI 3.141592

#define TEX TextureManager::Get()
#define KEYDOWN(k) Keyboard::Get()->Down(k)
#define KEYUP(k) Keyboard::Get()->Up(k)
#define KEYPRESS(k) Keyboard::Get()->Press(k)
#define DELTA Timer::Get()->GetElapsedTime()
#define CURTIME Timer::Get()->GetRunTime()
//#define EFFECT FXManager::Get()
//#define SOUND SoundManager::Get()
#define SCENE SceneManager::Get()
//#define CAM Camera::Get()
#define GM GameManager::Get()

//Framework Header
#include "Point.h"
#include "Vector2.h"
#include "Object.h"
#include "Circle.h"
#include "Rect.h"
#include "Line.h"

#include "Keyboard.h"
#include "Timer.h"


#include "Math.h"
#include "Texture.h"
#include "Bitmap.h"
#include "TextureManager.h"
#include "Animation.h"
#include "TextureRect.h"

//#include "SoundManager.h"
//#include "ImageFont.h"
//#include "FX.h"
//#include "FXManager.h"
//#include "Camera.h"


//Object Header

#include "Bullet.h"
#include "DefaultGunBullet.h"
#include "Eri.h"
#include "GameManager.h"

//Scene Header
#include "Scene.h"
#include "SceneManager.h"
#include "Program.h"
#include "NormalStageScene.h"

extern HWND hWnd;
extern HINSTANCE hInst;
extern Vector2 mousePos;