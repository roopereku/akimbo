#ifndef AKIMBO_VIEW_HH
#define AKIMBO_VIEW_HH

#include <akimbo/ValueProperty.hh>
#include <akimbo/Entity.hh>
#include <akimbo/Vector2.hh>

namespace akimbo
{

class View : public Entity
{
public:
	View();

	ValueProperty <Vec2i> size;

	virtual void onClick(Vec2i at) = 0;
	virtual void onDrag(Vec2i at) = 0;
};

}

#endif
