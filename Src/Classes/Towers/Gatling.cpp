#include"../../Interfaces/Towers/Gatling.hpp"
#include"../../Interfaces/Enemies/Enemie.hpp"
#include<iostream>
#include<algorithm>

using namespace std;

#define TILE_SIZE 60
#define SOUND_TRACK "Res/Towers/gatling.wav"

Gatling::Gatling(int fire_rate,int init_price,int upgrade_price,int upgrade_damage,int radius,enum damageType damage_type,
                    int damage,int lvl,string pic_address,chrono::time_point<chrono::steady_clock> last_shoot,
                    pair<float,float> position,Window* window,Enemie* target)
    :Tower(fire_rate,init_price,upgrade_price,upgrade_damage,radius,damage_type,damage,lvl,pic_address,last_shoot,
                position,window,target){
    Tower::sound_track = SOUND_TRACK;
}

void Gatling::find_taget(std::vector<Enemie*>& deployed){

    if(!(count(deployed.begin(),deployed.end(),this->target))) this->target=nullptr;
    vector<pair<Enemie*,float>> distance = Enemie().clothest_enemy(this->position,deployed);
    float radius_ = (float)this->radius/TILE_SIZE;
    for(int i = 0 ; i < distance.size() ; i++){
        if((this->target==nullptr)&&(distance[i].second<=radius_)&&(distance[i].first->get_name()!="Stubborn_Runner")){
            this->target = distance[i].first;
            break;
        }
        if((this->target!=nullptr)&&(this->target==distance[i].first)){
            if(distance[i].second>radius_) this->target=nullptr;
        }
    }
}