#include <iostream>
using namespace std;

struct Node {
	int id;
	string namaPelanggan;
	string jenisLayanan;
	float beratKg;
	float totalHarga;
	string status;
	Node *next;
};

int idPelanggan = 1;

// Buat Node Baru
Node *buatNode(string nama, string layanan, float berat) {
	Node *newNode = new Node;
	newNode->id = idPelanggan++;
	newNode->namaPelanggan = nama;
	newNode->jenisLayanan = layanan;
	newNode->beratKg = berat;
	newNode->status = "Sedang Antri";
	newNode->next = nullptr;

	float hargaPerKg = 0;
	if (layanan == "Cuci Kering") {
		hargaPerKg = 5000;
	} else if (layanan == "Cuci Setrika") {
		hargaPerKg = 8000;
	} else if (layanan == "Setrika Saja") {
		hargaPerKg = 4000;
	}
	newNode->totalHarga = berat * hargaPerKg;
	return newNode;
}

//insert diawal linkedlist
void insertDiawal(Node *&head, string nama, string layanan, float berat) {
	Node *newNode = buatNode(nama, layanan, berat);
	newNode->next = head;
	head = newNode;
	cout << "Pesanan Pertama berhasil ditambahkan dengan ID: " << newNode->id << endl;
}

//insert di tengah linkedlist
void insertDiTengah(Node *&head, string nama, string layanan, float berat) {
	Node *newNode = buatNode(nama, layanan, berat);
	if (head == nullptr) {
		head = newNode;
		return;
	} else {
		Node *current = head;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newNode;
		cout << "Pesanan Tengah berhasil ditambahkan dengan ID: " << newNode->id << endl;
	}
}

//insert di akhir linkedlist
void insertDiAkhir(Node *&head, string nama, string layanan, float berat) {
	Node *newNode = buatNode(nama, layanan, berat);
	if (head == nullptr) {
		head = newNode;
		return;
	}
	Node *current = head;
	while (current->next != nullptr) {
		current = current->next;
	}
	current->next = newNode;
	cout << "Pesanan Terakhir berhasil ditambahkan dengan ID: " << newNode->id << endl;
}

void cetakHarga(float harga) {
	cout << "Total Harga: Rp " << harga << endl;
}

//cetak satu node
void cetakNode(Node *node) {
	cout << "-------------------------" << endl;
	cout << "      Detail Pesanan     " << endl;
	cout << "-------------------------" << endl;
	cout << "ID: " << node->id << endl;
	cout << "Nama Pelanggan: " << node->namaPelanggan << endl;
	cout << "Jenis Layanan: " << node->jenisLayanan << endl;
	cout << "Berat (Kg): " << node->beratKg << endl;
	cetakHarga(node->totalHarga);
	cout << "Status: " << node->status << endl;
	cout << "-------------------------" << endl;
}

//cetak seluruh list
void cetakList(Node *head) {
	if (head == nullptr) {
		cout << "Tidak ada pesanan." << endl;
		return;
	}
	Node *current = head;
	while (current != nullptr) {
		cetakNode(current);
		cout << "-------------------------" << endl;
		current = current->next;
	}
}

void hapusbyID(Node *&head, int id) {
	if (head == nullptr){
		cout << " Daftar kosong." << endl;
		return;
	}
	if (head->id == id){
		Node *toDelete = head;
		head = head->next;
		cout << "Pesanan dengan ID " << id << "atas nama " << toDelete->namaPelanggan << " berhasil dihapus." << endl;
		delete toDelete;
		return;
	}
	Node *current = head;
	while (current->next != nullptr && current->next->id != id) {
		current = current->next;
	}
	if (current->next == nullptr) {
		cout << "Pesanan dengan ID " << id << " tidak ditemukan." << endl;
		return;
	}
	Node *toDelete = current->next;
	current->next = toDelete->next;
	cout << "Pesanan dengan ID " << id << "atas nama " << toDelete->namaPelanggan << " berhasil dihapus." << endl;
	delete toDelete;
}

void updateStatus(Node *head, int id, string newStatus) {
	Node *current = head;
	while (current != nullptr) {
		if (current->id == id) {
			current->status = newStatus;
			cout << "Status pesanan dengan ID " << id << " berhasil diperbarui menjadi: " << newStatus << endl;
			return;
		}
		current = current->next;
	}
	cout << "Pesanan dengan ID " << id << " tidak ditemukan." << endl;
}

Node *caribyID(Node *head, int id) {
	Node *current = head;
	while (current != nullptr) {
		if (current->id == id) {
			return current;
		}
		current = current->next;
	}
	return nullptr;
}

void clearList(Node *&head) {
	while (head != nullptr) {
		Node *toDelete = head;
		head = head->next;
		delete toDelete;
	}
	cout << "Semua pesanan berhasil dihapus." << endl;
}

void tampilmenu() {
	cout << "==============================" << endl;
	cout << "     	Sistem Laundry       " << endl;
	cout << "==============================" << endl;
	cout << "1. Tambah Pesanan di Awal" << endl;
	cout << "2. Tambah Pesanan di Tengah" << endl;
	cout << "3. Tambah Pesanan di Akhir" << endl;
	cout << "4. Cetak Semua Pesanan" << endl;
	cout << "5. Hapus Pesanan by ID" << endl;
	cout << "6. Update Status Pesanan by ID" << endl;
	cout << "7. Cari Pesanan by ID" << endl;
	cout << "8. Clear Semua Pesanan" << endl;
	cout << "9. Keluar" << endl;
	cout << "==============================" << endl;
	cout << "Pilih menu: ";
}

string tampiljenislayanan() {
	int pilihan;
	string jenisLayanan;

	cout << "=== Jenis Layanan Laundry ===" << endl;
	cout << "1. Cuci Kering (Rp 5000/Kg)" << endl;
	cout << "2. Cuci Setrika (Rp 8000/Kg)" << endl;
	cout << "3. Setrika Saja (Rp 4000/Kg)" << endl;
	cout << "==============================" << endl;
	cout << "Pilih jenis layanan: ";
	cin >> pilihan;
	cin.ignore(); // Bersihkan newline
	if (pilihan < 1 || pilihan > 3) {
		cout << "Pilihan tidak valid. Program akan keluar." << endl;
		return "";
	} else {
		string jenisLayanan;
		if (pilihan == 1) {
			jenisLayanan = "Cuci Kering";
		} else if (pilihan == 2) {
			jenisLayanan = "Cuci Setrika";
		} else {
			jenisLayanan = "Setrika Saja";
		}
		return jenisLayanan;
	}
}

int main() {
	Node *head = nullptr;
	int pilihanMenu = 0;

	do {
		tampilmenu();
		cin >> pilihanMenu;
		cin.ignore();

		if (pilihanMenu == 1) {
			string nama;
			float berat;

			cout << "==============================" << endl;
			cout << "Masukkan nama pelanggan: ";
			getline(cin, nama);

			cout << "Masukkan berat cucian (Kg): ";
			cin >> berat;
			cin.ignore();

			string jenisLayanan = tampiljenislayanan();
			insertDiawal(head, nama, jenisLayanan, berat);

		} else if (pilihanMenu == 2) {
			string nama;
			float berat;

			cout << "==============================" << endl;
			cout << "Masukkan nama pelanggan: ";
			getline(cin, nama);

			cout << "Masukkan berat cucian (Kg): ";
			cin >> berat;
			cin.ignore();

			string jenisLayanan = tampiljenislayanan();
			insertDiTengah(head, nama, jenisLayanan, berat);

		} else if (pilihanMenu == 3) {
			string nama;
			float berat;

			cout << "==============================" << endl;
			cout << "Masukkan nama pelanggan: ";
			getline(cin, nama);

			cout << "Masukkan berat cucian (Kg): ";
			cin >> berat;
			cin.ignore();

			string jenisLayanan = tampiljenislayanan();
			insertDiAkhir(head, nama, jenisLayanan, berat);

		} else if (pilihanMenu == 4) {
			cetakList(head);

		} else if (pilihanMenu == 5) {
			int idHapus;
			cout << "Masukkan ID pesanan yang ingin dihapus: ";
			cin >> idHapus;
			hapusbyID(head, idHapus);

		} else if (pilihanMenu == 6) {
			int idUpdate;
			string newStatus;

			cout << "Masukkan ID pesanan yang ingin diupdate statusnya: ";
			cin >> idUpdate;
			cin.ignore();

			cout << "Masukkan status baru (Sedang Antri/Sedang Diproses/Selesai): ";
			getline(cin, newStatus);

			updateStatus(head, idUpdate, newStatus);

		} else if (pilihanMenu == 7) {
			int idCari;
			cout << "Masukkan ID pesanan yang ingin dicari: ";
			cin >> idCari;

			Node *foundNode = caribyID(head, idCari);
			if (foundNode != nullptr) {
				cetakNode(foundNode);
			} else {
				cout << "Pesanan dengan ID " << idCari << " tidak ditemukan." << endl;
			}

		} else if (pilihanMenu == 8) {
			clearList(head);

		} else if (pilihanMenu == 9) {
			cout << "Terima kasih telah menggunakan sistem laundry. Program akan keluar." << endl;
			clearList(head);
			break;

		} else {
			cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
		}

	} while (true);

	return 0;
}
