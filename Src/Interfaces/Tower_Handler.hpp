#ifndef TOWER_HANDLER_HPP
#define TOWER_HANDLER_HPP

#include<vector>
#include"Towers/Tower.hpp"
#include"Game.hpp"
#include"../../Lib/RSDL/src/rsdl.hpp"

class Enemie;

class Tower_Handler{

public:

    Tower_Handler();
    void create_tower(Game* game,Window* window,std::vector<std::pair<float,float>> path,char pressed_key);
    void set_location(std::pair<float,float> last_clicked_position);
    void draw();
    void shoot(Window* window,std::vector<Enemie*>& deployed,Game* game,Wave_Handler* wave_handler);
    void upgrade(char pressed_key,Game* game);

private:

    std::vector<Tower*> towers;
    std::pair<float,float> last_clicked_position;
    bool validat(Game* game,std::vector<std::pair<float,float>> path,int price);

};

#endif