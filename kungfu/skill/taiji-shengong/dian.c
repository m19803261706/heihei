// heal.c



string query_name() { return "太极"ZJBR"疗伤"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	if (! target)
		return notify_fail("你要用真气为谁疗伤？\n");

	if (target == me)
		return notify_fail("你只能替别人疗伤。\n");

	if (me->is_fighting() || target->is_fighting())
		return notify_fail("战斗中无法运功疗伤！\n");

	if (target->query("not_living"))
		return notify_fail("你不能给" + target->name() + "疗伤。\n");

	if ((int)me->query("max_neili") < 1500)
		return notify_fail("你的内力还浅，不能运功疗伤。\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("你的真气现在不够，不能贸然行功。\n");

	if (target->query("eff_qi") >= target->query("max_qi") &&
	    target->query("eff_jing") >= target->query("max_jing"))
		return notify_fail("对方没有受伤，不需要接受治疗。\n");

	message_combatd(HIW "只见$N" HIW "双手食指和拇指虚拿，成“鹤嘴劲”势，"
			    "以食指指尖点在$n" HIW "耳尖三分处的“龙跃窍”，运"
			    "起\n内功，微微摆动。这" NOR + HIY "『鹤嘴劲点龙"
			    "跃窍』" NOR + HIW "使将出来，便是新断气之人也能还"
			    "魂片刻…………\n\n"
			    "不一会，$n" HIW "额头上冒出豆大汗珠，头上冒出隐隐"
			    "白雾，“哇”的一下吐出瘀血，脸色登时红润多了。\n"
			    NOR, me, target);

	me->add("neili", -800);
	me->receive_damage("qi", 100);
	me->receive_damage("jing", 50);

	target->receive_curing("qi", 100 + (int) me->query_skill("force") +
					   (int) me->query_skill("taiji-shengong", 1) * 3);

	if (target->query("qi") <= 0) target->set("qi", 1);
	target->receive_curing("jing", 100 + (int) me->query_skill("force") / 3 +
					     (int) me->query_skill("taiji-shengong", 1));

	if (target->query("jing") <= 0) target->set("jing", 1);
	if (! target->is_busy())
		target->stary_busy(2);

	message_vision("\n$N闭目冥坐，开始运功调息。\n", me);
	me->start_busy(10);

	return 1;
}
