#ifndef _RESOURCES_MANAGER_H_
#define _RESOURCES_MANAGER_H_

#include "atlas.h"

#include <string>
#include <graphics.h>
#include <unordered_map>

class ResourcesManager
{
public:
	static ResourcesManager* instance();

	void load();

	//对应于资源池的find方法
	Atlas* find_atlas(const std::string& id) const;
	IMAGE* find_image(const std::string& id) const;

private:
	static ResourcesManager* manager;

	//对应于图片形式建造两种资源池
	std::unordered_map<std::string, Atlas*> atlas_pool;
	std::unordered_map<std::string, IMAGE*> image_pool;

private:
	ResourcesManager();
	~ResourcesManager();

	//翻转图片的实现函数,因为图片资源只有一个朝向，所以要翻转
	void flip_image(IMAGE* src_image, IMAGE* dst_image, int num_h = 1);
	void flip_image(const std::string& src_id, const std::string dst_id, int num_h = 1);
	void flip_atlas(const std::string& src_id, const std::string dst_id);
	
};

#endif 
// !_RESOURCES_MANAGER_H_
