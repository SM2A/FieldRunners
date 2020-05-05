#ifndef TESLA_HPP
#define TESLA_HPP

#include"Tower.hpp"

class Tesla : public Tower{

public:

    Tesla(int fire_rate,int init_price,int upgrade_price,int upgrade_damage,int radius,enum damageType damage_type,
        int damage,int lvl,std::string pic_address,std::chrono::time_point<std::chrono::steady_clock> last_shoot
        ,std::pair<float,float> position,Window* window,Enemie* target=nullptr);

};

#endif