#ifndef GAME_HPP
#define GAME_HPP

#include"../../Lib/RSDL/src/rsdl.hpp"
#include<string>
#include<vector>

class Enemie;

class Game{

private:

    int player_health;
    int player_credit;
    int total_rounds;
    time_t init_time;

public:

    Game(int player_health,int player_credit,int total_rounds,time_t init_time);
    void draw_player_status(Window* window,int round);
    void enemy_damage(int damage,Window* window);
    bool is_lose();
    bool is_win(std::vector<std::vector<Enemie*>> undeployed,std::vector<Enemie*> deployed);
    bool enough_balance(int price);
    void pay_for_tower(int price);
    void kill_enemy(int bonus);
};

#endif