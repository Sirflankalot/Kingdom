#ifndef GROUND_FRICTION_H
#define GROUND_FRICTION_H

#include "Bases/component.h"
#include "Bases/mob.h"
#include "Other/tilemap.h"

/*
	Applies friction to mobs based on tiles friction values.
*/

namespace Component {

	class Ground_Friction : public Component_Base {
	  public:
		Ground_Friction(Mob* mob, Tile_Map* map);

		void logic(const float dt) override;

	  private:
		Tile_Map* m_tileMap;
	};
}

#endif // GROUND_FRICTION_H
