/*
Michael Henson
CSC215
Code Breaking 2
*/

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>

using namespace std;

int MAX_WRONG = 7; //sets up how many guesses can be incorrect

int main()
{
	//makes full screen when activated
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);

	//sets up color scheme and title
	system("color 0A");
	system("title Code Breaking Sim V. II");

	bool playAgain = false; //sets up boolean for playing again
	bool checkAgain = false; //sets up boolean for error catch
	char guess;
	char quit = '~';
	string fName; //first name is asked
	string lName; //last name is asked

	int simTries = 0; //variable for simulation tries. initial value placed outside of
						//loop to not effect actual runs

	//asks for player's name
	cout << "Hello recruit... Before we begin I must ask your name.\n";
	cout << "Enter your first name: "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //blue text
	cin >> fName; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //green text
	cout << "Now your last name please: "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //blue text
	cin >> lName; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //green text
	system("cls");
	cout << "Great... Thanks " << fName << "... Now we can begin!\n";
	system("pause");

	//Just some effect here
	for (int r = 0; r < 250; ++r)
	{
		cout << "*\n";
	}

	system("cls");
	//Greets user and breaks down the rules
	cout << "Welcome to Code Breakers Version II potential agent " << lName;
	cout << "\n\nThe rules are these... You will be given three words.\n";
	cout << "You must guess these words. With every correct word or incorrect\n";
	cout << "guess the amount you can get incorrect will go down. You use\n";
	cout << "up all your chances and the simulation ends. However your chances\n";
	cout << "go up if you keep failing the simulation and restarting rather than\n";
	cout << "quiting. You will not be given any hints. You must guess each letter.\n";
	cout << "You can guess multiple letters at once. You will be told\n";
	cout << "if you are correct or wrong for each letter guessed. If you want to\n";
	cout << "quit press the '~' key... Good luck " << fName << " " << lName << "\n\n";
	system("pause");

	do
	{
		//sets up just one wrong guess if max-wrong is 0 when program restarts
		if (MAX_WRONG == 0)
		{
			MAX_WRONG = 1;
		}

		++simTries; //adds one for each time the simulation has been run
		system("cls"); //clears console for more clean appearance

		//setup
		vector<string> words; //collection of usable words
		words.push_back("ASSET");
		words.push_back("AGENT");
		words.push_back("BAGMAN");
		words.push_back("BLOWN");
		words.push_back("BURNED");
		words.push_back("FLOATER");
		words.push_back("HANDLER");
		words.push_back("COMPROMISED");
		words.push_back("INFILTRATION");
		words.push_back("COUNTERINTELLIGENCE");

		//starts for loop for 3 words

		for (int p = 1; p < 4; ++p)
		{
			//sets up just one wrong guess if max-wrong is 0 when program restarts
			if (MAX_WRONG == 0)
			{
				MAX_WRONG = 1;
			}

			srand(static_cast<unsigned int>(time(0))); //sets up randomizer
			random_shuffle(words.begin(), words.end()); //randomizes word each time it loads up

			const string THE_WORD = words[0]; //word to guess
			int wrong = 0; //starting number of incorrect guesses
			string soFar(THE_WORD.size(), '-'); //letters of the word guessed so far
			string used = ""; //all letters guessed so far

			system("cls"); //clears console for more clean appearance

			//reminds user how to quit
			cout << "Remember if you want to quit you can press '~'\n";
			cout << "This is simulation number " << simTries << ".  Have fun!\n";
			cout << "Here's word number " << p << ".\n";

			//main loop
			while ((wrong < MAX_WRONG) && (soFar != THE_WORD))
			{
				cout << "\nYou have " << (MAX_WRONG - wrong);
				cout << " incorrect guess left " << fName << " and\n";
				cout << "you've used the following letters:\n" << used << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //blue text
				cout << "\nSo far, the word is:\n" << soFar << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //green text

				cout << "\n\nEnter your guess: "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //blue text
				cin >> guess; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //green text
				guess = toupper(guess); //makes guessed letter uppercase since words are in uppercase

				//tells user the letter has already been guessed
				while ((used.find(guess) != string::npos) && (guess != '~'))
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //red text
					cout << "\n\nYou've already guessed " << guess << fName << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //green text
					cout << "Enter your guess: "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //blue text
					cin >> guess; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //green text
					guess = toupper(guess);
				}

				used += guess;

				//if guess is part of word this if statement appends to current word count
				//as well as to used letters
				if (THE_WORD.find(guess) != string::npos)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
					cout << "\n\nThat's right! " << guess << " is in the word " << fName << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);

					for (int i = 0; i < THE_WORD.length(); ++i)
					{
						if (THE_WORD[i] == guess)
						{
							soFar[i] = guess;
						}
					}
				}

				//sets up quit command
				else if (guess == '~')
				{
					break;
				}

				//If guess isn't part of word this adds to the amount wrong as well as
				//informs player it isn't part of the word
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					cout << "\n\nSorry, " << fName << " but " << guess << " isn't in the word.\n";
					++wrong;
				}
			}

			//shuts down program if all guesses are either wrong or the word is guessed
			if (wrong == MAX_WRONG)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //sets text color to red
				cout << "\nERROR SIMULATION FAILED!\n\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //resets color to green
				p = 4;
				++MAX_WRONG;
			}

			//what to do if quitting
			else if (guess == '~')
			{
				p = 4;
				cout << "\nThanks for trying.\n";
				system("pause");
				break;
			}

			else //lets player know they got the word
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //sets color to blue
				cout << "\nCongratulations " << fName;
				cout << "\nYou guessed it!\n\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //resets color to green
				--MAX_WRONG;
			}
			cout << "\nThe word was " << THE_WORD << "\n\n";
			system("pause");
		}

		do //loop for error catching
		{
			cout << "\n\nWould you like to go again? Y/N: "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //blue text
			cin >> guess; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //green text
			if (guess == 'Y' || guess == 'y')
			{
				//replay program
				playAgain = true;
				//leave current loop
				checkAgain = false;
			}
			else if (guess == 'N' || guess == 'n')
			{
				cout << "\nPlease come play again sometime " << fName << " " << lName << endl;
				system("pause");
				//leave program
				playAgain = false;
				//leave current loop
				checkAgain = false;
			}
			else
			{
				//error catcher
				cout << "\nInvalid response. Please enter a valid response.\n";
				//resets current loop for proper guess
				checkAgain = true;
			}
		} while (checkAgain); //boolean for this do while loop

	} while (playAgain); //boolean to replay program
	return 0;
}
