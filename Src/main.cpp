#include <iostream>
#include<vector>
#include<chrono>
#include "../Lib/RSDL/src/rsdl.hpp"
#include"Interfaces/Back_Ground.hpp"
#include"Interfaces/Wave_Handler.hpp"
#include"Interfaces/Tower_Handler.hpp"
#include"Interfaces/Game.hpp"

using namespace std;

#define GAME_NAME "Field Runners"
#define SOUND_TRACK "Res/game.mp3"
#define WINDOW_HIGHT 1024
#define WINDOW_WIDTH 1365
#define INIT_LOCATION 0
#define PLAYER_HEALTH 20
#define PLAYER_CREDIT 200
#define DELAY 30

int main() {

    int clock_ = 0 ;
    Window* window = new Window(WINDOW_WIDTH,WINDOW_HIGHT,GAME_NAME);
    Back_Ground* back_ground = new Back_Ground();
    Wave_Handler* wave_handler = new Wave_Handler();
    Tower_Handler* tower_handler = new Tower_Handler();
    back_ground->read_input_path();
    wave_handler->read_waves();
    vector<Enemie*> deployed;
    enemy_data undeployed = wave_handler->create_troop(window,back_ground->get_path()[INIT_LOCATION]);
    Game* game = new Game(PLAYER_HEALTH,PLAYER_CREDIT,wave_handler->total_round(),time(0));
    chrono::time_point<chrono::steady_clock> time_ = chrono::steady_clock::now();
    window->play_music(SOUND_TRACK);

    while(true){
        if(clock_==101) clock_=0;
        if(game->is_lose()){
            back_ground->lose(window);
            break;
        }
        if(game->is_win(undeployed,deployed)){
            back_ground->win(window);
            break;
        }
        window->clear();
        back_ground->handle_event(window,tower_handler,game);
        back_ground->draw_field(window);
        wave_handler->send_troops(clock_,back_ground->get_path(),undeployed,deployed,time_,game,window);
        tower_handler->draw();
        tower_handler->shoot(window,deployed,game,wave_handler);
        game->draw_player_status(window,wave_handler->get_wave_num());
        window->update_screen();
        delay(DELAY); 
        clock_++;
    }

    return 0;
}