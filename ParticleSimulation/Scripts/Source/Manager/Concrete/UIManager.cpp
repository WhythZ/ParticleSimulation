#include "../../../Header/Manager/Concrete/UIManager.h"

#include <iostream>
#include <SDL2_gfxPrimitives.h>

#include "../../../Header/Manager/Concrete/GameManager.h"
#include "../../../Header/Manager/Concrete/ParticleManager.h"
#include "../../../Header/UIWidget/Concrete/UIW_ParticleBrushControl.h"

UIManager::UIManager()
{
	//初始化UI组件
	uiWidgets.emplace_back(new UIW_ParticleBrushControl());
}

UIManager::~UIManager()
{
    //释放每个UI组件的内存
	for (UIWidget* _widget : uiWidgets)
		delete _widget;
}

void UIManager::OnInput(const SDL_Event& _event)
{
    //鼠标指针移动事件
    if (_event.type == SDL_MOUSEMOTION)
    {
        //获取鼠标指针坐标
        cursorPosition.x = _event.motion.x;
        cursorPosition.y = _event.motion.y;
    }

    //更新每个UI组件
    for (UIWidget* _widget : uiWidgets)
        _widget->OnInput(_event);
}

void UIManager::OnUpdate(SDL_Renderer* _renderer)
{
    //更新每个UI组件
	for (UIWidget* _widget : uiWidgets)
		_widget->OnUpdate(_renderer);
}

void UIManager::OnRender(SDL_Renderer* _renderer)
{
    //更新每个UI组件
    for (UIWidget* _widget : uiWidgets)
        _widget->OnRender(_renderer);
}

void UIManager::DrawTexture(SDL_Renderer* _renderer, SDL_Texture* _texture, const SDL_Point& _leftUpPosition, const SDL_Point& _size)
{
	//临时存储每个渲染元素，每次渲染单个元素时复用
	static SDL_Rect _dstRect;

	//根据传入的顶点与尺寸绘制纹理
	_dstRect = { _leftUpPosition.x, _leftUpPosition.y, _size.x, _size.y };
	SDL_RenderCopy(_renderer, _texture, nullptr, &_dstRect);
}

void UIManager::DrawFilledCircle(SDL_Renderer* _renderer, const SDL_Point& _centerPosition, double _radius,
	const SDL_Color& _borderColor, const SDL_Color& _contentColor)
{
	//绘制圆填充
	filledCircleRGBA(_renderer, _centerPosition.x, _centerPosition.y, (Sint16)_radius,
		_contentColor.r, _contentColor.g, _contentColor.b, _contentColor.a);
	//绘制圆边框
	aacircleRGBA(_renderer, _centerPosition.x, _centerPosition.y, (Sint16)_radius,
		_borderColor.r, _borderColor.g, _borderColor.b, _borderColor.a);
}

void UIManager::DrawCircleRing(SDL_Renderer* _renderer, const SDL_Point& _centerPosition, double _radius, const SDL_Color& _ringColor)
{
    //绘制圆边框
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
    //计算边框矩形区域
    SDL_Rect borderRects[4];

    //上边框
    borderRects[0] =
    {
        _leftUpPosition.x,
        _leftUpPosition.y,
        _size.x,
        static_cast<int>(_borderThickness)
    };

    //下边框
    borderRects[1] =
    {
        _leftUpPosition.x,
        _leftUpPosition.y + _size.y - static_cast<int>(_borderThickness),
        _size.x,
        static_cast<int>(_borderThickness)
    };

    //左边框
    borderRects[2] =
    {
        _leftUpPosition.x,
        _leftUpPosition.y + static_cast<int>(_borderThickness),
        static_cast<int>(_borderThickness),
        _size.y - 2 * static_cast<int>(_borderThickness)
    };

    //右边框
    borderRects[3] =
    {
        _leftUpPosition.x + _size.x - static_cast<int>(_borderThickness),
        _leftUpPosition.y + static_cast<int>(_borderThickness),
        static_cast<int>(_borderThickness),
        _size.y - 2 * static_cast<int>(_borderThickness)
    };

    //设置边框颜色
    SDL_SetRenderDrawColor(_renderer, _borderColor.r, _borderColor.g,
        _borderColor.b, _borderColor.a);

    //绘制四个边框矩形
    SDL_RenderFillRects(_renderer, borderRects, 4);
}

void UIManager::DrawDynamicBar(SDL_Renderer* _renderer, const SDL_Point& _leftUpPosition, const SDL_Point& _size, int _borderThickness,
    const SDL_Color& _backgroundColor, const SDL_Color& _contentColor, double _contentRatio)
{
    static SDL_Rect _dstRect;

    //先规整传入的比例，控制在[0,1]之间
    double _ratio = (_contentRatio < 0) ? 0 : _contentRatio;
    _ratio = (_ratio > 1) ? 1 : _ratio;

    //数值值条先绘制背景颜色填充，再绘制内容颜色填充，先传入渲染器与左上顶点和右下顶点，然后是颜色
    _dstRect = { _leftUpPosition.x, _leftUpPosition.y, _size.x, _size.y };
    boxRGBA(_renderer, _dstRect.x, _dstRect.y, _dstRect.x + _dstRect.w, _dstRect.y + _dstRect.h,
        _backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a);
    //如果是如下绘制圆角矩形，则还需传入圆角半径
    //roundedBoxRGBA(_renderer, _dstRect.x, _dstRect.y, _dstRect.x + _dstRect.w, _dstRect.y + _dstRect.h,
    //	4, _backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a);

    //绘制内容的填充矩形（其水平宽度按照比例实时更新），其依据边框宽度收窄，背景颜色就相当于在内容颜色的外围形成一圈边框
    _dstRect = { _leftUpPosition.x + _borderThickness, _leftUpPosition.y + _borderThickness,
        (int)((_size.x - 2 * _borderThickness) * _ratio), _size.y - 2 * _borderThickness };
    boxRGBA(_renderer, _dstRect.x, _dstRect.y, _dstRect.x + _dstRect.w, _dstRect.y + _dstRect.h,
        _contentColor.r, _contentColor.g, _contentColor.b, _contentColor.a);
    //roundedBoxRGBA(_renderer, _dstRect.x, _dstRect.y, _dstRect.x + _dstRect.w, _dstRect.y + _dstRect.h,
    //	4, _contentColor.r, _contentColor.g, _contentColor.b, _contentColor.a);
}