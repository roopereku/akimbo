#include <akimbo/Entity.hh>
#include <akimbo/Core.hh>

namespace akimbo
{

Core& Entity::getCore()
{
	static thread_local Core core;
	return core;
}

void Entity::onPropertyChanged(Property& property)
{
}

void Entity::addTask(std::shared_ptr <Task>&& task)
{
	getCore().addTask(std::move(task));
}

}
