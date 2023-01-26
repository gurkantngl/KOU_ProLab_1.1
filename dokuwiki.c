#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
void namesAndDirectories(char txtNames[][100], int *txtCounter, char txtDirs[][100]);
void findLabel(char labels[][150], int numbers[], int *labelCounter, int *txtCounter, char txtNames[][100], char txtDirs[][100]);
void yetim(char labels[][150], int *labelCounter, char yetimler[][100], int *yetimCounter, int numbers[], char txtNames[][100], int *txtCounter);
void search(char labels[][150], int *labelCounter, char yetimler[][100], int *yetimCounter, int numbers[], char wanted[50], char txtNames[][100], char txtDirs[][100], int *txtCounter);
void outputTxt(char labels[][150], int *labelCounter, int numbers[], char yetimler[][100], int *yetimCounter, char *fileMode);
void guncelle(char labels[][150], char oldName[150], int *labelCounter, int *txtCounter, char txtDirs[][100], char txtNames[][100]);
void isimDegistir(char str[200], char oldName[150], char newName[150]);
void txtDegistir(char txtNames[][100], int *txtCounter);
void istenenEtiket(char txtNames[][100], int *txtCounter, char labels[][150], int *labelCounter, char istenenler[][100], int *istenenSayac);
void dosyaOlustur(int *yetimCounter, int *txtCounter, char yetimler[][100], char txtDirs[][100]);
void karakterKontrol(char wanted[50]);
void menu();
void aramaMenu();
void guncellemeMenu();
int main()
{
    setlocale(LC_ALL, "tr_tr.UTF-8");
    char labels[50][150], yetimler[100][100], oldName[150], wanted[100], txtNames[100][100], istenenler[100][100], txtDirs[100][100];
    int *numbers = (int *)calloc(150, sizeof(int));
    int labelCounter = 0, yetimCounter = 0, txtCounter = 0, istenenSayac = 0;

    namesAndDirectories(txtNames, &txtCounter, txtDirs);
    findLabel(labels, numbers, &labelCounter, &txtCounter, txtNames, txtDirs);
    yetim(labels, &labelCounter, yetimler, &yetimCounter, numbers, txtNames, &txtCounter);
    istenenEtiket(txtNames, &txtCounter, labels, &labelCounter, istenenler, &istenenSayac);
    outputTxt(labels, &labelCounter, numbers, yetimler, &yetimCounter, "w");
    printf("Dokuwikiye hoş geldiniz. Lütfen gerçekleştirmek istediğiniz eylemi seçiniz:\n\n");

    while (1)
    {
        menu();
        int secim;
        printf("İşlem seçin: ");
        scanf("%d", &secim);
        system("cls");
        switch (secim)
        {
        case 1: // Arama menüsü
        aramaMenu:
            aramaMenu();
            printf("İşlem seçiniz: ");
        araMenu:
            scanf("%d", &secim);
            switch (secim)
            {
            case 1:
                system("cls");
                printf("\n\tYetim labels\n");
                for (int i = 0; i < yetimCounter; i++)
                {
                    printf("%s, ", yetimler[i]);
                }
                printf("\n\n\tİstenen labels\n");
                for (int i = 0; i < istenenSayac; i++)
                {
                    printf("%s, ", istenenler[i]);
                }
                printf("\n\nAranacak kelimeyi giriniz:");
                getchar();
                fgets(wanted, 100, stdin);
                wanted[strlen(wanted) - 1] = '\0';
                search(labels, &labelCounter, yetimler, &yetimCounter, numbers, wanted, txtNames, txtDirs, &txtCounter);
                goto aramaMenu;
            case 2: // Ana Menü
                system("cls");
                continue;
            case 3: // Çıkış
                exit(0);
            default:
                printf("Lütfen 1-3 arasi sayı giriniz: ");
                goto araMenu;
            }
        case 2: // güncelleme menüsü
        guncelleme:
            guncellemeMenu();
        guncelMenu:
            printf("İşlem seçin: ");
            scanf("%d", &secim);
            switch (secim)
            {
            case 1:
                printf("||1)Etiket ismi değiştir                 ||\n");
                printf("||2)Txt ismi değiştir                    ||\n");
                printf("İşlem seçin: ");
                scanf("%d", &secim);
                system("cls");
                switch (secim)
                {
                case 1:
                    printf("\n\nEtiketler: ");
                    for (int i = 0; i < labelCounter; i++)
                    {
                        printf("%s, ", labels[i]);
                    }
                    printf("\n\nGüncellemek istediğiniz etiketin ismini giriniz:");
                    getchar();
                    fgets(oldName, 150, stdin);
                    oldName[strlen(oldName) - 1] = '\0';
                    guncelle(labels, oldName, &labelCounter, &txtCounter, txtDirs, txtNames);
                    FILE *output = fopen("./universite/output.txt", "a");
                    if (output == NULL)
                    {
                        printf("\nDosya Açma Hatası!\n");
                        exit(-1);
                    }
                    else
                    {
                        fprintf(output, "%s", "\n\t\tGÜNCEL LİSTE\n");
                        fclose(output);
                    }
                    txtCounter = 0, labelCounter = 0, txtCounter = 0, yetimCounter = 0;
                    for (int i = 0; i < 150; i++)
                    {
                        numbers[i] = 0;
                    }
                    namesAndDirectories(txtNames, &txtCounter, txtDirs);
                    findLabel(labels, numbers, &labelCounter, &txtCounter, txtNames, txtDirs);
                    yetim(labels, &labelCounter, yetimler, &yetimCounter, numbers, txtNames, &txtCounter);
                    outputTxt(labels, &labelCounter, numbers, yetimler, &yetimCounter, "a");
                    printf("Etiket ismi başarıyla değiştirildi!\n\n");
                    goto guncelleme;
                case 2:
                    txtDegistir(txtNames, &txtCounter);
                    for (int i = 0; i < txtCounter; i++)
                    {
                        numbers[i] = 0;
                    }
                    txtCounter = 0, labelCounter = 0, txtCounter = 0, yetimCounter = 0;
                    namesAndDirectories(txtNames, &txtCounter, txtDirs);
                    findLabel(labels, numbers, &labelCounter, &txtCounter, txtNames, txtDirs);
                    yetim(labels, &labelCounter, yetimler, &yetimCounter, numbers, txtNames, &txtCounter);
                    FILE *output1 = fopen("./universite/output.txt", "a");
                    if (output1 == NULL)
                    {
                        printf("\nDosya açma hatası\n");
                        exit(-1);
                    }
                    else
                    {
                        fprintf(output1, "%s", "\n\t\tGÜNCEL LİSTE\n");
                        fclose(output1);
                    }
                    outputTxt(labels, &labelCounter, numbers, yetimler, &yetimCounter, "a");
                    goto guncelleme;
                }
            case 2:
                system("cls");
                dosyaOlustur(&yetimCounter, &txtCounter, yetimler, txtDirs);
                FILE *output = fopen("./universite/output.txt", "a");
                if (output == NULL)
                {
                    printf("\nDosya açma hatası!\n");
                    exit(-1);
                }
                else
                {
                    fprintf(output, "%s", "\n\t\tGÜNCEL LİSTE\n");
                    fclose(output);
                }
                txtCounter = 0, labelCounter = 0, txtCounter = 0, yetimCounter = 0;
                free(numbers);
                int *numbers = (int *)calloc(150, sizeof(int));
                namesAndDirectories(txtNames, &txtCounter, txtDirs);
                findLabel(labels, numbers, &labelCounter, &txtCounter, txtNames, txtDirs);
                yetim(labels, &labelCounter, yetimler, &yetimCounter, numbers, txtNames, &txtCounter);
                outputTxt(labels, &labelCounter, numbers, yetimler, &yetimCounter, "a");
                goto guncelleme;
                break;
            case 3: // Ana menü
                system("cls");
                continue;
            case 4:
                exit(0);
            default:
                printf("Lütfen 1-4 arası sayı giriniz:\n");
                goto guncelMenu;
            }
            break;
        case 3: // output.txt
            system(".\\universite\\output.txt");
            system("cls");
            break;
        case 4: // çıkış
            exit(0);
        default:
            system("cls");
            printf("\tLütfen 1-4 arası sayi giriniz!\n");
            continue;
        }
    }
    return 0;
}
void namesAndDirectories(char txtNames[][100], int *txtCounter, char txtDirs[][100])
{
    system("cd universite & dir */ad/b/d/o:n>folderNames.txt");
    FILE *folderNames = fopen(".\\universite\\folderNames.txt", "r");
    if (folderNames == NULL)
    {
        printf("\nDosya açma hatası\n");
        exit(-1);
    }
    else
    {
        while (!feof(folderNames))
        {
            char folder[100];
            if (fgets(folder, 100, folderNames))
            {
                folder[strlen(folder) - 1] = '\0';
                char dir[200];
                sprintf(dir, "cd universite\\%s & dir *.TXT/b/o:n>../folders.txt", folder);
                system(dir);
                FILE *folders = fopen("./universite/folders.txt", "r");
                if (folders == NULL)
                {
                    printf("\nDosya açma hatası!\n");
                    exit(-1);
                }
                else
                {
                    while (!feof(folders))
                    {
                        if (fgets(txtNames[*txtCounter], 100, folders) && (strlen(txtNames[*txtCounter]) != 0))
                        {
                            txtNames[*txtCounter][strlen(txtNames[*txtCounter]) - 1] = '\0';
                            sprintf(txtDirs[*txtCounter], "%s", folder);
                            (*txtCounter)++;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
            }
        }
    }
}
void findLabel(char labels[][150], int numbers[], int *labelCounter, int *txtCounter, char txtNames[][100], char txtDirs[][100])
{
    for (int i = 0; i < (*txtCounter); i++)
    {
        char uni[100];
        sprintf(uni, "./universite/%s/%s", txtDirs[i], txtNames[i]);
        FILE *dosya = fopen(uni, "r");
        if (dosya == NULL)
        {
            printf("\nDosya açılamadı\n");
            exit(-1);
        }
        else
        {
            while (!feof(dosya))
            {
                char str[200];
                if (fgets(str, 200, dosya))
                {
                    char *ara_ptr = &str[0];
                    while (ara_ptr != NULL)
                    {
                        ara_ptr = strstr(ara_ptr, "[[");
                        if (ara_ptr != NULL)
                            ara_ptr += 2;
                        else
                            break;
                        int i = 0, bosluk = 0, punct = 0;
                        while (ara_ptr[i] != ']')
                        {
                            if (ara_ptr[i] == ' ')
                                bosluk++;
                            if ((ara_ptr[i] >= 33 && ara_ptr[i] <= 47) || (ara_ptr[i] >= 58 && ara_ptr[i] <= 68) || (ara_ptr[i] >= 91 && ara_ptr[i] <= 96 && ara_ptr[i] != 95) || (ara_ptr[i] >= 123 && ara_ptr[i] <= 126))
                            {
                                punct = 1;
                                break;
                            }
                            i++;
                        }
                        char *sonPtr = ara_ptr + i;
                        char s[50];
                        i = -1;
                        if (bosluk < 2 && punct == 0 && sonPtr[0] == ']' && sonPtr[1] == ']')
                        {
                            while ((ara_ptr[++i] != ']'))
                            {
                                s[i] = *(ara_ptr + i);
                            }
                            s[i] = '\0';
                            int var = 0;
                            for (int j = 0; j < (*labelCounter); j++)
                            {
                                if (strcmp(s, labels[j]) == 0)
                                {
                                    *(numbers + j) += 1;
                                    var = 1;
                                    break;
                                }
                            }
                            if (var == 0)
                            {
                                strcpy(labels[*labelCounter], s);
                                numbers[*labelCounter + 1] = 0;
                                *(numbers + (*labelCounter)) += 1;
                                (*labelCounter)++;
                            }
                        }
                    }
                }
            }
            fclose(dosya);
        }
    }
}
void yetim(char labels[][150], int *labelCounter, char yetimler[][100], int *yetimCounter, int numbers[], char txtNames[][100], int *txtCounter)
{
    for (int y = 0; y < (*labelCounter); y++)
    {
        int yetimMi = 0;
        for (int k = 0; k < (*txtCounter); k++)
        {
            char *txtKontrol = (char *)calloc(200, sizeof(char));
            strcpy(txtKontrol, txtNames[k]);
            txtKontrol[strlen(txtKontrol) - 4] = '\0';
            if (strcmp(labels[y], txtKontrol) == 0)
            {
                yetimMi = 1;
                free(txtKontrol);
                break;
            }
            free(txtKontrol);
        }
        if (yetimMi == 0)
        {
            strcpy(yetimler[*yetimCounter], labels[y]);
            (*yetimCounter)++;
        }
    }
}
void search(char labels[][150], int *labelCounter, char yetimler[][100], int *yetimCounter, int numbers[], char wanted[50], char txtNames[][100], char txtDirs[][100], int *txtCounter)
{
    int etiket = 0;
    for (int i = 0; i < (*labelCounter); i++)
    {
        if (strcmp(wanted, labels[i]) == 0)
        {
            etiket = 1;
            break;
        }
    }
    if (etiket == 1)
    {
        sprintf(wanted, "%s%s%s", "[[", wanted, "]]");
        printf("\n\tAradığınız kelime bir etikettir.\n");
    }
    else
    {
        printf("\n\tAradığınız kelime etiket değildir\n");
    }
    int toplam = 0;
    for (int i = 0; i < (*txtCounter); i++)
    {
        int satir = 1;
        char uni[100] = "./universite/";
        sprintf(uni, "./universite/%s/%s", txtDirs[i], txtNames[i]);
        FILE *dosya = fopen(uni, "r");
        if (dosya == NULL)
        {
            printf("\nDosya açma hatası\n");
            exit(-1);
        }
        else
        {
            while (!feof(dosya))
            {
                char str[200];
                if (fgets(str, 200, dosya))
                {
                    char *ara_ptr = strstr(str, wanted);
                    while (ara_ptr != NULL && (*(ara_ptr + strlen(wanted)) == ' '))
                    {
                        toplam++;
                        printf("%-40s%d. satır\n", txtNames[i], satir);
                        ara_ptr = strstr(ara_ptr + 1, wanted);
                    }
                }
                satir++;
            }
        }
        fclose(dosya);
    }
    if (toplam > 0)
    {
        printf("\t\tToplam: %d kez\n\n", toplam);
    }
    else if (toplam == 0)
    {
        printf("\nAradığınız kelime dosyalarda mevcut değildir\n\n");
    }
}
void outputTxt(char labels[][150], int *labelCounter, int numbers[], char yetimler[][100], int *yetimCounter, char *fileMode)
{
    FILE *output = fopen(".\\universite\\output.txt", fileMode);
    if (output == NULL)
    {
        printf("Dosya açma hatası!");
        exit(-1);
    }
    else
    {
        fprintf(output, "%s", "Etiket Listesi\t-\tTekrar Sayısı\n");
        for (int i = 0; i < (*labelCounter); i++)
        {
            fprintf(output, "%-30s%d\n", labels[i], numbers[i]);
        }
        fprintf(output, "%s", "\tYetim labels\n");
        for (int i = 0; i < (*yetimCounter); i++)
        {
            fprintf(output, "%s\n", yetimler[i]);
        }
    }
    fclose(output);
}
void guncelle(char labels[][150], char oldName[150], int *labelCounter, int *txtCounter, char txtDirs[][100], char txtNames[][100])
{
    int kontrol = 0, index;
    char newName[150];
check:
    for (int i = 0; i < (*labelCounter); i++)
    {
        if (strcmp(labels[i], oldName) == 0)
        {
            index = i;
            kontrol = 1;
            break;
        }
    }
    if (kontrol == 1)
    {
        printf("%s adlı etiketin yeni ismini giriniz:", oldName);
        fgets(newName, 150, stdin);
        newName[strlen(newName) - 1] = '\0';
        char yeni[100];
        strcpy(yeni, newName);
        strcpy(labels[index], newName);
        for (int i = 0; i < (*txtCounter); i++)
        {
            char dir[100], tmp[100];
            sprintf(dir, "./universite/%s/%s", txtDirs[i], txtNames[i]);
            FILE *dosya = fopen(dir, "a+");
            char degisen[100];
            sprintf(degisen, "./universite/%s/isimDegis.txt", txtDirs[i]);
            FILE *temp = fopen(degisen, "w");
            if (dosya == NULL || temp == NULL)
            {
                printf("\nDosya açma hatası\n");
                exit(-1);
            }
            else
            {
                while (!feof(dosya))
                {
                    char str[200];
                    if (fgets(str, 200, dosya))
                    {
                        isimDegistir(str, oldName, newName);
                        printf("\nstr: %s\n",str);
                        printf("\ntemp: %s\n",temp);
                        fputs(str, temp);
                    }
                }
                fclose(dosya);
                fclose(temp);
                remove(dir);
                char degis[100];
                sprintf(degis, "cd .\\universite\\%s\\ & ren \"isimDegis.txt\" \"%s\"", txtDirs[i], txtNames[i]);
                system(degis);
            }
            strcpy(tmp, txtNames[i]);
            tmp[strlen(tmp) - 4] = '\0';
            if (strcmp(tmp, oldName) == 0)
            {
                char tmp2[100];
                for (int i = 0; i < strlen(newName); i++)
                {
                    if (yeni[i] == ' ')
                    {
                        yeni[i] = '_';
                    }
                }
                yeni[strlen(yeni)] = '\0';
                sprintf(tmp2, "cd .\\universite\\%s\\ & ren \"%s.txt\" \"%s.txt\"", txtDirs[i], oldName, yeni);
                system(tmp2);
                sprintf(txtNames[i], "%s.txt", yeni);
            }
        }
    }
    else
    {
        printf("\nLütfen geçerli bir etiket ismi girin: ");
        fgets(oldName, 150, stdin);
        oldName[strlen(oldName) - 1] = '\0';
        goto check;
    }
}
void isimDegistir(char str[200], char oldName[150], char newName[150])
{
    char *search, tempTxt[150];
    strcpy(tempTxt, str);
    char *ptrSon = &str[0];
    while (strcmp(oldName, newName) == 0)
    {
        printf("\nTekrar girin: ");
        fgets(newName, 150, stdin);
        newName[strlen(newName) - 1] = '\0';
    }
    char *etiket = (char *)malloc(strlen(oldName) + 5);
    sprintf(etiket, "%s%s%s", "[[", oldName, "]]");
    while ((search = strstr(str, etiket)) != NULL)
    {
        int indexBas = search - str;
        int indexSon = indexBas + strlen(etiket);
        str[indexBas] = '\0';
        sprintf(str, "%s%s%s%s%s", str, "[[", newName, "]]", tempTxt + indexSon);
        strcpy(tempTxt, str);
    }
}
void txtDegistir(char txtNames[][100], int *txtCounter)
{
    char dosyaismi[150], yeni_Dosya_Ismi[150];
    printf("\nTxt dosyaları: ");
    for (int i = 0; i < (*txtCounter); i++)
    {
        printf("%s, ", txtNames[i]);
    }
    printf("\n\nİsmini değiştirmek istediğiniz txt dosyasının adını uzantısı olmadan giriniz: ");
isimKontrol:
    getchar();
    fgets(dosyaismi, 150, stdin);
    dosyaismi[strlen(dosyaismi) - 1] = '\0';
    // printf("%s\n",dosyaismi);
    strcat(dosyaismi, ".txt");
    int varMi = 0;
    for (int i = 0; i < (*txtCounter); i++)
    {
        if (strcmp(txtNames[i], dosyaismi) == 0)
        {
            printf("Dosyanın yeni adını uzantısı olmadan giriniz: ");
            fgets(yeni_Dosya_Ismi, 150, stdin);
            yeni_Dosya_Ismi[strlen(yeni_Dosya_Ismi) - 1] = '\0';
            strcat(yeni_Dosya_Ismi, ".txt");
            varMi = 1;
            break;
        }
    }
    if (varMi == 0)
    {
        printf("Mevcut olmayan dosya adı girdiniz\nTekrar giriniz: ");
        goto isimKontrol;
    }
    FILE *file1 = fopen("./universite/folderNames.txt", "r");
    if (file1 == NULL)
    {
        printf("\nDosya açma hatası\n");
        exit(-1);
    }
    else
    {
        int buldu = 0;
        while (!feof(file1) && buldu == 0)
        {
            char folder[100];
            if (fgets(folder, 100, file1) && strlen(folder) != 0)
            {
                folder[strlen(folder) - 1] = '\0';
                char sys[100], file[100];
                sprintf(sys, "cd universite\\%s & dir *.TXT/b/o:n>../folders.txt", folder);
                system(sys);
                FILE *file2 = fopen("./universite/folders.txt", "r");
                if (file2 == NULL)
                {
                    printf("\nDosya açma hatası!");
                    exit(-1);
                }
                else
                {
                    while (!feof(file2) && buldu == 0)
                    {
                        if (fgets(file, 100, file2) && strlen(file) != 0)
                        {
                            file[strlen(file) - 1] = '\0';
                            if (strcmp(file, dosyaismi) == 0)
                            {
                                char command[100];
                                sprintf(command, "cd .\\universite\\%s & ren \"%s\" \"%s\"", folder, dosyaismi, yeni_Dosya_Ismi);
                                system(command);
                                printf("\nDosya adı değiştirildi!\n\n\n");
                                buldu = 1;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}
void istenenEtiket(char txtNames[][100], int *txtCounter, char labels[][150], int *labelCounter, char istenenler[][100], int *istenenSayac)
{
    char txtKontrol[100];
    for (int i = 0; i < (*txtCounter); i++)
    {
        int istenenMi = 1;
        for (int j = 0; j < (*labelCounter); j++)
        {
            strcpy(txtKontrol, txtNames[i]);
            txtKontrol[strlen(txtKontrol) - 4] = '\0';
            for (int k = 0; k < strlen(txtKontrol); k++)
            {
                if (txtKontrol[k] == '_')
                {
                    txtKontrol[k] = ' ';
                }
            }
            if (strcmp(txtKontrol, labels[j]) == 0)
            {
                istenenMi = 0;
                break;
            }
        }
        if (istenenMi == 1)
        {
            strcpy(istenenler[*istenenSayac], txtKontrol);
            (*istenenSayac)++;
        }
    }
}
void dosyaOlustur(int *yetimCounter, int *txtCounter, char yetimler[][100], char txtDirs[][100])
{
    unsigned char *yeniDosya = (char *)malloc(150 * sizeof(char));
    printf("\n\tYetim labels: ");
    for (int i = 0; i < (*yetimCounter); i++)
    {
        printf("%s, ", yetimler[i]);
    }
    printf("\n\nDosyasını oluşturmak istediğiniz yetim etiketi giriniz:\n");
    getchar();
yetimKontrol:
    fgets(yeniDosya, 150, stdin);
    yeniDosya[strlen(yeniDosya) - 1] = '\0';
    int index = -1;
    for (int i = 0; i < (*yetimCounter); i++)
    {
        if (strcmp(yetimler[i], yeniDosya) == 0)
        {
            index = i;
            int dersKodu;
            char tmp[4];
            FILE *dersKoduDosyasi = fopen("kodSayi.txt", "r");
            if (dersKoduDosyasi == NULL)
            {
                dersKodu = 200;
            }
            else
            {
                fgets(tmp, 4, dersKoduDosyasi);
                dersKodu = atoi(tmp);
                fclose(dersKoduDosyasi);
            }
            char *dosyaDir = (char *)malloc(200 * sizeof(char));
            for (int i = 0; i < (*txtCounter); i++)
            {
                if ((strcmp("dersler", txtDirs[i]) == 0) || strcmp("Dersler", txtDirs[i]) == 0)
                {
                    sprintf(dosyaDir, "./universite/%s/%s.txt", txtDirs[i], yetimler[index]);
                }
            }
            FILE *olustur = fopen(dosyaDir, "w");
            free(dosyaDir);
            if (olustur == NULL)
            {
                printf("\nDosya açma hatası!");
                exit(-1);
            }
            else
            {
                fprintf(olustur, "Dersin Kodu: %s%d\n", "BLM", dersKodu);
                fprintf(olustur, "Dersin adı: [[%s]]\n", yeniDosya);
                fprintf(olustur, "Dersin içeriği:");
                fclose(olustur);
            }
            FILE *sayiTut = fopen("kodSayi.txt", "w");
            if (sayiTut == NULL)
            {
                printf("\nDosya açma hatası!");
                exit(-1);
            }
            else
            {
                dersKodu++;
                sprintf(tmp, "%d", dersKodu);
                fprintf(sayiTut, "%s", tmp);
                fclose(sayiTut);
                printf("\nDosya oluşturuldu!\n\n");
                break;
            }
        }
    }
    if (index == -1)
    {
        printf("\n\nOluşturmak istediğiniz dosya yetim etiket değildir\nTekrar giriniz: ");
        goto yetimKontrol;
    }
}
void karakterKontrol(char wanted[50]){
    
}
void menu()
{
    printf(" --------------- ANA MENÜ ------------------\n");
    printf("||1)Arama menüsü                         ||\n");
    printf("||2)Güncelleme menüsü                    ||\n");
    printf("||3)Output.txt görüntüleme               ||\n");
    printf("||4)Çıkış                                ||\n");
}
void aramaMenu()
{
    printf(" ------------- ARAMA MENÜSÜ -------------\n");
    printf("||1)Arama yap                            ||\n");
    printf("||2)Ana menüye dön                       ||\n");
    printf("||3)Çıkış                                ||\n");
}
void guncellemeMenu()
{
    printf(" ---------- GÜNCELLEME MENÜSÜ ----------\n");
    printf("||1)İsim degiştir                        ||\n");
    printf("||2)Dosya oluştur                        ||\n");
    printf("||3)Ana menüye dön                       ||\n");
    printf("||4)Çıkış                                ||\n");
}