#ifndef TOWER_HPP
#define TOWER_HPP

#include<string>
#include<vector>
#include<chrono>
#include"../Game.hpp"
#include"../../../Lib/RSDL/src/rsdl.hpp"

enum damageType{SINGLE,AREA_SPLASH};
class Enemie;
class Wave_Handler;

class Tower {

public:

    Tower();
    Tower(int fire_rate,int init_price,int upgrade_price,int upgrade_damage,int radius,enum damageType damage_type,
            int damage,int lvl,std::string pic_address,std::chrono::time_point<std::chrono::steady_clock> last_shoot
            ,std::pair<float,float> position,Window* window,Enemie* target=nullptr);
    
    bool is_on_tower(std::pair<float,float> location,std::vector<Tower*> towers);
    void draw();
    virtual bool shoot(Window* window,std::vector<Enemie*>& deployed,Game* game,Wave_Handler* wave_handler);
    std::pair<float,float> get_location();
    void upgrade(Game* game);

private:

    int fire_rate;
    int init_price;
    int upgrade_price;
    int upgrade_damage;
    enum damageType damage_type;
    int lvl;
    std::string pic_address;
    std::chrono::time_point<std::chrono::steady_clock> last_shoot;
    Window* window;
    
    void shoot_sound(Window* window);
    virtual void find_taget(std::vector<Enemie*>& deployed);

protected:

    int damage;
    int radius;
    std::pair<float,float> position;
    Enemie* target;
    std::string sound_track;

};

#endif