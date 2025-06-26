#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include <SDL.h>

#include "../Manager.hpp"

class GameManager :public Manager<GameManager>
{
	friend class Manager<GameManager>;

public:
	SDL_Rect windowRect;                       //游戏窗口矩形区域

private:
	SDL_Window* window = nullptr;              //游戏主窗口
	SDL_Renderer* renderer = nullptr;          //GPU加速渲染器
	SDL_Event event;                           //SDL事件捕获
	bool isQuit = false;

public:
	int Run(int, char**);                      //游戏程序主循环

private:
	GameManager();
	~GameManager();
	void InitAssert(bool, const char*);        //初始化断言

	void OnInput();
	void OnUpdate(double);
	void OnRender();
};

#endif
