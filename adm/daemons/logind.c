// logind.c 
 
 
#include <command.h> 
#include <login.h> 
#include <config.h> 
#include <getconfig.h> 
 
#define MUDLIST_CMD     "/cmds/usr/mudlist" 
#define REBOOT_CMD      "/cmds/arch/reboot" 
 
inherit F_DBASE; 
 
nosave int wiz_lock_level = 0; 
 
nosave string *movie; 
 
string *banned_name = ({ 
    "你", "你", "我", "他", "她", "它","东方", 
    "爸", "爷", "　", "妈","她妈","他妈","操操","fuck","下阴","阴部","口交","性交","阴唇","阴道", 
    "屎", "尿", "粪","操你","日你","大爷","老妈","干你","操妈", 
"自己","杀手","闪电","雪人","逍遥","我们","你们","他们","咱们","大家","某人","尸体", 
"天神","总管","龙神","仙人","巫师","门客","玩家","书","书剑","名字待定","中神通","蒙面", 
"蒙面人","刺客","忍者","镖师","鬼魂","头颅","杀人犯", 
// Mud 地名，门派名 
"衡山","华山","嵩山","恒山","泰山","雪山","黄山","天山","西域","苗疆","东北","中原", 
"南疆","长江","黄河","中国","中华","昆仑山","长白山","白驼山","武当山","峨嵋山", 
"冰火岛","桃花岛","黑木崖", 
"少林","丐帮","明教","密宗","古墓","全真","铁掌","大理","白驼","桃花","星宿", 
"天龙寺","大轮寺","五毒教","正义","邪恶","五岳剑派","日月神教","官府","武林", 
"少林寺","武当派","铁掌帮","普通百姓","峨嵋派","姑苏慕容","古墓派","华山派","嵩山派", 
"明教","神龙教","星宿派", 
// 重要人物名字 
"金庸","邓小平","江泽民","毛泽东","朱榕基","皇帝", "皇上","总理", "主席", "习近平", "李克强", 
 "管理员", "巫师", "干部", 
// 小说人物 
"三丰真人","张无极","郭大侠","杨改之","令狐聪","胡飞","苗仁凤","韦天宝","袁承志","胡亿刀", 
"陈伽洛","段羽","萧锋","乔锋","虚竺","东方教主","欧阳锋","洪九指","黄岛主","段皇爷", 
"燃灯大师","王重阳","周博通","黄帮主","风轻洋","独孤求败", 
// 脏话 
"统一","法轮","法轮研究","法轮大","吃人","他妈的","去你的","操你妈","干你娘","废物", 
"混蛋","坏蛋","杀人","抢劫","强奸","艺女","台独","领导","中央","屁眼","屁股","裸体", 
"放屁","鸡巴","阴道","婊子","你丫","日你","赤佬","瘪三","傻逼","蠢蛋","操他","我操", 
"太监","宦官","阉割","阉人","鸡", "奸淫", "淫荡", "轮奸", "奸", "三级", "政治", 
//特殊名字 
"淑女","君子", 
 
}); 
 string *banned_id =   ({"admin","arch","wizard","apprentice","immortal","player","fuck", "corpse", "mud", "none",
	});

string *yz_msg_list = ({});

//
// 少林派：
// 相传天下武功出少林，少林七十二绝技的确有过人之处，其内功更是位列榜首，只收男的，切忌破身。
// 少林弟子的基本轻功、基本招架、基本内功、佛学这四项技能都大于120级，可以拜三渡。
// 武功推荐：
// 兵器：日月鞭；
// 招架：金刚不坏体；
// 内功：混元一气功，易筋经，九阳；
// 轻功：蝙蝠步（公共武学，需先天臂力小于25，先天身法至少26）。
// 组合一：九阳+六脉+挪移+不坏体+九剑（狡黠13 30 24 13）
// 组合二：降龙+互搏+不坏体（光明或心狠30 13 24 13）结婚学了降龙再拜入少林
// 组合三：葵花+互搏+不坏体+蝙蝠步（阴险13 15 22 30）宗师前用本门武功过渡

// 武当派：
// 三丰真人自少林出来自创武当一派，至今影响仍在。武当择徒极严，非正直之人（正神）不收，不收叛师之人。
// 武功推荐：
// 兵器，太极剑；
// 空手，太极拳、空灵拳（公共武学）、六阴殛神掌（公共武学，要求男性，第一次结婚，妻子被玩家pk3次（100万经验以上））；
// 招架，太极拳；
// 内功，太极神功，易筋经；
// 组合一：辟邪剑+太极拳剑（阴险最好有鬼脉天赋13 22 15 30）杀剑用太极剑招架，空手用太极拳招架，攻防兼备。拜了三丰真人后学到太极拳剑再自宫。
// 组合二：黯然+互搏+蝙蝠步+太极拳（光明或阴险15 15 21 29）

// 峨眉派：
// 男女都收，但女的最有前途，最好出家，切忌破身。
// 武功推荐：
// 兵器：回风拂柳剑、越女剑、圣火令；
// 空手：六极神剑、玄阴炼骨爪；
// 招架：乾坤大挪移；
// 内功：临济十二庄（处女）；
// 临济庄的powerup加兵器伤害，建议走兵器路线，性格选择狡黠多变或阴险奸诈，属性分配13 26 20 21或13 27 20 20，一旦成功就可以临济+回风拂柳+蝙蝠步+乾坤大挪移+圣火令武功+六极神剑+越女剑+不败神功（或者葵花魔功）

// 华山剑宗：
// 技能推荐：
// 兵器：九剑归一、连风快剑；
// 内功：紫阳神功，易筋经&吸功大法；
// 拥有剑道修养（sword-cognize）就会出剑气，有剑气的剑法有：华山剑法，连风快剑，九剑归一，不败神功。
// 注：要出剑气不能exert powerup，回归华山派也会失去剑气。
// 组合一：互搏+不败+蝙蝠步（狡黠13 15 22 30）
// 组合二：九阳+六脉+挪移（性格随意13 30 24 13）九阳填补剑宗内功空缺，若中不了九阳就用易筋经或吸星。

// 丐帮：
// 天下第一大帮，帮主洪九指更是行侠仗义，丐帮杖法最多，心狠手辣之人有一定威望后可以到归云庄找飞天蝙蝠柯震恶学习降魔杖法。
// 武功推荐：
// 兵器：打狗棒；
// 空手：镇岳锁龙劲；
// 组合一：降龙+互搏+打狗（光明或心狠30 13 24 13）丐帮降龙，有攻无防。之所以先这俩性格，一可以加怒，二学宗师武功方便，九阴需要所有空手，丐帮除了指法其他都有；南海要杖法掌法，正好丐帮都有。
// 组合二：九阳+六脉+挪移+打狗+南海（13 29 25 13）

// 逍遥派：
// 本服主流门派，内功卓绝。总的来说有两个路线可以走，高悟性和高臂力。
// 武功推荐：
// 兵器：九剑归一；
// 空手：六极神剑；
// 招架：乾坤大挪移；
// 内功：青冥神功、紫阳神功；
// 轻功：洛神步法。
// 组合一：九剑+凌波+六脉+九阳+挪移（狡黠13 29 25 13）
// 组合二：小无相+降龙+互搏+凌波（光明30 15 20 15）
mapping liupai = ([
        "少林九阳流":([
                "天赋":"lucky",
                "属性":"13,30,24,13",
                "性格":"狡黠多变",
        ]),
        "少林破法流":([
                "天赋":"lucky",
                "属性":"30,13,24,13",
                "性格":"光明磊落",
        ]),
        "武当身法流":([
                "天赋":"lucky",
                "属性":"13,22,15,30",
                "性格":"阴险奸诈",
        ]),
        "武当均衡流":([
                "天赋":"lucky",
                "属性":"15,15,21,29",
                "性格":"光明磊落",
        ]),
        "峨眉均衡流":([
                "天赋":"lucky",
                "属性":"13,26,20,21",
                "性格":"狡黠多变",
        ]),
        "峨眉悟性流":([
                "天赋":"lucky",
                "属性":"13,27,20,20",
                "性格":"阴险奸诈",
        ]),
        "华山辟邪流":([
                "天赋":"ghost",
                "属性":"13,15,22,30",
                "性格":"阴险奸诈",
        ]),
        "华山九剑流":([
                "天赋":"lucky",
                "属性":"13,29,25,13",
                "性格":"光明磊落",
        ]),
        "丐帮降龙流":([
                "天赋":"lucky",
                "属性":"30,13,24,13",
                "性格":"光明磊落",
        ]),
        "丐帮打狗流":([
                "天赋":"lucky",
                "属性":"13,29,25,13",
                "性格":"光明磊落",
        ]),
        "逍遥九剑流":([
                "天赋":"lucky",
                "属性":"13,29,25,13",
                "性格":"光明磊落",
        ]),
        "逍遥降龙流":([
                "天赋":"lucky",
                "属性":"30,13,24,13",
                "性格":"光明磊落",
        ]),        
]);

//选择出生地，value为字符串直接选择出生地，如果是mapping则设定姓氏
mapping born = ([
        "关外人氏" : "/d/guanwai/kedian",
        "燕赵人氏" : "/d/beijing/kedian",
        "齐鲁人氏" : "/d/taishan/kedian",
        "秦晋人氏" : "/d/changan/kezhan",
        "中原人氏" : "/d/shaolin/kedian1",
        "西域人氏" : "/d/xingxiu/kedian",
        "荆州人氏" : "/d/xiangyang/kedian",
        "扬州人氏" : "/d/city/kedian",
        "苏州人氏" : "/d/suzhou/kedian",
        "杭州人氏" : "/d/hangzhou/kedian",
        "福建人氏" : "/d/fuzhou/kedian",
        "巴蜀人氏" : "/d/city3/kedian",
        "云南人氏" : "/d/dali/kedian",
        "两广人氏" : "/d/foshan/beidimiao",
        "欧阳世家" : ([ "born"      : "西域人氏",//氏族
                        "surname"   : "欧阳",//额外的性
                        "startroom" : "/d/baituo/dating",//初始路径
                        ]),
        "关外胡家" : ([ "born"      : "关外人氏",
                        "surname"   : "胡",
                        "startroom" : "/d/guanwai/xiaowu",
                        ]),
        "段氏皇族" : ([ "born"      : "大理人氏",
                        "surname"   : "段",
                        "startroom" : "/d/dali/wangfugate",
                        ]),
        "慕容世家" : ([ "born"      : "江南人氏",
                        "surname"   : "慕容",
                        "startroom" : "/d/yanziwu/cuixia",
                        ]),
]);

// 内部调用的函数 
private void get_user(string arg, object ob); 
private void get_char(string arg, object ob); 
void jiance(string arg,object ob,string str); 
private void init_new_player(object user); 
 
// 可以被外部调用的函数 
object  make_body(object ob); 
varargs void enter_world(object ob, object user, int silent); 
varargs void reconnect(object ob, object user, int silent); 
object find_body(string name); 
int check_legal_id(string arg); 
int check_legal_name(string arg, int maxlen); 

int link_number = 0;

string error_result(string msg)
{
        mapping error_map = ([
                "code":405,
        ]);

        if (msg)
        {
                error_map["msg"] = msg;
        }
        else
        {
                error_map["msg"] = "未知错误";
        }

        return json_encode(error_map) + "\n";
}


string login_result(int code,string msg)
{
        mapping login_map = ([
                "code":code,
                "msg":msg                
        ]);

        return json_encode(login_map) + "\n";
}

void create()  
{ 
        seteuid(ROOT_UID); 
        set("channel_id", "连线"); 
} 
 
void logon(object ob) 
{ 
        string str; 
        if (BAN_D->is_banned(query_ip_name(ob)) == 1) { 
                write(error_result("你IP地址已被封禁，如有问题。"));
                destruct(ob); 
                return; 
        } 
        str = ZJKEY; 
        link_number++;

        write("\n" +login_result(200,"正在等待连接确认,yes确认，wait继续等待，这是本次运行的第" + link_number + "次连接。"));
        input_to("jiance",ob,str); 
} 
 
void jiance(string arg,object ob,string str) 
{ 
        // write("收到的信息为：" + arg + "\n");

        // if (find_player("demodemo"))
        // {
        //         tell_object(find_player("demodemo",arg + "\n"));
        // }
        // ------------------------------------------------------
        // if(!arg) 
        // { 
        //         input_to("jiance",ob,str); 
        //         return; 
        // } 
        // else if (arg=="wait") 
        // { 
        //         write(login_result(200,"等待中"));
        //         input_to("jiance",ob,str);
        //         return; 
        // }
        // else if (arg=="yes")
        // {
        //         write(login_result(200,"请输入账号验证"));
        //         input_to("get_user", ob); 
        // }
        // else 
        // { 
        //         write(error_result("无法验证当前登录参数。"));
        //         input_to("jiance",ob,str); 
        //         return; 
        // }

        //直接调用get_user
        get_user(arg,ob);

} 
 
private void get_user(string arg, object ob) 
{ 
        //arg,账号║密码║密文║email。 
        //新版本格式：账号║║密码║手机号║ip地址
        object old_link,user; 
        string *myinfo,ip,myIphone; 
 
        if( !arg||arg=="") { 
                input_to("get_user", ob); 
                return; 
        }

        // write("测试222222\n");
        myinfo = explode(arg,"║"); 
 
        if( sizeof(myinfo) < 4 ) 
        { 
                write(error_result("验证格式错误，请重新输入格式验证"));
                input_to("get_user", ob); 
                return; 
        } 

        if( !check_legal_id(lower_case(myinfo[0]))) 
        { 
                //账号不合法 
                write(error_result("账号不合法"));
                input_to("get_user", ob); 
                return; 
        } 
        

        myinfo[0] = lower_case(myinfo[0]); 

        if (wiz_level(myinfo[0]) < wiz_lock_level) 
        { 
                write(error_result("对不起，"+LOCAL_MUD_NAME()+"正在维护中，请稍后登录。。。"));
                input_to("get_user",ob); 
                return; 
        } 
 
        if( (string)ob->set("id", myinfo[0]) != myinfo[0]) { 
                // write(ZJTMPSAY"未知错误，请重试i。。。\n"); 
                write(error_result("未知错误，请重试。。。"));
                input_to("get_user", ob); 
                return; 
        } 

        //设定手机号
        if (sizeof(myinfo) >= 3)
        {
                myIphone = myinfo[2];
        }
        else
        {
                myIphone = "未知";
        }

        //设定ip地址
        if (sizeof(myinfo) >= 4)
        {
                ip = myinfo[3];
        }
        else
        {
                ip = "未知";
        }

        if (myinfo[0] != "demo123" && myinfo[0] != "demodemo" && myinfo[0] != "sxpcgq7zsgw0")
        {
                int sum = 0;

                if( sizeof(myinfo) < 6 ) 
                { 
                        write(error_result("验证格式错误，请重新输入格式验证"));
                        input_to("get_user", ob); 
                        return; 
                } 

                // 如果myinfo[4]的长度 + 1 小于myinfo[5]，直接拒绝连接
                if (strlen(myinfo[4]) + 1 < to_int(myinfo[5]))
                {
                        write(error_result("验证码错误，识别到非法侵入，拒绝连接，错误码:00"));
                        input_to("get_user", ob);
                        return;
                }

                // 重定义myinfo[4],提取验证码，myinfo[5]会给出下标，代表myinfo[4]从哪个下标开始读取，读取十位结束
                myinfo[4] = myinfo[4][to_int(myinfo[5])..to_int(myinfo[5]) + 9];

                // 判定yz_msg_list中是否存在myinfo[4]
                if (sizeof(yz_msg_list))
                {
                        if (member_array(myinfo[4], yz_msg_list) != -1)
                        {
                                write(error_result("验证码错误，识别到非法侵入，拒绝连接，错误码:11"));
                                input_to("get_user", ob);
                                return;
                        }
                }

                // 如果验证码长度不等于10，直接拒绝连接
                if (strlen(myinfo[4]) != 10)
                {
                        write(error_result("验证码错误，识别到非法侵入，拒绝连接,错误码:22"));
                        input_to("get_user", ob);
                        return;
                }

                // 提取验证码的偶数位，然后使用to_int转换成数字，然后遍历累加如果最终结果不等于20，直接拒绝连接
                for (int i = 0; i < strlen(myinfo[4]); i++)
                {
                        if ((i + 1) % 2 == 0)
                        {
                                // write("当前数字：" + to_int(myinfo[4][i..i]) + "\n");
                                sum += to_int(myinfo[4][i..i]);
                        }
                }

                if (sum != 20)
                {
                        write(error_result("验证码错误，识别到非法侵入，拒绝连接,错误码:33"));
                        input_to("get_user", ob);
                        return;
                }

                // 如果yz_msg_list数组元素大于500，清空数组
                if (sizeof(yz_msg_list) > 500)
                {
                        yz_msg_list = ({});
                }

                yz_msg_list += ({myinfo[4]});


        }


        ob->set_temp("player_ip",ip);
        ob->set_temp("player_iphone",myIphone);

        //打印ip地址和手机号
        // write("ip：" + ip + "-手机号：" + myIphone + "\n");
 
        if( file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0 )  
        { 
                if( !ob->restore() )  
                { 
                        write(ZJTMPSAY"人物存档出现问题。。。\n"); 
                        input_to("get_user", ob); 
                        return; 
                } 
                
                if (! stringp(myinfo[1]) || crypt(myinfo[1], ob->query("password"))!=ob->query("password")) 
                { 
                        // write(INPUTTXT("角色密码错误-001，请重新输入密码：", myinfo[0]+"║$txt#║"+myinfo[2]+"║"+myinfo[3]+"\n"));
                        write(error_result("角色密码错误，请重新输入密码"));
                        input_to("get_user", ob);
                        return; 
                } 
        } 
        else  
                ob->set("body", USER_OB); 
 
        if( (string)ob->set("password",crypt(myinfo[1],0)) != crypt(myinfo[1],ob->query("password"))) { 
                // write(ZJTMPSAY"未知错误，请重试p。。。\n"); 
                write(error_result("密码加密验证比对错误，请重试。。。"));
                input_to("get_user", ob); 
                return; 
        } 
 
        write("\n"); 
 
        user = find_body(ob->query("id")); 
        if (user) { 
                old_link = user->query_temp("link_ob"); 
                if( old_link ) { 
                        if(interactive(user)) 
                        { 
                                tell_object(user, error_result("你的账号在别处登录，你被迫下线了！"));
                                exec(old_link, user); 
                        } 
                        destruct(old_link); 
                } 
                //200，登陆成功 
                write(login_result(200,"登录成功"));
                // write(ZJTMPSAY"登录成功，正在加载世界。。。\n"); 
                reconnect(ob, user); 
                return; 
        } 
        if( objectp(user = make_body(ob)) ) { 
                user->set_temp("link_ob",ob); 
                if( file_size(user->query_save_file() + __SAVE_EXTENSION__) >= 0 ){ 
                        if( user->restore() ) { 
                                //200，登陆成功
                                write(login_result(200,"登录成功"));
                                // write(ZJTMPSAY"登录成功，正在加载世界。。。\n"); 
                                enter_world(ob, user); 
                                return; 
                        } else { 
                                write(error_result("人物存档出现问题。。。"));
                                input_to("get_user", ob); 
                                return; 
                        } 
                } 
        } 
        destruct(user); 
        //建立角色，200，建立角色
        write(login_result(200,"建立角色"));
        input_to("get_char", ob); 
} 
 
private void get_char(string arg, object ob) 
{ 
        //arg,性别║昵称║出生地点║天赋║属性(力量，悟性，根骨，身法)║性格║流派。 
        object user; 
        string *myinfo,result; 
        string *myattr;

        //建立天赋字典表
        mapping talnetList = ([	
                "速行":"agile",
                "阴身":"ghost",
                "好战之气":"hatred",
                "好运":"lucky",
                "六道轮回":"lun",
                "天生真气":"mystery",
                "气盛":"power",
                "小周天运转":"self",
                "天生刀客":"tblade",
                "自幼通爪":"tclaw",
                "天生棍手":"tclub",
                "自幼通拳":"tcuff",
                "自幼通指":"tfinger",
                "天生锤手":"thammer",
                "手臂灵活":"thand",
                "鬼话连篇":"trick",
                "天生杖师":"tstaff",
                "自幼通掌":"tstrike",
                "天生剑客":"tsword",
                "拳脚灵活":"tunarmed",
                "自幼好鞭":"twhip",
                "驻颜":"youth",
        ]);

        if( !arg||arg=="wait"||arg=="") 
        { 
                write(login_result(200,"等待输入角色名中"));
                input_to("get_char", ob); 
                return; 
        } 
 
        myinfo = explode(arg,"║"); 

        if(sizeof(myinfo)!=7)
        { 
                write(error_result("格式错误。"));
                input_to("get_char", ob); 
                return; 
        }



        if (!undefinedp(talnetList[myinfo[3]]))
        {
                myinfo[3] = talnetList[myinfo[3]];
        }
        else
        {
                write(error_result("天赋不存在。"));
                input_to("get_char", ob); 
                return; 
        }

        //检查流派，如果是非自选流派开始检查liupai变量中的内容重新设定myinfo的各项信息
        if (myinfo[6] != "自主流")
        {
                if (! liupai[myinfo[6]])
                {
                        write(error_result("流派不存在。"));
                        input_to("get_char", ob); 
                        return; 
                }

                myinfo[3] = liupai[myinfo[6]]["天赋"];
                myinfo[4] = liupai[myinfo[6]]["属性"];
                myinfo[5] = liupai[myinfo[6]]["性格"];  
        }
 
        if( !check_legal_name(myinfo[1],8) ) { 
                //昵称不符合要求 
                input_to("get_char", ob); 
                return; 
        }


 
        ob->set("purename", myinfo[1]);//名（一个名字由姓和名组成，purename是名）

        //如果有姓氏，则设定姓氏
        if (mapp(born[myinfo[2]]))
        {
                if (!undefinedp(born[myinfo[2]]["surname"]))
                {        //加入氏族性
                        myinfo[1] = born[myinfo[2]]["surname"] + myinfo[1];
                        ob->set("surname",born[myinfo[2]]["surname"]);
                }
        }


        //设定属性
        //拆分字符串
        myattr = explode(myinfo[4],",");

        if (sizeof(myattr) != 4)
        {
                write(error_result("属性格式错误。"));
                input_to("get_char", ob); 
                return; 
        }

        //检查属性是否合法
        foreach(string attr in myattr)
        {
                if (to_int(attr) < 10 || to_int(attr) > 30)
                {
                        write(error_result("属性值不合法。"));
                        input_to("get_char", ob); 
                        return; 
                }
        }

        //属性总和不能超过80
        if (to_int(myattr[0]) + to_int(myattr[1]) + to_int(myattr[2]) + to_int(myattr[3]) != 80)
        {
                write(error_result("属性总和必须为80。"));
                input_to("get_char", ob); 
                return; 
        }


        if (stringp(result = NAME_D->invalid_new_name(myinfo[1]))) 
        { 
                write(error_result(result));
                input_to("get_char", ob); 
                return; 
        }

        ob->set("name", myinfo[1]);//设定姓名

        if( !objectp(user = make_body(ob)) ) 
        {
                //生成角色异常
                write(error_result("生成角色异常，无法重试，请直接联系客服处理。"));
                return; 
        }


                //设定世家信息，born_family和born
        //是否是mapping,用于设置出生地点
        if (mapp(born[myinfo[2]]))
        {
                user->set("born_family",myinfo[2]);
                user->set("born",born[myinfo[2]]["born"]);
                user->set("startroom",born[myinfo[2]]["startroom"]);
                
        }
        else
        {
                user->set("born_family",myinfo[2]);
                user->set("born",myinfo[2]);
                user->set("startroom",born[myinfo[2]]);
        }
        //设定天赋
        user->set("special_skill/"+myinfo[3],1);

        //设定属性
        user->set("str",to_int(myattr[0]));
        user->set("int",to_int(myattr[1]));
        user->set("con",to_int(myattr[2]));
        user->set("dex",to_int(myattr[3]));

        //设定性格
        user->set("character",myinfo[5]);

        user->set("kar", 10); 
        user->set("per", 10); 
        user->set("gender", myinfo[0]); 
        user->set("registered",1);
        init_new_player(user); 
        VIP_D->restore_vdata(user); 
        //200，登录成功
        write(login_result(200,"登录成功"));
        // call_out("enter_world",1,ob, user); 
        enter_world(ob, user);
} 
 
object make_body(object ob) 
{ 
        string err; 
        object user; 
         
 
        seteuid(getuid()); 
        user = new(USER_OB); 
        if (! user) 
        { 
                write("现在可能有人正在修改使用者物件的程式，无法进行复制。\n"); 
                write(err+"\n"); 
                return 0; 
        } 
        seteuid(ob->query("id")); 
        export_uid(user); 
        export_uid(ob); 
        seteuid(getuid()); 
        user->set("id", ob->query("id")); 
        user->set("surname", ob->query("surname")); 
        user->set("purename", ob->query("purename")); 
        user->set_name( 0, ({ ob->query("id")}) ); 
        return user; 
} 
 
private void init_new_player(object user) 
{ 
        // 初始化必要属性 
        user->set("title", "普通百姓"); 
        user->set("birthday", time() ); 
        user->set("potential", 99); 
        user->set("food", (user->query("str") + 10) * 10); 
        user->set("water", (user->query("str") + 10) * 10); 
        user->set("channels", ({ "chat", "rumor", "party", 
                                 "bill", "sos", "family", 
                                 "ic", "rultra" })); 
 
        // 记录名字 
        NAME_D->map_name(user->query("name"), user->query("id")); 
 
        // 设置必要的环境参数 
        user->set("env/wimpy", 60); 
} 
 
varargs void enter_world(object ob, object user, int silent) 
{ 
        object  login_ob; 
        string startroom; 
        string ipname; 
 
        if(! is_root(previous_object())) 
                return; 
 
        user->set_temp("link_ob", ob); 
        ob->set_temp("body_ob", user); 
        if(ob->query_temp("web_log")) 
        { 
                user->set_temp("web_log",1); 
                if(ob->query_temp("last_ip")) 
                        user->set("last_ip",ob->query_temp("last_ip")); 
        } 
        else 
        { 
                user->delete_temp("web_log"); 
                user->set("last_ip",query_ip_name(ob)); 
        } 
 
        log_file("loginip",ctime(time())+":"+user->query("id")+"从"+user->query("last_ip")+"进入游戏。\n"); 
        ob->set("registered", user->query("registered")); 
 
        if (interactive(ob)) exec(user, ob); 
 
        write("\n目前权限：" + wizhood(user) + "\n"); 
 
        user->setup(); 
        if (user->query("age") == 14) 
        { 
                user->set("food", user->max_food_capacity()); 
                user->set("water", user->max_water_capacity()); 
        } 
 
        user->save(); 
        user->set("last_save", time()); 
        user->force_me("mycmds"); 
        ob->save(); 
 
        // check the user 
        UPDATE_D->check_user(user); 
        TOP_D->map_user(user); 
 
        if (! silent) 
        { 
                if (! user->query("registered")) 
                        color_cat(UNREG_MOTD); 
                else 
                        color_cat(MOTD); 
 
                write("你连线进入了" + LOCAL_MUD_NAME() + "。\n\n"); 
 
                if (! user->query("registered") || ! stringp(user->query("character"))) 
                { 
                        if (user->is_ghost()) 
                                user->reincarnate(); 
                        user->set("startroom", REGISTER_ROOM); 
                } else 
                if (! stringp(user->query("born"))) 
                { 
                        if (user->is_ghost()) 
                                user->reincarnate(); 
                        user->set("startroom", BORN_ROOM); 
                } 
 
                if (user->is_in_prison()) 
                        startroom = user->query_prison(); 
                else 
                if (user->is_ghost()) 
                        startroom = DEATH_ROOM; 
                else 
                if (! stringp(startroom = user->query("startroom")) || 
                    file_size(startroom + ".c") < 0) 
                        startroom = START_ROOM; 
 
                // if ((user->query("str")+user->query("con")+user->query("dex")+user->query("int")) 
                //         >(100+user->query("relife/zhuanshi")*4+user->query("gift/lighting")+user->query("level")/10) 
                //         && user->query("id")!="luoyun") 
                // { 
                //         user->set("startroom", "/d/death/block"); 
                //         startroom = "/d/death/block"; 
                // } 
 
                if (present("chuwu dai 2", user)) 
                { 
                        user->set("startroom", "/d/death/block"); 
                        startroom = "/d/death/block"; 
                } 
 
                if (! catch(load_object(startroom))) 
                        user->move(startroom); 
                else 
                { 
                        user->move(START_ROOM); 
                        startroom = START_ROOM; 
                        user->set("startroom", START_ROOM); 
                } 
                tell_room(startroom, user->query("name") + "连线进入这个世界。\n", ({user})); 
        } 
 
        login_ob = new(LOGIN_OB); 
        login_ob->set("id", user->query("id")); 
        login_ob->restore(); 
        if (login_ob->query("registered")) 
        { 
                if (! intp(login_ob->query("login_times"))) 
                { 
                        write(NOR "\n你是第一次光临" + LOCAL_MUD_NAME() + "。\n"); 
                        login_ob->set("login_times", 1); 
                } else 
                { 
                        login_ob->add("login_times", 1); 
                        write("\n你上次光临" + LOCAL_MUD_NAME() + "是 " + HIG + ctime(login_ob->query("last_on")) + NOR + " 从 " + HIR + 
                                login_ob->query("last_from") + NOR + " 连接的。\n"); 
                } 
        } 
 
        destruct(login_ob); 
 
        CHANNEL_D->do_channel(this_object(), "sys",sprintf("%s(%s)由%s连线进入。",user->name(), user->query("id"), 
                                        (ipname = query_ip_number(user)) ? ipname : "未知地点")); 
 
        if (wizhood(user) != "(admin)" && EXAMINE_D->query("log_by/" + user->query("id"))) 
                user->start_log(); 
 
//      GIFT_D->check_gift(user); 
        if ((user->query("qi") < 0 || user->query("jing") < 0) && living(user)) 
                user->unconcious(); 
} 
 
varargs void reconnect(object ob, object user, int silent) 
{ 
        user->set_temp("link_ob", ob); 
        if(ob->query_temp("web_log")) 
                user->set_temp("web_log",1); 
        else 
                user->delete_temp("web_log"); 
        ob->set_temp("body_ob", user); 
        exec(user, ob); 
 
        user->reconnect(); 
        if( !silent && (! wizardp(user) || ! user->query("env/invisible"))) { 
                tell_room(environment(user), user->query("name") + "重新连线回到这个世界。\n", 
                ({user})); 
        } 
        CHANNEL_D->do_channel( this_object(), "sys", 
                sprintf("%s[%s]由%s重新连线进入。", user->query("name"), 
                        user->query("id"), query_ip_number(user))); 
        user->force_me("mycmds"); 
        user->force_me("look"); 
} 
 
int check_legal_id(string id)
{
	int i;

	id = lower_case(id);

	i = strlen(id);

	if( (i<4||i>20) && (string)SECURITY_D->get_status(id) == "(player)" ) {
                write(error_result("对不起，你的ID长度不符合要求(4-20)。"));
		return 0;
	}

	if( id[0]<'a' || id[0]>'z' ) {
                write(error_result("对不起，你的ID必须用英文字母开头。"));
		return 0;
	}

	while(i--)
	{
		if( !((id[i]>='a' && id[i]<='z')||id[i]=='_'||(id[i]>='0' && id[i]<='9')) ) {
                        write(error_result("对不起，你的ID只能用英文字母或包含数字及‘_’的组合。"));
			return 0;
		}
	}

	return 1;
}

int check_legal_name(string name, int maxlen)
{
	int i;

	i = strlen(name);
	
	if ((strlen(name) < 2) || (strlen(name) > 4))
	{
		write(ZJTMPSAY"对不起，你的中文姓名不能太长或太短。\n");
		return 0;
	}

	if (! is_chinese(name))
	{
		write(ZJTMPSAY"对不起，请您用「中文」取名字。\n");
		return 0;
	}

	return 1;
}

 
object find_body(string name) 
{ 
        object ob, *body; 
 
        if( objectp(ob = find_player(name)) ) 
                return ob; 
        body = children(USER_OB); 
        foreach(ob in body) if (getuid(ob) == name) return ob; 
        return 0; 
} 
 
int set_wizlock(int level) 
{ 
        if (wiz_level(this_player(1)) <= level) 
                return 0; 
 
        if (geteuid(previous_object()) != ROOT_UID) 
                return 0; 
 
        wiz_lock_level = level; 
        return 1; 
} 
 
int can_login(int level) 
{ 
        if (level < wiz_lock_level) 
                return 0; 
 
        return 1; 
} 
 
int howmuch_money(object ob) 
{ 
        int total; 
        int total2; 
        object gold, silver, coin; 
 
        total = 0; 
        total2 = 0; 
 
        gold = present("gold_money",ob); 
        silver = present("silver_money",ob); 
        coin = present("coin_money",ob); 
 
        if( gold ) total += gold->value(); 
        if( silver ) total += silver->value(); 
        if( coin ) total += coin->value(); 
 
        total2 = (int)ob->query("balance"); 
        if (!total2 || total2 < 0) { 
                ob->set("balance", 0); 
        } 
        total=total+total2; 
        return total; 
} 
 