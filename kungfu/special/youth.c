// youth.c 驻颜
// Created by Doing Lu 10/7/2K

//#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "驻颜" NOR; }

int perform(object me, string skill)
{
	return notify_fail("这项技能能够保持你青春永驻，不需要运用。\n");
}
