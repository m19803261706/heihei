// zuoyou-hubo.c 玄虚互质
// by Doing Lu

inherit SKILL;



#define LEVEL_PER_LAYER	 30
#define MAX_LAYER	       12

string type() { return "special"; }

int valid_learn(object me)
{
	int layer;
	int lvl;

	lvl = me->query_skill("zuoyou-hubo", 1);
	
	if (me->query("family/family_name") != "古墓派" && me->query("family/family_name") != "全真教")
		return notify_fail("你不是古墓或全真弟子，无法领会这种技能。\n");
	
	if (me->query("gender") == "无性" && lvl >= 50)
		return notify_fail("你默默凝神，试图分心二用，可是却觉得阴阳失调，心浮气躁。\n");

	if (lvl >= MAX_LAYER * LEVEL_PER_LAYER)
		return notify_fail("你的玄虚互质之术已经修炼的炉火纯青，再难进步了。\n");

	layer = lvl / LEVEL_PER_LAYER;
	if (layer > MAX_LAYER) layer = MAX_LAYER;

	if (me->query("int") > 28 ||
	    me->query("int") + layer > 34)
		return notify_fail("你觉得心烦意乱，难以尝试更高深的分心之术。\n");

	return 1;
}
int valid_research(object me)
{
	return notify_fail("玄虚互质只能通过学习不断提高。\n");
}

int practice_skill(object me)
{
	return notify_fail("玄虚互质只能通过学习不断提高。\n");
}

void skill_improved(object me)
{
	int lvl;
	int layer;

	lvl = me->query_skill("zuoyou-hubo", 1);
	layer = lvl / LEVEL_PER_LAYER;
	if (layer > MAX_LAYER) layer = MAX_LAYER;
	
	if (me->query("family/family_name") != "古墓派" && me->query("family/family_name") != "全真教") {
		tell_object(me, "你不是古墓或全真弟子，无法领会这种技能。\n");
		return;
	}
	
	if (! layer)
	{
		tell_object(me, HIM "你潜心领悟左右互"
				"博，若有所悟。"NOR"\n");
	} else
	if ((lvl % LEVEL_PER_LAYER) == 0)
	{
		tell_object(me, HIM "你领悟了第" + chinese_number(layer) +
			    "层境界的玄虚互质的奥妙。"NOR"\n");
	} else
		tell_object(me, HIM "你对第" + chinese_number(layer) +
			    "层境界的玄虚互质又加深了一点了解。"NOR"\n");
}
