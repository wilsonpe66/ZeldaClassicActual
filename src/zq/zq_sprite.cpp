#include "sprite.h"

int32_t fadeclk=-1;
int32_t frame=8;
bool BSZ=false;
int32_t conveyclk=0;
byte newconveyorclk=0;
bool freeze_guys=false;

void sprite::handle_sprlighting()
{
}

void sprite::check_conveyor()
{
}

void movingblock::push(zfix,zfix,int32_t,int32_t)
{
}

bool movingblock::animate(int32_t)
{
	return false;
}
