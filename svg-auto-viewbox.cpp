#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/intersect.hpp>
#include <cmdline/cmdline.h>

#define NANOSVG_IMPLEMENTATION   
#include <nanosvg/nanosvg.h>
#include <iostream>
#include <sstream>

#include <tinyxml2/tinyxml2.h>

typedef float real;
typedef glm::vec3 vec3;
typedef glm::vec2 vec2;
#define REAL float

struct AABB {

	AABB()
		: mMin(std::numeric_limits<real>::max()),
		mMax(-std::numeric_limits<real>::max())
	{}

	AABB(const vec2& mi, const vec2& ma) : mMin(mi), mMax(ma) {
		////
	}

	void offset(const vec2& o) {
		mMin += o;
		mMax += o;
	}

	void add(const vec2 &p) {
		mMin = glm::min(p, mMin);
		mMax = glm::max(p, mMax);
	}

	vec2 len() const { return mMax - mMin; }

	vec2 mMin;
	vec2 mMax;
};


int main(int ac, char** av) {
	for (int i = 1; i < ac; ++i) {
		struct NSVGimage* image;
		image = nsvgParseFromFile(av[i], "px", 1);
		if (image) {
			AABB aabb;
			aabb.add(glm::vec2(image->realBounds[0], image->realBounds[1]));
			aabb.add(glm::vec2(image->realBounds[2], image->realBounds[3]));

			glm::vec2 len = aabb.len();			

			tinyxml2::XMLDocument doc;
			doc.LoadFile(av[i]);
			auto svgElement = doc.FirstChildElement("svg");
			if (svgElement) {
				std::stringstream ss;
				ss << aabb.mMin.x << " " << aabb.mMin.y << " " << len.x << " " << len.y;
				svgElement->SetAttribute("viewBox", ss.str().c_str());
			}
			doc.SaveFile(av[i], true);
			nsvgDelete(image);
		}
	}
}