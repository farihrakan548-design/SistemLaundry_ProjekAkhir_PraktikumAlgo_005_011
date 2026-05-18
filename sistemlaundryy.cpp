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
	cout << "ID: " << node->id << endl;
	cout << "Nama Pelanggan: " << node->namaPelanggan << endl;
	cout << "Jenis Layanan: " << node->jenisLayanan << endl;
	cout << "Berat (Kg): " << node->beratKg << endl;
	cetakHarga(node->totalHarga);
	cout << "Status: " << node->status << endl;
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

void hapusbyID(Node *&head, int id){
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