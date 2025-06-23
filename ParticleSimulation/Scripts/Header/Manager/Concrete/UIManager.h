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

	//根据左上顶点位置、纹理尺寸，绘制纹理图片
	void DrawTexture(SDL_Renderer* , SDL_Texture*, const SDL_Point&, const SDL_Point&);
	//根据左上顶点位置、圆半径、边框颜色、内容颜色，绘制带边框的圆
	void DrawCircle(SDL_Renderer*, const SDL_Point&, double, const SDL_Color&, const SDL_Color&);
	//根据左上顶点位置、矩形尺寸、矩形颜色，绘制一个矩形色块
	void DrawBox(SDL_Renderer*, const SDL_Point&, const SDL_Point&, const SDL_Color&);

private:
	UIManager();
	~UIManager();
};

#endif
