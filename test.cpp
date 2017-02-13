#include<math.h>
#include<graphics.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#include "mmsystem.h"

#pragma comment(lib, "Winmm.lib")

int stone_x1 = 350, stone_y1 = -400, stone_x2, stone_y2, bird_x = 175, bird_y = 300, i = 0, score = 0, gover;
IMAGE stone_up1, stone_down1, stone_down2, stone_up2, score1[10], score2[10], bird1[4], bird2[4], background, gameover1, gameover2, beforegame, end;

void column();
void bird();
void load();
void judgement();
void gameover();
void start();
void getscore();

void start() {
	putimage(0, 0, &beforegame);
	char begin;

	begin = getch();
	if (begin == ' ') {
		gover = 1;
	}
}
void main() {
	initgraph(350, 600);

	HWND hwnd = GetHWnd();

	// 窗口标题
	SetWindowText(hwnd, L"Flappy Bird BY Yuhao");

	// 播放背景音乐
	mciSendString(L"open \"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sounds\\background.mp3\" alias music ", NULL, 0, NULL);
	mciSendString(L"play music", NULL, 0, NULL);

	load();
	start();
	srand((unsigned)time(NULL));
	BeginBatchDraw();
	
	putimage(0, 0, &background);
	bird();
	putimage(270, 0, &score1[0], NOTSRCERASE);
	putimage(270, 0, &score2[0], SRCINVERT);
	while (gover) {

		putimage(0, 0, &background);	

		column();
		bird();
		judgement();
		getscore();
		i++;
		if (i == 3) {
			i = 0;
		}
		FlushBatchDraw();
		
		if (gover == 0) {
			gameover();
		}
		Sleep(30);
	}

	Sleep(1000);
	closegraph();
}

// 载入所有图片
void load() {
	
	// 背景
	loadimage(&background, L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\backgroundfd.jpg");
	
	// 柱子
	loadimage(&stone_up1, L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\stone_up1.gif");
	loadimage(&stone_down1, L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\stone_down1.gif");
	loadimage(&stone_down2, L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\stone_down2.gif");
	loadimage(&stone_up2, L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\stone_up2.gif");	
	loadimage(&stone_up2, L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\stone_up2.gif");
	
	// 鸟
	loadimage(&bird1[0], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\bird1-1.gif");
	loadimage(&bird2[0], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\bird1-2.gif");
	loadimage(&bird1[1], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\bird3-1.gif");
	loadimage(&bird2[1], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\bird3-2.gif");
	loadimage(&bird1[2], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\bird2-1.gif");
	loadimage(&bird2[2], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\bird2-2.gif");
	loadimage(&bird1[3], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\bird4-1.gif");
	loadimage(&bird2[3], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\bird4-2.gif");
	
	// 分数
	loadimage(&score1[0], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\0_1.jpg");
	loadimage(&score1[1], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\1_1.jpg");
	loadimage(&score1[2], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\2_1.jpg");
	loadimage(&score1[3], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\3_1.jpg");
	loadimage(&score1[4], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\4_1.jpg");
	loadimage(&score1[5], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\5_1.jpg");
	loadimage(&score1[6], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\6_1.jpg");
	loadimage(&score1[7], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\7_1.jpg");
	loadimage(&score1[8], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\8_1.jpg");
	loadimage(&score1[9], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\9_1.jpg");
	loadimage(&score2[0], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\0_2.jpg");
	loadimage(&score2[1], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\1_2.jpg");
	loadimage(&score2[2], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\2_2.jpg");
	loadimage(&score2[3], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\3_2.jpg");
	loadimage(&score2[4], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\4_2.jpg");
	loadimage(&score2[5], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\5_2.jpg");
	loadimage(&score2[6], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\6_2.jpg");
	loadimage(&score2[7], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\7_2.jpg");
	loadimage(&score2[8], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\8_2.jpg");
	loadimage(&score2[9], L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\9_2.jpg");
	// 游戏结束
	loadimage(&gameover1, L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\gameover1.gif");
	loadimage(&gameover2, L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\gameover2.gif");
	loadimage(&beforegame, L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\beforegame.jpg");
	loadimage(&end, L"D:\\Program\\C\\Learn\\FlappyBird\\FlappyBird\\sourcefile\\atlast.jpg");
}

// 控制柱子
void column() {
	
	if (stone_x1 > 0 && stone_x1 <= 350) {				// 一根柱子

		putimage(stone_x1, stone_y1, &stone_up2, NOTSRCERASE);
		putimage(stone_x1, stone_y1, &stone_up1, SRCINVERT);

		putimage(stone_x1, 800 + stone_y1, &stone_down2, NOTSRCERASE);
		putimage(stone_x1, 800 + stone_y1, &stone_down1, SRCINVERT);

		stone_x1--;
	}
	else if (stone_x1 <= 0 && stone_x1 >= -140) {		// 两根柱子
		if (stone_x1 == 0) {
			stone_y2 = (-rand() % 400 - 200);			// 生成第二根柱子，随机生成stone_y2位置
			stone_x2 = stone_x1 + 350;					// 控制两根柱子的间距为350
		}
		putimage(stone_x1, stone_y1, &stone_up2, NOTSRCERASE);
		putimage(stone_x1, stone_y1, &stone_up1, SRCINVERT);

		putimage(stone_x1, 800 + stone_y1, &stone_down2, NOTSRCERASE);
		putimage(stone_x1, 800 + stone_y1, &stone_down1, SRCINVERT);

		putimage(stone_x2, stone_y2, &stone_up2, NOTSRCERASE);
		putimage(stone_x2, stone_y2, &stone_up1, SRCINVERT);

		putimage(stone_x2, 800 + stone_y2, &stone_down2, NOTSRCERASE);
		putimage(stone_x2, 800 + stone_y2, &stone_down1, SRCINVERT);

		stone_x1--;
		stone_x2--;
		if (stone_x1 == -140) {
			stone_x1 = stone_x2;
			stone_y1 = stone_y2;
		}
	}
}

// 控制鸟的飞行
void bird() {
	putimage(bird_x, bird_y, &bird1[i], NOTSRCERASE);
	putimage(bird_x, bird_y, &bird2[i], SRCINVERT);	

	// 鸟自动下降
	bird_y = bird_y + 3;
	char con;
	
	// 控制鸟的上升
	if (kbhit()) {
		con = getch();
		if (con = ' ') {
			// 控制平滑上升
			for (int j = 0; j < 8; j++) {
				bird_y = bird_y - 10;
			}
		}
	}	
}

void judgement() {
	if ((bird_x <= (stone_x1 + 140) && bird_x >= (stone_x1 - 30)) && (bird_y <= (stone_y1 + 600) || bird_y >= (stone_y1 + 776))) {
		gover = 0;
	}
	else if(bird_x == stone_x1 +141){
		score++;
	}
}

void gameover() {
	
	while (bird_y <= 600) {
		putimage(0, 0, &background);

		putimage(stone_x1, stone_y1, &stone_up2, NOTSRCERASE);
		putimage(stone_x1, stone_y1, &stone_up1, SRCINVERT);

		putimage(stone_x1, 800 + stone_y1, &stone_down2, NOTSRCERASE);
		putimage(stone_x1, 800 + stone_y1, &stone_down1, SRCINVERT);

		if (stone_x1 <= 0 && stone_x1 >= -140) {
			putimage(stone_x2, stone_y2, &stone_up2, NOTSRCERASE);
			putimage(stone_x2, stone_y2, &stone_up1, SRCINVERT);

			putimage(stone_x2, 800 + stone_y2, &stone_down2, NOTSRCERASE);
			putimage(stone_x2, 800 + stone_y2, &stone_down1, SRCINVERT);
		}
		
		getscore();

		putimage(bird_x, bird_y, &bird1[3], NOTSRCERASE);
		putimage(bird_x, bird_y, &bird2[3], SRCINVERT);

		bird_y += 2;
		if (bird_y >= 600) {
			putimage(0, 0, &end);
		}
		FlushBatchDraw();
		Sleep(10);

		
	}
}

void getscore() {
	if (score <= 10) {
		putimage(270, 0, &score1[score], NOTSRCERASE);
		putimage(270, 0, &score2[score], SRCINVERT);
	}
	else {
		putimage(270, 0, &score1[score], NOTSRCERASE);
		putimage(270, 0, &score2[score], SRCINVERT);
		putimage(240, 0, &score1[score / 10], NOTSRCERASE);
		putimage(240, 0, &score2[score / 10], SRCINVERT);
	}
}