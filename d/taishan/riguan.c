// Room: /d/taishan/.c
inherit ROOM;

void create()
{
	set("short", "日观峰");
	set("long", @LONG
这里是位于南天户西面的山岭，怪石攒簇，最高的地方一石
卓立，名为君子峰。往北走便是泰山的西天户。
LONG );
	set("exits", ([
		"westup" : __DIR__"yuhuang",
		"eastup" : __DIR__"tanhai",
	]));
	set("objects", ([
		__DIR__"npc/tianmen" : 1,
	]));
	set("no_clean_up", 0);
	setup();
}

