#include<iostream>
#include<fstream>
using namespace std;

void PauseScreen()
{
	cout << "\n\n" << " ";
	system("pause");
}


class BankAccount
{
	int AccNumber;
	char Accname[50];
	int deposit;
	char choice;
public:
	void MainMenu();
	void CreateNewAcc();
	void depinAcc(int);
	void drawinAcc(int);
	void ReturnAccData();
	int ReturnAccNum();
	int retdeposit();
	void ExitMenu();
};

void BankAccount::MainMenu()
{
	system("cls");
	cout << "______________________________________________________________" << endl << endl;
	cout << "  Welcome! Choose one of the following: " << endl;
	cout << "______________________________________________________________" << endl;

	cout << "\n 1. New Account";
	cout << "\n 2. Deposit or Withdraw";
	cout << "\n 3. Search For Account";
	cout << "\n 4. Show All Accounts";
	cout << "\n 5. EXIT";
	cout << "\n______________________________________________________________" << endl;
	cout << "\n\n - Select Your Option: ";
}

void BankAccount::CreateNewAcc()
{
	system("CLS");
	cout << "______________________________________________________________" << endl << endl;
	cout << "\t\t  Create New Account . . .  " << endl;
	cout << "______________________________________________________________" << endl;

	cout << "\n- Enter the Account Number: ";
	cin >> AccNumber;
	cout << "\n- Enter the name of the account owner: ";
	cin.ignore();
	cin.getline(Accname, sizeof(Accname));
	cout << "\n- Do you want to deposit an amount? [Y|N]: ";
	cin >> choice;
	if (choice == 'y' || choice == 'Y')
	{
		cout << "- Enter an amount in Egp: ";
		cin >> deposit;
	}
	else deposit = 0;
	PauseScreen();
}

void BankAccount::depinAcc(int x)
{
	deposit += x; // Balance of Account "deposit" = The current amount + what is added to it
}

void BankAccount::drawinAcc(int x)
{
	deposit -= x; // Balance of Account "deposit" = The current amount - what is withdrawn from it
}

void BankAccount::ReturnAccData() // To Return All Account Data such as its Number, Account owner name, etc ...
{
	cout << "\n - Account Number: " << AccNumber << "\t||\t" << "- Name: " << Accname << "\t\t||\t" << " - Balance: " << deposit << " EGP" << endl;
}


int BankAccount::ReturnAccNum() // To Return Account Number
{
	return AccNumber;
}

int BankAccount::retdeposit() // To Returns the current balance in the account
{
	return deposit;
}
void BankAccount::ExitMenu()
{
	system("cls");
	cout << "\n\n________________________________________________________________________________________________________________________" << endl << endl;
	cout << "\t\t\t\t	  File Organization Project . . .  " << endl;
	cout << "\t\t\t\t	  By: Ahmed Yousef - Nizar Esmat" << endl;
	cout << "________________________________________________________________________________________________________________________" << endl;

	cout << "\n________________________________________________________________________________________________________________________" << endl << endl;
	cout << "\t\t\t\t	     Have a good day . . .  " << endl;
	cout << "________________________________________________________________________________________________________________________\n" << endl << endl;
}




// File Handling Functions

//		*********** Function of writing the account in the File ***********
void WriteAccount()
{
	BankAccount account;
	ofstream outFile;
	outFile.open("FOProject.txt", ios::app);
	account.CreateNewAcc();
	outFile.write(reinterpret_cast<char*> (&account), sizeof(account));
	outFile.close();
}


//		*********** Function of searching for an account in the File ***********
void SearchForAcc(int n)
{
	BankAccount account;
	bool flag = false;
	ifstream inFile;
	inFile.open("FOProject.txt");
	if (!inFile)
	{
		cout << "\n- Couldn't open file";
	}
	system("cls");
	cout << "______________________________________________________________" << endl << endl;
	cout << "\t\t Account Details . . .  " << endl;
	cout << "______________________________________________________________" << endl << endl;

	while (!inFile.eof() && flag == false)
	{
		inFile.read(reinterpret_cast<char*> (&account), sizeof(account));
		if (account.ReturnAccNum() == n)
		{
			account.ReturnAccData();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n\n- Account number does not exist";

	PauseScreen();
}

//		*********** Function to display all existing accounts ***********
void ShowAllAcc()
{
	system("CLS");
	BankAccount account;
	ifstream inFile;
	inFile.open("FOProject.txt");
	if (!inFile)
	{
		cout << "\n- Couldn't open file";
		PauseScreen();
	}
	cout << "\t\t\t______________________________________________________________" << endl << endl;
	cout << "\t\t\t		 All accounts in the system . . .  " << endl;
	cout << "\t\t\t______________________________________________________________" << endl << endl;
	while (inFile.read(reinterpret_cast<char*> (&account), sizeof(account)))
	{
		account.ReturnAccData();
	}
	inFile.close();
	PauseScreen();
}

//		*********** Function to deposit amount in an account ***********
void deposit(int n)
{
	BankAccount account;
	fstream File;
	int Amount;
	bool flag = false;
	File.open("FOProject.txt", ios::in | ios::out);
	if (!File)
	{
		cout << "\n- Couldn't open file";
		PauseScreen();
	}
	while (!File.eof() && flag == false)
	{
		File.read(reinterpret_cast<char*> (&account), sizeof(account));

		if (account.ReturnAccNum() == n)
		{
			account.ReturnAccData();
			cout << "\n\n- Enter amount to deposit in account: ";
			cin >> Amount;
			account.depinAcc(Amount); // depinacc = deposit+amount;
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&account), sizeof(account));
			cout << "\n- You deposited " << Amount << " EGP in your account." << endl;
			cout << "- Your new balance is: " << account.retdeposit() << endl;
			flag = true;
		}
	}
	File.close();
	if (flag == false)
		cout << "\n\n- Account number does not exist";
	PauseScreen();
}

//		*********** Function to withdrawal amount from an account ***********

void withdraw(int n)
{
	int Amount, num, chkbal;
	bool flag = false;
	BankAccount account;
	fstream File;
	File.open("FOProject.txt", ios::in | ios::out);
	if (!File)
	{
		cout << "\n- Couldn't open file";
		return;
	}
	while (!File.eof() && flag == false)
	{
		File.read(reinterpret_cast<char*> (&account), sizeof(account));
		if (account.ReturnAccNum() == n)
		{
			account.ReturnAccData();
			cout << "\n\n- Enter amount to withdrawal: ";
			cin >> Amount;
			chkbal = account.retdeposit() - Amount;
			if (chkbal < 0)
				cout << "Not enough balance for withdrawal.";
			else
				account.drawinAcc(Amount); // drawinacc = deposit - amount;
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&account), sizeof(account));
			cout << "\n- You withdrew " << Amount << " EGP." << endl;
			cout << "- Your remaining balance is: " << account.retdeposit() << endl;
			flag = true;

		}
	}
	File.close();
	if (flag == false)
		cout << "\n\n- Account number does not exist";
	PauseScreen();
}

//		*********** End Of File Functions ***********



int main()
{
	BankAccount account;
	int choice;
	int num;
	do
	{
		account.MainMenu();
		cin >> choice;

		switch (choice)
		{
		case 1:
			WriteAccount();
			break;

		case 2:
			do
			{
				system("CLS");
				cout << "______________________________________________________________" << endl << endl;
				cout << "\t\t  Select a Transaction . . .  " << endl;
				cout << "______________________________________________________________" << endl;

				cout << "\n- 1. Deposit";
				cout << "\n- 2. Withdrawal";
				cout << "\n- 3. Back to Main Menu";
				cout << "\n\n- Select a Transaction: ";

				cin >> choice;
				switch (choice)
				{
				case 1:
					system("cls");
					cout << "______________________________________________________________" << endl << endl;
					cout << "\t\t  Deposit Transaction . . .  " << endl;
					cout << "______________________________________________________________" << endl;

					cout << "\n- Enter The account Number: ";
					cin >> num;
					deposit(num);
					break;
				case 2:
					system("CLS");
					cout << "______________________________________________________________" << endl << endl;
					cout << "\t\t  Withdrawal Transaction . . .  " << endl;
					cout << "______________________________________________________________" << endl;

					cout << "\n- Enter The account Number: ";
					cin >> num;
					withdraw(num);
					break;
				}
			} while (choice != 3);
			break;

		case 3:
			system("CLS");
			cout << "______________________________________________________________" << endl << endl;
			cout << "\t\t  Searching . . .  " << endl;
			cout << "______________________________________________________________" << endl;

			cout << "\n- Enter The account Number: "; cin >> num;
			SearchForAcc(num);
			break;
		case 4:
			ShowAllAcc();
			break;
		case 5:
			account.ExitMenu();
			break;
		default:
			cout << "\n- Invalid Entry, Kindly try Again.";
			PauseScreen();
		}

	} while (choice != 5);
	return 0;
}

