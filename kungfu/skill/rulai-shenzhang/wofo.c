


inherit F_SSERVER;

string query_name() { return HIW"我佛"ZJBR"慈悲"NOR; }

//int query_pcd() { return 1; }

int perform(object me, object target)
{
	int level;
	string msg;
	int ap, dp;

        level = me->query_skill("rulai-shenzhang", 1);

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("如来神掌的「我佛慈悲」只能对战斗中的对手使用。\n");

	if (! living(target)||target->query("qi")<10)
		return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	msg = HIY "$N" HIY "拈花而笑，轻颂一声「我佛慈悲」，手掌往$n周身大穴轻轻拂去。"
	      "$n明明看透了$N" HIY "手掌的轨迹，却无处可避。"NOR"\n";

	me->add("neili", -60);
	ap = me->query_skill("strike");
	dp = target->query_skill("force");
	if (ap + random(ap) > dp/100)
	{
		msg += HIR "结果$p" HIR "被$P" HIR "一掌印在身上，一时间只觉得呼吸不畅，"
		       "浑身动弹不得。"NOR"\n";
		target->start_busy(level / 10 + 2);
                target->receive_damage("qi", target->query("qi")-1);
                target->receive_wound("qi", target->query("max_qi")/5);
	} else
	{
		msg += CYN "然而$p" CYN "内力深厚，和$P" CYN
		       "微一交手，随即连退数步，已然脱离了$N的掌力范围。" NOR;
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}
