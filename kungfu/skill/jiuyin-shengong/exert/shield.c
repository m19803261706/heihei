// shield.c 九阴神功护体神功
//



inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string query_name() { return "九阴"ZJBR"护体"; }

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("你只能用九阴神功来提升自己的防御力。\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("你的内力不够。\n");

	if ((int)me->query_skill("jiuyin-shengong", 1) < 50)
		return notify_fail("你的九阴神功修为不够。\n");

	if ((int)me->query_temp("shield"))
		return notify_fail("你已经在运功中了。\n");

	skill = me->query_skill("jiuyin-shengong");
	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_combatd(HIW "$N" HIW "身子一晃，衣袖一波波的"
			"不住激荡，劲气逼人！"NOR"\n", me);

	me->add_temp("apply/armor", skill / 2);
	me->set_temp("shield", 1);

	me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 2 :), skill);

	if (me->is_fighting()) me->start_busy(2);

	return 1;
}

void remove_effect(object me, int amount)
{
	if (me->query_temp("shield"))
	{
		me->add_temp("apply/armor", -amount);
		me->delete_temp("shield");
		tell_object(me, "你的九阴神功运行完毕，将内力收回丹田。\n");
	}
}
