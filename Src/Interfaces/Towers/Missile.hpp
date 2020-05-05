#ifndef MISSILE_HPP
#define MISSILE_HPP

#include"Tower.hpp"

class Missile : public Tower{

public:

    Missile(int fire_rate,int init_price,int upgrade_price,int upgrade_damage,int radius,enum damageType damage_type,
        int damage,int lvl,std::string pic_address,std::chrono::time_point<std::chrono::steady_clock> last_shoot
        ,std::pair<float,float> position,Window* window,Enemie* target=nullptr);

    bool shoot(Window* window,std::vector<Enemie*>& deployed,Game* game,Wave_Handler* wave_handler);
};

#endif