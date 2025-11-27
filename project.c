#include <stdio.h>
#include <string.h>
#include <ctype.h>
typedef struct {
    char productId[10];  // ma hang hoa
    char name[50];       // ten hang hoa
    char unit[10];       // don vi 
    int qty;             // so luong ton kho
    int status;          // trang thai (1: con han su dung , 0: het han su dung)
}Product;

typedef struct {
    char transId[20];    // ma gia dich
    char productId[10];  // ma hang hoa
    char type[5];        // loai giao dich
    char date[15];       // thoi gian giao dich 
} Transaction;
Product products[20] ={
    {"SP001", "Gao ST25", "kg", 150, 1},
    {"SP002", "Duong trang", "kg", 80, 1},
    {"SP003", "Sua tuoi", "hop", 45, 0},
    {"SP004", "Nuoc ngot Coca", "lon", 120, 1},
    {"SP005", "Mi tom Hao Hao", "thung", 60, 1},
    {"SP006", "Kem danh rang", "tui", 25, 1},
    {"SP007", "Bot giat Omo", "tui", 35, 0},
    {"SP008", "Dau an Neptune", "chai", 70, 1},
    {"SP009", "Nuoc mam Chin-su", "chai", 90, 1},
    {"SP010", "Banh mi", "cai", 200, 1},
    {"SP011", "Trung ga", "qua", 180, 1},
    {"SP012", "Ca hop", "hop", 40, 0},
    {"SP013", "Khan giay", "goi", 75, 1},
    {"SP014", "Bia Tiger", "thung", 50, 1},
    {"SP015", "Ca phe G7", "hop", 65, 1},
    {"SP016", "Xa phong Lifebuoy", "cuc", 110, 1},
    {"SP017", "Dau goi Clear", "chai", 30, 0},
    {"SP018", "Banh snack", "tui", 150, 1},
    {"SP019", "Nuoc suoi La Vie", "chai", 200, 1},
    {"SP020", "Thuoc bo Vitamin", "vien", 85, 1}
};
//Product products[100];
int productCount = 20;
Transaction transactions[100];
int transactionCount = 0;

void deleteSpace(char *string, int length) {
    int start = 0;
    int end = length - 1;
    // xoa khoang trang o dau 
    while (string[start] == ' ') {
        start++;
    }

    // xoa khoang trang o cuoi
    while (string[end] == ' ' && end >= start) {
        end--;
    }

    // tao chuoi moi
    int j = 0;
    for (int i = start; i <= end; i++) {
        string[j++] = string[i];
    }
    string[j] = '\0';
}

void getnumber(char *suggest, int min, int max, int *number) {
    int result;
    char buffer[100];
    
    do { 
    printf("%s: ", suggest);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        continue; 
    }
    if (buffer[0] == '\n' || buffer[0] == '\0') {
        printf("Loi! Khong duoc de trong\n");
        continue;
    }
    int hasInvalidChar = 0;
    for(int i = 0; i < strlen(buffer); i++){
        if (buffer[i] == '\n') continue;
        
        if (buffer[i] < '0' || buffer[i] > '9') {
            hasInvalidChar = 1;
            break;
        }
    }
    
    if (hasInvalidChar) {
        printf("Loi! Vui long nhap so nguyen hop le\n");
        continue;
    }
    
    result = sscanf(buffer, "%d", number);  
    if (!result) {
        printf("Loi! Vui long nhap so nguyen hop le\n");
    } else if (*number < min || *number > max) {
        printf("Loi! Vui long nhap so tu %d den %d\n", min, max);
    } else {
        break; 
    }
} while (1);
}

void getstring(char *string, char *suggest, int size) {
    do {
        printf("%s: ", suggest);
        fgets(string, size, stdin);
        string[strcspn(string, "\n")] = '\0';
        deleteSpace(string, strlen(string));
        if (strlen(string) == 0) {
            printf("Loi! Khong duoc de trong\n");
        } else {
            break;
        }
    } while (1);
}

void printMenu() {
    printf("\n\t\t\t++====================MENU====================++\n");
    printf("\t\t\t||%-44s||\n", "1. Them mat hang moi");
    printf("\t\t\t||%-44s||\n", "2. Cap nhat thong tin");
    printf("\t\t\t||%-44s||\n", "3. Quan ly trang thai (khoa/xoa)");
    printf("\t\t\t||%-44s||\n", "4. Tra cuu");
    printf("\t\t\t||%-44s||\n", "5. Danh sach");
    printf("\t\t\t||%-44s||\n", "6. Sap xep danh sach hang hoa");
    printf("\t\t\t||%-44s||\n", "7. Giao dich xuat/nhap");
    printf("\t\t\t||%-44s||\n", "8. Lich su giao dich");
    printf("\t\t\t||%-44s||\n", "9. Thoat");
    printf("\t\t\t++============================================++\n");
}
int isDuplicateId(char *productId) {
    for (int i = 0; i < productCount; i++) {
        if (strcmpi(products[i].productId, productId) == 0) {
            return 1; 
        }
    }
    return 0;
}

void addItem() {
    int size = 0;
    int maxProducts=sizeof(products)/sizeof(int);
    if(productCount<maxProducts){
		    getnumber("Nhap so luong mat hang", 1, 100, &size);
		    for (int i = 0; i < size; i++) {
		        printf("\n>> Nhap thong tin san pham thu %d <<\n", i + 1);
		        do {
		            getstring(products[productCount].productId, "Ma hang hoa", 10);
		            if (isDuplicateId(products[productCount].productId)) {
		                printf("Loi! Ma hang hoa da ton tai. Vui long nhap ma khac.\n");
		            } else {
		                break;
		            }
		        } while (1);
		        do {
		            getstring(products[productCount].name, "Ten hang hoa", 50);
		            if (isDuplicateId(products[productCount].name)) {
		                printf("Loi! Ten hang hoa da ton tai. Vui long nhap ten khac.\n");
		            } else {
		                break;
		            }
		        } while (1);
		        getstring(products[productCount].unit, "Don vi tinh", 10);
		        getnumber("So luong ton kho", 0, 10000, &products[productCount].qty);    
		        products[productCount].status=1;
		        productCount++;
		    }
		    printf("Da them mat hang thanh cong!\n");
		}else{
			printf("danh sach da day, them moi that bai");
		}
	}

int forSure(){
	int number;
	getnumber("ban co chac chan thay doi (1: co | 0: khong)",0,1,&number);
	return number;
}
void displayProducts(){
    if(productCount == 0){
        printf("\n\t\t\t++====================THONG BAO====================++\n");
        printf("\t\t\t||%-48s||\n", " Danh sach hang hoa rong");
        printf("\t\t\t++==================================================++\n");
        return;
    }
    int tmp;
    int itemPerPage;
    int page=1;
    getnumber("Nhap so luong muc moi trang (1-10)", 1, 10, &itemPerPage);
    do{
	    int totalPages = (productCount + itemPerPage - 1) / itemPerPage;
	    int start = (page - 1) * itemPerPage;
	    int end = start + itemPerPage;
	    if(end > productCount){
	        end = productCount;
	    }
	        
	    printf("\n\t\t\t++====================DANH SACH HANG HOA (Trang %d/%d)====================++\n", page, totalPages);
	    printf("\t\t\t|| %-10s | %-20s | %-8s | %-6s | %-15s ||\n", 
	        "MA HANG", "TEN HANG", "DON VI", "SL TON", "TT");
	    printf("\t\t\t++-------------------------------------------------------------------------++\n");    
	        
	    for(int i = start; i < end; i++){
	        printf("\t\t\t|| %-10s | %-20s | %-8s | %-6d | %-15s ||\n",
	                products[i].productId,
	                products[i].name,
	                products[i].unit,
	                products[i].qty,
	                products[i].status == 1 ? "Con su dung" : "Da het han");
	        }
	        printf("\t\t\t++-------------------------------------------------------------------------++\n");
	        printf("\t\t\t|| Hien thi: %d-%d / %d san pham%-19s||\n", 
	               start + 1, end, productCount, "");
	        printf("\t\t\t++=========================================================================++\n");
	        printf("\t\t\t||1: Trang sau | 0: Thoat |2: Trang truoc \n");
	        printf("\t\t\t++=========================================================================++\n");
	        getnumber("lua chon cua ban",0,2,&tmp);
	        if(tmp == 1) {
	        if(page < totalPages){
				page++;
	            }else{
	            	printf("Day la trang cuoi.\n");	
				} 
	        } else if(tmp == 2) {
	            if(page > 1){
	            	page--;
	            }else{
	            	printf("Day la trang dau.\n");	
				} 
	        }else if(tmp == 0) {
	            break;
	        } else {
	            printf("Lua chon khong hop le!\n");
	        }
    }while(1);
}
void updateItem(){
    int flag = 0;
    int foundIndex = -1; 
    char searchProductId[10];
    char newName[50];
    char newUnit[10];
    int newQty;
    if(productCount == 0){
        printf("\n\t\t\t++====================THONG BAO====================++\n");
        printf("\t\t\t||%-48s||\n", " Danh sach hang hoa rong");
        printf("\t\t\t++==================================================++\n");
    }else{
	    getstring(searchProductId, "Nhap ma hang hoa can cap nhat", 10); 
	    for(int i = 0; i < productCount; i++){
	        if(strcmpi(searchProductId, products[i].productId) == 0){ 
	            flag = 1;
	            foundIndex = i;
	            break;
	        }
	    }
	    if(flag){
	       printf("\n\t\t\t++====================DANH SACH HANG HOA================================++\n");
	    	printf("\t\t\t|| %-10s | %-20s | %-8s | %-6s | %-7s ||\n", 
	           "MA HANG", "TEN HANG", "DON VI", "SL TON", "TT");
	    	printf("\t\t\t++-----------------------------------------------------------------------++\n");
	    	printf("\t\t\t|| %-10s | %-20s | %-8s | %-6d | %-6s ||\n",
	               products[foundIndex].productId,
	               products[foundIndex].name,
	               products[foundIndex].unit,
	               products[foundIndex].qty,
	               products[foundIndex].status == 1 ? "Con the su dung" : "Het han su dung");
	    printf("\t\t\t++=======================================================================++\n");
	        do {
	            getstring(newName, "Ten hang hoa moi", 50);
	            if(isDuplicateId(newName)==1){
	                printf("Loi! Ten hang hoa da ton tai. Vui long nhap ten khac.\n");
	            } else {
	                break;
	            }
	        } while (1);
	        
	        getstring(newUnit, "Don vi tinh moi", 10);
	        getnumber("So luong ton kho moi", 0, 10000, &newQty);
	        
	        int result = forSure();
	        if(result == 1){
	            strcpy(products[foundIndex].name, newName);
	            strcpy(products[foundIndex].unit, newUnit);
	            products[foundIndex].qty = newQty; 
	            printf("Cap nhat thanh cong\n"); 
	        } else {
	            printf("Huy cap nhat\n"); 
	        }
	    }else {
	        printf("\n\t\t\t++====================THONG BAO====================++\n");
        	printf("\t\t\t||%-48s||\n", " Ma hang hoa khong ton tai");
        	printf("\t\t\t++==================================================++\n");
	    }
	}
}
void statusItem(){
	char searchId[10];
	int flag=0;
	int choice;
	int foundIndex;
	int newStatus; 
	 if(productCount == 0){
        printf("\n\t\t\t++====================THONG BAO====================++\n");
        printf("\t\t\t||%-48s||\n", " Danh sach hang hoa rong");
        printf("\t\t\t++==================================================++\n");
        return;
    }else{
		getstring(searchId,"nhap ma hang hoa can doi trang thai: ",10);
		for(int i=0;i<productCount;i++){
			if(strcmpi(products[i].productId,searchId)==0){
				flag=1;
				foundIndex=i;
				break;
			}
		}
		if(flag){
			getnumber("ban hay lua chon trang thai (1:Khoa, 0:Xoa): ",0,1,&choice);
			if(choice==1){
				if(products[foundIndex].status){
					if(forSure()){
						products[foundIndex].status=0;
						printf("thay doi trang thai khoa thanh cong\n");
					}else{
						printf("huy thay doi  trang thai thanh cong\n");
					}
				}else{
					if(forSure()){
						products[foundIndex].status=0;
						printf("thay doi trang thai mo thanh cong\n");
					}else{
						printf("huy thay doi  trang thai thanh cong\n");
				}
			}
				
			}else{
				if(forSure()){
					for(int i=foundIndex; i<productCount; i++){
						strcpy(products[i].productId,products[i+1].productId);
						strcpy(products[i].name,products[i+1].name);
						strcpy(products[i].unit,products[i+1].unit);
						products[i].qty=products[i+1].qty;
						products[i].status=products[i+1].status;
					}
					productCount--;
					printf("xoa hang hoa thanh cong\n");
				}else{
					printf("huy xoa hang hoa thanh cong\n");	
				}
			}
					
		}else{
			printf("\n\t\t\t++====================THONG BAO====================++\n");
        	printf("\t\t\t||%-48s||\n", " Ma hang hoa khong ton tai");
        	printf("\t\t\t++==================================================++\n");
		}
	}
}

void searchValue(){
	char searchId[10];
	char searchName[50];
	int flag=0;
	int index=-1;
	int choice;
	getnumber("tim kiem theo (1: ma hang hoa, 0: ten hang hoa)",0,1,&choice);
	if(choice){
		getstring(searchId,"nhap ma hang hoa tim kiem",10);
		for(int i=0; i<productCount; i++){
			if(strcmp(searchId,products[i].productId)==0){
				flag=1;
				index=i;
				break;
			}	
		}
		if(flag){
				 printf("\n\t\t\t++====================DANH SACH HANG HOA DUOC TIM THAY====================++\n");
       			 printf("\t\t\t|| %-10s | %-20s | %-8s | %-6s | %-15s ||\n", 
               			"MA HANG", "TEN HANG", "DON VI", "SL TON", "TT");
       			 printf("\t\t\t++-------------------------------------------------------------------------++\n"); 
            	 printf("\t\t\t|| %-10s | %-20s | %-8s | %-6d | %-15s ||\n",
                   products[index].productId,
                   products[index].name,
                   products[index].unit,
                   products[index].qty,
                   products[index].status == 1 ? "Con su dung" : "Da het han");
        		 printf("\t\t\t++=========================================================================++\n");
			}else{
				printf("\n\t\t\t++====================THONG BAO====================++\n");
        		printf("\t\t\t||%-48s||\n", " Ma hang hoa khong ton tai");
        		printf("\t\t\t++==================================================++\n");
			}
		}else{
			flag=0;
			getstring(searchName,"nhap ten san pham",50);
			printf("\n\t\t\t++====================DANH SACH HANG HOA DUOC TIM THAY====================++\n");
       		printf("\t\t\t|| %-10s | %-20s | %-8s | %-6s | %-15s ||\n", 
               	"MA HANG", "TEN HANG", "DON VI", "SL TON", "TT");
            printf("\t\t\t++-------------------------------------------------------------------------++\n");
			for(int i=0; i<productCount; i++){
				 if(strstr(products[i].name, searchName) != NULL) {
				 	flag=1; 
            	 	printf("\t\t\t|| %-10s | %-20s | %-8s | %-6d | %-15s ||\n",
                   	products[i].productId,
                   	products[i].name,
                   	products[i].unit,
                   	products[i].qty,
                   	products[i].status == 1 ? "Con su dung" : "Da het han");	
				}
				if(!flag){
					printf("\n\t\t\t++====================THONG BAO====================++\n");
        			printf("\t\t\t||%-48s||\n", " ten san pham khong co trong danh sach");
        			printf("\t\t\t++==================================================++\n");
				}
				printf("\t\t\t++=========================================================================++\n");
			}
		}
	}
void sortQuantity(){
	int choice;
	 if(productCount == 0){
        printf("\n\t\t\t++====================THONG BAO====================++\n");
        printf("\t\t\t||%-48s||\n", " Danh sach hang hoa rong");
        printf("\t\t\t++==================================================++\n");
    }else{
    	int j=0;
    	getnumber("sap xep theo (0: Ten , 1: So luong)",0,1,&choice );
		if(choice){
			for(int i = 0; i<productCount-1; i++){
				for(int j=0; j<productCount-1-i;j++){
					if(products[j].qty>products[j+1].qty){
						Product tmp = products[j];
                		products[j] = products[j+1];
                		products[j+1] = tmp;
						
					}
				}
			}
			printf("\n\t\t\t++====================DANH SACH SAU KHI SAP XEP====================++\n");
        	printf("\t\t\t|| %-10s | %-20s | %-8s | %-6s | %-15s ||\n", 
               "MA HANG", "TEN HANG", "DON VI", "SL TON", "TT");
        	printf("\t\t\t++-------------------------------------------------------------------------++\n");    
        
        	for(int i = 0; i < productCount ; i++){
            printf("\t\t\t|| %-10s | %-20s | %-8s | %-6d | %-15s ||\n",
                   products[i].productId,
                   products[i].name,
                   products[i].unit,
                   products[i].qty,
                   products[i].status == 1 ? "Con su dung" : "Da het han");
        	}
        	printf("\t\t\t++=========================================================================++\n");	
		}else{
			for(int i = 0; i<productCount-1; i++){
				for(int j = 0; j<productCount-1-i;j++){
					if(strcmpi(products[j].name,products[j+1].name)>0){
						Product tmp = products[j];
                		products[j] = products[j+1];
                		products[j+1] = tmp;
					}
				}
			}
			printf("\n\t\t\t++====================DANH SACH HANG HOA (Trang %d/%d)====================++\n");
        	printf("\t\t\t|| %-10s | %-20s | %-8s | %-6s | %-15s ||\n", 
               "MA HANG", "TEN HANG", "DON VI", "SL TON", "TT");
        	printf("\t\t\t++-------------------------------------------------------------------------++\n");    
        	for(int i = 0; i < productCount ; i++){
            printf("\t\t\t|| %-10s | %-20s | %-8s | %-6d | %-15s ||\n",
                   products[i].productId,
                   products[i].name,
                   products[i].unit,
                   products[i].qty,
                   products[i].status == 1 ? "Con su dung" : "Da het han");
        	}
        	printf("\t\t\t++=========================================================================++\n");
		}	
	}
	
}
int isValidDate(char *date) {
    int day, month, year;
    char separator1, separator2; 
    if (sscanf(date, "%2d/%2d/%4d", &day, &month, &year) != 3) {
        return 0;
    }
    if (date[2] != '/' || date[5] != '/') {
        return 0;
    }
    if (strlen(date) != 10) {
        return 0;
    }
    if (month < 1 || month > 12) {
        return 0;
    }
    int maxDays = 31;
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDays = 30;
    } else if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            maxDays = 29;
        } else {
            maxDays = 28;
        }
    }
    
    if (day < 1 || day > maxDays) {
        return 0;
    }
    
    return 1;
}

void addTransaction(char *productId, char *type){
    char dateInput[15];
    if (transactionCount < 100) {
        sprintf(transactions[transactionCount].transId, "T%04d", transactionCount + 1);
        strcpy(transactions[transactionCount].productId,productId);
        strcpy(transactions[transactionCount].type, type);
        
        do {
            getstring(dateInput,"Nhap ngay giao dich (dd/mm/yyyy)",15);
            if (isValidDate(dateInput)) {
                strcpy(transactions[transactionCount].date, dateInput);
                break;
            } else {
                printf("LOI: Dinh dang ngay khong hop le! Vui long nhap lai.\n");
                printf("Dinh dang dung: dd/mm/yyyy (vi du: 15/03/2024)\n");
            }
        } while (1);
        transactionCount++;
    }
}

void importExport(){
	int choice;
	char seachId[50];
	int flag=0;
	int index=-1;
	int newQty;
	if(productCount == 0){
        printf("\n\t\t\t++====================THONG BAO====================++\n");
        printf("\t\t\t||%-48s||\n", " Danh sach hang hoa rong");
        printf("\t\t\t++==================================================++\n");
    }else{
    	getstring(seachId,"nhap ma hang hoa", 50);
    	for(int i=0; i<productCount; i++){
    		if(strcmpi(seachId,products[i].productId)==0){
    			flag=1;
    			index=i;
    			break;
    		}
    	}
    	if(flag){
    		printf("\n\t\t\t++====================DANH SACH HANG HOA DUOC TIM THAY====================++\n");
       		printf("\t\t\t|| %-10s | %-20s | %-8s | %-6s | %-15s ||\n", 
               		"MA HANG", "TEN HANG", "DON VI", "SL TON", "TT");
       		printf("\t\t\t++-------------------------------------------------------------------------++\n"); 
            printf("\t\t\t|| %-10s | %-20s | %-8s | %-6d | %-15s ||\n",
                products[index].productId,
                products[index].name,
                products[index].unit,
                products[index].qty,
                products[index].status == 1 ? "Con su dung" : "Da het han");
        	printf("\t\t\t++=========================================================================++\n");
        	getnumber("lua chon (1. xuat hang hoa, 0. nhap hang hoa)",0,1,&choice);
    		if(choice){
    			if(products[index].status){
    				getnumber("nhap so luong xuat hang hoa",0,products[index].qty,&newQty);
    				if(newQty<products[index].qty){
    					products[index].qty-=newQty;
    					addTransaction(products[index].productId,"OUT");
    					printf("xuat hang hoa thanh cong\n");
					}else{
						printf("\n\t\t\t++====================THONG BAO====================++\n");
        				printf("\t\t\t||%-48s||\n", "loi ! xuat hang hoa that bai");
        				printf("\t\t\t++==================================================++\n");
					}
    					
				}else{
					printf("\n\t\t\t++====================THONG BAO====================++\n");
        			printf("\t\t\t||%-48s||\n", " loi! hang da het han su dung");
        			printf("\t\t\t++==================================================++\n");
				}
			}else{
				getnumber("nhap so luong can nhap",1,100,&newQty);
				products[index].qty+=newQty;
				addTransaction(products[index].productId,"IN");
				printf("nhap hang hoa thanh cong\n");
			}
		}else{
			printf("\n\t\t\t++====================THONG BAO====================++\n");
        	printf("\t\t\t||%-48s||\n", " Ma hang hoa khong ton tai");
        	printf("\t\t\t++==================================================++\n");
		}
	}
}

void historyTransaction() {
    char searchId[10];
    int flag = 0;
    
    if (productCount == 0) {
        printf("\n\t\t\t++====================THONG BAO====================++\n");
        printf("\t\t\t||%-48s||\n", " Danh sach hang hoa rong");
        printf("\t\t\t++==================================================++\n");
        return;
    }
    
    getstring(searchId, "Nhap ma hang hoa can xem lich su giao dich", 10);
    for (int i = 0; i < productCount; i++) {
        if (strcmp(searchId, products[i].productId) == 0) {
            flag = 1;
            break;
        }
    }
    if (flag) {
    	int transactionFound = 0;
	    printf("\n\t\t\t++====================LICH SU GIAO DICH===============++\n");
	    printf("\t\t\t|| %-10s | %-10s | %-8s | %-12s ||\n", 
	           "MA GD", "MA HANG", "LOAI", "NGAY GD");
	    printf("\t\t\t++--------------------------------------------------------------++\n");
	    
	    for (int i = 0; i < transactionCount; i++) {
	        if (strcmp(searchId,transactions[i].productId) == 0){
	            transactionFound = 1;
	            printf("\t\t\t|| %-10s | %-10s | %-8s | %-12s ||\n",
	                   transactions[i].transId,
	                   transactions[i].productId,
	                   transactions[i].type,
	                   transactions[i].date);
	        }
	    }
	    
	    if (!transactionFound) {
	        printf("\t\t\t||%-55s||\n", " Hoang hoa chua co giao dich nhap/xuat");
	    }
	    
	    printf("\t\t\t++=====================================================++\n");
    }else{
    	printf("\n\t\t\t++====================THONG BAO====================++\n");
        printf("\t\t\t||%-48s||\n", " Ma hang hoa khong ton tai");
        printf("\t\t\t++==================================================++\n");
	} 
    
}

int main() {
    int choice;
    
    do {
        printMenu();
        getnumber(">>>>>>>>> Lua chon cua ban",1,9,&choice);
        
        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                updateItem();
                break;
            case 3:
                statusItem();
                break;
            case 4:
                searchValue();
                break;
            case 5:
                displayProducts();
                break;
            case 6:
                sortQuantity();
                break;
            case 7:
                importExport();
                break;
            case 8:
                historyTransaction();
                break;
            case 9:
                printf("Thoat chuong trinh. Tam biet!\n");
                break;
            default:
                printf("Lua chon khong hop le! Vui long chon tu 1-9.\n");
        }
    } while (choice != 9);
    
    return 0;
}

