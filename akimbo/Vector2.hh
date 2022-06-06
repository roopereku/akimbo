#ifndef AKIMBO_VECTOR2_HEADER
#define AKIMBO_VECTOR2_HEADER

#include <glm/vec2.hpp>

typedef glm::vec2 Vec2;
typedef glm::tvec2 <int> Vec2i;
typedef glm::tvec2 <size_t> Vec2s;

bool operator>=(const Vec2& first, const Vec2& second);
bool operator<=(const Vec2& first, const Vec2& second);
bool operator>(const Vec2& first, const Vec2& second);
bool operator<(const Vec2& first, const Vec2& second);

#endif
