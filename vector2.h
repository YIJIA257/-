#ifndef _VECTOR2_H_
#define _VECTOR2_H_
//二维向量类重写了运算符
//并提供获取长度和标准化的方法
//用来处理角色冲刺运动或子弹的飞行时十分有用


#include <cmath>
//定义二维坐标类
class Vector2
{
public:
	float x = 0;
	float y = 0;

public:
	Vector2() = default;
	~Vector2() = default;

	Vector2(float x, float y)
		: x(x), y(y) { }
	//设置坐标

	Vector2 operator+(const Vector2& vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}
	//定义加号重载符号，进行位置变换

	void operator+=(const Vector2& vec)
	{
		x += vec.x, y += vec.y;
	}

	void operator-=(const Vector2& vec)
	{
		x -= vec.x, y -= vec.y;
	}
	//定义减号重载符号，进行位置变换

	Vector2 operator-(const Vector2& vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	float operator*(const Vector2& vec) const
	{
		return x * vec.x + y * vec.y;
	}//定义乘号重载符

	Vector2 operator*(float val) const
	{
		return Vector2(x * val, y * val);
	}

	void operator*=(float val)
	{
		x *= val, y *= val;
	}

	float length()
	{
		return sqrt(x * x + y * y);
	}
	//定义两点间的距离

	Vector2 normalize()
	{
		float len = length();

		//进行初始化
		if (len == 0)
		{
			return Vector2(0, 0);
		}
		//如果长度为0，返回初始化

		return Vector2(x / len, y / len);
	}
};


#endif 
// !_VECTOR2_H_
//通过二维向量类来获取角色的位置
//并获取下一步的状态
