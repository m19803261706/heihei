// ghost.c 鬼脉
// Created by chenzzz 2004/05/28

//#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "鬼脉" NOR; }

int perform(object me, string skill)
{
	return notify_fail("这项技能使你的气血较一般人少，不需要使用。\n");
}

string explain()
{
	return "这项技能使你的气血较一般人少，不需要使用。";
}