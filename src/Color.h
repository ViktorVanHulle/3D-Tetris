#ifndef COLOR_H_
#define COLOR_H_

#include <glm/glm.hpp>

namespace Color {

	glm::vec4 chooseColor(int z) {
		if (z == 1) return glm::vec4(140.0f / 256.0f, 71.0f / 256.0f, 140.0f / 256.0f, 1.0f);
		if (z == 2) return glm::vec4(44.0f / 256.0f, 105.0f / 256.0f, 154.0f / 256.0f, 1.0f);
		if (z == 3) return glm::vec4(4.0f / 256.0f, 139.0f / 256.0f, 168.0 / 256.0f, 1.0f);
		if (z == 4) return glm::vec4(13.0f / 256.0f, 179.0f / 256.0f, 158.0f / 256.0f, 1.0f);
		if (z == 5) return glm::vec4(22.0f / 256.0f, 219.0f / 256.0f,  147.0f / 256.0f, 1.0f);
		if (z == 6) return glm::vec4(131.0f / 256.0f, 227.0f / 256.0f, 119.0f / 256.0f, 1.0f);
		if (z == 7) return glm::vec4(185.0f / 256.0f, 231.0f / 256.0f, 105.0f / 256.0f, 1.0f);
		if (z == 8) return glm::vec4(239.0f / 256.0f, 234.0f / 256.0f, 90.0f / 256.0f, 1.0f);
		if (z == 9) return glm::vec4(241.0f / 256.0f, 196.0f / 256.0f, 83.0f / 256.0f, 1.0f);
		if (z == 10) return glm::vec4(242.0f / 256.0f, 158.0f / 256.0f, 76.0f / 256.0f, 1.0f);

		return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
}

#endif // !COLOR_H_

