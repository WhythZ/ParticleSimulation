#include "../../../Header/UIWidget/Concrete/UIW_ParticleBrushControl.h"

#include <SDL2_gfxPrimitives.h>

#include "../../../Header/Manager/Concrete/GameManager.h"
#include "../../../Header/Manager/Concrete/UIManager.h"
#include "../../../Header/Manager/Concrete/ParticleManager.h"

const std::vector<SDL_Color> PARTICLE_COLORS =
{
    { 0, 0, 0, 0 },           //����ɫ��͸����
    { 139, 69, 19, 255 },     //����ɫ
    { 128, 128, 128, 255 },   //�л�ɫ
    { 150, 111, 51, 255 },    //ԭľɫ
    { 173, 216, 230, 220 },   //����ɫ����͸����
    { 194, 178, 128, 255 },   //ɳ��ɫ
    { 240, 248, 255, 255 },   //ѩ��ɫ
    { 60, 60, 60, 255 },      //���ɫ
    { 64, 164, 223, 200 },    //����ɫ
    { 20, 20, 20, 180 },      //����ɫ
    { 50, 255, 50, 200 },     //ӫ����
    { 255, 80, 0, 255 },      //����ɫ
    { 255, 69, 0, 255 },      //�Ⱥ�ɫ
    { 100, 100, 100, 180 },   //���ɫ
    { 210, 210, 210, 150 },   //ǳ��ɫ����͸����
};

UIW_ParticleBrushControl::UIW_ParticleBrushControl()
{
    //��ȡ������������
    int _particleTypeCount = static_cast<int>(ParticleType::COUNT);

    #pragma region ParticleTypeColorMapping
    //����ÿ���������Ͷ�Ӧ����ɫ
    for (int _i = 0; _i < _particleTypeCount; _i++)
        particleColors[static_cast<ParticleType>(_i)] = PARTICLE_COLORS[_i];
    #pragma endregion

    #pragma region ParticleTypeButtonRectMapping
	//��ʼ���������Ͱ�ť���Σ���ȥ1��Ϊ���ų�EMPTY����
    for (int _i = 0; _i < _particleTypeCount - 1; _i++)
    {
		//ע��˴�(_i+1)����ΪEMPTY���Ͳ���Ҫ��ť�����Դ�1��ʼ
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
	//��ʼ������ѡ������������Ŀ�Ⱥ͸߶�
    particleTypeSelectPanelRect.w = 2 * particleTypeSelectPanelBorderThickness + 
        (_particleTypeCount - 1) * (particleTypeButtonSize.x + particleTypeButtonDistanceBetween)
        - particleTypeButtonDistanceBetween;
    particleTypeSelectPanelRect.h = 2 * particleTypeSelectPanelBorderThickness + particleTypeButtonSize.y;
    #pragma endregion

    #pragma region BrushSizeControlPanelRect
	//����ǰ��ĳߴ磬��Ӧ�����û��ʴ�С�������������򣬱��������������
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

    //��ȡ���ָ��λ��
	static const UIManager& _ui = UIManager::Instance();
	const SDL_Point& _cursorPosition = _ui.cursorPosition;

    switch (_event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
    {
        if (_event.button.button == SDL_BUTTON_LEFT)
        {
            leftMouseDown = true;

            //�����������������ѡ����壬�����л���������
            if (SDL_PointInRect(&_cursorPosition, &particleTypeSelectPanelRect))
            {
				//���������������Ͱ�ť������Ƿ�������ĳ����ť
				for (const auto& _pair : particleButtonRects)
				{
					const ParticleType& _type = _pair.first;
					const SDL_Rect& _rect = _pair.second;
					
                    //����������ĳ���������Ͱ�ť�ϣ����л�������������
					if (SDL_PointInRect(&_cursorPosition, &_rect))
					{
                        //���µ�ǰ��������
						selectedParticleType = _type;
						break;
					}
				}
            }
            //����û�㵽���Ǿͻ��Ƶ�ǰѡ�����͵�����
            else
                DrawParticles(_cursorPosition.x, _cursorPosition.y, selectedParticleType, brushSize);
        }
        else if (_event.button.button == SDL_BUTTON_RIGHT)
        {
            rightMouseDown = true;
            
            //������ˢ�����ڵ�����
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
        if (leftMouseDown && !SDL_PointInRect(&_cursorPosition, &particleTypeSelectPanelRect))
            DrawParticles(_cursorPosition.x, _cursorPosition.y, selectedParticleType, brushSize);
        //������ƶ�·���ϲ�������
        else if (rightMouseDown)
            EraseParticles(_cursorPosition.x, _cursorPosition.y, brushSize);
        lastCursorPos = _cursorPosition;
    }
    break;
    case SDL_MOUSEWHEEL:
    {
        //�����ֵ������ʴ�С
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

    //��ȡ��Ҫ�õ��Ĺ�����
    static UIManager& _ui = UIManager::Instance();
    static ParticleManager& _pm = ParticleManager::Instance();
    
    //��ȡ���ָ��λ��
    const SDL_Point& _cursorPosition = _ui.cursorPosition;

    #pragma region DrawBrushSizeControlPanel
    //���Ʊ�ˢ��С��ʾ��
	_ui.DrawDynamicBar(_renderer,
        { brushSizeControlPanelRect.x, brushSizeControlPanelRect.y },
		{ brushSizeControlPanelRect.w, brushSizeControlPanelRect.h },
        brushSizeControlPanelBorderThickness,
		{ 100, 100, 100, 255 }, { 200, 200, 200, 255 },
        static_cast<double>(brushSize) / brushSizeMax
    );
    #pragma endregion

    #pragma region DrawParticleTypeSelectPanel
    //������������ѡ�����ı���
    _ui.DrawBox(_renderer, { particleTypeSelectPanelRect.x, particleTypeSelectPanelRect.y },
        { particleTypeSelectPanelRect.w, particleTypeSelectPanelRect.h }, { 50, 50, 50, 200 });

    //���ƿ�ѡ�����������
	for (const auto& _pair : particleButtonRects)
	{
		const ParticleType& _type = _pair.first;
		const SDL_Rect& _rect = _pair.second;
		//��ȡ��ǰ�������Ͷ�Ӧ����ɫ
		const SDL_Color& _color = particleColors[_type];
	
        //���ư�ť����
        _ui.DrawBox(_renderer, { _rect.x, _rect.y }, { _rect.w, _rect.h }, _color);
		//����ǵ�ǰѡ�е��������ͣ�����ư�ɫ�߿�
		if (_type == selectedParticleType)
			rectangleRGBA(_renderer, _rect.x, _rect.y, _rect.x + _rect.w, _rect.y + _rect.h, 255, 255, 255, 255);
	}
    #pragma endregion

    #pragma region DrawCursorBrush
    //�����λ�û��ƻ���Ԥ��
    SDL_Color _previewColor = particleColors[selectedParticleType];
    //��͸����Ԥ����ɫ
    _previewColor.a /= 2;

    if (brushSize > 1)
    {
        //���ƻ���ԲȦ
        aacircleRGBA(_renderer, _cursorPosition.x, _cursorPosition.y, brushSize,
            _previewColor.r, _previewColor.g, _previewColor.b, _previewColor.a);
    }
    #pragma endregion
}

void UIW_ParticleBrushControl::DrawParticles(int _centerX, int _centerY, ParticleType _type, int _radius)
{
    static GameManager& _gm = GameManager::Instance();
    static ParticleManager& _pm = ParticleManager::Instance();

    //����Ӱ������
    int _minX = std::max(0, _centerX - _radius);
    int _maxX = std::min(_gm.windowRect.w - 1, _centerX + _radius);
    int _minY = std::max(0, _centerY - _radius);
    int _maxY = std::min(_gm.windowRect.h - 1, _centerY + _radius);

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

void UIW_ParticleBrushControl::EraseParticles(int _centerX, int _centerY, int _radius)
{
    static GameManager& _gm = GameManager::Instance();
    static ParticleManager& _pm = ParticleManager::Instance();

    //����Ӱ������
    int _minX = std::max(0, _centerX - _radius);
    int _maxX = std::min(_gm.windowRect.w - 1, _centerX + _radius);
    int _minY = std::max(0, _centerY - _radius);
    int _maxY = std::min(_gm.windowRect.h - 1, _centerY + _radius);

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