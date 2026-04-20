#ifndef _COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_

#include "collision_box.h"

#include <vector>

class CollisionManager
{
public:
	//在外部通过类名调用，协助创建唯一实例manager
	static CollisionManager* instance();

	//创建碰撞箱
	CollisionBox* create_collision_box();

	//销毁碰撞箱  
	void destroy_collision_box(CollisionBox* collision_box);

	//检测碰撞，并调用相关的回调函数
	void process_collide();

	//绘制碰撞箱的框
	void on_debug_render();

private:
	//创建唯一实例唯一实例
	static CollisionManager* manager;

	//创建碰撞箱对象的数组
	std::vector<CollisionBox*> collision_box_list;

private:
	CollisionManager();
	~CollisionManager();

};

#endif // !_COLLISION_MANAGER_H_
