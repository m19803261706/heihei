inherit NPC;

void create()
{
	set_name("客人", ({ "du ke", "du", "ke" }) );
	set("gender", "男性" );
	set("age", 40);
	set("long",
	      "一个正兴高采烈的客人。\n");
	set("shen_type", 1);
	set("combat_exp", 10000);
	set("str", 17);
	set("dex", 20);
	set("con", 17);
	set("int", 22);
	set("attitude", "peaceful");
	set_skill("dodge",20);
	set_skill("unarmed",20);
	set("chat_chance", 1);
	set("chat_msg", ({
		"客人骂道：他妈的，今天怎么那么不顺？\n",
	}) );       

	setup();
	carry_object("/d/beijing/npc/obj/cloth")->wear();
	add_money("coin", 30);
}

