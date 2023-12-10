#include <akimbo/Property.hh>
#include <akimbo/Entity.hh>

namespace akimbo
{

Property::Property(Entity& host) : host(host)
{
}

bool Property::operator==(Property& rhs)
{
	return this == &rhs;
}

void Property::triggerChange()
{
	host.onPropertyChanged(*this);
}

}
