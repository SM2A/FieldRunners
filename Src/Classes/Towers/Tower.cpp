#include"../../Interfaces/Towers/Tower.hpp"
#include"../../Interfaces/Enemies/Enemie.hpp"
#include"../../Interfaces/Wave_Handler.hpp"
#include<algorithm>

using namespace std;

#define HORIZONTAL_START 120
#define VERTICAL_START 175
#define TOWER_SIZE 60
#define TILE_SIZE 60
#define MAX_LVL 3

Tower::Tower(){}

Tower::Tower(int fire_rate,int init_price,int upgrade_price,int upgrade_damage,int radius,enum damageType damage_type,
            int damage,int lvl,string pic_address,chrono::time_point<chrono::steady_clock> last_shoot,
            pair<float,float> position,Window* window,Enemie* target){

    this->fire_rate=fire_rate;
    this->init_price=init_price;
    this->upgrade_price=upgrade_price;
    this->upgrade_damage=upgrade_damage;
    this->radius=radius;
    this->damage_type=damage_type;
    this->damage=damage;
    this->lvl=lvl;
    this->pic_address=pic_address;
    this->last_shoot=last_shoot;
    this->position=position;
    this->window = window;
    this->target = target;
}

bool Tower::is_on_tower(std::pair<float,float> location,std::vector<Tower*> towers){

    for(int i = 0 ; i < towers.size() ; i++)
        if(location==towers[i]->position) return true;

    return false;
}

void Tower::draw(){

    string address = pic_address + to_string(lvl) + ".png";
    window->draw_img(address,Rectangle(Point((position.first*TILE_SIZE)+HORIZONTAL_START,
                            (position.second*TILE_SIZE)+VERTICAL_START),TOWER_SIZE,TOWER_SIZE));

}

void Tower::find_taget(vector<Enemie*>& deployed){

    if(!(count(deployed.begin(),deployed.end(),this->target))) this->target=nullptr;
    vector<pair<Enemie*,float>> distance = Enemie().clothest_enemy(this->position,deployed);
    float radius_ = (float)this->radius/TILE_SIZE;
    for(int i = 0 ; i < distance.size() ; i++){
        if((this->target==nullptr)&&(distance[i].second<=radius_)){
            this->target = distance[i].first;
            break;
        }
        if((this->target!=nullptr)&&(this->target==distance[i].first)){
            if(distance[i].second>radius_) this->target=nullptr;
        }
    }
}

bool Tower::shoot(Window* window,vector<Enemie*>& deployed,Game* game,Wave_Handler* wave_handler){
    
    this->find_taget(deployed);
    double time_spent = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now()-last_shoot).count();
    if((time_spent>=this->fire_rate)&&(this->target!=nullptr)){
        Enemie* kill = this->target->deal_damage(this->damage);
        shoot_sound(window);
        if(kill!=nullptr){
            this->target=nullptr;
            kill->die(game,window);
            window->play_sound_effect("Res/Enemies/die.wav");
            deployed.erase(remove(deployed.begin(),deployed.end(),kill),deployed.end());
            delete(kill);
            if(deployed.size()==0) wave_handler->next_wave();
        }
        this->last_shoot = chrono::steady_clock::now();
        return true;
    }
    return false;
}

void Tower::shoot_sound(Window* window){

    window->play_sound_effect(sound_track);
}

pair<float,float> Tower::get_location(){return this->position;}

void Tower::upgrade(Game* game){

    if((this->lvl!=MAX_LVL)&&(game->enough_balance(this->upgrade_price))){
        this->lvl++;
        this->damage+=this->upgrade_damage;
        game->pay_for_tower(this->upgrade_price);
    }
}