// maque.c

inherit NPC;

void create()
{
	set_name("麻雀", ({ "maque"}));
	set("race", "野兽");
	set("age", 3);
	set("long", "一只叽叽喳喳，飞来飞去的小麻雀。\n");
	set("attitude", "peaceful");

	set("limbs", ({ "头部", "身体", "翅膀", "爪子", "尾巴" }) );
	set("verbs", ({ "bite", "claw" }) );

	set("combat_exp", 300);
	set_temp("apply/attack", 3);
	set_temp("apply/defense", 5);
	set_temp("apply/armor", 1);

	set("chat_chance", 10);
	set("chat_msg", ({
	"麻雀在你头上打个转，又飞回树上。\n",
	"麻雀唧唧喳喳叫了几声。\n",
	}) );

	setup();
}
