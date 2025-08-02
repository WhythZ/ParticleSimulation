#include "../../../Header/Manager/Concrete/ParticleManager.h"

#include <iostream>
#include <cmath>

#include "../../../Header/Manager/Concrete/GameManager.h"

const std::vector<SDL_Color> PARTICLE_COLORS =
{
    //{ 0, 0, 0, 0 },           //无颜色（透明）
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
    //初始化前后缓冲
    frontBuffer.resize(windowRect.h * windowRect.w, Particle{ ParticleType::EMPTY });
    backBuffer.resize(windowRect.h * windowRect.w, Particle{ ParticleType::EMPTY });
    #pragma endregion
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::OnUpdate(double _delta)
{
    //重置后缓冲区，修改类型为EMPTY，重置更新状态
    for (Particle& _p : backBuffer)
    {
        _p.type = ParticleType::EMPTY;
		_p.isUpdatedThisFrame = false;
    }
    //使用resize会重新分配内存导致效率低下，也不要创建新对象导致额外开销
    //backBuffer.resize(windowRect.h * windowRect.w, ParticleType::EMPTY);
    //std::fill(backBuffer.begin(), backBuffer.end(), Particle{ ParticleType::EMPTY });

    //每个像素点代表一个粒子，从下向上遍历保证物理正确
	//奇偶行遍历方向不同，防止粒子更新始终偏向于某一方
    for (int _y = windowRect.h - 1; _y >= 0; _y--)
    {
        //使用位运算判断奇偶性比取模运算更快
        const bool _isSingularRow = _y & 1;
        
        //奇数行从左向右遍历，偶数行从右向左遍历
        if (_isSingularRow)
        {
            for (int _x = 0; _x < windowRect.w; _x++)
            {
				if (!frontBuffer[_y * windowRect.w + _x].isUpdatedThisFrame)
                    UpdateParticleAt(_x, _y);
            }
        }
        else
        {
            for (int _x = windowRect.w - 1; _x >= 0; _x--)
            {
                if (!frontBuffer[_y * windowRect.w + _x].isUpdatedThisFrame)
                    UpdateParticleAt(_x, _y);
            }
        }
    }
	//交换缓冲区，将后缓冲区的更新结果作为前缓冲区的状态
    std::swap(frontBuffer, backBuffer);
}

void ParticleManager::OnRender(SDL_Renderer* _renderer)
{
	//渲染每个像素点的粒子，根据类型渲染颜色
    for (int _y = 0; _y < windowRect.h; _y++)
    {
        for (int _x = 0; _x < windowRect.w; _x++)
        {
            //获取粒子类型
            ParticleType _type = frontBuffer[_y * windowRect.w + _x].type;
            //跳过空粒子渲染（关键优化！！不跳过会导致巨卡无比！！）
			if (_type == ParticleType::EMPTY) continue;
			
            //获取渲染颜色，注意+1是因为颜色数组中没有EMPTY的颜色
            SDL_Color _color = PARTICLE_COLORS[static_cast<uint8_t>(_type) - 1];
            SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, _color.a);
            SDL_RenderDrawPoint(_renderer, _x, _y);
        }
    }
}

void ParticleManager::BrushParticleAt(int _x, int _y, ParticleType _type)
{
    if (!IsValidPosition(_x, _y)) return;

    frontBuffer[_y * windowRect.w + _x].type = _type;
}

void ParticleManager::EmptizeParticleAt(int _x, int _y)
{
    if (!IsValidPosition(_x, _y)) return;

    //将粒子类型置空
    frontBuffer[_y * windowRect.w + _x].type = ParticleType::EMPTY;
}

void ParticleManager::UpdateParticleAt(int _x, int _y)
{
    Particle& _particle = frontBuffer[_y * windowRect.w + _x];

	//标记粒子在本帧已被更新，避免重复更新同一粒子
    _particle.isUpdatedThisFrame = true;

    //根据前缓冲区粒子类型调用对应更新函数，更新结果均写入后缓冲区
    switch (_particle.type)
    {
    case ParticleType::EMPTY: break; //空粒子直接跳过，防止额外开销
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

void ParticleManager::WriteParticleAt(int _x, int _y, ParticleType _type)
{
    backBuffer[_y * windowRect.w + _x].type = _type;
}

bool ParticleManager::IsValidPosition(int _x, int _y) const
{
    //检查坐标是否在窗口范围内
    return (_x >= windowRect.x && _x < windowRect.x + windowRect.w)
        && (_y >= windowRect.y && _y < windowRect.y + windowRect.h);

    //需要注意的是，目前实现的版本中每个像素点都是一个粒子瓦片，所以世界坐标和瓦片坐标一致
	//若后续需实现更复杂的瓦片（如n*n个像素点代表一个粒子瓦片），则需注意进行坐标的转换
}

bool ParticleManager::IsEmptyPType(int _x, int _y) const
{
    if (!IsValidPosition(_x, _y)) return false;

    int _idx = _y * windowRect.w + _x;
    return backBuffer[_idx].type == ParticleType::EMPTY;
}

bool ParticleManager::IsSolidPType(int _x, int _y) const
{
    if (!IsValidPosition(_x, _y)) return false;

    int _idx = _y * windowRect.w + _x;
    return backBuffer[_idx].type == ParticleType::DIRT
        || backBuffer[_idx].type == ParticleType::STONE
        || backBuffer[_idx].type == ParticleType::WOOD
        || backBuffer[_idx].type == ParticleType::ICE;
}

bool ParticleManager::IsPowderPType(int _x, int _y) const
{
    if (!IsValidPosition(_x, _y)) return false;

    int _idx = _y * windowRect.w + _x;
    return backBuffer[_idx].type == ParticleType::SAND
        || backBuffer[_idx].type == ParticleType::SNOW
        || backBuffer[_idx].type == ParticleType::GUNPOWDER;
}

bool ParticleManager::IsLiquidPType(int _x, int _y) const
{
    if (!IsValidPosition(_x, _y)) return false;

    int _idx = _y * windowRect.w + _x;
    return backBuffer[_idx].type == ParticleType::WATER
        || backBuffer[_idx].type == ParticleType::OIL
        || backBuffer[_idx].type == ParticleType::ACID
        || backBuffer[_idx].type == ParticleType::LAVA;
}

bool ParticleManager::IsSpreadPType(int _x, int _y) const
{
    if (!IsValidPosition(_x, _y)) return false;

    int _idx = _y * windowRect.w + _x;
    return backBuffer[_idx].type == ParticleType::FIRE;
}

bool ParticleManager::IsGasPType(int _x, int _y) const
{
    if (!IsValidPosition(_x, _y)) return false;

    int _idx = _y * windowRect.w + _x;
    return backBuffer[_idx].type == ParticleType::SMOKE
        || backBuffer[_idx].type == ParticleType::STEAM;
}

#pragma region UpdateSolid
void ParticleManager::UpdateDirt(int _x, int _y)
{
    //位置固定不动
    WriteParticleAt(_x, _y, ParticleType::DIRT);
}

void ParticleManager::UpdateStone(int _x, int _y)
{
    //位置固定不动
    WriteParticleAt(_x, _y, ParticleType::STONE);
}

void ParticleManager::UpdateWood(int _x, int _y)
{
    //位置固定不动
    WriteParticleAt(_x, _y, ParticleType::WOOD);
}

void ParticleManager::UpdateIce(int _x, int _y)
{
    //位置固定不动
    WriteParticleAt(_x, _y, ParticleType::ICE);
}
#pragma endregion

#pragma region UpdatePowder
void ParticleManager::UpdateSand(int _x, int _y)
{
    //缓存常用值
    ParticleType _currentType = ParticleType::SAND;
    
    #pragma region TryMove
    //随机选择先左还是先右
    int _dir = dist(rng) ? 1 : -1;
    //尝试向下移动
    if (IsEmptyPType(_x, _y + 1))
    {
        //先清空当前位置
        WriteParticleAt(_x, _y, ParticleType::EMPTY);
        //向下方下落，将其粒子类型替换
        WriteParticleAt(_x, _y + 1, _currentType);
    }
    //尝试朝斜下方移动
    else if (IsEmptyPType(_x + _dir, _y + 1))
    {
        //先清空当前位置
        WriteParticleAt(_x, _y, ParticleType::EMPTY);
        //向斜下方下落，将其粒子类型替换
        WriteParticleAt(_x + _dir, _y + 1, _currentType);
    }
    //尝试另一个对角线
    else if (IsEmptyPType(_x - _dir, _y + 1))
    {
        //先清空当前位置
        WriteParticleAt(_x, _y, ParticleType::EMPTY);
        //向斜下方下落，将其粒子类型替换
        WriteParticleAt(_x - _dir, _y + 1, _currentType);
    }
    //无法移动，保持原位
    else
        WriteParticleAt(_x, _y, _currentType);
    #pragma endregion
}

void ParticleManager::UpdateSnow(int _x, int _y)
{
}

void ParticleManager::UpdateGunPowder(int _x, int _y)
{
}
#pragma endregion

#pragma region UpdateLiquid
void ParticleManager::UpdateWater(int _x, int _y)
{
    //缓存常用值
    int _currentIdx = _y * windowRect.w + _x;
    ParticleType _currentType = ParticleType::WATER;

    #pragma region TryMove
    //随机选择先左还是先右
    int _dir = dist(rng) ? 1 : -1;
    //尝试向下移动
    if (IsEmptyPType(_x, _y + 1))
    {
        //先清空当前位置
        WriteParticleAt(_x, _y, ParticleType::EMPTY);
        //向下方下落，将其粒子类型替换
        WriteParticleAt(_x, _y + 1, _currentType);
    }
    //尝试朝斜下方移动
    else if (IsEmptyPType(_x + _dir, _y + 1))
    {
        //先清空当前位置
        WriteParticleAt(_x, _y, ParticleType::EMPTY);
        //向斜下方下落，将其粒子类型替换
        WriteParticleAt(_x + _dir, _y + 1, _currentType);
    }
    //尝试另一个对角线
    else if (IsEmptyPType(_x - _dir, _y + 1))
    {
        //先清空当前位置
        WriteParticleAt(_x, _y, ParticleType::EMPTY);
        //向斜下方下落，将其粒子类型替换
        WriteParticleAt(_x - _dir, _y + 1, _currentType);
    }
    //液体还可以向左右移动，但只能当其下方存在阻挡时才会尝试
    else if (IsSolidPType(_x, _y + 1) || IsPowderPType(_x, _y + 1) || IsLiquidPType(_x, _y + 1))
    {
        if (IsEmptyPType(_x + _dir, _y))
        {
            //先清空当前位置
            //WriteParticleAt(_x, _y, ParticleType::EMPTY);
            //向水平方向移动
            WriteParticleAt(_x + _dir, _y, _currentType);
        }
        else if (IsEmptyPType(_x - _dir, _y))
        {
            //先清空当前位置
            //WriteParticleAt(_x, _y, ParticleType::EMPTY);
            //向水平方向移动
            WriteParticleAt(_x - _dir, _y, _currentType);
        }
    }
    //无法移动，保持原位
    else
        WriteParticleAt(_x, _y, _currentType);
    #pragma endregion
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
#pragma endregion

#pragma region UpdateSpread
void ParticleManager::UpdateFire(int _x, int _y)
{
}
#pragma endregion

#pragma region UpdateGas
void ParticleManager::UpdateSmoke(int _x, int _y)
{
}

void ParticleManager::UpdateSteam(int _x, int _y)
{
}
#pragma endregion