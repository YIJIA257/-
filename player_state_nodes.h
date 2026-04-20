#ifndef _PLAYER_STATE_NODES_H_
#define _PLAYER_STATE_NODES_H_

#include "timer.h"
#include "state_node.h"

//攻击状态的类
class PlayerAttackState : public StateNode
{
public:
	PlayerAttackState();
	~PlayerAttackState() = default;

	//进入攻击状态执行的操作
	void on_enter() override;

	//更新状态
	void on_update(float delta) override;

	//退出一个状态的伴随操作
	void on_exit() override;

private:

	//设置定时器，用于判断状态的进度
	Timer timer;

private:

	//更新攻击碰撞箱的位置
	void update_hit_box_position();

};

//死亡状态，显然不可退出
class PlayerDeadState : public StateNode
{
public:
	PlayerDeadState();
	~PlayerDeadState() = default;

	//进入的死亡状态的操作
	void on_enter() override;

	//状态进度的更新
	void on_update(float delta) override;

private:

	//定时器用于更新状态的进度
	Timer timer;

};

class PlayerFallState : public StateNode//掉落状态
{
public:
	PlayerFallState() = default;
	~PlayerFallState() = default;

	//进入掉落状态的操作
	void on_enter() override;

	//状态进度的更新
	void on_update(float delta) override;

};

class PlayerIdleState : public StateNode
{
public:
	PlayerIdleState() = default;
	~PlayerIdleState() = default;

	//进入闲置状态的操作
	void on_enter() override;

	//状态的更新
	void on_update(float delta) override;

};

class PlayerJumpState : public StateNode
{
public:
	PlayerJumpState() = default;
	~PlayerJumpState() = default;

	//进入跳跃状态的操作
	void on_enter() override;

	//更新状态
	void on_update(float delta) override;

};

class PlayerRollState : public StateNode
{
public:
	PlayerRollState();
	~PlayerRollState() = default;

	//进入翻滚状态的操作
	void on_enter() override;

	//状态的更新
	void on_update(float delta) override;

	//退出翻滚状态执行的操作
	void on_exit() override;

private:

	//计时器记录CD等
	Timer timer;

};

class PlayerRunState : public StateNode
{
public:
	PlayerRunState() = default;
	~PlayerRunState() = default;

	//进入跑动状态的操作
	void on_enter() override;

	//跑步状态的更新
	void on_update(float delta) override;

	//退出跑步状态执行的操作
	void on_exit() override;

};

#endif 
// !_PLAYER_STATE_NODES_H_
