#include"../../Interfaces/Enemies/Enemie.hpp"

#define ERROR_RANGE 0.05
#define TILE_SIZE 60
#define PIC_EXTENTION ".png"
#define RIGHT "Right/"
#define DOWN "Down/"
#define UP "Up/"
#define HORIZONTAL_START 120
#define VERTICAL_START 175
#define DELAY 30
#define FRACTION 45000
#define FIRST_INDEX 0
#define CENTER 0.5
#define DED 0
#define DIE_SOUND_TRACK "Res/Enemies/die.wav"

using namespace std;

Enemie::Enemie(){}

Enemie::Enemie(float health,int speed,int kill_bounus,int damage,pair<float,float> location,string pic_address,
                                int size,int pic_count,Window* window,int destination_index){

    this->health=health;
    this->speed = speed;
    this->kill_bounus = kill_bounus;
    this->damage = damage;
    this->location = location;
    this->pic_address=pic_address;
    this->pic_count = pic_count;
    this->size = size;
    this->window=window;
    this->destination_index=destination_index;
}

Enemie* Enemie::move(path_data path,int clock,Game* game,Window* window){

    axis axis_ = abs(location.first - path[destination_index].first) < ERROR_RANGE ? X : Y;
    direction direction_;
    if(axis_==X) direction_ = ((int)(location.second)<(int)path[destination_index].second) ? FORWARD : BACKWARD;
    else if(axis_==Y) direction_ = ((int)(location.first)<(int)path[destination_index].first) ? FORWARD : BACKWARD ;

    draw(axis_,direction_,clock);
    if((abs(location.first - path[destination_index].first) < ERROR_RANGE)
        &&(abs(location.second - path[destination_index].second) < ERROR_RANGE)) 
            destination_index++;

    if(destination_index==path.size()){
        game->enemy_damage(this->damage,window);
        return this;
    }
    return nullptr;
}

void Enemie::draw(axis axis_,direction direction_,int clock){

    float step = !direction_ ? (float)(speed*DELAY)/FRACTION : (float)((-1)*speed*DELAY)/FRACTION;
    string picture = pic_address;
    bool flip = false;

    if(axis_==X) {
        location.second+=step;
        string address = (step > 0) ? DOWN+to_string(clock%pic_count)+PIC_EXTENTION :
                                        UP+to_string(clock%pic_count)+PIC_EXTENTION;
        picture+=address;
    }
    else if(axis_==Y) {
        location.first+=step;
        picture=picture+RIGHT+to_string(clock%pic_count)+PIC_EXTENTION;
        flip = (step > 0) ? false : true;
    }

    window->draw_img(picture,Rectangle(Point((TILE_SIZE*location.first)+HORIZONTAL_START,
                (TILE_SIZE*location.second)+VERTICAL_START),size,size),NULL_RECT,0,flip);
}

void swap(pair<Enemie*,float>& one,pair<Enemie*,float>& two){

    pair<Enemie*,float> temp_pair = one;
    one = two;
    two = temp_pair;
}

vector<pair<Enemie*,float>> Enemie::clothest_enemy(pair<float,float> center,vector<Enemie*> deployed){

    vector<pair<Enemie*,float>> distance;

    for(Enemie* enemy : deployed){
        pair<Enemie*,float> enemy_distance;
        enemy_distance.first = enemy;
        enemy_distance.second = sqrt((pow((center.first-enemy->location.first),2)+
                                      pow((center.second-enemy->location.second),2)));
        distance.push_back(enemy_distance);
    }
    if(deployed.size()>=2){
        for(int i = 0 ; i < distance.size()-1 ; i++){
            int min_index = i;
            for(int j = i+1 ; j < distance.size() ; j++){
                if(distance[j].second<distance[min_index].second) min_index = j;
            }
            swap(distance[min_index],distance[i]);
        }
    }
    return distance;
}

Enemie* Enemie::deal_damage(int damage){

    this->health-=damage;    
    if(this->health<=DED) return this;
    return nullptr;
}

void Enemie::die(Game* game,Window* Wndow){

    game->kill_enemy(this->kill_bounus);
}

pair<float,float> Enemie::get_location(){
    return this->location;
}

string Enemie::get_name(){return this->name;}