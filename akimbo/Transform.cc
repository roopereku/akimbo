#include "Transform.hh"

#include <glm/gtc/matrix_transform.hpp>

namespace Akimbo {

void Transform::scale(Vec3 amount)
{
	transform = glm::scale(transform, amount);
}

void Transform::rotate(Vec3 amount)
{
	transform = glm::rotate(transform, glm::radians(amount.x), Vec3(1, 0, 0));
	transform = glm::rotate(transform, glm::radians(amount.y), Vec3(0, 1, 0));
	transform = glm::rotate(transform, glm::radians(amount.z), Vec3(0, 0, 1));
}

void Transform::scale(float x, float y, float z)
{
	scale(Vec3(x, y, z));
}

void Transform::rotate(float x, float y, float z)
{
	rotate(Vec3(x, y, z));
}

}
