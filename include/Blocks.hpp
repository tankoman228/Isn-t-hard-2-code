#pragma once

#include <UI.h>
#include <Particles.h>
#include <Voids.h>
#include <Physics.h>
#include <Player.h>

#define px p.x
#define py p.y

#undef sx
#undef sy

#define psx p.sx
#define psy p.sy

struct Movable : public Sq {

	Sprite box;
	Sq anticheat = Sq(0,0,67); //Player mustn't get coin if it is blocked with movable!

	Movable(int _x, int _y, Texture& t, IntRect r);
	Movable(int _x, int _y, int _look);

	void InitMovablePhysics(int _x, int _y);
	void editor_behave();
	void cycle(float dt);
	void save(ofstream& save);
	void editing();
	void do_some_magic();
	void render();
};

void spawn_movable(int x, int y, int _type);

const inline bool* a = dmode;
const inline bool* b = crystal;
const inline bool* c = lmode;
const inline bool* d = barmode;

struct AbstractBlock : public Sq {

	Sprite box;
	int rotation = 0; float magnet = 0.14;
	bool electric = false;

	//editor flickering
	void do_some_magic();
	void update_scrolling();
	bool if_collide();
	void rotate(int angle);
	void editing();
	void setOpacity(int new_opacity /*0 is invisible, 255 is maximum*/);
	void basic_init(int x_, int y_, int rotation_, int _id);

	virtual void render();
	virtual void save(ofstream& save);
	virtual bool* getTarget();
	virtual int getGroup();
	virtual bool getReverse();
	virtual void editor_exist();
	virtual void cycle() {}

	AbstractBlock() {}
};

//Main layer

struct Wall : public AbstractBlock {

	Wall(int _x, int _y, int _id, int rotation_, int look);

	void cycle();
	void edit();
};

struct TargetGroupController : public AbstractBlock {

	Text text = Text(::text);
	bool* target;
	int group;
	bool reversed = false;

	bool* getTarget();
	int getGroup();
	void editing();
	void setTextColor();
	void editor_exist();
	bool getReverse();
};

struct Switcher : public TargetGroupController {

	bool irreversible = false, available = true; 

	Switcher(int _x, int _y, int _id, int rotation_, bool* target_, int group_, bool irreversible_);
	
	void editor_exist();
	void update();
	void cycle();
	void save(ofstream& save);
};

struct Detector : public TargetGroupController {

	Detector(int _x, int _y, int _id, int rotation_, bool* target_, int group_, bool reversed_);

	void cycle();
	void save(ofstream& save);
};

struct Questions : public AbstractBlock {

	int look;
	Text txt = Text(::text);

	Questions(int _x, int _y, int _id, int rotation_, int _look);

	void cycle();
	void update();
	void editor_exist();
};

struct Special : public AbstractBlock {

	int look;
	Special(int _x, int _y, int _id, int rotation_, int _look);

	void cycle();
	void render();
	void editing();
	void save(ofstream& save);
};

struct View_det : public TargetGroupController {

	View_det(int _x, int _y, int _id, int rotation_, bool* target_, int group_);

	void cycle();
	void render();
};

struct Speed_det : public TargetGroupController {

	Speed_det(int _x, int _y, int _id, int rotation_, bool* target_, int group_);

	void cycle();
	void render();
	void editor_exist();
};

//Floor

struct Basic_floor : public AbstractBlock {

	Basic_floor(int _x, int _y, int _id, int rotation_, int look);

	void cycle();
	void edit();
};

struct Special_floor : public AbstractBlock {

	int look;
	Special_floor(int _x, int _y, int _id, int rotation_, int _look);

	void cycle();
	void render();
	void save(ofstream& save);
	void edit();
	void editor_exist();
};

struct Portal : public AbstractBlock {

	int tp_to;
	Portal(int _x, int _y, int _id, int _tp_to);

	void render();
	void save(ofstream& save);
	void editor_exist();
	void edit();
};

struct Floor_button : public TargetGroupController {

	bool change = false; 

	Floor_button(int _x, int _y, int _id, int rotation_, bool* target_, int group_, bool change_);

	void cycle();
	void save(ofstream& save);
};

struct Door : public TargetGroupController {

	bool reversed;
	Door(int _x, int _y, int _id, int rotation_, bool* target_, int _group, bool reversed_);

	void cycle();
	void save(ofstream& save);
	bool getReverse();
};

//Electricity

struct Electric : public AbstractBlock {

	Sprite bg;
	int con[4] = {0,0,0,0}; int con_size = 0;
	int charge = 0, type = 0, group;

	Electric(int _x, int _y, int rotation, int _type, int _group);
	Electric();

	void set_connections(int* cons);
	void render();
};

inline vector <Electric*> electric;

void rech(int a, int b);
void rech(Electric& a, Electric& b);
void rech(Electric& a, int c);
void rech_give_charge(int a);

struct Wire : public Electric {

	int type = 0;

	Wire(int _x, int _y, int rotation_, int _type);
	void cycle();
	void save(ofstream& save);
};

struct Generator : public Electric {

	bool generator = true;

	Generator(int _x, int _y, int rotation_, int type, bool generator_);

	void cycle();
	void editor_exist();
	void save(ofstream& save);
};

struct ElectricSwitcher : public Electric {

	bool* target; int group;
	Text text = ::text;

	ElectricSwitcher(int x_, int y_, int rotation_, int type_, bool* target_, int group_);

	void setTextColor();
	bool* getTarget();
	int getGroup();
	void cycle();
	void save(ofstream& save);
	void editing();
	void editor_exist();
};

struct Switcher2 : public Electric {

	bool* target; bool reversed; int group;
	Text text = ::text;

	Switcher2(int x_, int y_, int rotation_, int type_, bool* target_, int group_, bool reversed_);

	bool* getTarget();
	int getGroup();
	void setTextColor();
	void cycle();
	void save(ofstream& save);
	void editing();
	void editor_exist();
};

struct Ac : public Electric {

	bool* target; int group; 
	Text text = ::text;

	Ac(int x_, int y_, int rotation_, int type_, bool* target_, int group_);

	bool* getTarget();
	int getGroup();
	void setTextColor();
	void cycle();
	void save(ofstream& save);
	void editing();
	void editor_exist();
};

struct El_Detector : public Electric {

	bool* target; int group;
	Text text = ::text;

	El_Detector(int x_, int y_, int rotation_, int type_, bool* target_, int group_);

	void setTextColor();
	bool* getTarget();
	int getGroup();
	void cycle();
	void save(ofstream& save);
	void editing();
	void editor_exist();
};

struct El_button : public Electric {

	bool reversed;
	El_button(int _x, int _y, int _rotation, bool _reversed);

	void cycle();
	void save(ofstream& save);
};

//Triggers

struct Trigger : public AbstractBlock {

	bool once_flag = false, stop = false;
	Sprite zone_marker;

	virtual void trigger() {}

	void render();
	void editor_exist();
	void edit();
	void save(ofstream& save);
};

struct Camera_trigger : public Trigger {
	Camera_trigger(int id_, int x_, int y_, int size_);
	void trigger();
};

struct Blind_trigger : public Trigger {
	int fade_time = 0;

	Blind_trigger(int id_, int x_, int y_, int size_);
	void render();
};

struct Portal_trigger : public Trigger {

	int delta_x = 200, delta_y = -500;
	Sprite zone_marker2, box2;

	Portal_trigger(int id_, int x_, int y_, int size_, int dx, int dy);

	void trigger();
	void edit();
	void editor_exist();
	void save(ofstream& save);
};

struct Player_size_trigger : public Trigger {

	float player_scale_multiplier = 1.24;

	void trigger();
	void edit();
	void save(ofstream& save);

	Player_size_trigger(int id_, int x_, int y_, int size_, float _player_scale_multiplier);
};

struct Text_Block : public AbstractBlock {

	Text txt;
	string text;

	Text_Block(int id_, int x_, int y_, string str);

	void render();
	void editor_exist();
	void edit();
	void editing();
	void save(ofstream& save);
};
