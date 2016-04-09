#ifndef Aggressive_Targeting_H
#define Aggressive_Targeting_H

/*
    Targets anything that attacks it, but is aggressive towards the player.
    Becomes non-aggressive after "m_maxDist" tiles away.
*/

#include "tilemap.h"
#include "enemy_mob.h"
#include "component.h"
#include "player.h"

#include <vector>
#include <memory>

typedef std::unique_ptr<Mob> MobPtr;
typedef std::vector<MobPtr> MobPtrVec;


namespace Component
{

class Aggressive_Targeting : public Component_Base
{
    public:
        Aggressive_Targeting ( Enemy_Mob* mob, Player* player,
                              MobPtrVec* mobs, unsigned maxDist );

        void
        logic   ( const float dt ) override;

    private:
        void
        checkDistToPlayer   ();

        void
        checkTarget         ();

        const unsigned
        getDistance         ( const sf::Vector2i& otherPos ) const;


    private:
        Enemy_Mob*  m_mob;              //The mob to be controlling
        MobPtrVec*  m_mobVec;           //The list of potential mobs to be attacking
        unsigned    m_maxDist;          //The max distance before it becomes non aggressive

        Player*     m_player;
};

}

#endif // Aggressive_Targeting_H