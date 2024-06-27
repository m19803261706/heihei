// liandan_lin7.c

 

#define LIANDAN_LIN     __DIR__"liandan_lin"

inherit LIANDAN_LIN;

void create()
{
	set("short", "城西后林");
	set("long", @LONG
这是一片茂密的树林。很多棵几十丈高的大树聚在一块，象一把把琼天大
伞，连日月都被遮蔽得暗然无光。树林中还不时可以听到大自然发出的声响。
LONG );
	set("exits", ([
		"north" : __DIR__"ximenwai",
		"south" : __DIR__"liandan_lin6",
		"east" : __DIR__"liandan_lin7",
		"west" : __DIR__"liandan_lin8",
	]));

	setup();
	//replace_program(LIANDAN_LIN);
}
