#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include "state_node.h"

#include <string>
#include <graphics.h>
#include <unordered_map>

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	//更新状态
	void on_update(float delta);

	//设置初始状态
	void set_entry(const std::string& id);

	//切换状态
	void switch_to(const std::string& id);

	//注册新的状态
	void register_state(const std::string& id, StateNode* state_node);

private:
	//检测是否初始化也就是说是否进行了on_enter
	bool need_init = true;

	//记录当前状态
	StateNode* current_state = nullptr;

	//设置资源池
	std::unordered_map<std::string, StateNode*> state_pool;

};

#endif 
// !_STATE_MACHINE_H_
