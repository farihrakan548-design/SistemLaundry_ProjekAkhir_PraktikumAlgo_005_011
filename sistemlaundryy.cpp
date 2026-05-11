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

int idCounter = 1;

// Buat Node Baru
Node *buatNode(string nama, string layanan, float berat) {
	Node *newNode = new Node;
	newNode->id = idCounter++;
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

	//insert diawal linkedlist
	void insertDiAwal(Node *&head, string nama, string layanan, float berat) {
	Node *newNode = buatNode(nama, layanan, berat);
	newNode->next = head;
	head = newNode;
	cout << "Pesanan berhasil ditambahkan dengan ID: " << newNode->id << endl;
}

int main(){

}