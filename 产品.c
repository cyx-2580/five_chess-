#pragma warning(disable: 4996)
#include<stdio.h>
//全局变量；
//1.棋盘
char arr[10][10];
//#################################
//cyx-五子棋;
// 功能函数声明；
//1.开始界面
int begin(void);

//2,棋局界面
int chess(void);
//2.2非法坐标提醒；
int gps(int a,int b);
//2.3判断胜利
int over(int a,int b, int number);              //读数
int over_out_nember(int out, int number);            //最终判断
//3.结算界面
void out_cg(int out);

//4,非法选项
int bug(int a);

//5.刷新棋盘
void new(void);
//##########################################################################################################
//##########################################################################################################
//主函数只负责处理功能函数,和输入输出
int main(void) {
    int out = 0;    //专门负责
    one____begin:
    printf("开始游戏_____输入1\n");      
    printf("退出_________输入0\n");
    printf("不要输入奇怪的东西,否则会有可怕的事情发生QWQ\n另外确保输入法处于英文输入法\n");
    out = begin();    //调用begin_1函数
    printf("##########################################################################\n");
    if (out = -1) {
        return 0;
    }
    else if (out== 0) {
        printf("不多坐会儿？\n");                     /*在begin（）中选择退出后2次选项*/
        printf("\"坚决退出_________输入0\"\n");
        printf("\"放弃退出_________输入1\"\n");
        out = begin();              //调用begin输入
        printf("##########################################################################\n");
            if (out == 0) {
                printf("好友，你我一见如故，如今你却要走，那么我便送你一送\n");
                return 0;
            }
            else {
                goto one____begin;    //跳转到开始界面
            }
    }
    else {
        printf("你是黑方，现在你来挑战扮演白方的你\n");
        new();
        int qq=chess();    //开始棋局界面
        if (qq == 666) {
            goto one____begin;
        }
        goto one____begin;
    }
    return 0;
}

//###########################################################################################################
//###########################################################################################################

/*1.1开始界面
判断是否输入违法；违法输出调用int bug(void);
*/
int begin(void) {
    int out;
    scanf("%d", &out);
    if (out != 1 && out != 0) {
        if (bug(out) == -1) {
            return 0;
        }
        else {
            return begin();
        }
    }
    return out;
}

//#########################################################################
//2,1棋局界面
/*功能1轮流下棋,功能2返回开始界面
O代表白子，#代表黑子，@代表空地；
先打印棋盘再通过输入坐标的方式落子————判断输入是否违法
通过反复打印刷新棋盘，并更新回合数
输出666表示强制退出
输出0表示完赛退出
*/
int chess(void) {
    int out = 0;
    int a, b,number=0;
    do {
        number++;
        printf("若像回到开始界面请输入括号内的内容（31543,10086）确保输入法处于英文输入法\n");
        printf("____________ 第%d回合_____________\n", (number+1)/2);
        printf("友情提醒O代表白子，#代表黑子，@代表空地\n");
        for (int i = 0;i < 10;i++) {
            for (int j = 0;j < 10;j++) {
                printf("%-2c", arr[i][j]);
            }
            printf("\n");
        }
        printf("输入坐标,（形式：x,y）确保输入法处于英文输入法,格式输错了重新输入\n");
        int OK;
        do {
            scanf("%d,%d", &a, &b);
            OK = gps(a, b);
            if (OK == 666) {
                return 666;
            }
        } while (OK == 0);            //判断坐标合法
        if (number % 2 == 1) {
            arr[a][b] = '#';
        }
        else {
            arr[a][b] = 'O';
        }
        if (number >= 9) {
            out = over(a, b, number);
            if (out != 0) {
                out_cg(out);
                return 0;
            }
        }
        if (number == 81) {
            out_cg(3);
            return 0;
        }
        printf("##########################################################################\n");
    } while (1);     //在棋局界面反复执行
}


/*2.2非法坐标
如果是越界输入则提醒“在棋盘上似乎找不到你想下的位置”
       该位置有子则提醒
       该位置是坐标则提醒
       输错了输出0；对了输出1
       推出输入666；；*/
int gps(int a,int b) {
    if (a == 31543 && b == 10086) {
        return 666;
        new();
    }
    else if (a < 0 || a>9 || b < 0 || b>9) {
        printf("在棋盘上似乎找不到你想下的位置\n");
        return 0;
    }
    else if (a == 0 || b == 0) {
        printf("该位置是坐标,不能落子\n");
        return 0;
    }
    else if (arr[a][b] != '@') {
        printf("这个位置已经有棋子了\n");
        return 0;
    }
    return 1;
}
/*2.3判断胜利
* 
输出1表示胜利
输出2表示失败
输出0代表游戏继续
（默认黑子我自己）*/
int over(int a, int b, int number) {
    int out = 0;
    int over_;
        //纵向判断5子
    for (int i = a + 1;i < 10;i++) {
        if (arr[i][b] == arr[a][b]) {
            out++;
        }
        if (arr[i][b] != arr[a][b]) {
            break;
        }
    }
    for (int i = a - 1;i > 0;i--) {
        if (arr[i][b] == arr[a][b]) {
            out++;
        }
        if (arr[i][b] != arr[a][b]) {
            break;
        }
    }
    over_ = over_out_nember(out, number);
    if (over_ != 0) {
        return over_;
    }
    out = 0;
    //横向判断5子
    for (int i = b + 1;i < 10;i++) {
        if (arr[a][i] == arr[a][b]) {
            out++;
        }
        if (arr[a][i] != arr[a][b]) {
            break;
        }
    }
    for (int i = b - 1;i > 0;i--) {
        if (arr[a][i] == arr[a][b]) {
            out++;
        }
        if (arr[a][i] != arr[a][b]) {
            break;
        }
    }
    over_ = over_out_nember(out, number);
    if (over_ != 0) {
        return over_;
    }
    out = 0;
    //斜向判断5子（左上到右下）
    for (int i = a + 1, j = b + 1;i < 10 && j < 10;i++, j++) {
        if (arr[i][j] == arr[a][b]) {
            out++;
        }
        if (arr[i][j] != arr[a][b]) {
            break;
        }
    }
    for (int i = a - 1, j = b - 1;i > 0 && j > 0;i--, j--) {
        if (arr[i][j] == arr[a][b]) {
            out++;
        }
        if (arr[i][j] != arr[a][b]) {
            break;
        }
    }
    over_ = over_out_nember(out, number);
    if (over_ != 0) {
        return over_;
    }
    out = 0;
    //斜向判断5子（右上到左下）
    for (int i = a-1, j = b+1;i > 0 && j < 10;i--, j++) {
        if (arr[i][j] == arr[a][b]) {
            out++;
        }
        if (arr[i][j] != arr[a][b]) {
            break;
        }
    }
    for (int i = a+1, j = b-1;i < 10 && j > 0;i++, j--) {
        if (arr[i][j] == arr[a][b]) {
            out++;
        }
        if (arr[i][j] != arr[a][b]) {
            break;
        }
    }
    over_ = over_out_nember(out, number);
    if (over_ != 0) {
        return over_;
    }
    else {
        return 0;
    }
}


//2.3.2最终判断
int over_out_nember(int out,int number) {            
    if (out >= 4 ) {
        if ((number % 2) == 1) {
            return 1;
        }
        if ((number % 2) == 0){
            return 2;
        }
    }
    return 0;
}

//#########################################################################
//3.结算界面
/*只负责打印胜利或平局
输入1表示胜利
输入2表示失败
输入3表示平局
接收回合数
并给出结果和评价
若NB，不愧是你：NB，不愧是你
  输了：fu,你比较适合做一头猪
  平局：不会真有人无聊吧棋盘填满了吧？？？
  输入任意键返回开始界面*/

void out_cg(int out){
    if (out == 1) {
        printf("你过关\nNB，不愧是你\n");
    }
    if (out == 2) {
        printf("你输了\nfu,你比较适合做一头猪\n");
    }
    if (out == 3) {
        printf("不会真有人无聊吧棋盘填满了吧？？？\n");
    }
    printf("##########################################################################\n");
}
//#########################################################################
//4,非法选项
/*接受信息然后输出固定信息
* 输出格式第0~9次调用：“这是你第n次输入奇怪的东西，n次警告”返回1
        第10次调用：”回家吧孩子，我看你也没想玩五子棋QWQ“返回0
                      然后printf("程序员大人生气的把你送回了家")直接退出程序*/
//设置静态本地变量
int bug(int a) {
    static int out = 0;
    if (out < 9) {
        out++;
        printf("这是你第%d次输入奇怪的东西，%d次警告\n", out, out);
        return 0;
    }
    else {
        printf("回家吧孩子，我看你也没想玩五子棋QWQ\n");
        return -1;
    }
}

//刷新棋盘
void new(void){
    for (int i = 0;i < 10;i++) {
            for (int j = 0;j < 10;j++) {
                if (i == 0) {
                    arr[i][j] = j + '0';
                }
                else if (j == 0) {
                    arr[i][j] = i + '0';
                }
                else {
                    arr[i][j] = '@';
                }
            }
    }
}


