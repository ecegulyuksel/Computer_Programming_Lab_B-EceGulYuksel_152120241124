#include <iostream>
#include <string>
#include <iomanip> // Saat formatı icin setfill setw

using namespace std;

struct Page {
    string url;
    string title;
    int accessTime[3]; //saat dk sn
    Page* next;
    Page* prev;
};

void PageVisiting(Page*& head, Page*& tail, Page*& current, const string& url, const string& title, int h, int m, int s) {
    Page* newPage = new Page();
    newPage->url = url;
    newPage->title = title;
    newPage->accessTime[0] = h;
    newPage->accessTime[1] = m;
    newPage->accessTime[2] = s;
    newPage->next = nullptr;
    newPage->prev = nullptr;

    if (head == nullptr) {
        // Liste boşsa ilk eleman ekleniyor
        head = tail = current = newPage;
    }
    else {
        //en sona ekleme
        tail->next = newPage;
        newPage->prev = tail;
        tail = newPage;
        current = newPage; 
    }
    cout << "ziyaret ettin: " << title << " (" << url << ")\n";
}

//Önceki sayfaya git
void goBack(Page*& current) {
    if (current != nullptr && current->prev != nullptr) {
        current = current->prev;
        cout << "geri gittin: " << current->title << "\n";
    }
    else {
        cout << "Geri gidilecek bir sayfa yok!!!\n";
    }
}

// Forward: Sonraki sayfaya git
void goForward(Page*& current) {
    if (current != nullptr && current->next != nullptr) {
        current = current->next;
        cout << "ileri gitttin:" << current->title << "\n";
    }
    else {
        cout << "ileri gidilecek bir sayfa yok!!!\n";
    }
}

// Delete: Mevcut sayfayı sil 
void deleteCurrent(Page*& head, Page*& tail, Page*& current) {
    if (current == nullptr) {
        cout << "Gecmis tamamen bos.\n";
        return;
    }

    Page* toDelete = current;

    // Önceki düğümü onar
    if (current->prev != nullptr) {
        current->prev->next = current->next;
    }
    else {
        head = current->next; // Silinen şey head ise, head'i bir ileri kaydır
    }

    // Sonraki düğümü onar
    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }
    else {
        tail = current->prev; // Silinen şey tail ise, tail'i bir geri kaydır
    }

    // Silindikten sonra current işaretçisini mantıklı bir yere taşı
    if (current->prev != nullptr) {
        current = current->prev; // Geriye düş
    }
    else {
        current = current->next; // Geri yoksa ileriye düş (head silindiyse)
    }

    cout << "Silindi: " << toDelete->url << "\n";
    delete toDelete;
}

//Gemişi listele
void showHistory(Page* head, Page* current) {
    if (head == nullptr) {
        cout << "tarayici gecmisi bos.\n";
        return;
    }

    cout << "\n... Tarayici Gecmisi ...\n";
    Page* temp = head;
    while (temp != nullptr) {
        // Mevcut sayfayı vurgula
        if (temp == current) {
            cout << " [->] ";
        }
        else {
            cout << "       ";
        }

        cout << temp->title << " | " << temp->url << " | zaman: ";

        for (int i = 0; i < 3; i++) {
            // Saat formatının düzgün görünmesi için tek haneli sayılara 0 ekleme
            cout << setfill('0') << setw(2) << temp->accessTime[i];
            if (i < 2) cout << ":";
        }
        cout << "\n";

        temp = temp->next;
    }
    cout << "------------------------\n";
}

int main() {
    Page* head = nullptr;
    Page* tail = nullptr;
    Page* current = nullptr;
    int choice;

    while (true) {
        cout << "\n[1] Visit \n";
        cout << "[2] Back \n";
        cout << "[3] Forward \n";
        cout << "[4] Delete Current \n";
        cout << "[5] Display History \n";
        cout << "[6] Exit \n";
        cout << "Seciminiz: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Lutfen gecerli bir sayi girin.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            string url, title;
            int h, m, s;
            cout << "URL: ";
            cin >> url;
            cout << "Title: ";
            cin.ignore(); // getline oncesi buffer temizligi
            getline(cin, title);
            cout << "Saat girin (Orn: 14 32 00): ";
            cin >> h >> m >> s;

            if (cin.fail() || h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "gecersiz saat formati girdiniz!!!\n";
            }
            else {
                PageVisiting(head, tail, current, url, title, h, m, s);
            }
            break;
        }
        case 2:
            goBack(current);
            break;
        case 3:
            goForward(current);
            break;
        case 4:
            deleteCurrent(head, tail, current);
            break;
        case 5:
            showHistory(head, current);
            break;
        case 6:
            cout << "Tarayici kapaniyor. Bellek temizleniyor...\n";
            // Memory Management: Çıkışta tüm düğümleri sil
            while (head != nullptr) {
                Page* temp = head;
                head = head->next;
                delete temp;
            }
            return 0;
        default:
            cout << "gecersiz secim. Tekrar deneyin.\n";
        }
    }
}