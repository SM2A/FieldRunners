#include"../Interfaces/Back_Ground.hpp"
#include<sstream>
#include<iostream>

using namespace std;

#define FIRST_INDEX 0
#define TILE_SIZE 60
#define FLAG_SIZE 40
#define HORIZONTAL_START 120
#define VERTICAL_START 175
#define HORIZONTAL_TRIM 15
#define VERTICAL_TRIM 30

#define BACK_GROUND_PATH "Res/background.png"
#define TILE_PATH_PATH "Res/tile.png"
#define START_FLAG_PATH "Res/start.png"
#define END_FLAG_PATH "Res/finish.png"

#define END_VERTICAL 312
#define END_HORIZONTAL 478
#define END_SIZE 400
#define LOSE_DEALY 3000
#define WIN_DEALY 8000
#define GAME_OVER_PATH "Res/game_over.png"
#define WIN_PATH "Res/win.png"
#define WIN_SOUND_TRACK "Res/win.wav"
#define LOSE_SOUND_TRACK "Res/game_over.wav"



Back_Ground::Back_Ground(){}

void Back_Ground::draw_field(Window* window){

    window->draw_img(BACK_GROUND_PATH);

    for(pair<int,int> xy : path){
        window->draw_img(TILE_PATH_PATH,Rectangle(Point((TILE_SIZE*xy.first)+HORIZONTAL_START,
        (TILE_SIZE*xy.second)+VERTICAL_START),TILE_SIZE,TILE_SIZE));
    }
    window->draw_img(START_FLAG_PATH,Rectangle(Point((TILE_SIZE*path[FIRST_INDEX].first)+HORIZONTAL_START,
                        (TILE_SIZE*path[FIRST_INDEX].second)+VERTICAL_START),FLAG_SIZE,FLAG_SIZE));
    window->draw_img(END_FLAG_PATH,Rectangle(Point((TILE_SIZE*path[path.size()-1].first)+VERTICAL_TRIM+HORIZONTAL_START,
                        (TILE_SIZE*path[path.size()-1].second)+HORIZONTAL_TRIM+VERTICAL_START),FLAG_SIZE,FLAG_SIZE));
}

path_data Back_Ground::read_input_path(){
    
    string way;
    getline(cin,way);
    stringstream stream(way);
    path_data path;
    int x,y;

    while(stream>>x){
        stream>>y;
        pair<int,int> path_x_y;
        path_x_y.first=x;
        path_x_y.second=y;
        if(path.size()>=1){      
            fill_path_x(path,x,y);  
            fill_path_y(path,x,y);
        }
        path.push_back(path_x_y);
    }
    this->path=path;
    return path;
}

void Back_Ground::fill_path_y(path_data& path,float x,float y){

    if((x==path[path.size()-1].first)&&((y!=path[path.size()-1].second+1)||(y!=path[path.size()-1].second-1))){
        int step = (y<path[path.size()-1].second) ? -1 : 1;
        int final = y;
        for(int y_=path[path.size()-1].second+step;y_!=final;){
            pair<int,int> path_x_y;
            path_x_y.first=x;
            path_x_y.second=y_;
            path.push_back(path_x_y);
            y_+=step;
        }
    }
}

void Back_Ground::fill_path_x(path_data& path,float x,float y){

    if((y==path[path.size()-1].second)&&((x!=path[path.size()-1].first+1)||(x!=path[path.size()-1].first-1))){
        int step = (x<path[path.size()-1].first) ? -1 : 1;
        int final = x;
        for(int x_=path[path.size()-1].first+step;x_!=final;){
            pair<int,int> path_x_y;
            path_x_y.first=x_;
            path_x_y.second=y;
            path.push_back(path_x_y);
            x_+=step;
        }
    }
}

path_data Back_Ground::get_path(){return path;}

void Back_Ground::handle_event(Window* window,Tower_Handler* tower_handler,Game* game){

    while(window->has_pending_event()){
        Event event = window->poll_for_event();
        switch(event.get_type()){

            case Event::QUIT :{
                exit(0);
                break;

            }case Event::LCLICK:{
                Point position = event.get_mouse_position();
                pair<float,float> location;
                location.first = (int)((position.x-HORIZONTAL_START)/TILE_SIZE);
                location.second = (int)((position.y-VERTICAL_START)/TILE_SIZE);
                tower_handler->set_location(location);
                break;

            }case Event::KEY_PRESS:{
                tower_handler->create_tower(game,window,path,event.get_pressed_key());
                tower_handler->upgrade(event.get_pressed_key(),game);
                break;
            }
        }
    }
}

void Back_Ground::lose(Window* window){

    window->draw_img(GAME_OVER_PATH,Rectangle(Point(END_HORIZONTAL,END_VERTICAL),END_SIZE,END_SIZE));
    window->stop_music();
    window->play_sound_effect(LOSE_SOUND_TRACK);
    window->update_screen();
    delay(LOSE_DEALY);
}

void Back_Ground::win(Window* window){

    window->draw_img(WIN_PATH,Rectangle(Point(END_HORIZONTAL,END_VERTICAL),END_SIZE,END_SIZE));
    window->stop_music();
    window->play_sound_effect(WIN_SOUND_TRACK);
    window->update_screen();
    delay(WIN_DEALY);
}