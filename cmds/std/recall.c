
inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
	string file;
	string str;
	object ob;
 
	if (! environment(me)) 
		return 0; 

	if (! arg )
		return help(me);
			       
	if (me->is_busy())
		return notify_fail("你正忙著呢。\n");

	if (me->is_ghost()) 
		return notify_fail("等你还了阳再说吧。\n"); 
		
	if (me->is_in_prison())   
		return notify_fail("你正在做牢呢。\n");

	if (! me->query("born"))
		return notify_fail("你还没有出生呢！\n");

	if (me->query("doing"))
		return notify_fail("你还想干什么？！\n");
		
	if (environment(me)->query("no_magic"))
		return notify_fail("你发现这里有点古怪！\n");		
	
	if (arg == "back")
	{			
		if (me->query_temp("jun_quest/party"))
			return notify_fail("你还想在战争中使用？！\n");

		if (present("biao huo", me))
			return notify_fail("你身上带著镖银，不能施展！\n");
		
		if (present("letter", me) || present("receipt", me)) 
			return notify_fail("你身上带著密函，不能施展。\n");
		
		file = "/d/city/kedian";
		
		if (base_name(environment(me)) == file)
			return notify_fail("你已经在扬州客店了。\n");
			
		if (! get_object(file))
			return notify_fail("你感觉到似乎有什么不对劲！\n");

		message("vision", me->name() + "举起右手在面前极速画了一个圆，竟划破了面前的"
			"空间，只见圆内的空间真空将" + me->name() + "给吸了进去。\n",
			environment(me), ({me}));
		
		tell_object(me, "你从客店的某个角落空间裂缝中钻出。\n");

		me->move(file);
		message("vision", me->name() + "从客店的某个角落空间裂缝中钻出。\n",
			environment(me), ({me}));

		return 1;
	}

     str = me->query_temp("pet_id");      
		     
     if (! stringp(file = me->query("can_whistle/" + str)))
		return notify_fail("你并没有这个魔幻兽。\n");

	if (file_size(file + ".c") < 0)
		return notify_fail("你并没有这个魔幻兽!\n");
				
	if (arg == "change" && ! me->query("beastdied"))
	{
		if (! objectp(ob = present(str, environment(me))))
			return notify_fail("你得首先把你的魔幻兽召唤到身旁来。\n");
		
		if (ob->query("owner") != me->query("id"))
			return notify_fail("你的魔幻兽并不在你的身旁。\n");
				
		if (! living(ob)) return notify_fail("你的魔幻兽目前处于昏迷状态呢。\n");

		message_vision("$N举起右手在面前极速画了一个圆，大喊"
			"一声，“$n，铠化！”\n", me, ob);
		
		if (! ob->receive_change(me))
		{
			message_vision("然而什么也没有发生 :)\n", me);			
			return 1;
		} 
	} else
	if (arg == "recover" && ! me->query("beastdied"))
	{
		 if (! objectp(ob = present(str, me)))
			return notify_fail("你身上并没有任何铠化的魔幻兽。\n");
				       
		if (ob != me->query_temp("is_changing"))
			return notify_fail("你身上并没有任何铠化的魔幻兽。\n");  

		if (ob->query("owner") != me->query("id"))
			return notify_fail("你身上并没有任何铠化的魔幻兽。\n");
					
		if (! living(ob)) return notify_fail("你的魔幻兽目前处于昏迷状态呢。\n");

		message_vision("$N集中心智，在心中慢慢的呼道：“$n，解除铠化。”\n", me, ob);
		
		if (! ob->receive_recover(me))
		{
			message_vision("然而什么也没有发生 :)\n", me);			
			return 1;
		}		  
	}
	/* 
	else
	if (arg == "reborn" && me->query("beastdied"))
	{
		if (me->query_skill("huisheng-jue", 1) < 100)
			return notify_fail("你的回生决功力不够，无法让魔幻兽重生。\n"); 

		if (me->query("neili") < me->query("max_neili") * 9 / 10)
			return notify_fail("你现在内力并不充沛，怎敢贸然运用？\n");

		if (me->query("jingli") < me->query("max_jingli") * 9 / 10)
			return notify_fail("你现在精力不济，怎敢贸然运用？\n");

		if (me->query_skill("force") < 200)
			return notify_fail("你的内功根基不够扎实，不能贸然运用。\n");

		if (me->query("max_neili") < 3000)
			return notify_fail("你尝试运了一下内力，无法顺"
				   "利运足一个周天，难以施展你的能力。\n");

		if (me->query("max_jingli") < 1000)
			return notify_fail("你试图凝神运用精力，但是感觉尚有欠缺。\n");				
		
		if (me->query("experience") < me->query("learned_experience") + 1000) 
			return notify_fail("你现在积累的实战体会还太少，无法贸然运用。\n");

		message_sort(HIR "$N集中精神，手指大地，同时运转丹田内力，经"
			"由奇经八脉源源由体内流出，注入大地。"NOR"\n", me); 

		me->start_busy(1);
	
		me->add("max_neili", -500);
		me->set("neili", (int)me->query("max_neili"));
		me->add("max_jingli", -300);
		me->set("jingli", (int)me->query("max_jingli"));	
		me->add("learned_experience", 1000);
		me->delete("beastdied");
		tell_object(me, HIW "你凝神片刻，觉得魔幻兽"
			HIW "似乎复活过来，就在不远处，不禁微微一笑。"NOR"\n");									     
		
	} 
	*/
	else return help(me);
	return 1;
}

int help(object me)
{
 write(@HELP
指令格式 : recall change|recover <id>
让魔幻兽铠化或解除铠化，让魔幻兽复活的指令为< recall reborn >
回到扬州客店的指令为 < recall back >。
HELP
    );
    return 1;
}
