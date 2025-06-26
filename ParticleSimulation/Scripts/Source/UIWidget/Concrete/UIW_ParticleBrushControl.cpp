#include "../../../Header/UIWidget/Concrete/UIW_ParticleBrushControl.h"

#include <SDL2_gfxPrimitives.h>

#include "../../../Header/Manager/Concrete/GameManager.h"
#include "../../../Header/Manager/Concrete/UIManager.h"
#include "../../../Header/Manager/Concrete/ParticleManager.h"

const std::vector<SDL_Color> PARTICLE_COLORS =
{
    { 0, 0, 0, 0 },           //无颜色（透明）
    { 139, 69, 19, 255 },     //深棕色
    { 128, 128, 128, 255 },   //中灰色
    { 150, 111, 51, 255 },    //原木色
    { 173, 216, 230, 220 },   //淡蓝色（半透明）
    { 194, 178, 128, 255 },   //沙黄色
    { 240, 248, 255, 255 },   //雪白色
    { 60, 60, 60, 255 },      //深黑色
    { 64, 164, 223, 200 },    //天蓝色
    { 20, 20, 20, 180 },      //亮黑色
    { 50, 255, 50, 200 },     //荧光绿
    { 255, 80, 0, 255 },      //亮橙色
    { 255, 69, 0, 255 },      //橙红色
    { 100, 100, 100, 180 },   //深灰色
    { 210, 210, 210, 150 },   //浅灰色（半透明）
};

UIW_ParticleBrushControl::UIW_ParticleBrushControl()
{
    //获取粒子类型数量
    int _particleTypeCount = static_cast<int>(ParticleType::COUNT);

    #pragma region ParticleTypeColorMapping
    //设置每种粒子类型对应的颜色
    for (int _i = 0; _i < _particleTypeCount; _i++)
        particleColors[static_cast<ParticleType>(_i)] = PARTICLE_COLORS[_i];
    #pragma endregion

    #pragma region ParticleTypeButtonRectMapping
	//初始化粒子类型按钮矩形，减去1是为了排除EMPTY类型
    for (int _i = 0; _i < _particleTypeCount - 1; _i++)
    {
		//注意此处(_i+1)是因为EMPTY类型不需要按钮，所以从1开始
        particleButtonRects[static_cast<ParticleType>(_i + 1)] =
		{
            particleTypeSelectPanelRect.x + particleTypeSelectPanelBorderThickness
                + _i * (particleTypeButtonSize.x + particleTypeButtonDistanceBetween),
            particleTypeSelectPanelRect.y + particleTypeSelectPanelBorderThickness,
			particleTypeButtonSize.x,
            particleTypeButtonSize.y
		};
    }
    #pragma endregion

    #pragma region ParticleTypeSelectPanelRect
	//初始化粒子选择面板矩形区域的宽度和高度
    particleTypeSelectPanelRect.w = 2 * particleTypeSelectPanelBorderThickness + 
        (_particleTypeCount - 1) * (particleTypeButtonSize.x + particleTypeButtonDistanceBetween)
        - particleTypeButtonDistanceBetween;
    particleTypeSelectPanelRect.h = 2 * particleTypeSelectPanelBorderThickness + particleTypeButtonSize.y;
    #pragma endregion

    #pragma region BrushSizeControlPanelRect
	//根据前面的尺寸，对应地设置画笔大小控制面板矩形区域，保持连贯的美观性
    brushSizeControlPanelRect =
    {
        particleTypeSelectPanelRect.x,
        particleTypeSelectPanelRect.y + particleTypeSelectPanelRect.h + panelDistanceBetween,
        particleTypeSelectPanelRect.w,
        particleTypeSelectPanelRect.h / 3
    };
    #pragma endregion
}

UIW_ParticleBrushControl::~UIW_ParticleBrushControl()
{
}

void UIW_ParticleBrushControl::OnInput(const SDL_Event& _event)
{
	UIWidget::OnInput(_event);

    //获取鼠标指针位置
	static const UIManager& _ui = UIManager::Instance();
	const SDL_Point& _cursorPosition = _ui.cursorPosition;

    switch (_event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
    {
        if (_event.button.button == SDL_BUTTON_LEFT)
        {
            leftMouseDown = true;

            //若点击到了粒子类型选择面板，则检查切换粒子类型
            if (SDL_PointInRect(&_cursorPosition, &particleTypeSelectPanelRect))
            {
				//遍历所有粒子类型按钮，检查是否点击到了某个按钮
				for (const auto& _pair : particleButtonRects)
				{
					const ParticleType& _type = _pair.first;
					const SDL_Rect& _rect = _pair.second;
					
                    //如果鼠标点击在某个粒子类型按钮上，则切换到该粒子类型
					if (SDL_PointInRect(&_cursorPosition, &_rect))
					{
                        //更新当前粒子类型
						selectedParticleType = _type;
						break;
					}
				}
            }
            //否则没点到，那就绘制当前选中类型的粒子
            else
                DrawParticles(_cursorPosition.x, _cursorPosition.y, selectedParticleType, brushSize);
        }
        else if (_event.button.button == SDL_BUTTON_RIGHT)
        {
            rightMouseDown = true;
            
            //擦除笔刷区域内的粒子
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
        if (leftMouseDown && !SDL_PointInRect(&_cursorPosition, &particleTypeSelectPanelRect))
            DrawParticles(_cursorPosition.x, _cursorPosition.y, selectedParticleType, brushSize);
        //在鼠标移动路径上擦除粒子
        else if (rightMouseDown)
            EraseParticles(_cursorPosition.x, _cursorPosition.y, brushSize);
        lastCursorPos = _cursorPosition;
    }
    break;
    case SDL_MOUSEWHEEL:
    {
        //鼠标滚轮调整画笔大小
        if (_event.wheel.y > 0)
            brushSize = std::min(brushSize + 1, brushSizeMax);
        else if (_event.wheel.y < 0)
            brushSize = std::max(brushSize - 1, 1);
    }
    break;
    default:
        break;
    }
}

void UIW_ParticleBrushControl::OnUpdate(SDL_Renderer* _renderer)
{
	UIWidget::OnUpdate(_renderer);
}

void UIW_ParticleBrushControl::OnRender(SDL_Renderer* _renderer)
{
	UIWidget::OnRender(_renderer);

    //获取需要用到的管理器
    static UIManager& _ui = UIManager::Instance();
    static ParticleManager& _pm = ParticleManager::Instance();
    
    //获取鼠标指针位置
    const SDL_Point& _cursorPosition = _ui.cursorPosition;

    #pragma region DrawBrushSizeControlPanel
    //绘制笔刷大小提示条
	_ui.DrawDynamicBar(_renderer,
        { brushSizeControlPanelRect.x, brushSizeControlPanelRect.y },
		{ brushSizeControlPanelRect.w, brushSizeControlPanelRect.h },
        brushSizeControlPanelBorderThickness,
		{ 100, 100, 100, 255 }, { 200, 200, 200, 255 },
        static_cast<double>(brushSize) / brushSizeMax
    );
    #pragma endregion

    #pragma region DrawParticleTypeSelectPanel
    //绘制例子类型选择面板的背景
    _ui.DrawBox(_renderer, { particleTypeSelectPanelRect.x, particleTypeSelectPanelRect.y },
        { particleTypeSelectPanelRect.w, particleTypeSelectPanelRect.h }, { 50, 50, 50, 200 });

    //绘制可选择的粒子类型
	for (const auto& _pair : particleButtonRects)
	{
		const ParticleType& _type = _pair.first;
		const SDL_Rect& _rect = _pair.second;
		//获取当前粒子类型对应的颜色
		const SDL_Color& _color = particleColors[_type];
	
        //绘制按钮矩形
        _ui.DrawBox(_renderer, { _rect.x, _rect.y }, { _rect.w, _rect.h }, _color);
		//如果是当前选中的粒子类型，则绘制白色边框
		if (_type == selectedParticleType)
			rectangleRGBA(_renderer, _rect.x, _rect.y, _rect.x + _rect.w, _rect.y + _rect.h, 255, 255, 255, 255);
	}
    #pragma endregion

    #pragma region DrawCursorBrush
    //在鼠标位置绘制画笔预览
    SDL_Color _previewColor = particleColors[selectedParticleType];
    //半透明化预览颜色
    _previewColor.a /= 2;

    if (brushSize > 1)
    {
        //绘制画笔圆圈
        aacircleRGBA(_renderer, _cursorPosition.x, _cursorPosition.y, brushSize,
            _previewColor.r, _previewColor.g, _previewColor.b, _previewColor.a);
    }
    #pragma endregion
}

void UIW_ParticleBrushControl::DrawParticles(int _centerX, int _centerY, ParticleType _type, int _radius)
{
    static GameManager& _gm = GameManager::Instance();
    static ParticleManager& _pm = ParticleManager::Instance();

    //计算影响区域
    int _minX = std::max(0, _centerX - _radius);
    int _maxX = std::min(_gm.windowRect.w - 1, _centerX + _radius);
    int _minY = std::max(0, _centerY - _radius);
    int _maxY = std::min(_gm.windowRect.h - 1, _centerY + _radius);

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

void UIW_ParticleBrushControl::EraseParticles(int _centerX, int _centerY, int _radius)
{
    static GameManager& _gm = GameManager::Instance();
    static ParticleManager& _pm = ParticleManager::Instance();

    //计算影响区域
    int _minX = std::max(0, _centerX - _radius);
    int _maxX = std::min(_gm.windowRect.w - 1, _centerX + _radius);
    int _minY = std::max(0, _centerY - _radius);
    int _maxY = std::min(_gm.windowRect.h - 1, _centerY + _radius);

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