#include <iostream>
#include <fstream>
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

void garis() {
	cout << "========================================" << endl;
}

bool kembaliMenu() {
	char pilih;
	cout << endl;
	cout << "Kembali ke menu utama? (Y/N): ";
	cin >> pilih;
	cin.ignore();

	return pilih == 'Y' || pilih == 'y';
}

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

void cetakNode(Node *node) {
	garis();
	cout << "            DETAIL PESANAN" << endl;
	garis();
	cout << "ID Pesanan      : " << node->id << endl;
	cout << "Nama Pelanggan  : " << node->namaPelanggan << endl;
	cout << "Jenis Layanan   : " << node->jenisLayanan << endl;
	cout << "Berat Cucian    : " << node->beratKg << " Kg" << endl;
	cout << "Total Harga     : Rp " << node->totalHarga << endl;
	cout << "Status Laundry  : " << node->status << endl;
	garis();
}

void cetakList(Node *head) {
	if (head == nullptr) {
		cout << endl;
		cout << "Belum ada pesanan laundry." << endl;
		return;
	}

	Node *current = head;

	while (current != nullptr) {
		cetakNode(current);
		current = current->next;
	}
}

string tampiljenislayanan() {
	int pilihan;

	garis();
	cout << "             JENIS LAYANAN" << endl;
	garis();
	cout << "1. Cuci Kering   - Rp 5000/Kg" << endl;
	cout << "2. Cuci Setrika  - Rp 8000/Kg" << endl;
	cout << "3. Setrika Saja  - Rp 4000/Kg" << endl;
	garis();

	cout << "Pilih layanan: ";
	cin >> pilihan;
	cin.ignore();

	if (pilihan == 1) {
		return "Cuci Kering";
	} else if (pilihan == 2) {
		return "Cuci Setrika";
	} else if (pilihan == 3) {
		return "Setrika Saja";
	}

	return "";
}

void inputDataPesanan(string &nama, float &berat, string &jenisLayanan) {
	garis();
	cout << "            INPUT PESANAN" << endl;
	garis();

	cout << "Masukkan nama pelanggan : ";
	getline(cin, nama);

	cout << "Masukkan berat cucian   : ";
	cin >> berat;
	cin.ignore();

	jenisLayanan = tampiljenislayanan();
}

void insertDiawal(Node *&head, string nama, string layanan, float berat) {
	Node *newNode = buatNode(nama, layanan, berat);

	newNode->next = head;
	head = newNode;

	cout << endl;
	cout << "Pesanan berhasil ditambahkan di awal." << endl;
	cout << "ID Pesanan : " << newNode->id << endl;
}

void insertDiTengah(Node *&head, string nama, string layanan, float berat) {
	Node *newNode = buatNode(nama, layanan, berat);

	if (head == nullptr) {
		head = newNode;
	} else {
		Node *current = head;

		while (current->next != nullptr) {
			current = current->next;
		}

		current->next = newNode;
	}

	cout << endl;
	cout << "Pesanan berhasil ditambahkan di tengah." << endl;
	cout << "ID Pesanan : " << newNode->id << endl;
}

void insertDiAkhir(Node *&head, string nama, string layanan, float berat) {
	Node *newNode = buatNode(nama, layanan, berat);

	if (head == nullptr) {
		head = newNode;
	} else {
		Node *current = head;

		while (current->next != nullptr) {
			current = current->next;
		}

		current->next = newNode;
	}

	cout << endl;
	cout << "Pesanan berhasil ditambahkan di akhir." << endl;
	cout << "ID Pesanan : " << newNode->id << endl;
}

void hapusbyID(Node *&head, int id) {
	if (head == nullptr) {
		cout << endl;
		cout << "Daftar pesanan kosong." << endl;
		return;
	}

	if (head->id == id) {
		Node *toDelete = head;
		head = head->next;

		cout << endl;
		cout << "Pesanan ID " << id << " atas nama "
			 << toDelete->namaPelanggan << " berhasil dihapus." << endl;

		delete toDelete;
		return;
	}

	Node *current = head;

	while (current->next != nullptr && current->next->id != id) {
		current = current->next;
	}

	if (current->next == nullptr) {
		cout << endl;
		cout << "Pesanan tidak ditemukan." << endl;
		return;
	}

	Node *toDelete = current->next;
	current->next = toDelete->next;

	cout << endl;
	cout << "Pesanan ID " << id << " atas nama "
		 << toDelete->namaPelanggan << " berhasil dihapus." << endl;

	delete toDelete;
}

void updateStatus(Node *head, int id, string newStatus) {
	Node *current = head;

	while (current != nullptr) {
		if (current->id == id) {
			current->status = newStatus;

			cout << endl;
			cout << "Status pesanan berhasil diperbarui." << endl;
			cout << "ID Pesanan  : " << id << endl;
			cout << "Status Baru : " << newStatus << endl;
			return;
		}

		current = current->next;
	}

	cout << endl;
	cout << "Pesanan tidak ditemukan." << endl;
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

int hitungJumlahPesanan(Node *head) {
	int jumlah = 0;

	while (head != nullptr) {
		jumlah++;
		head = head->next;
	}

	return jumlah;
}

float hitungTotalPendapatan(Node *head) {
	float total = 0;

	while (head != nullptr) {
		total += head->totalHarga;
		head = head->next;
	}

	return total;
}

int hitungPesananSelesai(Node *head) {
	int jumlah = 0;

	while (head != nullptr) {
		if (head->status == "Selesai") {
			jumlah++;
		}

		head = head->next;
	}

	return jumlah;
}

void tampilStatistik(Node *head) {
	garis();
	cout << "          STATISTIK LAUNDRY" << endl;
	garis();
	cout << "Total Pesanan      : " << hitungJumlahPesanan(head) << endl;
	cout << "Pesanan Selesai    : " << hitungPesananSelesai(head) << endl;
	cout << "Total Pendapatan   : Rp " << hitungTotalPendapatan(head) << endl;
	garis();
}

void nukerData(Node *a, Node *b) {
	int tempId = a->id;
	a->id = b->id;
	b->id = tempId;

	string tempNama = a->namaPelanggan;
	a->namaPelanggan = b->namaPelanggan;
	b->namaPelanggan = tempNama;

	string tempLayanan = a->jenisLayanan;
	a->jenisLayanan = b->jenisLayanan;
	b->jenisLayanan = tempLayanan;

	float tempBerat = a->beratKg;
	a->beratKg = b->beratKg;
	b->beratKg = tempBerat;

	float tempHarga = a->totalHarga;
	a->totalHarga = b->totalHarga;
	b->totalHarga = tempHarga;

	string tempStatus = a->status;
	a->status = b->status;
	b->status = tempStatus;
}

void sortById(Node *head) {
	Node *current = head;

	while (current != nullptr) {
		Node *minNode = current;
		Node *nextNode = current->next;

		while (nextNode != nullptr) {
			if (nextNode->id < minNode->id) {
				minNode = nextNode;
			}

			nextNode = nextNode->next;
		}

		nukerData(current, minNode);
		current = current->next;
	}
}

void sortByNama(Node *head) {
	Node *current = head;

	while (current != nullptr) {
		Node *minNode = current;
		Node *nextNode = current->next;

		while (nextNode != nullptr) {
			if (nextNode->namaPelanggan < minNode->namaPelanggan) {
				minNode = nextNode;
			}

			nextNode = nextNode->next;
		}

		nukerData(current, minNode);
		current = current->next;
	}
}

void sortByStatus(Node *head) {
	Node *current = head;

	while (current != nullptr) {
		Node *minNode = current;
		Node *nextNode = current->next;

		while (nextNode != nullptr) {
			if (nextNode->status < minNode->status) {
				minNode = nextNode;
			}

			nextNode = nextNode->next;
		}

		nukerData(current, minNode);
		current = current->next;
	}
}

void sortByHarga(Node *head) {
	Node *current = head;

	while (current != nullptr) {
		Node *minNode = current;
		Node *nextNode = current->next;

		while (nextNode != nullptr) {
			if (nextNode->totalHarga < minNode->totalHarga) {
				minNode = nextNode;
			}

			nextNode = nextNode->next;
		}

		nukerData(current, minNode);
		current = current->next;
	}
}

void sortByBerat(Node *head) {
	Node *current = head;

	while (current != nullptr) {
		Node *minNode = current;
		Node *nextNode = current->next;

		while (nextNode != nullptr) {
			if (nextNode->beratKg < minNode->beratKg) {
				minNode = nextNode;
			}

			nextNode = nextNode->next;
		}

		nukerData(current, minNode);
		current = current->next;
	}
}

void clearList(Node *&head) {
	while (head != nullptr) {
		Node *toDelete = head;
		head = head->next;
		delete toDelete;
	}
}

void hapusSemuaPesanan(Node *&head) {
	clearList(head);
	cout << endl;
	cout << "Semua pesanan berhasil dihapus." << endl;
}

void tambahNodeDariFile(Node *&head, int id, string nama, string layanan, float berat, float harga, string status) {
	Node *newNode = new Node;

	newNode->id = id;
	newNode->namaPelanggan = nama;
	newNode->jenisLayanan = layanan;
	newNode->beratKg = berat;
	newNode->totalHarga = harga;
	newNode->status = status;
	newNode->next = nullptr;

	if (id >= idPelanggan) {
		idPelanggan = id + 1;
	}

	if (head == nullptr) {
		head = newNode;
	} else {
		Node *current = head;

		while (current->next != nullptr) {
			current = current->next;
		}

		current->next = newNode;
	}
}

void simpanKeFile(Node *head) {
	string namaFile;

	cout << endl;
	cout << "Masukkan nama file untuk menyimpan data: ";
	getline(cin, namaFile);

	ofstream file(namaFile.c_str());

	if (!file.is_open()) {
		cout << endl;
		cout << "File gagal dibuat." << endl;
		return;
	}

	Node *current = head;

	while (current != nullptr) {
		file << current->id << endl;
		file << current->namaPelanggan << endl;
		file << current->jenisLayanan << endl;
		file << current->beratKg << endl;
		file << current->totalHarga << endl;
		file << current->status << endl;

		current = current->next;
	}

	file.close();

	cout << endl;
	cout << "Data berhasil disimpan ke file: " << namaFile << endl;
}

void bacaFile(Node *&head) {
	string namaFile;

	cout << endl;
	cout << "Masukkan nama file yang ingin dibaca: ";
	getline(cin, namaFile);

	ifstream file(namaFile.c_str());

	if (!file.is_open()) {
		cout << endl;
		cout << "File tidak ditemukan." << endl;
		return;
	}

	clearList(head);
	idPelanggan = 1;

	int id;
	string nama;
	string layanan;
	float berat;
	float harga;
	string status;

	while (file >> id) {
		file.ignore();

		getline(file, nama);
		getline(file, layanan);

		file >> berat;
		file >> harga;
		file.ignore();

		getline(file, status);

		tambahNodeDariFile(head, id, nama, layanan, berat, harga, status);
	}

	file.close();

	cout << endl;
	cout << "Data berhasil dibaca dari file: " << namaFile << endl;

	cetakList(head);
}

void tampilmenu() {
	garis();
	cout << "             SISTEM LAUNDRY" << endl;
	garis();
	cout << "1.  Tambah Pesanan" << endl;
	cout << "2.  Tampilkan Semua Pesanan" << endl;
	cout << "3.  Cari Pesanan by ID" << endl;
	cout << "4.  Update Status Pesanan" << endl;
	cout << "5.  Hapus Pesanan by ID" << endl;
	cout << "6.  Sorting Pesanan" << endl;
	cout << "7.  Statistik Laundry" << endl;
	cout << "8.  Simpan Data ke File" << endl;
	cout << "9.  Baca Data dari File" << endl;
	cout << "10. Hapus Semua Pesanan" << endl;
	cout << "11. Keluar Program" << endl;
	garis();
	cout << "Pilih menu: ";
}

int main() {
	Node *head = nullptr;

	int pilihanMenu;
	bool lanjut = true;

	do {
		tampilmenu();

		cin >> pilihanMenu;
		cin.ignore();

		if (pilihanMenu == 1) {
			int pilihanTambah;

			garis();
			cout << "          TAMBAH PESANAN" << endl;
			garis();
			cout << "1. Tambah di Awal" << endl;
			cout << "2. Tambah di Tengah" << endl;
			cout << "3. Tambah di Akhir" << endl;
			garis();

			cout << "Pilih posisi data: ";
			cin >> pilihanTambah;
			cin.ignore();

			string nama;
			string jenisLayanan;
			float berat;

			inputDataPesanan(nama, berat, jenisLayanan);

			if (jenisLayanan != "" && berat > 0) {
				if (pilihanTambah == 1) {
					insertDiawal(head, nama, jenisLayanan, berat);
				} else if (pilihanTambah == 2) {
					insertDiTengah(head, nama, jenisLayanan, berat);
				} else if (pilihanTambah == 3) {
					insertDiAkhir(head, nama, jenisLayanan, berat);
				} else {
					cout << endl;
					cout << "Pilihan posisi tidak valid." << endl;
				}
			} else {
				cout << endl;
				cout << "Pesanan gagal ditambahkan." << endl;
			}

		} else if (pilihanMenu == 2) {
			garis();
			cout << "           DAFTAR PESANAN" << endl;
			garis();
			cetakList(head);

		} else if (pilihanMenu == 3) {
			int idCari;

			garis();
			cout << "            CARI PESANAN" << endl;
			garis();

			cout << "Masukkan ID pesanan: ";
			cin >> idCari;
			cin.ignore();

			Node *foundNode = caribyID(head, idCari);

			if (foundNode != nullptr) {
				cetakNode(foundNode);
			} else {
				cout << endl;
				cout << "Pesanan tidak ditemukan." << endl;
			}

		} else if (pilihanMenu == 4) {
			int idUpdate;
			int pilihanStatus;
			string newStatus = "";

			garis();
			cout << "           UPDATE STATUS" << endl;
			garis();

			cout << "Masukkan ID pesanan: ";
			cin >> idUpdate;
			cin.ignore();

			garis();
			cout << "1. Sedang Antri" << endl;
			cout << "2. Sedang Diproses" << endl;
			cout << "3. Selesai" << endl;
			garis();

			cout << "Pilih status baru: ";
			cin >> pilihanStatus;
			cin.ignore();

			if (pilihanStatus == 1) {
				newStatus = "Sedang Antri";
			} else if (pilihanStatus == 2) {
				newStatus = "Sedang Diproses";
			} else if (pilihanStatus == 3) {
				newStatus = "Selesai";
			}

			if (newStatus != "") {
				updateStatus(head, idUpdate, newStatus);
			} else {
				cout << endl;
				cout << "Pilihan status tidak valid." << endl;
			}

		} else if (pilihanMenu == 5) {
			int idHapus;

			garis();
			cout << "           HAPUS PESANAN" << endl;
			garis();

			cout << "Masukkan ID pesanan: ";
			cin >> idHapus;
			cin.ignore();

			hapusbyID(head, idHapus);

		} else if (pilihanMenu == 6) {
			int pilihanSort;

			garis();
			cout << "          SORTING PESANAN" << endl;
			garis();
			cout << "1. Sort by ID" << endl;
			cout << "2. Sort by Nama" << endl;
			cout << "3. Sort by Status" << endl;
			cout << "4. Sort by Harga" << endl;
			cout << "5. Sort by Berat" << endl;
			garis();

			cout << "Pilih sorting: ";
			cin >> pilihanSort;
			cin.ignore();

			if (head == nullptr) {
				cout << endl;
				cout << "Data pesanan masih kosong." << endl;
			} else if (pilihanSort == 1) {
				sortById(head);
				cout << endl;
				cout << "Data berhasil diurutkan berdasarkan ID." << endl;
			} else if (pilihanSort == 2) {
				sortByNama(head);
				cout << endl;
				cout << "Data berhasil diurutkan berdasarkan nama." << endl;
			} else if (pilihanSort == 3) {
				sortByStatus(head);
				cout << endl;
				cout << "Data berhasil diurutkan berdasarkan status." << endl;
			} else if (pilihanSort == 4) {
				sortByHarga(head);
				cout << endl;
				cout << "Data berhasil diurutkan berdasarkan harga." << endl;
			} else if (pilihanSort == 5) {
				sortByBerat(head);
				cout << endl;
				cout << "Data berhasil diurutkan berdasarkan berat." << endl;
			} else {
				cout << endl;
				cout << "Pilihan sorting tidak valid." << endl;
			}

		} else if (pilihanMenu == 7) {
			tampilStatistik(head);

		} else if (pilihanMenu == 8) {
			simpanKeFile(head);

		} else if (pilihanMenu == 9) {
			bacaFile(head);

		} else if (pilihanMenu == 10) {
			hapusSemuaPesanan(head);

		} else if (pilihanMenu == 11) {
			cout << endl;
			cout << "Terima kasih telah menggunakan sistem laundry." << endl;
			clearList(head);
			break;

		} else {
			cout << endl;
			cout << "Pilihan menu tidak valid." << endl;
		}

		if (pilihanMenu != 11) {
			lanjut = kembaliMenu();

			if (!lanjut) {
				cout << endl;
				cout << "Program selesai." << endl;
				clearList(head);
			}

			cout << endl;
		}

	} while (lanjut);

	return 0;
}
