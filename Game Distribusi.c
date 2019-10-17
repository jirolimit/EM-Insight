/*syarat : 
1.array 
2.Struck

struck : 
nama, npm dan kelas digabungin (3 kesamping banyak kebawah, dimensi 2 batasnya)

3.Fungsi,passing point cth: tampilkan (int a, int b); int a dan b merupakan passing point

syarat tambahan
1.Explore fungsional mis : library GTK untuk mengganti interface lebih menarik, library plot grafik.

minggu depan tunjukkan program.

anda kerja dalam bidang apapun, biasanya cari library.
untuk mempersimple gunakan aplikasi yang sama untuk uas juga hanya dikembangkan.
*/

/*Tema Gatrik, mis : suatu perusahaan ingin menganalisis spek pembangkit yang ingin 
dia operasikan pada suatu kabupaten dimana kabupaten terdiri dari 2 desa
dengan pembangkit harus bisa membackup kabupaten lain disekitarnya. 
Seandainya load berubah ubah tiap waktu dan 
tunjukkan mekanisme untuk distribusi saat keadaan darurat terjadi.
Pengunaan Array pada variasi load setiap rumah misal: [R1  12; 13 R2 ] [i1;i2]= output V
Pengunaan struck pendataan desa yang wajib dan backup
Fungsi lakukan modular saja
input: beban, SDA, plot Fasa pengaruh beban dan SDA, SDA kurang kasih notifikasi, aktifkan generator tambahan
SDA !!!algoritma untuk menangani itu!!!.
mis er= 70 = 1-100 if G=1-70 error 
Nama desa, Prioritas desa,*/

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <strings.h>

int lastStatus[10]; //status Generator. terdapat constrain 10 generator.

int ssalah(const char *const message)
{
   int nilai;

    printf("%s > ", message);
    while (scanf("%d", &nilai) != 1)
    { 
        int chr;
        printf("\tMasukkan angka \n");
        do {
            chr = getchar();
        } while ((chr != EOF) && (chr != '\n'));
        printf("%s > ", message);
    }
    return nilai;
}

int salah(const char *const message)
{
   int nilai;

    printf("%s > ", message);
    while ((scanf("%d", &nilai) != 1) || nilai<1|| nilai>10)
    { 
        int chr;
        printf("\tMasukkan 1->10\n");
        do {
            chr = getchar();
        } while ((chr != EOF) && (chr != '\n'));
        printf("%s > ", message);
    }
    return nilai;
}

int cs(int G){
	int id;
	
	for(id=0;id<G;id++){
		printf("Generator%d berstatus %d\n",id+1,lastStatus[id]);
	}
}

void setOn(int Id, int isOn){
	//Method ini harus anda gunakan untuk mengupdate status Generator di database di cloud.
	//GenId adalah ID Generator yang diset statusnya. isOn = 1 artinya menyala, isOn = 0 artinya mati.
	//lakukan sesuatu di sini untuk mengupdate status Generator
	lastStatus[Id]=isOn;
}

double Power(double a, double b){
	double I,R,P;
	I=a/b;
	printf("masukkan beban pengguna!\n");
	R=ssalah("Beban Listrik Pengguna?");
	P=(pow(I,2))*R;
	return P;
}
/*int getStatus(int GId){
	return lastStatus[GId];
}*/

//notifikasi ke konsumer dan mitra
int Notif(){
	printf("\nhubungi Pak Ucup, Pengusaha Listrik Murah\n");
	//jawabannya random;
	printf("hubungi Pak Ichat, Konglomerat selalu ada tapi mahal\n");
	//charge;
	printf("minta maaf ke warga\n");
}

//sistem mematikan hidupkan secara otomatis
double Oprec(double P, int G){
	int id,On,cd;
	id=G-1;
	id=0;
	cd=id;

	while (On*10<P){ //10 merupakan asumsi kapasitas generator
		//lakukan cek Onnya dlu
		//bandingkan daya dari generator nyala dengan P beban
		setOn(cd,1);
		On=0;
		
		for(id=0;id<G;id++){	
			On+=lastStatus[id];
		}
		
		printf("Generator %d berstatus %d\n",cd+1,lastStatus[cd]);
		cd++;	
		
		if(On==G&&G*10<P){
			Notif();
			break;
		}
	}
	
	printf("Jumlah generator nyala %d saat daya sebesar %lf\n",On,P);
}

//manual mati hidupkan generator in case generator dengan id tertentu perlu maintanence dll.
int manual(int G){
	char perintah[100];
	int id;
	//int Jack[id];
	printf("contoh:(1 off) atau (1 selesai)\n" );
	while(strcasecmp(perintah,"selesai")!=0){
		printf("\t pilihanmu?");
		scanf("%d %s",&id,&perintah);
		
		if(strcasecmp(perintah,"on")==0){
			setOn(id-1,1);
		}
		else if(strcasecmp(perintah,"off")==0){
			setOn(id-1,0);
		}
	}
}

//Program otomasi contohnya 2x2
double Operasi(){
	double P;
	int n;
	srand(time(0));
	n=rand()%10+1;//bikin jumlah loop random antara 1-10
	double matrix[n][n];
	double ratio, deta, detb;
	double ma[n][n];
	double mb[n][1];//n sesuai jumlah loop cuma kebawah saja untuk kesamping 1
	int i, j, k;
    //bakal tetap sama nilainya (gak random lagi) kalo hilang
    printf("matrix atas:\n");
	for(i = 0; i <n ; i++){
        for(j = 0; j < n; j++){   
			if(j==n-1){
				matrix[i][j]=rand()%10 + 1;
    		}
			else{
				matrix[i][j]=rand()%100 + 100;
			}
			printf("%lf\t\t ", matrix[i][j]);
		}
	printf("\n\n");
	}
	
	//menyimpan nilai matrix buat mencari determinan bawah karena pas pengolahan bakal berubah;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            ma[i][j]=matrix[i][j];
        }
    }
    //langkah pertama cari determinan atas
	/* Conversion of matrix to upper triangular */
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(j>i){
                ratio = matrix[j][i]/matrix[i][i];
                for(k = 0; k < n; k++){
                    matrix[j][k] -= ratio * matrix[i][k];
                }
            }
        }
    }
    deta = 1; //storage for determinant
    for(i = 0; i < n; i++)
    deta *= matrix[i][i]; //langkah terakhir dapat determinan atas
    printf("determinan atas : %lf\n\n", deta);
    printf("Masukkan beban di loop yang ingin dicari I nya contoh:\n[Load antara loop]\n[Load khusus I2] \n");
    printf("ada %d baris kebawah sesuai loopnya\n",n);
	for (i = 0; i < n; i++)
	{
            for (j = 0; j < 1; j++)
            {
                 printf("\nEnter a[%d][%d] value :: ",i,j);
                 mb[i][j]=rand()%100 + 100;
                 printf("%lf",mb[i][j]);
  		}printf("\n\n");
    }
    //langkah mengganti Beban akhir ke baris terakhir matrix
    for(i = 0; i < n; i++){
	ma[i][n-1]=mb[i][0];}
	//tes matrix bawah yang telah diganti 
	printf("matrix bawah:\n");
	for(i = 0; i < n; i++){
	 	for (j = 0; j < n; j++)
            {
            
			printf("%lf\t\t ", ma[i][j]);
    }printf("\n\n");
}
	//langkah mencari segitiga atas
	for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(j>i){
                ratio = ma[j][i]/ma[i][i];
                for(k = 0; k < n; k++){
                    ma[j][k] -= ratio * ma[i][k];
                }
            }
        }
    }
    detb = 1; //storage for determinant
    for(i = 0; i < n; i++)
    detb *= ma[i][i];//langkah terakhir mendapat determinan bawah
    printf("determinan bawah : %.2f\n\n", detb);
    P=Power(deta,detb);//mencari P dimana Det atas/bawah = arus nantinya diolah
    printf("daya dioperasi %lf\n",P);
	return P;
    
}
//Simulasi dimana kita bisa input ke matrix;
int sim(int G){
	double P;
	double matrix[10][10], ratio, deta,detb;
	double ma[10][10];
	int i, j, k, n;
    printf("Masukkan jumlah Loop: ");
    scanf("%d", &n);
    double mb[n][1];
	printf("Masukkan matriks, contoh matriks : \n");\
    printf("[Beban dialiri I1\t\t Vloop1]\n[Beban diantara loop1 dan 2\t Vloop2]\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            scanf("%lf", &matrix[i][j]);
        }
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            ma[i][j]=matrix[i][j];
        }
    }
    /* Conversion of matrix to upper triangular */
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(j>i){
                ratio = matrix[j][i]/matrix[i][i];
                for(k = 0; k < n; k++){
                    matrix[j][k] -= ratio * matrix[i][k];
                }
            }
        }
    }
    deta = 1; //storage for determinant
    for(i = 0; i < n; i++)
    deta *= matrix[i][i];
    printf("determinan atas : %lf\n\n", deta);
    printf("Masukkan beban di loop yang ingin dicari I nya contoh:\n[Load antara loop]\n[Load khusus I2] \n");
    printf("%d\n",n);
	for(i = 0; i < n; i++){
    	for(j = 0; j < 1; j++){
            printf("\nEnter a[%d][%d] value :: ",i,j);
            scanf("%lf", &mb[i][j]);
        }
    }
    
    for(i = 0; i < n; i++){
		ma[i][n-1]=mb[i][0];
		}
	for(i = 0; i < n; i++){
	 	for (j = 0; j < n; j++){
            printf("%lf ", ma[i][j]);
    	}
		printf("\n\n");
	}
	
	for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(j>i){
                ratio = ma[j][i]/ma[i][i];
                for(k = 0; k < n; k++){
                    ma[j][k] -= ratio * ma[i][k];
                }
            }
        }
    }
    detb = 1; //storage for determinant
    for(i = 0; i < n; i++){
    	detb *= ma[i][i];
    	printf("determinan bawah : %lf\n\n", detb);
    	P=Power(deta,detb);
    	Oprec(P,G);
    }
}
//menu
int menu(int no,int G)
	{
		switch(no)
		{case 1 :
			cs(G);
			break;
		 case 2 :
			manual(G);
		 	break;
		case 3 :
		 	Notif();
		 	break;
		case 4 :
			sim(G);
			break;
		default : 
		    printf("salah input bro pilih 1->4");
	}
}



int main () {
    int choice;
    double P;
    int id;
	int state[id];
	int G;
	printf("masukkan jumlah generator\n");
	G=salah("jumlah Generator?");
	printf("baik ada %d generator yang anda miliki\n",G);
	while(1){
	printf("pilih menu dimana \n1.status, \n2.Operasi manual, \n3.Notifikasi Konsumen, \n4.Simulasi\n");

		clock_t start_time = clock();
		
		while(clock()-start_time<5000){
			//state[id] = getStatus(id);
			if(kbhit()){
			choice=ssalah("Pilihan x>");
   			menu(choice,G);
			break;
   }
			else if(!kbhit()){
				if(clock()-start_time==5000){
					printf("\n");
                    clock_t end_time = clock()/1000;
                    P=Operasi();
					Oprec(P,G);
					cs(G);
					//printf("Waktu berakhir: %ld detik terlewati\n",end_time);
				
				
				}
			}
		} 
	
   //cs(G);
   //anggap simulasi sebagai kenyataan dulu;
	/*
	printf("Daya Maks :%lf",P);
    Oprec();*/
   
}return 0;
}


/*ide bikin sesuai loop misal 3 loop pake aturan kVL ada 3 arus yang artinya matrix 3 x 3 dimana 
[11 12 13]
[21 22 23]
[31 32 33]
11 beban di loop 1 only
12 beban antar loop 1 dan 2
13 V di loop1
21 beban antar loop 2&1
22 beban loop 2 
23 V di loop2
31 beban antarar loop 3&1
32 beban antara loop 3 &2
33 V loop 3
matrix ynya isi loop 3 dimana akan ditukar ke matrix awal dimana 13=beban antar loop 1&3,23=beban atar loop 2&3, 33=Beban loop 3; Polanya terus berlanjut;
*/
//karena paralel Tegangan sama ,I beda, P dikirim tetap sama jadi kita cuma bandingkan mana yang paling maks
//generate load random,untuk status dan operasional, generate random juga untuk kemungkinan gagal sistem
//Bikin loss rate tetap dikali jarak untuk load beban yang tetap dimana beban ini bersifat drop voltage;



