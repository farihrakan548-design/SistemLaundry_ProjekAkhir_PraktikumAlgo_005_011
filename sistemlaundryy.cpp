#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>

using namespace std;

// Struktur data utama untuk menyimpan informasi pesanan laundry
struct DataLaundry {
	int id;
	char namaPelanggan[100];
	int kodeLayanan;
	float beratKg;
	float totalHarga;
	int kodeStatus;
};

// Node linked list
struct Node {
	DataLaundry data;
	Node *next;
};

int idPelanggan = 1;

void garis() {
	cout << "========================================" << endl;
}

// Mengubah kode layanan menjadi teks
const char *namaLayanan(int kodeLayanan) {
	if (kodeLayanan == 1) {
		return "Cuci Kering";
	} else if (kodeLayanan == 2) {
		return "Cuci Setrika";
	} else if (kodeLayanan == 3) {
		return "Setrika Saja";
	}

	return "Tidak Diketahui";
}

// Mengubah kode status menjadi teks
const char *namaStatus(int kodeStatus) {
	if (kodeStatus == 1) {
		return "Sedang Antri";
	} else if (kodeStatus == 2) {
		return "Sedang Diproses";
	} else if (kodeStatus == 3) {
		return "Selesai";
	}

	return "Tidak Diketahui";
}

// Harga per Kg
float hargaPerKg(int kodeLayanan) {
	if (kodeLayanan == 1) {
		return 5000;
	} else if (kodeLayanan == 2) {
		return 8000;
	} else if (kodeLayanan == 3) {
		return 4000;
	}

	return 0;
}

// Membuat node baru
Node *buatNode(DataLaundry data) {
	Node *newNode = new Node;

	newNode->data = data;
	newNode->next = NULL;

	return newNode;
}

// Input data pesanan
int tampiljenislayanan() {
	int pilihan;

	garis();
	cout << "             JENIS LAYANAN" << endl;
	garis();
	cout << "1. Cuci Kering   - Rp 5000/Kg" << endl;
	cout << "2. Cuci Setrika  - Rp 8000/Kg" << endl;
	cout << "3. Setrika Saja  - Rp 4000/Kg" << endl;
	garis();

	cout << "Pilih layanan : ";
	cin >> pilihan;
	cin.ignore();

	if (pilihan >= 1 && pilihan <= 3) {
		return pilihan;
	}

	return 0;
}

DataLaundry inputDataPesanan() {
	DataLaundry data;

	garis();
	cout << "            INPUT PESANAN" << endl;
	garis();

	data.id = idPelanggan++;

	cout << "Masukkan nama pelanggan : ";
	cin.getline(data.namaPelanggan, 100);

	cout << "Masukkan berat cucian   : ";
	cin >> data.beratKg;
	cin.ignore();

	data.kodeLayanan = tampiljenislayanan();

	data.totalHarga =
		data.beratKg * hargaPerKg(data.kodeLayanan);

	data.kodeStatus = 1;

	return data;
}

// Cetak detail node
void cetakNode(Node *node) {
	garis();
	cout << "            DETAIL PESANAN" << endl;
	garis();

	cout << "ID Pesanan      : "
		 << node->data.id << endl;

	cout << "Nama Pelanggan  : "
		 << node->data.namaPelanggan << endl;

	cout << "Jenis Layanan   : "
		 << namaLayanan(node->data.kodeLayanan) << endl;

	cout << "Berat Cucian    : "
		 << node->data.beratKg << " Kg" << endl;

	cout << "Total Harga     : Rp "
		 << node->data.totalHarga << endl;

	cout << "Status Laundry  : "
		 << namaStatus(node->data.kodeStatus) << endl;

	garis();
}

// Tampilkan semua data
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

// Insert awal
void insertDiawal(Node *&head, DataLaundry data) {

	Node *newNode = buatNode(data);

	newNode->next = head;
	head = newNode;

	cout << endl;
	cout << "Pesanan berhasil ditambahkan di awal."
		 << endl;
}

// Insert tengah
void insertDiTengah(Node *&head, DataLaundry data) {

	Node *newNode = buatNode(data);

	if (head == NULL) {
		head = newNode;

	} else {

		int jumlah = 0;

		Node *current = head;

		while (current != NULL) {
			jumlah++;
			current = current->next;
		}

		int posisi = jumlah / 2;

		current = head;

		for (int i = 1; i < posisi; i++) {
			current = current->next;
		}

		newNode->next = current->next;
		current->next = newNode;
	}

	cout << endl;
	cout << "Pesanan berhasil ditambahkan di tengah."
		 << endl;
}

// Insert akhir
void insertDiAkhir(Node *&head, DataLaundry data) {

	Node *newNode = buatNode(data);

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
	cout << "Pesanan berhasil ditambahkan di akhir."
		 << endl;
}

// Sequential Search
Node *caribyID(Node *head, int id) {

	Node *current = head;

	while (current != NULL) {

		if (current->data.id == id) {
			return current;
		}

		current = current->next;
	}

	return NULL;
}

// Update status
void updateStatus(Node *head, int id, int statusBaru) {

	Node *current = head;

	while (current != NULL) {

		if (current->data.id == id) {

			current->data.kodeStatus = statusBaru;

			cout << endl;
			cout << "Status berhasil diupdate." << endl;

			return;
		}

		current = current->next;
	}

	cout << endl;
	cout << "Pesanan tidak ditemukan." << endl;
}

// Hapus berdasarkan ID
void hapusbyID(Node *&head, int id) {

	if (head == NULL) {
		cout << "Data kosong." << endl;
		return;
	}

	if (head->data.id == id) {

		Node *hapus = head;

		head = head->next;

		delete hapus;

		cout << "Data berhasil dihapus." << endl;

		return;
	}

	Node *current = head;

	while (current->next != NULL &&
		   current->next->data.id != id) {

		current = current->next;
	}

	if (current->next == NULL) {

		cout << "Data tidak ditemukan." << endl;

		return;
	}

	Node *hapus = current->next;

	current->next = hapus->next;

	delete hapus;

	cout << "Data berhasil dihapus." << endl;
}

// Tukar data
void nukerData(Node *a, Node *b) {

	DataLaundry temp = a->data;

	a->data = b->data;
	b->data = temp;
}

// Bubble Sort ID
void sortById(Node *head) {

	bool tukar;

	do {

		tukar = false;

		Node *current = head;

		while (current->next != NULL) {

			if (current->data.id >
				current->next->data.id) {

				nukerData(current, current->next);

				tukar = true;
			}

			current = current->next;
		}

	} while (tukar);
}

// Bubble Sort Nama
void sortByNama(Node *head) {

	bool tukar;

	do {

		tukar = false;

		Node *current = head;

		while (current->next != NULL) {

			if (strcmp(current->data.namaPelanggan,
					   current->next->data.namaPelanggan) > 0) {

				nukerData(current, current->next);

				tukar = true;
			}

			current = current->next;
		}

	} while (tukar);
}

// Bubble Sort Harga
void sortByHarga(Node *head) {

	bool tukar;

	do {

		tukar = false;

		Node *current = head;

		while (current->next != NULL) {

			if (current->data.totalHarga >
				current->next->data.totalHarga) {

				nukerData(current, current->next);

				tukar = true;
			}

			current = current->next;
		}

	} while (tukar);
}

// Statistik
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

		total += head->data.totalHarga;

		head = head->next;
	}

	return total;
}

void tampilStatistik(Node *head) {

	garis();

	cout << "          STATISTIK LAUNDRY" << endl;

	garis();

	cout << "Jumlah Pesanan  : "
		 << hitungJumlahPesanan(head) << endl;

	cout << "Total Pendapatan: Rp "
		 << hitungTotalPendapatan(head) << endl;

	garis();
}

// Simpan file TEXT
void simpanKeFile(Node *head) {

	if (head == NULL) {

		cout << endl;
		cout << "Tidak ada data." << endl;

		return;
	}

	char namaFile[100];

	cout << endl;
	cout << "Masukkan nama file : ";

	cin.getline(namaFile, 100);

	FILE *file = fopen(namaFile, "w");

	if (file == NULL) {

		cout << "File gagal dibuat." << endl;

		return;
	}

	Node *current = head;

	while (current != NULL) {

		fprintf(file, "%d\n",
				current->data.id);

		fprintf(file, "%s\n",
				current->data.namaPelanggan);

		fprintf(file, "%d\n",
				current->data.kodeLayanan);

		fprintf(file, "%.2f\n",
				current->data.beratKg);

		fprintf(file, "%.2f\n",
				current->data.totalHarga);

		fprintf(file, "%d\n",
				current->data.kodeStatus);

		current = current->next;
	}

	fclose(file);

	cout << endl;
	cout << "Data berhasil disimpan." << endl;
}

// Tambah node dari file
void tambahNodeDariFile(Node *&head,
						DataLaundry data) {

	Node *newNode = buatNode(data);

	if (head == NULL) {

		head = newNode;

	} else {

		Node *current = head;

		while (current->next != NULL) {
			current = current->next;
		}

		current->next = newNode;
	}

	if (data.id >= idPelanggan) {
		idPelanggan = data.id + 1;
	}
}

// Baca file TEXT
void bacaFile(Node *&head) {

	char namaFile[100];

	cout << endl;
	cout << "Masukkan nama file : ";

	cin.getline(namaFile, 100);

	FILE *file = fopen(namaFile, "r");

	if (file == NULL) {

		cout << "File tidak ditemukan." << endl;

		return;
	}

	DataLaundry data;

	while (fscanf(file, "%d\n", &data.id) != EOF) {

		fgets(data.namaPelanggan, 100, file);

		data.namaPelanggan[
			strcspn(data.namaPelanggan, "\n")
		] = '\0';

		fscanf(file, "%d\n",
			   &data.kodeLayanan);

		fscanf(file, "%f\n",
			   &data.beratKg);

		fscanf(file, "%f\n",
			   &data.totalHarga);

		fscanf(file, "%d\n",
			   &data.kodeStatus);

		tambahNodeDariFile(head, data);
	}

	fclose(file);

	cout << endl;
	cout << "Data berhasil dibaca." << endl;
}

// Hapus semua data
void clearList(Node *&head) {

	while (head != NULL) {

		Node *hapus = head;

		head = head->next;

		delete hapus;
	}
}

// Menu utama
void tampilmenu() {

	garis();

	cout << "          SISTEM LAUNDRY" << endl;

	garis();

	cout << "1. Tambah Pesanan" << endl;
	cout << "2. Tampilkan Semua" << endl;
	cout << "3. Cari by ID" << endl;
	cout << "4. Update Status" << endl;
	cout << "5. Hapus Pesanan" << endl;
	cout << "6. Sorting Data" << endl;
	cout << "7. Statistik" << endl;
	cout << "8. Simpan File" << endl;
	cout << "9. Baca File" << endl;
	cout << "10. Keluar" << endl;

	garis();

	cout << "Pilih menu : ";
}

int main() {

	Node *head = NULL;

	int menu;

	do {

		tampilmenu();

		cin >> menu;
		cin.ignore();

		if (menu == 1) {

			int posisi;

			cout << "1. Awal" << endl;
			cout << "2. Tengah" << endl;
			cout << "3. Akhir" << endl;

			cout << "Pilih posisi : ";

			cin >> posisi;
			cin.ignore();

			DataLaundry data =
				inputDataPesanan();

			if (posisi == 1) {

				insertDiawal(head, data);

			} else if (posisi == 2) {

				insertDiTengah(head, data);

			} else if (posisi == 3) {

				insertDiAkhir(head, data);
			}

		} else if (menu == 2) {

			cetakList(head);

		} else if (menu == 3) {

			int id;

			cout << "Masukkan ID : ";
			cin >> id;
			cin.ignore();

			Node *hasil =
				caribyID(head, id);

			if (hasil != NULL) {

				cetakNode(hasil);

			} else {

				cout << "Data tidak ditemukan."
					 << endl;
			}

		} else if (menu == 4) {

			int id, status;

			cout << "Masukkan ID : ";
			cin >> id;

			cout << "1. Sedang Antri" << endl;
			cout << "2. Sedang Diproses" << endl;
			cout << "3. Selesai" << endl;

			cout << "Pilih status : ";
			cin >> status;
			cin.ignore();

			updateStatus(head, id, status);

		} else if (menu == 5) {

			int id;

			cout << "Masukkan ID : ";
			cin >> id;
			cin.ignore();

			hapusbyID(head, id);

		} else if (menu == 6) {

			int pilihSort;

			cout << "1. Sort ID" << endl;
			cout << "2. Sort Nama" << endl;
			cout << "3. Sort Harga" << endl;

			cout << "Pilih : ";

			cin >> pilihSort;
			cin.ignore();

			if (pilihSort == 1) {

				sortById(head);

			} else if (pilihSort == 2) {

				sortByNama(head);

			} else if (pilihSort == 3) {

				sortByHarga(head);
			}

			cout << "Sorting berhasil." << endl;

		} else if (menu == 7) {

			tampilStatistik(head);

		} else if (menu == 8) {

			simpanKeFile(head);

		} else if (menu == 9) {

			bacaFile(head);

		} else if (menu == 10) {

			cout << endl;
			cout << "Terima kasih." << endl;

			clearList(head);
		}

	} while (menu != 10);

	return 0;
}