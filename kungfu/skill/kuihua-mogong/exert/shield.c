// shield.c 护体神功
//



inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string query_name() { return "魔功"ZJBR"护体"; }

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("你只能用葵花魔功来提升自己的防御力。\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("你的内力不够。\n");

	if ((int)me->query_skill("kuihua-mogong", 1) < 50)
		return notify_fail("你的葵花魔功修为不够。\n");

	if ((int)me->query_temp("shield"))
		return notify_fail("你已经在运功中了。\n");

	skill = me->query_skill("kuihua-mogong");
	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_combatd(HIW "$N" HIW "身子如陀螺般急转不停，一股"
			"气流护住了全身！"NOR"\n", me);

	me->add_temp("apply/armor", skill / 2);
	me->set_temp("shield", 1);

	me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 2 :), skill);

	if (me->is_fighting()) me->start_busy(2);

	return 1;
}

void remove_effect(object me, int amount)
{
	me->add_temp("apply/armor", -amount);
	me->delete_temp("shield");
	tell_object(me, "你的葵花魔功运行完毕，将内力收回丹田。\n");
}
