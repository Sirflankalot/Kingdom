#include "ground_friction.h"

/*
	Applies friction to mobs based on tiles friction values.
*/

namespace Component {

	Ground_Friction::Ground_Friction(Mob* mob, Tile_Map* map) : Component_Base(mob), m_tileMap(map) {}

	void Ground_Friction::logic(const float dt) {
		// Shorthand
		sf::Vector2i pos = m_mob->getTileMapPosition();

		if (m_tileMap->at(pos)->isWalkable()) {
			m_mob->setVelocity({(float) m_mob->getVelocity().x * (float) m_tileMap->getFrictionAt(pos),
								(float) m_mob->getVelocity().y * (float) m_tileMap->getFrictionAt(pos)});
		}
	}
}
