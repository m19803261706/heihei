//#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "锤法真解" NOR; }

int perform(object me, string skill)
{
	return notify_fail("这项技能可以提高你对锤法的领悟。\n");
}

string explain()
{
return "这是人类与生俱来的天赋，对所有的锤法都会有更强的领悟。";
}
