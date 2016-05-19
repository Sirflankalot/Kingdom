#include "test.h"

#include "Base/tile_types.h"

#include "levelgen.h"
#include "rand.h"

#include "Enemies/shark.h"
#include "Enemies/zombie.h"

#include <iostream>
#include <thread>

namespace State {

    Test::Test(Game* game) : State_Base(game), generator(m_tileMap, getGame()), m_player(game, &m_tileMap) {
        m_lights.emplace_back(m_player.getTileMapPosition(), 5);

        for (int i = 0; i < 100; i++) {
            m_lights.emplace_back(sf::Vector2i(kingdom_random::num(1, Tiles::Info::MAP_SIZE),
                                               kingdom_random::num(1, Tiles::Info::MAP_SIZE)),
                                  9);
        }
    }

    void Test::input(const double dt) {
        m_player.input(dt);
    }

    // Always update lights, and then tiles and then entities
    void Test::update(const double dt) {
        addMobs();

        m_lights.at(0).setTileLocation(m_player.getTileMapPosition());

        m_tileMap.update(dt, m_player.getTileMapPosition(), m_lights);

        m_player.update(dt);

        for (auto& mob : m_mobs)
            mob->update(dt);

        for (unsigned i = 0; i < m_mobs.size(); i++) {
            m_mobs.at(i)->update(dt);
            if (!m_mobs.at(i)->isAlive()) {
                m_mobs.erase(m_mobs.begin() + i);
            }
        }
    }

    void Test::glDraw(const double dt) {}

    void Test::sfDraw(const double dt) {
        getGame().getWindow().pushGLStates();

        m_tileMap.draw(getGame().getWindow().get(), m_player.getTileMapPosition());
        m_player.draw(getGame().getWindow().get());

        for (auto& mob : m_mobs)
            mob->draw(getGame().getWindow().get());

        getGame().getWindow().popGLStates();
    }
    sf::Clock mobPrint;
    void Test::addMobs() {
        if (timer.getElapsedTime().asSeconds() > 0.3f) {
            // if ( random::num( 1, 10) == 1)
            { addZombie(); }
            timer.restart();
        }

        if (mobPrint.getElapsedTime().asSeconds() > 5) {
            std::cout << "Num mobs: " << m_mobs.size() << std::endl;
            mobPrint.restart();
        }
    }

    void Test::addZombie() {
        m_mobs.emplace_back(std::make_unique<Zombie>(&getGame(), &m_tileMap, &m_player, &m_mobs));
    }

    void Test::addShark() {
        m_mobs.emplace_back(std::make_unique<Shark>(&getGame(), &m_tileMap, &m_player));
    }

} // Namespace State
