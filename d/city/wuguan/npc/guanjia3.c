//guanjia3.c 马房管事
// Modify By River@SJ

inherit NPC;


void create()
{
       set_name("马房管事", ({ "mafang guanshi", "guanshi" }) );
       set("gender", "男性" );
       set("age", 30);
       set("long","他是襄阳武馆的一个管家，专管马房里的大小杂事！\n");
       set("combat_exp", 2500);
       set("attitude", "friendly");
       set("inquiry", ([
             "打扫马房" : "你就在这老老实实给我打扫马房，没有我的满意，你别想回去覆命！",
             "打扫" : "你就在这老老实实给我打扫马房，没有我的满意，你别想回去覆命！",
       ]) );

       setup();
}

void init()
{
       object ob;
       ::init();
       if( interactive(ob = this_player()) && !is_fighting() ) {
              remove_call_out("greeting");
              call_out("greeting", 1, ob);
       }
}

void greeting(object ob)
{
       if( !ob || environment(ob) != environment() ) return;
       if(ob->query_temp("job_name") != "打扫马房") return; 
       if (!( present("sao zhou", ob))){
           command("hmm "+ob->query("id"));
           command("say 你还没领工具吧，去物品房找六师兄要。");
           return;
       }
       if(!(ob->query_temp("job_name")!="打扫马房")){
           command("nod "+ob->query("id"));
           command("say " + RANK_D->query_respect(ob)+"，你就在这打扫马房吧。"NOR);
       }
}
