// lucky.c 鸿运当头
// Created by Doing Lu 10/7/2K

//#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "拳道真解" NOR; }

int perform(object me, string skill)
{
	return notify_fail("这项技能可以提高你对拳法的领悟。\n");
}

string explain()
{
return "这是人类与生俱来的天赋，对所有的拳法都会有更强的领悟。";
}
