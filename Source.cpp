//filename: Blackjack
//usage: a game
//coder: sunflower

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int player();
int produce(int number[]);
void show(int number[]);
char judge();
double sum(int number[]);
void computer(double number[]);

//the main program
int main(){
	char YN;

	srand(time(NULL));

	cout << "player time:" << endl;
	player();		//player time begins
	cout << "\nDo you want to continue?(y/n)\t";
	YN = judge();	
	if (YN == 'Y' || YN == 'y')
		main();
	else return 0;

}

//the player time
int player(){
	int numberOfPlayer[21] = { 0 }, times = 2;
	double resultOfPlayer[2] = { 0 };
	char choose;
	bool flag(true);

	cout << "player gets :\t";
	numberOfPlayer[0] = produce(numberOfPlayer);	//get the first number
	numberOfPlayer[1] = produce(numberOfPlayer);	//get the second number
	show(numberOfPlayer);			//show what player gets out
	do {
		cout << "Do you want another one?(y/n)\t";
		choose = judge();
		if (choose == 'Y' || choose == 'y'){
			numberOfPlayer[times] = produce(numberOfPlayer);	//get next number 
			resultOfPlayer[1] = ++times;				//get the number of cards player gets
			resultOfPlayer[0] = sum(numberOfPlayer);	//calculate the score player gets
			cout << "player gets:\t";
			show(numberOfPlayer);
			if (resultOfPlayer[0] > 21)			//judge whether player lose
				flag = false;
		}
		else{
			computer(resultOfPlayer);		//computer time begins
			return 0;
		}
	} while (flag);
	cout << "\nplayer lose!";
	return 0;

}

//to get a random number
int produce(int number[]){
	int temp, i = 0;
	temp = (rand() % 4 + 1) * 100 + rand() % 13 + 1;		//to get a number which stands for a card
	for (i = 0; number[i] != 0; ++i){					//to prevent any two cards from being same
		if (temp == number[i]){
			temp = (rand() % 4 + 1) * 100 + rand() % 13 + 1;
			i = 0;
		}
	}
	return temp;
}

//to show what cards player or computer gets
void show(int number[]){
	int number1, number2, i = 0;

	while (number[i] != 0){
		number1 = number[i] / 100;				//to translate the random number to two meaningful numbers
		number2 = number[i] - number1 * 100;		
		switch (number1){
		case 1: cout << "heart ";
			break;
		case 2: cout << "diamond ";
			break;
		case 3: cout << "spade ";
			break;
		case 4: cout << "club ";
			break;
		}
		switch (number2){
		case 1: cout << "A" << "\t";
			break;
		case 11: cout << "J" << "\t";
			break;
		case 12: cout << "Q" << "\t";
			break;
		case 13: cout << "K" << "\t";
			break;
		default: cout << number2 << "\t";
 		}
		++i;
	}
	cout << endl;
}

//to judge whether the input of player is right and return the right input
char judge(){
	char choose;

	cin >> choose;
	if (cin.fail() || (choose != 'y' && choose != 'Y' && choose != 'N' && choose != 'n')){
		cout << "please input right value(y/n):";
		cin.sync();
		cin.clear();
		return judge();
	}
	else return choose;
}

//to calculate the score of player and computer
double sum(int number[]){
	int i = 0;
	double theSum = 0.0;
	while (number[i] != 0){
		if (number[i] % 100 > 10) theSum += 0.5;	//to translate the random number into a meaningful number
		else theSum += number[i] % 100;
		++i;
	}
	return theSum;
}

//the computer time
void computer(double number[]){
	double SUM = number[0], TIMES = number[1];
	int numberOfComputer[21] = { 0 }, times = 2;

	cout << "\ncomputer time:\t";
	numberOfComputer[0] = produce(numberOfComputer);		//it's same to player 
	numberOfComputer[1] = produce(numberOfComputer);
	show(numberOfComputer);
	while (sum(numberOfComputer) < SUM){					//if computer hasn't win, then gets another card.
		numberOfComputer[times] = produce(numberOfComputer);
		++times;
		cout << "computer gets:\t";
		show(numberOfComputer);
	}
	if (sum(numberOfComputer) > 21)				//if the score of computer has greater than 21, then player win.
		cout << "player win!";
	else cout << "player lost!";
}