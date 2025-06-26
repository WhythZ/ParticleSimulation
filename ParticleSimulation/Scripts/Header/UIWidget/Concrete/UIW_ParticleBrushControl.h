#ifndef _UIW_BRUSH_CONTROL_H_
#define _UIW_BRUSH_CONTROL_H_

#include <unordered_map>

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
	int brushSizeMax = 40;                                            //��ˢ���ߴ��С
	int brushSize = 20;                                               //��ˢ��ǰ�ߴ��С

	SDL_Rect brushSizeControlPanelRect = { 0,0,0,0 };                 //���ʴ�С����������
	int brushSizeControlPanelBorderThickness = 5;                     //���ʴ�С�������߿���
	#pragma endregion

	#pragma region ParticleType
	ParticleType selectedParticleType = ParticleType::SAND;           //��ǰѡ�е���������
	std::unordered_map<ParticleType, SDL_Color> particleColors;       //<��������,������ɫ>ӳ���
	std::unordered_map<ParticleType, SDL_Rect>  particleButtonRects;  //<��������,��ť����>ӳ���
	
	SDL_Rect particleTypeSelectPanelRect = { 10,10,0,0 };             //��������ѡ��������

	SDL_Point particleTypeButtonSize = { 40,40 };                     //�����������͵İ�ť�ߴ�
	int particleTypeButtonDistanceBetween = 5;                        //�������Ͱ�ť��ļ��
	int particleTypeSelectPanelBorderThickness = 5;                   //��������ѡ�����߿�
	#pragma endregion
	
	int panelDistanceBetween = 10;                                    //�����

	//#pragma region Text
	//SDL_Point textSize = { 0, 0 };                                    //�ı��ߴ�
	//const SDL_Color textColor = { 255,255,255,255 };                  //�ı���ɫ
	//SDL_Texture* textTexture = nullptr;                               //�ı�����
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