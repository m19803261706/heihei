// Room: Yanyu2.c  烟雨楼二楼
// Date: Sep.6 1997

inherit ROOM;

string look_bian();

void create()
{
	set("short", "烟雨楼二楼");
	set("long", @LONG
烟雨楼在南湖畔，四望临风，醺醺醉人。柳岸翻曳，禽噪起伏。
湖面轻烟薄雾，几尾小舟荡漾其间。半湖水里都浮着碧油油的菱叶，
越女轻歌，娇痴无那。
    你放眼观赏，直欲跳入她的怀中。

    楼中立了一幅长匾(bian)，绞丝镶边，楠木为里，年代虽久，
桐油粉漆，犹自清新如昨。柱子上隐隐有些字迹（ziji）。
LONG );
	set("no_sleep_room",1);
	set("item_desc", ([
	    "ziji" : "江南七怪叫板邱处机处。\n",
	    "bian" : (: look_bian :),
	]));

	set("exits", ([
	    "down"     : __DIR__"yanyu",
	]));
	set("no_clean_up", 0);
	setup();
}

string look_bian()
{
	return
	"※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n"
	"※※※※　　　		    　　　　　　　　　　　　※※※※\n"
	"※※※※　　　　	    　西洲曲    　	　　　　※※※※\n"
	"※※※※　					    　　※※※※\n"
	"※※※※　忆梅下西洲  折梅寄江北  单衫杏子红  双鬓鸦雏色　※※※※\n"
	"※※※※　西洲在何处  双桨摇头度  日暮伯劳飞  风吹乌桕树　※※※※\n"
	"※※※※　树下即门前  门中露翠钿  开门郎不至  出门采红莲　※※※※\n"
	"※※※※　采莲南塘秋  莲花过人头  低头弄莲子  莲子清如水　※※※※\n"
	"※※※※　置莲怀袖中  莲心彻底红  忆郎郎不至  仰首思飞鸿　※※※※\n"
	"※※※※　飞鸿满西洲  望楼上青楼  楼高望不见  尽日栏杆头　※※※※\n"
	"※※※※　栏杆十二曲  垂手明如玉  卷帘天自高  海水摇空绿　※※※※\n"
	"※※※※　海水梦悠悠  君愁我亦愁  南风如我意  吹梦到西洲　※※※※\n"
	"※※※※　　　　　　　　　　　		    　　　　※※※※\n"
	"※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n";
}
