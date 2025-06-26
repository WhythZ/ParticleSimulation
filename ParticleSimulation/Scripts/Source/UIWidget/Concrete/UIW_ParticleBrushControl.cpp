#include "../../../Header/UIWidget/Concrete/UIW_ParticleBrushControl.h"

#include "../../../Header/Manager/Concrete/GameManager.h"
#include "../../../Header/Manager/Concrete/UIManager.h"
#include "../../../Header/Manager/Concrete/ParticleManager.h"
#include "../../../Header/Manager/Concrete/ResourceManager.h"

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

const std::vector<std::string> PARTICLE_NAMES =
{
    "DIRT",
    "STONE",
    "WOOD",
    "ICE",
    "SAND",
    "SNOW",
    "GUNPOWDER",
    "WATER",
    "OIL",
    "ACID",
    "LAVA",
    "FIRE",
    "SMOKE",
    "STEAM"
};

UIW_ParticleBrushControl::UIW_ParticleBrushControl()
{
    //获取粒子类型数量
    int _particleTypeCount = static_cast<int>(ParticleType::COUNT);

    #pragma region ParticleMappings
    //设置每种粒子类型对应的颜色
    for (int _i = 0; _i < _particleTypeCount; _i++)
        particleColors[static_cast<ParticleType>(_i)] = PARTICLE_COLORS[_i];

	//初始化粒子类型按钮矩形，减去1是为了排除EMPTY类型
    for (int _i = 0; _i < _particleTypeCount - 1; _i++)
    {
		//注意此处(_i+1)是因为EMPTY类型（其底层类型值为0）无对应按钮和文本名称，应当从1开始
        ParticleType _type = static_cast<ParticleType>(_i + 1);
        particleButtonRects[_type] =
		{
            particleTypeSelectPanelRect.x + particleTypeSelectPanelBorderThickness
                + _i * (particleTypeButtonSize.x + particleTypeButtonDistanceBetween),
            particleTypeSelectPanelRect.y + particleTypeSelectPanelBorderThickness,
			particleTypeButtonSize.x,
            particleTypeButtonSize.y
		};
		particleNames[_type] = PARTICLE_NAMES[_i];
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
        particleTypeSelectPanelRect.y + particleTypeSelectPanelRect.h + elementDistanceBetween,
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
                DrawParticles(_cursorPosition.x, _cursorPosition.y, selectedParticleType, brushSizeCurrent);
        }
        else if (_event.button.button == SDL_BUTTON_RIGHT)
        {
            rightMouseDown = true;
            
            //擦除笔刷区域内的粒子
            EraseParticles(_cursorPosition.x, _cursorPosition.y, brushSizeCurrent);
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
            DrawParticles(_cursorPosition.x, _cursorPosition.y, selectedParticleType, brushSizeCurrent);
        //在鼠标移动路径上擦除粒子
        else if (rightMouseDown)
            EraseParticles(_cursorPosition.x, _cursorPosition.y, brushSizeCurrent);
        lastCursorPos = _cursorPosition;
    }
    break;
    case SDL_MOUSEWHEEL:
    {
        //鼠标滚轮调整画笔大小
        if (_event.wheel.y > 0)
            brushSizeCurrent = std::min(brushSizeCurrent + 1, brushSizeMaximum);
        else if (_event.wheel.y < 0)
            brushSizeCurrent = std::max(brushSizeCurrent - 1, 1);
    }
    break;
    default:
        break;
    }
}

void UIW_ParticleBrushControl::OnUpdate(SDL_Renderer* _renderer)
{
	UIWidget::OnUpdate(_renderer);

    #pragma region Clear
    //由于每帧OnUpdate函数都会生成一张文本的纹理，故先清除掉上一帧的遗留垃圾
    SDL_DestroyTexture(particleTypeTextTexture);
    particleTypeTextTexture = nullptr;
    SDL_DestroyTexture(particleTypeTextTexture);
    particleTypeTextTexture = nullptr;
    #pragma endregion

    #pragma region ParticleTypeText
    //先将文本以特定字体加载到内存中
    static TTF_Font* _font = ResourceManager::Instance().GetFontPool().find(FontResID::Ipix)->second;
    SDL_Surface* _ptTextSurface = TTF_RenderText_Blended(_font,
        particleNames[selectedParticleType].c_str(), particleTypeTextColor);
    //获取转化后的图片的长宽
    particleTypeTextSize = { _ptTextSurface->w, _ptTextSurface->h };
    //然后再将其转化为纹理格式
    particleTypeTextTexture = SDL_CreateTextureFromSurface(_renderer, _ptTextSurface);
    //然后清理已经无用了的Surface垃圾
    SDL_FreeSurface(_ptTextSurface);
    #pragma endregion
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
		brushSizeControlPanelBackgroundColor, brushSizeControlPanelContentColor,
        static_cast<double>(brushSizeCurrent) / brushSizeMaximum
    );
    #pragma endregion

    #pragma region DrawParticleTypeSelectPanel
    //绘制粒子类型选择面板的背景
    _ui.DrawFilledBox(_renderer, { particleTypeSelectPanelRect.x, particleTypeSelectPanelRect.y },
        { particleTypeSelectPanelRect.w, particleTypeSelectPanelRect.h }, particleTypeSelectPanelBackgroundColor);

    //绘制可选择的粒子类型
	for (const auto& _pair : particleButtonRects)
	{
		const ParticleType& _type = _pair.first;
		const SDL_Rect& _rect = _pair.second;
		//获取当前粒子类型对应的颜色
		const SDL_Color& _color = particleColors[_type];
	
        //绘制按钮矩形
        _ui.DrawFilledBox(_renderer, { _rect.x, _rect.y }, { _rect.w, _rect.h }, _color);
		//如果是当前选中的粒子类型，则绘制边框
		if (_type == selectedParticleType)
			_ui.DrawBoxLine(_renderer, { _rect.x, _rect.y }, { _rect.w, _rect.h }, particleTypeButtonBorderColor);
	}
    #pragma endregion

    #pragma region DrawParticleTypeName
    SDL_Point _positionLeftUp = { 0,0 };
    _positionLeftUp.x = particleTypeSelectPanelRect.x + particleTypeSelectPanelRect.w + elementDistanceBetween;
    _positionLeftUp.y = particleTypeSelectPanelRect.y;
    _ui.DrawTexture(_renderer, particleTypeTextTexture, _positionLeftUp, particleTypeTextSize);
    #pragma endregion

    #pragma region DrawCursorBrush
    //在鼠标位置绘制画笔预览
    SDL_Color _previewColor = particleColors[selectedParticleType];
    //半透明化预览颜色
    _previewColor.a /= 2;

    //绘制画笔圆圈
    if (brushSizeCurrent > 1)
        _ui.DrawCircleRing(_renderer, _cursorPosition, brushSizeCurrent, _previewColor);
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