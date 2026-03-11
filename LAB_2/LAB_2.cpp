#include <iostream>
#include <string>

using namespace std;

//Node
struct Node {
    string songTitle;
    Node* next;
};

void addSong(Node** head, string title) { //** : Amacımız main fonksiyonunun içindeki orijinal head değişkenini kalıcı olarak değiştirebilmektir.
    Node* newNode = new Node();
    newNode->songTitle = title;
    newNode->next = *head;
    *head = newNode;
    cout << "Added: " << title << endl;
}

void searchSong(Node* head, string& title) {
    Node* current = head;
    while (current != nullptr) {
        if (current->songTitle == title) {
            cout << "Song found: " << title << endl; 
            return; 
        }
        current = current->next;
    }
    cout << "Song not found: " << title << endl; 
}

void displaySongs(Node* head) {
    if (head == nullptr) {
        cout << "Playlist is empty." << endl;
        return;
    }

    Node* current = head;
    cout << "Users Playlist:\n " << endl;
    int order = 1;
    while (current != nullptr) {
        cout << order << ". " << current->songTitle << endl;
        current = current->next;
        order++;
    }
	cout << endl;
}

int main() {
    Node* head = nullptr;
    int choice;
    string title;
    
    while (true) {
        cout << "1. Add Song" << endl;
        cout << "2. Search Song" << endl;
        cout << "3. Display Playlist" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear(); // cin'in hata  durumunu
            cin.ignore(10000, '\n'); // Bellekte sıkışıp kalan hatalı harfleri çöpe at
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        switch (choice) {
        case 1:
            cout << "Enter song title: ";
            cin.ignore(); 
            getline(cin, title);
            addSong(&head, title);
            break;
        case 2:
            cout << "Enter song title to search: ";
            cin.ignore(); 
            getline(cin, title);
            searchSong(head, title);
            break;
        case 3:
            displaySongs(head);
            break;
        case 4:
            cout << "Exiting..." << endl;
            while (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;  //RAM temizleme
			}
                return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
            }
        }

    }

