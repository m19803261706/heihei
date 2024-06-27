// Room: /city/duchang.c
inherit ROOM;
void create()
{
	set("short", "密室");
	set("long", @LONG。
LONG );
	set("item_desc", ([
		"【牌子】" : "二楼的拱猪房正处于测试阶段。\n",
	]));
	set("objects", ([
		CLASS_D("shenlong")+"/pang" : 1,
	]));
	set("exits", ([
		// "west" : __DIR__"daxiao",
		// "up"   : __DIR__"duchang2",
		"east" : __DIR__"nandajie1",
	]));
	setup();
}

