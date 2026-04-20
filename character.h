#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "vector2.h"
#include "animation.h"
#include "collision_box.h"
#include "state_machine.h"

#include <string>
#include <graphics.h>
#include <unordered_map>

class Character
{
public:
	Character();
	~Character();

	//扣血
	void decrease_hp();

	int get_hp() const
	{
		//加血
		return hp;
	}

	//设置位置
	void set_position(const Vector2& position)
	{
		this->position = position;
	}

	//得到位置
	const Vector2& get_position() const
	{
		return position;
	}

	//设置速度
	void set_velocity(const Vector2& velocity)
	{
		this->velocity = velocity;
	}

	//得到速度
	const Vector2& get_velocity() const
	{
		return velocity;
	}

	//得到碰撞箱中心位置
	Vector2 get_logic_center() const
	{
		return Vector2(position.x, position.y - logic_height / 2);
	}

	//设置重力的影响
	void set_gravity_enabled(bool flag)
	{
		enable_gravity = flag;
	}

	//得到碰撞箱
	CollisionBox* get_hit_box()
	{
		return hit_box;
	}

	//得到受击碰撞箱
	CollisionBox* get_hurt_box()
	{
		return hurt_box;
	}

	//判断角色是否位于地面上
	bool is_on_floor() const
	{
		return position.y >= FLOOR_Y;
	}

	//返回地面的y坐标
	float get_floor_y() const
	{
		return FLOOR_Y;
	}

	//无敌时间的计时器
	void make_invulnerable()
	{
		is_invulnerable = true;
		timer_invulnerable_status.restart();
	}

	//处理玩家操纵的信息
	virtual void on_input(const ExMessage& msg);

	//状态的更新
	virtual void on_update(float delta);

	//渲染角色
	virtual void on_render();

	//角色受伤的逻辑
	virtual void on_hurt();

	//切换状态
	void switch_state(const std::string& id);

	//设置角色动画
	void set_animation(const std::string& id);

protected:
	struct AnimationGroup
	{
		//角色朝向的动画
		Animation left;
		Animation right;
	};

protected:
	const float FLOOR_Y = 620;										// 地板的竖直方向坐标
	const float GRAVITY = 980 * 2;									// 重力大小

protected:
	int hp = 10;													// 角色生命值
	Vector2 position;												// 角色脚底位置
	Vector2 velocity;												// 角色速度
	float logic_height = 0;											// 角色的逻辑高度
	bool is_facing_left = true;										// 当前角色是否朝向左			
	StateMachine state_machine;										// 角色逻辑状态机
	bool enable_gravity = true;										// 启用重力模拟
	bool is_invulnerable = false;									// 当前是否无敌
	Timer timer_invulnerable_blink;									// 无敌闪烁状态定时器
	Timer timer_invulnerable_status;								// 无敌状态定时器
	bool is_blink_invisible = false;								// 当前是否处于闪烁的不可见帧
	CollisionBox* hit_box = nullptr;								// 攻击碰撞箱
	CollisionBox* hurt_box = nullptr;								// 受击碰撞箱
	AnimationGroup* current_animation = nullptr;					// 当前角色动画
	std::unordered_map<std::string, AnimationGroup> animation_pool;	// 角色动画池

};

#endif
// !_CHARACTER_H_
