#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include <SDL.h>

#include "../Manager.hpp"

class GameManager :public Manager<GameManager>
{
	friend class Manager<GameManager>;

public:
	SDL_Rect windowRect;                       //��Ϸ���ھ�������

private:
	SDL_Window* window = nullptr;              //��Ϸ������
	SDL_Renderer* renderer = nullptr;          //GPU������Ⱦ��
	SDL_Event event;                           //SDL�¼�����
	bool isQuit = false;

public:
	int Run(int, char**);                      //��Ϸ������ѭ��

private:
	GameManager();
	~GameManager();
	void InitAssert(bool, const char*);        //��ʼ������

	void OnInput();
	void OnUpdate(double);
	void OnRender();
};

#endif
