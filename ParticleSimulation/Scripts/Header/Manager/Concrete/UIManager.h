#ifndef _UI_MANAGER_H_
#define _UI_MANAGER_H_

#include <SDL.h>

#include "../Manager.hpp"
#include "ResourceManager.h"
#include "../../Particle/ParticleType.h"

class UIManager :public Manager<UIManager>
{
	friend class Manager<UIManager>;

private:
	ParticleType selectedParticle = ParticleType::SAND;    //��������ѡ��
	int brushSize = 5;                                     //���ʳߴ��С

	#pragma region MouseCursor
	bool leftMouseDown = false;                            //����������״̬
	bool rightMouseDown = false;                           //����Ҽ�����״̬
	SDL_Point lastMousePos = { 0, 0 };                     //����ϴ�λ��
	#pragma endregion

	#pragma region ParticleSelection
	SDL_Rect particleSelectorRect = { 10, 10, 200, 40 };   //����ѡ��������
	SDL_Rect brushSizeRect = { 10, 60, 200, 20 };          //���ʴ�С��������
	#pragma endregion

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
	#pragma endregion

private:
	UIManager();
	~UIManager();

	void DrawParticles(int, int, ParticleType, int);
	void EraseParticles(int, int, int);

	void DrawParticleSelector(SDL_Renderer*);
	void DrawBrushSizeControl(SDL_Renderer*);
};

#endif
