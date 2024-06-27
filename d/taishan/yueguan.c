// Room: /d/taishan/.c
inherit ROOM;

void create()
{
	set("short", "月观峰");
	set("long", @LONG
这里是位于南天户西面的山岭，怪石攒簇，最高的地方一石卓立，
名为君子峰。往北走便是泰山的西天户。
LONG );
	set("exits", ([
		"east" : __DIR__"nantian",
		"northup" : __DIR__"xitian",
	]));
	set("no_clean_up", 0);
	set("outdoors", "taishan");
	setup();
}

