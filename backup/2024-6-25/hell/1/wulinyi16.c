// by luoyun

inherit ROOM;

void create()
{
	set("short", "武林一街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"south" : __DIR__"xijie3",
		"north" : __DIR__"wulinyi17",
	]));
	//set("price_build", 1000);
	setup();
}
