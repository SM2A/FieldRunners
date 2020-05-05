#ifndef RUNNER_HPP
#define RUNNER_HPP

#include"Enemie.hpp"

class Runner : public Enemie {

public:

    Runner(float health,int speed,int kill_bounus,int damage,std::pair<float,float> location,
                std::string pic_address,int size,int pic_count,Window* window,int destination_index=1);

};

#endif