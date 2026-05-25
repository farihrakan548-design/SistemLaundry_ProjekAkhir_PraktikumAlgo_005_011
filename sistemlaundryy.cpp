#include <iostream>
#include <stdlib.h>
#include <stdio.h>
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

// Node linked list menyimpan satu data laundry
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
	} else {
		return "Tidak Diketahui";
	}
}

// Mengubah kode status menjadi teks
const char *namaStatus(int kodeStatus) {
	if (kodeStatus == 1) {
		return "Sedang Antri";
	} else if (kodeStatus == 2) {
		return "Sedang Diproses";
	} else if (kodeStatus == 3) {
		return "Selesai";
	} else {
		return "Tidak Diketahui";
	}
}

// Menentukan harga per kg berdasarkan kode layanan
float hargaPerKg(int kodeLayanan) {
	if (kodeLayanan == 1) {
		return 5000;
	} else if (kodeLayanan == 2) {
		return 8000;
	} else if (kodeLayanan == 3) {
		return 4000;
	} else {
		return 0;
	}
}

bool kembaliMenu() {
	char pilih;

	cout << endl;
	cout << "Kembali ke menu utama? (Y/N): ";
	cin >> pilih;
	cin.ignore();

	return pilih == 'Y' || pilih == 'y';
}

int tampiljenislayanan() {
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

	if (pilihan >= 1 && pilihan <= 3) {
		return pilihan;
	} else {
		return 0;
	}
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
	data.totalHarga = data.beratKg * hargaPerKg(data.kodeLayanan);
	data.kodeStatus = 1;

	return data;
}

Node *buatNode(DataLaundry data) {
	Node *newNode = new Node;

	newNode->data = data;
	newNode->next = NULL;

	return newNode;
}

void cetakNode(Node *node) {
	garis();
	cout << "            DETAIL PESANAN" << endl;
	garis();
	cout << "ID Pesanan      : " << node->data.id << endl;
	cout << "Nama Pelanggan  : " << node->data.namaPelanggan << endl;
	cout << "Jenis Layanan   : " << namaLayanan(node->data.kodeLayanan) << endl;
	cout << "Berat Cucian    : " << node->data.beratKg << " Kg" << endl;
	cout << "Total Harga     : Rp " << node->data.totalHarga << endl;
	cout << "Status Laundry  : " << namaStatus(node->data.kodeStatus) << endl;
	garis();
}

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

void insertDiawal(Node *&head, DataLaundry data) {
	Node *newNode = buatNode(data);

	newNode->next = head;
	head = newNode;

	cout << endl;
	cout << "Pesanan berhasil ditambahkan di awal." << endl;
	cout << "ID Pesanan : " << newNode->data.id << endl;
}

void insertDiTengah(Node *&head, DataLaundry data) {
	Node *newNode = buatNode(data);

	if (head == NULL) {
		head = newNode;
	} else if (head->next == NULL) {
		head->next = newNode;
	} else {
		int jumlah = 0;
		Node *current = head;

		while (current != NULL) {
			jumlah++;
			current = current->next;
		}

		int posisiTengah = jumlah / 2;
		current = head;

		for (int i = 1; i < posisiTengah; i++) {
			current = current->next;
		}

		newNode->next = current->next;
		current->next = newNode;
	}

	cout << endl;
	cout << "Pesanan berhasil ditambahkan di tengah." << endl;
	cout << "ID Pesanan : " << newNode->data.id << endl;
}

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
	cout << "Pesanan berhasil ditambahkan di akhir." << endl;
	cout << "ID Pesanan : " << newNode->data.id << endl;
}

void hapusbyID(Node *&head, int id) {
	if (head == NULL) {
		cout << endl;
		cout << "Daftar pesanan kosong." << endl;
		return;
	}

	if (head->data.id == id) {
		Node *toDelete = head;
		head = head->next;

		cout << endl;
		cout << "Pesanan ID " << id << " atas nama "
			 << toDelete->data.namaPelanggan << " berhasil dihapus." << endl;

		delete toDelete;
		return;
	}

	Node *current = head;

	while (current->next != NULL && current->next->data.id != id) {
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
		 << toDelete->data.namaPelanggan << " berhasil dihapus." << endl;

	delete toDelete;
}

void updateStatus(Node *head, int id, int kodeStatusBaru) {
	Node *current = head;

	while (current != NULL) {
		if (current->data.id == id) {
			current->data.kodeStatus = kodeStatusBaru;

			cout << endl;
			cout << "Status pesanan berhasil diperbarui." << endl;
			cout << "ID Pesanan  : " << id << endl;
			cout << "Status Baru : " << namaStatus(kodeStatusBaru) << endl;
			return;
		}

		current = current->next;
	}

	cout << endl;
	cout << "Pesanan tidak ditemukan." << endl;
}

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

int hitungPesananSelesai(Node *head) {
	int jumlah = 0;

	while (head != NULL) {
		if (head->data.kodeStatus == 3) {
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
	DataLaundry temp = a->data;
	a->data = b->data;
	b->data = temp;
}

void sortById(Node *head) {
	Node *current = head;

	while (current != NULL) {
		Node *minNode = current;
		Node *nextNode = current->next;

		while (nextNode != NULL) {
			if (nextNode->id < minNode->id) {
				minNode = nextNode;
			}

			nextNode = nextNode->next;
		}

		nukerData(current, minNode);
		current = current->next;
	}
}

// Fungsi untuk mengurutkan pesanan laundry berdasarkan nama pelanggan
void sortByNama(Node *head) {
	Node *current = head;

	while (current != NULL) {
		Node *minNode = current;
		Node *nextNode = current->next;

		while (nextNode != NULL) {
			if (bandingTeks(nextNode->namaPelanggan, minNode->namaPelanggan) < 0) {
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

	while (current != NULL) {
		Node *minNode = current;
		Node *nextNode = current->next;

		while (nextNode != NULL) {
			if (bandingTeks(nextNode->status, minNode->status) < 0) {
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

	while (current != NULL) {
		Node *minNode = current;
		Node *nextNode = current->next;

		while (nextNode != NULL) {
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

	while (current != NULL) {
		Node *minNode = current;
		Node *nextNode = current->next;

		while (nextNode != NULL) {
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
	while (head != NULL) {
		Node *toDelete = head;
		head = head->next;
		delete toDelete;
	}
}

void hapusSemuaPesanan(Node *&head) {
	clearList(head);
	idPelanggan = 1;

	cout << endl;
	cout << "Semua pesanan berhasil dihapus." << endl;
}

void tambahNodeDariFile(Node *&head, DataLaundry data) {
	Node *newNode = buatNode(data);

	if (data.id >= idPelanggan) {
		idPelanggan = data.id + 1;
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

void simpanKeFile(Node *head) {
	if (head == NULL) {
		cout << endl;
		cout << "Tidak ada data untuk disimpan." << endl;
		return;
	}

	char namaFile[100];

	cout << endl;
	cout << "Masukkan nama file untuk menyimpan data: ";
	cin.getline(namaFile, 100);

	FILE *file;
	file = fopen(namaFile, "wb");

	if (file == NULL) {
		cout << endl;
		cout << "File gagal dibuat." << endl;
		return;
	}

	Node *current = head;

	while (current != NULL) {
		fwrite(&current->data, sizeof(DataLaundry), 1, file);
		current = current->next;
	}

	fclose(file);

	cout << endl;
	cout << "Data berhasil disimpan ke file: " << namaFile << endl;
}

void bacaFile(Node *&head) {
	char namaFile[100];

	cout << endl;
	cout << "Masukkan nama file yang ingin dibaca: ";
	cin.getline(namaFile, 100);

	FILE *file;
	file = fopen(namaFile, "rb");

	if (file == NULL) {
		cout << endl;
		cout << "File tidak ditemukan." << endl;
		return;
	}

	clearList(head);
	idPelanggan = 1;

	DataLaundry data;

	while (fread(&data, sizeof(DataLaundry), 1, file) == 1) {
		tambahNodeDariFile(head, data);
	}

	fclose(file);

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

			DataLaundry data = inputDataPesanan();

			if (data.kodeLayanan != 0 && data.beratKg > 0) {
				if (pilihanTambah == 1) {
					insertDiawal(head, data);
				} else if (pilihanTambah == 2) {
					insertDiTengah(head, data);
				} else if (pilihanTambah == 3) {
					insertDiAkhir(head, data);
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

			if (pilihanStatus >= 1 && pilihanStatus <= 3) {
				updateStatus(head, idUpdate, pilihanStatus);
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
			cout << "2. Sort by Status" << endl;
			cout << "3. Sort by Harga" << endl;
			cout << "4. Sort by Berat" << endl;
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
				sortByStatus(head);
				cout << endl;
				cout << "Data berhasil diurutkan berdasarkan status." << endl;
			} else if (pilihanSort == 3) {
				sortByHarga(head);
				cout << endl;
				cout << "Data berhasil diurutkan berdasarkan harga." << endl;
			} else if (pilihanSort == 4) {
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
