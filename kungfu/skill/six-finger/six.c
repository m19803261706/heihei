// six.c 六脉剑气



inherit F_SSERVER;

string query_name() { return "六脉"ZJBR"剑气"; }
string *pfm_type() { return ({ "finger", }); }

int perform(object me, object target)
{
	mapping prepare;
	string msg;
	int skill;
	int delta;
	int ap, dp;
	int i;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}
	if (userp(me) && me->query("family/family_name") !="段氏皇族")
	{
		tell_object(me, "你不是段氏皇族人，根本使不出六脉剑气。\n");
		return 0;
	}
	if (! me->is_fighting(target))
		return notify_fail("「六脉剑气」只能对战斗中的对手使用。\n");

	if (me->query_skill_mapped("finger") != "six-finger")
		return notify_fail("你没有激发六极神剑，无法施展「六脉剑气」。\n");

	if (me->query_skill_prepared("finger") != "six-finger")
		return notify_fail("你没有准备使用六极神剑，无法施展「六脉剑气」。\n");

	skill = me->query_skill("six-finger", 1);

	if (skill < 200)
		return notify_fail("你的六极神剑修为有限，无法使用「六脉剑气」！\n");

	if (me->query_skill("force") < 360)
		return notify_fail("你的内功火候不够，难以施展「六脉剑气」！\n");

	if (me->query("max_neili") < 5000)
		return notify_fail("你的内力修为没有达到那个境界，无法运转内力形成「六脉剑气」！\n");

	if (me->query("neili") < 500)
		return notify_fail("你的真气不够，现在无法施展「六脉剑气」！\n");

	if (me->query_temp("weapon"))
		return notify_fail("你必须是空手才能施展「六脉剑气」！\n");

	if (! living(target))
		return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	msg = HIY "$N" HIY "摊开双手，手指连弹，霎时间空气炙热，几"
	      "欲沸腾，六道剑气分自六穴，一起杀向$n" HIY "！"NOR"\n";

	ap = me->query_skill("finger");
	dp = target->query_skill("force");
	if (ap / 2 + random(ap) > dp)
	{
		msg += HIR "$n" HIR "见此剑气纵横，微一愣神，不禁心萌退意。"NOR"\n";
		delta = -skill / 3;
	} else
		delta = 0;

	message_combatd(msg, me, target);

	me->add("neili", -300);
	target->add_temp("apply/parry", delta);
	target->add_temp("apply/dodge", delta);
/*
    if ( me->query("env/sign1") == "3478"&& me->query("mywife") ) {
		tell_object(me,HIY"你心无旁骛，对手在你眼中处处皆是"HIR"破绽。"NOR"\n");
		me->add_temp("apply/unarmed_damage", skill/2);
		me->add_temp("apply/attack", skill/2);
		target->add_temp("apply/parry", -skill/2);
		target->add_temp("apply/dodge", -skill/2);
		me->set_temp("papapa", 1);
	}
*/
	for (i = 0; i < 6; i++)
	{
		if (! me->is_fighting(target))
			break;
		if (random(3) == 1 && ! target->is_busy())
			target->start_busy(1);
		me->set_temp("six-action", i);
		COMBAT_D->do_attack(me, target, 0, 0);
	}
/*
    if ( me->query_temp("papapa")) {
		me->add_temp("apply/unarmed_damage", -skill/2);
		me->add_temp("apply/attack", -skill/2);
		target->add_temp("apply/parry", skill/2);
		target->add_temp("apply/dodge", skill/2);
		me->delete_temp("papapa");
	}
*/
	target->add_temp("apply/parry", -delta);
	target->add_temp("apply/dodge", -delta);
	target->interrupt_me(target, 1);
	me->delete_temp("six-action");
	me->start_busy(1 + random(6));

	return 1;
}
