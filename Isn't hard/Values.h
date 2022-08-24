#pragma once
#pragma comment(lib,"User32.lib")

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <windows.h>
#include <SFML/Audio.hpp>
#include <fstream>
#include <vector>
#include <thread>

using namespace sf; using namespace std;

/*const int wid = 60, hei = 30;*/ //Delete this later

int screenw, screenh;

float ex = 0, ey = 0; //eyes

float scale = 1;
int scrollx = 0, scrolly = 0; //camera

//float px = 0, py = 0;

bool dmode[999];
bool crystal[999];
bool lmode[999];
bool barmode[999]; //doors and other things

bool block_collision = false; //if any block of map_basic is being touched by player
int colint = 0; //time of player-block collision

bool stop_physics = true; //stops physics (after changing on false/true, must be Sleep(100);)
bool scroll_pinned = false;

class Block; vector <Block*> map_basic, map_floor; 
class Movable; vector <Movable*> movables; //map

vector <Block*> triggers;

class Sq; Sq* chosen; //in editor

float UI_scale = 1;

float teleport_frame;
int tx[5], ty[5], teleport_to = -1; 

float helper_s[2], helper_s2;
int i, j, k, s, helper; //helper values. Use carefully

int coins_gathered = 0, coins_required, lvlnum = 1, levels_opened = 1;

int alpha = 255, tick = 0, level_scroll = 0;
int editor_scroll = 128, partnum, editor_mode = 1, editor_layer = 0, editor_block = 1, tp_rech = 0;
int achieve_fade = 0, editor_choose = 1, player_at_button = -1, page = 0;
int last_group = 0, last_angle = 0, last_size = 384, achievements_scroll = 0;
int BG_particles_number = 12, achievement_file[2];

float player_scale = 1;

int dir = 3; //direction of player rotation (from 1 to 8) (1 is -90, 2 is -45, 3 is 0, 5 is 90, 7 is 180)

bool saveornot, onclick = false, on_teleport = false;
bool button_overlapped = false, context_menu = false, close = false;
bool click_button_menu = false;
bool option_mode = false;
bool on_keyboard_click = false;
bool on_portal_trigger_edit = false;
bool deleting = false;

std::string mode = "menu", helper_string = "", lvl_name = "Does_not_exist", current_filename = "";

Sprite playerS, eyes, block, cursor, spiral[5], blend, NPC, lvl_but, box, box_but;
Font font; Text text, ach_text; Sprite ach_box, ach_BG;

Texture body_t, eyes_t, box_t, box_but_t, cur, spir, inter, lev, blink;
Texture blue, el, switch_t, door, smth, smth2, smth3, str, corn, movable, finon, finoff, wall, bg, port_in, port_o, noth, glass;
Texture gray, gr, grb, strp, differ, rb, rose, green, greenf, greenw, roseb, greenf2, fl, crys, act, gravs, grav, buttonblock;
Texture _arrow, white, rosebut, whitewall, rosefloor2, rose_door, gray2, blue_floor2;
Texture rosebricks, portal2, lamp_blue, lamp_green, speed_det, view_det, player_det, player_det_inv, pusher, void_el;
Texture t_play, t_levels, t_editor, t_ach, t_options, t_exit, ach_t, ach_bg;
Texture e_B, e_grid, e_E, e_Gr, e_Gy, e_L, e_L2, e_M, e_Mech, e_next, e_prev, e_play, e_player, e_plus, e_Q, e_R, e_Rt, e_save, e_load, e_fill;
Texture some_help, trash, position_detector, achievement_button_t, c_button;
Texture arrow_editor_t, editor_option, editor_num, editor_col, e_rotate__, EM_add, e_multichoose, e_copy;
Texture textblock, ach_complete;

Texture t_camera, block_choose, t_plus, t_minus, t_darkness, t_portal, t_portal2, t_player_size;

Texture c_plus, c_minus, c_ac, BGel, c_one, c_corner, c_cross3, c_cross4, c_line, c_resist, c_sensor, c_sensor_on, c_switch, c_switch_off, c_switcher3;
Texture blue1_; //BG particle

SoundBuffer scl, push, coin_s, boom, cryst, ach_b;
Sound s1, sound_p, sound_c, sound_b, _break, ach_s; Sound electro; SoundBuffer elbuf;
SoundBuffer telep; Sound tp_s; Sound sound_ab; SoundBuffer arpush;
Sound tp1, tp2, push2, open; SoundBuffer tp1_buf, tp2_buf, push2_buf, open_buf;
Music music;

RenderWindow window; ofstream logg;