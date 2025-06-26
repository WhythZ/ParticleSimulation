#ifndef _UIW_BRUSH_CONTROL_H_
#define _UIW_BRUSH_CONTROL_H_

#include <unordered_map>
#include <string>

#include "../UIWidget.h"
#include "../../../Header/Particle/ParticleType.h"

class UIW_ParticleBrushControl :public UIWidget
{
private:
	#pragma region MouseInput
	bool leftMouseDown = false;                                       //����������״̬
	bool rightMouseDown = false;                                      //����Ҽ�����״̬
	SDL_Point lastCursorPos = { 0,0 };                                //���ָ���ϴ�λ��
	#pragma endregion
	
	#pragma region BrushSize
	int brushSizeMaximum = 40;                                        //��ˢ���ߴ��С
	int brushSizeCurrent = 20;                                        //��ˢ��ǰ�ߴ��С

	SDL_Rect brushSizeControlPanelRect = { 0,0,0,0 };                 //���ʴ�С����������
	#pragma endregion

	#pragma region ParticleType
	ParticleType selectedParticleType = ParticleType::SAND;           //��ǰѡ�е���������
	std::unordered_map<ParticleType, SDL_Color> particleColors;       //<��������,������ɫ>ӳ���
	std::unordered_map<ParticleType, SDL_Rect>  particleButtonRects;  //<��������,��ť����>ӳ���
	std::unordered_map<ParticleType, std::string>  particleNames;     //<��������,�����ִ�>ӳ���
	
	SDL_Rect particleTypeSelectPanelRect = { 10,10,0,0 };             //��������ѡ��������
	SDL_Point particleTypeButtonSize = { 40,40 };                     //�����������͵İ�ť�ߴ�
	#pragma endregion
	
	#pragma region TextUI
	SDL_Texture* particleTypeTextTexture = nullptr;                   //�ı�����
	SDL_Point particleTypeTextSize = { 0, 0 };                        //�ı��ߴ�
	const SDL_Color particleTypeTextColor = { 255,255,255,255 };      //�ı���ɫ
	#pragma endregion

	#pragma region ApperanceDetails
	const int elementDistanceBetween = 10;                            //��Ԫ�أ���塢�ı��ȣ���ļ��

	const int brushSizeControlPanelBorderThickness = 5;               //���ʴ�С�������߿���
	const int particleTypeSelectPanelBorderThickness = 5;             //��������ѡ�����߿���
	const int particleTypeButtonDistanceBetween = 5;                  //�������Ͱ�ť��ļ��

	SDL_Color brushSizeControlPanelBackgroundColor = { 50,50,50,200 };
	SDL_Color brushSizeControlPanelContentColor = { 200,200,200,255 };
	SDL_Color particleTypeSelectPanelBackgroundColor = { 50,50,50,200 };
	SDL_Color particleTypeButtonBorderColor = { 255,255,255,255 };
	#pragma endregion

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