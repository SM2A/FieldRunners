#ifndef ENEMIE_HPP
#define ENEMIE_HPP

#include<string>
#include"../Back_Ground.hpp"
#include"../Game.hpp"

enum direction{FORWARD,BACKWARD};
enum axis{X,Y};

class Enemie {

public:

    Enemie();
    Enemie(float health,int speed,int kill_bounus,int damage,std::pair<float,float> location,
                std::string pic_address,int size,int pic_count,Window* window,int destination_index=1);
    Enemie* move(std::vector<std::pair<float,float>> path,int clock,Game* game,Window* window);
    std::vector<std::pair<Enemie*,float>> clothest_enemy(std::pair<float,float> center,std::vector<Enemie*> deployed);
    Enemie* deal_damage(int damage);
    void die(Game* game,Window* Wndow);
    std::pair<float,float> get_location();
    std::string get_name();

private:

    float health;
    int speed;
    int kill_bounus;
    int damage;
    std::pair<float,float> location;
    Window* window;
    int destination_index;
    std::string pic_address;
    int pic_count;
    int size;

    void draw(axis axis_,direction direction_,int clock);

protected:

    std::string name;

};

#endif