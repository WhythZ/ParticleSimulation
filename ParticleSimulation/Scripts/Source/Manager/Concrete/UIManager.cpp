#include "../../../Header/Manager/Concrete/UIManager.h"

#include <iostream>
#include <SDL2_gfxPrimitives.h>

#include "../../../Header/Manager/Concrete/GameManager.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::OnInput(const SDL_Event& _event)
{
	switch (_event.type)
	{
	case SDL_MOUSEBUTTONUP:
		break;
	default:
		break;
	}
}

void UIManager::OnUpdate(SDL_Renderer* _renderer)
{
}

void UIManager::OnRender(SDL_Renderer* _renderer)
{
}

void UIManager::DrawTexture(SDL_Renderer* _renderer, SDL_Texture* _texture, const SDL_Point& _LeftUpPosition, const SDL_Point& _size)
{
	//临时存储每个渲染元素，每次渲染单个元素时复用
	static SDL_Rect _dstRect;

	//根据传入的顶点与尺寸绘制纹理
	_dstRect = { _LeftUpPosition.x, _LeftUpPosition.y, _size.x, _size.y };
	SDL_RenderCopy(_renderer, _texture, nullptr, &_dstRect);
}

void UIManager::DrawCircle(SDL_Renderer* _renderer, const SDL_Point& _LeftUpPosition, double _radius,
	const SDL_Color& _borderColor, const SDL_Color& _contentColor)
{
	//绘制圆填充
	filledCircleRGBA(_renderer, _LeftUpPosition.x, _LeftUpPosition.y, (Sint16)_radius,
		_contentColor.r, _contentColor.g, _contentColor.b, _contentColor.a);
	//绘制圆边框
	aacircleRGBA(_renderer, _LeftUpPosition.x, _LeftUpPosition.y, (Sint16)_radius,
		_borderColor.r, _borderColor.g, _borderColor.b, _borderColor.a);
}

void UIManager::DrawBox(SDL_Renderer* _renderer, const SDL_Point& _LeftUpPosition, const SDL_Point& _size, const SDL_Color& _color)
{
	boxRGBA(_renderer, _LeftUpPosition.x, _LeftUpPosition.y, _LeftUpPosition.x + _size.x, _LeftUpPosition.y + _size.y,
		_color.r, _color.g, _color.b, _color.a);
}