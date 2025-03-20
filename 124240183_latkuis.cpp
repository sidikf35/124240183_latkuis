#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Pegawai
{
    int id;
    string nama;
    double gaji;
};

void tambahPegawai()
{
    ofstream file("pegawai.dat", ios::app | ios::binary);
    if (!file)
    {
        cerr << "Error: Tidak dapat membuka file." << endl;
        return;
    }

    cout << "===Tambah data===" << endl;

    int jumlah;
    cout << "Masukan jumlah data: ";
    cin >> jumlah;

    for (int i = 0; i < jumlah; ++i)
    {
        Pegawai pegawai;
        cout << "Masukan id: ";
        cin >> pegawai.id;
        cin.ignore();
        cout << "Masukan nama: ";
        getline(cin, pegawai.nama);
        cout << "Masukan gaji: ";
        cin >> pegawai.gaji;

        file.write(reinterpret_cast<char *>(&pegawai), sizeof(Pegawai));
        cout << "----------------------------------------" << endl;
    }

    file.close();
    cout << jumlah << " data berhasil ditambahkan" << endl;
}

int bacaSemuaPegawai(Pegawai pegawai[], int maxSize)
{
    ifstream file("pegawai.dat", ios::binary);
    if (!file)
    {
        cerr << "Error: Tidak dapat membuka file." << endl;
        return 0;
    }

    int count = 0;
    while (file.read(reinterpret_cast<char *>(&pegawai[count]), sizeof(Pegawai)) && count < maxSize)
    {
        count++;
    }

    file.close();
    return count;
}

void lihatDaftarPegawai()
{
    const int MAX_PEGawai = 100;
    Pegawai pegawai[MAX_PEGawai];

    int jumlah = bacaSemuaPegawai(pegawai, MAX_PEGawai);

    if (jumlah == 0)
    {
        cout << "Tidak ada data pegawai yang tersedia." << endl;
        return;
    }

    for (int i = 0; i < jumlah - 1; ++i)
    {
        for (int j = 0; j < jumlah - i - 1; ++j)
        {
            if (pegawai[j].id > pegawai[j + 1].id)
            {
                swap(pegawai[j], pegawai[j + 1]);
            }
        }
    }

    cout << "===Daftar Pegawai===" << endl;
    cout << "Data Pegawai yang telah diurutkan:" << endl;

    for (int i = 0; i < jumlah; ++i)
    {
        cout << "----------------------------------------" << endl;
        cout << "ID: " << pegawai[i].id << endl;
        cout << "Nama: " << pegawai[i].nama << endl;
        cout << "Gaji: Rp. " << fixed << setprecision(0) << pegawai[i].gaji << endl;
    }
    cout << "----------------------------------------" << endl;
}

void cariPegawai()
{
    const int MAX_PEGawai = 100;
    Pegawai pegawai[MAX_PEGawai];

    int jumlah = bacaSemuaPegawai(pegawai, MAX_PEGawai);

    if (jumlah == 0)
    {
        cout << "Tidak ada data pegawai yang tersedia." << endl;
        return;
    }

    int id;
    cout << "Masukan id untuk dicari: ";
    cin >> id;

    bool ditemukan = false;
    for (int i = 0; i < jumlah; ++i)
    {
        if (pegawai[i].id == id)
        {
            cout << "Pegawai di Temukan" << endl;
            cout << "----------------------------------------" << endl;
            cout << "ID: " << pegawai[i].id << endl;
            cout << "Nama: " << pegawai[i].nama << endl;
            cout << "Gaji: Rp. " << fixed << setprecision(0) << pegawai[i].gaji << endl;
            cout << "----------------------------------------" << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan)
    {
        cout << "Pegawai dengan ID " << id << " tidak ditemukan." << endl;
    }
}

void perbaruiGajiPegawai()
{
    const int MAX_PEGawai = 100;
    Pegawai pegawai[MAX_PEGawai];

    int jumlah = bacaSemuaPegawai(pegawai, MAX_PEGawai);

    if (jumlah == 0)
    {
        cout << "Tidak ada data pegawai yang tersedia." << endl;
        return;
    }

    int id;
    cout << "===Perbarui Gaji===" << endl;
    cout << "Masukan id untuk dicari: ";
    cin >> id;

    bool ditemukan = false;
    for (int i = 0; i < jumlah; ++i)
    {
        if (pegawai[i].id == id)
        {
            cout << "Pegawai di Temukan" << endl;
            cout << "----------------------------------------" << endl;
            cout << "ID: " << pegawai[i].id << endl;
            cout << "Nama: " << pegawai[i].nama << endl;
            cout << "Masukan gaji Baru: ";
            cin >> pegawai[i].gaji;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan)
    {
        cout << "Pegawai dengan ID " << id << " tidak ditemukan." << endl;
        return;
    }

    ofstream file("pegawai.dat", ios::binary);
    if (!file)
    {
        cerr << "Error: Tidak dapat membuka file." << endl;
        return;
    }

    for (int i = 0; i < jumlah; ++i)
    {
        file.write(reinterpret_cast<const char *>(&pegawai[i]), sizeof(Pegawai));
    }

    file.close();
    cout << "Gaji pegawai berhasil diperbarui!" << endl;
}

int main()
{
    int pilihan;

    do
    {
        cout << "===SI Kepegawaian===" << endl;
        cout << "1. Tambah data pegawai" << endl;
        cout << "2. Lihat data pegawai" << endl;
        cout << "3. Cari data pegawai" << endl;
        cout << "4. Perbarui gaji" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tambahPegawai();
            break;
        case 2:
            lihatDaftarPegawai();
            break;
        case 3:
            cariPegawai();
            break;
        case 4:
            perbaruiGajiPegawai();
            break;
        case 0:
            cout << "Keluar dari program. Terima kasih!" << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);

    return 0;
}