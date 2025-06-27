#include "../../../Header/Manager/Concrete/ParticleManager.h"

#include <iostream>
#include <cmath>

#include "../../../Header/Manager/Concrete/GameManager.h"

ParticleManager::ParticleManager()
{
    #pragma region RandomEngine
    //初始化随机数生成器
    std::random_device _rd;
    rng = std::mt19937(_rd());
    #pragma endregion

	//获取游戏窗口矩形区域
    windowRect = GameManager::Instance().windowRect;
    
    #pragma region DoubleBuffer
    //分配双缓冲内存，堆区线性数组
    frontBuffer = new Particle[windowRect.w * windowRect.h];
    backBuffer = new Particle[windowRect.w * windowRect.h];
	//以EMPTY粒子填充整个前缓冲和后缓冲
    ClearAllParticles();
    #pragma endregion
}

ParticleManager::~ParticleManager()
{
	//释放双缓冲内存
    delete[] frontBuffer;
    delete[] backBuffer;
}

void ParticleManager::OnUpdate(double _delta)
{   
    //重置后缓冲，等待写入更新结果
    std::fill_n(backBuffer, windowRect.w * windowRect.h, Particle{});

    //每个像素点代表一个粒子，遍历屏幕像素点更新粒子状态，从底部向上更新避免更新顺序影响物理效果
    for (int _y = windowRect.h - 1; _y >= 0; _y--)
    {
        for (int _x = 0; _x < windowRect.w; _x++)
        {
			//从前缓冲区获取粒子，将更新结果写入后缓冲区
            Particle& _particle = frontBuffer[_y * windowRect.w + _x];

            //根据粒子类型调用更新函数
            switch (_particle.type)
            {
            //遇到空类型则直接跳过
			case ParticleType::EMPTY: continue;
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
	//交换缓冲区，将后缓冲区的更新结果作为前缓冲区的状态
    std::swap(frontBuffer, backBuffer);
}

void ParticleManager::OnRender(SDL_Renderer* _renderer)
{
	//渲染每个像素点对应的粒子为一个特定颜色，并调整Gamma值模拟光影效果等
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

    //设置粒子颜色
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
    //将粒子设置为空
    if (IsValidPosition(_x, _y))
        frontBuffer[_y * windowRect.w + _x] = Particle{};
}

void ParticleManager::ClearAllParticles()
{
    std::fill_n(frontBuffer, windowRect.w * windowRect.h, Particle{});
    std::fill_n(backBuffer, windowRect.w * windowRect.h, Particle{});
}

Particle ParticleManager::GetParticle(int _x, int _y) const
{
	//获取指定位置的粒子对象，如果位置无效则返回空粒子
    if (IsValidPosition(_x, _y))
        return frontBuffer[_y * windowRect.w + _x];
    return Particle{};
}

bool ParticleManager::IsValidPosition(int _x, int _y) const
{
	//检查坐标是否在窗口范围内
    return (_x >= windowRect.x && _x < windowRect.x + windowRect.w)
        && (_y >= windowRect.y && _y < windowRect.y + windowRect.h);
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
    Particle& p = frontBuffer[_y * windowRect.w + _x];

    //尝试向下移动
    if (IsValidPosition(_x, _y + 1))
    {
        Particle& below = backBuffer[(_y + 1) * windowRect.w + _x];
        if (below.type == ParticleType::EMPTY)
        {
            backBuffer[(_y + 1) * windowRect.w + _x] = p;
            return;
        }
    }

    //随机选择先左下方还是先右下方
    int dir = dist(rng) ? 1 : -1;
    //尝试朝斜下方移动
    if (IsValidPosition(_x + dir, _y + 1))
    {
        Particle& diag = backBuffer[(_y + 1) * windowRect.w + _x + dir];
        if (diag.type == ParticleType::EMPTY)
        {
            backBuffer[(_y + 1) * windowRect.w + _x + dir] = p;
            return;
        }
    }
    //尝试另一个对角线
    if (IsValidPosition(_x - dir, _y + 1))
    {
        Particle& diag = backBuffer[(_y + 1) * windowRect.w + _x - dir];
        if (diag.type == ParticleType::EMPTY)
        {
            backBuffer[(_y + 1) * windowRect.w + _x - dir] = p;
            return;
        }
    }

    //无法移动，保持原位
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