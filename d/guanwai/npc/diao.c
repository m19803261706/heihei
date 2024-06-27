//  /guanwai/npc/diao.c

inherit NPC;


void create()
{
	set_name(HIY"金雕"NOR, ({ "diao"}));
	set("race", "野兽");
	set("age", 3);
	set("long", "一只大金雕，正立在树枝上仰视长天。\n");
	set("attitude", "peaceful");

	set("limbs", ({ "头部", "身体", "翅膀", "爪子", "尾巴" }) );
	set("verbs", ({ "bite", "claw" }) );

	set("combat_exp", 30000);
	set_temp("apply/attack", 100);
	set_temp("apply/defense", 150);
	set_temp("apply/armor", 50);

	setup();
}
