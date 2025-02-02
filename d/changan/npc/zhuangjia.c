//zhuangjia.c



inherit NPC;

object room = 0;

void create()
{
	set_name( "陪玩", ({ "zhuang jia", "zhuang" }) );
	set("long", "这是长安娱乐场的陪玩，骰子上的功夫出神入化，如果你输了就得喝酒。\n");
	set("attitude", "friendly");
	set("title", HIR "骰子圣手" NOR);
	set("force_factor", 30);
	set("max_kee", 3000);
	set("max_sen", 3000);
	set("eff_gin", 3000);
	set("eff_kee", 3000);
	set("eff_sen", 3000);
	set("kee", 3000);
	set("sen", 3000);
	set("max_force", 3000);
	set("force", 3000);
	set("max_mana", 3000);
	set("mana", 3000);
	set("age", 47);
	set_temp("apply/damage",600);
	set("gender", "男性" );
	set("str", 40);
	set("cor", 35);
	set("cps", 30);
	set("per",10);
	set("max_force",3000);
	set("force_factor",40);
	set_skill("parry",170);
	set_skill("unarmed",170);
	set_skill("force",170);
	set_skill("dodge",170);
	set("combat_exp", 300000);

	setup();
	carry_object(__DIR__"obj/choupao")->wear();
}

void greeting(object ob)
{
	if (! ob || environment(ob) != environment())
		return;
	switch(random(3))
	{
	case 0:
		say("陪玩笑咪咪地说道：这位" + RANK_D->query_respect(ob) +
		    "，过来喝两杯？\n");
		break;
	case 1:
		say("陪玩晃了晃手中的骰子，叫道：这位" +
		    RANK_D->query_respect(ob) +
		    "，别犹豫了。想喝酒来找我！\n");
		break;
	case 2:
		say("陪玩说道：这位" + RANK_D->query_respect(ob) +
		    "，来！来！来！ 先喝一杯！\n");
		break;
	}
}
