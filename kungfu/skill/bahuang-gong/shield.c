// shield.c 八荒六合唯我独尊之护体神功
//



inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string query_name() { return "八荒"ZJBR"护体"; }

string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("你只能用九天十地唯我至尊功来提升自己的防御力。\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("你的内力不够。\n");

	if ((int)me->query_skill("bahuang-gong", 1) < 50)
		return notify_fail("你的九天十地唯我至尊功修为不够。\n");

	if ((int)me->query_temp("shield"))
		return notify_fail("你已经在运功中了。\n");

	skill = me->query_skill("force");
	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_combatd(HIW "$N" HIW "双手平举过顶，运起八荒六合唯"
			"我独尊功功，全身顿时笼罩在劲气之中！"NOR"\n", me);

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
		tell_object(me, "你的九天十地唯我至尊功运行完"
			    "毕，将内力收回丹田。\n");
	}
}
