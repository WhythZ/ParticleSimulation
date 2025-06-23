#ifndef _UI_MANAGER_H_
#define _UI_MANAGER_H_

#include <SDL.h>

#include "../Manager.hpp"
#include "ResourceManager.h"

class UIManager :public Manager<UIManager>
{
	friend class Manager<UIManager>;

private:


public:
	void OnInput(const SDL_Event&);
	void OnUpdate(SDL_Renderer*);
	void OnRender(SDL_Renderer*);

	//�������϶���λ�á�����ߴ磬��������ͼƬ
	void DrawTexture(SDL_Renderer* , SDL_Texture*, const SDL_Point&, const SDL_Point&);
	//�������϶���λ�á�Բ�뾶���߿���ɫ��������ɫ�����ƴ��߿��Բ
	void DrawCircle(SDL_Renderer*, const SDL_Point&, double, const SDL_Color&, const SDL_Color&);
	//�������϶���λ�á����γߴ硢������ɫ������һ������ɫ��
	void DrawBox(SDL_Renderer*, const SDL_Point&, const SDL_Point&, const SDL_Color&);

private:
	UIManager();
	~UIManager();
};

#endif
