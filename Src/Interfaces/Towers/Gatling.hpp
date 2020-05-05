#ifndef GATLING_HPP
#define GATLING_HPP

#include"Tower.hpp"

class Gatling : public Tower{

public:

    Gatling(int fire_rate,int init_price,int upgrade_price,int upgrade_damage,int radius,enum damageType damage_type,
        int damage,int lvl,std::string pic_address,std::chrono::time_point<std::chrono::steady_clock> last_shoot
        ,std::pair<float,float> position,Window* window,Enemie* target=nullptr);

    void find_taget(std::vector<Enemie*>& deployed);
};

#endif