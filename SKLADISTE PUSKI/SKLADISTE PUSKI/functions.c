#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataType.h"
#include "functions.h"

static int brojPusaka = 0;
//funckije za zauzimanje memorije, za pisanje i ucitavanje datoteke
void kreiranjeDatoteke(const char* const ime) {

	FILE* fp = fopen(ime, "rb");

	// ak ne postoji stvaramo novu datoteku sa wb, ako postoji samo zatvaramo
	if (fp == NULL) {
		fp = fopen(ime, "wb");

		fwrite(&brojPusaka, sizeof(int), 1, fp);

		fclose(fp);
	}
	else {
		fclose(fp);
	}

}

void dodajPusku(const char* const ime) {

	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Dodavanje puske u datoteku clanovi.bin");
		exit(EXIT_FAILURE);
	}

	//citamo prvi red datoteke i zapisujemo broj clanova u varijablu brojPusaka
	fread(&brojPusaka, sizeof(int), 1, fp);
	printf("Broj pusaka: %d\n\n", brojPusaka);

	PUSKA temp = { 0 };
	temp.id = brojPusaka + 1;
	getchar();

	printf("Unesite ime puske: ");
	scanf("%24[^\n]", temp.imePuske);
	getchar();

	printf("Unesite kalibar puske: ");
	scanf("%f", &temp.kalibar);

	printf("Unesite domet: ");
	scanf("%d", &temp.domet);

	printf("Unesite brzinu metka: ");
	scanf("%d", &temp.brzinaMetka);

	//pomicemo se na kraj datoteke i zapisujemo novog clana tamo
	fseek(fp, sizeof(PUSKA) * brojPusaka, SEEK_CUR);
	fwrite(&temp, sizeof(PUSKA), 1, fp);
	printf("Nova puska dodana.\n\n");

	// povratak na pocetak datoteke
	rewind(fp);
	brojPusaka++;

	// zapis novog broja clanova
	fwrite(&brojPusaka, sizeof(int), 1, fp);

	fclose(fp);
}

void* ucitajPuske(const char* const ime) {

	FILE* fp = fopen(ime, "rb");

	if (fp == NULL) {
		perror("Ucitavanje korisnika iz clanovi.bin");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(&brojPusaka, sizeof(int), 1, fp);
	printf("Broj clanova: %d\n", brojPusaka);

	PUSKA* poljePusaka = (PUSKA*)calloc(brojPusaka, sizeof(PUSKA));

	if (poljePusaka == NULL) {
		perror("Zauzimanje memorije za studente");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(poljePusaka, sizeof(PUSKA), brojPusaka, fp);

	printf("Svi clanovi uspjesno ucitani.\n\n");

	return poljePusaka;
}

void ispisiSve(const PUSKA* polje) {

	if (brojPusaka == 0) {
		printf("Polje pusaka prazno\n");
		return;
	}

	int i;

	for (i = 0; i < brojPusaka; i++) {
		printf("Puska broj %d\nID: %d\nIme puske: %s\nKalibar: %.2f mm\nDomet: %d m\nBrzina metka %d m/s \n\n",
			i + 1,
			(polje + i)->id,
			(polje + i)->imePuske,
			(polje + i)->kalibar,
			(polje + i)->domet,
			(polje + i)->brzinaMetka);
	}
}

void* pretraziPuske(PUSKA* const polje) {

	if (brojPusaka == 0) {
		printf("Polje pusaka prazno\n");
		return;
	}

	int i;

	int trazeniId;

	printf("Unesite ID puske koju trazite: \n");
	scanf("%d", &trazeniId);

	// ako nademo clana vracamo cijeli element polja s trazenim id-em
	for (i = 0; i < brojPusaka; i++) {

		if (trazeniId == (polje + i)->id) {
			printf("Puska pronadena.\n");

			return (polje + i);
		}
	}

	// vracamo NULL u slucaju da ne nademo nijednu pusku s tim id
	return NULL;
}

void zamjena(PUSKA* const veci, PUSKA* const manji) {
	PUSKA temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}

void* sortirajPoBrziniMetka(const PUSKA* polje) {

	int min = -1;

	for (int i = 0; i < brojPusaka - 1; i++) {

		min = i;
		for (int j = i + 1; j < brojPusaka; j++) {

			if ((polje + j)->brzinaMetka < (polje + min)->brzinaMetka) {
				min = j;
			}
		}

		zamjena((polje + i), (polje + min));
	}

	return polje;
}

void ispisiSortirano(const PUSKA* polje) {

	if (brojPusaka == 0) {
		printf("Polje pusaka prazno\n");
		return;
	}

	int i;

	polje = sortirajPoBrziniMetka(polje);

	for (i = 0; i < brojPusaka; i++) {
		printf("Puska broj %d\nID: %d\nIme puske: %s\nKalibar: %.2f mm\nDomet: %d m\nBrzina metka %d m/s \n\n",
			i + 1,
			(polje + i)->id,
			(polje + i)->imePuske,
			(polje + i)->kalibar,
			(polje + i)->domet,
			(polje + i)->brzinaMetka);
	}
}

void azurirajPusku(PUSKA* polje, const char* const dat) {

	if (brojPusaka == 0) {
		printf("Polje pusaka prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Azuriranje puske");
		exit(EXIT_FAILURE);
	}

	int trazeniId;

	printf("Unesite ID puske koju zelite azurirati: ");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojPusaka) {
			printf("Puska s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojPusaka);

	PUSKA temp = { 0 };

	temp.id = trazeniId;

	getchar();
	printf("Unesite ime puske (trenutno: %s): ", (polje + trazeniId - 1)->imePuske);
	scanf("%24[^\n]", temp.imePuske);
	getchar();

	printf("Unesite kalibar puske (trenutno: %d mm): ", (polje + trazeniId - 1)->kalibar);
	scanf("%d", &temp.kalibar);

	printf("Unesite domet (trenutno: %d m): ", (polje + trazeniId - 1)->domet);
	scanf("%d", &temp.domet);

	printf("Unesite brzinu metka (trenutno: %d m/s): ", (polje + trazeniId - 1)->brzinaMetka);
	scanf("%d", &temp.brzinaMetka);

	fseek(fp, sizeof(int), SEEK_SET);
	fseek(fp, sizeof(PUSKA) * (trazeniId - 1), SEEK_CUR);
	fwrite(&temp, sizeof(PUSKA), 1, fp);

	printf("Puska uspjesno azurirana\n");

	fclose(fp);
}

void brisanjePuske(PUSKA* const polje, const char* const dat) {

	if (brojPusaka == 0) {
		printf("Polje pusaka prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Brisanje pusaka");
		exit(EXIT_FAILURE);
	}

	fseek(fp, sizeof(int), SEEK_CUR);

	int i, trazeniId;

	printf("Unesite ID puske kojeg zelite obrisati: ");

	do {
		scanf("%d", &trazeniId);
		if (trazeniId < 1 || trazeniId > brojPusaka) {
			printf("Puska s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojPusaka);

	PUSKA* pomocnoPolje = (PUSKA*)calloc(brojPusaka - 1, sizeof(PUSKA));

	int counter = 0;

	for (i = 0; i < brojPusaka; i++) {

		if (trazeniId != (polje + i)->id) {
			*(pomocnoPolje + counter) = *(polje + i);

			if ((pomocnoPolje + counter)->id > trazeniId) {
				(pomocnoPolje + counter)->id -= 1;
			}

			fwrite((pomocnoPolje + counter), sizeof(PUSKA), 1, fp);
			counter++;
		}
	}

	free(pomocnoPolje);
	pomocnoPolje = NULL;

	rewind(fp);

	fwrite(&counter, sizeof(int), 1, fp);
	fclose(fp);

	printf("Puska je uspjesno obrisana\n");
}