#ifndef SCRAMBLER_HPP
#define SCRAMBLER_HPP

#include "Enemie.hpp"

class Scrambler : public Enemie {

public:

    Scrambler(float health,int speed,int kill_bounus,int damage,std::pair<float,float> location,
                std::string pic_address,int size,int pic_count,Window* window,int destination_index=1);

};

#endif