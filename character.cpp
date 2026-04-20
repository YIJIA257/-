#include "character.h"
#include "collision_manager.h"

Character::Character()
{
	hit_box = CollisionManager::instance()->create_collision_box();//攻击碰撞箱
	hurt_box = CollisionManager::instance()->create_collision_box();//受击碰撞箱

	timer_invulnerable_status.set_wait_time(1.0f);//无敌特效的计时器
	timer_invulnerable_status.set_one_shot(true);
	timer_invulnerable_status.set_on_timeout([&]()
		{
			is_invulnerable = false;
		});

	timer_invulnerable_blink.set_wait_time(0.075f);
	timer_invulnerable_blink.set_one_shot(false);
	timer_invulnerable_blink.set_on_timeout([&]()
		{
			is_blink_invisible = !is_blink_invisible;
		});
}

Character::~Character()
{
	CollisionManager::instance()->destroy_collision_box(hit_box);
	CollisionManager::instance()->destroy_collision_box(hurt_box);
}

void Character::decrease_hp()
{
	if (is_invulnerable) return;

	hp -= 1;
	if (hp > 0)
	{
		make_invulnerable();
	}
		
	on_hurt();
}

void Character::on_input(const ExMessage& msg) { }//只有玩家才能操纵，所以留空，再通过派生类写内容


void Character::on_update(float delta)
{
	state_machine.on_update(delta);

	//检测死亡，死亡不能动，所以速度为0
	if (hp <= 0)
	{
		velocity.x = 0;
	}
		
	if (enable_gravity)
	{
		velocity.y += GRAVITY * delta;
	}
	
	position += velocity * delta;//重力影响速度

	if (position.y >= FLOOR_Y)//让角色一直保持在地板上，避免穿模
	{
		position.y = FLOOR_Y;
		velocity.y = 0;
	}

	//防止出地图
	if (position.x <= 0)
	{
		position.x = 0;
	}

	if (position.x >= getwidth()) position.x = (float)getwidth();

	//受击碰撞箱和角色的位置碰撞箱位置一致
	hurt_box->set_position(get_logic_center());

	//无敌状态的更新
	timer_invulnerable_status.on_update(delta);

	if (is_invulnerable)
	{
		//无敌状态的闪烁动画的的更新
		timer_invulnerable_blink.on_update(delta);
	}

	if (!current_animation) return;
	
	//设置动画朝向
	Animation& animation = (is_facing_left 
		? current_animation->left : current_animation->right);

	animation.on_update(delta);
	animation.set_position(position);
}

void Character::on_render()
{
	if (!current_animation || (is_invulnerable && is_blink_invisible)) return;//检测当前动画是否被设置或是否闪烁不可见

	(is_facing_left ? current_animation->left : current_animation->right).on_render();
}

void Character::on_hurt()
{
	//处理受击逻辑
}

void Character::switch_state(const std::string& id)
{
	state_machine.switch_to(id);
}

void Character::set_animation(const std::string& id)
{
	current_animation = &animation_pool[id];

	current_animation->left.reset();
	current_animation->right.reset();
}
