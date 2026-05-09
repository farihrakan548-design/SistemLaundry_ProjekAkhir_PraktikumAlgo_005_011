#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Node {
    int    id;           
    string namaPelanggan;
    string jenisLayanan; 
    float  beratKg;
    float  totalHarga;
    string status;       
    Node  *next;
};

int idCounter = 1; 

Node *createNode(string nama, string layanan, float berat) {
    Node *newNode    = new Node;
    newNode->id      = idCounter++;
    newNode->namaPelanggan = nama;
    newNode->jenisLayanan  = layanan;
    newNode->beratKg       = berat;
    newNode->status        = "Antri";
    newNode->next          = nullptr;


    float hargaPerKg = 0;
    if      (layanan == "Cuci Kering")   hargaPerKg = 5000;
    else if (layanan == "Cuci Setrika")  hargaPerKg = 8000;
    else if (layanan == "Setrika")       hargaPerKg = 4000;

    newNode->totalHarga = berat * hargaPerKg;
    return newNode;
}

void insertDiAwal(Node *&head, string nama, string layanan, float berat) {
    Node *newNode  = createNode(nama, layanan, berat);
    newNode->next  = head;
    head           = newNode;
    cout << "[+] Order berhasil ditambahkan di awal daftar. ID: " << newNode->id << "\n";
}

void insertDiAkhir(Node *&head, string nama, string layanan, float berat) {
    Node *newNode = createNode(nama, layanan, berat);
    if (head == nullptr) {
        head = newNode;
        cout << "[+] Order pertama berhasil ditambahkan. ID: " << newNode->id << "\n";
        return;
    }
    Node *current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
    cout << "[+] Order berhasil ditambahkan di akhir daftar. ID: " << newNode->id << "\n";
}

void insertDiTengah(Node *&head, string nama, string layanan, float berat, int posisi) {
    Node *newNode = createNode(nama, layanan, berat);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node *current = head;
    for (int i = 1; i < posisi && current != nullptr; i++) {
        current = current->next;
    }
    if (current == nullptr) {
        cout << "[!] Posisi tidak valid!\n";
        delete newNode;
        idCounter--;
        return;
    }
    newNode->next = current->next;
    current->next = newNode;
    cout << "[+] Order berhasil disisipkan setelah posisi " << posisi << ". ID: " << newNode->id << "\n";
}

void printNode(Node *node) {
    cout << left
         << "| " << setw(5)  << node->id
         << "| " << setw(18) << node->namaPelanggan
         << "| " << setw(16) << node->jenisLayanan
         << "| " << setw(8)  << node->beratKg
         << "| " << setw(12) << node->totalHarga
         << "| " << setw(10) << node->status
         << "|\n";
}

void printList(Node *head) {
    if (head == nullptr) {
        cout << "[!] Daftar order kosong.\n";
        return;
    }
    cout << "\n";
    cout << string(77, '=') << "\n";
    cout << left
         << "| " << setw(5)  << "ID"
         << "| " << setw(18) << "Nama Pelanggan"
         << "| " << setw(16) << "Layanan"
         << "| " << setw(8)  << "Berat"
         << "| " << setw(12) << "Harga"
         << "| " << setw(10) << "Status"
         << "|\n";
    cout << string(77, '=') << "\n";
    Node *current = head;
    while (current != nullptr) {
        printNode(current);
        current = current->next;
    }
    cout << string(77, '=') << "\n\n";
}

void deleteByID(Node *&head, int id) {
    if (head == nullptr) {
        cout << "[!] Daftar kosong.\n";
        return;
    }
    if (head->id == id) {
        Node *toDelete = head;
        head = head->next;
        cout << "[-] Order ID " << id << " atas nama " << toDelete->namaPelanggan << " berhasil dihapus.\n";
        delete toDelete;
        return;
    }
    Node *current = head;
    while (current->next != nullptr && current->next->id != id) {
        current = current->next;
    }
    if (current->next == nullptr) {
        cout << "[!] Order dengan ID " << id << " tidak ditemukan.\n";
        return;
    }
    Node *toDelete  = current->next;
    current->next   = toDelete->next;
    cout << "[-] Order ID " << id << " atas nama " << toDelete->namaPelanggan << " berhasil dihapus.\n";
    delete toDelete;
}

void updateStatus(Node *head, int id, string statusBaru) {
    Node *current = head;
    while (current != nullptr) {
        if (current->id == id) {
            current->status = statusBaru;
            cout << "[~] Status order ID " << id << " diperbarui menjadi \"" << statusBaru << "\".\n";
            return;
        }
        current = current->next;
    }
    cout << "[!] Order dengan ID " << id << " tidak ditemukan.\n";
}

Node *searchByNama(Node *head, string nama) {
    Node *current = head;
    while (current != nullptr) {
        if (current->namaPelanggan == nama) {
            return current; 
        }
        current = current->next;
    }
    return nullptr;
}

Node *searchByID(Node *head, int id) {
    Node *current = head;
    while (current != nullptr) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void sortByNama(Node *head) {
    if (head == nullptr) return;
    bool swapped;
    do {
        swapped = false;
        Node *current = head;
        while (current->next != nullptr) {
            if (current->namaPelanggan > current->next->namaPelanggan) {
                swap(current->id,            current->next->id);
                swap(current->namaPelanggan, current->next->namaPelanggan);
                swap(current->jenisLayanan,  current->next->jenisLayanan);
                swap(current->beratKg,       current->next->beratKg);
                swap(current->totalHarga,    current->next->totalHarga);
                swap(current->status,        current->next->status);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
    cout << "[*] Daftar order berhasil diurutkan berdasarkan nama pelanggan (A-Z).\n";
}

void sortByHarga(Node *head) {
    if (head == nullptr) return;
    bool swapped;
    do {
        swapped = false;
        Node *current = head;
        while (current->next != nullptr) {
            if (current->totalHarga > current->next->totalHarga) {
                swap(current->id,            current->next->id);
                swap(current->namaPelanggan, current->next->namaPelanggan);
                swap(current->jenisLayanan,  current->next->jenisLayanan);
                swap(current->beratKg,       current->next->beratKg);
                swap(current->totalHarga,    current->next->totalHarga);
                swap(current->status,        current->next->status);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
    cout << "[*] Daftar order berhasil diurutkan berdasarkan harga (murah -> mahal).\n";
}

void hitungPendapatan(Node *head) {
    float total = 0;
    int   jumlah = 0;
    Node *current = head;
    while (current != nullptr) {
        total += current->totalHarga;
        jumlah++;
        current = current->next;
    }
    cout << "\n>>> Total Order   : " << jumlah << " order\n";
    cout << ">>> Total Pendapatan: Rp " << fixed << setprecision(0) << total << "\n\n";
}

void clearList(Node *&head) {
    Node *current = head;
    while (current != nullptr) {
        Node *toDelete = current;
        current = current->next;
        delete toDelete;
    }
    head = nullptr;
    cout << "[x] Semua data order telah dihapus.\n";
}

void tampilkanMenu() {
    cout << "\n========================================\n";
    cout << "       SISTEM MANAJEMEN LAUNDRY         \n";
    cout << "========================================\n";
    cout << " 1. Tambah Order (di Akhir)             \n";
    cout << " 2. Tambah Order (di Awal)              \n";
    cout << " 3. Tambah Order (di Tengah/Posisi)     \n";
    cout << " 4. Hapus Order (by ID)                 \n";
    cout << " 5. Update Status Order                 \n";
    cout << " 6. Cari Order by Nama                  \n";
    cout << " 7. Cari Order by ID                    \n";
    cout << " 8. Tampilkan Semua Order               \n";
    cout << " 9. Urutkan by Nama (A-Z)               \n";
    cout << "10. Urutkan by Harga (Murah-Mahal)      \n";
    cout << "11. Hitung Total Pendapatan             \n";
    cout << "12. Hapus Semua Order                   \n";
    cout << " 0. Keluar                              \n";
    cout << "========================================\n";
    cout << "Pilihan: ";
}

string inputLayanan() {
    int pil;
    cout << "Jenis Layanan:\n";
    cout << "  1. Cuci Kering  (Rp 5.000/kg)\n";
    cout << "  2. Cuci Setrika (Rp 8.000/kg)\n";
    cout << "  3. Setrika      (Rp 4.000/kg)\n";
    cout << "Pilih: ";
    cin >> pil;
    cin.ignore();
    if (pil == 1) return "Cuci Kering";
    if (pil == 2) return "Cuci Setrika";
    if (pil == 3) return "Setrika";
    return "Cuci Kering";
}

int main() {
    Node *head = nullptr;

    // --- Data awal demo ---
    insertDiAkhir(head, "Budi Santoso",  "Cuci Setrika", 3.5);
    insertDiAkhir(head, "Ani Rahayu",    "Cuci Kering",  2.0);
    insertDiAkhir(head, "Citra Dewi",    "Setrika",      1.5);
    insertDiAkhir(head, "Deni Kurniawan","Cuci Setrika", 5.0);
    insertDiAkhir(head, "Eko Prasetyo",  "Cuci Kering",  4.0);

    int pilihan;
    do {
        tampilkanMenu();
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            string nama, layanan;
            float berat;
            cout << "Nama Pelanggan: "; getline(cin, nama);
            layanan = inputLayanan();
            cout << "Berat (kg)    : "; cin >> berat; cin.ignore();
            insertDiAkhir(head, nama, layanan, berat);

        } else if (pilihan == 2) {
            string nama, layanan;
            float berat;
            cout << "Nama Pelanggan: "; getline(cin, nama);
            layanan = inputLayanan();
            cout << "Berat (kg)    : "; cin >> berat; cin.ignore();
            insertDiAwal(head, nama, layanan, berat);

        } else if (pilihan == 3) {
            string nama, layanan;
            float berat;
            int posisi;
            cout << "Nama Pelanggan: "; getline(cin, nama);
            layanan = inputLayanan();
            cout << "Berat (kg)    : "; cin >> berat; cin.ignore();
            cout << "Sisipkan setelah posisi ke-: "; cin >> posisi; cin.ignore();
            insertDiTengah(head, nama, layanan, berat, posisi);

        } else if (pilihan == 4) {
            int id;
            cout << "Masukkan ID order yang ingin dihapus: "; cin >> id; cin.ignore();
            deleteByID(head, id);

        } else if (pilihan == 5) {
            int id;
            cout << "Masukkan ID order: "; cin >> id; cin.ignore();
            cout << "Status baru (Antri / Diproses / Selesai): ";
            string st; getline(cin, st);
            updateStatus(head, id, st);

        } else if (pilihan == 6) {
            string nama;
            cout << "Masukkan nama yang dicari: "; getline(cin, nama);
            Node *hasil = searchByNama(head, nama);
            if (hasil != nullptr) {
                cout << "\n[v] Order ditemukan (address: " << hasil << "):\n";
                cout << string(77, '-') << "\n";
                printNode(hasil);
                cout << string(77, '-') << "\n";
            } else {
                cout << "[!] Order atas nama \"" << nama << "\" tidak ditemukan.\n";
            }

        } else if (pilihan == 7) {
            int id;
            cout << "Masukkan ID yang dicari: "; cin >> id; cin.ignore();
            Node *hasil = searchByID(head, id);
            if (hasil != nullptr) {
                cout << "\n[v] Order ditemukan (address: " << hasil << "):\n";
                cout << string(77, '-') << "\n";
                printNode(hasil);
                cout << string(77, '-') << "\n";
            } else {
                cout << "[!] Order ID " << id << " tidak ditemukan.\n";
            }

        } else if (pilihan == 8) {
            printList(head);

        } else if (pilihan == 9) {
            sortByNama(head);
            printList(head);

        } else if (pilihan == 10) {
            sortByHarga(head);
            printList(head);

        } else if (pilihan == 11) {
            hitungPendapatan(head);

        } else if (pilihan == 12) {
            clearList(head);

        } else if (pilihan == 0) {
            cout << "\nTerima kasih! Program selesai.\n";

        } else {
            cout << "[!] Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    clearList(head);
    return 0;
}
