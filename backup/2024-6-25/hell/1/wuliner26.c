

inherit ROOM;

void create()
{
	set("short", "武林二街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"west" : __DIR__"wuliner25",
		"east" : __DIR__"wuliner27",
	]));
	set("price_build", 1000);
	setup();
}
