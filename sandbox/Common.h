#ifndef COLOR_H
#define	COLOR_H

namespace Sandbox
{
	// RGBA color struct initialized to magenta
	struct Color
	{
		float r = 1.f;
		float g = 0.f;
		float b = 1.f;
		float a = 1.f;

		void Set(float red = 1, float green = 0, float blue = 1, float alpha = 1)
		{
			r = red;
			g = green;
			b = blue;
			a = alpha;
		}
	};
}



#endif