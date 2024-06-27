// Room: /city/wumiao.c
// YZC 1995/12/04 

#include <room.h>

inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
	set("short", "武庙");
	set("long", @LONG
这里是岳王庙的正殿，内有岳飞像，像上方悬挂岳飞手书“还我河山”的
横匾。殿两侧壁上嵌着“尽忠报国”四个大字。武人到此，都放下武器，毕恭
毕敬地上香礼拜。旁边似乎有一道侧门。
LONG );
	set("no_fight", "1");
	set("no_steal", "1");
	set("no_learn", "1");
	set("no_study", "1");
	set("no_learn", "1");
	set("no_dazuo", "1");
	set("no_sleep_room", "1");

	set("valid_startroom","1");
	set("objects", ([
		__DIR__"obj/box" : 1,
	]));

	set("action_list", ([
		"每日签到" : "day_sign",
		"签到说明" : "help vip/vipbox",
		//"推广礼盒" : "getgift",
	]));

	set("exits", ([
		"east" : __DIR__"beidajie2",
		"north"   : __DIR__"wumiao2",
		"northwest": "/d/wizard/guest_room",
	]));
	create_door("northwest", "竹门", "southeast", DOOR_CLOSED);
	setup();
}

void init()
{
	add_action("do_sign","day_sign");
	//add_action("get_gift","getgift");
}

int valid_leave(object me, string dir)
{
	if (dir == "northwest" && ! userp(me) && ! me->is_chatter())
		return 0;
	return ::valid_leave(me, dir);
}

int get_gift(string arg)
{
 
	object gift,me;
	
	me = this_player();

	if(!arg)
	{
		write(INPUTTXT("请输入推广码领取礼物：","getgift $txt#")+"\n");
		return 1;
	}
	if(!VIP_D->query_qian(arg))
		return notify_fail("没有这个推广码，请检查确认！\n");
	if(me->query("zjvip/tgm"))
		return notify_fail("你已经领取过推广礼物了，不能重复！\n");
	VIP_D->set_qian(arg+"/"+me->query("id"),1);
	me->set("zjvip/tgm",arg);
	gift = new("/clone/gift/tg_gift");
	tell_object(me,"恭喜你获得了"+gift->short()+"，赶紧打开来看看有什么惊喜吧！\n");
	gift->set("bind",me->query("id"));
	log_ufile(me,"tg_gift","输入"+arg+"领取推广礼盒。\n");
	gift->move(me);

	return 1;
}

int do_sign(string arg)
{
	object ob,me;
 string hol;
	int vlv,last,times,pot;
 

	me = this_player();

	last = me->query("last_day_sign");
	times = me->query("day_sign_times");
	if(time()/86400 == last/86400)
		return notify_fail("你今天已签过到了，你目前已连续签到【"+times+"】天。\n");

	if(time()/86400 - last/86400 > 1)
	{
		tell_object(me,"你昨天没有签到记录，连续记录从今天开始。\n");
		times = 0;
	}

	me->set("last_day_sign",time());
	times += 1;
	me->set("day_sign_times",times);
	vlv = me->query("zjvip/level");
	pot = vlv*100 + 500 + times*20;
	if(me->query("zjvip/times")>0)
		pot *= 2;
	me->add("potential",pot);
	me->add("combat_exp",pot*2);
	tell_object(me,"你连续签到"+times+"次，获得"+pot*2+"经验和"+pot+"潜能。\n");
	me->add("zjvip/sign_exp",times);
	tell_object(me,"你连续签到"+times+"次，获得"+times+"点vip经验。\n");
	log_ufile(me,"sign","连续第"+times+"次签到获得"+pot*2+"经验和"+pot+"潜能。\n");

	if(vlv)
	{
		ob = new("/clone/gift/vip_box"+vlv);
		ob->set_amount(1);
		tell_object(me,"你获得了"+ob->short()+"。\n");
		log_ufile(me,"sign","签到获得"+ob->short()+"\n");
		ob->move(me);
	}
	if(times>=15)
	{
		tell_object(me,"你上一轮签到圆满达到最高目标，今天开始开始将重新计算。\n");
		ob = new("/clone/gift/sign_box");
		tell_object(me,"你获得了一个"+ob->short()+"。\n");
		ob->move(me);
		me->set("day_sign_times",0);
		times = 0;
	}
	GIFT_D->check_gift(me);
	if(hol = "/adm/daemons/payd"->is_hol())
	{
		tell_object(me,HIG"今天是"HIY+hol+HIG"，祝您节日愉快"NOR"。\n");
	}
	else if(localtime(time())[6]==0 || localtime(time())[6]==6)
	{
		tell_object(me,HIG"今天是"HIY"周末"HIG"，祝您周末愉快！"NOR"。\n");
	}
	return 1;
}
