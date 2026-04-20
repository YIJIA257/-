#include "collision_manager.h"

#include <algorithm>
#include <graphics.h>

//实现唯一实例
CollisionManager* CollisionManager::manager = nullptr;

//检测唯一实例是否初始化
CollisionManager* CollisionManager::instance()
{
	if (!manager)
	{
		manager = new CollisionManager();
	}
		
	return manager;
}

//创建一个碰撞箱，并将其放入碰撞箱列表
CollisionBox* CollisionManager::create_collision_box()
{
	CollisionBox* collision_box = new CollisionBox();

	collision_box_list.push_back(collision_box);

	return collision_box;
}

//摧毁碰撞箱，并实现在列表中的删除
void CollisionManager::destroy_collision_box(CollisionBox* collision_box)
{
	collision_box_list.erase(std::remove(collision_box_list.begin(), 
		collision_box_list.end(), collision_box), collision_box_list.end());

	delete collision_box;
}

//检测碰撞
void CollisionManager::process_collide()
{
	//遍历每个对象
	for (CollisionBox* collision_box_src : collision_box_list)
	{
		if (!collision_box_src->enabled || collision_box_src->layer_dst == CollisionLayer::None)
		{
			continue;
		}

		for (CollisionBox* collision_box_dst : collision_box_list)
		{
			if (!collision_box_dst->enabled || collision_box_src == collision_box_dst
				|| collision_box_src->layer_dst != collision_box_dst->layer_src)
			{
				continue;
			}

			//最右的边界点
			bool is_collide_x = (max(collision_box_src->position.x + collision_box_src->size.x / 2, 
				collision_box_dst->position.x + collision_box_dst->size.x / 2) - min(collision_box_src->position.x
					- collision_box_src->size.x / 2, collision_box_dst->position.x - collision_box_dst->size.x / 2) 
				<= collision_box_src->size.x + collision_box_dst->size.x);

			//最左的边界
			bool is_collide_y = (max(collision_box_src->position.y + collision_box_src->size.y / 2, 
				collision_box_dst->position.y + collision_box_dst->size.y / 2) - min(collision_box_src->position.y
					- collision_box_src->size.y / 2, collision_box_dst->position.y - collision_box_dst->size.y / 2)
				<= collision_box_src->size.y + collision_box_dst->size.y);

			//若发生碰撞则调用被碰对象的回调函数
			if (is_collide_x && is_collide_y && collision_box_dst->on_collide)
			{
				collision_box_dst->on_collide();
			}
		}
	}
}

//绘制碰撞箱
void CollisionManager::on_debug_render()
{
	for (CollisionBox* collision_box : collision_box_list)
	{
		setlinecolor(collision_box->enabled ? RGB(255, 195, 195) : RGB(115, 115, 175));

		//绘制矩形碰撞箱
		rectangle((int)(collision_box->position.x - collision_box->size.x / 2),
			(int)(collision_box->position.y - collision_box->size.y / 2),
			(int)(collision_box->position.x + collision_box->size.x / 2),
			(int)(collision_box->position.y + collision_box->size.y / 2));
	}
}

CollisionManager::CollisionManager() = default;

CollisionManager::~CollisionManager() = default;
