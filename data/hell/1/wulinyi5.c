// by luoyun

inherit ROOM;

void create()
{
	set("short", "武林一街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"north" : __DIR__"wulinyi4",
		"south" : __DIR__"dongjie3",
	]));
	//set("price_build", 1000);
	setup();
}
