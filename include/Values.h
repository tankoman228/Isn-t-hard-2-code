#pragma once
#pragma comment(lib,"User32.lib")

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <SFML/Audio.hpp>
#include <fstream>
#include <vector>
#include <thread>

using namespace sf; using namespace std;

inline int screenw = 0, screenh = 0;

inline float scale = 1;
inline int scrollx = 0, scrolly = 0; //camera

inline bool dmode[999];
inline bool crystal[999];
inline bool lmode[999];
inline bool barmode[999]; //doors and other things

inline bool block_collision = false; //if any block of map_basic is being touched by player
inline int colint = 0; //time of player-block collision

inline bool scroll_pinned = false;

class Block; inline vector <Block*> map_basic, map_floor; 
class Movable; inline vector <Movable*> movables; //map

inline vector <Block*> triggers;

class Sq; inline Sq* chosen; //in editor

inline float UI_scale = 1;

inline float teleport_frame;
inline int tx[5], ty[5], teleport_to = -1; 

inline int coins_gathered = 0, coins_required, lvlnum = 1, levels_opened = 1;

inline int alpha = 255, tick = 0, level_scroll = 0;
inline int editor_scroll = 128, partnum, editor_mode = 1, editor_layer = 0, editor_block = 1, tp_rech = 0;
inline int achieve_fade = 0, editor_choose = 1, player_at_button = -1, page = 0;
inline int last_group = 0, last_angle = 0, last_size = 384;
inline int BG_particles_number = 12;

inline int CurrentAchievementData[2]; // вспомогательный буфер, когда открывается уровень ачивки, только так игра запомнит, какой, индекс то у всех один

inline float player_scale = 1;

inline int dir = 3; //direction of player rotation (from 1 to 8) (1 is -90, 2 is -45, 3 is 0, 5 is 90, 7 is 180)

inline bool saveornot, onclick = false, on_teleport = false;
inline bool button_overlapped = false, context_menu = false, close = false;
inline bool click_button_menu = false;
inline bool option_mode = false;
inline bool on_keyboard_click = false;
inline bool on_portal_trigger_edit = false;
inline bool deleting = false;

inline std::string helper_string = "", lvl_name = "Does_not_exist", current_filename = "";

inline Sprite playerS, eyes, blink, cursor, spiral[5], blend, block, box, box_but;
inline Font font; 
inline Text text, ach_text; 
inline Sprite ach_box, ach_BG;

inline std::map<std::string, Texture> Textures;
inline Texture *MapBasicTextures[128]; // кэш текстур для разных ID
inline Texture *MapFloorTextures[128]; // кэш текстур для разных ID

inline Texture t_play, t_levels, t_editor, t_ach, t_options, t_exit, ach_t, ach_bg;
inline Texture e_B, e_grid, e_E, e_Gr, e_Gy, e_L, e_L2, e_M, e_Mech, e_next, e_prev, e_play, e_player, e_plus, e_Q, e_R, e_Rt, e_save, e_load, e_fill;
inline Texture arrow_editor_t, editor_option, editor_num, editor_col, e_rotate__, EM_add, e_multichoose, e_copy;
inline Texture textblock, ach_complete, trash, t_plus, t_minus;
inline Texture achievement_button_t;

inline SoundBuffer scl, push, coin_s, boom, cryst, ach_b;
inline Sound s1, sound_p, sound_c, sound_b, _break, ach_s; 
inline Sound electro; 
inline SoundBuffer elbuf;
inline SoundBuffer telep; 
inline Sound tp_s; 
inline Sound sound_ab; 
inline SoundBuffer arpush;
inline Sound tp1, tp2, push2, open; 
inline SoundBuffer tp1_buf, tp2_buf, push2_buf, open_buf;
inline Music music;

inline RenderWindow window; 
inline ofstream logg;

// TODO: удалить
inline void Sleep(int time) {
    sleep(milliseconds(time));
}