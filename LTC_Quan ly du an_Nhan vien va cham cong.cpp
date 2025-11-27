#include <stdio.h>
#include <string.h>

#define MAX 100

struct Employee {
	char empId[20];
    char name[50];
    char position[15];
    double baseSalary;
    int workDay;
};

struct TimeSheet {
	char logId[20];
    char empId[20];
    char date[20];
    char status[10];
};

// -------------------------------------MENU------------------------------------------ //

void showMenu() {
    printf("+--------------------MENU--------------------+\n");
    printf("|1. Them nhan vien                           |\n");
    printf("|2. Cap nhat nhan vien                       |\n");
    printf("|3. Xoa nhan vien                            |\n");
    printf("|4. Hien thi danh sach                       |\n");
    printf("|5. Tim kiem theo ten                        |\n");
    printf("|6. Sap xep theo luong                       |\n");
    printf("|7. Cham cong ngay                           |\n");
    printf("|8. Xem bang cong                            |\n");
    printf("|0. Thoat                                    |\n");
    printf("+--------------------------------------------+\n");
    printf("Chon: ");
}

int main() {
    struct Employee emp[MAX];
    struct TimeSheet ts[MAX];

    int n = 0;
    int tsCount = 0;
    int choice;

    do {
        showMenu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addEmployee(emp, &n); break;
            case 2: updateEmployee(emp, n); break;
            case 3: deleteEmployee(emp, &n); break;
            case 4: displayEmployees(emp, n); break;
            case 5: searchByName(emp, n); break;
            case 6: sortBySalary(emp, n); break;
            case 7: timeKeeping(emp, n, ts, &tsCount); break;
            //case 8: viewTimeSheet(ts, tsCount); break;
            case 0: printf("Thoat...\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }

    } while (choice != 0);

    return 0;
}

int findEmployee(struct Employee arr[], int n, char empId[]) {
	for (int i = 0; i < n; i++) {
		if(strcmp(arr[i].empId, empId) == 0) return i;
	}
	return -1;
}

void printEmployee(struct Employee e) {
    printf("%-10s | %-20s | %-10s | %-10.2lf | %d\n",
           e.empId, e.name, e.position, e.baseSalary, e.workDay);
}
// F01 : Them nhan vien moi  //

void addEmployee(struct Employee emp[], int *n) {

    if (*n >= MAX) {
        printf("Danh sach day, them that bai!\n");
        return;
    }

    struct Employee e;

    printf("Nhap ma nhan vien: ");
    fgets(e.empId, sizeof(e.empId), stdin);
    e.empId[strcspn(e.empId, "\n")] = '\0';

    if (strlen(e.empId) == 0) {
        printf("Ma nhan vien khong duoc de trong!\n");
        return;
    }

    if (findEmployee(emp, *n, e.empId) != -1) {
        printf("Ma nhan vien bi trung!\n");
        return;
    }

    printf("Nhap ten nhan vien: ");
    fgets(e.name, sizeof(e.name), stdin);
    e.name[strcspn(e.name, "\n")] = '\0';

    if (strlen(e.name) == 0) {
        printf("Ten nhan vien khong duoc de trong!\n");
        return;
    }

    printf("Nhap chuc vu: ");
    fgets(e.position, sizeof(e.position), stdin);
    e.position[strcspn(e.position, "\n")] = '\0';

    if (strlen(e.position) == 0) {
        printf("Chuc vu khong duoc de trong!\n");
        return;
    }

    printf("Nhap luong co ban: ");
    if (scanf("%lf", &e.baseSalary) != 1 || e.baseSalary <= 0) {
        printf("Luong co ban phai la so duong!\n");
        while(getchar() != '\n'); // Clear buffer
        return;
    }

    printf("Nhap ngay cong: ");
    if (scanf("%d", &e.workDay) != 1 || e.workDay < 0) {
        printf("Ngay cong phai la so >= 0!\n");
        while(getchar() != '\n'); 
        return;
    }

    while(getchar() != '\n');

    emp[*n] = e;
    (*n)++;

    printf("Them nhan vien thanh cong!\n");
}


// F02 : Cap nhat ho so nhan vien //

void updateEmployee(struct Employee emp[], int n) {
    char id[20];
    char newPosition[30];
    double newBaseSalary;

    printf("Nhap ma nhan vien can cap nhat: ");
    fflush(stdin);
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    // Validate: mã NV không duoc rong //
    if (strlen(id) == 0) {
        printf("Ma nhan vien khong duoc de trong!\n");
        return;
    }

    // Tìm nhân viên //
    int pos = findEmployee(emp, n, id);
    if (pos == -1) {
        printf("Khong tim thay nhan vien co ma [%s]!\n", id);
        return;
    }

    printf("\n--- Cap nhat thong tin cho nhan vien: %s - %s ---\n",
           emp[pos].empId, emp[pos].name);

    // Nhap chuc vu moi //
    printf("Cap nhat chuc vu: ");
    fflush(stdin);
    fgets(newPosition, sizeof(newPosition), stdin);
    newPosition[strcspn(newPosition, "\n")] = '\0';

    // Validate: không duoc trong //
    if (strlen(newPosition) == 0) {
        printf("Chuc vu khong duoc de trong!\n");
        return;
    }

    // Nhap luong co ban moi //
    printf("Cap nhat luong co ban: ");
    scanf("%lf", &newBaseSalary);

    // Validate: phai > 0 //
    if (newBaseSalary <= 0) {
        printf("Luong co ban phai la so duong!\n");
        return;
    }

    // Cap nhat vào struct //
    strcpy(emp[pos].position, newPosition);
    emp[pos].baseSalary = newBaseSalary;

    printf("Cap nhat ho so nhan vien thanh cong!\n");
}


// F03 : Sa thai / nghi viec ( xoa nhan vien ) //

void deleteEmployee(struct Employee emp[], int *n) {
	char id[20];
	printf("Nhap ma nhan vien can xoa: ");
	fflush(stdin);
	fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int pos = findEmployee(emp, *n, id);
    if (pos == -1) {
        printf("Khong tim thay nhan vien!\n");
        return;
    }

    printf("Xoa thanh cong!\n");
}

// F04 : Hien thi danh sach nhan vien //

void displayEmployees(struct Employee emp[], int n) {
    if (n == 0) {
        printf("Danh sach rong!\n");
        return;
    }

    printf("\n%-10s | %-20s | %-10s | %-10s | %s\n",
           "ID", "Name", "Position", "Salary", "WorkDay");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printEmployee(emp[i]);
    }
}

// F05 Tim kiem theo ten //
void searchByName(struct Employee emp[], int n) {
    char key[50];
    printf("Nhap ten can tim: ");
    fflush(stdin);
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    if (strlen(key) == 0) {
        printf("Ten khong duoc rong!\n");
        return;
    }

    int found = 0;

    for (int i = 0; i < n; i++) {
        if (strstr(emp[i].name, key) != NULL) {
            printEmployee(emp[i]);
            found = 1;
        }
    }

    if (!found)
        printf("Khong tim thay!\n");
}

// F06 Sap xep theo luong //
void sortBySalary(struct Employee emp[], int n) {
    int choice;
    printf("1. Tang dan\n2. Giam dan\nChon: ");
    scanf("%d", &choice);

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((choice == 1 && emp[i].baseSalary > emp[j].baseSalary) ||
                (choice == 2 && emp[i].baseSalary < emp[j].baseSalary)) {
                struct Employee tmp = emp[i];
                emp[i] = emp[j];
                emp[j] = tmp;
            }
        }
    }
    printf("Sap xep thanh cong!\n");
}

// F07 Cham cong theo ngay //
void timeKeeping(struct Employee emp[], int n, struct TimeSheet ts[], int *tsCount) {
	char id[20], date[20];
	
	printf("Nhap ma nhan vien: ");
	fflush(stdin);
	fgets(id, sizeof(id), stdin);
	id[strcspn(id, "\n")] = '\0';
	
	int pos = findEmployee(emp, n, id);
	if (pos == -1) {
		printf("Khong tim thay nhan vien!\n");
		return;
	}
	printf("Nhap ngay cham cong (DD/MM/YYYY): ");
	fflush(stdin);
	fgets(date, sizeof(date), stdin);
	date[strcspn(date, "\n")] = '\0';
	
	 if (strlen(date) == 0) {
        printf("Ngay cham cong khong duoc de trong!\n");
        return;
    }

    if (!isValidDate(date)) {
        printf("Ngay cham cong khong dung dinh dang dd/mm/yyyy!\n");
        return;
    }
}



