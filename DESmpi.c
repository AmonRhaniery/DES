#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>
#include <mpi.h>

int IP[] = 
{
	  58, 50, 42, 34, 26, 18, 10, 2,
	  60, 52, 44, 36, 28, 20, 12, 4,
	  62, 54, 46, 38, 30, 22, 14, 6,
	  64, 56, 48, 40, 32, 24, 16, 8,
	  57, 49, 41, 33, 25, 17,  9, 1,
	  59, 51, 43, 35, 27, 19, 11, 3,
	  61, 53, 45, 37, 29, 21, 13, 5,
	  63, 55, 47, 39, 31, 23, 15, 7
};

int E[] = 
{
	  32,  1,  2,  3,  4,  5,
	   4,  5,  6,  7,  8,  9,
	   8,  9, 10, 11, 12, 13,
	  12, 13, 14, 15, 16, 17,
	  16, 17, 18, 19, 20, 21,
	  20, 21, 22, 23, 24, 25,
	  24, 25, 26, 27, 28, 29,
	  28, 29, 30, 31, 32,  1
};

int P[] = 
{
	  16,  7, 20, 21,
	  29, 12, 28, 17,
	   1, 15, 23, 26,
	   5, 18, 31, 10,
	   2,  8, 24, 14,
	  32, 27,  3,  9,
	  19, 13, 30,  6,
	  22, 11,  4, 25
};

int FP[] = 
{
	  40, 8, 48, 16, 56, 24, 64, 32,
	  39, 7, 47, 15, 55, 23, 63, 31,
	  38, 6, 46, 14, 54, 22, 62, 30,
	  37, 5, 45, 13, 53, 21, 61, 29,
	  36, 4, 44, 12, 52, 20, 60, 28,
	  35, 3, 43, 11, 51, 19, 59, 27,
	  34, 2, 42, 10, 50, 18, 58, 26,
	  33, 1, 41,  9, 49, 17, 57, 25
};

int S1[4][16] = 
{
		14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
		0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
		4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
		15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
};

int S2[4][16] = 
{
	15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
	 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
	13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
};

int S3[4][16] = 
{
	10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
	 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
};

int S4[4][16] = 
{
	 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
	13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
	 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
};

int S5[4][16] = 
{
	 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
	11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
};

int S6[4][16] = 
{
	12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
	 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
	 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
};

int S7[4][16]= 
{
	 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
	 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
	 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
};

int S8[4][16]= 
{
	13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
	 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
	 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
	 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
};

int PC1[] = 
{
	  57, 49, 41, 33, 25, 17,  9,
	   1, 58, 50, 42, 34, 26, 18,
	  10,  2, 59, 51, 43, 35, 27,
	  19, 11,  3, 60, 52, 44, 36,
	  63, 55, 47, 39, 31, 23, 15,
	   7, 62, 54, 46, 38, 30, 22,
	  14,  6, 61, 53, 45, 37, 29,
	  21, 13,  5, 28, 20, 12,  4
};

int PC2[] = 
{
	  14, 17, 11, 24,  1,  5,
	   3, 28, 15,  6, 21, 10,
	  23, 19, 12,  4, 26,  8,
	  16,  7, 27, 20, 13,  2,
	  41, 52, 31, 37, 47, 55,
	  30, 40, 51, 45, 33, 48,
	  44, 49, 39, 56, 34, 53,
	  46, 42, 50, 36, 29, 32
};

int SHIFTS[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

FILE* out;
FILE* registro;
int msgCorreta;
int msgCorretaAux[1];
int LEFT[17][32], RIGHT[17][32];
int IPtext[64];
int EXPtext[48];
int XORtext[48];
int X[8][6];
int X2[32];
int R[32];
int key56bit[56];
int key48bit[17][48];
int CIPHER[64];
int ENCRYPTED[64];
int BITS[] = {16,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56};
int vez;
int CHAVE[64];
int CHAVES56[56];
int CIFRA[64];
int DECODIFICADO[64];
int npes, myrank;
int MSGBITS[64];

void expansion_function(int pos, int text)
{
    int i;
	for (i = 0; i < 48; i++)
		if (E[i] == pos + 1)
			EXPtext[i] = text;
}

int initialPermutation(int pos, int text)
{
	int i;
	for (i = 0; i < 64; i++)
		if (IP[i] == pos + 1)
			break;
	IPtext[i] = text;
}

int F1(int i)
{
	int r, c, b[6];
    int j;
	for (j = 0; j < 6; j++)
		b[j] = X[i][j];

	r = b[0] * 2 + b[5];
	c = 8 * b[1] + 4 * b[2] + 2 * b[3] + b[4];
	if (i == 0)
		return S1[r][c];
	else if (i == 1)
		return S2[r][c];
	else if (i == 2)
		return S3[r][c];
	else if (i == 3)
		return S4[r][c];
	else if (i == 4)
		return S5[r][c];
	else if (i == 5)
		return S6[r][c];
	else if (i == 6)
		return S7[r][c];
	else if (i == 7)
		return S8[r][c];
}

int XOR(int a, int b)
{
	return (a ^ b);
}

int ToBits(int value)
{
	int k, j, m;
	static int i;
	if (i % 32 == 0)
		i = 0;
	for (j = 3; j >= 0; j--) 
	{
		m = 1 << j;
		k = value & m;
		if (k == 0)
			X2[3 - j + i] = '0' - 48;
		else
			X2[3 - j + i] = '1' - 48;
	}
	i = i + 4;
}

int SBox(int XORtext[])
{
	int k = 0;
    int i,j;
	for (i = 0; i < 8; i++)
		for (j = 0; j < 6; j++)
			X[i][j] = XORtext[k++];

	int value;
	for (i = 0; i < 8; i++) 
	{
		value = F1(i);
		ToBits(value);
	}
}

int PBox(int pos, int text)
{
	int i;
	for (i = 0; i < 32; i++)
		if (P[i] == pos + 1)
			break;
	R[i] = text;
}

void cipher(int Round, int mode)
{
    int i;
	for (i = 0; i < 32; i++)
		expansion_function(i, RIGHT[Round - 1][i]);

	for (i = 0; i < 48; i++) 
	{
		if (mode == 0)
			XORtext[i] = XOR(EXPtext[i], key48bit[Round][i]);
		else
			XORtext[i] = XOR(EXPtext[i], key48bit[17 - Round][i]);
	}

	SBox(XORtext);

	for (i = 0; i < 32; i++)
		PBox(i, X2[i]);
	for (i = 0; i < 32; i++)
		RIGHT[Round][i] = XOR(LEFT[Round - 1][i], R[i]);
}

void finalPermutation(int pos, int text)
{
	int i;
	for (i = 0; i < 64; i++)
		if (FP[i] == pos + 1)
			break;
	ENCRYPTED[i] = text;
}

void convertToBinary(int n)
{
	int k, m;
    int i;
	for (i = 7; i >= 0; i--) 
	{
		m = 1 << i;
		k = n & m;
		if (k == 0)
			fprintf(out, "0");
		else
			fprintf(out, "1");
	}
}

int convertCharToBit(long int n)
{
	FILE* inp = fopen("input.txt", "rb");
	out = fopen("bits.txt", "wb+");
	char ch;
	int i = n * 8;
	while (i) 
	{
		ch = fgetc(inp);
		if (ch == -1)
			break;
		i--;
		convertToBinary(ch);
	}
	fclose(out);
	fclose(inp);
}

void Encryption(long int plain[])
{
	out = fopen("cipher.txt", "ab+");
    int i;
	for (i = 0; i < 64; i++)
		initialPermutation(i, plain[i]);

	for (i = 0; i < 32; i++)
		LEFT[0][i] = IPtext[i];
	for (i = 32; i < 64; i++)
		RIGHT[0][i - 32] = IPtext[i];

    int k;
	for (k = 1; k < 17; k++) 
	{
		cipher(k, 0);

		for (i = 0; i < 32; i++)
			LEFT[k][i] = RIGHT[k - 1][i];
	}

	for (i = 0; i < 64; i++) 
	{
		if (i < 32)
			CIPHER[i] = RIGHT[16][i];
		else
			CIPHER[i] = LEFT[16][i - 32];
		finalPermutation(i, CIPHER[i]);
	}

	for (i = 0; i < 64; i++)
		fprintf(out, "%d", ENCRYPTED[i]);
	fclose(out);
}

void Decryption(long int plain[])
{
	//out = fopen("decrypted.txt", "ab+");
    int i;
	for (i = 0; i < 64; i++)
		initialPermutation(i, plain[i]);

	for (i = 0; i < 32; i++)
		LEFT[0][i] = IPtext[i];

	for (i = 32; i < 64; i++)
		RIGHT[0][i - 32] = IPtext[i];

    int k;
	for (k = 1; k < 17; k++) {
		cipher(k, 1);

		for (i = 0; i < 32; i++)
			LEFT[k][i] = RIGHT[k - 1][i];
	}
	for (i = 0; i < 64; i++) 
	{
		if (i < 32)
			CIPHER[i] = RIGHT[16][i];
		else
			CIPHER[i] = LEFT[16][i - 32];
		finalPermutation(i, CIPHER[i]);
	}
	for (i = 0; i < 64; i++)
		DECODIFICADO[i]=ENCRYPTED[i];
		//fprintf(out, "%d", ENCRYPTED[i]);

	//fclose(out);
}

void convertToBits(int ch[])
{
	int value = 0;
    int i;
	for (i = 7; i >= 0; i--)
		value += (int)pow(2, i) * ch[7 - i];
	fprintf(out, "%c", value);
}

int bittochar()
{
	out = fopen("result.txt", "ab+");
    int i;
	for (i = 0; i < 64; i = i + 8)
		convertToBits(&ENCRYPTED[i]);
	fclose(out);
}

void key56to48(int round, int pos, int text)
{
	int i;
	for (i = 0; i < 56; i++)
		if (PC2[i] == pos + 1)
			break;
	key48bit[round][i] = text;
}

int key64to56(int pos, int text)
{
	int i;
	for (i = 0; i < 56; i++)
		if (PC1[i] == pos + 1)
			break;
	key56bit[i] = text;
}

void key64to48(unsigned int key[])
{
	int k, backup[17][2];
	int CD[17][56];
	int C[17][28], D[17][28];

    int i;
	for (i = 0; i < 64; i++)
		key64to56(i, key[i]);

	for (i = 0; i < 56; i++)
		if (i < 28)
			C[0][i] = key56bit[i];
		else
			D[0][i - 28] = key56bit[i];

    int x;
	for (x = 1; x < 17; x++) 
	{
		int shift = SHIFTS[x - 1];

		for (i = 0; i < shift; i++)
			backup[x - 1][i] = C[x - 1][i];
		for (i = 0; i < (28 - shift); i++)
			C[x][i] = C[x - 1][i + shift];
		k = 0;
		for (i = 28 - shift; i < 28; i++)
			C[x][i] = backup[x - 1][k++];

		for (i = 0; i < shift; i++)
			backup[x - 1][i] = D[x - 1][i];
		for (i = 0; i < (28 - shift); i++)
			D[x][i] = D[x - 1][i + shift];
		k = 0;
		for (i = 28 - shift; i < 28; i++)
			D[x][i] = backup[x - 1][k++];
	}

    int j;
	for (j = 0; j < 17; j++) 
	{
		for (i = 0; i < 28; i++)
			CD[j][i] = C[j][i];
		for (i = 28; i < 56; i++)
			CD[j][i] = D[j][i - 28];
	}

	for (j = 1; j < 17; j++)
		for (i = 0; i < 56; i++)
			key56to48(j, i, CD[j][i]);
}

void decrypt(long int n)
{
	long int plain[n * 64];
	int i = -1;

    int k;
	for(k=0;k<64;k++){
		plain[k]=CIFRA[k];
	}

	for (i = 0; i < n; i++) 
	{
		Decryption(plain + i * 64);
	}
}

void encrypt(long int n)
{
	FILE* in = fopen("bits.txt", "rb");

	long int plain[n * 64];
	int i = -1;
	char ch;

	while (!feof(in)) 
	{
		ch = getc(in);
		plain[++i] = ch - 48;
	}

	for (i = 0; i < n; i++)
		Encryption(plain + 64 * i);

	fclose(in);
}

void create16Keys()
{

	unsigned int key[64];
	int i = 0, ch;

	for (i=0;i<64;i++){
		key[i]=CHAVE[i];
	}

	key64to48(key);

}

long int findFileSize()
{
	FILE* inp = fopen("input.txt", "rb");
	long int size;
	if (fseek(inp, 0L, SEEK_END))
		perror("fseek() failed");
	else // size will contain no. of chars in input file.
		size = ftell(inp);
	fclose(inp);

	return size;
}

void keyTo64Bits(){
	int i=0;
	int j=0;
	char ch;

//preencher com bit paridade a cada oitavo bit
	int qtdUns=0;
	int count=0;
    int k;
	for(k=0;k<64;k++){
		if (count==7){
			if(qtdUns%2==0){
				CHAVE[k]=1;
			}else{
				CHAVE[k]=0;
			}
			qtdUns=0;
			count=0;		
		} else {
			CHAVE[k]=CHAVES56[j];
			if(CHAVES56[j]==1){
				qtdUns+=1;
			}
			j++;
			count++;
		}
	}
	
	//verificar vetor CHAVE
 /* 	registro = fopen("registro.log","a+");
	fprintf(registro,"CHAVE 64 BITS: ");
	for(int k=0;k<64;k++){
		fprintf(registro,"%d",CHAVE[k]);
	}
	fprintf(registro,"\n");
	fclose(registro); */
}

//k valor inteiro long long
void chavebits(long long int k){
	long long int c;
    long long unsigned int m;
	int j=0;
	for (c = 55; c >= 0; c--)
    {
        m = k >> c;

        if (m & 1)
			CHAVES56[j]=1;
        else
			CHAVES56[j]=0;
	j++;
    }

/* 	registro=fopen("registro.log","a+");
	fprintf(registro,"Testando chave %lld :\n",k); 
	//verificar chave do arquivo key.txt

	for (int k=0;k<56;k++){
		fprintf(registro,"%d",CHAVES56[k]);
	}
	fprintf(registro,"\n");
	fclose(registro); */

	keyTo64Bits(); //chave 64 bits escrita no key.txt

}

void decriptografarDES(){
/* 	registro=fopen("registro.log","a+");
	fprintf(registro,"Executando descriptografia com DES... \n");
	fclose(registro); */

	create16Keys();

	long int n = findFileSize() / 8;

/* 	registro=fopen("registro.log","a+");
	fprintf(registro,"Convertendo mensagem original para bits...\n");
	fclose(registro); */

	convertCharToBit(n);

/* 	registro=fopen("registro.log","a+");
	fprintf(registro,"Descriptando mensagem original...\n");
	fclose(registro); */

	decrypt(n);
}

void verificarMensagem(int k){
	//verificar se chave está correta, o arquivo bits tem que ser igual ao decrypted
/* 	registro=fopen("registro.log","a+");
	fprintf(registro,"Verificando mensagem decifrada gerada em bits com o arquivo decrypted... \n");
	fclose(registro); */
    
/*      if(myrank==60){
        printf("\n CHAVE %d\n",k);
        int z;
       for(z=0;z<64;z++){
            printf("%d",DECODIFICADO[z]);
        }
        printf("\n");
        printf("\n MSG ORIGINAL %d\n",k);
       for(z=0;z<64;z++){
            printf("%d",MSGBITS[z]);
        }
        printf("\n");
    } */

	int i=0;
	while(i<64){
		if(DECODIFICADO[i]==MSGBITS[i]){
			i++;
			if(i==64){
				msgCorreta=1;
                printf("Encontrada com a chave %d.\n",k);
			}
		}else{
			break;
		}
	}
	//fclose(descriptografado);
	
}

void escreverCifra(){
	FILE* in = fopen("cifras.txt","rb");
	//out = fopen("cipher.txt","wb+");

	registro = fopen("registro.log","a+");
	fprintf(registro,"Escrevendo cifra da chave de %d bits:\n",BITS[vez]);
	fclose(registro);

	int contMax=64*(vez+1)+vez; //se 1a vez=0 cont=64, 2a vez=1 cont 128...
	int i=0;
	char ch;
    int z=0;
	while (i<contMax){
		ch = getc(in);
        
		if(i>=contMax-64){
			//escrever cifra no cipher /* 0 a 63 ; 65 a 128 ; 130 a 193 ;*/ 
			//fprintf(out,"%c",ch);
			CIFRA[z]=ch-48;
            //CIFRA[i%64]=ch-48;
            z++;
		}
		i++;
	}
	fclose(in);
	//fclose(out);

	//verificar cifra
	registro = fopen("registro.log","a+");
	//out = fopen("cipher.txt","rb");
	//ch=getc(out);
	for(i=0;i<64;i++){
		fprintf(registro,"%d",CIFRA[i]);
	}
/* 	while(ch!=EOF){
		fprintf(registro,"%c",ch);
		ch = getc(out);
	} */
	fprintf(registro,"\n");
	fclose(registro);
	//fclose(out);

}
void escreverBits() {
    FILE* arqBits=fopen("bits.txt", "rb");
	int b=0;
	while(b<64){
		//char chDes = getc(descriptografado);
		char chBits = getc(arqBits);
        int x=chBits-48;
        MSGBITS[b]=x;
        b++;
	}
	//fclose(descriptografado);
	fclose(arqBits);  
}

int main(int argc, char *argv[])
{
	//MPI

    MPI_Init(&argc, &argv); 
    MPI_Comm_size(MPI_COMM_WORLD, &npes); 
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    if(myrank==0){    //zerar os arquivos
        registro = fopen("registro.log", "wb+");
        fclose(registro);
        out = fopen("chaves.txt", "wb+");
        fclose(out);
    }
	vez=0; //vez=0 é chave de 16 bitz 

	struct timeval start, end;
	gettimeofday(&start, NULL); // Start timer

    escreverBits();
    
  	for(vez=0;vez<1;vez++){ 
		long long unsigned int N=pow(2,BITS[vez]); //limite de chave que pode ser usada, de acordo com a quantidade de bits especificada para a cifra em questão
		long long unsigned int k; //chave da vez
        
		escreverCifra(); //escrever qual é a cifra da vez
        MPI_Barrier(MPI_COMM_WORLD); //esperar todos os arquivos necessários para o processo estarem prontos

        int qtdPorProc=N/npes; //quantidade a ser distribuida a cada proces
        msgCorreta=0;
        msgCorretaAux[0]=0;
		for(k=myrank*qtdPorProc;k<(myrank+1)*qtdPorProc;k++){

			chavebits(k);

			decriptografarDES();

			verificarMensagem(k);

            //escrever chave no arquivo
			if(msgCorreta==1){

				out = fopen("chaves.txt","ab+");
				//convertendo de 64bits para 56
				int cont=0,i=0,z=0;
                int aux[56];
				char ch;
                for(i=0;i<64;i++){
                    if(cont==7){
                        cont=0;
                        continue;
                    }
                    aux[z]=CHAVE[i];
                    z++;
                    cont++;
                }
                //convertendo de 56bits para o bit da vez
                for(i=56-BITS[vez];i<56;i++){
                    fprintf(out,"%d",aux[i]);
                }
				fprintf(out, "\n");

				registro=fopen("registro.log","a+");
				fprintf(registro,"Mensagem de %d bits encontrada pelo processo %d de %d, e escrita no arquivo chaves.txt.\n",BITS[vez],myrank,npes);
				fclose(registro);
            
				fclose(out); 
				//break;
			} 
		
            //Trocar dados de msgCorreta para saber se pode parar
            int z;
            for(z=0;z<npes;z++){
                MPI_Bcast(msgCorretaAux,1,MPI_INT,z,MPI_COMM_WORLD);
                if (msgCorretaAux[0]==1){ 
                    msgCorreta=1;
/*                     registro=fopen("registro.log","a+");
                    fprintf(registro,"Mensagem correta recebida no processo %d.\n",myrank);
                    fclose(registro); */
                }
                if(msgCorreta==1)
                    msgCorretaAux[0]=1;
            }
            

            if(msgCorreta==1)
                break;

          
        }        
        MPI_Barrier(MPI_COMM_WORLD); 
		if (msgCorreta==0){
 					registro=fopen("registro.log","a+");
					fprintf(registro,"Mensagem não encontrada para %d bits no processo %d.\n", BITS[vez],myrank);
					fclose(registro);
		}
        else {
  /*           registro=fopen("registro.log","a+");
            fprintf(registro,"Mensagem correta recebida no processo %d.\n",myrank);
            fclose(registro); */
        }

	}
    
    MPI_Barrier(MPI_COMM_WORLD); //esperar todos os processos terminarem

	gettimeofday(&end, NULL); // End timer
	double time_taken = (end.tv_sec - start.tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec -  
                              start.tv_usec)) * 1e-6;
	registro=fopen("registro.log","a+");
    fprintf(registro,"Tempo que o programa %d levou foi de: %.6lf segundos.\n", myrank,time_taken);
	fclose(registro);

    MPI_Finalize(); //testar mudar isso de lugar, pra ser um tempo só para todos os processos

	return 0;
}
