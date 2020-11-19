
#pragma once

//место для макросов...

//начальные значения...
#define BEGIN_X 1
#define BEGIN_Y 1
#define FIELD_BEGIN_X BEGIN_X
#define FIELD_BEGIN_Y BEGIN_Y
#define INITIAL_SPEED 350
#define SPEED_MULTIPIER 0.1
//коды клавиш
#define KEY_ARROW_UP 72
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_DOWN 80
#define KEY_ARROW_LEFT 75
#define SPACE 32
//чары
#define FIELD_FRAME 178
#define BLOCK char(254)
#define EMPTY ' '
//цвета
#define FULL_PALETTE 0b0111'1111
#define CLEAR_PALETTE 0b0000'1111
#define FIELD_COLOR 0b0000'1111

//цвета фигур
#define T_COLOR 0b0000'1100
#define O_COLOR 0b0000'1101
#define I_COLOR 0b0000'0011
#define S_COLOR 0b0000'1110
#define J_COLOR 0b0000'1010
#define L_COLOR 0b0000'1001
#define Z_COLOR 0b0000'1011

#include <deque>
#include <Windows.h>
#include <map>
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <memory>
#include <conio.h>
#include <functional>
#include <type_traits>
#include <thread>
#include <mutex>
#include <chrono>

extern HANDLE hConsole;