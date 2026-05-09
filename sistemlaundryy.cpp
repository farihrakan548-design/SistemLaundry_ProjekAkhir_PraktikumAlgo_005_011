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