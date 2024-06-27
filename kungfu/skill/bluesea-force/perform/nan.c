// nan.c 南海无影杖



inherit F_SSERVER;
 
string query_name() { return "无影"ZJBR"神杖"; }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int count;
	int lvl;
	int i,ap,dp;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("南海无影杖只能对战斗中的对手使用。\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    weapon->query("skill_type") != "staff")
		return notify_fail("先去找一把杖吧。\n");

	if (me->query("neili") < 200)
		return notify_fail("你的真气不够，无法施展南海无影杖！\n");

	if ((lvl = me->query_skill("bluesea-force", 1)) < 150)
		return notify_fail("你的南海玄功火候不够，无法施展南海无影杖！\n");

	if (! living(target))
	       return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	ap = me->query_skill("bluesea-force")*2 + me->query("con") * 20 +
	     me->query_skill("martial-cognize", 1);
	dp = target->query_skill("force") + target->query("con") * 20 +
	     target->query_skill("martial-cognize", 1);

	msg = HIC "$N" HIC "一圈手腕，将" + weapon->name() + HIC
	      "舞成一团光芒，进退间身形忽然变快，霎时合数招为一击攻向$n"
	      HIC "！"NOR"\n";
	i = 5;
	if (ap / 2 + random(ap) > dp)
	{
		msg += HIY "内力激荡之下，$n" HIY "登时觉得呼吸"
		       "不畅，浑身有如重压，万分难受，只见$N"
		       HIY "一杖接一杖的攻到，有如海浪。"NOR"\n";
		count = me->query_skill("bluesea-force", 1) / 5;
		me->add_temp("apply/attack", count);
		i += random(5);
	} else
	{
		msg += CYN "$n" CYN "见来招奇快，只好振作精神勉力抵挡。"NOR"\n";
		count = 0;
	}

	message_combatd(msg, me, target);
	me->add("neili", -i * 20);

	while (i--)
	{
		if(!target) break;
		if (! me->is_fighting(target))
			break;
		if (i > 5 && ! target->is_busy())
			target->start_busy(1);
		COMBAT_D->do_attack(me, target, weapon, 0);
	}
	if(target)
		target->interrupt_me(target, 1);

	me->add_temp("apply/attack", -count);
	me->start_busy(1 + random(7));
	return 1;
}
