
inherit ROOM;

void create()
{
	set("short", "东街五号");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"west" : __DIR__"dongjie5",
		"north" : __DIR__"wulinsi11",
		//"east" : __DIR__"dongjie7",
		"south" : __DIR__"wulinsi12",
	]));
	set("objects", ([
	]));
	setup();
}
