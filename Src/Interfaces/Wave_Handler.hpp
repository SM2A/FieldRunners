#ifndef WAVE_HANDLER_HPP
#define WAVE_HANDLER_HPP

#include<vector>
#include<chrono>
#include"Enemies/Enemie.hpp"
#include"Game.hpp"

enum enemy{RUNNER,STUBBORN_RUNNER,SUPER_TROOPER,SCRAMBLER};
typedef std::vector<std::vector<int>> wave_data;
typedef std::vector<std::vector<Enemie*>> enemy_data;

class Wave_Handler{

public:

    Wave_Handler(int wave_num = 0 , time_t rest_time = time(0));
    void read_waves();
    void send_troops(int clock,path_data path,enemy_data& undeployed,std::vector<Enemie*>& deployed,
                        std::chrono::time_point<std::chrono::steady_clock> &previos,Game* game,Window* window);
    enemy_data create_troop(Window* window,std::pair<float,float> init_location);
    int total_round();
    int get_wave_num();
    void next_wave();

private:

    wave_data wave;
    int wave_num ;
    time_t rest_time;
};

#endif