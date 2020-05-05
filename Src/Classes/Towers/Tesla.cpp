#include"../../Interfaces/Towers/Tesla.hpp"

using namespace std;

#define SOUND_TRACK "Res/Towers/tesla.wav"

Tesla::Tesla(int fire_rate,int init_price,int upgrade_price,int upgrade_damage,int radius,enum damageType damage_type,
            int damage,int lvl,string pic_address,chrono::time_point<chrono::steady_clock> last_shoot,
            pair<float,float> position,Window* window,Enemie* target)
    :Tower(fire_rate,init_price,upgrade_price,upgrade_damage,radius,damage_type,damage,lvl,pic_address,last_shoot,
            position,window,target){

        Tower::sound_track = SOUND_TRACK;
}