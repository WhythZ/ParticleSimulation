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
	ParticleType selectedParticle = ParticleType::SAND;    //粒子类型选择
	int brushSize = 5;                                     //画笔尺寸大小

	#pragma region MouseCursor
	bool leftMouseDown = false;                            //鼠标左键按下状态
	bool rightMouseDown = false;                           //鼠标右键按下状态
	SDL_Point lastMousePos = { 0, 0 };                     //鼠标上次位置
	#pragma endregion

	#pragma region ParticleSelection
	SDL_Rect particleSelectorRect = { 10, 10, 200, 40 };   //粒子选择器区域
	SDL_Rect brushSizeRect = { 10, 60, 200, 20 };          //画笔大小控制区域
	#pragma endregion

public:
	void OnInput(const SDL_Event&);
	void OnUpdate(SDL_Renderer*);
	void OnRender(SDL_Renderer*);

	#pragma region BasicShapes
	//根据左上顶点位置、纹理尺寸，绘制纹理图片
	void DrawTexture(SDL_Renderer* , SDL_Texture*, const SDL_Point&, const SDL_Point&);
	//根据左上顶点位置、圆半径、边框颜色、内容颜色，绘制带边框的圆
	void DrawCircle(SDL_Renderer*, const SDL_Point&, double, const SDL_Color&, const SDL_Color&);
	//根据左上顶点位置、矩形尺寸、矩形颜色，绘制一个矩形色块
	void DrawBox(SDL_Renderer*, const SDL_Point&, const SDL_Point&, const SDL_Color&);
	//根据左上顶点位置、矩形尺寸、向内边框厚度、矩形颜色，绘制一个边框
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
