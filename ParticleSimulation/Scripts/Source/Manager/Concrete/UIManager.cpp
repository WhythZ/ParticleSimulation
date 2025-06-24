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
            //����Ƿ�����UI����
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
        //������ƶ�·���ϻ�������
        if (leftMouseDown && !SDL_PointInRect(&_cursorPosition, &particleSelectorRect))
            DrawParticles(_cursorPosition.x, _cursorPosition.y, selectedParticle, brushSize);
        //������ƶ�·���ϲ�������
        else if (rightMouseDown)
            EraseParticles(_cursorPosition.x, _cursorPosition.y, brushSize);
        lastMousePos = _cursorPosition;
    }
        break;
    case SDL_MOUSEWHEEL:
    {
        //�����ֵ������ʴ�С
        if (_event.wheel.y > 0)
            brushSize = std::min(brushSize + 1, 20);
        else if (_event.wheel.y < 0)
            brushSize = std::max(brushSize - 1, 1);
    }
        break;
    case SDL_KEYDOWN:
    {
        //���̿�ݼ��л���������
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

    //����UIԪ��
    DrawParticleSelector(_renderer);
    DrawBrushSizeControl(_renderer);

    //�����λ�û��ƻ���Ԥ��
    SDL_Color previewColor = _particleColors[selectedParticle];
    //��͸��Ԥ��
    previewColor.a = 100;

    if (brushSize > 1)
    {
        //���ƻ���ԲȦ
        aacircleRGBA(_renderer, _cursorPosition.x, _cursorPosition.y, brushSize,
            previewColor.r, previewColor.g, previewColor.b, previewColor.a);
    }
    else
    {
        //���Ƶ������ص�
        SDL_SetRenderDrawColor(_renderer, previewColor.r, previewColor.g, previewColor.b, previewColor.a);
        SDL_RenderDrawPoint(_renderer, _cursorPosition.x, _cursorPosition.y);
    }
}

void UIManager::DrawParticles(int _centerX, int _centerY, ParticleType _type, int _radius)
{
    static ParticleManager& _pm = ParticleManager::Instance();
    static auto& _particleColors = _pm.particleColors;

    //����Ӱ������
    int _minX = std::max(0, _centerX - _radius);
    int _maxX = std::min(GameManager::Instance().windowRect.w - 1, _centerX + _radius);
    int _minY = std::max(0, _centerY - _radius);
    int _maxY = std::min(GameManager::Instance().windowRect.h - 1, _centerY + _radius);

    //��Բ���������������
    for (int _y = _minY; _y <= _maxY; _y++)
    {
        for (int _x = _minX; _x <= _maxX; _x++)
        {
            //����㵽Բ�ĵľ���
            double _dist = std::sqrt((_x - _centerX) * (_x - _centerX) + (_y - _centerY) * (_y - _centerY));

            //�����Բ�ڣ��������
            if (_dist <= _radius)
            {
                //���ݾ������ĵ�λ������һЩ�����
                if (_dist < _radius * 0.7 || (rand() % 100) < 70)
                    _pm.AddParticle(_x, _y, _type);
            }
        }
    }
}

void UIManager::EraseParticles(int _centerX, int _centerY, int _radius)
{
    static ParticleManager& _pm = ParticleManager::Instance();

    //����Ӱ������
    int _minX = std::max(0, _centerX - _radius);
    int _maxX = std::min(GameManager::Instance().windowRect.w - 1, _centerX + _radius);
    int _minY = std::max(0, _centerY - _radius);
    int _maxY = std::min(GameManager::Instance().windowRect.h - 1, _centerY + _radius);

    //��Բ�������ڲ�������
    for (int _y = _minY; _y <= _maxY; _y++)
    {
        for (int _x = _minX; _x <= _maxX; _x++)
        {
            //����㵽Բ�ĵľ���
            double _dist = std::sqrt((_x - _centerX) * (_x - _centerX) + (_y - _centerY) * (_y - _centerY));

            //�����Բ�ڣ���������
            if (_dist <= _radius)
                _pm.RemoveParticle(_x, _y);
        }
    }
}

void UIManager::DrawParticleSelector(SDL_Renderer* _renderer)
{
    static ParticleManager& _pm = ParticleManager::Instance();
    static auto& _particleColors = _pm.particleColors;

    //����ѡ��������
    DrawBox(_renderer, { particleSelectorRect.x, particleSelectorRect.y },
        { particleSelectorRect.w, particleSelectorRect.h }, { 50, 50, 50, 200 });

    //���ƿ�ѡ�����������
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

        //�������Ӱ�ť
        DrawBox(_renderer, { x, y }, { _buttonSize, _buttonSize }, color);

        //���ǵ�ǰѡ�е����ӣ�����2���غ�ı߿�
        if (types[_i] == selectedParticle)
            DrawBorder(_renderer, { x, y }, { _buttonSize, _buttonSize }, 2, { 255, 255, 255, 255 });
    }
}

void UIManager::DrawBrushSizeControl(SDL_Renderer* _renderer)
{
    //���Ʊ���
    DrawBox(_renderer, { brushSizeRect.x, brushSizeRect.y },
        { brushSizeRect.w, brushSizeRect.h }, { 50, 50, 50, 200 });

    //���ƻ��ʴ�Сָʾ��
    SDL_Color indicatorColor = { 200, 200, 200, 255 };
    int indicatorWidth = brushSize * 5;
    int indicatorX = brushSizeRect.x + (brushSizeRect.w - indicatorWidth) / 2;
    int indicatorY = brushSizeRect.y + (brushSizeRect.h - 10) / 2;

    DrawBox(_renderer, { indicatorX, indicatorY }, { indicatorWidth, 10 }, indicatorColor);

    //�����ı���ʾ��������
}

#pragma region BasicShapes
void UIManager::DrawTexture(SDL_Renderer* _renderer, SDL_Texture* _texture, const SDL_Point& _LeftUpPosition, const SDL_Point& _size)
{
	//��ʱ�洢ÿ����ȾԪ�أ�ÿ����Ⱦ����Ԫ��ʱ����
	static SDL_Rect _dstRect;

	//���ݴ���Ķ�����ߴ��������
	_dstRect = { _LeftUpPosition.x, _LeftUpPosition.y, _size.x, _size.y };
	SDL_RenderCopy(_renderer, _texture, nullptr, &_dstRect);
}

void UIManager::DrawCircle(SDL_Renderer* _renderer, const SDL_Point& _LeftUpPosition, double _radius,
	const SDL_Color& _borderColor, const SDL_Color& _contentColor)
{
	//����Բ���
	filledCircleRGBA(_renderer, _LeftUpPosition.x, _LeftUpPosition.y, (Sint16)_radius,
		_contentColor.r, _contentColor.g, _contentColor.b, _contentColor.a);
	//����Բ�߿�
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
    //����߿��������
    SDL_Rect borderRects[4];

    //�ϱ߿�
    borderRects[0] =
    {
        _LeftUpPosition.x,
        _LeftUpPosition.y,
        _size.x,
        static_cast<int>(_borderThickness)
    };

    //�±߿�
    borderRects[1] =
    {
        _LeftUpPosition.x,
        _LeftUpPosition.y + _size.y - static_cast<int>(_borderThickness),
        _size.x,
        static_cast<int>(_borderThickness)
    };

    //��߿�
    borderRects[2] =
    {
        _LeftUpPosition.x,
        _LeftUpPosition.y + static_cast<int>(_borderThickness),
        static_cast<int>(_borderThickness),
        _size.y - 2 * static_cast<int>(_borderThickness)
    };

    //�ұ߿�
    borderRects[3] =
    {
        _LeftUpPosition.x + _size.x - static_cast<int>(_borderThickness),
        _LeftUpPosition.y + static_cast<int>(_borderThickness),
        static_cast<int>(_borderThickness),
        _size.y - 2 * static_cast<int>(_borderThickness)
    };

    //���ñ߿���ɫ
    SDL_SetRenderDrawColor(_renderer, _borderColor.r, _borderColor.g,
        _borderColor.b, _borderColor.a);

    //�����ĸ��߿����
    SDL_RenderFillRects(_renderer, borderRects, 4);
}
#pragma endregion