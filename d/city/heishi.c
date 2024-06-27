// by luoyun_微笑
// heishi.c

inherit ROOM;

void create()
{
	set("short", "黑市");
	set("long", "这里是黑市，物品交易的场所。");
	set("exits", ([
		"northwest":__DIR__"guangchang",
	]));
	set("objects", ([
		__DIR__"npc/shenyi" : 1,
	]));
	set("action_list", ([
		"寄售物品" : "jishou",
		"物品列表" : "jylist",
		"重选性格" : "xingge",
		"重新洗点" : "xidian",
	]));
	set("no_fight","1");
	set("no_steal", "1");
	set("no_sleep_room", "1");
	setup();
}

void init()
{
	add_action("do_stock", "jishou");
	add_action("do_buy", "jybuy");
	add_action("do_list", "jylist");
	add_action("do_cha", "jychakan");
	add_action("do_unstock", "quhui");
	add_action("do_xingge","xingge");
	add_action("do_uses","xidian");
	add_action("do_effect", "effect");
}

int do_stock(string arg)
{
	tell_object(this_player(),SALE_D->do_stock(this_player(),arg)+"\n");
	return 1;
}

int do_buy(string arg)
{
	tell_object(this_player(),SALE_D->do_buy(this_player(),arg)+"\n");
	return 1;
}

int do_cha(string arg)
{
	tell_object(this_player(),SALE_D->do_cha(this_player(),arg)+"\n");
	return 1;
}

int do_list(string arg)
{
//	return notify_fail(OKSAY"集市暂时关闭！\n");
	if(!arg)
		arg = "全部 1";
	tell_object(this_player(),SALE_D->do_list(this_player(),arg)+"\n");
	return 1;
}

int do_unstock(string arg)
{
	tell_object(this_player(),SALE_D->do_unstock(this_player(),arg)+"\n");
	return 1;
}



int do_xingge(string arg)
{
object me = this_player();
tell_object(me,ZJOBLONG"请选择性格，第一次免费，之后每次扣费200元宝：\n"
		ZJOBACTS2+ZJMENUF(2,2,6,30)+
        "狡黠多变:effect 狡黠多变"ZJSEP
		"光明磊落:effect 光明磊落"ZJSEP
		"阴险奸诈:effect 阴险奸诈"ZJSEP
		"心狠手辣:effect 心狠手辣\n");
	return 1;
}


int do_effect(string arg)
{
	object me = this_player();
	if (me->query("xixingge")&&me->query("yuanbao") < 200)
	{
	tell_object(me,HIR"你的元宝数量不够！！"NOR"\n");		
		return 1;
	}
	if (me->query("character")==arg)
		{
	tell_object(me,HIR"请选择与你现在性格不一样的！"NOR"\n");		
		return 1;
	}
	if (arg=="狡黠多变") 
	 me->set("character", "狡黠多变");
	else
	 if (arg=="光明磊落") 
	   me->set("character", "光明磊落");

	else 
	if (arg=="心狠手辣") 
	 me->set("character", "心狠手辣");

	else 
	if (arg=="阴险奸诈") 
	me->set("character", "阴险奸诈");
		else 	
		{
	tell_object(me,HIR"\n敬请期待新性格！"NOR"\n");		
	return 1;
		}
	  tell_object(me,"性格转换成功!\n");
	  if (me->query("xixingge"))
	  {	  me->add("yuanbao",-200);
    tell_object(me,"200元宝已扣除!\n");
	  }
	  me->set("xixingge",1);
    return 1;
}

varargs int do_uses(string arg)
{
	mapping shuxing=([]), my;
	string *sname, str, line;
	int i;
	int max_sx, max_sx2;
	int tmpstr, tmpint, tmpcon, tmpdex;
	object me = this_player();
		
	if (!me->query("xidian")) {
		tell_object(me, "你当前可以免费试用一次。\n");
	}
	if (me->query("xidian") && me->query("yuanbao") < 200)
	{
		return notify_fail("你的元宝不够。\n");
	}
	if(!arg) {
		str = ZJOBLONG+ "你真的想重新分配先天属性吗？请慎重选择，一旦洗点造成严重后果概不负责，第一次免费,后续收费200元宝！\n";
		str += ZJOBACTS2+ZJMENUF(3,3,9,30);
		
		str += sprintf("确定:xidian -yes" + ZJSEP);
		str += sprintf("取消:look");
		tell_object(me, str + "\n");
	 return 1;
	} else if(arg == "-yes") {
		max_sx = (me->query("con") + me->query("dex")+me->query("int")+me->query("str"))
					-(me->query("gift/shenliwan") + me->query("gift/xiandan")+me->query("gift/unknowdan")+me->query("gift/lighting") +me->query("gift/xisuidan"))
					-(me->query("level")/10-me->query("tianfu_point"));
		
		write(INPUTTXT(HIR"注：值必须在13-30之间"ZJBR"总和不能超过你现有的先天"+max_sx+"点。"
											+NOR+ZJBR+HIW+"(臂力 悟性 根骨 身法)"
											+NOR+ZJBR+HIY+"(例：20 20 20 20，中间以空格隔开)"+NOR+
												ZJBR+"请输入四项先天点数：","xidian $txt#")+"\n");
	} else if(sscanf(arg, "-yes %d %d %d %d", tmpstr, tmpint, tmpcon, tmpdex) == 4) {
		if (tmpstr < 13 || tmpstr >30
			|| tmpint < 13 || tmpint >30
			|| tmpcon < 13 || tmpcon >30
			|| tmpdex < 13 || tmpdex >30) {
				write(HIR"你有一项输入不在(13-30)范围之内。"NOR"\n");
				return 1;
			}
		my = me->query_entire_dbase();
		max_sx = (my["con"] + my["dex"]+my["int"]+my["str"])
					-(me->query("gift/shenliwan") + me->query("gift/xiandan")+me->query("gift/unknowdan")+me->query("gift/lighting") +me->query("gift/xisuidan"))
					-(my["level"]/10-my["tianfu_point"]);
			
		if (tmpstr+ tmpint+ tmpcon+ tmpdex != max_sx) {
			write(HIR"你想分配的先天点数不等于目前的总先天属性。"NOR"\n");
			return 1;
		}
		
		line = sprintf("str(%d)int(%d)con(%d)dex(%d)", tmpstr, tmpint, tmpcon, tmpdex);
		
		tmpstr += me->query("gift/shenliwan");
		tmpint += me->query("gift/xiandan");
		tmpcon += me->query("gift/xisuidan")+me->query("gift/lighting");
		tmpdex += me->query("gift/unknowdan");
		max_sx2 = tmpstr+ tmpint+ tmpcon+ tmpdex;
		
		my["str"]= tmpstr;
		my["int"]= tmpint;
		my["con"]= tmpcon;
		my["dex"]= tmpdex;
		my["tianfu_point"] = my["level"] /10;
		
		CHANNEL_D->do_channel(present("shenyi",this_object()), "chat", "今日，"+me->name()+"在我处重塑了身体！");
		message_vision(HIY"$N在黑市重塑了身体！"NOR"\n", me);
		tell_object(me, HIY"身体重塑成功，请再操作升级一次天赋！"NOR"\n");
		
		//检查分配先天后的技能是否符合要求，不符合的删除
		UPDATE_D->check_skill(me);
		me->save();
	//	log_file("/cmds/xidian", sprintf("%s  洗点=%s  总计=str(%d)int(%d)con(%d)dex(%d) 总共(%d/%d点) 洗点时间：%s\n", 
	//										me->name()+"("+my["id"]+")", line, tmpstr, tmpint, tmpcon, tmpdex, max_sx, max_sx2, CHINESE_D->chinese_date(time(), 2)));
	if (me->query("xidian"))
		me->add("yuanbao",-200);
		
	 me->set("xidian", 1);
	} else if(sscanf(arg, "%d %d %d %d", tmpstr, tmpint, tmpcon, tmpdex) == 4) {
		
		str = ZJOBLONG+ HIC"你的设置："HIG"臂力("+tmpstr+") 悟性("+tmpint+") 根骨("+tmpcon+") 身法("+tmpdex+")"NOR
				+ZJBR"真的想重新分配先天属性吗？"ZJBR
										+"请慎重选择！最后一次提醒！一旦洗点，将不可恢复，造成严重后果概不负责！"NOR"\n";
		str += ZJOBACTS2+ZJMENUF(3,3,9,30);
		
		str += sprintf("确定:xidian -yes " +tmpstr+" "+ tmpint+" "+ tmpcon+" "+ tmpdex+ ZJSEP);
		str += sprintf("取消:look");
		tell_object(me, str + "\n");
	} else 
		me->force_me("xidian");
	return 1;
}