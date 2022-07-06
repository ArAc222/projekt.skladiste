#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "dataType.h"
#include "functions.h"

static int brojClanova = 0;

int izbornik(const char* const ime) {

	printf("\t\t----------------------------------------\n\n");
	printf("\t\tOdaberite opciju: \n\n");
	printf("\t\t\n\n");

	printf("\t\tOpcija 1: Dodavanje puske!\n");
	printf("\t\tOpcija 2: Ispisi podatke o svim puskama!\n");
	printf("\t\tOpcija 3: Sortiraj po brzini metka!\n");
	printf("\t\tOpcija 4: Pretrazivanje puske po ID-u!\n");
	printf("\t\tOpcija 5: Azuriraj pusku!\n");
	printf("\t\tOpcija 6: Obrisi pusku!\n");

	printf("\t\t----------------------------------------\n\n");

	int odgovor = 0;

	static PUSKA* poljePusaka = NULL;
	static PUSKA* pronadenaPuska = NULL;

	scanf("%d", &odgovor);

	switch (odgovor) {
	case 1:
		dodajPusku(ime);
		break;
	case 2:
		if (poljePusaka != NULL) {
			free(poljePusaka);
			poljePusaka = NULL;
		}

		poljePusaka = (PUSKA*)ucitajPuske(ime);

		ispisiSve(poljePusaka);
		break;
	case 3:
		if (poljePusaka != NULL) {
			free(poljePusaka);
			poljePusaka = NULL;
		}

		poljePusaka = (PUSKA*)ucitajPuske(ime);

		ispisiSortirano(poljePusaka);
		break;
	case 4:
		if (poljePusaka != NULL) {
			free(poljePusaka);
			poljePusaka = NULL;
		}

		poljePusaka = (PUSKA*)ucitajPuske(ime);

		pronadenaPuska = (PUSKA*)pretraziPuske(poljePusaka);

		if (pronadenaPuska != NULL) {
			printf("ID: %d\n", pronadenaPuska->id);
			printf("Ime: %s\n", pronadenaPuska->imePuske);
			printf("Kalibar: %.2f mm\n", pronadenaPuska->kalibar);
			printf("Domet: %d m\n", pronadenaPuska->domet);
			printf("Brzina metka: %d m/s\n", pronadenaPuska->brzinaMetka);
		}
		else {
			printf("Ne postoji clan s tim ID-em.\n");
		}

		break;
	case 5:
		if (poljePusaka != NULL) {
			free(poljePusaka);
			poljePusaka = NULL;
		}

		poljePusaka = (PUSKA*)ucitajPuske(ime);

		azurirajPusku(poljePusaka, ime);
		break;
	case 6:
		if (poljePusaka != NULL) {
			free(poljePusaka);
			poljePusaka = NULL;
		}

		poljePusaka = (PUSKA*)ucitajPuske(ime);

		brisanjePuske(poljePusaka, ime);
		break;
	default:
		free(poljePusaka);
		poljePusaka = NULL;
		odgovor = 0;
	}

	return odgovor;
}