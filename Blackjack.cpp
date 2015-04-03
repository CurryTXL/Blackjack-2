//Name：Blackjack.cpp
//The game Blackjack

#include<iostream> 
#include<cstdlib> 
#include<ctime> 
using namespace std; 

int poker[52];

void Initialize();		//to initialize the poker
int DealCard();		//to deal a random card
void ShowCard(int);		//to show the name of a card
bool CheckInput();		//to check player's input

void Initialize()
{	for (int i=0; i<52; ++i) poker[i]=1;
}	

int DealCard()
{	int k;
	srand(time(NULL));	
	do k = rand() % 52;
	while (poker[k] == 0); 
	poker[k] = 0;
	return k;
}

void ShowCard(int t)
{	switch (t/13) {
		case 0: cout << "spade "; break; 
		case 1: cout << "heart "; break; 
		case 2: cout << "club "; break; 
		default: cout << "diamond "; 
	}
	switch (t%13) {
		case 0: cout << "A  "; break; 
		case 1: cout << "2  "; break; 
		case 2: cout << "3  "; break; 
		case 3: cout << "4  "; break; 
		case 4: cout << "5  "; break; 
		case 5: cout << "6  "; break; 
		case 6: cout << "7  "; break; 
		case 7: cout << "8  "; break; 
		case 8: cout << "9  "; break; 
		case 9: cout << "10  "; break; 
		case 10: cout << "J  "; break; 
		case 11: cout << "Q  "; break; 
		default: cout << "K  "; 
	}
}

bool CheckInput()
{	char choice[2]={'\0'};
	bool flag;
	cin >> choice;
	flag = true;
	while (flag){
		flag = false;
		try{
			if (choice[1] != '\0') throw 1;
			if (choice[0]!='y'&&choice[0]!='Y'&&choice[0]!='n'&&choice[0]!='N') throw 1;
		}
		catch (int){
			cout << "Illegal input. Please input 'y' or 'n': ";
			cin >> choice;
			flag=true;
		}
	}
	if (choice[0] == 'Y' || choice[0] == 'y') return true;
	else return false;
}

int main()
{	int i, j, n, mark[21];		//n is the number of player's cards. mark[21] is because you can have up to 21 cards(4K 4Q 4J 4A 4'2' and 1'3'). 
	double poker_point[52], player_point, computer_point;	
	bool play, deal;
	
	for (i=0; i<52; ++i){		//initialize the point of each card
		if ((i%13)>=0 && (i%13)<=9) poker_point[i] = i%13+1;
		else poker_point[i] = 0.5;
	} 
	
	play = true;
	while (play){
		Initialize();
		
		cout << "Player's turn: " << endl;
		player_point = 0;		//player will get two random cards at the beginning
		mark[0] = DealCard();
		player_point += poker_point[mark[0]];
		mark[1] = DealCard();
		player_point += poker_point[mark[1]];
		i = 1;
		cout << "You get cards: ";
		for (j=0; j<=i; ++j) ShowCard(mark[j]);
		
		cout << endl << "Continue to ask for a card(y/n): ";
		deal = CheckInput();
		while (deal){
			++i;
			mark[i]=DealCard();
			player_point += poker_point[mark[i]];
			cout << "Continue to deal: ";
			for (j=0; j<=i; ++j) ShowCard(mark[j]);
			if (player_point > 21) break;
			cout << endl << "Continue to ask for a card(y/n): ";
			deal = CheckInput();
		}
		n = i+1;
		if (player_point > 21) cout << endl << "Sorry, you lose.";
		else{
			
			cout << endl << "Computer's turn: " << endl;
			computer_point = 0;		//computer will get two random cards at the beginning
			mark[0] = DealCard();
			computer_point += poker_point[mark[0]];
			mark[1] = DealCard();
			computer_point += poker_point[mark[1]];
			i = 1;
			cout << "Computer get cards: ";
			for (j=0; j<=i; ++j) ShowCard(mark[j]);
			
			deal = true;
			if (computer_point > player_point) deal = false;
			while (deal){
				++i;
				mark[i]=DealCard();
				computer_point += poker_point[mark[i]];
				cout << endl << "Continue to deal: ";
				for (j=0; j<=i; ++j) ShowCard(mark[j]);
				if (computer_point > 21 || computer_point > player_point) break;
				if (computer_point == player_point && (i+1) > n) break;
			}
			if (computer_point > 21) cout << endl << "Yes, you win!";
			else cout << endl << "Sorry, you lose.";
		}
		
		cout << endl << "Continue the game(y/n): ";
		play = CheckInput();
		cout << endl;
	}
	
	return 0;	
}
