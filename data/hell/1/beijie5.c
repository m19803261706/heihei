// by luoyun

inherit ROOM;

void create()
{
	set("short", "北街五号");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"south" : __DIR__"beijie4",
		"east" : __DIR__"wulinsan1",
		"west" : __DIR__"wulinsan36",
		"north" : __DIR__"beijie6",
	]));
	set("objects", ([
	]));
	setup();
}