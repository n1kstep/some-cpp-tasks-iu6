#include <iostream>
#include "cstring"

struct Element {
    char name[30];
    double weight;
    char cond[30];
};

Element* initElement() {
    Element* el = new Element;
    printf("������� �������� ��������:\n");
    scanf("%s", &el->name);
    printf("������� ��� ��������:\n");
    scanf("%lf", &el->weight);
    printf("������� ������������ ��������:\n");
    scanf("%s", &el->cond);
    return el;
}

void initFile(FILE* f) {
    int n;
    rewind(f);
    Element* el;
    printf("������� ���������� ��������� ��� ����������:\n");
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        printf("������� ���������� �� �������� #%d:\n", i);
        el = initElement();
        fwrite(el, sizeof(Element), 1, f);
    }
    delete el;
}

FILE* openOrCreateFile(const char *name) {
    FILE* f = fopen(name,"rb+");
    if (f == NULL) {
        f = fopen(name,"wb+");
        initFile(f);
        puts("���� ��� ������");
    }
    else {
        puts("���� ��� ������");
    }
    return f;
}

void printFile(FILE* f) {
    if (f == NULL) {
        puts("���� �� ��� ������!");
    }
    else {
        int ind = 0;
        rewind(f);
        Element *el = new Element;
        printf("------+----------------------+-----------+--------------------+\n");
        printf("Index |         Name         |  Weight   |     Conductivity\n", ind, el->name, el->weight, el->cond);
        printf("------+----------------------+-----------+--------------------+\n");
        while (fread(el, sizeof(*el), 1, f) != 0) {
            printf(" %-4d | %-20s | %-5.3lf\t | %-20s\n", ind, el->name, el->weight, el->cond);
            printf("------+----------------------+-----------+--------------------+\n");
            ind++;
        }
        delete el;
    }
}

void addElement(FILE* f) {
    Element *el = initElement();
    fwrite(el, sizeof(Element), 1, f);
    delete el;
}

FILE* delElement(FILE* f, int ind) {
    if (f == NULL) {
        puts("���� �� ��� ������!");
    }
    else {
        int n = 0;
        FILE *g;
        rewind(f);
        Element *el = new Element;
        g = fopen("tmp_data", "wb");
        while (fread(el, sizeof(*el), 1, f) != 0) {
            if (n != ind) {
                fwrite(el, sizeof(Element), 1, g);
            }
            n++;
        }
        fclose(f);
        fclose(g);
        remove("task_data");
        rename("tmp_data", "task_data");
        f = fopen("task_data", "ab+");
    }
    return f;
}

double printMax(FILE* f, double initVal, int ind) {
    double maxVal = -1000;
    if (f == NULL) {
        puts("���� �� ��� ������!");
    }
    else {
        rewind(f);
        Element *el = new Element;
        Element maxEl;
        while (fread(el, sizeof(*el), 1, f) != 0) {
            if (el->weight >= maxVal && el->weight < initVal) {
                maxEl = *el;
                maxVal = el->weight;
            }
        }
        printf(" %-4d | %-20s | %-5.3lf\t | %-20s\n", ind, maxEl.name, maxEl.weight, maxEl.cond);
        printf("---------------------------------------------------------------\n");
        delete el;
    }
    return maxVal;
}

double printMin(FILE* f, double initVal, int ind) {
    double minVal = 1000;
    if (f == NULL) {
        puts("���� �� ��� ������!");
    }
    else {
        rewind(f);
        Element *el = new Element;
        Element minEl;
        while (fread(el, sizeof(*el), 1, f) != 0) {
            if (el->weight <= minVal && el->weight > initVal) {
                minEl = *el;
                minVal = el->weight;
            }
        }
        printf(" %-4d | %-20s | %-5.3lf\t | %-20s\n", ind, minEl.name, minEl.weight, minEl.cond);
        printf("---------------------------------------------------------------\n");
        delete el;
    }
    return minVal;
}

void sortByWeight(FILE* f, bool asc = true) {
    if (f == NULL) {
        puts("���� �� ��� ������!");
    }
    else {
        int ind = 0, cnt = 0;
        rewind(f);
        double initVal;
        Element *el = new Element;
        printf("---------------------------------------------------------------\n");
        printf("Index |         Name         |  Weight   |     Conductivity\n", ind, el->name, el->weight, el->cond);
        printf("---------------------------------------------------------------\n");
        if (asc) {
            initVal = -1000;
        } else {
            initVal = 1000;
        }
        while (fread(el, sizeof(*el), 1, f) != 0) {
            cnt++;
        }
        for (int i = 0; i < cnt; ++i) {
            if (asc) {
                initVal = printMin(f, initVal, ind);
            } else {
                initVal = printMax(f, initVal, ind);
            }
            ind++;
        }
        delete el;
    }
}

void searchByCond(FILE* f, char* cond) {
    if (f == NULL) {
        puts("���� �� ��� ������!");
    }
    else {
        int ind = 0;
        rewind(f);
        Element *el = new Element;
        printf("---------------------------------------------------------------\n");
        printf("Index |         Name         |  Weight   |     Conductivity\n", ind, el->name, el->weight, el->cond);
        printf("---------------------------------------------------------------\n");
        while (fread(el, sizeof(*el), 1, f) != 0) {
            if (strcmp(el->cond, cond) == 0) {
                printf(" %-4d | %-20s | %-5.3lf\t | %-20s\n", ind, el->name, el->weight, el->cond);
                printf("---------------------------------------------------------------\n");
                ind++;
            }
        }
        delete el;
    }
}

void searchByWeight(FILE* f, char* cond, double lim, bool more = true) {
    if (f == NULL) {
        puts("���� �� ��� ������!");
    }
    else {
        int ind = 0;
        rewind(f);
        Element *el = new Element;
        printf("---------------------------------------------------------------\n");
        printf("Index |         Name         |  Weight   |     Conductivity\n", ind, el->name, el->weight, el->cond);
        printf("---------------------------------------------------------------\n");
        while (fread(el, sizeof(*el), 1, f) != 0) {
            if (strcmp(el->cond, cond) == 0) {
                if ((more) && (el->weight >= lim)) {
                    printf(" %-4d | %-20s | %-5.3lf\t | %-20s\n", ind, el->name, el->weight, el->cond);
                    printf("---------------------------------------------------------------\n");
                    ind++;
                } else if ((!more) && (el->weight <= lim)) {
                    printf(" %-4d | %-20s | %-5.3lf\t | %-20s\n", ind, el->name, el->weight, el->cond);
                    printf("---------------------------------------------------------------\n");
                    ind++;
                }
            } else if ((!more) && (el->weight <= lim) && (strcmp(el->cond, cond) == 0)) {
                printf(" %-4d | %-20s | %-5.3lf\t | %-20s\n", ind, el->name, el->weight, el->cond);
                printf("---------------------------------------------------------------\n");
                ind++;
            }
        }
        delete el;
    }
}

int main() {
    setlocale(0, "russian");
    int n;
    bool flag = true;
    FILE* f = NULL;

    while (flag) {
        printf("1 - ������� ��� ���������������� ����\n"
               "2 - ������ ���� ������\n"
               "3 - �������� �������\n"
               "4 - ������� �������\n"
               "5 - ����� �� ����������\n"
               "6 - ����� �� ���������\n");
        scanf("%d", &n);
        switch (n) {
            case 1: {
                f = openOrCreateFile("task_data");
                break;
            }
            case 2: {
                printFile(f);
                break;
            }
            case 3: {
                addElement(f);
                break;
            }
            case 4: {
                puts("������� ������ �������� ��� ��������:");
                int ind;
                scanf("%d", &ind);
                f = delElement(f, ind);
                puts("������� ��� ������");
                break;
            }
            case 5: {
                int m;
                printf("1 - ����� �� ������������\n"
                       "2 - ����� �� ������������ � ����\n"
                       "3 - ���������� �� ����\n"
                       "4 - ����� �� �������\n");
                scanf("%d", &m);
                switch (m) {
                    case 1: {
                        char cond[80];
                        puts("������� ������������ ��� ������:");
                        getchar();
                        gets_s(cond);
                        searchByCond(f, cond);
                        break;
                    }
                    case 2: {
                        char cond[80];
                        double lim;
                        int more;
                        puts("������� ������������ ��� ������:");
                        getchar();
                        gets_s(cond);
                        puts("������� ������ �� ���� ��� ������:");
                        scanf("%lf", &lim);
                        puts("> ������� (1) ��� < ������� (0) ��� ������:");
                        scanf("%d", &more);
                        searchByWeight(f, cond, lim, more);
                        break;
                    }
                    case 3: {
                        int asc;
                        puts("�� ����������� (1) ��� �� �������� (0) ��� ����������:");
                        scanf("%d", &asc);
                        sortByWeight(f, asc);
                        break;
                    }
                    default: {
                        break;
                    }
                }
                break;
            }
            default: {
                flag = false;
                break;
            }
        }
    }
    fclose(f);
}
