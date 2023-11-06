#ifndef AKIMBO_WINDOW_HH
#define AKIMBO_WINDOW_HH

#include <akimbo/ValueProperty.hh>
#include <akimbo/UpdatingEntity.hh>

#include <string_view>

namespace akimbo
{

class Window : public UpdatingEntity
{
public:
	ValueProperty <unsigned> width;
	ValueProperty <unsigned> height;

protected:
	Window();
	virtual ~Window();

	virtual void onResize();
	virtual void onUpdate() override = 0;

private:
	void onPropertyChanged(Property& property) final override;
};

}

#endif
