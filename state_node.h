#ifndef _STATE_NODE_H_
#define _STATE_NODE_H_

#include <graphics.h>

class StateNode
{
public:
	StateNode() = default;
	~StateNode() = default;

	//当前进入此状态时的行为
	virtual void on_enter() { }

	//在状态内持续进行的行为
	virtual void on_update(float delta) { }

	//状态退出时的行为
	virtual void on_exit() { }

};

#endif 
// !_STATE_NODE_H_
