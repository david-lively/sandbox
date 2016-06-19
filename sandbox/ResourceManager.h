#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <memory>
#include <typeinfo>
#include <string>
#include <map>
#include "Identity.h"

namespace Sandbox
{

	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		template<typename T>
		T& Create(const std::string& tag = "")
		{
			T& item = std::make_shared<T>();
		
			item.Tag = tag;
			m_resources[item.Id] = item;

			return *item;
		}

	private:
		std::map<int, std::shared_ptr<Identity>> m_resources;



	};
}

#endif