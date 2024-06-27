// rideto.c



inherit F_CLEAN_UP;

int help(object me);

mapping places = ([
	"yangzhou" : "/d/city/guangchang",
	"gc"       : "/d/city/guangchang",
	"beijing"  : "/d/beijing/tiananmen",
	"chengdu"  : "/d/city3/guangchang",
	"changan"  : "/d/changan/bridge2",
	"suzhou"   : "/d/suzhou/canlangting",
	"hangzhou" : "/d/hangzhou/road10",
	"fuzhou"   : "/d/fuzhou/dongjiekou",
	"foshan"   : "/d/foshan/street3",
	"guiyun"   : "/d/guiyun/taihu",
	"heimuya"  : "/d/heimuya/up1",
//	"kunming"  : "/d/kunming/jinrilou",
//	"lanzhou"  : "/d/lanzhou/guangchang",
//	"kaifeng"  : "/d/kaifeng/zhuque",
	"wugong"   : "/d/quanzhen/zhongxin",
	"taishan"  : "/d/taishan/taishanjiao",
	"dali"     : "/d/dali/center",
	"nanyang"  : "/d/shaolin/nanyang",
	"quanzhou" : "/d/quanzhou/zhongxin",
	"jiaxing"  : "/d/quanzhou/jiaxing",
	"xiangyang": "/d/xiangyang/guangchang",
	"yongdeng" : "/d/huanghe/yongdeng",
	"lingzhou" : "/d/lingzhou/center",
 //       "jingzhou" : "/d/jingzhou/guangchang",
 //       "zhongzhou": "/d/zhongzhou/shizhongxin",
	"henyang"  : "/d/henshan/hengyang",
	"guanwai"  : "/d/guanwai/jishi",
	"xingxiu"  : "/d/xingxiu/xxh1",
	"baituo"   : "/d/baituo/guangchang",       
	"quanzhen" : "/d/quanzhen/damen",
	"zhongnan" : "/d/quanzhen/shanjiao",
	"gumu"     : "/d/gumu/mumen",
 //       "luoyang"  : "/d/luoyang/center",
	"murong"   : "/d/yanziwu/hupan",
	"lingjiu"  : "/d/lingjiu/jian",
	"shaolin"  : "/d/shaolin/shanmen",
	"wudang"   : "/d/wudang/jiejianyan",
	"xiaoyao"  : "/d/xiaoyao/xiaodao4",	
	"huashan"  : "/d/huashan/shaluo",
	"xueshan"  : "/d/xuedao/nroad4",
	"xuedao"   : "/d/xuedao/wangyougu",
 //       "kunlun"   : "/d/kunlun/klshanlu",
	"emei"     : "/d/emei/huayanding",
	"mingjiao" : "/d/mingjiao/shanjiao",
	"nanhai"   : "/d/xiakedao/haibin",
	// "taohua"   : "/d/taohua/jingshe",
	"hujia"    : "/d/guanwai/xiaoyuan",
	"yanziwu"  : "/d/yanziwu/bozhou",
]);

int main(object me, string arg)
{
	object riding, room;
	string where;

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
		
	if (! objectp(riding = me->query_temp("is_riding")))
		return notify_fail("你还没有坐骑！\n"); 
	
	if (! present(riding->query("id"), me))
		return notify_fail("你的坐骑不在你身边！\n");

	/*
	if (present("letter", me)) 
		return notify_fail("你身上带着密函！\n");
	*/
		
	if (! environment(me)->query("outdoors")) 
		return notify_fail("在房间里不能乱跑！\n");
		
	if (environment(me)->query("no_magic") || environment(me)->query("no_fly"))
		return notify_fail("你发现这里有点古怪，你的坐骑好象不听你的指挥！\n");		

	if (member_array(arg, keys(places)) == -1 && arg != "home") 
		return notify_fail("这个地方无法乘坐骑去。\n");
		
	if (arg == "home" && ! me->query("private_room/position")) 
		return notify_fail("你还没有住房呢！\n");

	if (arg == "home" && stringp(me->query("private_room/position")) &&
	    file_size(me->query("private_room/position") + ".c") > 0)
		room = get_object(me->query("private_room/position"));
	else
	room = get_object(places[arg]);
	if (! room) return notify_fail("你感觉到似乎那个地方有点不对劲。\n");
	
	message("vision", me->name() + "骑着「" + riding->name() + NOR "」匆匆忙忙地离开了。\n",
		environment(me), ({me}));
	
	where = room->query("short");
	
	tell_object(me, "你一路马不停蹄，终于赶到了" + where + "。\n");
	me->move(room);

	message("vision", me->name() + "骑着「" + riding->name() + NOR "」一路疾驰而来。\n",
		environment(me), ({me}));

	// me->receive_damage("qi", 10);

	return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : rideto <地点>
----------------------------------------------------------------------
利用坐骑到达某个地点。目前可以利用坐骑去的地方有：
yangzhou : 扬  州	beijing  : 北  京	chengdu  : 成  都
changan  : 长  安	hangzhou : 杭  州	suzhou   : 苏  州
xiangyang: 襄  阳	fuzhou   : 福  州	foshan   : 佛  山
lingzhou : 灵  州	henyang  : 衡  阳	jiaxing  : 嘉  兴	
quanzhou : 泉  州	dali     : 大  理	wudang   : 武当山
taishan  : 泰  山	quanzhen : 全真教	emei     : 峨眉山	
mingjiao : 光明顶	xingxiu  : 星宿海	gumu     : 古  墓	
huashan  : 华  山	murong   : 慕  容	xueshan  : 雪  山
xuedao   : 雪刀门	xiaoyao  : 逍遥林	lingjiu  : 灵鹫宫	
guanwai  : 关  外	guiyun   : 归云庄	nanhai   : 南  海
wugong   : 武功镇	zhongnan : 终南山	yanziwu  : 燕子坞	
heimuya  : 黑木崖	nanyang  : 南  阳	home     : 住  房
----------------------------------------------------------------------
HELP
	);

	return 1;
}
 

