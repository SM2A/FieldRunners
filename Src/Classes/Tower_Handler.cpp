#include"../Interfaces/Tower_Handler.hpp"
#include"../Interfaces/Towers/Gatling.hpp"
#include"../Interfaces/Towers/Missile.hpp"
#include"../Interfaces/Towers/Tesla.hpp"
#include"../Interfaces/Enemies/Enemie.hpp"

using namespace std;

#define GATLING_FIRE_RATE 1000
#define GATLING_PRICE 55
#define GATLING_U_PRICE 40
#define GATLING_DAMAGE 35
#define GATLING_U_DAMAGE 35
#define GATLING_RADUIS 150
#define GATLING_DAMAGE_TYPE SINGLE
#define GATLING_LVL 1
#define GATLING_PIC_PATH "Res/Towers/gattling"

#define MISSILE_FIRE_RATE 3000
#define MISSILE_PRICE 70
#define MISSILE_U_PRICE 60
#define MISSILE_DAMAGE 75
#define MISSILE_U_DAMAGE 75
#define MISSILE_RADUIS 150
#define MISSILE_DAMAGE_TYPE AREA_SPLASH
#define MISSILE_LVL 1
#define MISSILE_PIC_PATH "Res/Towers/missile"

#define TESLA_FIRE_RATE 1500
#define TESLA_PRICE 120
#define TESLA_U_PRICE 100
#define TESLA_DAMAGE 700
#define TESLA_U_DAMAGE 1000
#define TESLA_RADUIS 150
#define TESLA_DAMAGE_TYPE SINGLE
#define TESLA_LVL 1
#define TESLA_PIC_PATH "Res/Towers/tesla"

Tower_Handler::Tower_Handler(){}

void Tower_Handler::create_tower(Game* game,Window* window,vector<pair<float,float>> path,char pressed_key){

    switch(pressed_key){

        case 'g':{
            if(!validat(game,path,GATLING_PRICE)) break;
            Gatling* gatling = new Gatling(GATLING_FIRE_RATE,GATLING_PRICE,GATLING_U_PRICE,GATLING_U_DAMAGE,GATLING_RADUIS,
            GATLING_DAMAGE_TYPE,GATLING_DAMAGE,GATLING_LVL,GATLING_PIC_PATH,chrono::steady_clock::now(),last_clicked_position,window); 
            towers.push_back(gatling);
            game->pay_for_tower(GATLING_PRICE);
            break;

        }case 't':{
            if(!validat(game,path,TESLA_PRICE)) break;
            Tesla* tesla = new Tesla(TESLA_FIRE_RATE,TESLA_PRICE,TESLA_U_PRICE,TESLA_U_DAMAGE,TESLA_RADUIS,
            TESLA_DAMAGE_TYPE,TESLA_DAMAGE,TESLA_LVL,TESLA_PIC_PATH,chrono::steady_clock::now(),last_clicked_position,window);
            towers.push_back(tesla);
            game->pay_for_tower(TESLA_PRICE);
            break;

        }case 'm':{
            if(!validat(game,path,MISSILE_PRICE)) break;
            Missile* missile = new Missile(MISSILE_FIRE_RATE,MISSILE_PRICE,MISSILE_U_PRICE,MISSILE_U_DAMAGE,MISSILE_RADUIS,
            MISSILE_DAMAGE_TYPE,MISSILE_DAMAGE,MISSILE_LVL,MISSILE_PIC_PATH,chrono::steady_clock::now(),last_clicked_position,window);
            towers.push_back(missile);
            game->pay_for_tower(MISSILE_PRICE);
            break;
        }
    }
}

void Tower_Handler::set_location(pair<float,float> last_clicked_position){

    this->last_clicked_position=last_clicked_position;
}

bool Tower_Handler::validat(Game* game,vector<pair<float,float>> path,int price){

    bool is_on_path = false,is_on_tower = false,enough_balance = true;
    is_on_tower = Tower().is_on_tower(last_clicked_position,towers);
    enough_balance = game->enough_balance(price);
    for(std::pair<float,float> tile : path)
        if(tile==last_clicked_position) is_on_path = true;

    return ((enough_balance)&&(!is_on_path)&&(!is_on_tower));
}

void Tower_Handler::draw(){

    for(Tower* tower : towers)
        tower->draw();
}

void Tower_Handler::shoot(Window* window,vector<Enemie*>& deployed,Game* game,Wave_Handler* wave_handler){

    for(Tower* tower : towers)
        tower->shoot(window,deployed,game,wave_handler);
}

void Tower_Handler::upgrade(char pressed_key,Game* game){

    if(pressed_key=='u'){
        for(Tower* tower : towers){
            if(tower->get_location()==last_clicked_position) tower->upgrade(game);
        }
    }
}