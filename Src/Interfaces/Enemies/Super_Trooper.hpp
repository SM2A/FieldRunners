#ifndef SUPER_TROOPER_HPP
#define SUPER_TROOPER_HPP

#include"Enemie.hpp"

class Super_Trooper : public Enemie{

public:

    Super_Trooper(float health,int speed,int kill_bounus,int damage,std::pair<float,float> location,
                std::string pic_address,int size,int pic_count,Window* window,int destination_index=1);

};

#endif