

inherit ROOM;

void create()
{
	set("short", "武林二街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"north" : __DIR__"wuliner9",
		"south" : __DIR__"wuliner11",
	]));
	set("price_build", 1000);
	setup();
}
