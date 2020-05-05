#include"../../Interfaces/Towers/Missile.hpp"
#include"../../Interfaces/Enemies/Enemie.hpp"
#include"../../Interfaces/Wave_Handler.hpp"
#include<algorithm>

using namespace std;

#define SOUND_TRACK "Res/Towers/missile.wav"
#define EXPLODE_RANGE 50
#define TILE_SIZE 60

Missile::Missile(int fire_rate,int init_price,int upgrade_price,int upgrade_damage,int radius,enum damageType damage_type,
                int damage,int lvl,string pic_address,chrono::time_point<chrono::steady_clock> last_shoot,
                pair<float,float> position,Window* window,Enemie* target)
    :Tower(fire_rate,init_price,upgrade_price,upgrade_damage,radius,damage_type,damage,lvl,pic_address,last_shoot,
                position,window,nullptr){

    Tower::sound_track = SOUND_TRACK;
}

bool Missile::shoot(Window* window,std::vector<Enemie*>& deployed,Game* game,Wave_Handler* wave_handler){
    
    bool is_shoot = Tower::shoot(window,deployed,game,wave_handler);
    if((this->target!=nullptr)&&(is_shoot)){
        vector<pair<Enemie*,float>> explode_range = Enemie().clothest_enemy(this->target->get_location(),deployed);
        float damage_range = (float)EXPLODE_RANGE/TILE_SIZE;
        for(int i=0;i<explode_range.size();i++){
            if(damage_range>=explode_range[i].second){            
                Enemie* kill = explode_range[i].first->deal_damage(this->damage);
                if(kill!=nullptr){
                    kill->die(game,window);
                    window->play_sound_effect("Res/Enemies/die.wav");
                    deployed.erase(remove(deployed.begin(),deployed.end(),kill),deployed.end());
                    delete(kill);
                    if(deployed.size()==0) wave_handler->next_wave();
                }
            }
        }
    }
}