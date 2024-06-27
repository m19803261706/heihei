

#include <login.h>
#include <command.h>

inherit ROOM;

int is_chat_room() { return 1; }

int do_wash(string arg);
int do_washto(string arg);
int do_born(string arg);
int do_pianshu(string arg);

mapping born = ([
	"关外人氏" : "/d/guanwai/kedian",
	"燕赵人氏" : "/d/beijing/kedian",
	"齐鲁人氏" : "/d/taishan/kedian",
	"秦晋人氏" : "/d/changan/kezhan",
	"中原人氏" : "/d/shaolin/kedian1",
	"西域人氏" : "/d/xingxiu/kedian",
	"荆州人氏" : "/d/xiangyang/kedian",
	"扬州人氏" : "/d/city/kedian",
	"苏州人氏" : "/d/suzhou/kedian",
	"杭州人氏" : "/d/hangzhou/kedian",
	"福建人氏" : "/d/fuzhou/kedian",
	"巴蜀人氏" : "/d/city3/kedian",
	"云南人氏" : "/d/dali/kedian",
	"两广人氏" : "/d/foshan/beidimiao",
	"欧阳世家" : ([ "born"      : "西域人氏",
			"surname"   : "欧阳",
			"startroom" : "/d/baituo/dating",
		     ]),
	"关外胡家" : ([ "born"      : "关外人氏",
			"surname"   : "胡",
			"startroom" : "/d/guanwai/xiaowu",
		     ]),
	"段氏皇族" : ([ "born"      : "大理人氏",
			"surname"   : "段",
			"startroom" : "/d/dali/wangfugate",
		     ]),
	"慕容世家" : ([ "born"      : "江南人氏",
			"surname"   : "慕容",
			"startroom" : "/d/yanziwu/cuixia",
		     ]),
]);

void create()
{
	int i, k;
	string desc;
	string *position;

	set("short", HIR "阎罗殿" NOR);
	set("long", @LONG
这里阴深恐怖，让人感觉到一阵阵的寒意，两旁列着牛头马面，冥
府狱卒，各个威严肃穆。十殿阎罗，尽皆在此，地藏王坐在大堂之上，
不怒自威。
    大殿角落有一个石头砌成的池子，其中水清澈却不见底，不知道它
究竟有多深。
    旁边有几个牌子，你也许应该仔细看看。
LONG );
	set("no_fight", 1);
	set("item_desc", ([
		"偏属" : "请选择你的属性偏属，然后进行洗点！\n"ZJOBACTS"猛士型：高臂力偏属。:pianshu msx$zj#智慧型：高悟性偏属。:pianshu zhx$zj#耐力型：高根骨偏属。:pianshu nlx$zj#敏捷型：高身法偏属。:pianshu mjx$zj#均衡型：各项平均20属性。:pianshu jhx\n",
		"洗点" : "投胎之前可以先洗一下属性点，直到自己满意：\n"ZJOBACTS"偏属随机洗点:wash$zj#指定分配洗点:washto\n",
		"转生" : "投胎乃人生大事，切记不可草率！"ZJBR"请选择你的转生地点：\n"ZJOBACTS,
	]));

	set("objects", ([
		__DIR__"npc/dizangwang" : 1,
	]));

	set("no_say", "阎罗殿内阴森恐怖，你哪里敢乱说话？\n");

	desc = query("item_desc/转生");
	position = keys(born);

	for (i = 0, k = 1; i < sizeof(position); i++)
	{
		if (! stringp(born[position[i]]))
			continue;
		desc += sprintf("%2d. " HIW "%s" NOR ":born %s$zj#", k++, position[i], position[i]);
	}
	for (i = 0; i < sizeof(position); i++)
	{
		if (! mapp(born[position[i]]))
			continue;
		desc += sprintf("%2d. " HIC "%s" NOR ":born %s$zj#", k++, position[i], position[i]);
	}
	set("item_desc/转生", desc+"\n");

	setup();
}

void init()
{
	add_action("do_wash", "wash");
	add_action("do_washto", "washto");
	add_action("do_born", "born");
	add_action("do_pianshu", "pianshu");
}

int do_pianshu(string arg)
{
	object me = this_player();

	if (arg=="msx")
	{
		me->set("type","猛士型");
		me->delete_temp("washed");
  		write(ZJOBLONG"你选择了猛士型角色属性，属性设定成功！"ZJBR"请点击洗点完成属性选择。\n",me);
		return 1;
	}
	else if (arg=="zhx")
	{
		me->set("type","智慧型");
		me->delete_temp("washed");
  		write(ZJOBLONG"你选择了智慧型角色属性，属性设定成功！"ZJBR"请点击洗点完成最终属性选择。\n",me);
		return 1;
	}
	else if (arg=="nlx")
	{
		me->set("type","耐力型");
		me->delete_temp("washed");
  		write(ZJOBLONG"你选择了耐力型角色属性，属性设定成功！"ZJBR"请点击洗点完成最终属性选择。\n",me);
		return 1;
	}
	else if (arg=="mjx")
	{
		me->set("type","敏捷型");
		me->delete_temp("washed");
  		write(ZJOBLONG"你选择了敏捷型角色属性，属性设定成功！"ZJBR"请点击洗点完成最终属性选择。\n",me);
		return 1;
	}
	else if (arg=="jhx")
	{
		me->set("type","均衡型");
		me->delete_temp("washed");
  		write(ZJOBLONG"你选择了均衡型角色属性，属性设定成功！"ZJBR"请点击洗点完成最终属性选择。\n",me);
		return 1;
	}
	else
	{
  		write(ZJOBLONG"选择错误，请重新选择！\n",me);
		return 1;
	}
}

int do_wash(string arg)
{
	int i;
	int points;
	int tmpstr, tmpint, tmpcon, tmpdex;
	object me;
	mapping my;

	if (! objectp(me = this_player()) ||
	    ! userp(me))
		return 1;

	if(!me->query("type"))
	{
  		write(ZJOBLONG"你还没有设定属性偏属，请先设定偏属！\n",me);
  		return 1;
	}
	write(HIC "你跳入忘忧池，顿时被一股激流卷了进去。"NOR"\n", me);

	tmpstr = tmpint = tmpcon = tmpdex = 13;

	switch (me->query("type"))
	{
	case "猛士型":
		tmpstr = 30;
		tmpcon = 24;
		break;

	case "智慧型":
		tmpint = 30;
		tmpcon = 24;
		break;

	case "耐力型":
		tmpcon = 30;
		tmpint = 24;
		break;

	case "敏捷型":
		tmpdex = 30;
		tmpint = 24;
		break;

	case "均衡型":
		tmpstr = 20;
		tmpcon = 20;
		tmpint = 20;
		tmpdex = 20;
		break;

	default:
		break;
	}

	points = 80 - (tmpstr + tmpint + tmpcon + tmpdex);
	for (i = 0; i < points; i++) {
		switch (random(4)) {
		case 0: if (tmpstr < 30) tmpstr++; else i--; break;
		case 1: if (tmpint < 30) tmpint++; else i--; break;
		case 2: if (tmpcon < 30) tmpcon++; else i--; break;
		case 3: if (tmpdex < 30) tmpdex++; else i--; break;
		}
	}

	my = me->query_entire_dbase();

	my["str"] = tmpstr;
	my["int"] = tmpint;
	my["con"] = tmpcon;
	my["dex"] = tmpdex;
	my["kar"] = 10 + random(21);
	my["per"] = 10 + random(21);

	write(HIC "“啪”的一声，你被湿漉漉的抛了出来。"NOR"\n", me);
	write(sprintf(HIY "\n你这次获得的四项先天天赋分别是：\n"
			  "膂力：【 " HIG "%d" HIY " 】 "
			  "悟性：【 " HIG "%d" HIY " 】\n"
			  "根骨：【 " HIG "%d" HIY " 】 "
			  "身法：【 " HIG "%d" HIY " 】\n"
			  "如果你满意，就去转生吧！"NOR"\n",
		      tmpstr, tmpint, tmpcon, tmpdex));
	me->set_temp("washed", 1);

	return 1;
}

int do_washto(string arg)
{
	int i,n;
	int points;
	int tmpstr, tmpint, tmpcon, tmpdex;
	object me;
	mapping my;

	if (! objectp(me = this_player()) || ! userp(me))
		return 1;
	if (!arg||!stringp(arg))
	{
		tell_object(me,INPUTTXT("请输入你想分配的方案：$br#"
						"按照臂力、悟性、根骨、身法次序输入4个用"
						"空格分开的数，注意每个数不能低于13或大于30，4个数之和必须为80。","washto $txt#")+"\n");
		return 1;
	}

	if(sscanf(arg, "%d %d %d %d",tmpstr,tmpint,tmpcon,tmpdex)  != 4)
	{
		tell_object(me,INPUTTXT("输入格式不对，请重新输入你想分配的方案：$br#"
						"按照臂力、悟性、根骨、身法次序输入4个用"
						"空格分开的数，注意每个数不能低于13或大于30，4个数之和必须为80。","washto $txt#")+"\n");
		return 1;
	}

	if(tmpstr<13||tmpint<13||tmpcon<13||tmpdex<13||tmpstr>30||tmpint>30||tmpcon>30||tmpdex>30||(tmpstr+tmpint+tmpcon+tmpdex)!=80)
	{
		tell_object(me,INPUTTXT("输入格式不对，请重新输入你想分配的方案：$br#"
						"按照臂力、悟性、根骨、身法次序输入4个用"
						"空格分开的数，注意每个数不能低于13或大于30，4个数之和必须为80。","washto $txt#")+"\n");
		return 1;
	}

	write(HIC "你跳入忘忧池，顿时被一股激流卷了进去。"NOR"\n", me);

	my = me->query_entire_dbase();

	my["str"] = tmpstr;
	my["int"] = tmpint;
	my["con"] = tmpcon;
	my["dex"] = tmpdex;
	my["kar"] = 10 + random(21);
	my["per"] = 10 + random(21);

	write(HIC "“啪”的一声，你被湿漉漉的抛了出来。"NOR"\n", me);
	write(sprintf(HIY "\n你这次获得的四项先天天赋分别是：\n"
			  "膂力：【 " HIG "%d" HIY " 】 "
			  "悟性：【 " HIG "%d" HIY " 】\n"
			  "根骨：【 " HIG "%d" HIY " 】 "
			  "身法：【 " HIG "%d" HIY " 】\n"
			  "如果你满意，就去转生吧！"NOR"\n",
		      tmpstr, tmpint, tmpcon, tmpdex));
	me->set_temp("washed", 1);

	return 1;
}

int do_born(string arg)
{
	object me;
	object obj;
	object item;
	mixed dest;
	string new_name;
	string msg;

	if (! objectp(me = this_player()) ||
	    ! userp(me))
		return 1;

	if (! me->query_temp("washed"))
		return notify_fail(ZJOBLONG"你先选择好天赋并在忘忧池中洗好点再投胎也不迟啊！\n");

	if (arg && arg[0] < 160)
		return notify_fail("你必须输入中文地名，比如born 扬州人氏，或者是born 欧阳世家以避免投错胎。\n");

	new_name = 0;
	if (arg) sscanf(arg, "%s %s", arg, new_name);

	if (! arg || (! stringp(dest = born[arg]) && ! mapp(dest)))
	{
		message_vision("牛头恶狠狠的对$N说：你要干什么！投胎去哪里？\n", me);
		return 1;
	}

	if (mapp(dest) && stringp(dest["notice"]))
		return notify_fail(dest["notice"]);

	if (stringp(dest))
	{
		if (! objectp(obj = find_object(dest)))
			obj = load_object(dest);
		me->set("startroom", dest);
		me->set("born", arg);
		me->set("born_family", "没有");
	} else
	{
		if (! objectp(obj = find_object(dest["startroom"])))
			obj = load_object(dest["startroom"]);

		if (new_name)
		{
			if (! sscanf(new_name, dest["surname"] + "%*s"))
				new_name = dest["surname"] + new_name;

			if (strlen(new_name) > 8)
				return notify_fail("你的名字太长了。\n");

			if (strlen(new_name) < 4)
				return notify_fail("你的名字太短了。\n");

			if (! is_chinese(new_name))
				return notify_fail("请你用中文起名字。\n");
		}

		if (me->query("surname") != dest["surname"])
		{
			// 名字需要变化
			NAME_D->remove_name(me->name(1), me->query("id"));
			if (! new_name) new_name = dest["surname"] + me->query("purename");
			if (stringp(msg = NAME_D->invalid_new_name(new_name)))
			{
				write(msg);
				write("你可以考虑在投入世家的时候重新选择名字：born <世家> <名字>\n");
				return 1;
			}
			me->set("surname", dest["surname"]);
			me->set("purename", new_name[strlen(dest["surname"])..<1]);
			me->set_name();
			NAME_D->map_name(me->name(1), me->query("id"));
		}

		me->set("startroom", dest["startroom"]);
		me->set("born", dest["born"]);
		me->set("born_family", arg);

		if (mapp(dest["family"]))
		{
			me->set("family", dest["family"]);
			me->assign_apprentice(dest["family"]["title"], 0);
		}
	}
	if (! objectp(obj))
	{
		message_vision("牛头一呆，搔搔头说：怎么好像有问题...\n", me);
		return 1;
	}

	message_vision("牛头飞起一脚，将$N踢了出去。\n", me);

	// 选择特殊技能
	UPDATE_D->born_player(me);

	me->move(obj);
	me->set("mud_age", 0);
	me->set("age", 14);
	me->save();
	message_vision("$N揉揉眼睛，迷惘的望着这个陌生的世界。\n", me);

	return 1;
}
