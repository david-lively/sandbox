#ifndef IDENTITY_H
#define	IDENTITY_H

#include <string>

namespace Sandbox
{
	class Identity
	{
	public:
		int Id;
		std::string Tag;

		Identity()
		{
			Id = ++m_nextId;
		}

	private:
		static int m_nextId;
	};
}


#endif