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
	SDL_Point cursorPosition = { 0,0 };        //鼠标指针坐标

private:
	std::vector<UIWidget*> uiWidgets;          //UI组件列表

public:
	void OnInput(const SDL_Event&);
	void OnUpdate(SDL_Renderer*);
	void OnRender(SDL_Renderer*);

	//根据左上顶点位置、纹理尺寸，绘制纹理图片
	void DrawTexture(SDL_Renderer* , SDL_Texture*, const SDL_Point&, const SDL_Point&);
	//根据圆心位置、圆半径、圆环颜色，绘制空心圆环
	void DrawCircleRing(SDL_Renderer*, const SDL_Point&, double, const SDL_Color&);
	//根据圆心位置、圆半径、边框颜色、内容颜色，绘制带边框的填充圆
	void DrawFilledCircle(SDL_Renderer*, const SDL_Point&, double, const SDL_Color&, const SDL_Color&);
	//根据左上顶点位置、矩形尺寸、矩形颜色，绘制一个空心矩形
	void DrawBoxLine(SDL_Renderer*, const SDL_Point&, const SDL_Point&, const SDL_Color&);
	//根据左上顶点位置、矩形尺寸、矩形颜色，绘制一个矩形色块
	void DrawFilledBox(SDL_Renderer*, const SDL_Point&, const SDL_Point&, const SDL_Color&);
	//根据左上顶点位置、矩形尺寸、向内边框厚度、矩形颜色，绘制一个边框
	void DrawBorder(SDL_Renderer*, const SDL_Point&, const SDL_Point&, size_t, const SDL_Color&);
	//根据左上顶点位置、条尺寸、边框厚度、背景颜色、内容颜色、内容数值比例，绘制动态更新的数值条
	void DrawDynamicBar(SDL_Renderer*, const SDL_Point&, const SDL_Point&, int, const SDL_Color&, const SDL_Color&, double);

private:
	UIManager();
	~UIManager();
};

#endif
