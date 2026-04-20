#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "barb.h"
#include "sword.h"
#include "character.h"

class Enemy : public Character
{
public:
	//继承角色的基类
	Enemy();
	~Enemy();

	void on_update(float delta) override;
	//随时更新和渲染
	void on_render() override;
	//随机的攻击方式

	void on_hurt() override;

	//受伤后的无敌帧
	void set_facing_left(bool flag)
	{
		is_facing_left = flag;
	}

	bool get_facing_left() const
	{
		return is_facing_left;
	}
	//盘面段敌人的朝向并掉头

	void set_dashing_in_air(bool flag)
	{
		is_dashing_in_air = flag;
	}

	bool get_dashing_in_air() const
	{
		return is_dashing_in_air;
	}
	//判断是否在天上冲刺

	void set_dashing_on_floor(bool flag)
	{
		is_dashing_on_floor = flag;
	}

	bool get_dashing_on_floor() const
	{
		return is_dashing_on_floor;
	}
	//判断是否在地面天上冲刺

	void set_throwing_silk(bool flag)
	{
		is_throwing_silk = flag;
		collision_box_silk->set_enabled(flag);
	}

	bool get_throwing_silk() const
	{
		return is_throwing_silk;
	}
	//判断是否在丢绢
	void throw_barbs();
	//判断是否在丢石头
	void throw_sword();
	//判断是否在丢武器

	void on_dash();
	//判断是否在冲刺
	void on_throw_silk();
	//判断是否在丢绢

private:
	bool is_throwing_silk = false;
	bool is_dashing_in_air = false;
	bool is_dashing_on_floor = false;
	
	Animation animation_silk;
	AnimationGroup animation_dash_in_air_vfx;
	AnimationGroup animation_dash_on_floor_vfx;
	Animation* current_dash_animation = nullptr;
	//导入各个攻击动作的图库
	
	std::vector<Barb*> barb_list;
	std::vector<Sword*> sword_list;
	CollisionBox* collision_box_silk = nullptr;

};

#endif 
// !_ENEMY_H_
