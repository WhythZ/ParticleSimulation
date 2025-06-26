#include "../../../Header/Manager/Concrete/ParticleManager.h"

#include <iostream>
#include <cmath>

#include "../../../Header/Manager/Concrete/GameManager.h"

ParticleManager::ParticleManager()
{
    #pragma region RandomEngine
    //��ʼ�������������
    std::random_device _rd;
    rng = std::mt19937(_rd());
    #pragma endregion

    #pragma region DoubleBuffer
    //����˫�����ڴ�
    windowRect = GameManager::Instance().windowRect;
    frontBuffer = new Particle[windowRect.w * windowRect.h];
    backBuffer = new Particle[windowRect.w * windowRect.h];
    #pragma endregion

    //����Գ�ʼ��
    ClearParticles();
}

ParticleManager::~ParticleManager()
{
	//�ͷ�˫�����ڴ�
    delete[] frontBuffer;
    delete[] backBuffer;
}

void ParticleManager::OnUpdate(double _delta)
{   
    //���ú󻺳�
    std::fill_n(backBuffer, windowRect.w * windowRect.h, Particle{});

    //ÿ�����ص����һ�����ӣ�������Ļ���ص��������״̬���ӵײ����ϸ��±������˳��Ӱ������Ч��
    for (int _y = windowRect.h - 1; _y >= 0; _y--)
    {
        for (int _x = 0; _x < windowRect.w; _x++)
        {
            Particle& _particle = frontBuffer[_y * windowRect.w + _x];

            if (_particle.type == ParticleType::EMPTY) continue;

            //�����������͵��ø��º���
            switch (_particle.type)
            {
            case ParticleType::EMPTY: UpdateEmpty(_x, _y); break;
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
            //�����������ͱ���ԭλ
            default: backBuffer[_y * windowRect.w + _x] = _particle; break;
            }
        }
    }
    //����������
    SwapBuffers();
}

void ParticleManager::OnRender(SDL_Renderer* _renderer)
{
	//��Ⱦÿ�����ص��Ӧ������Ϊһ���ض���ɫ��������Gammaֵģ���ӰЧ����
    for (int _y = 0; _y < windowRect.h; _y++)
    {
        for (int _x = 0; _x < windowRect.w; _x++)
        {
            Particle& _particle = frontBuffer[_y * windowRect.w + _x];
            if (_particle.type == ParticleType::EMPTY) continue;

            SDL_SetRenderDrawColor(_renderer,
                _particle.color.r, _particle.color.g, _particle.color.b, _particle.color.a);
            SDL_RenderDrawPoint(_renderer, _x, _y);
        }
    }
}

void ParticleManager::AddParticle(int _x, int _y, ParticleType _type)
{
    if (!IsValidPosition(_x, _y)) return;

    Particle _particle;
    _particle.type = _type;
    _particle.updatedInThisFrame = false;

    //����������ɫ
    switch (_type)
    {
    case ParticleType::SAND: _particle.color = { 194, 178, 128, 255 }; break;
    case ParticleType::WATER: _particle.color = { 64, 164, 223, 200 }; break;
    case ParticleType::FIRE: _particle.color = { 255, 69, 0, 255 }; break;
    case ParticleType::SMOKE: _particle.color = { 100, 100, 100, 180 }; break;
    case ParticleType::STONE: _particle.color = { 120, 120, 120, 255 }; break;
    case ParticleType::WOOD: _particle.color = { 150, 111, 51, 255 }; break;
    case ParticleType::LAVA: _particle.color = { 207, 16, 32, 255 }; break;
    case ParticleType::ACID: _particle.color = { 50, 255, 50, 200 }; break;
    default: _particle.color = { 255, 255, 255, 255 }; break;
    }

    frontBuffer[_y * windowRect.w + _x] = _particle;
}

void ParticleManager::RemoveParticle(int _x, int _y)
{
    //����������Ϊ��
    if (IsValidPosition(_x, _y))
        frontBuffer[_y * windowRect.w + _x] = Particle{};
}

void ParticleManager::ClearParticles()
{
    std::fill_n(frontBuffer, windowRect.w * windowRect.h, Particle{});
    std::fill_n(backBuffer, windowRect.w * windowRect.h, Particle{});
}

void ParticleManager::SwapBuffers()
{
    std::swap(frontBuffer, backBuffer);
}

Particle ParticleManager::GetParticle(int _x, int _y) const
{
    if (IsValidPosition(_x, _y))
        return frontBuffer[_y * windowRect.w + _x];
    return Particle{};
}

bool ParticleManager::IsValidPosition(int _x, int _y) const
{
    return _x >= 0 && _x < windowRect.w && _y >= 0 && _y < windowRect.h;
}

#pragma region UpdateSpecificParticleType
void ParticleManager::UpdateEmpty(int _x, int _y)
{
}

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
    Particle& p = frontBuffer[_y * windowRect.w + _x];

    //���������ƶ�
    if (IsValidPosition(_x, _y + 1))
    {
        Particle& below = backBuffer[(_y + 1) * windowRect.w + _x];
        if (below.type == ParticleType::EMPTY)
        {
            backBuffer[(_y + 1) * windowRect.w + _x] = p;
            return;
        }
    }

    //���ѡ������������
    int dir = dist(rng) ? 1 : -1;

    //��������/�����ƶ�
    if (IsValidPosition(_x + dir, _y + 1))
    {
        Particle& diag = backBuffer[(_y + 1) * windowRect.w + _x + dir];
        if (diag.type == ParticleType::EMPTY)
        {
            backBuffer[(_y + 1) * windowRect.w + _x + dir] = p;
            return;
        }
    }

    //������һ���Խ���
    if (IsValidPosition(_x - dir, _y + 1))
    {
        Particle& diag = backBuffer[(_y + 1) * windowRect.w + _x - dir];
        if (diag.type == ParticleType::EMPTY)
        {
            backBuffer[(_y + 1) * windowRect.w + _x - dir] = p;
            return;
        }
    }

    //�޷��ƶ�������ԭλ
    backBuffer[_y * windowRect.w + _x] = p;
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