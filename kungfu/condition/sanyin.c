// sanyin.c


#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "sanyin"; }

string chinese_name() { return "六阴蜈蚣爪之毒"; }

string update_msg_others()
{
       return "$N突然浑身不住的抖动，看上去十分痛苦。\n";
}

string update_msg_self()
{
	return HIB "忽然你觉得四肢百赅是似乎有无数小虫在游走，麻痒难忍！"NOR"\n";
}

