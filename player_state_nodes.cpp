#include "player.h"
#include "character_manager.h"
#include "player_state_nodes.h"

PlayerAttackState::PlayerAttackState()
{
	timer.set_wait_time(0.3f);
	timer.set_one_shot(true);

	timer.set_on_timeout([&]()
		{
			Player* player = (Player*)CharacterManager::instance()->get_player();
			player->set_attacking(false);
		});
}

//进入状态的初始化操作
void PlayerAttackState::on_enter()
{
	//在管理器中设置对应的状态
	CharacterManager::instance()->get_player()->set_animation("attack");

	//初始化攻击碰撞箱与角色的状态
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->get_hit_box()->set_enabled(true);
	player->set_attacking(true);
	update_hit_box_position();
	player->on_attack();

	timer.restart();

	switch (range_random(1, 3))
	{
	case 1:
		play_audio(_T("player_attack_1"), false);
		break;
	case 2:
		play_audio(_T("player_attack_2"), false);
		break;
	case 3:
		play_audio(_T("player_attack_3"), false);
		break;
	}
}

//状态内部一切的更新都封装在此
void PlayerAttackState::on_update(float delta)
{
	timer.on_update(delta);
	update_hit_box_position();

	Player* player = (Player*)CharacterManager::instance()->get_player();

	if (player->get_hp() <= 0)
	{
		player->switch_state("dead");
	}
	else if (!player->get_attacking())
	{
		if (player->get_velocity().y > 0)
		{
			player->switch_state("fall");
		}
		else if (player->get_move_axis() == 0)
		{
			player->switch_state("idle");
		}
		else if (player->is_on_floor() && player->get_move_axis() != 0)
		{
			player->switch_state("run");
		}
	}
}

//状态的退出操作
void PlayerAttackState::on_exit()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->get_hit_box()->set_enabled(false);
	player->set_attacking(false);
}

//更新攻击碰撞箱的位置
void PlayerAttackState::update_hit_box_position()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	Vector2 pos_center = player->get_logic_center();
	CollisionBox* hit_box = player->get_hit_box();
	const Vector2& size_hit_box = hit_box->get_size();

	//攻击碰撞箱位置略微偏移
	Vector2 pos_hit_box;
	switch (player->get_attack_dir())
	{
	case Player::AttackDir::Up:
		pos_hit_box = { pos_center.x, pos_center.y - size_hit_box.y / 2 };
		break;
	case Player::AttackDir::Down:
		pos_hit_box = { pos_center.x, pos_center.y + size_hit_box.y / 2 };
		break;
	case Player::AttackDir::Left:
		pos_hit_box = { pos_center.x - size_hit_box.x / 2, pos_center.y };
		break;
	case Player::AttackDir::Right:
		pos_hit_box = { pos_center.x + size_hit_box.x / 2, pos_center.y };
		break;
	}
	hit_box->set_position(pos_hit_box);
}

//死亡状态的初始化
PlayerDeadState::PlayerDeadState()
{
	timer.set_wait_time(2.0f);
	timer.set_one_shot(true);
	timer.set_on_timeout([&]()
		{
			MessageBox(GetHWnd(), _T("不对……\n这样不行。"), _T("挑战失败！"), MB_OK);
			exit(0);
		});
}

//死亡状态的进入操作
void PlayerDeadState::on_enter()
{
	CharacterManager::instance()->get_player()->set_animation("dead");

	play_audio(_T("player_dead"), false);
}

//死亡状态内部的更新
void PlayerDeadState::on_update(float delta)
{
	timer.on_update(delta);
}

//掉落状态进入时的操作
void PlayerFallState::on_enter()
{
	CharacterManager::instance()->get_player()->set_animation("fall");
}

//掉落状态更新的操作
void PlayerFallState::on_update(float delta)
{
	Player* player = (Player*)CharacterManager::instance()->get_player();

	if (player->get_hp() <= 0)
	{
		player->switch_state("dead");
	}
	else if (player->is_on_floor())
	{
		player->switch_state("idle");
		player->on_land();

		play_audio(_T("player_land"), false);
	}
	else if (player->can_attack())
		player->switch_state("attack");
}

//闲置状态进入时的操作
void PlayerIdleState::on_enter()
{
	CharacterManager::instance()->get_player()->set_animation("idle");
}

//闲置状态更新时的操作
void PlayerIdleState::on_update(float delta)
{
	Player* player = (Player*)CharacterManager::instance()->get_player();

	if (player->get_hp() <= 0)
	{
		player->switch_state("dead");
	}
	else if (player->can_attack())
	{
		player->switch_state("attack");
	}
	else if (player->get_velocity().y > 0)
	{
		player->switch_state("fall");
	}
	else if (player->can_jump())
	{
		player->switch_state("jump");
	}
	else if (player->can_roll())
	{
		player->switch_state("roll");
	}
	else if (player->is_on_floor() && player->get_move_axis() != 0)
	{
		player->switch_state("run");
	}
}

//进入跳跃模式的操作
void PlayerJumpState::on_enter()
{
	CharacterManager::instance()->get_player()->set_animation("jump");

	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->on_jump();

	play_audio(_T("player_jump"), false);
}

//跳跃状态的更新
void PlayerJumpState::on_update(float delta)
{
	Player* player = (Player*)CharacterManager::instance()->get_player();

	if (player->get_hp() <= 0)
	{
		player->switch_state("dead");
	}
	else if (player->get_velocity().y > 0)
	{
		player->switch_state("fall");
	}
	else if (player->can_attack())
	{
		player->switch_state("attack");
	}

}

//翻滚状态的初始化
PlayerRollState::PlayerRollState()
{
	timer.set_wait_time(0.35f);
	timer.set_one_shot(true);
	timer.set_on_timeout([&]()
		{
			Player* player = (Player*)CharacterManager::instance()->get_player();
			player->set_rolling(false);
		});
}

//进入翻滚状态的所有操作被封装于此
void PlayerRollState::on_enter()
{
	CharacterManager::instance()->get_player()->set_animation("roll");

	Player* player = (Player*)CharacterManager::instance()->get_player();

	//因为翻滚时无敌，所以关闭了受击碰撞箱
	player->get_hurt_box()->set_enabled(false);
	player->set_rolling(true);
	player->on_roll();
	timer.restart();

	play_audio(_T("player_roll"), false);
}

//翻滚状态的更新
void PlayerRollState::on_update(float delta)
{
	timer.on_update(delta);

	Player* player = (Player*)CharacterManager::instance()->get_player();

	if (!player->get_rolling())
	{
		if (player->get_move_axis() != 0)
		{
			player->switch_state("run");
		}
		else if (player->can_jump())
		{
			player->switch_state("jump");
		}	
		else
		{
			player->switch_state("idle");
		}
	}
}

//退出翻滚状态的操作
void PlayerRollState::on_exit()
{
	CharacterManager::instance()->get_player()->get_hurt_box()->set_enabled(true);
}

//进入奔跑状态的操作
void PlayerRunState::on_enter()
{
	CharacterManager::instance()->get_player()->set_animation("run");

	play_audio(_T("player_run"), true);
}

//在跑步状态的更新
void PlayerRunState::on_update(float delta)
{
	Player* player = (Player*)CharacterManager::instance()->get_player();

	if (player->get_hp() <= 0)
	{
		player->switch_state("dead");
	}
	else if (player->get_move_axis() == 0)
	{
		player->switch_state("idle");
	}
	else if (player->can_jump())
	{
		player->switch_state("jump");
	}
	else if (player->can_attack())
	{
		player->switch_state("attack");
	}
	else if (player->can_roll())
	{
		player->switch_state("roll");
	}
	else
	{

	}
}

//跑步状态结束的操作
void PlayerRunState::on_exit()
{
	stop_audio(_T("player_run"));

}
