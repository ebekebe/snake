#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <time.h>
#include <string>
#include <fstream>
#include <cstring>


using namespace std;


bool gameover,menu,gameoff,settings,namein,scooore; // переменные отвечающие за включение и выключение функций
const int w = 20; //длина
const int h = 20; //высота 
int sharp = 0; // отслеживает  положение выбранного пункта меню
int x, y, frutX, frutY, score1, score, ogrL, ogrR, str, recol, l, n; // x, y кординаты головы змеи; frutX, frutY кординаты фрукта;
// score подсчет очков игрока;  score1 используется для подсчета количества цифр в количестве очков
// recol выбраный пункт настроек;  ogrL, ogrR до и после какоц кординаты мы должны выводить пробелы на экран
string name; // ИМЯ ИГРОКА 
string dot; //количество точек между именем и очками в файле, который хранит результаты
int tailX[100], tailY[100]; // запоминает кординаты эллементов хвоста змеи
int ntail=0; // количество эллементов хвоста
int set = 0; // ослеживает положение выбраного пункта настроек
double frametime, prevframetime, dt;
enum eDirection{STOP, ENTER, ESC, LEFT, RIGHT, UP, DOWN}; // директория хранящяя  действия отвечающие на нажатия клавишь
eDirection dir;
int scoresize, namesize; // длина имени и числа очков игрока
int row = 0; //количество строк в файле хранящем резульататы
const int rows = 19;
const char ch = '\n';
char mass[rows][21]; //массив для хранение информации считаной с файла
 

void setup() { // функция запускающаяся в самом начале работы программы 
	menu = false;
	gameoff = false;
	settings = true;
	gameover = true;
	namein = true;
	scooore = true;
	x = w / 2;
	y = h / 2;
	l = x - 2;
	n = x - 1;
	srand(time(NULL));
	frutX = rand() % l+1;
	frutY = rand() % n+1;
	score = 0;
	scoresize = 1;
	dot = "";
	
	
}


void namedrow() { // функция отрисовки меню ввод имени 
	system("cls"); // отчистка экрана 
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < w; j++) {
			if ((i == 0 && j < h) || (i == 2 && j < h))
				cout << "#";
			else if (i == 1 && j==2) {
				cout << "enter your name";
				str = i;
			}
			else if (str = i&& j > 16)
				cout << " ";
			else if (str!=i)
				cout << " ";
		}
		cout << endl;
	}
	getline(cin, name);//вводим имя
	row = 0;

	ifstream chetstrok("score.txt"); //считаем количество строк в файле
	while (!chetstrok.eof())
	{
		if (chetstrok.get() == '\n')
			row = row + 1;
	}
	
		score1 = score;
		while (score1 >= 10) { //считаем количество цифр в количестве очков игрока
			score1 = score1 / 10;
			scoresize = scoresize + 1;
		}
		namesize = name.length(); // считаем длинну имени
		for (int i = 0; i < 16-(scoresize + namesize); i++) {//считаем количество точек между именем и количеством очков
			dot = dot + ".";
		}
	


		

		if (row == 0) {// если в файле нет никакой информации, то мы просто вводим туда 1-ый результат
			ofstream vvodscore;
			vvodscore.open("score.txt", ios::app);
			vvodscore << "# " << name << dot << score << " #" << endl;
			vvodscore.close();
		}
		else if (row <= 18 && row > 0) { //если в файле есть как минимум один результат то мы вводи текущий результат и сортируем относительно других результатов
			ofstream vvodscore;
			vvodscore.open("score.txt", ios::app);
			vvodscore << "# " << name << dot << score << " #" << endl;
			vvodscore.close();



			ifstream sort("score.txt", ios::out);
			for (int r = 0; r < row + 1; r++)
				sort.getline(mass[r], w + 1, ch); //Считываем строки в массив
			sort.close();

			SortMas(row, 21); //сортируем информацию из файла


	
			ofstream del;
			del.open("score.txt", ios::trunc); //отчищаем файл от информации
			del.close();


			ofstream sortirovka;  // записываем отсортированые резульаты в файл
			sortirovka.open("score.txt", ios::app);
			for (int i = 0; (i < row + 1) && (i < 18); i++)
			{
				sortirovka << mass[i] << endl;

			}
			sortirovka.close();
			
		}
		
		row = 0;
		namein = true;
		menu = false;
		
}


void SortMas(int N, int strLen) // функция сортировки  
{
	char buf1[30], buf2[30];
	int sc = 0, nSc = 0, i = strLen - 1, k;

	for (size_t i = 0; i < N; i++)
	{
		printf("%s\n", mass[i]);
	}

	strcpy(buf1, mass[N]);
	while (buf1[i] != '.')
		i--;
	i++;

	while (buf1[i] != ' ')
	{
		nSc = nSc * 10 + (buf1[i++] - '0');
	}

	for (k = N - 1; k >= 0; k--)
	{
		sc = 0;
		i = strLen - 1;
		while (mass[k][i] != '.')
			i--;
		i++;

		while (mass[k][i] != ' ')
		{
			sc = sc * 10 + mass[k][i++] - '0';
		}

		if (nSc > sc)
			strcpy(mass[k + 1], mass[k]);
		else
			break;

	}
	strcpy(mass[k + 1], buf1);
}


void scoredrow() { //функция отрисовки меню результатов
	system("cls");
	row = 0;
	ifstream chetstrok;
	chetstrok.open("score.txt");  // определяем количество строк
	while (!chetstrok.eof())
	{
		if (chetstrok.get() == '\n')
			row = row + 1;
	}
	chetstrok.close();

	for (int i = 0; i < w; i++)
		cout << "#";
	cout << endl;

	if (row == (h - 2)) { //количество строк = максимальнум помещающемся в поле
		ifstream vivodscore; 
		vivodscore.open("score.txt", ios::out);
		for (int r = 0; r < row; r++)
		{
			vivodscore.getline(mass[r], w + 1, ch); //Считываем строки в массив
			cout << mass[r] << endl; //Выводи строку из массива
		}
		vivodscore.close();
	}
	else { // если колчиество строк меньше чем может поместиться в поле

		ifstream vivodscore;
		vivodscore.open("score.txt", ios::out);
		for (int r = 0; r < row; r++)
		{
			vivodscore.getline(mass[r], w + 1, ch);
			cout << mass[r] << endl;
		}
		vivodscore.close();
			for (int i = 0; i <= h-row-3; i++) {
				for (int j = 0; j < w; j++) {
					if ( (j == 0 && i <= h-1 - row ) || (j == w - 1 && i <= h-1 - row ))
						cout << "#";
					else
							cout << " ";
					}
				cout << endl;
			}
		}
		for (int i = 0; i < w; i++)
			cout << "#";
		row = 0;
	}


void scoreinput() { // отслеживаем нажатие клавишь в меню рекордов
	if (_kbhit()) {
		switch (_getch())
		{
		case 27:
			dir = ESC;
			break;
		}
	}
}

void scorelogic() {  // выполняем действия присвоенные определенным клавишам
	switch (dir) {
	case ESC:
		scooore = true;
		menu = false;
		break;
	}
}


void setdrow() { // отрисовка меню настроек
	system("cls");
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if ((i == 0 && j < h) || (i == w - 1 && j < h) || (j == 0 && i < w) || (j == h - 1 && i < w))
				cout << "#";	
			else if (i == 3 && j == x - 7) {
				if (set == 0) {
					cout << ">through wall<";  
					ogrL = x - 7;
					ogrR = x + 6;
					str = i;
				}
				else {
					cout << " through wall";
					ogrL = x - 7;
					ogrR = x + 5;
					str = i;
				}
			}
			else if (i == 5 && j == x - 7) {
				if (set == 1) {
					cout << ">wall of death<";   
					ogrL = x - 7;
					ogrR = x + 7;
					str = i;
				}
				else {
					cout << " wall of death";
					ogrL = x - 7;
					ogrR = x + 6;
					str = i;
				}
			}
			else if (i == str && (j<ogrL || j>ogrR))
				cout << " ";
			else if (i != str)
				cout << " ";
		}
		cout << endl;
	}
}


void setinput() {    // отслеживаем нажатие клавишь в меню рекордов
	if (_kbhit()) {
		switch (_getch())
		{
		case 72:
			dir = UP;
			break;
		case 80:
			dir = DOWN;
			break;
		case 13:
			dir = ENTER;
			break;
		case 27:
			dir = ESC;
			break;
		}
	}
}


void setlogic() { // выполняем действия присвоенные определенным клавишам
	if (set == 0) {
		switch (dir) {
		case UP:
			set = 1;
			dir = STOP;
			break;
		case DOWN:
			set = 1;
			dir = STOP;
			break;
		}
	}
	else if (set == 1) {
		switch (dir) {
		case UP:
			set = 0;
			dir = STOP;
			break;
		case DOWN:
			set = 0;
			dir = STOP;
			break;
		}
	}
	switch (dir) {
	case ENTER:
		if (set == 0) {
			recol = 0;
			settings = true;
		}
		if (set == 1) {
			recol = 1;
			settings = true;
		}
		dir = STOP;
		break;
	case ESC:
		settings = true;
		break;
	}
}


void drowmenu() { //отрисвока меню
	system("cls");
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if ((i == 0 && j < h) || (i == w - 1 && j < h) || (j == 0 && i < w) || (j == h - 1 && i < w))
				cout << "#";
			else if (i == 3 && j == x - 4) {
				if (sharp == 0) {
					cout << ">start<";
					ogrL = x - 4;
					ogrR = x + 2;
					str = i;
				}
				else  {
					cout << " start";
					ogrL = x - 4;
					ogrR = x + 1;
					str = i;
				}
			}
			else if (i == 5 && j == x - 5) {
				if (sharp == 1) {
					cout << ">settings<";
					ogrL = x - 5;
					ogrR = x + 4;
					str = i;
				}
				else {
					cout << " settings";
					ogrL = x - 5;
					ogrR = x + 3;
					str = i;
				}		
			}
			else if (i == 7 && j == x - 4) {
				if (sharp == 2) {
					cout << ">score<";
					ogrL = x - 4;
					ogrR = x + 2;
					str = i;
				}
				else {
					cout << " score";
					ogrL = x - 4;
					ogrR = x + 1;
					str = i;
				}
			}
			else if (i == 9 && j == x - 4) {
				if (sharp == 3) {
					cout << ">close<";
					ogrL = x - 4;
					ogrR = x + 2;
					str = i;
				}
				else {
					cout << " close";
					ogrL = x - 4;
					ogrR = x + 1;
					str = i;
				}
			}
			else if (i == str && (j<ogrL || j>ogrR))
				cout << " ";
			else if(i!=str)
				cout << " ";
		}
		cout << endl;
	}
}


void inputmenu() { // отслеживаем нажатие клавишь в меню рекордов
	if (_kbhit()) {
		switch (_getch())
		{
		case 72:
			dir = UP;
			break;
		case 80:
			dir = DOWN;
			break;
		case 13:
			dir = ENTER;
			break;
		}
	}
}


void logicmenu() { // выполняем действия присвоенные определенным клавишам
	if (sharp == 0) {
		switch (dir){
		case UP:
			sharp = 3;
			dir = STOP;
			break;
		case DOWN:
			sharp = 1;
			dir = STOP;
			break;
		}
	}
	else if (sharp == 1) {
			switch (dir) {
			case UP:
				sharp = 0;
				dir = STOP;
				break;
			case DOWN:
				sharp = 2;
				dir = STOP;
				break;
		}
	}
	else if (sharp == 2) {
		switch (dir) {
		case UP:
			sharp = 1;
			dir = STOP;
			break;
		case DOWN:
			sharp = 3;
			dir = STOP;
			break;
		}
	}
	else if (sharp == 3) {
		switch (dir) {
		case UP:
			sharp = 2;
			dir = STOP;
			break;
		case DOWN:
			sharp = 0;
			dir = STOP;
			break;
		}
	}
	switch(dir) {
		case ENTER:
			if (sharp == 3) {
				menu = true;
				gameover = true;
				gameoff = true;
				settings = true;
			}
			if (sharp == 1) {
				menu = true;
				gameover = true;
				settings = false;
			}
			if (sharp == 0) {
				menu = true;
				settings = true;
				gameover = false;
			}
			if (sharp == 2) {
				menu = true;
				scooore = false;
			}
			dir = STOP;
			break;
	}
}


void drow() { // отрисовка игрового меню
	system("cls");
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if ((i == 0 && j < h) || (i == w - 1 && j < h) || (j == 0 && i < w) || (j == h - 1 && i < w))
					cout << "#";
				else if (i == y && j == x)
					cout << "0";
				else if (i == frutY && j == frutX)
					cout << "F";
				else {
					bool print = false;
					for (int k = 0; k < ntail; k++) {
						if (tailX[k] == j && tailY[k] == i) {
							print = true;
							cout << "o";
						}
					}
					if (!print)
						cout << " ";
				}
			}
			cout << endl;
		}
		cout << "score: " << score << endl;
	

	}


void input() {  // отслеживаем нажатие клавишь в меню рекордов
	if (_kbhit()) {
		switch (_getch())
		{
		case 75:
			dir = LEFT;
			break;
		case 72:
			dir = UP;
			break;
		case 77:
			dir = RIGHT;
			break;
		case 80:
			dir = DOWN;
			break;
		case 13:
			dir = ENTER;
			break;
		case 27:
			dir = ESC;
			break;
		}
	}
}


void logic() {   // выполняем действия присвоенные определенным клавишам
	int prevx = tailX[0];   // алгоритм запоминания кординат для хвоста змеи
	int prevy = tailY[0];
	int prev2x, prev2y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < ntail; i++) {
		prev2x = tailX[i];
		prev2y = tailY[i];
		tailX[i] = prevx;
		tailY[i] = prevy;
		prevx = prev2x;
		prevy = prev2y;
	}
		switch (dir) // смещение кординат головы змеи по нажатию клавишь
		{
		case LEFT:
			x = x - 1;
			break;
		case RIGHT:
			x = x + 1;
			break;
		case UP:
			y = y - 1;
			break;
		case DOWN:
			y = y + 1;
			break;
		case ESC: // выход в меню без записи результатов
			gameover = true;
			menu = false;
			break;
		}
		if (recol == 1) { // проигрышь от столкновения ссо стеной
			if (x > w - 2 || x<1 || y>h - 2 || y < 1) {
				gameover = true;
				namein = false;
			}
		}
		else if(recol == 0){ // проход сквозь стены
			if (x >= w - 1)
				x = 1;
			else if (x < 1)
				x = w - 2;
			if (y >= h - 1)
				y = 1;
			else if (y < 1)
				y = h - 2;
		}


		for (int i = 0; i < ntail; i++) { // проигрышь при столкновении с эллементом хвоста
			if (tailX[i] == x && tailY[i] == y) {
				gameover = true;
				namein = false;
			}
		}
		if (x == frutX&&y == frutY) { // отрисовка нвого фрукта
			score += 10;
			srand(time(NULL));
			frutX = rand() % l + 1;
			frutY = rand() % n + 1;
			for (int j = 0; j < ntail; j++) {//новые кординаты фрукта если старые совпадают с кординатами хвоста змеи
				for (int i = 0; i < ntail; i++) {
					while (tailX[i] == frutX && tailY[i] == frutY) {
						frutX = rand() % l + 1;
						frutY = rand() % n + 1;
					}
				}
			}
			ntail++;
		}
}


int main() { // главное тело программы
	while (!gameoff) {
		setup();
		while (!menu) { //  меню
			inputmenu();
			prevframetime = frametime;
			frametime = clock() / CLOCKS_PER_SEC;
			dt += frametime - prevframetime;
			if (dt > 0.001)
			{
				logicmenu();
				drowmenu();
				dt = 0;
			}
		}
		while (!settings) { // настройка
			setinput();
			prevframetime = frametime;
			frametime = clock() / CLOCKS_PER_SEC;
			dt += frametime - prevframetime;
			if (dt > 0.001)
			{
				setlogic();
				setdrow();
				dt = 0;
			}
		}
		while (!gameover) { // игровое меню
			input();
			prevframetime = frametime;
			frametime = clock() / CLOCKS_PER_SEC;
			dt += frametime - prevframetime;
			if (dt > 0.0001)
			{
				logic();
				drow();
				dt = 0;
			}
		}
		while (!namein) { // меню ввод имени
			prevframetime = frametime;
			frametime = clock() / CLOCKS_PER_SEC;
			dt += frametime - prevframetime;
			if (dt > 0.0001)
			{
				namedrow();
				dt = 0;
			}
		}
			while (!scooore) { // меню рекордов
				scoreinput();
				prevframetime = frametime;
				frametime = clock() / CLOCKS_PER_SEC;
				dt += frametime - prevframetime;
				if (dt > 0.0001)
				{
					scorelogic();
					scoredrow();
					dt = 0;
				}
			}
		for (int i = 0; i < 100; i++) { // обнуление кординат хвоста змеи 
			tailX[i] = -1;
			tailY[i] = -1;
		}
		ntail = 0;
		sharp = 0;
	}
	system("cls");
		return 0;
	}