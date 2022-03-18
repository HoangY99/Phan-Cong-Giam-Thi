#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <stdbool.h>
#include <cstdlib>
#include <ctime>

using namespace std;
struct phongThi
{
	string tenPhong;
	string khu;
};
phongThi phong[40];

struct giamThi
{
	string ten, ngaySinh, donVi, stt, maGV;
	int maGT, maGTB[10], KQphong[4] = { 0,0,0,0 }; //= 0;
	int soGTB = 0;
	//long maGV;
	phongThi phongCua[10];
	giamThi() {}


};
giamThi giangVien[100];
giamThi giamThiHanhLang[100];

void docDanhSachCanBo(ifstream& myfile, giamThi giangVien[], int i) {
	getline(myfile, giangVien[i].ten, ',');
	myfile.ignore(1);
	getline(myfile, giangVien[i].maGV, ',');
	myfile.ignore(1);
}

void docDanhSachPhongThi(ifstream& myfile2, phongThi phong[], int i) {
	getline(myfile2, phong[i].tenPhong, ',');
	myfile2.ignore(1);
}

void phanCong(giamThi giangVien[], int k, int cnt, int cnt2) {
	int kq1, kq2, stt = 1;
	bool checkDaCoPhong = false, checkTrungTen = false, checkTrungGTB = false, checkTrungPhongCu = false;

	//CA THI k

	cout << endl << "Ca thi:" << k << endl;
	//lap tung phong
	for (int i = 128; i <= 167; i++) {

		//chon giam thi 1, dieu kien: chua co phong, ko trung phong cu
		srand(time(NULL));
		do {
			//reset bien check
			checkTrungGTB = false; checkDaCoPhong = false; checkTrungTen = false, checkTrungPhongCu = false;
			kq1 = 1 + (int)(rand() * (cnt - 1 + 1.0) / (1.0 + RAND_MAX));
			//cout << "ket qua 1 ne: " << kq1 << endl;
			//check da co phong chua:
			if (giangVien[kq1].KQphong[k - 1] != 0) {
				checkDaCoPhong = true;
			}//cout << "checkDaCoPhong: " << checkDaCoPhong << endl;

			//check trung phong cu:
			for (int l = 0; l <= k; l++) {
				if (i == giangVien[kq1].KQphong[l]) {
					checkTrungPhongCu = true;
				}
			}//cout << " checkTrungPhongCu: " << checkTrungPhongCu<<endl;

		} while (checkDaCoPhong || checkTrungPhongCu);

		//gan thong tin ma GT, phong cho giam thi 1
		giangVien[kq1].maGT = kq1;
		giangVien[kq1].KQphong[k - 1] = i;



		//chon giam thi 2, dieu kien: chua co phong, ko phai la giam thi 1, ko phai tung la ban giam thi cua giam thi 1
		srand(time(NULL));
		do {
			//reset bien check
			checkTrungGTB = false; checkDaCoPhong = false; checkTrungTen = false, checkTrungPhongCu = false;

			kq2 = 1 + (int)(rand() * (cnt - 1 + 1.0) / (1.0 + RAND_MAX));
			//cout <<"ket qua 2 ne: " <<kq2<<endl;

			//check da co phong chua:
			if (giangVien[kq2].KQphong[k - 1] != 0) {
				checkDaCoPhong = true;
			}//cout << "checkDaCoPhong: " << checkDaCoPhong << endl;

			//check trung ten
			if (giangVien[kq2].ten == giangVien[kq1].ten) {
				checkTrungTen = true;
			}//cout << "checkTrungTen: " << checkTrungTen << endl;

			//tim xem co kq2 trong ds giam thi ban cua giam thi 1 ko
			for (int j = 0; j <= giangVien[kq2].soGTB; j++) {
				if (kq2 == giangVien[kq1].maGTB[j]) {
					checkTrungGTB = true;

				}
			}
			//cout << "checkTrungGTB: " << checkTrungGTB << endl<<endl;

			//check trung phong cu:
			for (int l = 0; l <= k; l++) {
				if (i == giangVien[kq2].KQphong[l]) {
					checkTrungPhongCu = true;
				}
			}//cout << "checkTrungPhongCu: " << checkTrungPhongCu<<endl;


		} while (checkDaCoPhong || checkTrungTen || checkTrungGTB || checkTrungPhongCu);

		//while ( !(giangVien[kq2].KQphong == 0 && giangVien[kq2].ten != giangVien[kq1].ten && checkTrungGTB != 1) );
		//gan thong tin maGT, phong cho giam thi giam thi 2
		giangVien[kq2].maGT = kq2;
		giangVien[kq2].KQphong[k - 1] = i;
		//them vao ds giam thi ban cua giam thi 2
		giangVien[kq2].maGTB[giangVien[kq2].soGTB] = kq1;
		giangVien[kq2].soGTB++;
		//them vao ds giam thi ban cua giam thi 1
		giangVien[kq1].maGTB[giangVien[kq1].soGTB] = kq2;
		giangVien[kq1].soGTB++;




		/*cout << "PHONG: " << i << endl;
		cout << "giam thi 1: " << endl;
		cout << giangVien[kq1].ten << "    Phong: " << giangVien[kq1].KQphong << "	maGT: "<< kq1 << "   maGTB: " << giangVien[kq1].maGTB<<endl;
		cout << "giam thi 2: " << endl;
		cout << giangVien[kq2].ten << "    Phong: " << giangVien[kq2].KQphong << "	maGT: " << kq2 << "   maGTB: " << giangVien[kq2].maGTB << endl;*/

		cout << "	" << "PHONG: " << i << endl;

		const char separator = ' ';
		const int namewidth = 10;
		const int numwidth = 12;




		cout << "+" << left << setw(20) << setfill(separator) << "--------------------";
		cout << "+" << left << setw(15) << setfill(separator) << "---------------";
		cout << "+" << left << setw(15) << setfill(separator) << "---------------";
		cout << "+" << left << setw(15) << setfill(separator) << "---------------";
		cout << "+" << left << setw(15) << setfill(separator) << "---------------";
		cout << "+" << left << setw(15) << setfill(separator) << "---------------"
			<< "|" << endl;
		if (1)
		{


			cout << "|" << left << setw(20) << setfill(separator) << "ten";
			cout << "|" << left << setw(15) << setfill(separator) << "giam thi";
			cout << "|" << left << setw(15) << setfill(separator) << "phong";
			cout << "|" << left << setw(15) << setfill(separator) << "ma gt";
			cout << "|" << left << setw(15) << setfill(separator) << "ma gtb";
			cout << "|" << left << setw(15) << setfill(separator) << "ds ma gtb"
				<< "|" << endl;



			cout << "+" << left << setw(20) << setfill(separator) << "--------------------";
			cout << "+" << left << setw(15) << setfill(separator) << "---------------";
			cout << "+" << left << setw(15) << setfill(separator) << "---------------";
			cout << "+" << left << setw(15) << setfill(separator) << "---------------";
			cout << "+" << left << setw(15) << setfill(separator) << "---------------";
			cout << "+" << left << setw(15) << setfill(separator) << "---------------"
				<< "|" << endl;
		}


		cout << "|" << left << setw(20) << setfill(separator) << giangVien[kq1].ten;
		cout << "|" << left << setw(15) << setfill(separator) << "giam thi 1";
		cout << "|" << left << setw(15) << setfill(separator) << giangVien[kq1].KQphong[k - 1];
		cout << "|" << left << setw(15) << setfill(separator) << giangVien[kq1].maGT;
		cout << "|" << left << setw(15) << setfill(separator) << giangVien[kq1].maGTB[giangVien[kq1].soGTB - 1];
		cout << "|" << left << setw(15) << setfill(separator) << giangVien[kq1].maGTB[0] << " " << giangVien[kq1].maGTB[1] << " " << giangVien[kq1].maGTB[2] << " " << giangVien[kq1].soGTB << " " << checkTrungGTB << "|" << endl;

		cout << "+" << left << setw(15) << setfill(separator) << "---------------";
		cout << "+" << left << setw(20) << setfill(separator) << "--------------------";
		cout << "+" << left << setw(15) << setfill(separator) << "---------------";
		cout << "+" << left << setw(15) << setfill(separator) << "---------------";
		cout << "+" << left << setw(15) << setfill(separator) << "---------------";
		cout << "+" << left << setw(15) << setfill(separator) << "---------------"
			<< "|";

		cout << "|" << left << setw(15) << setfill(separator) << "giam thi 2";
		cout << "|" << left << setw(20) << setfill(separator) << giangVien[kq2].ten;
		cout << "|" << left << setw(15) << setfill(separator) << giangVien[kq2].KQphong[k - 1];
		cout << "|" << left << setw(15) << setfill(separator) << giangVien[kq2].maGT;
		cout << "|" << left << setw(15) << setfill(separator) << giangVien[kq2].maGTB[giangVien[kq2].soGTB - 1];
		cout << "|" << left << setw(15) << setfill(separator) << giangVien[kq2].maGTB[0] << " " << giangVien[kq2].maGTB[1] << " " << giangVien[kq2].maGTB[2] << " " << giangVien[kq2].soGTB << "|" << endl;

		cout << "+" << left << setw(15) << setfill(separator) << "---------------";
		cout << "+" << left << setw(20) << setfill(separator) << "--------------------";
		cout << "+" << left << setw(15) << setfill(separator) << "---------------";
		cout << "+" << left << setw(15) << setfill(separator) << "---------------";
		cout << "+" << left << setw(15) << setfill(separator) << "---------------";
		cout << "+" << left << setw(15) << setfill(separator) << "---------------"
			<< "|" << endl;

		//ghi vao file
		fstream f;
		f.open("dsCoiThi.txt", ios::out | ios::app);
		f << giangVien[kq1].ten << ", " << giangVien[kq1].maGV << ", " << "giam thi 1" << ", " << i;
		stt++;
		f << giangVien[kq2].ten << ", " << giangVien[kq2].maGV << ", " << "giam thi 2" << ", " << i;
		f.close();
		stt++;

	}

	//Phan cong giam thi hanh lang
	int soGiamThiHanhLang = 0, soPhongDuocGiamSatBoiMotGiamThiHanhLang = 0;
	for (int i = 0; i <= cnt; i++) {
		if (giangVien[i].KQphong[k - 1] == 0) {

			giamThiHanhLang[soGiamThiHanhLang] = giangVien[i];
			soGiamThiHanhLang++;
		}
		soPhongDuocGiamSatBoiMotGiamThiHanhLang = cnt2 / soGiamThiHanhLang;
	}
	cout << endl << "so giam thi hanh la ca " << k << ": " << soGiamThiHanhLang << " " << soPhongDuocGiamSatBoiMotGiamThiHanhLang << endl;
	//ghi vao file
	int phongBatDau = 128, phongKetThuc;
	fstream f2;
	f2.open("dsGiamSat.txt", ios::out | ios::app);
	for (int i = 0; i < soGiamThiHanhLang; i++) {
		phongKetThuc = phongBatDau + soPhongDuocGiamSatBoiMotGiamThiHanhLang;
		f2 << giamThiHanhLang[i].ten << ", " << giamThiHanhLang[i].maGV << ", " << phongBatDau << ", " << phongKetThuc;
		phongBatDau = phongKetThuc;
	}
	f2 << "\n";
	f2.close();

}


int main() {

	//doc ds canbo
	ifstream myfile("dsCanBo.txt");
	int cnt = 0;
	string mytext;
	while (getline(myfile, mytext))
		cnt++;
	myfile.close();
	myfile.open("dsCanBo.txt");

	for (int i = 0; i <= cnt - 1; i++)
	{
		docDanhSachCanBo(myfile, giangVien, i);

	}

	//doc ds phong thi
	ifstream myfile2("dsPhongThi.txt");
	int cnt2 = 0;
	string mytext2;
	while (getline(myfile2, mytext2))
		cnt2++;
	myfile2.close();
	myfile2.open("dsPhongThi.txt");

	for (int i = 0; i <= cnt2 - 1; i++)
	{
		docDanhSachPhongThi(myfile2, phong, i);

	}

	//goi ham phan cong
	phanCong(giangVien, 2, cnt, cnt2);
	phanCong(giangVien, 3, cnt, cnt2);
	phanCong(giangVien, 4, cnt, cnt2);

	cout << endl << cnt << " " << cnt2;

	return 0;
}
