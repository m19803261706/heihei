// lamaism.c 密宗心法

inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me)
{
    if (me->query("family/family_name") != "血刀门"
        && me->query("family/family_name") != "雪山寺"
        && me->query("family/family_name") != "段氏皇族")
    return notify_fail("只有血刀门、雪山寺、段氏皇族的弟子才能学习该技能。\n");
    
    return 1;
}

int practice_skill(object me)
{
    return notify_fail("密宗心法只能靠学(learn)来提高。\n");
}

