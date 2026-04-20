#ifndef _BARB_H_
#define _BARB_H_

#include "animation.h"
#include "collision_box.h"

class Barb
{
public:
	Barb();
	~Barb();

	void on_update(float delta);
	void on_render();

	void set_position(const Vector2& position)
	{
		//更新刺球的位置并判断是否碰撞
		this->base_position = position;
		this->current_position = position;
	}

	bool check_valid() const
	{
		return is_valid;
		//判断刺球是否有效
	}

private:
	enum class Stage
	{
		//待机
		Idle,
		//瞄准
		Aim,
		//冲刺
		Dash,
		//硬直
		Break
	};

private:
	const float SPEED_DASH = 1500.0f;

private:
	Timer timer_idle;
	//控制闲置状态的持续时间

	Timer timer_aim;
	//控制瞄准状态的持续时间

	int diff_period = 0;
	//随机值，控制浮动的运动周期偏移

	bool is_valid = true;
	float total_delta_time = 0;

	Vector2 velocity;
	Vector2 base_position;
	Vector2 current_position;
	//设置速度位置
	
	Animation animation_loose;
	Animation animation_break;
	Animation* current_animation = nullptr;

	Stage stage = Stage::Idle;
	CollisionBox* collision_box = nullptr;

private:
	void on_break();
	//封装刺球破碎时的处理

};

#endif 
// !_BARB_H_
