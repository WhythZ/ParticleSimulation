#include "../../Header/Infrastructure/Vector2f.h"
#include <cmath>

Vector2f::Vector2f(float _x, float _y) :x(_x), y(_y) {}

float Vector2f::Length() const
{
	return sqrt(x * x + y * y);
}

Vector2f Vector2f::Normalized() const
{
	//若向量为零向量，则返回零向量即可
	if (Length() == 0)
		return Vector2f(0, 0);
	//反之则返回该向量方向上的单位向量（模长为1的向量）
	return Vector2f(x / Length(), y / Length());
}

bool Vector2f::ApproxZero() const
{
	//判断两个物体之间是否重合时（比如某怪物是否到达目标地点），直接将向量的浮点数元素x、y和0作比较是不精确的，会出现二者永远无法被判定为重合的情况
	return Length() < 0.001;
}

bool Vector2f::operator==(const Vector2f& _compare) const
{
	return (x == _compare.x) && (y == _compare.y);
}

bool Vector2f::operator!=(const Vector2f& _compare) const
{
	return !(*this == _compare);
}

bool Vector2f::operator>(const Vector2f& _compare) const
{
	return Length() > _compare.Length();
}

bool Vector2f::operator>=(const Vector2f& _compare) const
{
	return Length() >= _compare.Length();
}

bool Vector2f::operator<(const Vector2f& _compare) const
{
	return Length() < _compare.Length();
}

bool Vector2f::operator<=(const Vector2f& _compare) const
{
	return Length() <= _compare.Length();
}

Vector2f Vector2f::operator+(const Vector2f& _plus) const
{
	return Vector2f(x + _plus.x, y + _plus.y);
}

void Vector2f::operator+=(const Vector2f& _plus)
{
	x += _plus.x;
	y += _plus.y;
}

Vector2f Vector2f::operator-(const Vector2f& _minus) const
{
	return Vector2f(x - _minus.x, y - _minus.y);
}

void Vector2f::operator-=(const Vector2f& _minus)
{
	x -= _minus.x;
	y -= _minus.y;
}

Vector2f Vector2f::operator*(const float& _mtp) const
{
	return Vector2f(x * _mtp, y * _mtp);
}

void Vector2f::operator*=(const float& _mtp)
{
	x *= _mtp;
	y *= _mtp;
}

float Vector2f::operator*(const Vector2f& _mtp) const
{
	return (x * _mtp.x) + (y * _mtp.y);
}

//左移运算符重载用于输出
std::ostream& operator<<(std::ostream& _cout, const Vector2f& _obj)
{
	_cout << "(" << _obj.x << "," << _obj.y << ")";
	return _cout;
}