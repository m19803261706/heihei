//#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "拳脚真解" NOR; }

int perform(object me, string skill)
{
	return notify_fail("这项技能可以提高你对拳脚的领悟。\n");
}

string explain()
{
return "这是人类与生俱来的天赋，对所有的拳脚都会有更强的领悟。";
}
