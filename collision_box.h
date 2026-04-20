#ifndef _COLLISION_BOX_H_
#define _COLLISION_BOX_H_

#include "vector2.h"
#include "collision_layer.h"

#include <functional>

class CollisionManager;

//碰撞箱的类
class CollisionBox
{
	friend class CollisionManager;

public:
	//设置是否启用碰撞检测
	void set_enabled(bool flag)
	{
		enabled = flag;
	}

	//设置碰撞层
	void set_layer_src(CollisionLayer layer)
	{
		layer_src = layer;
	}

	//设置碰撞层
	void set_layer_dst(CollisionLayer layer)
	{
		layer_dst = layer;
	}

	void set_on_collide(std::function<void()> on_collide)
	{
		this->on_collide = on_collide;
	}

	void set_size(const Vector2& size)
	{
		this->size = size;
	}

	const Vector2& get_size() const
	{
		return size;
	}

	void set_position(const Vector2& position)
	{
		this->position = position;
	}

private:
	Vector2 size;

	//箱子中心点所在位置
	Vector2 position;
	bool enabled = true;
	std::function<void()> on_collide;

	//自身层级
	CollisionLayer layer_src = CollisionLayer::None;
	//发生碰撞的对象的层级
	CollisionLayer layer_dst = CollisionLayer::None;

private:
	CollisionBox() = default;
	~CollisionBox() = default;

};

#endif 
// !_COLLISION_BOX_H_
