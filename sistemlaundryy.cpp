#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

// Struktur data untuk menyimpan informasi pesanan laundry
struct Node {
	int id;
	char namaPelanggan[100];
	char jenisLayanan[50];
	float beratKg;
	float totalHarga;
	char status[50];
	Node *next;
};

int idPelanggan = 1;

void garis() {
	cout << "========================================" << endl;
}

// Fungsi untuk menyalin teks tanpa string.h
void salinTeks(char tujuan[], const char sumber[]) {
	int i = 0;

	while (sumber[i] != '\0') {
		tujuan[i] = sumber[i];
		i++;
	}

	tujuan[i] = '\0';
}

// Fungsi untuk membandingkan dua teks tanpa string.h
int bandingTeks(const char a[], const char b[]) {
	int i = 0;

	while (a[i] != '\0' && b[i] != '\0') {
		if (a[i] < b[i]) {
			return -1;
		} else if (a[i] > b[i]) {
			return 1;
		}

		i++;
	}

	if (a[i] == '\0' && b[i] == '\0') {
		return 0;
	} else if (a[i] == '\0') {
		return -1;
	} else {
		return 1;
	}
}

// Fungsi untuk mengecek dua teks sama atau tidak
bool samaTeks(const char a[], const char b[]) {
	return bandingTeks(a, b) == 0;
}

// Fungsi untuk menghapus enter dari hasil fgets
void hapusEnter(char teks[]) {
	int i = 0;

	while (teks[i] != '\0') {
		if (teks[i] == '\n' || teks[i] == '\r') {
			teks[i] = '\0';
			return;
		}

		i++;
	}
}

// Fungsi untuk menanyakan apakah pengguna ingin kembali ke menu utama
bool kembaliMenu() {
	char pilih;

	cout << endl;
	cout << "Kembali ke menu utama? (Y/N): ";
	cin >> pilih;
	cin.ignore();

	return pilih == 'Y' || pilih == 'y';
}

// Fungsi untuk membuat node baru dengan data pesanan laundry
Node *buatNode(const char nama[], const char layanan[], float berat) {
	Node *newNode = new Node;

	newNode->id = idPelanggan++;
	salinTeks(newNode->namaPelanggan, nama);
	salinTeks(newNode->jenisLayanan, layanan);
	newNode->beratKg = berat;
	salinTeks(newNode->status, "Sedang Antri");
	newNode->next = NULL;

	float hargaPerKg = 0;

	if (samaTeks(layanan, "Cuci Kering")) {
		hargaPerKg = 5000;
	} else if (samaTeks(layanan, "Cuci Setrika")) {
		hargaPerKg = 8000;
	} else if (samaTeks(layanan, "Setrika Saja")) {
		hargaPerKg = 4000;
	}

	newNode->totalHarga = berat * hargaPerKg;

	return newNode;
}

// Fungsi untuk mencetak detail pesanan laundry
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

// Fungsi untuk mencetak semua pesanan laundry dalam bentuk daftar
void cetakList(Node *head) {
	if (head == NULL) {
		cout << endl;
		cout << "Belum ada pesanan laundry." << endl;
		return;
	}

	Node *current = head;

	while (current != NULL) {
		cetakNode(current);
		current = current->next;
	}
}

// Fungsi untuk menampilkan pilihan jenis layanan laundry
void tampiljenislayanan(char jenisLayanan[]) {
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
		salinTeks(jenisLayanan, "Cuci Kering");
	} else if (pilihan == 2) {
		salinTeks(jenisLayanan, "Cuci Setrika");
	} else if (pilihan == 3) {
		salinTeks(jenisLayanan, "Setrika Saja");
	} else {
		salinTeks(jenisLayanan, "");
	}
}

// Fungsi untuk menginput data pesanan laundry dari pengguna
void inputDataPesanan(char nama[], float &berat, char jenisLayanan[]) {
	garis();
	cout << "            INPUT PESANAN" << endl;
	garis();

	cout << "Masukkan nama pelanggan : ";
	cin.getline(nama, 100);

	cout << "Masukkan berat cucian   : ";
	cin >> berat;
	cin.ignore();

	tampiljenislayanan(jenisLayanan);
}

// Fungsi untuk menambahkan pesanan laundry baru di awal
void insertDiawal(Node *&head, const char nama[], const char layanan[], float berat) {
	Node *newNode = buatNode(nama, layanan, berat);

	newNode->next = head;
	head = newNode;

	cout << endl;
	cout << "Pesanan berhasil ditambahkan di awal." << endl;
	cout << "ID Pesanan : " << newNode->id << endl;
}

// Fungsi untuk menambahkan pesanan laundry baru di tengah
void insertDiTengah(Node *&head, const char nama[], const char layanan[], float berat) {
	Node *newNode = buatNode(nama, layanan, berat);

	if (head == NULL) {
		head = newNode;
	} else {
		Node *current = head;

		while (current->next != NULL) {
			current = current->next;
		}

		current->next = newNode;
	}

	cout << endl;
	cout << "Pesanan berhasil ditambahkan di tengah." << endl;
	cout << "ID Pesanan : " << newNode->id << endl;
}

// Fungsi untuk menambahkan pesanan laundry baru di akhir
void insertDiAkhir(Node *&head, const char nama[], const char layanan[], float berat) {
	Node *newNode = buatNode(nama, layanan, berat);

	if (head == NULL) {
		head = newNode;
	} else {
		Node *current = head;

		while (current->next != NULL) {
			current = current->next;
		}

		current->next = newNode;
	}

	cout << endl;
	cout << "Pesanan berhasil ditambahkan di akhir." << endl;
	cout << "ID Pesanan : " << newNode->id << endl;
}

// Fungsi untuk menghapus pesanan laundry berdasarkan ID
void hapusbyID(Node *&head, int id) {
	if (head == NULL) {
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

	while (current->next != NULL && current->next->id != id) {
		current = current->next;
	}

	if (current->next == NULL) {
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

// Fungsi untuk memperbarui status pesanan laundry berdasarkan ID
void updateStatus(Node *head, int id, const char newStatus[]) {
	Node *current = head;

	while (current != NULL) {
		if (current->id == id) {
			salinTeks(current->status, newStatus);

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

// Fungsi untuk mencari pesanan laundry berdasarkan ID
Node *caribyID(Node *head, int id) {
	Node *current = head;

	while (current != NULL) {
		if (current->id == id) {
			return current;
		}

		current = current->next;
	}

	return NULL;
}

int hitungJumlahPesanan(Node *head) {
	int jumlah = 0;

	while (head != NULL) {
		jumlah++;
		head = head->next;
	}

	return jumlah;
}

float hitungTotalPendapatan(Node *head) {
	float total = 0;

	while (head != NULL) {
		total += head->totalHarga;
		head = head->next;
	}

	return total;
}

int hitungPesananSelesai(Node *head) {
	int jumlah = 0;

	while (head != NULL) {
		if (samaTeks(head->status, "Selesai")) {
			jumlah++;
		}

		head = head->next;
	}

	return jumlah;
}

// Fungsi untuk menampilkan statistik laundry
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

	char tempNama[100];
	salinTeks(tempNama, a->namaPelanggan);
	salinTeks(a->namaPelanggan, b->namaPelanggan);
	salinTeks(b->namaPelanggan, tempNama);

	char tempLayanan[50];
	salinTeks(tempLayanan, a->jenisLayanan);
	salinTeks(a->jenisLayanan, b->jenisLayanan);
	salinTeks(b->jenisLayanan, tempLayanan);

	float tempBerat = a->beratKg;
	a->beratKg = b->beratKg;
	b->beratKg = tempBerat;

	float tempHarga = a->totalHarga;
	a->totalHarga = b->totalHarga;
	b->totalHarga = tempHarga;

	char tempStatus[50];
	salinTeks(tempStatus, a->status);
	salinTeks(a->status, b->status);
	salinTeks(b->status, tempStatus);
}

// Fungsi untuk mengurutkan pesanan laundry berdasarkan ID
void sortById(Node *head) {
	if (head == NULL) {
		return;
	}
	bool tukar;
	Node *current;
	do {
		tukar = false;
		current = head;
		while (current->next != NULL) {
			if (current->id > current->next->id) {
				nukerData(current, current->next);
				tukar = true;
			}
			current = current->next;
		}
	} while (tukar);
}

// Fungsi untuk mengurutkan pesanan laundry berdasarkan nama pelanggan
void sortByNama(Node *head) {
	if (head == NULL) {
		return;
	}
	bool tukar;
	Node *current;
	do {
		tukar = false;
		current = head;
		while (current->next != NULL) {
			if (bandingTeks(current->namaPelanggan,
							current->next->namaPelanggan) > 0) {
				nukerData(current, current->next);
				tukar = true;
			}
			current = current->next;
		}
	} while (tukar);
}

// Fungsi untuk mengurutkan pesanan laundry berdasarkan status
void sortByStatus(Node *head) {
	if (head == NULL) {
		return;
	}
	bool tukar;
	Node *current;
	do {
		tukar = false;
		current = head;
		while (current->next != NULL) {
			if (bandingTeks(current->status,
							current->next->status) > 0) {
				nukerData(current, current->next);
				tukar = true;
			}
			current = current->next;
		}
	} while (tukar);
}

// Fungsi untuk mengurutkan pesanan laundry berdasarkan harga
void sortByHarga(Node *head) {
	if (head == NULL) {
		return;
	}
	bool tukar;
	Node *current;
	do {
		tukar = false;
		current = head;
		while (current->next != NULL) {
			if (current->totalHarga >
				current->next->totalHarga) {

				nukerData(current, current->next);
				tukar = true;
			}
			current = current->next;
		}
	} while (tukar);
}

// Fungsi untuk mengurutkan pesanan laundry berdasarkan berat
void sortByBerat(Node *head) {
	if (head == NULL) {
		return;
	}
	bool tukar;
	Node *current;
	do {
		tukar = false;
		current = head;
		while (current->next != NULL) {
			if (current->beratKg >
				current->next->beratKg) {
				nukerData(current, current->next);
				tukar = true;
			}
			current = current->next;
		}
	} while (tukar);
}

// Fungsi untuk menghapus semua pesanan laundry dari daftar
void clearList(Node *&head) {
	while (head != NULL) {
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

// Fungsi untuk menambahkan node pesanan laundry dari data yang dibaca dari file
void tambahNodeDariFile(Node *&head, int id, const char nama[], const char layanan[],
						float berat, float harga, const char status[]) {
	Node *newNode = new Node;

	newNode->id = id;
	salinTeks(newNode->namaPelanggan, nama);
	salinTeks(newNode->jenisLayanan, layanan);
	newNode->beratKg = berat;
	newNode->totalHarga = harga;
	salinTeks(newNode->status, status);
	newNode->next = NULL;

	if (id >= idPelanggan) {
		idPelanggan = id + 1;
	}

	if (head == NULL) {
		head = newNode;
	} else {
		Node *current = head;

		while (current->next != NULL) {
			current = current->next;
		}

		current->next = newNode;
	}
}

// Fungsi untuk menyimpan data pesanan laundry ke file menggunakan stdio.h
void simpanKeFile(Node *head) {
	char namaFile[100];

	cout << endl;
	cout << "Masukkan nama file untuk menyimpan data: ";
	cin.getline(namaFile, 100);

	FILE *file;
	file = fopen(namaFile, "w");

	if (file == NULL) {
		cout << endl;
		cout << "File gagal dibuat." << endl;
		return;
	}

	Node *current = head;

	while (current != NULL) {
		fprintf(file, "%d\n", current->id);
		fprintf(file, "%s\n", current->namaPelanggan);
		fprintf(file, "%s\n", current->jenisLayanan);
		fprintf(file, "%.2f\n", current->beratKg);
		fprintf(file, "%.2f\n", current->totalHarga);
		fprintf(file, "%s\n", current->status);

		current = current->next;
	}

	fclose(file);

	cout << endl;
	cout << "Data berhasil disimpan ke file: " << namaFile << endl;
}

// Fungsi untuk membaca data pesanan laundry dari file menggunakan stdio.h
void bacaFile(Node *&head) {
	char namaFile[100];

	cout << endl;
	cout << "Masukkan nama file yang ingin dibaca: ";
	cin.getline(namaFile, 100);

	FILE *file;
	file = fopen(namaFile, "r");

	if (file == NULL) {
		cout << endl;
		cout << "File tidak ditemukan." << endl;
		return;
	}

	clearList(head);
	idPelanggan = 1;

	char baris[200];
	char nama[100];
	char layanan[50];
	char status[50];

	int id;
	float berat;
	float harga;

	while (fgets(baris, 200, file) != NULL) {
		hapusEnter(baris);
		id = atoi(baris);

		if (fgets(nama, 100, file) == NULL) {
			break;
		}
		hapusEnter(nama);

		if (fgets(layanan, 50, file) == NULL) {
			break;
		}
		hapusEnter(layanan);

		if (fgets(baris, 200, file) == NULL) {
			break;
		}
		hapusEnter(baris);
		berat = atof(baris);

		if (fgets(baris, 200, file) == NULL) {
			break;
		}
		hapusEnter(baris);
		harga = atof(baris);

		if (fgets(status, 50, file) == NULL) {
			break;
		}
		hapusEnter(status);

		tambahNodeDariFile(head, id, nama, layanan, berat, harga, status);
	}

	fclose(file);

	cout << endl;
	cout << "Data berhasil dibaca dari file: " << namaFile << endl;

	cetakList(head);
}

// Fungsi untuk menampilkan menu utama sistem laundry
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

// Fungsi utama untuk menjalankan program sistem laundry
int main() {
	Node *head = NULL;

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

			char nama[100];
			char jenisLayanan[50];
			float berat;

			inputDataPesanan(nama, berat, jenisLayanan);

			if (!samaTeks(jenisLayanan, "") && berat > 0) {
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

			if (foundNode != NULL) {
				cetakNode(foundNode);
			} else {
				cout << endl;
				cout << "Pesanan tidak ditemukan." << endl;
			}

		} else if (pilihanMenu == 4) {
			int idUpdate;
			int pilihanStatus;
			char newStatus[50];

			salinTeks(newStatus, "");

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
				salinTeks(newStatus, "Sedang Antri");
			} else if (pilihanStatus == 2) {
				salinTeks(newStatus, "Sedang Diproses");
			} else if (pilihanStatus == 3) {
				salinTeks(newStatus, "Selesai");
			}

			if (!samaTeks(newStatus, "")) {
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

			if (head == NULL) {
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
