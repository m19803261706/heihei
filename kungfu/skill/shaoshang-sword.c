// six-fingers.c 六极神剑 - 少商剑

inherit SKILL;

mapping *action = ({
	([ "name":   "少商剑",
	   "action": "$N反过手来，双手拇指同时捺出，嗤嗤两声急响，“少商剑”"
		     "有如石迫天惊、风雨大至之势，指向$n的$l",
	   "force":  370,
	   "dodge":  10,
	   "damage": 100,
	   "damage_type":  "刺伤"
	]),
});

string main_skill() { return "six-finger"; }

int valid_enable(string usage) { return usage=="finger" ||  usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练少商剑必须空手。\n");

	if ((int)me->query("max_neili") < 2250)
		return notify_fail("你的内力太弱，无法学少商剑。\n");

	if ((int)me->query_skill("finger", 1) < (int)me->query_skill("shaoshang-sword", 1))
		return notify_fail("你的基本指法水平有限，无法无法领会更高深的少商剑。\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action); i > 0; i--)
		if(level >= action[i-1]["lvl"])
			return action[i-1]["skill_name"];
}

int practice_skill(object me)
{
 
 

	if ((int)me->query_skill("six-finger", 1))
		return notify_fail("你已经学齐六极神剑了。\n");

	if ((int)me->query("qi") < 100)
		return notify_fail("你的体力太低了。\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("你的内力不够练少商剑。\n");

	me->receive_damage("qi", 40);
	me->add("neili", -80);
	return 1;
}
					  
mixed hit_ob(object me, object victim, int damage_bonus)
{
	if( damage_bonus < 100 ) return 0;

	if( random(damage_bonus/4) > victim->query_str() )
	{
		victim->receive_wound("qi", (damage_bonus - 100) / 2 );
		return HIR "你听到「嗤啦」一声轻响，脸上竟溅到一些血滴！"NOR"\n";
	}
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}