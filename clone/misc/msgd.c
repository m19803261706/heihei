 
 
inherit ITEM; 
inherit F_SAVE; 
 
#define MSGFILE "/data/msg/msgd.o" 
 
int do_addmsg(string arg); 
int do_listmsg(string arg); 
int do_delmsg(string arg); 
 
string *msg = ({ 
       "带导字的属于资深老玩家,没有特权,不过有不懂得可以问导.", 
//         "节日冲优惠多多，详情看指南-冲值说明。", 
//    //     "新手可以在武庙输入推广码领取新手礼盒，快速升级。", 
//         "记得武庙每日签到哦，连续签到次数越多，奖励越高。", 
// //      "签到系统已更新，连续签到15天有签到礼盒。", 
//         "连续签到会获得等于连续次数的vip经验。", 
// //      "当经验达到一万，可以到武庙西ask wizard about 储物袋。", 
// //      "新手任务即将简化，减轻新手枯燥感觉。", 
//         "终极地狱，持续更新，长久稳定，致力于打造最好的文字游戏平台。", 
//         "指文游－终极地狱唯一QQ群号741136160。", 
//         "指文游－管理员唯一QQ号18770773。", 
}); 
 
nosave int cnd; 
 
void create() 
{ 
        seteuid(getuid()); 
        set_weight(900000000); 
        set_name("新闻广播",({"msgd","msg"})); 
        set("channel_id","新闻使者"); 
        set("unit", "个"); 
        set("no_get", 1); 
        set("no_drop", 1); 
        set("no_give", 1); 
 
        setup(); 
        if (clonep()) 
                return; 
        CHANNEL_D->do_channel( this_object(), "sys", "新闻系统已经启动。\n");    
        call_out("on_time",10); 
} 
 
void init() 
{ 
        add_action("do_addmsg","addmsg"); 
        add_action("do_listmsg","listmsg"); 
        add_action("do_delmsg","delmsg"); 
} 
 
int valid_string(string arg) 
{ 
        return 1; 
} 
 
int valid_use() 
{ 
        object me=this_player(1); 
         
        if (wiz_level(me)<wiz_level("(arch)")) 
                return 0; 
        return 1; 
} 
string query_save_file() 
{ 
        return MSGFILE; 
} 
 
void on_time() 
{ 
        int i,j; 
         
        i=sizeof(msg); 
        if (i<=0){ 
                //CHANNEL_D->do_channel(this_object(),"chat", 
                //      "没有新闻\n"); 
                call_out("on_time",300); 
                return; 
                } 
         
        CHANNEL_D->do_channel(this_object(),"chat",msg[cnd]); 
        cnd++; 
        if((cnd+1)>=sizeof(msg)) cnd = 0; 
 
        call_out("on_time",300); 
} 
 
int do_addmsg(string arg) 
{ 
        object me=this_player(1),ob; 
         
        if (!wizardp(me))
                return 0;
        if (!arg||!valid_string(arg)) 
                return notify_fail("非法的信息\n"); 
        msg += ({arg}); 
        save(); 
        tell_object(me,"新闻增加完毕\n");                
        return 1; 
} 
 
int do_listmsg(string arg) 
{ 
        int i; 
        object me=this_player();
        
        if (!wizardp(me))
                return 0;
        for (i=0;i<sizeof(msg);i++) 
                printf("%4d    :    %s\n",i+1,msg[i]); 
        return 1;     
} 
      
int do_delmsg(string arg) 
{ 
        object me=this_player(1),ob; 
        int i; 
        if (!wizardp(me))
                return 0;
        if (sscanf(arg, "%d", i)!=1) 
                return notify_fail("你要删除哪一条信息？\n"); 
        msg -= ({msg[i-1]}); 
        save(); 
        tell_object(me,"新闻删除完毕\n"); 
        return 1; 
} 
      
