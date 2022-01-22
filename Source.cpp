#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
class HASH
{
private: struct node
{
	int accountNo;
	string name;
	float balance;
	node* next;
}
		 *list, *p, *t, *q;
		 node* H[5];
public: HASH()
{
	for (int i = 0; i < 5; ++i)
	{
		H[i] = NULL;
	}
}
		void Menu()
		{
			cout << "----------Menu----------" << endl;
			cout << "1. Show my balance" << endl;
			cout << "2. Deposit in my account" << endl;
			cout << "3. Withdraw from my account" << endl;
			cout << "4. Show me all" << endl;
			cout << "5. Close my account" << endl;

		}

		void Balance(int i)
		{
			p = list;
			while (p != NULL && p->accountNo != i)
			{
				p = p->next;
			} if (p == NULL) { cout << "\t\tAccount DNE" << endl; }
			else { cout << setprecision(2) << fixed << "\t\t" << p->name << ", your balance is: " << p->balance << endl; }
			p = NULL;
		}

		void Deposit(int i, int amt)
		{
			p = list;
			while (p->accountNo != i) { p = p->next; }
			p->balance += amt;
			cout << setprecision(2) << fixed << "\t\t" << p->name << ", your new balance is: " << p->balance << endl;
			cout << endl;
		}
		void Withdraw(int i, int amt)
		{
			p = list;
			while (p->accountNo != i) { p = p->next; }
			if (p->balance < amt)
			{
				cout << "\t\tInsufficient funds";
				cout << setprecision(2) << fixed << "\t\t" << p->name << ", your current balance is: " << p->balance << endl;
			}
			else {
				p->balance = p->balance - amt;
				cout << setprecision(2) << fixed << "\t\t" << p->name << ", your new balance is: " << p->balance << endl;
			}
		}
		void Displayall()
		{
			int width = 15;
			p = list;
			cout << "AccountNO" << setw(6)<<" " << "Name" << setw(11)<<" "<< "Balance" << endl;
			while (p != NULL) {
				cout << left
					<< setw(width) << p->accountNo
					<< setw(width) << p->name
					<< setprecision(2) << fixed << setw(width) << p->balance << endl;
				p = p->next;
			}
		}
		void CloseAccount(int i)
		{
			p = list;
			string n;
			if (list->accountNo == i)
			{
				list = list->next;
				n = p->name;
				delete p;
			}
			else
			{
				while (p != NULL && p->accountNo != i) { t = p; p = p->next; }
				if (p == NULL) { cout << "Account has been closed" << endl; }
				else { t->next = p->next; n = p->name; delete p; cout << n << ", we closed your account" << endl; }
			}
		}
		void AddAccount(int i, float b, string n)
		{
			p = new(node);
			p->name = n;
			p->accountNo = i;
			p->balance = b;
			p->next = NULL;
			if (list == NULL)
			{
				list = p;
			}
			else
			{
				t = q = list;
				// q=q->next;
				if (q->accountNo > p->accountNo)
				{
					p->next = q; list = p;
				}
				else
				{
					while (q->accountNo < p->accountNo && q->next != NULL)
					{
						t = q; q = q->next;
					} if (q->next == NULL)
					{
						q->next = p;
					}
					else
					{
						t->next = p;
						p->next = q;
					}
				}
			}
		}
};

int main()
{
	fstream f;
	int accountNo;
	float balance;
	string name;
	HASH o;
	//open file
	f.open("data.txt");
	if (f.fail()) {
		cout << "File not found" << endl;
	}
	else
	{
		while (f >> accountNo)
		{
			f >> name >> balance;
			o.AddAccount(accountNo, balance, name);
		}
	} f.close();
	bool cont = true;
	int choice;
	o.Menu();
	while (cont)
	{
		cout << "\nPlease enter your choice: "; cin >> choice;
		if (choice > 0 && choice < 6)
		{
			switch (choice)
			{
			case 1:
				int givenNo;
				cout << "\n\tEnter your account Number: "; cin >> givenNo;
				o.Balance(givenNo);
				break;
			case 2:
				int gNO, deposit;
				cout << "\n\tEnter your account Number: "; cin >> gNO;
				cout << "\n\tHow much would you like to deposit: "; cin >> deposit;
				o.Deposit(gNO, deposit);
				break;
			case 3:
				int NO, withdraw;
				cout << "\n\tEnter your account Number: "; cin >> NO;
				cout << "\n\tHow much would you like to withdraw: "; cin >> withdraw;
				o.Withdraw(NO, withdraw);
				break;
			case 4:
				o.Displayall();
				break;
			case 5:
				int No;
				cout << "\n\tEnter your account Number: "; cin >> No;
				o.CloseAccount(No);
			}
			//continue option
			char ch;
			cout << "\n Continue(y/n)"; cin >> ch;
			if (isupper(ch)) { ch = tolower(ch); }
			if (ch == 'n') { cout << "Thank you"; cont = false; break; }
			else
			{
				cout << "\tEnter an option between 1-5" << endl;
			}
		}
	}
	system("pause");
	return 0;
}
/*
*/
