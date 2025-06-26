#ifndef _UIW_BRUSH_CONTROL_H_
#define _UIW_BRUSH_CONTROL_H_

#include <unordered_map>

#include "../UIWidget.h"
#include "../../../Header/Particle/ParticleType.h"

class UIW_ParticleBrushControl :public UIWidget
{
private:
	#pragma region MouseInput
	bool leftMouseDown = false;                                       //鼠标左键按下状态
	bool rightMouseDown = false;                                      //鼠标右键按下状态
	SDL_Point lastCursorPos = { 0,0 };                                //鼠标指针上次位置
	#pragma endregion
	
	#pragma region BrushSize
	int brushSizeMax = 40;                                            //笔刷最大尺寸大小
	int brushSize = 20;                                               //笔刷当前尺寸大小

	SDL_Rect brushSizeControlPanelRect = { 0,0,0,0 };                 //画笔大小控制面板矩形
	int brushSizeControlPanelBorderThickness = 5;                     //画笔大小控制面板边框厚度
	#pragma endregion

	#pragma region ParticleType
	ParticleType selectedParticleType = ParticleType::SAND;           //当前选中的粒子类型
	std::unordered_map<ParticleType, SDL_Color> particleColors;       //<粒子类型,粒子颜色>映射表
	std::unordered_map<ParticleType, SDL_Rect>  particleButtonRects;  //<粒子类型,按钮矩形>映射表
	
	SDL_Rect particleTypeSelectPanelRect = { 10,10,0,0 };             //粒子类型选择面板矩形

	SDL_Point particleTypeButtonSize = { 40,40 };                     //单个粒子类型的按钮尺寸
	int particleTypeButtonDistanceBetween = 5;                        //粒子类型按钮间的间距
	int particleTypeSelectPanelBorderThickness = 5;                   //粒子类型选择面板边宽
	#pragma endregion
	
	int panelDistanceBetween = 10;                                    //面板间距

	//#pragma region Text
	//SDL_Point textSize = { 0, 0 };                                    //文本尺寸
	//const SDL_Color textColor = { 255,255,255,255 };                  //文本颜色
	//SDL_Texture* textTexture = nullptr;                               //文本纹理
	//#pragma endregion

public:
	UIW_ParticleBrushControl();
	~UIW_ParticleBrushControl();

	void OnInput(const SDL_Event&) override;
	void OnUpdate(SDL_Renderer*) override;
	void OnRender(SDL_Renderer*) override;

private:
	void DrawParticles(int, int, ParticleType, int);
	void EraseParticles(int, int, int);
};

#endif