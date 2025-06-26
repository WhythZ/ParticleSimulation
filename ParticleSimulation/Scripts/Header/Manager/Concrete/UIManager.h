#ifndef _UI_MANAGER_H_
#define _UI_MANAGER_H_

#include <SDL.h>

#include "../Manager.hpp"
#include "ResourceManager.h"
#include "../../UIWidget/UIWidget.h"

class UIManager :public Manager<UIManager>
{
	friend class Manager<UIManager>;

public:
	SDL_Point cursorPosition = { 0,0 };        //���ָ������

private:
	std::vector<UIWidget*> uiWidgets;          //UI����б�

public:
	void OnInput(const SDL_Event&);
	void OnUpdate(SDL_Renderer*);
	void OnRender(SDL_Renderer*);

	#pragma region BasicShapes
	//�������϶���λ�á�����ߴ磬��������ͼƬ
	void DrawTexture(SDL_Renderer* , SDL_Texture*, const SDL_Point&, const SDL_Point&);
	//�������϶���λ�á�Բ�뾶���߿���ɫ��������ɫ�����ƴ��߿��Բ
	void DrawCircle(SDL_Renderer*, const SDL_Point&, double, const SDL_Color&, const SDL_Color&);
	//�������϶���λ�á����γߴ硢������ɫ������һ������ɫ��
	void DrawBox(SDL_Renderer*, const SDL_Point&, const SDL_Point&, const SDL_Color&);
	//�������϶���λ�á����γߴ硢���ڱ߿��ȡ�������ɫ������һ���߿�
	void DrawBorder(SDL_Renderer*, const SDL_Point&, const SDL_Point&, size_t, const SDL_Color&);
	//�������϶���λ�á����ߴ硢�߿��ȡ�������ɫ��������ɫ��������ֵ���������ƶ�̬���µ���ֵ��
	void DrawDynamicBar(SDL_Renderer*, const SDL_Point&, const SDL_Point&, int, const SDL_Color&, const SDL_Color&, double);
	#pragma endregion

private:
	UIManager();
	~UIManager();
};

#endif
