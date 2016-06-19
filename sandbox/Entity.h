#ifndef ENTITY_H
#define	ENTITY_H

#include <set>
#include <typeindex>
#include <typeinfo>
#include <map>

#include "Identity.h"
#include "Component.h"


namespace Sandbox
{
	class Entity : public Identity
	{
	public:
		Entity();
		~Entity();

		template<typename T>
		bool Is()
		{
			return m_components.count(std::type_index(typeid(T))) > 0;
		}

		template<typename T>
		T* As()
		{
			if (Is<T>())
			{
				return (T*)m_components[std::type_index(typeid(T))];
			}
			else
				return nullptr;
		}

	private:
		std::map<std::type_index, Component*> m_components;

	};
}

#endif
