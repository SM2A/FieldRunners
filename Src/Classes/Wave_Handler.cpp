#include"../Interfaces/Wave_Handler.hpp"
#include"../Interfaces/Enemies/Runner.hpp"
#include"../Interfaces/Enemies/Scrambler.hpp"
#include"../Interfaces/Enemies/Stubborn_Runner.hpp"
#include"../Interfaces/Enemies/Super_Trooper.hpp"
#include<string>
#include<iostream>
#include<sstream>
#include<chrono>

#define WAVE_TIME 500
#define EMPTY 0
#define REST_TIME 3

#define RUNNER_HEALTH 250
#define RUNNER_SPEED 50
#define RUNNER_KILL_BOUNUS 6
#define RUNNER_DAMAGE 1
#define RUNNER_PIC_ADDRESS "Res/Enemies/Runner/"
#define RUNNER_PIC_COUNT 12
#define RUNNER_SIZE 40

#define STUBBORN_RUNNER_HEALTH 400
#define STUBBORN_RUNNER_SPEED 30
#define STUBBORN_RUNNER_KILL_BOUNUS 10
#define STUBBORN_RUNNER_DAMAGE 4
#define STUBBORN_RUNNER_PIC_ADDRESS "Res/Enemies/Stubborn_Runner/"
#define STUBBORN_RUNNER_PIC_COUNT 16
#define STUBBORN_RUNNER_SIZE 40

#define SUPER_TROOPER_HEALTH 500
#define SUPER_TROOPER_SPEED 25
#define SUPER_TROOPER_KILL_BOUNUS 8
#define SUPER_TROOPER_DAMAGE 4
#define SUPER_TROOPER_PIC_ADDRESS "Res/Enemies/Super_Trooper/"
#define SUPER_TROOPER_PIC_COUNT 21
#define SUPER_TROOPER_SIZE 40

#define SCRAMBLER_HEALTH 100
#define SCRAMBLER_SPEED 90
#define SCRAMBLER_KILL_BOUNUS 4
#define SCRAMBLER_DAMAGE 2
#define SCRAMBLER_PIC_ADDRESS "Res/Enemies/Scrambler/"
#define SCRAMBLER_PIC_COUNT 4
#define SCRAMBLER_SIZE 40

using namespace std;

Wave_Handler::Wave_Handler(int wave_num , time_t rest_time ){

    this->wave_num = wave_num;
    this->rest_time = rest_time;
}

void Wave_Handler::read_waves(){

    string single_wave;
    wave_data waves;
    
    while(getline(cin,single_wave)){
        vector<int> enemie;
        int enemie_count;
        stringstream stream(single_wave);
        while(stream>>enemie_count) enemie.push_back(enemie_count);
        waves.push_back(enemie);
    }
    
    wave = waves;
}

void Wave_Handler::send_troops(int clock_,path_data path,enemy_data& undeployed,vector<Enemie*>& deployed,
                                chrono::time_point<chrono::steady_clock> &previos,Game* game,Window* window){

    double time_spent = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now()-previos).count();

    if((undeployed[wave_num].size()!=0)&&(time_spent>=WAVE_TIME)){
        srand(time(0));
        int random_enemy = rand()%undeployed[wave_num].size();
        deployed.push_back(undeployed[wave_num][random_enemy]);
        undeployed[wave_num].erase(undeployed[wave_num].begin()+random_enemy);
        previos = chrono::steady_clock::now();
    }

    for(int i = 0 ; i < deployed.size() ; i++){
        Enemie* kill = deployed[i]->move(path,clock_,game,window);
        if(kill!=nullptr){
            delete(kill);
            deployed.erase(deployed.begin()+i);
            if((deployed.size()==0)) {
                rest_time = time(0);
            }
        }
    }

    if((deployed.size()==0)&&(difftime(time(0),rest_time)>=REST_TIME)) wave_num++;
}

enemy_data Wave_Handler::create_troop(Window* window,pair<float,float> init_location){

    enemy_data troops;
    for(int wave_num = 0 ; wave_num < wave.size() ; wave_num++){
        vector<Enemie*> wave_troops;
        for(int troop = 0 ; troop < wave[wave_num].size() ; troop++){
            for(int troop_count = 0 ; troop_count < wave[wave_num][troop] ; troop_count++){
                switch (troop){
                    case RUNNER:{
                        float health = (0.9 + (0.1*(wave_num+1))) * RUNNER_HEALTH;
                        Runner* runner = new Runner(health,RUNNER_SPEED,RUNNER_KILL_BOUNUS,RUNNER_DAMAGE,
                        init_location,RUNNER_PIC_ADDRESS,RUNNER_SIZE,RUNNER_PIC_COUNT,window);
                        wave_troops.push_back(runner);
                        break;
                    }case STUBBORN_RUNNER:{
                        float health = (0.9 + (0.1*(wave_num+1))) * STUBBORN_RUNNER_HEALTH;
                        Stubborn_Runner* stubbor_runner = new Stubborn_Runner(health,STUBBORN_RUNNER_SPEED,
                        STUBBORN_RUNNER_KILL_BOUNUS,STUBBORN_RUNNER_DAMAGE,init_location,
                        STUBBORN_RUNNER_PIC_ADDRESS,STUBBORN_RUNNER_SIZE,STUBBORN_RUNNER_PIC_COUNT,window);
                        wave_troops.push_back(stubbor_runner);
                        break;
                    }case SUPER_TROOPER:{
                        float health = (0.9 + (0.1*(wave_num+1))) * SUPER_TROOPER_HEALTH;
                        Super_Trooper* super_trooper = new Super_Trooper(health,SUPER_TROOPER_SPEED,
                        SUPER_TROOPER_KILL_BOUNUS,SUPER_TROOPER_DAMAGE,init_location,
                        SUPER_TROOPER_PIC_ADDRESS,SUPER_TROOPER_SIZE,SUPER_TROOPER_PIC_COUNT,window);
                        wave_troops.push_back(super_trooper);
                        break;
                    }case SCRAMBLER:{
                        float health = (0.9 + (0.1*(wave_num+1))) * SCRAMBLER_HEALTH;
                        Scrambler* scrambler = new Scrambler(health,SCRAMBLER_SPEED,SCRAMBLER_KILL_BOUNUS,
                        SCRAMBLER_DAMAGE,init_location,SCRAMBLER_PIC_ADDRESS,SCRAMBLER_SIZE,SCRAMBLER_PIC_COUNT,window);
                        wave_troops.push_back(scrambler);
                        break;
                    } 
                }
            }
        }
        troops.push_back(wave_troops);
    }

    return troops;
}

int Wave_Handler::total_round(){return wave.size();}

int Wave_Handler::get_wave_num(){return wave_num;}

void Wave_Handler::next_wave(){

    rest_time = time(0);
}