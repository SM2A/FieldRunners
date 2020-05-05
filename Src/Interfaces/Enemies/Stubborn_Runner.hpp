#ifndef STUBBORN_RUNNER_HPP
#define STUBBORN_RUNNER_HPP

#include"Enemie.hpp"

class Stubborn_Runner : public Enemie{

public:

    Stubborn_Runner(float health,int speed,int kill_bounus,int damage,std::pair<float,float> location,
                std::string pic_address,int size,int pic_count,Window* window,int destination_index=1);

};

#endif