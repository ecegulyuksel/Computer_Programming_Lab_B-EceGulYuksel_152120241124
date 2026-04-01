#include <iostream>
#include <string>

using namespace std;

struct MoneyBundle {
	string serialNumber;
	string currencyType;
	int billCounts[3]; //100s, 50s, 20s
	MoneyBundle* next;
};

struct Customer {
	string customerName;
	string transactionType;
};

struct SafeStack {
	MoneyBundle* top;
};

struct BankQueue {
	Customer arr[5];
	int front;
	int rear;
	int count;
};

void initStack(SafeStack& safe) {
	safe.top = nullptr;
}

void initQueue(BankQueue& q) {
	q.front = 0;
	q.rear = 0;
	q.count = 0;
}

void pushMoney(SafeStack& safe, string serial, string currency, int b100, int b50, int b20) {
	MoneyBundle* newBundle = new MoneyBundle;
	newBundle->serialNumber = serial;
	newBundle->currencyType = currency;
	newBundle->billCounts[0] = b100;
	newBundle->billCounts[1] = b50;
	newBundle->billCounts[2] = b20;

	newBundle->next = safe.top;
	safe.top = newBundle;
	cout << "(SAFE) Added money bundle: " << serial << " (" << currency << ")" << endl;
}

MoneyBundle* popMoney(SafeStack& safe) {
	if (safe.top == nullptr) return nullptr;

	MoneyBundle* temp = safe.top;
	safe.top = safe.top->next;
	return temp;
}

void enqueueCustomer(BankQueue& q, string name, string type) {
	if (q.count == 5) {
		cout << "(QUEUE) Bank queue is FULL! Cannot add: " << name << endl;
		return;
	}

	q.arr[q.rear].customerName = name;
	q.arr[q.rear].transactionType = type;
	q.rear = (q.rear + 1) % 5;
	q.count++;
	cout << "(QUEUE) Customer added: " << name << " (" << type << ")" << endl;
}

Customer dequeueCustomer(BankQueue& q) {
	Customer served = q.arr[q.front];
	q.front = (q.front + 1) % 5;
	q.count--;
	return served;
}

void processTransaction(SafeStack& safe, BankQueue& q) {
	cout << "\n[PROCESSING TRANSACTION]..." << endl;

	if (q.count == 0) {
		cout << "Error: No customers waiting in the queue." << endl;
		return;
	}
	if (safe.top == nullptr) {
		cout << "Error: No money bundles left in the safe!" << endl;
		return;
	}

	Customer currentCustomer = dequeueCustomer(q);
	MoneyBundle* moneyGiven = popMoney(safe);

	cout << "Served Customer: " << currentCustomer.customerName << " (" << currentCustomer.transactionType << ")" << endl;
	cout << "Handed over Money Bundle: " << moneyGiven->serialNumber << " (" << moneyGiven->currencyType << ")" << endl;

	// Eklendi: Hocanızın istediği toplam para hesabı örneği
	int totalAmount = (moneyGiven->billCounts[0] * 100) +
		(moneyGiven->billCounts[1] * 50) +
		(moneyGiven->billCounts[2] * 20);
	cout << "Total Amount Handed: " << totalAmount << " " << moneyGiven->currencyType << "\n" << endl;

	delete moneyGiven;
}

void displaySystem(SafeStack& safe, BankQueue& q) {
	cout << "\nSafe (Money Stack):" << endl;
	if (safe.top == nullptr) {
		cout << "The safe is empty." << endl;
	}
	else {
		MoneyBundle* temp = safe.top;
		while (temp != nullptr) {
			cout << "Bundle: " << temp->serialNumber << " | Currency: " << temp->currencyType
				<< " | Bills (100s, 50s, 20s): " << temp->billCounts[0] << ", "
				<< temp->billCounts[1] << ", " << temp->billCounts[2] << endl;
			temp = temp->next;
		}
	}
	cout << "--------------------------" << endl;

	cout << "Waiting Customers (Queue):" << endl;
	if (q.count == 0) {
		cout << "No customers in line." << endl;
	}
	else {
		for (int i = 0; i < q.count; i++) {
			int index = (q.front + i) % 5;
			cout << i + 1 << ". " << q.arr[index].customerName << " - " << q.arr[index].transactionType << endl;
		}
	}
	cout << "---------------------------------\n" << endl;
}

void cleanupSafe(SafeStack& safe) {
	while (safe.top != nullptr) {
		MoneyBundle* temp = popMoney(safe);
		delete temp;
	}
}

int main() {
	SafeStack mySafe;
	BankQueue myQueue;

	initStack(mySafe);
	initQueue(myQueue);

	int choice;
	bool running = true;

	while (running) {
		cout << "\n=== BANK SYSTEM MENU ===" << endl;
		cout << "1. Receive Money (Push to Safe)" << endl;
		cout << "2. New Customer (Enqueue)" << endl;
		cout << "3. Process Transaction (Serve Customer)" << endl;
		cout << "4. Display System Status" << endl;
		cout << "5. Exit" << endl;
		cout << "Select an operation (1-5): ";
		cin >> choice;

		if (choice == 1) {
			string serial, currency;
			int b100, b50, b20;
			cout << "Enter Serial Number (e.g., SN1001): ";
			cin >> serial;
			cout << "Enter Currency Type (e.g., TL, USD): ";
			cin >> currency;
			cout << "Enter number of 100s bills: ";
			cin >> b100;
			cout << "Enter number of 50s bills: ";
			cin >> b50;
			cout << "Enter number of 20s bills: ";
			cin >> b20;
			pushMoney(mySafe, serial, currency, b100, b50, b20);
		}
		else if (choice == 2) {
			string name, type;
			cout << "Enter Customer Name: ";
			cin >> name;
			cout << "Enter Transaction Type (e.g., Deposit, Withdraw): ";
			cin >> type;
			enqueueCustomer(myQueue, name, type);
		}
		else if (choice == 3) {
			processTransaction(mySafe, myQueue);
		}
		else if (choice == 4) {
			displaySystem(mySafe, myQueue);
		}
		else if (choice == 5) {
			cout << "Exiting and cleaning up memory..." << endl;
			running = false;
		}
		else {
			cout << "Invalid choice! Please select between 1-5." << endl;
		}
	}

	cleanupSafe(mySafe);
	return 0;
}