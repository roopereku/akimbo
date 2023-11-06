#include <akimbo/Property.hh>
#include <akimbo/PropertyHost.hh>

namespace akimbo
{

Property::Property(PropertyHost& host) : host(host)
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
