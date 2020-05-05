#include"../Interfaces/Game.hpp"

#define HEART_ADDRESS "Res/heart.png"
#define HEART_VERTICAL 100
#define HEART_HORIZONTAL 1200
#define HERAT_SIZE 60
#define CREDIT_ADDRESS "Res/credit.png"
#define CREDIT_VERTICAL 100
#define CREDIT_HORIZONTAL 1000
#define CREDIT_SIZE 60
#define ROUND_VERTICAT 110
#define ROUND_HORIZONTAL 600
#define FONT_ADDRESS "Res/OpenSans.ttf"
#define TIME_VERTICAT 110
#define TIME_HORIZONTAL 200
#define SEC_PER_MIN 60
#define LOSE 0
#define EMPTY 0
#define BEEP "Res/beep.wav"

using namespace std;

Game::Game(int player_health,int player_credit,int total_rounds,time_t init_time){

    this->player_health = player_health;
    this->player_credit = player_credit;
    this->total_rounds = total_rounds;
    this->init_time = init_time;
}

void Game::draw_player_status(Window* window,int round){

    window->draw_img(HEART_ADDRESS,Rectangle(Point(HEART_HORIZONTAL,HEART_VERTICAL),HERAT_SIZE,HERAT_SIZE));
    window->show_text(to_string(player_health),Point(HEART_HORIZONTAL+15,HEART_VERTICAL+10),WHITE,FONT_ADDRESS);
    window->draw_img(CREDIT_ADDRESS,Rectangle(Point(CREDIT_HORIZONTAL,CREDIT_VERTICAL),CREDIT_SIZE,CREDIT_SIZE));
    window->show_text(to_string(player_credit),Point(CREDIT_HORIZONTAL+15,CREDIT_VERTICAL+10),WHITE,FONT_ADDRESS);
    round++;
    string round_ = "Round : " + to_string(round) + " / " + to_string(total_rounds);
    window->show_text(round_,Point(ROUND_HORIZONTAL,ROUND_VERTICAT),WHITE,FONT_ADDRESS);
    string out_timer = to_string((int)difftime(time(0),init_time)/SEC_PER_MIN) + " : " 
                        + to_string((int)difftime(time(0),init_time)%SEC_PER_MIN);
    window->show_text(out_timer,Point(TIME_HORIZONTAL,TIME_VERTICAT),WHITE,FONT_ADDRESS);
}

void Game::enemy_damage(int damage,Window* window){
    player_health-=damage;
    window->play_sound_effect(BEEP);
    if(player_health<=LOSE) player_health=0;
}

bool Game::is_lose(){

    if(player_health==LOSE) return true;

    return false;
}

bool Game::is_win(vector<vector<Enemie*>> undeployed,vector<Enemie*> deployed){

    bool checker = true;
    for(vector<Enemie*> wave : undeployed)
        if(wave.size()!=EMPTY) checker=false;

    if((deployed.size()==EMPTY)&&checker) return true;

    return false;
}

bool Game::enough_balance(int price){

    if(this->player_credit>=price) return true;
    return false;
}

void Game::pay_for_tower(int price){

    this->player_credit-=price;
}

void Game::kill_enemy(int bonus){
    player_credit+=bonus;
}