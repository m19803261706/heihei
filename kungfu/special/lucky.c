// lucky.c 鸿运当头
// Created by Doing Lu 10/7/2K

//#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "鸿运当头" NOR; }

int perform(object me, string skill)
{
	return notify_fail("这项技能能给你带来很好的运气，不需要运用。\n");
}

string explain()
{
	return "这项技能能给你带来很好的运气，不需要运用。";
}