#ifndef _VECTOR_2_F_H_
#define _VECTOR_2_F_H_

#include <iostream>

class Vector2f
{
public:
	float x = 0;
	float y = 0;

public:
	Vector2f(float, float);
	Vector2f() = default;
	~Vector2f() = default;

	float Length() const;                      //获取向量模长
	Vector2f Normalized() const;                //返回标准化的单位向量
	bool ApproxZero() const;                   //向量接近为零的判断

	bool operator==(const Vector2f&) const;     //向量的判等
	bool operator!=(const Vector2f&) const;     //向量的判不等
	bool operator>(const Vector2f&) const;      //左侧向量模长大于右侧
	bool operator>=(const Vector2f&) const;     //左侧向量模长大于等于右侧
	bool operator<(const Vector2f&) const;      //左侧向量模长小于右侧
	bool operator<=(const Vector2f&) const;     //左侧向量模长小于等于右侧

	Vector2f operator+(const Vector2f&) const;   //加法
	Vector2f operator-(const Vector2f&) const;   //减法
	Vector2f operator*(const float&) const;     //常数乘法
	float operator*(const Vector2f&) const;     //向量乘法

	void operator+=(const Vector2f&);           //加等于
	void operator-=(const Vector2f&);           //减等于
	void operator*=(const float&);             //乘等于
};

//声明运算符重载
std::ostream& operator<<(std::ostream& _cout, const Vector2f& _obj);

#endif
