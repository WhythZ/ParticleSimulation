#include "../../../Header/Manager/Concrete/UIManager.h"

#include <iostream>
#include <SDL2_gfxPrimitives.h>

#include "../../../Header/Manager/Concrete/GameManager.h"
#include "../../../Header/Manager/Concrete/ParticleManager.h"
#include "../../../Header/UIWidget/Concrete/UIW_ParticleBrushControl.h"

UIManager::UIManager()
{
	//��ʼ��UI���
	uiWidgets.emplace_back(new UIW_ParticleBrushControl());
}

UIManager::~UIManager()
{
    //�ͷ�ÿ��UI������ڴ�
	for (UIWidget* _widget : uiWidgets)
		delete _widget;
}

void UIManager::OnInput(const SDL_Event& _event)
{
    //���ָ���ƶ��¼�
    if (_event.type == SDL_MOUSEMOTION)
    {
        //��ȡ���ָ������
        cursorPosition.x = _event.motion.x;
        cursorPosition.y = _event.motion.y;
    }

    //����ÿ��UI���
    for (UIWidget* _widget : uiWidgets)
        _widget->OnInput(_event);
}

void UIManager::OnUpdate(SDL_Renderer* _renderer)
{
    //����ÿ��UI���
	for (UIWidget* _widget : uiWidgets)
		_widget->OnUpdate(_renderer);
}

void UIManager::OnRender(SDL_Renderer* _renderer)
{
    //����ÿ��UI���
    for (UIWidget* _widget : uiWidgets)
        _widget->OnRender(_renderer);
}

void UIManager::DrawTexture(SDL_Renderer* _renderer, SDL_Texture* _texture, const SDL_Point& _leftUpPosition, const SDL_Point& _size)
{
	//��ʱ�洢ÿ����ȾԪ�أ�ÿ����Ⱦ����Ԫ��ʱ����
	static SDL_Rect _dstRect;

	//���ݴ���Ķ�����ߴ��������
	_dstRect = { _leftUpPosition.x, _leftUpPosition.y, _size.x, _size.y };
	SDL_RenderCopy(_renderer, _texture, nullptr, &_dstRect);
}

void UIManager::DrawFilledCircle(SDL_Renderer* _renderer, const SDL_Point& _centerPosition, double _radius,
	const SDL_Color& _borderColor, const SDL_Color& _contentColor)
{
	//����Բ���
	filledCircleRGBA(_renderer, _centerPosition.x, _centerPosition.y, (Sint16)_radius,
		_contentColor.r, _contentColor.g, _contentColor.b, _contentColor.a);
	//����Բ�߿�
	aacircleRGBA(_renderer, _centerPosition.x, _centerPosition.y, (Sint16)_radius,
		_borderColor.r, _borderColor.g, _borderColor.b, _borderColor.a);
}

void UIManager::DrawCircleRing(SDL_Renderer* _renderer, const SDL_Point& _centerPosition, double _radius, const SDL_Color& _ringColor)
{
    //����Բ�߿�
    aacircleRGBA(_renderer, _centerPosition.x, _centerPosition.y, (Sint16)_radius,
        _ringColor.r, _ringColor.g, _ringColor.b, _ringColor.a);
}

void UIManager::DrawBoxLine(SDL_Renderer* _renderer, const SDL_Point& _leftUpPosition, const SDL_Point& _size, const SDL_Color& _color)
{
    rectangleRGBA(_renderer, _leftUpPosition.x, _leftUpPosition.y,
        _leftUpPosition.x + _size.x, _leftUpPosition.y + _size.y,
        _color.r, _color.g, _color.b, _color.a);
}

void UIManager::DrawFilledBox(SDL_Renderer* _renderer, const SDL_Point& _leftUpPosition, const SDL_Point& _size, const SDL_Color& _color)
{
	boxRGBA(_renderer, _leftUpPosition.x, _leftUpPosition.y, _leftUpPosition.x + _size.x, _leftUpPosition.y + _size.y,
		_color.r, _color.g, _color.b, _color.a);
}

void UIManager::DrawBorder(SDL_Renderer* _renderer, const SDL_Point& _leftUpPosition, const SDL_Point& _size,
    size_t _borderThickness, const SDL_Color& _borderColor)
{
    //����߿��������
    SDL_Rect borderRects[4];

    //�ϱ߿�
    borderRects[0] =
    {
        _leftUpPosition.x,
        _leftUpPosition.y,
        _size.x,
        static_cast<int>(_borderThickness)
    };

    //�±߿�
    borderRects[1] =
    {
        _leftUpPosition.x,
        _leftUpPosition.y + _size.y - static_cast<int>(_borderThickness),
        _size.x,
        static_cast<int>(_borderThickness)
    };

    //��߿�
    borderRects[2] =
    {
        _leftUpPosition.x,
        _leftUpPosition.y + static_cast<int>(_borderThickness),
        static_cast<int>(_borderThickness),
        _size.y - 2 * static_cast<int>(_borderThickness)
    };

    //�ұ߿�
    borderRects[3] =
    {
        _leftUpPosition.x + _size.x - static_cast<int>(_borderThickness),
        _leftUpPosition.y + static_cast<int>(_borderThickness),
        static_cast<int>(_borderThickness),
        _size.y - 2 * static_cast<int>(_borderThickness)
    };

    //���ñ߿���ɫ
    SDL_SetRenderDrawColor(_renderer, _borderColor.r, _borderColor.g,
        _borderColor.b, _borderColor.a);

    //�����ĸ��߿����
    SDL_RenderFillRects(_renderer, borderRects, 4);
}

void UIManager::DrawDynamicBar(SDL_Renderer* _renderer, const SDL_Point& _leftUpPosition, const SDL_Point& _size, int _borderThickness,
    const SDL_Color& _backgroundColor, const SDL_Color& _contentColor, double _contentRatio)
{
    static SDL_Rect _dstRect;

    //�ȹ�������ı�����������[0,1]֮��
    double _ratio = (_contentRatio < 0) ? 0 : _contentRatio;
    _ratio = (_ratio > 1) ? 1 : _ratio;

    //��ֵֵ���Ȼ��Ʊ�����ɫ��䣬�ٻ���������ɫ��䣬�ȴ�����Ⱦ�������϶�������¶��㣬Ȼ������ɫ
    _dstRect = { _leftUpPosition.x, _leftUpPosition.y, _size.x, _size.y };
    boxRGBA(_renderer, _dstRect.x, _dstRect.y, _dstRect.x + _dstRect.w, _dstRect.y + _dstRect.h,
        _backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a);
    //��������»���Բ�Ǿ��Σ����贫��Բ�ǰ뾶
    //roundedBoxRGBA(_renderer, _dstRect.x, _dstRect.y, _dstRect.x + _dstRect.w, _dstRect.y + _dstRect.h,
    //	4, _backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a);

    //�������ݵ������Σ���ˮƽ��Ȱ��ձ���ʵʱ���£��������ݱ߿�����խ��������ɫ���൱����������ɫ����Χ�γ�һȦ�߿�
    _dstRect = { _leftUpPosition.x + _borderThickness, _leftUpPosition.y + _borderThickness,
        (int)((_size.x - 2 * _borderThickness) * _ratio), _size.y - 2 * _borderThickness };
    boxRGBA(_renderer, _dstRect.x, _dstRect.y, _dstRect.x + _dstRect.w, _dstRect.y + _dstRect.h,
        _contentColor.r, _contentColor.g, _contentColor.b, _contentColor.a);
    //roundedBoxRGBA(_renderer, _dstRect.x, _dstRect.y, _dstRect.x + _dstRect.w, _dstRect.y + _dstRect.h,
    //	4, _contentColor.r, _contentColor.g, _contentColor.b, _contentColor.a);
}