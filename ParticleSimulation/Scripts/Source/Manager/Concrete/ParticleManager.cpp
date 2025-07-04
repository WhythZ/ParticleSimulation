#include "../../../Header/Manager/Concrete/ParticleManager.h"

#include <iostream>
#include <cmath>

#include "../../../Header/Manager/Concrete/GameManager.h"

const std::vector<SDL_Color> PARTICLE_COLORS =
{
    //{ 0, 0, 0, 0 },           //����ɫ��͸����
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

ParticleManager::ParticleManager()
{
    #pragma region RandomEngine
    //��ʼ�������������
    std::random_device _rd;
    rng = std::mt19937(_rd());
    #pragma endregion

	//��ȡ��Ϸ���ھ�������
    windowRect = GameManager::Instance().windowRect;
    
    #pragma region DoubleBuffer
    //��ʼ��ǰ�󻺳�
    frontBuffer.resize(windowRect.h * windowRect.w, Particle{ ParticleType::EMPTY });
    backBuffer.resize(windowRect.h * windowRect.w, Particle{ ParticleType::EMPTY });
    #pragma endregion
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::OnUpdate(double _delta)
{
    //���ú󻺳�����ע�����resize���������ȫ���·����ڴ������Ч�ʵ���
    //backBuffer.resize(windowRect.h * windowRect.w, ParticleType::EMPTY);
    std::fill(backBuffer.begin(), backBuffer.end(), Particle{ ParticleType::EMPTY });

    //ÿ�����ص����һ�����ӣ��������ϱ�����֤����Ч����ȷ��
    for (int _y = windowRect.h - 1; _y >= 0; _y--)
    {
        for (int _x = 0; _x < windowRect.w; _x++)
        {
			ParticleType& _type = frontBuffer[_y * windowRect.w + _x].type;

            //����ǰ�������������͵��ö�Ӧ���º��������½����д��󻺳���
            switch (_type)
            {
			case ParticleType::EMPTY: backBuffer[_y * windowRect.w + _x] = ParticleType::EMPTY; break;
            case ParticleType::DIRT: UpdateDirt(_x, _y); break;
            case ParticleType::STONE: UpdateStone(_x, _y); break;
            case ParticleType::WOOD: UpdateWood(_x, _y); break;
            case ParticleType::ICE: UpdateIce(_x, _y); break;
            case ParticleType::SAND: UpdateSand(_x, _y); break;
            case ParticleType::SNOW: UpdateSnow(_x, _y); break;
            case ParticleType::GUNPOWDER: UpdateGunPowder(_x, _y); break;
            case ParticleType::WATER: UpdateWater(_x, _y); break;
            case ParticleType::OIL: UpdateOil(_x, _y); break;
            case ParticleType::ACID: UpdateAcid(_x, _y); break;
            case ParticleType::LAVA: UpdateLava(_x, _y); break;
            case ParticleType::FIRE: UpdateFire(_x, _y); break;
            case ParticleType::SMOKE: UpdateSmoke(_x, _y); break;
            case ParticleType::STEAM: UpdateSteam(_x, _y); break;
            default: break;
            }
        }
    }
	//���������������󻺳����ĸ��½����Ϊǰ��������״̬
    std::swap(frontBuffer, backBuffer);
}

void ParticleManager::OnRender(SDL_Renderer* _renderer)
{
	//��Ⱦÿ�����ص�����ӣ�����������Ⱦ��ɫ
    for (int _y = 0; _y < windowRect.h; _y++)
    {
        for (int _x = 0; _x < windowRect.w; _x++)
        {
            //��ȡ��������
            ParticleType _type = frontBuffer[_y * windowRect.w + _x].type;
            //������������Ⱦ���ؼ��Ż������������ᵼ�¾޿��ޱȣ�����
			if (_type == ParticleType::EMPTY) continue;
			
            //��ȡ��Ⱦ��ɫ��ע��+1����Ϊ��ɫ������û��EMPTY����ɫ
            SDL_Color _color = PARTICLE_COLORS[static_cast<uint8_t>(_type) - 1];
            SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, _color.a);
            SDL_RenderDrawPoint(_renderer, _x, _y);
        }
    }
}

void ParticleManager::SetParticleAt(int _x, int _y, ParticleType _type)
{
    if (!IsValidPosition(_x, _y)) return;

    frontBuffer[_y * windowRect.w + _x].type = _type;
}

void ParticleManager::EmptizeParticleAt(int _x, int _y)
{
    if (!IsValidPosition(_x, _y)) return;

    //�����������ÿ�
    frontBuffer[_y * windowRect.w + _x].type = ParticleType::EMPTY;
}

bool ParticleManager::IsValidPosition(int _x, int _y) const
{
    //��������Ƿ��ڴ��ڷ�Χ��
    return (_x >= windowRect.x && _x < windowRect.x + windowRect.w)
        && (_y >= windowRect.y && _y < windowRect.y + windowRect.h);

    //��Ҫע����ǣ�Ŀǰʵ�ֵİ汾��ÿ�����ص㶼��һ��������Ƭ�����������������Ƭ����һ��
	//��������ʵ�ָ����ӵ���Ƭ����n*n�����ص����һ��������Ƭ��������ע����������ת��
}

#pragma region UpdateSpecificParticleType
void ParticleManager::UpdateDirt(int _x, int _y)
{
}

void ParticleManager::UpdateStone(int _x, int _y)
{
}

void ParticleManager::UpdateWood(int _x, int _y)
{
}

void ParticleManager::UpdateIce(int _x, int _y)
{
}

void ParticleManager::UpdateSand(int _x, int _y)
{
    //���������ƶ�
    if (IsValidPosition(_x, _y + 1))
    {
        Particle& _below = backBuffer[(_y + 1) * windowRect.w + _x];
        if (_below.type == ParticleType::EMPTY)
        {
            //����յ�ǰλ��
            backBuffer[_y * windowRect.w + _x].type = ParticleType::EMPTY;
			//���·����䣬����������������Ϊɳ��
            backBuffer[(_y + 1) * windowRect.w + _x].type = ParticleType::SAND;
            return;
        }
    }

    //���ѡ�������·����������·�
    int _dir = dist(rng) ? 1 : -1;

    //���Գ�б�·��ƶ�
    if (IsValidPosition(_x + _dir, _y + 1))
    {
        Particle& _diag = backBuffer[(_y + 1) * windowRect.w + (_x + _dir)];
        if (_diag.type == ParticleType::EMPTY)
        {
            //����յ�ǰλ��
            backBuffer[_y * windowRect.w + _x].type = ParticleType::EMPTY;
            //��б�·����䣬����������������Ϊɳ��
            backBuffer[(_y + 1) * windowRect.w + (_x + _dir)].type = ParticleType::SAND;
            return;
        }
    }
    //������һ���Խ���
    if (IsValidPosition(_x - _dir, _y + 1))
    {
        Particle& diag = backBuffer[(_y + 1) * windowRect.w + (_x - _dir)];
        if (diag.type == ParticleType::EMPTY)
        {
            //����յ�ǰλ��
			backBuffer[_y * windowRect.w + _x].type = ParticleType::EMPTY;
            //��б�·����䣬����������������Ϊɳ��
            backBuffer[(_y + 1) * windowRect.w + (_x - _dir)].type = ParticleType::SAND;
            return;
        }
    }

    //�޷��ƶ�������ԭλ
    backBuffer[_y * windowRect.w + _x].type = ParticleType::SAND;
}

void ParticleManager::UpdateSnow(int _x, int _y)
{
}

void ParticleManager::UpdateGunPowder(int _x, int _y)
{
}

void ParticleManager::UpdateWater(int _x, int _y)
{
}

void ParticleManager::UpdateOil(int _x, int _y)
{
}

void ParticleManager::UpdateAcid(int _x, int _y)
{
}

void ParticleManager::UpdateLava(int _x, int _y)
{
}

void ParticleManager::UpdateFire(int _x, int _y)
{
}

void ParticleManager::UpdateSmoke(int _x, int _y)
{
}

void ParticleManager::UpdateSteam(int _x, int _y)
{
}
#pragma endregion