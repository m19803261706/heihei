// zhenwu.c 太极剑法「真武除邪」


#include <combat.h>

inherit F_SSERVER;

string final(object me, object target, int damage);

string query_name() { return "真武"ZJBR"除邪"; }
string *pfm_type() { return ({ "sword", }); }

string query_txt()
{
	return "要求：经过三丰真人指点绝技，基本剑法160级，内力300"ZJBR
	"效果：对比自身剑法激发等级和目标招架激发，同等级1/2概率，对目标造成造成一个单招伤害，同时追加伤害/4的精神伤害，本技能对邪派有10%命中和伤害加成";
}

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;

	if (userp(me) && ! me->query("can_perform/taiji-jian/zhenwu"))
		return notify_fail("你还不会使用「真武除邪」这一绝技。\n");

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("「真武除邪」只能对战斗中的对手使用。\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");

	if ((int)me->query_skill("taiji-jian", 1) < 160)
		return notify_fail("你的太极剑法不够娴熟，不会使用「真武除邪」。\n");

	if (me->query("neili") < 300)
		return notify_fail("你现在真气不够，无法使用「真武除邪」。\n");

	if (me->query_skill_mapped("sword") != "taiji-jian") 
		return notify_fail("你没有激发太极剑法，无法使用「真武除邪」！\n");

    if (! living(target))
	    return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	msg = HIY "$N" HIY "平平挥出一剑，横扫$n" HIY "。"NOR"\n";

	ap = me->query_skill("sword");
	dp = target->query_skill("parry");
	if (target->is_bad()) ap += ap / 10;

	me->start_busy(2);
	if (ap / 2 + random(ap) > dp)
	{
		damage = ap + random(ap / 3);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60, (: final, me, target, damage :));
		me->add("neili", -210);
	} else
	{
		msg += HIG "可是$p" HIG "看破了$P" HIG "的企图，镇"
		       "定逾恒，全神应对自如。"NOR"\n";
		me->add("neili", -100);
	}
	message_combatd(msg, me, target);

	return 1;
}

string final(object me, object target, int damage)
{
	target->receive_damage("jing", damage / 4, me);
	target->receive_wound("jing", damage / 8, me);
	return  HIY "结果$p" HIY "没有把它放在心上，随"
		"手应了一招，却见$P" HIY "剑势忽然一变"
		"，气象万千，变幻无穷，极具王者风范！\n"
		HIR "$p" HIR "惊慌失措，呆在当场，被$P"
		HIR "这一剑击中要害！鲜血崩流，惨不忍睹！"NOR"\n";
}

