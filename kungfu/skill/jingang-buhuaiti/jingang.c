

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string query_name() { return "金刚"ZJBR"不坏"; }

int perform(object me, object target)
{
	int skill;

	if ((int)me->query("neili") < 100)
		return notify_fail("你的内力不够。\n");

	if ((int)me->query_skill("jingang-buhuaiti", 1) < 100)
		return notify_fail("你的金刚不坏护体神功修为不够。\n");

	if ((int)me->query_temp("shield"))
		return notify_fail("你已经运起护体神功了。\n");

	skill = me->query_skill("force");
	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_combatd(HIY "只听$N" HIY "高呼佛号，霎那间皮肤竟犹如镀金一般，发出灿灿金光。"NOR"\n", me);

	me->add_temp("apply/armor", skill / 2);
	me->set_temp("shield", 1);

	me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);

	if (me->is_fighting()) me->start_busy(2);

	return 1;
}

void remove_effect(object me, int amount)
{
	if (me->query_temp("shield"))
	{
		me->add_temp("apply/armor", -(amount / 2));
		me->delete_temp("shield");
		tell_object(me, "你的金刚不坏护体神功运行完毕，将内力收回丹田。\n");
	}
}

