// fly.c



inherit F_CLEAN_UP;

int help(object me);

mapping city_name = ([
	"1":"武林城",
]);

mapping places = ([
	"yz" : "/d/city/guangchang",
	"yangzhou" : "/d/city/guangchang",

	"shenlong"       : "/d/shenlong/kongdi",
	"sld"       : "/d/shenlong/kongdi",

	"hujia"  : "/d/guanwai/baihe",
	"hj"  : "/d/guanwai/baihe",
	"gw"  : "/d/guanwai/jishi",
	"guanwai"  : "/d/guanwai/jishi",

	"bj"  : "/d/beijing/tiananmen",
	"beijing"  : "/d/beijing/tiananmen",

	"cd"  : "/d/city3/guangchang",
	"chengdu"  : "/d/city3/guangchang",

	"changan"  : "/d/changan/bridge2",
	"ca"  : "/d/changan/bridge2",

	"fz"   : "/d/fuzhou/dongjiekou",
	"fuzhou"   : "/d/fuzhou/dongjiekou",

	"foshan"   : "/d/foshan/street3",
	"fs"   : "/d/foshan/street3",

	"qz" : "/d/quanzhou/zhongxin",
	"quanzhou" : "/d/quanzhou/zhongxin",

	"jx"  : "/d/quanzhou/jiaxing",
	"jiaxing"  : "/d/quanzhou/jiaxing",

	"hz" : "/d/hangzhou/road10",
	"hangzhou" : "/d/hangzhou/road10",

	"sz"   : "/d/suzhou/canlangting",
	"suzhou"   : "/d/suzhou/canlangting",

	"hmy"  : "/d/heimuya/up1",
	"wugong"   : "/d/quanzhen/zhongxin",

	"ts"  : "/d/taishan/taishanjiao",
	"taishan"  : "/d/taishan/taishanjiao",

	"dl"     : "/d/dali/center",
	"dali"     : "/d/dali/center",

	"nanyang"  : "/d/shaolin/nanyang",
	"ny"  : "/d/shaolin/nanyang",

	"xy": "/d/xiangyang/guangchang",
	"xiangyang": "/d/xiangyang/guangchang",

	"yongdeng" : "/d/huanghe/yongdeng",
	"yd" : "/d/huanghe/yongdeng",

	"lingzhou" : "/d/lingzhou/center",
	"lz" : "/d/lingzhou/center",

	"henyang"  : "/d/henshan/hengyang",
	"hy"  : "/d/henshan/hengyang",

	"xx"  : "/d/xingxiu/xxh1",
	"xingxiu"  : "/d/xingxiu/xxh1",

	"bt"   : "/d/baituo/guangchang",       
	"baituo"   : "/d/baituo/guangchang",     

	"qzj" : "/d/quanzhen/damen",
	"quanzhen" : "/d/quanzhen/damen",

	"zhongnan" : "/d/quanzhen/shanjiao",
	"gm"     : "/d/gumu/mumen",
	"gumu"     : "/d/gumu/mumen",

	"mr"   : "/d/yanziwu/hupan",
	"murong"   : "/d/yanziwu/hupan",
	"yzw"  : "/d/yanziwu/bozhou",

	"lj"  : "/d/lingjiu/jian",
	"lingjiu"  : "/d/lingjiu/jian",

	"sl"  : "/d/shaolin/shanmen",
	"shaolin"  : "/d/shaolin/shanmen",

	"ruzhou"  : "/d/shaolin/ruzhou",
	"rz"  : "/d/shaolin/ruzhou",

	"wd"   : "/d/wudang/jiejianyan",
	"wudang"   : "/d/wudang/jiejianyan",

	"xyg"  : "/d/xiaoyao/xiaodao4",	
	"xiaoyao"  : "/d/xiaoyao/xiaodao4",	

	"hs"  : "/d/huashan/shaluo",
	"huashan"  : "/d/huashan/shaluo",
	"hsjz"  : "/d/huashan/pingdi",

	"xs"  : "/d/xuedao/nroad4",
	"xueshan"  : "/d/xuedao/nroad4",

	"xd"   : "/d/xuedao/wangyougu",
	"xuedao"   : "/d/xuedao/wangyougu",

	"kl"   : "/d/kunlun/klshanlu",
	"kunlun"   : "/d/kunlun/klshanlu",

	"em"     : "/d/emei/huayanding",
	"emei"     : "/d/emei/huayanding",
	"jinding"  : "/d/emei/jinding",

	"mj" : "/d/mingjiao/shanjiao",
	"mingjiao" : "/d/mingjiao/shanjiao",
	"nanhai"   : "/d/xiakedao/haibin",

	"guiyun"   : "/d/guiyun/taihu",

	"thd"  : "/d/taohua/tingzi",
	"taohua"  : "/d/taohua/tingzi",

	"moye"  : "/d/item/xiaowu",
]);

int main(object me, string arg)
{
	object flying, room;
	string msg,where,*citys,dir;
	int i;

	if (! arg) return help(me);  

	if (me->over_encumbranced()) 
		return notify_fail("你的负荷过重，动弹不得。\n"); 
	
	if (me->query_encumbrance() < 0) 
		return notify_fail("你的负荷出现故障，动弹不得。\n"); 

	if (me->query_temp("sleeped")) 
		return notify_fail("你现在正躺着呢。\n");

	if (me->is_in_prison())   
		return notify_fail("你正在做牢呢，你想干什么？！\n");
				
	if (me->is_fighting()) 
		return notify_fail("你现在正在战斗！\n");

	if (me->is_busy() || me->query("doing")) 
		return notify_fail("你的动作还没有完成，不能移动。\n");

	if (me->query_temp("is_flying")) 
		return notify_fail("你现在正在飞行中！\n");
		
	if (! environment(me)->query("outdoors")&& !wizardp(me) ) 
		return notify_fail("在房间里不能乱跑！\n");
		
	if (environment(me)->query("no_magic") || environment(me)->query("no_fly"))
		return notify_fail("你发现这里有点古怪，你的神雕好象不听你的指挥！\n");		

	if (arg == "home" && ! me->query("private_room/position")) 
		return notify_fail("你还没有住房呢！\n");

	if (arg == "home" && stringp(me->query("private_room/position")) && file_size(me->query("private_room/position") + ".c") > 0)
		room = get_object(me->query("private_room/position"));
	else if(arg == "hell")
	{
		citys = list_dirs("/data/hell/");
		if (sizeof(citys)<1) {
			return notify_fail("目前空中之城是空城！\n");
		}
		msg = ZJOBLONG"请选择城市：\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
		for(i=0;i<sizeof(citys);i++)
		{
			msg += city_name[citys[i]]+":fly hell "+citys[i];
			if(i<(sizeof(citys)-1)) msg += ZJSEP;
		}
		write(msg+"\n");
		return 1;
	}
	else if(sscanf(arg,"hell %s",dir)==1)
	{
		//if(!wizardp(me))
		//	return notify_fail("稍后开放。\n");
		if(file_size("/data/hell/"+dir)!=-2)
			return notify_fail("没有这个城市。\n");
		if(file_size("/data/hell/"+dir+"/guangchang.c")<0)
			return notify_fail("城市入口错误，请联系管理员。\n");
		room = get_object("/data/hell/"+dir+"/guangchang");
	}
	else
	{
		if (member_array(arg, keys(places)) == -1) 
			return notify_fail("这个地方无法驾驭神雕飞去。\n");
		room = get_object(places[arg]);
	}
	if (! room) return notify_fail("你感觉到似乎那个地方有点不对劲。\n");

	where = room->query("short");
	message_vision(HIM"$N猛吹一声口哨，从空中招来一只"HIW"白雕"NOR+HIM"。"HIM"\n$N跃上白雕，直上云霄向"+where+""HIM"方向飞去。"NOR"\n"NOR"\n", me);
	me->move("/d/city/kongzhong");

	me->set_temp("is_flying",1);

	if (me->query("zjvip/times") >1) call_out("fly_fin",1,where,flying,me,room);
        else call_out("fly_fin",3,where,flying,me,room);
	return 1;
}
void fly_fin(string where,object flying,object me,object room)
{
	if (!me)
		return;
	me->move(room);

	tell_object(me, HIC"你一路驾御白雕飞行，终于赶到了" + where + ""HIC"。"NOR"\n"NOR"\n");
        tell_room(environment(me),HIC""+me->name()+"乘坐"HIW"白雕"HIC"从远处飞驰而来，徐徐落下。"NOR"\n",me);
	me->delete_temp("is_flying");

}
int help(object me)
{
	write(@HELP
指令格式 : fly <地点>
乘坐白雕瞬间飞到某个地点。目前可以去的地方有：
----------------------------------------------------------------------
yangzhou : 扬  州	beijing : 北  京	chengdu : 成  都
changan : 长  安	hangzhou : 杭  州	suzhou : 苏  州
xiangyang: 襄  阳	fuzhou : 福  州	  foshan : 佛  山
lingzhou : 灵  州	henyang  : 衡  阳	jiaxing : 嘉  兴	
quanzhou : 泉  州	dali  : 大  理	wudang : 武当山
taishan : 泰  山	quanzhen : 全真教	emei : 峨眉山	
mingjiao : 光明顶	xingxiu : 星宿海	gumu : 古  墓	
huashan : 华  山	murong  : 慕  容	xueshan : 雪  山
xuedao   : 雪刀门	xiaoyao  : 逍遥林	lingjiu : 灵鹫宫	
guanwai  : 关  外	guiyun   : 归云庄	nanhai   : 南  海
wugong   : 武功镇	zhongnan : 终南山	yzw  : 燕子坞	
hmy  : 黑木崖	nanyang  : 南  阳	kl   : 昆仑山
sl  : 少林派	bt   : 白驼山	home  : 住  房
thd     : 桃花岛  hsjz  : 华山剑宗
----------------------------------------------------------------------
HELP
	);

	return 1;
}
 
