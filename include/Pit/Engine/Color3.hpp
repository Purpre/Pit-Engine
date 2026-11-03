#pragma once
#include <glm/glm.hpp>

namespace Color3
{

struct RGB
{
	float r;
	float g;
	float b;

	RGB(float r, float g, float b) : r(r), g(g), b(b)
	{
	}

	RGB() = default;
};

struct HSV
{
	float h; // Hue
	float s; // Saturation
	float v; // Value

	HSV(float h, float s, float v) : h(h), s(s), v(v)
	{
	}

	HSV() = default;
};

inline HSV normalize(const HSV& hsv)
{
	HSV normalized;
	normalized.h = hsv.h / 360.0f; // H → [0, 1]
	normalized.s = glm::clamp(hsv.s, 0.0f, 1.0f);
	normalized.v = glm::clamp(hsv.v, 0.0f, 1.0f);
	return normalized;
}

inline RGB normalize(const RGB rgb)
{
	RGB normalized;
	normalized.r = rgb.r / 255.0f;
	normalized.g = rgb.g / 255.0f;
	normalized.b = rgb.b / 255.0f;
	return normalized;
}

inline RGB hsvToRgb(const HSV& hsv)
{
	HSV n = normalize(hsv);

	float h = n.h;
	float s = n.s;
	float v = n.v;

	float c = v * s;
	float x = c * (1.0f - glm::abs(glm::mod(h * 6.0f, 2.0f) - 1.0f));
	float m = v - c;

	float r = 0, g = 0, b = 0;

	if (h < 1.0f / 6.0f)
	{
		r = c;
		g = x;
		b = 0;
	}
	else if (h < 2.0f / 6.0f)
	{
		r = x;
		g = c;
		b = 0;
	}
	else if (h < 3.0f / 6.0f)
	{
		r = 0;
		g = c;
		b = x;
	}
	else if (h < 4.0f / 6.0f)
	{
		r = 0;
		g = x;
		b = c;
	}
	else if (h < 5.0f / 6.0f)
	{
		r = x;
		g = 0;
		b = c;
	}
	else
	{
		r = c;
		g = 0;
		b = x;
	}

	RGB result;
	result.r = (r + m) * 255.0f;
	result.g = (g + m) * 255.0f;
	result.b = (b + m) * 255.0f;

	return result;
}

inline HSV rgbToHsv(const RGB& rgb)
{
	RGB n = normalize(rgb);

	float r = n.r;
	float g = n.g;
	float b = n.b;

	float max = glm::max(r, glm::max(g, b));
	float min = glm::min(r, glm::min(g, b));
	float delta = max - min;

	HSV hsv;
	hsv.v = max;

	if (delta < 0.00001f)
	{
		hsv.h = 0.0f;
		hsv.s = 0.0f;
		return hsv;
	}

	hsv.s = (max > 0.0f) ? (delta / max) : 0.0f;

	if (max == r)
		hsv.h = (g - b) / delta + (g < b ? 6.0f : 0.0f);
	else if (max == g)
		hsv.h = (b - r) / delta + 2.0f;
	else
		hsv.h = (r - g) / delta + 4.0f;

	hsv.h *= 60.0f;

	return hsv;
}

} // namespace Color3