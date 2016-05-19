#ifndef Aggressive_Targeting_H
#define Aggressive_Targeting_H

/*
    Targets anything that attacks it, but is aggressive towards the player.
    Becomes non-aggressive after "m_maxDist" tiles away.
*/

#include "Bases/component.h"
#include "Bases/enemy_mob.h"
#include "player.h"

#include <memory>
#include <vector>

namespace Component {

    class Aggressive_Targeting : public Component_Base {
        typedef std::vector<std::unique_ptr<Mob>> MobPtrVec;

      public:
        Aggressive_Targeting(Mob* mob, Player* player, MobPtrVec* mobs, unsigned maxDist);

        void logic(const float dt) override;

      private:
        void checkDistToPlayer();

        void checkTarget();

        const unsigned getDistance(const sf::Vector2i& otherPos) const;

      private:
        MobPtrVec* m_mobVec; // The list of potential mobs to be attacking
        unsigned m_maxDist;  // The max distance before it becomes non aggressive

        Player* m_player;
    };
}

#endif // Aggressive_Targeting_H
