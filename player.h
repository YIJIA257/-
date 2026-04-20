#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "character.h"

class Player : public Character
{
public:
	enum class AttackDir
	{
		//攻击方向的枚举，决定攻击动画的绘制位置
		Up, Down, Left, Right
	};

public:
	Player();
	~Player();

	//虚函数的覆盖

	//收集输入的操作信息，并实现相关操作
	void on_input(const ExMessage& msg) override;

	//实现角色全方位的更新（CD，碰撞箱位置与人物保持一致等等）
	void on_update(float delta) override;

	//渲染相关的动画
	void on_render() override;

	//实现受伤的外部细节（受伤音效）
	void on_hurt() override;

	//翻滚操作
	void set_rolling(bool flag)
	{
		is_rolling = flag;
	}

	//检测角色是否处于翻滚状态
	bool get_rolling() const
	{
		return is_rolling;
	}

	//检测玩家是否可以翻滚（CD与死亡状态的检查）
	bool can_roll() const
	{
		return is_roll_cd_comp && !is_rolling && is_roll_key_down;
	}

	//设置是否可以攻击
	void set_attacking(bool flag)
	{
		//攻击
		is_attacking = flag;
	}

	//检测是否处于攻击状态
	bool get_attacking() const
	{
		return is_attacking;
	}

	//检测是否可以攻击
	bool can_attack() const
	{
		return is_attack_cd_comp && !is_attacking && is_attack_key_down;
	}

	//检测是否可以跳跃
	bool can_jump() const
	{
		//跳跃
		return is_on_floor() && is_jump_key_down;
	}

	int get_move_axis() const
	{
		//获取移动方向
		return is_right_key_down - is_left_key_down;
	}

	AttackDir get_attack_dir() const
	{
		//获取攻击方向
		return attack_dir;
	}

	//实现跳跃的操作
	void on_jump();

	//实现落地的操作
	void on_land();

	//实现翻滚操作
	void on_roll();

	//实现攻击操作
	void on_attack();

private:
	//CD与速度的常量
	const float CD_ROLL = 0.75f;
	const float CD_ATTACK = 0.5f;
	const float SPEED_RUN = 300.0f;
	const float SPEED_JUMP = 780.0f;
	const float SPEED_ROLL = 800.0f;

private:
	//翻滚与翻滚CD的状态
	Timer timer_roll_cd;
	bool is_rolling = false;
	bool is_roll_cd_comp = true;

	//攻击与攻击CD的状态
	Timer timer_attack_cd;
	bool is_attacking = false;
	bool is_attack_cd_comp = true;

	//玩家对角色的操纵的相关按钮的开关
	bool is_left_key_down = false;
	bool is_right_key_down = false;
	bool is_jump_key_down = false;
	bool is_roll_key_down = false;
	bool is_attack_key_down = false;

	//不同方向的4个斩击特效
	Animation animation_slash_up;
	Animation animation_slash_down;
	Animation animation_slash_left;
	Animation animation_slash_right;

	//角色的攻击方向
	AttackDir attack_dir = AttackDir::Right;

	//存储每次的攻击特效
	Animation* current_slash_animation = nullptr;

	//起跳和落地的烟
	bool is_jump_vfx_visible = false;
	Animation animation_jump_vfx;

	bool is_land_vfx_visible = false;
	Animation animation_land_vfx;

private:
	//鼠标获取攻击方向
	void update_attack_dir(int x, int y);

};

#endif 
// !_PLAYER_H_
