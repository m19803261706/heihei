

inherit F_SSERVER;
 
string query_name() { return "群魔"ZJBR"乱舞"; }
string *pfm_type() { return ({ "staff", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int count;
	int lvl;
	int i;
 
	if (userp(me) && ! me->query("can_perform/fengmo-zhang/qunmo"))
		return notify_fail("你还不会使用「群魔乱舞」这一招。\n");

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("「群魔乱舞」只能对战斗中的对手使用。\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("你使用的武器不对。\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("你的内功火候不够，难以施展「群魔乱舞」！\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("你的真气不够，无法施展「群魔乱舞」！\n");

	if ((lvl = (int)me->query_skill("fengmo-zhang", 1)) < 120)
		return notify_fail("你的疯魔杖法还不到家，无法使用「群魔乱舞」！\n");

	if (me->query_skill_mapped("staff") != "fengmo-zhang")
		return notify_fail("你没有激发疯魔杖法，无法使用「群魔乱舞」！\n");

       if (! living(target))
	      return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	msg = HIR "只见$N" HIR "眼中杀气大盛，暴喝一声，飞扑上前，"
		  "便如发狂一般，手中的" + weapon->name() +
	      HIR "化出数道残影，一齐打向$n" HIR "！"NOR"\n";

	if (lvl / 2 + random(lvl) > target->query_skill("parry") * 2 / 3)
	{
		msg += HIY "$n" HIY "见$N" HIY "这等声势，早已无心恋"
		       "战，一时不知应该如何抵挡，唯有连连后退。"NOR"\n";
		count = lvl / 6;
		me->add_temp("apply/attack", count);
	} else
		count = 0;

	message_combatd(msg, me, target);
	me->add("neili", -100);

	for (i = 0; i < 3; i++)
	{
		if (! me->is_fighting(target))
			break;
		if (random(2) && ! target->is_busy())
			target->start_busy(1);
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->add_temp("apply/attack", -count);
	me->start_busy(1 + random(5));
	return 1;
}

