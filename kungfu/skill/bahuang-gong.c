// bahuang-gong.c 九天十地唯我至尊功

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force) { return force == "lingjiu-xinfa"; }

int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("bahuang-gong", 1);
    return lvl * lvl * 15 * 15 / 100 / 200;
}

int valid_learn(object me)
{
	if ((int)me->query_skill("force", 1) < 80)
		return notify_fail("你的基本内功火候还不够。\n");

	if (me->query("gender") == "无性" &&
	(int)me->query_skill("bahuang-gong", 1) > 49)
		return notify_fail("你无根无性，阴阳不调，难以领会高深的九天十地唯我至尊功。\n");

    	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("九天十地唯我至尊功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
	return __DIR__"bahuang-gong/" + func;
}
