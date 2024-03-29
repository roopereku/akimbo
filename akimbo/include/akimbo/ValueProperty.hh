#ifndef AKIMBO_VALUE_PROPERTY_HH
#define AKIMBO_VALUE_PROPERTY_HH

#include <akimbo/Property.hh>

#include <utility>

namespace akimbo
{

template <typename T>
class ValueProperty : public Property
{
public:
	ValueProperty(Entity& host) : Property(host)
	{
	}

	ValueProperty(Entity& host, T&& initial) : Property(host), value(initial)
	{
	}

	ValueProperty <T>& operator=(T&& value)
	{
		this->value = std::move(value);
		triggerChange();

		return *this;
	}

	ValueProperty <T>& operator=(const T& value)
	{
		this->value = value;
		triggerChange();

		return *this;
	}

	T& operator()()
	{
		return value;
	}

	void assignWithoutTrigger(T&& value)
	{
		this->value = std::move(value);
	}

	void assignWithoutTrigger(const T& value)
	{
		this->value = value;
	}

	const T& getValue()
	{
		return value;
	}

private:
	T value;
};

}

#endif
