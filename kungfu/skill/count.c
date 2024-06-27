// count.c

inherit SKILL;

string type() { return "knowledge"; }

void skill_improved(object me)
{
}

int valid_learn(object me)
{
 

	if (me->query("family/family_name") != "桃花岛")
		return notify_fail("桃花岛的弟子才能学习该技能。\n");
	if ((int)me->query_skill("mathematics", 1) < 50)
		return notify_fail("你的算术知识太差，无法理解阴阳八卦的奥妙。\n");
	if ((int)me->query_skill("mathematics", 1) < (int)me->query_skill("count", 1))
		return notify_fail("你的算术知识有限，无法理解更深奥的阴阳八卦。\n");
	if ((int)me->query_skill("count", 1) > (int)me->query("int")*10)
		return notify_fail("你的先天悟性不够，无法理解更深奥的阴阳八卦。\n");

	return 1;
}