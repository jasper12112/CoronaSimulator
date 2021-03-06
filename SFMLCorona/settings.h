#pragma once

#define FRAME_RATE_LIMIT 75
#define SPEEDARR [35, 50, 75, 100, 150]

//Person info (TOTAL PEOPLE, SIZE OF PEOPLE)
#define TOTAL_PEOPLE 100
#define PersonSize 3

//Playfield
#define PFieldX 600
#define pFieldY 600

//Simulation hours CURRENTLY NOT USED
#define SIM_HOURS 10000

//Total infected people at start
#define TOTAL_START_INFECTED 5

//PERSON SETTINGS (RADIUS IN WHICH YOU CAN INFECT, HOW LONG INFECTED, HOW LONG IMMUNE, HOW LONG MAX STAY, PLAYER SPEED)
#define INFECTION_RADIUS 7
#define INFECTION_TIME 1000
#define IMMUNE_TIME 500
#define STAY_TIME 150
#define PLAYER_SPEED .3

#define SHOW_RADIUS 0

//80 = 20%
#define INFECTION_CHANCE 95
#define CHANCE_TO_DIE  99

//POPULAIR PLACES (CHANGE 2 =80%)
#define TOTAL_POPULAR_PLACES 10
#define CHANGE_GO_PLACE 1