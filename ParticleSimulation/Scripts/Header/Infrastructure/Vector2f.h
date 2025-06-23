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

	float Length() const;                      //��ȡ����ģ��
	Vector2f Normalized() const;                //���ر�׼���ĵ�λ����
	bool ApproxZero() const;                   //�����ӽ�Ϊ����ж�

	bool operator==(const Vector2f&) const;     //�������е�
	bool operator!=(const Vector2f&) const;     //�������в���
	bool operator>(const Vector2f&) const;      //�������ģ�������Ҳ�
	bool operator>=(const Vector2f&) const;     //�������ģ�����ڵ����Ҳ�
	bool operator<(const Vector2f&) const;      //�������ģ��С���Ҳ�
	bool operator<=(const Vector2f&) const;     //�������ģ��С�ڵ����Ҳ�

	Vector2f operator+(const Vector2f&) const;   //�ӷ�
	Vector2f operator-(const Vector2f&) const;   //����
	Vector2f operator*(const float&) const;     //�����˷�
	float operator*(const Vector2f&) const;     //�����˷�

	void operator+=(const Vector2f&);           //�ӵ���
	void operator-=(const Vector2f&);           //������
	void operator*=(const float&);             //�˵���
};

//�������������
std::ostream& operator<<(std::ostream& _cout, const Vector2f& _obj);

#endif
