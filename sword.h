#ifndef _SWORD_H_
#define _SWORD_H_

#include "animation.h"
#include "collision_box.h"

//包含头文件，定义道具类
class Sword
{
public:
	Sword(const Vector2& position, bool move_left);
	~Sword();

	//更新剑的状态
	void on_update(float delta);

	//渲染剑的动画
	void on_render();

	//检测剑对象是否有效
	bool check_valid() const
	{
		return is_valid;
	}

//在外部检查对象是否可以移除
private:
	const float SPEED_MOVE = 1250.0f;

private:

	//位置，速度，图画，是否有效的开关，碰撞箱
	Vector2 position;
	Vector2 velocity;
	Animation animation;
	bool is_valid = true;
	CollisionBox* collision_box = nullptr;

};

#endif 
// !_SWORD_H_
