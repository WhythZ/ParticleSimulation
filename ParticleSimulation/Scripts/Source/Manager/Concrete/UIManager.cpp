#include "../../../Header/Manager/Concrete/UIManager.h"

#include <iostream>
#include <SDL2_gfxPrimitives.h>

#include "../../../Header/Manager/Concrete/GameManager.h"
#include "../../../Header/Manager/Concrete/ParticleManager.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::OnInput(const SDL_Event& _event)
{
    static GameManager& _gm = GameManager::Instance();
    SDL_Point _cursorPosition = _gm.cursorPosition;

    switch (_event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
    {
        if (_event.button.button == SDL_BUTTON_LEFT)
        {
            leftMouseDown = true;
            //检查是否点击了UI区域
            if (!SDL_PointInRect(&_cursorPosition, &particleSelectorRect))
                DrawParticles(_cursorPosition.x, _cursorPosition.y, selectedParticle, brushSize);
        }
        else if (_event.button.button == SDL_BUTTON_RIGHT)
        {
            rightMouseDown = true;
            EraseParticles(_cursorPosition.x, _cursorPosition.y, brushSize);
        }
    }
        break;
    case SDL_MOUSEBUTTONUP:
    {
        if (_event.button.button == SDL_BUTTON_LEFT)
            leftMouseDown = false;
        else if (_event.button.button == SDL_BUTTON_RIGHT)
            rightMouseDown = false;
    }
        break;
    case SDL_MOUSEMOTION:
    {
        //在鼠标移动路径上绘制粒子
        if (leftMouseDown && !SDL_PointInRect(&_cursorPosition, &particleSelectorRect))
            DrawParticles(_cursorPosition.x, _cursorPosition.y, selectedParticle, brushSize);
        //在鼠标移动路径上擦除粒子
        else if (rightMouseDown)
            EraseParticles(_cursorPosition.x, _cursorPosition.y, brushSize);
        lastMousePos = _cursorPosition;
    }
        break;
    case SDL_MOUSEWHEEL:
    {
        //鼠标滚轮调整画笔大小
        if (_event.wheel.y > 0)
            brushSize = std::min(brushSize + 1, 20);
        else if (_event.wheel.y < 0)
            brushSize = std::max(brushSize - 1, 1);
    }
        break;
    case SDL_KEYDOWN:
    {
        //键盘快捷键切换粒子类型
        //switch (_event.key.keysym.sym)
        //{
        //case SDLK_1: selectedParticle = ParticleType::; break;
        //case SDLK_2: selectedParticle = ParticleType::; break;
        //default: break;
        //}
    }
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
    static auto& _particleColors = ParticleManager::Instance().particleColors;
    static GameManager& _gm = GameManager::Instance();
    SDL_Point _cursorPosition = _gm.cursorPosition;

    //绘制UI元素
    DrawParticleSelector(_renderer);
    DrawBrushSizeControl(_renderer);

    //在鼠标位置绘制画笔预览
    SDL_Color previewColor = _particleColors[selectedParticle];
    //半透明预览
    previewColor.a = 100;

    if (brushSize > 1)
    {
        //绘制画笔圆圈
        aacircleRGBA(_renderer, _cursorPosition.x, _cursorPosition.y, brushSize,
            previewColor.r, previewColor.g, previewColor.b, previewColor.a);
    }
    else
    {
        //绘制单个像素点
        SDL_SetRenderDrawColor(_renderer, previewColor.r, previewColor.g, previewColor.b, previewColor.a);
        SDL_RenderDrawPoint(_renderer, _cursorPosition.x, _cursorPosition.y);
    }
}

void UIManager::DrawParticles(int _centerX, int _centerY, ParticleType _type, int _radius)
{
    static ParticleManager& _pm = ParticleManager::Instance();
    static auto& _particleColors = _pm.particleColors;

    //计算影响区域
    int _minX = std::max(0, _centerX - _radius);
    int _maxX = std::min(GameManager::Instance().windowRect.w - 1, _centerX + _radius);
    int _minY = std::max(0, _centerY - _radius);
    int _maxY = std::min(GameManager::Instance().windowRect.h - 1, _centerY + _radius);

    //在圆形区域内添加粒子
    for (int _y = _minY; _y <= _maxY; _y++)
    {
        for (int _x = _minX; _x <= _maxX; _x++)
        {
            //计算点到圆心的距离
            double _dist = std::sqrt((_x - _centerX) * (_x - _centerX) + (_y - _centerY) * (_y - _centerY));

            //如果在圆内，添加粒子
            if (_dist <= _radius)
            {
                //根据距离中心的位置增加一些随机性
                if (_dist < _radius * 0.7 || (rand() % 100) < 70)
                    _pm.AddParticle(_x, _y, _type);
            }
        }
    }
}

void UIManager::EraseParticles(int _centerX, int _centerY, int _radius)
{
    static ParticleManager& _pm = ParticleManager::Instance();

    //计算影响区域
    int _minX = std::max(0, _centerX - _radius);
    int _maxX = std::min(GameManager::Instance().windowRect.w - 1, _centerX + _radius);
    int _minY = std::max(0, _centerY - _radius);
    int _maxY = std::min(GameManager::Instance().windowRect.h - 1, _centerY + _radius);

    //在圆形区域内擦除粒子
    for (int _y = _minY; _y <= _maxY; _y++)
    {
        for (int _x = _minX; _x <= _maxX; _x++)
        {
            //计算点到圆心的距离
            double _dist = std::sqrt((_x - _centerX) * (_x - _centerX) + (_y - _centerY) * (_y - _centerY));

            //如果在圆内，擦除粒子
            if (_dist <= _radius)
                _pm.RemoveParticle(_x, _y);
        }
    }
}

void UIManager::DrawParticleSelector(SDL_Renderer* _renderer)
{
    static ParticleManager& _pm = ParticleManager::Instance();
    static auto& _particleColors = _pm.particleColors;

    //绘制选择器背景
    DrawBox(_renderer, { particleSelectorRect.x, particleSelectorRect.y },
        { particleSelectorRect.w, particleSelectorRect.h }, { 50, 50, 50, 200 });

    //绘制可选择的粒子类型
    const std::vector<ParticleType> types =
    {
        ParticleType::DIRT, ParticleType::STONE, ParticleType::WOOD, ParticleType::ICE,
        ParticleType::SAND, ParticleType::SNOW, ParticleType::GUNPOWDER, ParticleType::SALT,
        ParticleType::WATER, ParticleType::OIL, ParticleType::ACID, ParticleType::LAVA,
        ParticleType::FIRE, ParticleType::SMOKE, ParticleType::STEAM
    };

    int _buttonSize = 30;
    int _margin = 5;
    int _startX = particleSelectorRect.x + _margin;
    int _startY = particleSelectorRect.y + _margin;

    for (size_t _i = 0; _i < types.size(); _i++)
    {
        int x = _startX + _i * (_buttonSize + _margin);
        int y = _startY;

        SDL_Color color = _particleColors[types[_i]];

        //绘制粒子按钮
        DrawBox(_renderer, { x, y }, { _buttonSize, _buttonSize }, color);

        //若是当前选中的粒子，绘制2像素厚的边框
        if (types[_i] == selectedParticle)
            DrawBorder(_renderer, { x, y }, { _buttonSize, _buttonSize }, 2, { 255, 255, 255, 255 });
    }
}

void UIManager::DrawBrushSizeControl(SDL_Renderer* _renderer)
{
    //绘制背景
    DrawBox(_renderer, { brushSizeRect.x, brushSizeRect.y },
        { brushSizeRect.w, brushSizeRect.h }, { 50, 50, 50, 200 });

    //绘制画笔大小指示器
    SDL_Color indicatorColor = { 200, 200, 200, 255 };
    int indicatorWidth = brushSize * 5;
    int indicatorX = brushSizeRect.x + (brushSizeRect.w - indicatorWidth) / 2;
    int indicatorY = brushSizeRect.y + (brushSizeRect.h - 10) / 2;

    DrawBox(_renderer, { indicatorX, indicatorY }, { indicatorWidth, 10 }, indicatorColor);

    //绘制文本提示，待补充
}

#pragma region BasicShapes
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

void UIManager::DrawBorder(SDL_Renderer* _renderer, const SDL_Point& _LeftUpPosition, const SDL_Point& _size,
    size_t _borderThickness, const SDL_Color& _borderColor)
{
    //计算边框矩形区域
    SDL_Rect borderRects[4];

    //上边框
    borderRects[0] =
    {
        _LeftUpPosition.x,
        _LeftUpPosition.y,
        _size.x,
        static_cast<int>(_borderThickness)
    };

    //下边框
    borderRects[1] =
    {
        _LeftUpPosition.x,
        _LeftUpPosition.y + _size.y - static_cast<int>(_borderThickness),
        _size.x,
        static_cast<int>(_borderThickness)
    };

    //左边框
    borderRects[2] =
    {
        _LeftUpPosition.x,
        _LeftUpPosition.y + static_cast<int>(_borderThickness),
        static_cast<int>(_borderThickness),
        _size.y - 2 * static_cast<int>(_borderThickness)
    };

    //右边框
    borderRects[3] =
    {
        _LeftUpPosition.x + _size.x - static_cast<int>(_borderThickness),
        _LeftUpPosition.y + static_cast<int>(_borderThickness),
        static_cast<int>(_borderThickness),
        _size.y - 2 * static_cast<int>(_borderThickness)
    };

    //设置边框颜色
    SDL_SetRenderDrawColor(_renderer, _borderColor.r, _borderColor.g,
        _borderColor.b, _borderColor.a);

    //绘制四个边框矩形
    SDL_RenderFillRects(_renderer, borderRects, 4);
}
#pragma endregion