#ifndef BACK_GROUND_HPP
#define BACK_GROUND_HPP

#include<string>
#include<vector>
#include "../../Lib/RSDL/src/rsdl.hpp"
#include"Tower_Handler.hpp"
#include"Game.hpp"

typedef std::vector<std::pair<float,float>> path_data;

class Back_Ground{

public:

    Back_Ground();
    void draw_field(Window* window);
    path_data read_input_path();
    path_data get_path();
    void handle_event(Window* window,Tower_Handler* tower_handler,Game* game);
    void lose(Window* window);
    void win(Window* window);

private:

    path_data path;

    void fill_path_x(path_data& path,float x,float y);
    void fill_path_y(path_data& path,float x,float y);
};

#endif