#include<iostream>
#include <conio.h>
#include<cstring>
#include <fstream>
using namespace std;

struct Date{
    int day;
    int month;
    int year;
};
typedef struct Date DATE;

struct nhanVien{
    int maSoNV;
    string hoDem;
    string ten;
    string gen;
    string birthDay;
    nhanVien *next;   
};
typedef struct nhanVien NhanVien;

struct Nv{
    NhanVien *nvHead;
    NhanVien *nvTail;
};
typedef struct Nv NV;

struct deTai{
    int maSoDT;
    string tenDeTai;
    int namBatDau;
    int namKetThuc;
    long long kinhPhi;   
    deTai *next;
};
typedef struct deTai DeTai;

struct Dt{
    DeTai *dtHead;
    DeTai *dtTail;
} ;
typedef struct Dt DT ;

struct nhanVienDeTai{
    int maSoNV;
    int maSoDT;
    string vaiTro;
    nhanVienDeTai *next;
};
typedef struct nhanVienDeTai NhanVienDeTai;

struct nVDT{
    NhanVienDeTai *nvdtHead;
    NhanVienDeTai *nvdtTail;
};
typedef struct nVDT NVDT;

void KhoiTaoListNV(NV &listNV);
void KhoiTaoListDT(DT &listDT);
void KhoiTaoListNVDT(NVDT &listNVDT);

void menu(NV &listNV,DT &listDT,NVDT &listNVDT);

int main(){
    NV listNV; KhoiTaoListNV(listNV);
    DT listDT; KhoiTaoListDT(listDT);
    NVDT listNVDT; KhoiTaoListNVDT(listNVDT);
    menu(listNV,listDT,listNVDT);
    return 0;
}

//Hàm thêm dữ liệu nhập xuất vào file text
void addToText(string text){
    ofstream file("text.txt", ios::app); // Mở file trong chế độ ghi tiếp
    if (!file) {
        cout<<"Khong the mo file!";
        return;
    }
    file<<text;
    file.close();
}

//Hàm check file đã tồn tại chưa
bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

//Hàm lựa chọn (VD: Nam - Nữ - Khác)
int luaChon(string str1, string str2, string str3, string str4, string str5, string str6) {
    const int numOptions = 6;
    string options[numOptions] = {str1, str2, str3, str4, str5, str6};
    int currentOption = 0;
    char ch;
    while (true) {
        // system("cls");
        cout << "\r";
        int realNumOpt=numOptions;
        for (int i = 0; i < numOptions; ++i) {
            if (options[i].empty()) {
                realNumOpt=realNumOpt-1;
                continue;
            }
            if (i == currentOption) {
                cout << "  > " << options[i] << " <    ";
            } else {
                cout << "    " << options[i] << "      ";
            }
        }
        cout << "\t\t\t";
        ch = _getch();
        switch (ch) {
            case 'a':
            case 'A':
                currentOption = (currentOption - 1 + realNumOpt) % realNumOpt;
                break;
            case 'd':
            case 'D':
                currentOption = (currentOption + 1) % realNumOpt;
                break;
            case 13: // Phím Enter
                cout<<endl;
                for (int i = 0; i < numOptions; ++i) {
                    if (options[i].empty()) {
                        realNumOpt=realNumOpt-1;
                        continue;
                    }
                    if (i == currentOption) {
                        addToText("  > "+options[i]+" <    ");
                    } else {
                        addToText("    "+options[i]+"      ");
                    }
                }
                return currentOption;
            default:
                break;
        }
    }
}

//Hàm sửa string cho đúng họ tên
string checkString(const string& stringInput) {
    string newString;
    int i=0;
    while(stringInput[i]==' '){
        i++;
    }
//xóa khoảng trắng thừa
    if(stringInput[stringInput.length()-1]==' '){
        for(int j=i;j<stringInput.length()-1;j++){
            if (stringInput[j] != ' ' || (stringInput[j] == ' ' && stringInput[j + 1] != ' ')) {
                newString += stringInput[j];
            }
        }
    }else{
        for(int j=i;j<stringInput.length();j++){
            if (stringInput[j] != ' ' || (stringInput[j] == ' ' && stringInput[j - 1] != ' ')) {
                newString += stringInput[j];
            }
        }
    }
//chỉnh sửa lại chữ hoa - chữ thường
    for (int j=0;j<newString.length();j++){
        if(newString[j] >='A' && newString[j]<='Z'){
                newString[j]=newString[j] + ('a'-'A');
            }
    }
    for (int j=0;j<newString.length();j++){
        if(j==0){
            if(newString[j] >='a' && newString[j]<='z'){
                newString[j]=newString[j] + ('A'-'a');
            }
        }
        else if(newString[j]==' '){
            if(newString[j+1] >'a' && newString[j+1]<'z'){
                newString[j+1]=newString[j+1] + ('A'-'a');
            }
        }
    }
    return newString;
}

//In ra khoang cách trắng để vẽ bảng
void spaceLength(string strHeader, int strValueLnegth){
    int x=strHeader.length();
    int y=strValueLnegth;
    string line(x-y,' ');
    cout<<line<<"|";
}

// In ra dòng tiêu đề của bảng
void headerOutput(string strHeader1, string strHeader2, string strHeader3, string strHeader4,string strHeader5,string strHeader6,string strHeader7){
    int x1=strHeader1.length();
    int x2=strHeader2.length();
    int x3=strHeader3.length();
    int x4=strHeader4.length();
    int x5=strHeader5.length();
    int x6=strHeader6.length();
    int x7=strHeader7.length();
    string line(x1+x2+x3+x4+x5+x6,'_');
    cout<<line<<endl;
    cout<<strHeader1<<strHeader2<<strHeader3<<strHeader4<<strHeader5<<strHeader6<<strHeader7<<endl;
    
    for(int i=0;i<x1+x2+x3+x4+x5+x6+x7;i++){
        if(i==0||i==x1||i==x1+x2||i==x1+x2+x3||i==x1+x2+x3+x4||i==x1+x2+x3+x4+x5||i==x1+x2+x3+x4+x5+x6){
            cout<<"|";
            continue;
        }
        cout<<"-";
    }
    cout<<endl;
}

// In ra dòng kết thúc của bảng
void headerOutLine(string strHeader1, string strHeader2, string strHeader3, string strHeader4,string strHeader5,string strHeader6,string strHeader7){
    int x1=strHeader1.length();
    int x2=strHeader2.length();
    int x3=strHeader3.length();
    int x4=strHeader4.length();
    int x5=strHeader5.length();
    int x6=strHeader6.length();
    int x7=strHeader7.length();
    for(int i=0;i<x1+x2+x3+x4+x5+x6+x7;i++){
        if(i==0||i==x1||i==x1+x2||i==x1+x2+x3||i==x1+x2+x3+x4||i==x1+x2+x3+x4+x5||i==x1+x2+x3+x4+x5+x6){
            cout<<"|";
            continue;
        }
        cout<<"_";
    }
    cout<<endl;
}

//In ra khoang cách trắng để vẽ bảng trong file text
void spaceLengthToText(string strHeader, int strValueLnegth){
    int x=strHeader.length();
    int y=strValueLnegth;
    string line(x-y,' ');
    addToText(line+"|");
}

// In ra dòng tiêu đề của bảng để ghi vào file text
void headerOutputToText(string strHeader1, string strHeader2, string strHeader3, string strHeader4,string strHeader5,string strHeader6,string strHeader7){
    int x1=strHeader1.length();
    int x2=strHeader2.length();
    int x3=strHeader3.length();
    int x4=strHeader4.length();
    int x5=strHeader5.length();
    int x6=strHeader6.length();
    int x7=strHeader7.length();
    string line(x1+x2+x3+x4+x5+x6,'_');
    addToText(line+"\n");
    addToText(strHeader1+strHeader2+strHeader3+strHeader4+strHeader5+strHeader6+strHeader7+"\n");
    
    for(int i=0;i<x1+x2+x3+x4+x5+x6+x7;i++){
        if(i==0||i==x1||i==x1+x2||i==x1+x2+x3||i==x1+x2+x3+x4||i==x1+x2+x3+x4+x5||i==x1+x2+x3+x4+x5+x6){
            addToText("|");
            continue;
        }
        addToText("-");
    }
    addToText("\n");
}

// In ra dòng kết thúc của bảng để ghi vào file text
void headerOutLineToText(string strHeader1, string strHeader2, string strHeader3, string strHeader4,string strHeader5,string strHeader6,string strHeader7){
    int x1=strHeader1.length();
    int x2=strHeader2.length();
    int x3=strHeader3.length();
    int x4=strHeader4.length();
    int x5=strHeader5.length();
    int x6=strHeader6.length();
    int x7=strHeader7.length();
    for(int i=0;i<x1+x2+x3+x4+x5+x6+x7;i++){
        if(i==0||i==x1||i==x1+x2||i==x1+x2+x3||i==x1+x2+x3+x4||i==x1+x2+x3+x4+x5||i==x1+x2+x3+x4+x5+x6){
            addToText("|");
            continue;
        }
        addToText("_");
    }
    addToText("\n");
}

//Hàm đếm độ dài của số int
int intLength(int x) {
    int result = 0;
    if (x == 0) {
        return 1;
    }
    while (x != 0) {
        result++;
        x = x / 10; 
    }
    return result;
}

//Hàm kiểm tra năm nhuận
int checkLeapYear(int year){
    if(year%400==0){
        return 1;
    }
    if(year%100==0){
        return 0;
    }
    if(year%4==0){
        return 1;
    }
    return 0;
}

//Hàm kiểm tra ngày tháng
int checkDate(DATE date){
    if(date.year<1000){
        return 0;
    }
    if(date.day<=0 || date.month<=0 || date.year<=0){
            return 0;
        }
        if(date.month>12){
            return 0;
        }
        if(date.month==2){
            if(checkLeapYear(date.year)){
                if(date.day>29){
                    return 0;
                }
            }else{
                if(date.day>28){
                    return 0;
                }
            }
        }
        if(date.month==4 || date.month==6 || date.month==9 || date.month==11){
            if(date.day>30){
                return 0;
            }
        }
        if(date.day>31){
            return 0;
        }
        return 1;
}

//Hàm xuất ra định dạng ngày tháng
string BirthDay(DATE& date) {
    // cin >> date.year >> date.month >> date.day;
    while (!(cin >> date.day) || !(cin >> date.month) || !(cin >> date.year) || date.year>2023 ) {
        addToText(to_string(date.day) + " " + to_string(date.month) + " " + to_string(date.year));
        cin.clear();
        cin.ignore(1000, '\n'); // Xóa bỏ các ký tự dư thừa trong bộ nhớ đệm
        cout<<"Ngay sinh khong hop le, hay nhap lai!"<<endl<<"Ngay sinh (yyyy mm dd): ";
        addToText("\nNgay sinh khong hop le, hay nhap lai!\nNgay sinh (yyyy mm dd): ");
    }
    addToText(to_string(date.day) + " " + to_string(date.month) + " " + to_string(date.year)+"\n");
    if(checkDate(date)==0){
        cout<<"Ngay sinh khong hop le, hay nhap lai!"<<endl<<"Ngay sinh (yyyy mm dd): ";
        addToText("Ngay sinh khong hop le, hay nhap lai!\nNgay sinh (yyyy mm dd): ");
        DATE newDate;
        return BirthDay(newDate);
    }
    return to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
}


//Các hàm liên quan đến ListNV ( danh sách nhân viên)
void KhoiTaoListNV(NV &listNV){
    listNV.nvHead=NULL;
    listNV.nvTail=NULL;
}
NhanVien *KhoiTaoNV(int maSoNV , string hoDem, string ten, string gen, string birthDay){
    NhanVien *newNV = new NhanVien; // cap bo nho cho newNV (nv mới)
    if(newNV==NULL){
		cout<<endl<<"Khong du bo nho de cap phat !";
		return NULL;
	}
    newNV->maSoNV = maSoNV;
    newNV-> hoDem = hoDem;
    newNV-> ten = ten;
    newNV-> gen = gen;
    newNV->birthDay = birthDay;
    newNV->next=NULL;
    return newNV;
}
void XuatListNV(NV listNV){
    if(listNV.nvHead==NULL){
        cout<<"Danh sach nhan vien chua co phan tu nao!"<<endl;
        addToText("\t\tDanh sach nhan vien chua co phan tu nao!\n");
    }else{
        cout<<"Danh sach nhan vien: "<<endl;
        addToText("Danh sach nhan vien: \n");
        headerOutput("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
        headerOutputToText("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
        for(NhanVien *i=listNV.nvHead;i!=NULL;i=i->next){
            cout<<"| "<<i->maSoNV; spaceLength("| Ma so NV ",2+intLength(i->maSoNV));
            addToText("| "+to_string(i->maSoNV)); spaceLengthToText("| Ma so NV ",2+intLength(i->maSoNV));
            cout<<" "<<i->hoDem; spaceLength("|    Ho ten dem    ",2+i->hoDem.length());
            addToText(" "+i->hoDem); spaceLengthToText("|    Ho ten dem    ",2+i->hoDem.length());
            cout<<" "<<i->ten;  spaceLength("|   Ten   ",2+i->ten.length());
            addToText(" "+i->ten);spaceLengthToText("|   Ten   ",2+i->ten.length());
            cout<<" "<<i->gen;spaceLength("|  Gioi tinh  ",2+i->gen.length());
            addToText(" "+ i->gen) ;spaceLengthToText("|  Gioi tinh  ",2+i->gen.length());
            cout<<" "<<i->birthDay;spaceLength("|     Ngay sinh     ",2+i->birthDay.length());
            addToText(" "+i->birthDay) ;spaceLengthToText("|     Ngay sinh     ",2+i->birthDay.length());
            cout<<endl; addToText("\n");
            if(i==listNV.nvTail){
                headerOutLine("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
                headerOutLineToText("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
                addToText("\n");
            }
        }
    }
}
int saveListNvToFile(const NV& listNV, const string& filename) {
    ofstream file(filename, ios::binary);
    if(!file){
        return 1;
    }
    NhanVien* currentNV = listNV.nvHead;
    while (currentNV != nullptr) {
        file.write(reinterpret_cast<const char*>(&currentNV->maSoNV), sizeof(currentNV->maSoNV));

        int hoDemLength = currentNV->hoDem.length();
        file.write(reinterpret_cast<const char*>(&hoDemLength), sizeof(hoDemLength));
        file.write(currentNV->hoDem.c_str(), hoDemLength);

        int tenLength = currentNV->ten.length();
        file.write(reinterpret_cast<const char*>(&tenLength), sizeof(tenLength));
        file.write(currentNV->ten.c_str(), tenLength);

        int genLength = currentNV->gen.length();
        file.write(reinterpret_cast<const char*>(&genLength), sizeof(genLength));
        file.write(currentNV->gen.c_str(), genLength);

        int birthDayLength = currentNV->birthDay.length();
        file.write(reinterpret_cast<const char*>(&birthDayLength), sizeof(birthDayLength));
        file.write(currentNV->birthDay.c_str(), birthDayLength);

        currentNV = currentNV->next;
    }
    file.close();
}
void loadListNvFromFile(NV& listNV, const string& filename) {
    ifstream file(filename, ios::binary);
    while (file.peek() != EOF) {
        NhanVien* newNV = new NhanVien;

        file.read(reinterpret_cast<char*>(&newNV->maSoNV), sizeof(newNV->maSoNV));

        int hoDemLength;
        file.read(reinterpret_cast<char*>(&hoDemLength), sizeof(hoDemLength));
        char* hoDemBuffer = new char[hoDemLength + 1];
        file.read(hoDemBuffer, hoDemLength);
        hoDemBuffer[hoDemLength] = '\0';
        newNV->hoDem = hoDemBuffer;
        delete[] hoDemBuffer;

        int tenLength;
        file.read(reinterpret_cast<char*>(&tenLength), sizeof(tenLength));
        char* tenBuffer = new char[tenLength + 1];
        file.read(tenBuffer, tenLength);
        tenBuffer[tenLength] = '\0';
        newNV->ten = tenBuffer;
        delete[] tenBuffer;

        int genLength;
        file.read(reinterpret_cast<char*>(&genLength), sizeof(genLength));
        char* genBuffer = new char[genLength + 1];
        file.read(genBuffer, genLength);
        genBuffer[genLength] = '\0';
        newNV->gen = genBuffer;
        delete[] genBuffer;

        int birthDayLength;
        file.read(reinterpret_cast<char*>(&birthDayLength), sizeof(birthDayLength));
        char* birthDayBuffer = new char[birthDayLength + 1];
        file.read(birthDayBuffer, birthDayLength);
        birthDayBuffer[birthDayLength] = '\0';
        newNV->birthDay = birthDayBuffer;
        delete[] birthDayBuffer;

        newNV->next = nullptr;

        if (listNV.nvTail == nullptr) {
            listNV.nvHead = newNV;
            listNV.nvTail = newNV;
        } else {
            listNV.nvTail->next = newNV;
            listNV.nvTail = newNV;
        }
    }
    file.close();
}

//Hàm tìm ra vị trí thích hợp để add nhân viên có maSoNV vào
NhanVien *searchToAddNV(const NV& listNV,int maSoNV){
    NhanVien* nvPrev = nullptr;
    NhanVien* nvCurrent = listNV.nvHead;
    if(listNV.nvTail!=nullptr &&listNV.nvTail->maSoNV<maSoNV){
        return listNV.nvTail;
    }
    while (nvCurrent != nullptr && nvCurrent->maSoNV <= maSoNV) {
        nvPrev = nvCurrent;
        nvCurrent = nvCurrent->next;
    }
    return nvPrev;
}

//Hàm thêm nhân viên 1 vào sau nhân viên 2
void addNV(NV &listNV, NhanVien *nv1, NhanVien *nv2){
    //nếu nv 2 không tồn tại thì thêm vào đầu
    if(nv2==nullptr){
        nv1->next=listNV.nvHead;
        listNV.nvHead=nv1;
        if(listNV.nvTail==nullptr){
            listNV.nvTail=nv1;
        }
    }
    //Nếu nhân viên 2 đang là nhân viên cuối thì thêm nv1 vào cuối
    else if(nv2==listNV.nvTail){
        if(listNV.nvTail==NULL){
                listNV.nvHead=listNV.nvTail=nv1; 
            }
            else{
                listNV.nvTail->next=nv1; 
                listNV.nvTail=nv1;
                listNV.nvTail->next=nullptr;
            }
    }else{
        for(NhanVien *i=listNV.nvHead;i!=nullptr;i=i->next){
            if(i->maSoNV==nv2->maSoNV){
                NhanVien *nv2_after=i->next;
                nv2->next=nv1;
                nv1->next=nv2_after;
            }
        }
    }
	
}

//Hàm input mã Số nv tự động
int MaSoNV(NV& listNV) {
    int maSoNV = 0;
    int beforeMaSoNV = 0;
    for (NhanVien* i = listNV.nvHead; i != NULL; i = i->next) {
        if (beforeMaSoNV != i->maSoNV - 1) {
            maSoNV = beforeMaSoNV;
            break;
        }
        beforeMaSoNV = i->maSoNV;
    }
    maSoNV=beforeMaSoNV+1;
    return maSoNV;
}

//Hàm xóa nhan vien co ma so nv= maSoNV
void xoaDuLieuNVDT_NV(NVDT &listNVDT,int maSoNV); //đầu tiên gọi hàm xóa tất cả nhân viên có maSoNV trong list NVDT
void xoaNV(NV &listNV,NVDT &listNVDT, int maSoNV){
    NhanVien* nvPrev = nullptr;
    NhanVien* nv = listNV.nvHead;

    xoaDuLieuNVDT_NV(listNVDT,maSoNV);
    
    while (nv != nullptr) {
        if (nv->maSoNV == maSoNV ) {
            if (nvPrev != nullptr) {
                nvPrev->next = nv->next;
            } else {
                listNV.nvHead = nv->next;
            }
            if(nv==listNV.nvTail){
                listNV.nvTail=nvPrev;
            }
            delete nv;
            return; 
        }

        nvPrev = nv;
        nv = nv->next;
    }

}

//Hàm lấy ra nhân viên có mã số maSoNV
NhanVien *searchNV(NV &listNV,int maSoNV){
    for(NhanVien *i=listNV.nvHead;i!=nullptr;i=i->next){
        if(i->maSoNV==maSoNV){
            return i;
            break;
        }
        if(i->maSoNV>maSoNV){
            return nullptr;
        }
    }
    return nullptr;
}


//Các hàm liên quan đến ListDT (Danh sách đề tài)
void KhoiTaoListDT(DT &listDT){
    listDT.dtHead=NULL;
    listDT.dtTail=NULL;
}
DeTai *KhoiTaoDT(int maSoDT , string tenDeTai, int namBatDau, int namKetThuc, long long kinhPhi ){
    DeTai *newDT = new DeTai; // cap bo nho cho newNV (nv mới)
    if(newDT==NULL){
		cout<<endl<<"Khong du bo nho de cap phat !";
		return NULL;
	}
    newDT->maSoDT = maSoDT;
    newDT-> tenDeTai = tenDeTai;
    newDT-> namBatDau = namBatDau;
    newDT-> namKetThuc = namKetThuc;
    newDT->kinhPhi = kinhPhi;
    newDT->next=NULL;
    return newDT;
}
void XuatListDT(DT listDT){
    if(listDT.dtHead==NULL){
        cout<<"Danh sach de tai chua co phan tu nao!"<<endl;
        addToText("Danh sach de tai chua co phan tu nao!\n");
    }else{
        cout<<"Danh sach de tai: "<<endl;
        addToText("Danh sach de tai: \n");
        headerOutput("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
        headerOutputToText("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
        for(DeTai *i=listDT.dtHead;i!=NULL;i=i->next){
            string kinhPhi=to_string(i->kinhPhi);
            cout<<"| "<<i->maSoDT;spaceLength("| Ma so DT ",2+intLength(i->maSoDT));
                addToText("| "+ to_string(i->maSoDT) );spaceLengthToText("| Ma so DT ",2+intLength(i->maSoDT));
            cout<<" "<<i->tenDeTai;spaceLength("|    Ten de tai    ",2+i->tenDeTai.length());
                addToText(" "+i->tenDeTai);spaceLengthToText("|    Ten de tai    ",2+i->tenDeTai.length());
            cout<<" "<<i->namBatDau;spaceLength("| Nam bat dau ",2+intLength(i->namBatDau));
                addToText(" "+to_string(i->namBatDau));spaceLengthToText("| Nam bat dau ",2+intLength(i->namBatDau));
            cout<<" "<<i->namKetThuc;spaceLength("| Nam ket thuc ",2+intLength(i->namKetThuc));
                addToText(" "+to_string(i->namKetThuc));spaceLengthToText("| Nam ket thuc ",2+intLength(i->namKetThuc));
            cout<<" "<<kinhPhi;spaceLength("|        Kinh phi        ",2+kinhPhi.length());	
                addToText(" "+kinhPhi);spaceLengthToText("|        Kinh phi        ",2+kinhPhi.length());
            cout<<endl;
                addToText("\n");
            if(i==listDT.dtTail){
                headerOutLine("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
                headerOutLineToText("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
                addToText("\n");
            }
        }
    }
}
int saveListDtToFile(const DT& listDT, const string& filename) {
    ofstream file(filename, ios::binary);
    if(!file){
        return 1;
    }
    DeTai* currentDT = listDT.dtHead;
    while (currentDT != nullptr) {
        file.write(reinterpret_cast<const char*>(&currentDT->maSoDT), sizeof(currentDT->maSoDT));

        int tenDeTaiLength = currentDT->tenDeTai.length();
        file.write(reinterpret_cast<const char*>(&tenDeTaiLength), sizeof(tenDeTaiLength));
        file.write(currentDT->tenDeTai.c_str(), tenDeTaiLength);

        file.write(reinterpret_cast<const char*>(&currentDT->namBatDau), sizeof(currentDT->namBatDau));

        file.write(reinterpret_cast<const char*>(&currentDT->namKetThuc), sizeof(currentDT->namKetThuc));

        file.write(reinterpret_cast<const char*>(&currentDT->kinhPhi), sizeof(currentDT->kinhPhi));

        currentDT = currentDT->next;
    }
    file.close();
}
void loadListDtFromFile(DT& listDT, const string& filename) {
    ifstream file(filename, ios::binary);
    while (file.peek() != EOF) {
        DeTai* newDT = new DeTai;

        file.read(reinterpret_cast<char*>(&newDT->maSoDT), sizeof(newDT->maSoDT));

        int tenDeTaiLength;
        file.read(reinterpret_cast<char*>(&tenDeTaiLength), sizeof(tenDeTaiLength));
        char* tenDeTaiBuffer = new char[tenDeTaiLength + 1];
        file.read(tenDeTaiBuffer, tenDeTaiLength);
        tenDeTaiBuffer[tenDeTaiLength] = '\0';
        newDT->tenDeTai = tenDeTaiBuffer;
        delete[] tenDeTaiBuffer;

        file.read(reinterpret_cast<char*>(&newDT->namBatDau), sizeof(newDT->namBatDau));

        file.read(reinterpret_cast<char*>(&newDT->namKetThuc), sizeof(newDT->namKetThuc));

        file.read(reinterpret_cast<char*>(&newDT->kinhPhi), sizeof(newDT->kinhPhi));

        newDT->next = nullptr;

        if (listDT.dtTail == nullptr) {
            listDT.dtHead = newDT;
            listDT.dtTail = newDT;
        } else {
            listDT.dtTail->next = newDT;
            listDT.dtTail = newDT;
        }
    }
    file.close();
}

//Hàm tìm ra vị trí thích hợp để add dề tài có maSoDT vào
DeTai *searchToAddDT(const DT& listDT,int maSoDT){
    DeTai* dtPrev = nullptr;
    DeTai* dtCurrent = listDT.dtHead;
    if(listDT.dtTail!=nullptr &&listDT.dtTail->maSoDT<maSoDT){
        return listDT.dtTail;
    }
    while (dtCurrent != nullptr && dtCurrent->maSoDT <= maSoDT) {
        dtPrev = dtCurrent;
        dtCurrent = dtCurrent->next;
    }
    return dtPrev;
}

//Hàm thêm đề tài 1 vào sau đề tài 2
void addDT(DT &listDT, DeTai *dt1, DeTai *dt2){
    //Nếu đề tài 2 không tồn tại thì thêm dt1 vào đầu
    if(dt2==nullptr){
        dt1->next=listDT.dtHead;
        listDT.dtHead=dt1;
        if(listDT.dtTail==nullptr){
            listDT.dtTail=dt1;
        }
    }
    //Nếu đề tài 2 là đề tài cuối thì thêm dt1 vào cuối
    else if(dt2==listDT.dtTail){
        if(listDT.dtTail==NULL){
                listDT.dtHead=listDT.dtTail=dt1; 
            }
            else{
                listDT.dtTail->next=dt1; 
                listDT.dtTail=dt1;
                listDT.dtTail->next=nullptr;
            }
    }
    //Neu khong thi them de tai 2 vao giua
    else{
        for(DeTai *i=listDT.dtHead;i!=nullptr;i=i->next){
            if(i->maSoDT==dt2->maSoDT){
                DeTai *dt2_after=i->next;
                dt2->next=dt1;
                dt1->next=dt2_after;
            }
        }
    }
	
}

//Ham input ma so DT tu dong
int MaSoDT(DT& listDT){
    int maSoDT = 0;
    int beforMaSoDT = 0;
    for(DeTai *i=listDT.dtHead;i!=NULL;i=i->next){
        if(beforMaSoDT!=i->maSoDT-1){
            maSoDT=beforMaSoDT;
            break;
        }
        beforMaSoDT=i->maSoDT;
    }
    maSoDT=beforMaSoDT+1;
    return maSoDT;
}

//Hàm xóa de tai co ma so dt= maSoDT
void xoaDuLieuNVDT_DT(NVDT &listNVDT,int maSoDT); //đầu tiên gọi hàm xóa tất cả nhân viên có maSoNV trong list NVDT
void xoaDT(DT &listDT,NVDT &listNVDT, int maSoDT){
    DeTai* dtPrev = nullptr;
    DeTai* dt = listDT.dtHead;

    xoaDuLieuNVDT_DT(listNVDT,maSoDT);
    
    while (dt != nullptr) {
        if (dt->maSoDT == maSoDT ) {
            if (dtPrev != nullptr) {
                dtPrev->next = dt->next;
            } else {
                listDT.dtHead = dt->next;
            }
            if(dt==listDT.dtTail){
                listDT.dtTail=dtPrev;
            }
            delete dt;
            return; 
        }

        dtPrev = dt;
        dt = dt->next;
    }

}

//Hàm lấy ra đề tài có mã số maSoDT
DeTai *searchDT(DT &listDT,int maSoDT){
    for(DeTai *i=listDT.dtHead;i!=nullptr;i=i->next){
        if(i->maSoDT==maSoDT){
            return i;
        }
        if(i->maSoDT>maSoDT){
            return nullptr;
        }
    }
    return nullptr;
} 

//tìm vị trí để thích hợp để add deTai có năm bắt đầu theo thứ tự tăng dần
DeTai *searchToAddDT_namBatDau(DT &listDT, int namBatDau){
    DeTai* dtPrev = nullptr;
    DeTai* dtCurrent = listDT.dtHead;
    if(listDT.dtTail!=nullptr &&listDT.dtTail->namBatDau<namBatDau){
        return listDT.dtTail;
    }
    while (dtCurrent != nullptr && dtCurrent->namBatDau <= namBatDau) {
        dtPrev = dtCurrent;
        dtCurrent = dtCurrent->next;
    }
    return dtPrev;
}

//Hàm sap xep danh sach de tai theo tung nam bat dau
void sortDT_namBatDau( DT& listDT){
    DT newListDT;
    newListDT.dtHead=nullptr;
    newListDT.dtTail=nullptr;
    DeTai *index=listDT.dtHead;
    while (index != nullptr) {
        DeTai* k = searchToAddDT_namBatDau(newListDT, index->namBatDau);
        DeTai* tmp = KhoiTaoDT(index->maSoDT,index->tenDeTai,index->namBatDau,index->namKetThuc,index->kinhPhi);
        index = index->next;
        addDT(newListDT, tmp, k);
    }
    listDT= newListDT;
}

DT sortDT_maSoDT( DT& listDT){
    DT newListDT;
    newListDT.dtHead=nullptr;
    newListDT.dtTail=nullptr;
    DeTai *index=listDT.dtHead;
    while (index != nullptr) {
        DeTai* k = searchToAddDT(newListDT, index->maSoDT);
        DeTai* tmp = KhoiTaoDT(index->maSoDT,index->tenDeTai,index->namBatDau,index->namKetThuc,index->kinhPhi);;
        index = index->next;
        addDT(newListDT, tmp, k);
        delete listDT.dtHead;
        listDT.dtHead=index;
    }
    listDT.dtTail=nullptr;
    return newListDT;
}


//Các hàm liên quan đến ListNVDT (Danh sách nhân viên - đề tài)
void KhoiTaoListNVDT(NVDT &listNVDT){
    listNVDT.nvdtHead=NULL;
    listNVDT.nvdtTail=NULL;
}
NhanVienDeTai *KhoiTaoNVDT(int maSoNV, int maSoDT, string vaiTro){
    NhanVienDeTai *newNVDT = new NhanVienDeTai; // cap bo nho cho newNV (nv mới)
    if(newNVDT==NULL){
		cout<<endl<<"Khong du bo nho de cap phat !";
		return NULL;
	}
    newNVDT->maSoNV = maSoNV;
    newNVDT-> maSoDT = maSoDT;
    newNVDT-> vaiTro = vaiTro;
    newNVDT->next=NULL;
    return newNVDT;
}
void XuatListNVDT(NVDT listNVDT){
    if(listNVDT.nvdtHead==NULL){
        cout<<"Danh sach nhan vien - de tai chua co phan tu nao!"<<endl;
        addToText("Danh sach nhan vien - de tai chua co phan tu nao!\n");
    }else{
        cout<<"Danh sach nhan vien - de tai: "<<endl;
        addToText("Danh sach nhan vien - de tai: \n");
        headerOutput("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
        headerOutputToText("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
        for(NhanVienDeTai *i=listNVDT.nvdtHead;i!=NULL;i=i->next){
            cout<<"| "<<i->maSoNV;spaceLength("| Ma so NV ",2+intLength(i->maSoNV));
                addToText("| "+to_string(i->maSoNV));spaceLengthToText("| Ma so NV ",2+intLength(i->maSoNV));
            cout<<" "<<i->maSoDT;spaceLength("| Ma so DT ",2+intLength(i->maSoDT));
                addToText(" "+to_string(i->maSoDT));spaceLengthToText("| Ma so DT ",2+intLength(i->maSoDT));
            cout<<" "<<i->vaiTro;spaceLength("|   Vai tro   ",2+i->vaiTro.length());
                addToText(" "+i->vaiTro);spaceLengthToText("|   Vai tro   ",2+i->vaiTro.length());
            cout<<endl;
                addToText("\n");
            if(i==listNVDT.nvdtTail){
                headerOutLine("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
                headerOutLineToText("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
                addToText("\n");
            }
        }
    }
}
int saveListNvdtToFile(const NVDT& listNVDT, const string& filename) {
    ofstream file(filename, ios::binary);
    if(!file){
        return 1;
    }
    NhanVienDeTai* currentNVDT = listNVDT.nvdtHead;
    while (currentNVDT != nullptr) {
        file.write(reinterpret_cast<const char*>(&currentNVDT->maSoNV), sizeof(currentNVDT->maSoNV));

        file.write(reinterpret_cast<const char*>(&currentNVDT->maSoDT), sizeof(currentNVDT->maSoDT));

        int vaiTroLength = currentNVDT->vaiTro.length();
        file.write(reinterpret_cast<const char*>(&vaiTroLength), sizeof(vaiTroLength));
        file.write(currentNVDT->vaiTro.c_str(), vaiTroLength);

        currentNVDT = currentNVDT->next;
    }
    file.close();
}
void loadListNvdtFromFile(NVDT& listNVDT, const string& filename) {
    ifstream file(filename, ios::binary);
    while (file.peek() != EOF) {
        NhanVienDeTai* newNVDT = new NhanVienDeTai;

        file.read(reinterpret_cast<char*>(&newNVDT->maSoNV), sizeof(newNVDT->maSoNV));

        file.read(reinterpret_cast<char*>(&newNVDT->maSoDT), sizeof(newNVDT->maSoDT));

        int vaiTroLength;
        file.read(reinterpret_cast<char*>(&vaiTroLength), sizeof(vaiTroLength));
        char* vaiTroBuffer = new char[vaiTroLength + 1];
        file.read(vaiTroBuffer, vaiTroLength);
        vaiTroBuffer[vaiTroLength] = '\0';
        newNVDT->vaiTro = vaiTroBuffer;
        delete[] vaiTroBuffer;

        newNVDT->next = nullptr;

        if (listNVDT.nvdtTail == nullptr) {
            listNVDT.nvdtHead = newNVDT;
            listNVDT.nvdtTail = newNVDT;
        } else {
            listNVDT.nvdtTail->next = newNVDT;
            listNVDT.nvdtTail = newNVDT;
        }
    }
    file.close();
}

//Hàm tìm ra vị trí thích hợp để add nhân viên - dề tài có maSoNV maSoDT vào
NhanVienDeTai* searchToAddNhanVienDeTai(NVDT& listNVDT, int maSoNV, int maSoDT) {
    NhanVienDeTai* nvdtPrev = nullptr;
    NhanVienDeTai* nvdtCurrent = listNVDT.nvdtHead;
    if(listNVDT.nvdtTail!=nullptr){
        if(listNVDT.nvdtTail->maSoNV==maSoNV && listNVDT.nvdtTail->maSoDT<maSoDT){
            return listNVDT.nvdtTail;
        }
        if(listNVDT.nvdtTail->maSoNV<maSoNV){
            return listNVDT.nvdtTail;
        }
    }
    while (nvdtCurrent != nullptr && nvdtCurrent->maSoNV <= maSoNV) {
        if (nvdtCurrent->maSoNV == maSoNV && nvdtCurrent->maSoDT > maSoDT) {
            break;
        }
        nvdtPrev = nvdtCurrent;
        nvdtCurrent = nvdtCurrent->next;
    }
    return nvdtPrev;
}

//Thêm nhân (viên - đề tài) 1 vao sau nhân (viên - đề tài) 2
void addNVDT(NVDT &listNVDT, NhanVienDeTai *nvdt1, NhanVienDeTai *nvdt2){
    if(nvdt2==nullptr){
        nvdt1->next=listNVDT.nvdtHead;
        listNVDT.nvdtHead=nvdt1;
        if(listNVDT.nvdtTail==nullptr){
            listNVDT.nvdtTail=nvdt1;
        }
    }
    else if(nvdt2==listNVDT.nvdtTail){
        if(listNVDT.nvdtTail==NULL){
            listNVDT.nvdtHead=listNVDT.nvdtTail=nvdt1; 
        }
        else{
            listNVDT.nvdtTail->next=nvdt1;
            listNVDT.nvdtTail=nvdt1;
            listNVDT.nvdtTail->next=nullptr;
        }
    }else{
        for(NhanVienDeTai *i=listNVDT.nvdtHead;i!=nullptr;i=i->next){
            if(i->maSoDT==nvdt2->maSoDT && i->maSoNV==nvdt2->maSoNV){
                NhanVienDeTai *nvdt2_after=i->next;
                nvdt2->next=nvdt1;
                nvdt1->next=nvdt2_after;
            }
        }
    }
        
}

//Hàm lấy ra nhân viên - đề tài
NhanVienDeTai* searchNVDT(NVDT &listNVDT,int maSoNV,int maSoDT){
    for(NhanVienDeTai *i=listNVDT.nvdtHead;i!=nullptr;i=i->next){
        if(i->maSoNV==maSoNV){
            if(i->maSoDT==maSoDT){
                return i;
            }
            if(i->maSoDT>maSoDT){
                return nullptr;
            }
        }
        if(i->maSoNV>maSoNV){
            return nullptr;
        }
    }
    return nullptr;
}


//các hàm kiểm tra xem dữ liệu có trong danh sách không
bool checkNV(const NV& listNV, int maSoNV) {
    for (NhanVien* i = listNV.nvHead; i != nullptr; i = i->next) {
        if (maSoNV == i->maSoNV) {
            return true;
        }
    }
    return false;
}
bool checkDT(const DT& listDT, int maSoDT) {
    for (DeTai* i = listDT.dtHead; i != nullptr; i = i->next) {
        if (maSoDT == i->maSoDT) {
            return true;
        }
    }
    return false;
}
bool checkNVDT_NV(const NVDT& listNVDT, int thisMaSoNV) {
    for (NhanVienDeTai* i = listNVDT.nvdtHead; i != nullptr; i = i->next) {
        if (i->maSoNV== thisMaSoNV) {
            return true;
        }
    }
    return false;
}
bool checkNVDT_DT(const NVDT& listNVDT, int thisMaSoDT) {
    for (NhanVienDeTai* i = listNVDT.nvdtHead; i != nullptr; i = i->next) {
        if (thisMaSoDT == i->maSoDT) {
            return true;
        }
    }
    return false;
}
bool checkNVDT(const NVDT& listNVDT, int thisMaSoNV, int thisMaSoDT) {
    for(NhanVienDeTai *i=listNVDT.nvdtHead;i!=nullptr;i=i->next){
        if(i->maSoNV==thisMaSoNV && i->maSoDT==thisMaSoDT){
            return true;
        }
    }
    return false;
}

//Hàm xóa tất cả các maSoNV trong bảng nhân viên - đề tài 
void xoaDuLieuNVDT_NV(NVDT& listNVDT, int maSoNV) {
    NhanVienDeTai* nvdtPrev = nullptr;
    NhanVienDeTai* nvdt = listNVDT.nvdtHead;

    while (nvdt != nullptr) {
        if (nvdt->maSoNV == maSoNV) {
            NhanVienDeTai* nvdtToDelete = nvdt;

            if (nvdtPrev != nullptr) {
                nvdtPrev->next = nvdt->next;
            } else {
                listNVDT.nvdtHead = nvdt->next;
            }
            if (nvdtToDelete == listNVDT.nvdtTail) {
                listNVDT.nvdtTail = nvdtPrev;
            }

            nvdt = nvdt->next;
            delete nvdtToDelete;
        } else {
            nvdtPrev = nvdt;
            nvdt = nvdt->next;
        }
    }
}

//Hàm xóa tất cả các maSoDT trong bảng nhân viên - đề tài
void xoaDuLieuNVDT_DT(NVDT& listNVDT, int maSoDT) {
    NhanVienDeTai* nvdtPrev = nullptr;
    NhanVienDeTai* nvdt = listNVDT.nvdtHead;

    while (nvdt != nullptr) {
        if (nvdt->maSoDT == maSoDT) {
            NhanVienDeTai* nvdtToDelete = nvdt;

            if (nvdtPrev != nullptr) {
                nvdtPrev->next = nvdt->next;
            } else {
                listNVDT.nvdtHead = nvdt->next;
            }
            if (nvdtToDelete == listNVDT.nvdtTail) {
                listNVDT.nvdtTail = nvdtPrev;
            }

            nvdt = nvdt->next;
            delete nvdtToDelete;
        } else {
            nvdtPrev = nvdt;
            nvdt = nvdt->next;
        }
    }
}

//Hàm xóa 1 dữ liệu trong file nhân viên - đề tài
void xoaDuLieuNVDT(NVDT& listNVDT, int maSoNV, int maSoDT) {
    NhanVienDeTai* nvdtPrev = nullptr;
    NhanVienDeTai* nvdt = listNVDT.nvdtHead;

    while (nvdt != nullptr) {
        if (nvdt->maSoDT == maSoDT && nvdt->maSoNV == maSoNV) {
            if (nvdtPrev != nullptr) {
                nvdtPrev->next = nvdt->next;
            } else {
                listNVDT.nvdtHead = nvdt->next;
            }
            if(nvdt == listNVDT.nvdtTail){
                listNVDT.nvdtTail=nvdtPrev;
            }
            delete nvdt;
            return; 
        }

        nvdtPrev = nvdt;
        nvdt = nvdt->next;
    }
}


//Hàm check nhập nhân viên và output ra nhân viên
int nhapNV(NV & listNV){
    cout<<"Nhap ma so nhan vien: "; addToText("Nhap ma so nhan vien: ");
    int maSoNV;
    // cin>>maSoNV;
    while (!(cin >> maSoNV)) {
        addToText("a\n");
        cin.clear();
        cin.ignore(1000, '\n'); 
        cout << "Ma so nhan vien khong hop le, hay nhap lai!" << endl; addToText("Ma so nhan vien khong hop le, hay nhap lai!\n");
        cout<<"Nhap ma so nhan vien: ";addToText("Nhap ma so nhan vien: ");
    }
    addToText(to_string(maSoNV)+"\n");
    if(!checkNV(listNV,maSoNV)){
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Khong ton tai nhan vien co ma so "<<maSoNV<<" ! Hay kiem tra lai."<<endl; addToText("Khong ton tai nhan vien co ma so "+to_string(maSoNV)+" ! Hay kiem tra lai.\n");
        cout<<endl<<"Nhap phim bat ki de tiep tuc!"; addToText("Return\n");
        getch();
        return 0;
    }
    for(NhanVien *i=listNV.nvHead;i!=nullptr;i=i->next){
        if(i->maSoNV==maSoNV){
            headerOutput("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
            headerOutputToText("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
            cout<<"| "<<i->maSoNV; spaceLength("| Ma so NV ",2+intLength(i->maSoNV));
            addToText("| "+to_string(i->maSoNV)); spaceLengthToText("| Ma so NV ",2+intLength(i->maSoNV));
            cout<<" "<<i->hoDem; spaceLength("|    Ho ten dem    ",2+i->hoDem.length());
            addToText(" "+i->hoDem); spaceLengthToText("|    Ho ten dem    ",2+i->hoDem.length());
            cout<<" "<<i->ten;  spaceLength("|   Ten   ",2+i->ten.length());
            addToText(" "+i->ten);spaceLengthToText("|   Ten   ",2+i->ten.length());
            cout<<" "<<i->gen;spaceLength("|  Gioi tinh  ",2+i->gen.length());
            addToText(" "+ i->gen) ;spaceLengthToText("|  Gioi tinh  ",2+i->gen.length());
            cout<<" "<<i->birthDay;spaceLength("|     Ngay sinh     ",2+i->birthDay.length());
            addToText(" "+i->birthDay) ;spaceLengthToText("|     Ngay sinh     ",2+i->birthDay.length());
            cout<<endl; addToText("\n");
            headerOutLine("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
            headerOutLineToText("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
            addToText("\n");
            break;
        }
    }
    cout<<endl;
    return maSoNV;
}

//Hàm check nhập đề tài và output ra đề tài
int nhapDT(DT &listDT){
    cout<<"Nhap ma so de tai: "; addToText("Nhap ma so de tai: ");
    int maSoDT;
    // cin>>maSoDT;
    while (!(cin >> maSoDT)) {
        addToText("a\n");
        cin.clear();
        cin.ignore(1000, '\n'); 
        cout << "Ma so de tai khong hop le, hay nhap lai!" << endl;addToText("Ma so de tai khong hop le, hay nhap lai!\n");
        cout<<"Nhap ma so de tai: "; addToText("Nhap ma so de tai: ");
    }
    addToText(to_string(maSoDT)+"\n");
    if(!checkDT(listDT,maSoDT)){
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Khong ton tai de tai co ma so "<<maSoDT<<" ! Hay kiem tra lai."<<endl; addToText("Khong ton tai de tai co ma so "+to_string(maSoDT)+" ! Hay kiem tra lai.\n");
        cout<<endl<<"Nhap phim bat ki de tiep tuc!"; addToText("Return\n");
        getch();
        return 0;
    }
    for(DeTai *i=listDT.dtHead;i!=nullptr;i=i->next){
        if(i->maSoDT==maSoDT){
            headerOutput("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
            headerOutputToText("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
            string kinhPhi=to_string(i->kinhPhi);
            cout<<"| "<<i->maSoDT;spaceLength("| Ma so DT ",2+intLength(i->maSoDT));
                addToText("| "+ to_string(i->maSoDT) );spaceLengthToText("| Ma so DT ",2+intLength(i->maSoDT));
            cout<<" "<<i->tenDeTai;spaceLength("|    Ten de tai    ",2+i->tenDeTai.length());
                addToText(" "+i->tenDeTai);spaceLengthToText("|    Ten de tai    ",2+i->tenDeTai.length());
            cout<<" "<<i->namBatDau;spaceLength("| Nam bat dau ",2+intLength(i->namBatDau));
                addToText(" "+to_string(i->namBatDau));spaceLengthToText("| Nam bat dau ",2+intLength(i->namBatDau));
            cout<<" "<<i->namKetThuc;spaceLength("| Nam ket thuc ",2+intLength(i->namKetThuc));
                addToText(" "+to_string(i->namKetThuc));spaceLengthToText("| Nam ket thuc ",2+intLength(i->namKetThuc));
            cout<<" "<<kinhPhi;spaceLength("|        Kinh phi        ",2+kinhPhi.length());	
                addToText(" "+kinhPhi);spaceLengthToText("|        Kinh phi        ",2+kinhPhi.length());
            cout<<endl;
                addToText("\n");
            headerOutLine("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
            headerOutLineToText("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
            addToText("\n");
            break;
        }
    }
    cout<<endl;
    return maSoDT;
}


//các hàm menu thêm dữ liệu vào danh sách
void menuThemDuLieuListNV(NV &listNV){
    nhapLaiNV:
    int maSoNV=MaSoNV(listNV);
    hoDem:
    cout<<"Ho va ten dem: "; addToText("Ho va ten dem: ");
        string hoDem;
        getline(cin,hoDem);
        addToText(hoDem+"\n");
        for(int i=0;i<hoDem.length();i++){
            if(hoDem[i]>='0'&&hoDem[i]<='9'){
                cout<<"Ho dem khong the chua chu so!"<<endl; addToText("Ho dem khong the chua chu so!\n");
                cout<<"Vui long nhap lai. ";    addToText("Vui long nhap lai. ");
                goto hoDem;
            }
        }
        hoDem=checkString(hoDem);
    ten:
    cout<<"Ten: "; addToText("Ten: ");
        string ten;
        getline(cin,ten); addToText(ten+"\n");
        ten=checkString(ten);
        for(int i=0;i<ten.length();i++){
            if(ten[i]>='0'&&ten[i]<='9'){
                cout<<"Ten khong the chua chu so!"<<endl; addToText("Ten khong the chua chu so!\n");
                cout<<"Vui long nhap lai. ";addToText("Vui long nhap lai. ");
                goto ten;
            }
            if(ten[i]==' '){
                cout<<"Ten khong the chua dau cach (ten chi la 1 tu)!"<<endl; addToText("Ten khong the chua dau cach (ten chi la 1 tu)!\n");
                cout<<"Vui long nhap lai. ";addToText("Vui long nhap lai. ");
                goto ten;
            }
        }
    cout<<"Gioi tinh: "; addToText("Gioi tinh: \n");
        cout<<endl;
        int genNum = luaChon("Nam","Nu","Khac","","","");
        string gen;
        switch(genNum){
            case 0: gen="Nam";break;
            case 1: gen="Nu";break;
            case 2: gen="Khac";break;
        }
        cout<<endl; addToText("\n");
    cout<<"Ngay sinh (dd mm yyyy): "; addToText("Ngay sinh (dd mm yyyy): ");
        DATE d;
        string birthDay=BirthDay(d); 
    cout<<endl<<"Check thong tin: "<<endl;
        addToText("\nCheck thong tin: \n");

        headerOutput("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
        headerOutputToText("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
        cout<<"| "<<maSoNV; spaceLength("| Ma so NV ",2+intLength(maSoNV));
        addToText("| "+to_string(maSoNV)); spaceLengthToText("| Ma so NV ",2+intLength(maSoNV));
        cout<<" "<<hoDem; spaceLength("|    Ho ten dem    ",2+hoDem.length());
        addToText(" "+hoDem); spaceLengthToText("|    Ho ten dem    ",2+hoDem.length());
        cout<<" "<<ten;  spaceLength("|   Ten   ",2+ten.length());
        addToText(" "+ten);spaceLengthToText("|   Ten   ",2+ten.length());
        cout<<" "<<gen;spaceLength("|  Gioi tinh  ",2+gen.length());
        addToText(" "+ gen) ;spaceLengthToText("|  Gioi tinh  ",2+gen.length());
        cout<<" "<<birthDay;spaceLength("|     Ngay sinh     ",2+birthDay.length());
        addToText(" "+birthDay) ;spaceLengthToText("|     Ngay sinh     ",2+birthDay.length());
        cout<<endl; addToText("\n");
        headerOutLine("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
        headerOutLineToText("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
        addToText("\n");
        
        // cout<<maSoNV<<"  "<<hoDem<<"  "<<ten<<"  "<<gen<<"  "<<birthDay;
        cout<<endl;
        int check=luaChon("Luu","Huy","Nhap lai","","","");
    if(check==0){
        NhanVien *newNV = KhoiTaoNV(maSoNV, hoDem, ten, gen, birthDay);
        NhanVien *nv = searchToAddNV(listNV,maSoNV);
        addNV(listNV, newNV,nv);
        // saveListNvToFile(listNV,"NV.bin");
        cin.clear();
        cin.ignore();
        addToText("\n");
    }else if(check==2){
        cout<<endl<<endl<<"Nhap lai: "<<endl;
        addToText("\n\nNhap lai: \n");
        cin.clear();
        cin.ignore();
        goto nhapLaiNV;
    }else if(check==1){
        cin.clear();
        cin.ignore();
        addToText("\n");
    }
}
void menuThemDuLieuListDT(DT &listDT){
    nhapLaiDT:
    int maSoDT=MaSoDT(listDT);
    cout<<"Ten de tai: ";addToText("Ten de tai: ");
        string tenDeTai;
        getline(cin,tenDeTai); addToText(tenDeTai);
    cout<<"Nam bat dau: ";addToText("\nNam bat dau: ");
        int namBatDau;
        // cin>>namBatDau;
        while (!(cin >> namBatDau)|| namBatDau >2023 || namBatDau<1000) {
            addToText(to_string(namBatDau));
            cin.clear();
            cin.ignore(1000, '\n'); 
            cout << "Nam bat dau khong hop le, hay nhap lai!" << endl; addToText("\nNam bat dau khong hop le, hay nhap lai!\n" );
            cout << "Nam bat dau: "; addToText("\nNam bat dau: " );
        }
        addToText(to_string(namBatDau));
    cout<<"Nam ket thuc: ";addToText("\nNam ket thuc: ");
        int namKetThuc;
        // cin>>namKetThuc;
        while (!(cin >> namKetThuc)|| namKetThuc < 1000 ||namKetThuc<namBatDau) {
            if(namKetThuc<namBatDau ){
                cout<<endl<<"Nam ket thuc khong the nho hon nam bat dau. Hay nhap lai !"<<endl; addToText("\nNam ket thuc khong the nho hon nam bat dau. Hay nhap lai !\n");
                cout<<"Nam ket thuc: "; addToText("Nam ket thuc: ");
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }
            cin.clear();
            cin.ignore(1000, '\n'); 
            cout << "Nam ket thuc khong hop le, hay nhap lai!" << endl; addToText("\nNam ket thuc khong hop le, hay nhap lai!\n" );
            cout << "Nam ket thuc: "; addToText("\nNam ket thuc: " );
        }
        addToText(to_string(namKetThuc)+"\n");
    cout<<"Kinh phi: "; addToText("Kinh phi: ");
        long long kinhPhi;
        // cin>>kinhPhi;
        while (!(cin >> kinhPhi) || kinhPhi < 0) {
            addToText(to_string(kinhPhi));
            cin.clear();
            cin.ignore(1000, '\n'); 
            cout << "Kinh phi khong hop le, hay nhap lai!" << endl;addToText("\nKinh phi khong hop le, hay nhap lai!\n" );
            cout << "Kinh phi: ";addToText("Kinh phi: ");
        }
        addToText(to_string(kinhPhi));
    cout<<endl<<"Check thong tin: "<<endl; addToText("\n\nCheck thong tin: \n");

        headerOutput("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
        headerOutputToText("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
        string kinhPhiS=to_string(kinhPhi);
        cout<<"| "<<maSoDT;spaceLength("| Ma so DT ",2+intLength(maSoDT));
            addToText("| "+ to_string(maSoDT) );spaceLengthToText("| Ma so DT ",2+intLength(maSoDT));
        cout<<" "<<tenDeTai;spaceLength("|    Ten de tai    ",2+tenDeTai.length());
            addToText(" "+tenDeTai);spaceLengthToText("|    Ten de tai    ",2+tenDeTai.length());
        cout<<" "<<namBatDau;spaceLength("| Nam bat dau ",2+intLength(namBatDau));
            addToText(" "+to_string(namBatDau));spaceLengthToText("| Nam bat dau ",2+intLength(namBatDau));
        cout<<" "<<namKetThuc;spaceLength("| Nam ket thuc ",2+intLength(namKetThuc));
            addToText(" "+to_string(namKetThuc));spaceLengthToText("| Nam ket thuc ",2+intLength(namKetThuc));
        cout<<" "<<kinhPhiS;spaceLength("|        Kinh phi        ",2+kinhPhiS.length());	
            addToText(" "+kinhPhiS);spaceLengthToText("|        Kinh phi        ",2+kinhPhiS.length());
        cout<<endl;
            addToText("\n");
        headerOutLine("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
        headerOutLineToText("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
        addToText("\n");

        // cout<<maSoDT<<"  "<<tenDeTai<<"  "<<namBatDau<<"  "<<namKetThuc<<"  "<<kinhPhi;
        cout<<endl; addToText("\n");
        int check=luaChon("Luu","Huy","Nhap lai","","","");
    if(check==0){
        DeTai *newDT = KhoiTaoDT(maSoDT , tenDeTai, namBatDau, namKetThuc,kinhPhi);
        DeTai *dt=searchToAddDT(listDT,maSoDT);
        addDT(listDT,newDT, dt);
        // saveListDtToFile(listDT,"DT.bin");
        cin.clear();
        cin.ignore();
        addToText("\n");
    }else if(check==2){
        cout<<endl<<endl<<"Nhap lai: "<<endl;addToText("\n\nNhap lai: \n");
        cin.clear();
        cin.ignore();
        goto nhapLaiDT;
    }else if(check==1){
        cin.clear();
        cin.ignore();
        addToText("\n");
    }
}
void menuThemDuLieuListNVDT(NV &listNV,DT &listDT,NVDT &listNVDT){
    nhapLaiNVDT:
    int maSoNV=nhapNV(listNV);
    if(maSoNV==0){
        return;
    }
    int maSoDT=nhapDT(listDT);
    if(maSoDT == 0){
        return;
    }
    while(1){
        if(!checkNVDT(listNVDT,maSoNV,maSoDT)){
            break;
        }else{
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<endl;
            cout<<"Nhan vien co ma so "<<maSoNV<<" da thuoc de tai "<<maSoDT<<" roi, khong the them nua!"<<endl;
                addToText("Nhan vien co ma so "+to_string(maSoNV)+" da thuoc de tai "+to_string(maSoDT)+" roi, khong the them nua!\n");
            cout<<endl<<"Nhap phim bat ki de tiep tuc !"; 
                addToText("\nNhap phim bat ki de tiep tuc !");
            _getch();
            return;
        }
    }
    cout<<endl<<"Vai tro: "; addToText("Vai tro: \n");
        cout<<endl;
        int vaiTroNum=luaChon("Chu nhiem","Thu ki","Thanh vien","","","");
        string vaiTro;
        switch (vaiTroNum){
            case 0: vaiTro="Chu nhiem";break;
            case 1: vaiTro="Thu ki";break;
            case 2: vaiTro="Thanh vien";break;
        }
        cout<<endl;
        addToText("\n");
    cout<<endl<<"Check thong tin: "<<endl; addToText("\nCheck thong tin: \n");

        headerOutput("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
        headerOutputToText("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
        cout<<"| "<<maSoNV;spaceLength("| Ma so NV ",2+intLength(maSoNV));
            addToText("| "+to_string(maSoNV));spaceLengthToText("| Ma so NV ",2+intLength(maSoNV));
        cout<<" "<<maSoDT;spaceLength("| Ma so DT ",2+intLength(maSoDT));
            addToText(" "+to_string(maSoDT));spaceLengthToText("| Ma so DT ",2+intLength(maSoDT));
        cout<<" "<<vaiTro;spaceLength("|   Vai tro   ",2+vaiTro.length());
            addToText(" "+vaiTro);spaceLengthToText("|   Vai tro   ",2+vaiTro.length());
        cout<<endl;
        addToText("\n");
        headerOutLine("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
        headerOutLineToText("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
        addToText("\n");

        cout<<endl;
        int check=luaChon("Luu","Huy","Nhap lai","","","");;
    if(check==0){
        NhanVienDeTai *newNVDT = KhoiTaoNVDT(maSoNV, maSoDT, vaiTro);
        NhanVienDeTai *nvdtPrev=searchToAddNhanVienDeTai(listNVDT,maSoNV,maSoDT);
        addNVDT(listNVDT,newNVDT,nvdtPrev);
        // saveListDtToFile(listDT,"DT.bin");
        cin.clear();
        cin.ignore();
        addToText("\n");
    }else if(check==2){
        cout<<endl<<endl<<"Nhap lai: "<<endl; addToText("\n\nNhap lai: \n");
        cin.clear();
        cin.ignore();
        goto nhapLaiNVDT;
    }else if(check==1){
        cin.clear();
        cin.ignore();
        addToText("\n");
    }
    // saveListNvdtToFile(listNVDT,"NVDT.bin");
}

//các hàm menu xóa dữ liệu khỏi danh sách
void menuXoaDuLieuListNVDT(NVDT &listNVDT,NV &listNV,DT &listDT){
    nhapLaiXoaNVDT:
    cout<<"Nhap ma so nhan vien: "; addToText("Nhap ma so nhan vien: ");
        int maSoNV;
        // cin>>maSoNV;
        while (!(cin >> maSoNV)) {
            addToText("a\n");
            cin.clear();
            cin.ignore(1000, '\n'); 
            cout << "Ma so nhan vien khong hop le, hay nhap lai!" << endl; addToText("Ma so nhan vien khong hop le, hay nhap lai!\n");
            cout<<"Nhap ma so nhan vien: ";addToText("Nhap ma so nhan vien: ");
        }
        addToText(to_string(maSoNV)+"\n");
        while(1){
            if(!checkNV(listNV,maSoNV)){
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Khong ton tai nhan vien co ma so "<<maSoNV<<" ! Hay kiem tra lai."<<endl; addToText("Khong ton tai nhan vien co ma so "+to_string(maSoNV) +" ! Hay kiem tra lai.\n");
                cout<<endl<<"Nhap phim bat ki de tiep tuc!"; addToText("Return\n");
                getch();
                return;
            }
            if(checkNVDT_NV(listNVDT,maSoNV)){
                break;
            }
            else{
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Nhan vien co ma so "<<maSoNV<<" khong tham gia de tai nao ! Hay kiem tra lai."<<endl; addToText("Nhan vien co ma so "+to_string(maSoNV)+" khong tham gia de tai nao ! Hay kiem tra lai.\n");
                cout<<endl<<"Nhap phin bat ki de tiep tuc!"; addToText("Return\n");
                getch();
                return;
            }
        }

        cout<<"Cac de tai ma nhan vien co ma so "<<maSoNV<<" tham gia: "<<endl; addToText("Cac de tai ma nhan vien co ma so "+to_string(maSoNV)+" tham gia: \n");
        headerOutput("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
        headerOutputToText("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
        for(NhanVienDeTai *i=listNVDT.nvdtHead;i!=nullptr;i=i->next){
            if(i->maSoNV==maSoNV){
                cout<<"| "<<i->maSoNV;spaceLength("| Ma so NV ",2+intLength(i->maSoNV));
                addToText("| "+to_string(i->maSoNV));spaceLengthToText("| Ma so NV ",2+intLength(i->maSoNV));
                cout<<" "<<i->maSoDT;spaceLength("| Ma so DT ",2+intLength(i->maSoDT));
                addToText(" "+to_string(i->maSoDT));spaceLengthToText("| Ma so DT ",2+intLength(i->maSoDT));
                cout<<" "<<i->vaiTro;spaceLength("|   Vai tro   ",2+i->vaiTro.length());
                addToText(" "+i->vaiTro);spaceLengthToText("|   Vai tro   ",2+i->vaiTro.length());
                cout<<endl;
                addToText("\n");
            }
        }
        headerOutLine("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
        headerOutLineToText("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
        cout<<endl;addToText("\n");

    cout<<"Nhap ma so de tai muon xoa: ";addToText("Nhap ma so de tai muon xoa: ");
        int maSoDT;
        // cin>>maSoDT;
        while (!(cin >> maSoDT)) {
            addToText("b\n");
            cin.clear();
            cin.ignore(1000, '\n'); 
            cout << "Ma so de tai khong hop le, hay nhap lai!" << endl; addToText("Ma so de tai khong hop le, hay nhap lai!\n");
            cout<<"Nhap ma so de tai muon xoa: "; addToText("Nhap ma so de tai muon xoa: ");
        }
        addToText(to_string(maSoDT)+"\n");
        while(1){
            if(!checkDT(listDT,maSoDT)){
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Khong ton tai de tai co ma so "<<maSoDT<<" ! Hay kiem tra lai."<<endl; addToText("Khong ton tai de tai co ma so "+to_string(maSoDT)+" ! Hay kiem tra lai.\n");
                cout<<"Nhap phim bat ki de tiep tuc!";
                getch();addToText("Return\n");
                return;
            }
            if(checkNVDT(listNVDT,maSoNV, maSoDT)){
                break;
            }else{
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Nhan vien co ma so "<<maSoNV<<" khong tham gia de tai "<<maSoDT<<" ! Hay kiem tra lai."<<endl; addToText("Nhan vien co ma so "+to_string(maSoNV)+" khong tham gia de tai "+to_string(maSoDT)+" ! Hay kiem tra lai.\n");
                cout<<endl<<"Nhap phin bat ki de tiep tuc!";addToText("Return\n");
                getch();
                return;
            }
        }
    cout<<"Ban chac chan muon xoa nhan vien - de tai tren ?"<<endl; addToText("Ban chac chan muon xoa nhan vien - de tai tren ?\n");
    int check=luaChon("Xoa", "Huy","Nhap lai","","","");addToText("\n");
    if(check==0){
        cin.ignore();
        cin.clear();
        xoaDuLieuNVDT(listNVDT,maSoNV,maSoDT);
        cout<<"Xoa thanh cong!";addToText("Xoa thanh cong!");
    }else if(check==1){
        cin.ignore();
        cin.clear();
        addToText("Return\n");
    }else if(check==2){
        cout<<endl<<endl<<"Nhap lai: "<<endl; addToText("\n\nNhap lai!\n");
        cin.clear();
        cin.ignore();
        goto nhapLaiXoaNVDT;
    }

}
void menuXoaDuLieuListNV(NV &listNV, NVDT &listNVDT){
    nhapLaiXoaNV:
    int maSoNV=nhapNV(listNV);
    if (maSoNV==0){
        return;
    }
    cout<<"Ban chac chan muon xoa nhan vien tren ?"<<endl; addToText("Ban chac chan muon xoa nhan vien tren ?\n");
    int check=luaChon("Xoa", "Huy","Nhap lai","","","");addToText("\n");
    if(check==0){
        cin.clear();
        cin.ignore();
        xoaNV(listNV,listNVDT,maSoNV);
        cout<<endl<<endl<<"Da xoa nhan vien "<<maSoNV<<" !"<<endl; addToText("Da xoa nhan vien "+to_string(maSoNV)+" !\n");
    }else if(check==1){
        cin.ignore();
        cin.clear(); addToText("Da huy!\n");
    }else if(check==2){
        cout<<endl<<endl<<"Nhap lai: "<<endl;addToText("\nNhap lai!\n");
        cin.clear();
        cin.ignore();
        goto nhapLaiXoaNV;
    }
}
void menuXoaDuLieuListDT(DT &listDT, NVDT &listNVDT){
    nhapLaiXoaDT:
    int maSoDT=nhapDT(listDT);
    if(maSoDT==0){
        return;
    }
    cout<<endl<<"Ban chac chan muon xoa de tai tren ?"<<endl; addToText("Ban chac chan muon xoa de tai tren ?\n");
    int check=luaChon("Xoa", "Huy","Nhap lai","","","");addToText("\n");
    cout<<endl;
    if(check==0){
        cin.ignore();
        cin.clear();
        xoaDT(listDT,listNVDT,maSoDT);
        cout<<endl<<endl<<"Da xoa de tai "<< maSoDT<<" !"<<endl; addToText("Da xoa de tai "+to_string(maSoDT)+" !\n");
    }else if(check==1){
        cin.ignore();
        cin.clear();addToText("Da huy!\n");
    }else if(check==2){
        cout<<endl<<"Nhap lai: "<<endl;addToText("\nNhap lai!\n");
        cin.clear();
        cin.ignore();
        goto nhapLaiXoaDT;
    }
}

//Các hàm chỉnh sửa dữ liệu của danh sách
void menuSuaDuLieuListNV(NV &listNV){
    nhapLaiCapNhatNV:
    int maSoNV=nhapNV(listNV);
    if (maSoNV==0){
        return;
    }
    NhanVien *nv=searchNV(listNV,maSoNV);
    cout<<"Chon thong tin muon chinh sua: "<<endl; addToText("Chon thong tin muon chinh sua: \n");
    int luachon=luaChon("Ho ten dem","Ten","Gioi tinh","Ngay sinh","Huy","Nhap lai ma so nhan vien");
    string newHoDem=nv->hoDem;
    string newTen=nv->ten;
    string newGen=nv->gen;
    string newBirthDay=nv->birthDay;
    cout<<endl;
    addToText("\n");
    cin.clear();
    cin.ignore();
    switch(luachon){
        case 0:
            newHoDem:
            cout<<"Nhap ho ten dem moi: "; addToText("Nhap ho ten dem moi: ");
            getline(cin,newHoDem); addToText(newHoDem+"\n");
            for(int i=0;i<newHoDem.length();i++){
                if(newHoDem[i]>='0'&&newHoDem[i]<='9'){
                    cout<<"Ho dem khong the chua chu so!"<<endl; addToText("Ho dem khong the chua chu so!\n");
                    cout<<"Vui long nhap lai. ";addToText("Vui long nhap lai. ");
                    goto newHoDem;
                }
            }
            newHoDem = checkString(newHoDem);
            break;
        case 1:
            newTen:
            cout<<"Nhap ten moi: "; addToText("Nhap ten moi: ");
            getline(cin,newTen);addToText(newTen+"\n");
            for(int i=0;i<newTen.length();i++){
                if(newTen[i]>='0'&&newTen[i]<='9'){
                    cout<<"Ten khong the chua chu so!"<<endl;addToText("Ten khong the chua chu so!\n");
                    cout<<"Vui long nhap lai. ";addToText("Vui long nhap lai. ");
                    goto newTen;
                }
                if(newTen[i]==' '){
                    cout<<"Ten khong the chua dau cach (ten chi la 1 tu)!"<<endl; addToText("Ten khong the chua dau cach (ten chi la 1 tu)!\n");
                    cout<<"Vui long nhap lai. ";addToText("Vui long nhap lai. ");
                    goto newTen;
                }
            }
            newTen=checkString(newTen);
            break;
        case 2:
            cout<<"Chon gioi tinh moi: "<<endl; addToText("Chon gioi tinh moi: \n");
            switch(luaChon("Nam","Nu","Khac","","","")){
                case 0: newGen="Nam";break;
                case 1: newGen="Nu";break;
                case 2: newGen="Khac";break;
            }
            break;
        case 3:
            cout<<"Nhap ngay sinh moi (dd mm yyyy): "; addToText("Nhap ngay sinh moi (dd mm yyyy): ");
            DATE d; 
            newBirthDay=BirthDay(d);
            break;
        case 4:
            addToText("\nReturn\n");
            return;
        case 5:
            cout<<"Nhap lai!"<<endl;
            addToText("Nhap lai: \n");
            goto nhapLaiCapNhatNV;

    }
    cout<<endl;addToText("\n");
    cout<<"Thong tin sau khi chinh sua: "<<endl; addToText("Thong tin sau khi chinh sua: \n");
        headerOutput("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
        headerOutputToText("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
        cout<<"| "<<maSoNV; spaceLength("| Ma so NV ",2+intLength(maSoNV));
        addToText("| "+to_string(maSoNV)); spaceLengthToText("| Ma so NV ",2+intLength(maSoNV));
        cout<<" "<<newHoDem; spaceLength("|    Ho ten dem    ",2+newHoDem.length());
        addToText(" "+newHoDem); spaceLengthToText("|    Ho ten dem    ",2+newHoDem.length());
        cout<<" "<<newTen;  spaceLength("|   Ten   ",2+newTen.length());
        addToText(" "+newTen);spaceLengthToText("|   Ten   ",2+newTen.length());
        cout<<" "<<newGen;spaceLength("|  Gioi tinh  ",2+newGen.length());
        addToText(" "+ newGen) ;spaceLengthToText("|  Gioi tinh  ",2+newGen.length());
        cout<<" "<<newBirthDay;spaceLength("|     Ngay sinh     ",2+newBirthDay.length());
        addToText(" "+newBirthDay) ;spaceLengthToText("|     Ngay sinh     ",2+newBirthDay.length());
        cout<<endl; addToText("\n");
        headerOutLine("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
        headerOutLineToText("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
        addToText("\n");

    cout<<endl;
    int check=luaChon("Cap nhat","Huy","","","","");
    if(check==0){
        nv->hoDem=newHoDem;
        nv->ten=newTen;
        nv->gen=newGen;
        nv->birthDay=newBirthDay;
        cout<<endl<<"Cap nhat thanh cong!"<<endl; addToText("\nCap nhap thanh cong!\n");
        cout<<endl<<"Nhap phim bat ki de tiep tuc."; addToText("Return\n");
        cin.clear();
        cin.ignore();
    }
    else if(check==1){
        addToText("\nReturn\n");
        return;
    }

}
void menuSuaDuLieuListDT(DT &listDT){
    nhapLaiCapNhatDT:
    int maSoDT=nhapDT(listDT);
    if(maSoDT == 0){
        return;
    }
    DeTai *dt=searchDT(listDT,maSoDT);
    cout<<"Chon thong tin muon chinh sua: "<<endl; addToText("Chon thong tin muon chinh sua: \n");
    int luachon=luaChon("Ten de tai","Nam bat dau","Nam ket thuc","Kinh phi","Huy","Nhap lai ma so de tai");
    string newTenDeTai=dt->tenDeTai;
    int newNamBatDau=dt->namBatDau;
    int newNamKetThuc=dt->namKetThuc;
    long long newKinhPhi=dt->kinhPhi;
    cout<<endl;addToText("\n");
    cin.clear();
    cin.ignore();
    switch(luachon){
        case 0:
            cout<<"Nhap ten de tai moi: "; addToText("Nhap ten de tai moi: ");
            getline(cin,newTenDeTai); addToText(newTenDeTai);
            break;
        case 1:
            cout<<"Nhap nam bat dau moi: "; addToText("Nhap nam bat dau moi: ");
            while (!(cin >> newNamBatDau)|| newNamBatDau >2023 || newNamBatDau<1000 || newNamBatDau>newNamKetThuc) {
                addToText(to_string(newNamBatDau));
                if(newNamBatDau>newNamKetThuc){
                    cout<<endl<<"Nam bat dau khong the lon hon nam ket thuc !"<<endl; addToText("\nNam bat dau khong the lon hon nam ket thuc !\n");
                    cout<<endl<<"Nhap phim bat ki de tiep tuc."; addToText("Return\n");
                    getch();
                    return;
                }
                cin.clear();
                cin.ignore(1000, '\n'); 
                cout << "Nam bat dau khong hop le, hay nhap lai!" << endl; addToText("Nam bat dau khong hop le, hay nhap lai!\n");
                cout << "Nam bat dau: ";addToText("Nam bat dau: ");
            }
            break;
        case 2:
            cout<<"Nhap nam ket thuc moi: "; addToText("Nhap nam ket thuc moi: ");
            while (!(cin >> newNamKetThuc) || newNamKetThuc < 1000 ||newNamKetThuc<newNamBatDau) {
                addToText(to_string(newNamKetThuc));
                cin.clear();
                cin.ignore(1000, '\n'); 
                cout << "Nam ket thuc khong hop le, hay nhap lai!" << endl; addToText("Nam ket thuc khong hop le, hay nhap lai!\n");
                cout << "Nam ket thuc: ";addToText("Nam ket thuc: ");
            }
            break;
        case 3:
            cout<<"Nhap kinh phi moi: "; addToText("Nhap kinh phi moi: ");
            while (!(cin >> newKinhPhi) || newKinhPhi < 0) {
                addToText(to_string(newKinhPhi));
                cin.clear();
                cin.ignore(1000, '\n'); 
                cout << "Kinh phi khong hop le, hay nhap lai!" << endl; addToText("Kinh phi khong hop le, hay nhap lai!\n");
                cout << "Kinh phi: ";addToText("Kinh phi: ");
            }
            break;
        case 4:
            addToText("Return\n");
            return;
        case 5:
            cout<<"Nhap lai!"<<endl;
            addToText("\nNhap lai!\n");
            goto nhapLaiCapNhatDT;
    }
    cout<<endl;
    cout<<"Thong tin sau khi chinh sua: "<<endl; addToText("\nThong tin sau khi chinh sua: \n");

    headerOutput("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
    headerOutputToText("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
    string kinhPhiS=to_string(newKinhPhi);
    cout<<"| "<<maSoDT;spaceLength("| Ma so DT ",2+intLength(maSoDT));
        addToText("| "+ to_string(maSoDT) );spaceLengthToText("| Ma so DT ",2+intLength(maSoDT));
    cout<<" "<<newTenDeTai;spaceLength("|    Ten de tai    ",2+newTenDeTai.length());
        addToText(" "+newTenDeTai);spaceLengthToText("|    Ten de tai    ",2+newTenDeTai.length());
    cout<<" "<<newNamBatDau;spaceLength("| Nam bat dau ",2+intLength(newNamBatDau));
        addToText(" "+to_string(newNamBatDau));spaceLengthToText("| Nam bat dau ",2+intLength(newNamBatDau));
    cout<<" "<<newNamKetThuc;spaceLength("| Nam ket thuc ",2+intLength(newNamKetThuc));
        addToText(" "+to_string(newNamKetThuc));spaceLengthToText("| Nam ket thuc ",2+intLength(newNamKetThuc));
    cout<<" "<<kinhPhiS;spaceLength("|        Kinh phi        ",2+kinhPhiS.length());	
        addToText(" "+kinhPhiS);spaceLengthToText("|        Kinh phi        ",2+kinhPhiS.length());
    cout<<endl;
        addToText("\n");
    headerOutLine("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
    headerOutLineToText("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
    addToText("\n");

    cout<<endl;
    int check=luaChon("Cap nhat","Huy","","","","");
    addToText("\n");
    if(check==0){
        dt->tenDeTai=newTenDeTai;
        dt->namBatDau=newNamBatDau;
        dt->namKetThuc=newNamKetThuc;
        dt->kinhPhi=newKinhPhi;
        cout<<endl<<"Cap nhat thanh cong!"<<endl; addToText("Cap nhat thanh cong!\nReturn\n");
        cout<<endl<<"Nhap phim bat ki de tiep tuc.";
        cin.clear();
        cin.ignore();
        getch();
    }
    else if(check==1){
        cout<<endl<<"Da huy!"<<endl<<" Nhap phim bat ki de tiep tuc.";
        addToText("Da huy!\nReturn\n");
        cin.clear();
        cin.ignore();
        return;
    }
    
}
void menuSuaDuLieuListNVDT( NV &listNV, DT &listDT,NVDT &listNVDT){
    nhapLaiChinhSuaNVDT:
    cout<<"Nhap ma so nhan vien: "; addToText("Nhap ma so nhan vien: ");
        int maSoNV;
        // cin>>maSoNV;
        while (!(cin >> maSoNV)) {
            addToText("a\n");
            cin.clear();
            cin.ignore(1000, '\n'); 
            cout << "Ma so nhan vien khong hop le, hay nhap lai!" << endl; addToText("Ma so nhan vien khong hop le, hay nhap lai!\n");
            cout<<"Nhap ma so nhan vien: "; addToText("Nhap ma so nhan vien: ");
        }
        addToText(to_string(maSoNV)+"\n");
        while(1){
            if(!checkNV(listNV,maSoNV)){
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Khong ton tai nhan vien co ma so "<<maSoNV<<" ! Hay kiem tra lai."<<endl; addToText("Khong ton tai nhan vien co ma so "+to_string(maSoNV) +" ! Hay kiem tra lai.\n");
                cout<<endl<<"Nhap phim bat ki de tiep tuc!";addToText("Return\n");
                getch();
                return;
            }
            if(checkNVDT_NV(listNVDT,maSoNV)){
                break;
            }
            else{
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Nhan vien co ma so "<<maSoNV<<" khong tham gia de tai nao ! Hay kiem tra lai."<<endl; addToText("Nhan vien co ma so "+to_string(maSoNV)+" khong tham gia de tai nao ! Hay kiem tra lai.\n");
                cout<<endl<<"Nhap phin bat ki de tiep tuc!";addToText("Return\n");
                getch();
                return;
            }
        }

        cout<<"Cac de tai ma nhan vien co ma so "<<maSoNV<<" tham gia: "<<endl; addToText("Cac de tai ma nhan vien co ma so "+to_string(maSoNV)+" tham gia: \n");
        headerOutput("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
        headerOutputToText("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
        for(NhanVienDeTai *i=listNVDT.nvdtHead;i!=nullptr;i=i->next){
            if(i->maSoNV==maSoNV){
                cout<<"| "<<i->maSoNV;spaceLength("| Ma so NV ",2+intLength(i->maSoNV));
                addToText("| "+to_string(i->maSoNV));spaceLengthToText("| Ma so NV ",2+intLength(i->maSoNV));
                cout<<" "<<i->maSoDT;spaceLength("| Ma so DT ",2+intLength(i->maSoDT));
                addToText(" "+to_string(i->maSoDT));spaceLengthToText("| Ma so DT ",2+intLength(i->maSoDT));
                cout<<" "<<i->vaiTro;spaceLength("|   Vai tro   ",2+i->vaiTro.length());
                addToText(" "+i->vaiTro);spaceLengthToText("|   Vai tro   ",2+i->vaiTro.length());
                cout<<endl;
                addToText("\n");
            }
        }
        headerOutLine("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
        headerOutLineToText("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
        cout<<endl;
        addToText("\n");

    cout<<"Nhap ma so de tai muon chinh sua: "; addToText("Nhap ma so de tai muon chinh sua: ");
        int maSoDT;
        // cin>>maSoDT;
        while (!(cin >> maSoDT)) {
            addToText("a\n");
            cin.clear();
            cin.ignore(1000, '\n'); 
            cout << "Ma so de tai khong hop le, hay nhap lai!" << endl; addToText("Ma so de tai khong hop le, hay nhap lai!\n");
            cout<<"Nhap ma so de tai muon xoa: ";addToText("Nhap ma so de tai muon xoa: ");
        }
        addToText(to_string(maSoDT)+"\n");
        while(1){
            if(!checkDT(listDT,maSoDT)){
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Khong ton tai de tai co ma so "<<maSoDT<<" ! Hay kiem tra lai."<<endl; addToText("Khong ton tai de tai co ma so "+to_string(maSoDT)+" ! Hay kiem tra lai.\n");
                getch();addToText("Return\n");
                return;
            }
            if(checkNVDT(listNVDT,maSoNV, maSoDT)){
                break;
            }else{
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Nhan vien co ma so "<<maSoNV<<" khong tham gia de tai "<<maSoDT<<" ! Hay kiem tra lai."<<endl; addToText("Nhan vien co ma so "+to_string(maSoNV)+" khong tham gia de tai "+to_string(maSoDT)+" ! Hay kiem tra lai.\n");
                cout<<endl<<"Nhap phin bat ki de tiep tuc!";addToText("Return\n");
                getch();
                return;
            }
        }
    cout<<"Chon vai tro moi: "; addToText("Chon vai tro moi: \n");
    cout<<endl;
    string newVaiTro;
    switch (luaChon("Chu nhiem","Thu ki","Thanh vien","","","")){
        case 0: newVaiTro="Chu nhiem";break;
        case 1: newVaiTro="Thu ki";break;
        case 2: newVaiTro="Thanh vien";break;
    }
    cout<<endl;addToText("\n");
    cout<<"Thong tin sau khi chinh sua: "<<endl; addToText("Thong tin sau khi chinh sua: \n");
    headerOutput("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
    headerOutputToText("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
        cout<<"| "<<maSoNV;spaceLength("| Ma so NV ",2+intLength(maSoNV));
            addToText("| "+to_string(maSoNV));spaceLengthToText("| Ma so NV ",2+intLength(maSoNV));
        cout<<" "<<maSoDT;spaceLength("| Ma so DT ",2+intLength(maSoDT));
            addToText(" "+to_string(maSoDT));spaceLengthToText("| Ma so DT ",2+intLength(maSoDT));
        cout<<" "<<newVaiTro;spaceLength("|   Vai tro   ",2+newVaiTro.length());
            addToText(" "+newVaiTro);spaceLengthToText("|   Vai tro   ",2+newVaiTro.length());
        cout<<endl;
        addToText("\n");
    headerOutLine("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
    headerOutLineToText("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");

        cout<<endl;addToText("\n");
        int check=luaChon("Cap nhat","Huy","Nhap lai","","","");addToText("\n");
    if(check==0){
        NhanVienDeTai *nvdt=searchNVDT(listNVDT,maSoNV,maSoDT);
        nvdt->vaiTro=newVaiTro;
        cout<<"Cap nhat thanh cong!";addToText("Cap nhat thanh cong!\n");
        cin.clear();
        cin.ignore();
    }else if(check==2){
        cout<<endl<<endl<<"Nhap lai! "<<endl;addToText("\nNhap lai! \n");
        cin.clear();
        cin.ignore();
        goto nhapLaiChinhSuaNVDT;
    }else if(check==1){
        addToText("Return\n");
        cin.clear();
        cin.ignore();
    }
}


//các hàm menu con trong menu chính
void menuThemDuLieu(NV &listNV,DT &listDT,NVDT &listNVDT){
    system("cls");
    const int numOptions = 4;
    string options[numOptions] = { "\t1. Nhan vien", "\t2. De tai", "\t3. Nhan vien - de tai", "\t4. Quay lai"};
    int currentOption = 0;
    char ch;
    while (true) {
        system("cls");
        string menuHeader="|        Them du lieu vao file        ";
        headerOutput(menuHeader,"|","","","","","");
        for (int i = 0; i < numOptions; ++i) {
            if (i == currentOption) {
                cout << "| --> " << options[i] ;spaceLength(menuHeader,options[i].length()+7);cout<< endl;
            } else {
                cout << "|     "<< options[i] ;spaceLength(menuHeader,options[i].length()+7);cout<< endl;
            }
        }
        headerOutLine(menuHeader,"|","","","","","");
        ch = _getch();
        switch (ch) {
            case 'w':
            case 'W':
                currentOption = (currentOption - 1 + numOptions) % numOptions;
                break;
            case 's':
            case 'S':
                currentOption = (currentOption + 1) % numOptions;
                break;
            case 13:
                addToText("\n2.1"+options[currentOption]+"\n");
                cout<<endl;
                if(currentOption==0){
                    menuThemDuLieuListNV(listNV);
                }
                else if(currentOption==1){
                   menuThemDuLieuListDT(listDT);
                }
                else if(currentOption==2){
                    menuThemDuLieuListNVDT(listNV,listDT,listNVDT);
                }
                else if(currentOption==3){
                    addToText("Return\n");
                    return;
                }
                break;
            default:
                break;
        }
    }
}
void menuXuatDuLieu(NV &listNV,DT &listDT,NVDT &listNVDT){
    system("cls");
    const int numOptions = 4;
    string options[numOptions] = { "\t1. Nhan vien", "\t2. De tai", "\t3. Nhan vien - de tai", "\t4. Quay lai"};
    int currentOption = 0;
    char ch;
    while (true) {
         system("cls");
        string menuHeader="|           Xuat du lieu           ";
        headerOutput(menuHeader,"|","","","","","");
        for (int i = 0; i < numOptions; ++i) {
            if (i == currentOption) {
                cout << "| --> " << options[i] ;spaceLength(menuHeader,options[i].length()+7);cout<< endl;
            } else {
                cout << "|     "<< options[i] ;spaceLength(menuHeader,options[i].length()+7);cout<< endl;
            }
        }
        headerOutLine(menuHeader,"|","","","","","");
        ch = _getch();
        switch (ch) {
            case 'w':
            case 'W':
                currentOption = (currentOption - 1 + numOptions) % numOptions;
                break;
            case 's':
            case 'S':
                currentOption = (currentOption + 1) % numOptions;
                break;
            case 13:
                addToText("0."+options[currentOption]+"\n");
                cout<<endl;
               if(currentOption==0){
                    XuatListNV(listNV);
                }
                else if(currentOption==1){
                    XuatListDT(listDT);
                }
                else if(currentOption==2){
                    XuatListNVDT(listNVDT);
                }
                else if(currentOption==3){
                    addToText("Return\n");
                    return;
                }
                cout<<endl<<"Nhan phim bat ki de tiep tuc!";
                -getch();
                break;
            default:
                break;
        }
    }
}
void menuXoaMotDongDuLieu(NV &listNV,DT &listDT,NVDT &listNVDT){
    system("cls");
    const int numOptions = 4;
    string options[numOptions] = { "\t1. Nhan vien", "\t2. De tai", "\t3. Nhan vien - de tai", "\t4. Quay lai"};
    int currentOption = 0;
    char ch;
    while (true) {
         system("cls");
        string menuHeader="|       Xoa mot dong du lieu cua file       ";
        headerOutput(menuHeader,"|","","","","","");
        for (int i = 0; i < numOptions; ++i) {
            if (i == currentOption) {
                cout << "| --> " << options[i] ;spaceLength(menuHeader,options[i].length()+7);cout<< endl;
            } else {
                cout << "|     "<< options[i] ;spaceLength(menuHeader,options[i].length()+7);cout<< endl;
            }
        }
        headerOutLine(menuHeader,"|","","","","","");
        ch = _getch();
        switch (ch) {
            case 'w':
            case 'W':
                currentOption = (currentOption - 1 + numOptions) % numOptions;
                break;
            case 's':
            case 'S':
                currentOption = (currentOption + 1) % numOptions;
                break;
            case 13:
                cout<<endl;
                addToText("\n2.2"+options[currentOption]+"\n");
               if(currentOption==0){
                    menuXoaDuLieuListNV(listNV,listNVDT);
                }
                else if(currentOption==1){
                    menuXoaDuLieuListDT(listDT,listNVDT);
                }
                else if(currentOption==2){
                    menuXoaDuLieuListNVDT(listNVDT,listNV,listDT);
                }
                else if(currentOption==3){
                    addToText("Return\n");
                    return;
                }
                break;
            default:
                break;
        }
    }
}
void menuChinhSuaDuLieu(NV &listNV,DT &listDT,NVDT &listNVDT){
    system("cls");
    const int numOptions = 4;
    string options[numOptions] = { "\t1. Nhan vien", "\t2. De tai", "\t3. Nhan vien - de tai", "\t4. Quay lai"};
    int currentOption = 0;
    char ch;
    while (true) {
         system("cls");
        string menuHeader="|       Chinh sua du lieu cua file       ";
        headerOutput(menuHeader,"|","","","","","");
        for (int i = 0; i < numOptions; ++i) {
            if (i == currentOption) {
                cout << "| --> " << options[i] ;spaceLength(menuHeader,options[i].length()+7);cout<< endl;
            } else {
                cout << "|     "<< options[i] ;spaceLength(menuHeader,options[i].length()+7);cout<< endl;
            }
        }
        headerOutLine(menuHeader,"|","","","","","");
        ch = _getch();
        switch (ch) {
            case 'w':
            case 'W':
                currentOption = (currentOption - 1 + numOptions) % numOptions;
                break;
            case 's':
            case 'S':
                currentOption = (currentOption + 1) % numOptions;
                break;
            case 13:
                cout<<endl;
                addToText("\n2.3"+options[currentOption]+"\n");
                if(currentOption==0){
                    menuSuaDuLieuListNV(listNV);
                }
                else if(currentOption==1){
                    menuSuaDuLieuListDT(listDT);
                }
                else if(currentOption==2){
                    menuSuaDuLieuListNVDT(listNV,listDT,listNVDT);
                }
                else if(currentOption==3){
                    addToText("Return\n");
                    return;
                }
                break;
            default:
                break;
        }
    }
}
void yeuCau3(NV &listNV,NVDT &listNVDT){
    system("cls");
    cout<<"Cho biet danh sach de tai ma nhan vien nay tham gia la thu ki/ chu nhiem."<<endl;addToText("Cho biet danh sach de tai ma nhan vien nay tham gia la thu ki/ chu nhiem.\n");
    cout<<"Nhap ma so nhan vien: ";addToText("Nhap ma so nhan vien: ");
        int maSoNV;
        // cin>>maSoNV;
        while (!(cin >> maSoNV)) {
            addToText("c\n");
            cin.clear();
            cin.ignore(1000, '\n'); 
            cout << "Ma so nhan vien khong hop le, hay nhap lai!" << endl; addToText("Ma so nhan vien khong hop le, hay nhap lai!\n" );
            cout<<"Nhap ma so nhan vien: ";addToText("Nhap ma so nhan vien: ");
        }
        addToText(to_string(maSoNV)+"\n");
        while(1){
            if(!checkNV(listNV,maSoNV)){
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Khong ton tai nhan vien co ma so "<<maSoNV<<" ! Hay kiem tra lai."<<endl; addToText("Khong ton tai nhan vien co ma so "+to_string(maSoNV)+" ! Hay kiem tra lai.\n");
                cout<<endl<<"Nhap phim bat ki de tiep tuc!";addToText("Return\n");
                getch();
                return;
            }
            if(checkNVDT_NV(listNVDT,maSoNV)){
                break;
            }
            else{
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Nhan vien co ma so "<<maSoNV<<" khong tham gia de tai nao ! Hay kiem tra lai."<<endl; addToText("Nhan vien co ma so "+to_string(maSoNV)+" khong tham gia de tai nao ! Hay kiem tra lai.\n");
                cout<<endl<<"Nhap phin bat ki de tiep tuc!";addToText("Return\n");
                getch();
                return;
            }
    }
    cout<<endl;
    int check=0;
    for(NhanVienDeTai *i=listNVDT.nvdtHead;i!=nullptr;i=i->next){
        if(i->maSoNV==maSoNV && (i->vaiTro=="Chu nhiem"|| i->vaiTro=="Thu ki")){
            check++;
        }
    }
    if(check>0){
        cout<<"Cac de tai ma nhan vien co ma so "<<maSoNV<<" tham gia co vai tro la thu ki hoac chu nhiem la: "<<endl;
        headerOutput("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
        headerOutputToText("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
        for(NhanVienDeTai *i=listNVDT.nvdtHead;i!=nullptr;i=i->next){
            if(i->maSoNV==maSoNV && (i->vaiTro=="Chu nhiem"|| i->vaiTro=="Thu ki")){
                cout<<"| "<<i->maSoNV;spaceLength("| Ma so NV ",2+intLength(i->maSoNV));
                    addToText("| "+to_string(i->maSoNV));spaceLengthToText("| Ma so NV ",2+intLength(i->maSoNV));
                cout<<" "<<i->maSoDT;spaceLength("| Ma so DT ",2+intLength(i->maSoDT));
                    addToText(" "+to_string(i->maSoDT));spaceLengthToText("| Ma so DT ",2+intLength(i->maSoDT));
                cout<<" "<<i->vaiTro;spaceLength("|   Vai tro   ",2+i->vaiTro.length());
                    addToText(" "+i->vaiTro);spaceLengthToText("|   Vai tro   ",2+i->vaiTro.length());
                cout<<endl;
                    addToText("\n");
            }
        }
        headerOutLine("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
        headerOutLineToText("| Ma so NV ","| Ma so DT ","|   Vai tro   ","","","|","");
    }else{
        cout<<"Khong co de tai nao ma nhan vien co ma so "<<maSoNV<<" tham gia co vai tro la thu ki hoac chu nhiem ! "<<endl;
        addToText("Khong co de tai nao ma nhan vien co ma so "+to_string(maSoNV)+" tham gia co vai tro la thu ki hoac chu nhiem ! \n");
    }

    cout<<endl<<"Nhap phim bat ki de tiep tuc!"; addToText("Return\n");
    getch();
    cin.clear();
    cin.ignore();
    
}
void yeuCau4(DT listDT){
    system("cls");
    cout<<"Danh sach de tai theo tung nam bat dau:"<<endl;
    addToText("Danh sach de tai theo tung nam bat dau:\n");

    sortDT_namBatDau(listDT);
    XuatListDT(listDT);
    
    //sap xep lai theo maSoDT
    // listDT= sortDT_maSoDT(listDT);
    addToText("Return\n");
    cout<<endl<<"Nhap phim bat ki de tiep tuc!";
    cin.clear();
    cin.ignore();
}
void yeuCau5(NV &listNV,DT &listDT,NVDT &listNVDT){
    system("cls");
    cout<<"Yeu cau 5!"<<endl;
    cout<<"Hien thi thi thong tin chi tiet ve de tai!"<<endl;
    cout<<endl;
    cout<<"Nhap ma so de tai: ";addToText("Nhap ma so de tai: ");
    int maSoDT;
    // cin>>maSoDT;
    while (!(cin >> maSoDT)) {
        addToText("a\n");
        cin.clear();
        cin.ignore(1000, '\n'); 
        cout << "Ma so de tai khong hop le, hay nhap lai!" << endl; addToText("Ma so de tai khong hop le, hay nhap lai!\n");
        cout<<"Nhap ma so de tai: ";addToText("Nhap ma so de tai: ");
    }
    addToText(to_string(maSoDT)+"\n");
    if(!checkDT(listDT,maSoDT)){
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Khong ton tai de tai co ma so "<<maSoDT<<" ! Hay kiem tra lai."<<endl; addToText("Khong ton tai de tai co ma so "+to_string(maSoDT)+" ! Hay kiem tra lai.\n");
        cout<<endl<<"Nhap phim bat ki de tiep tuc!";addToText("Return\n");
        getch();
        return;
    }
    DeTai *dt=searchDT(listDT,maSoDT);
    NhanVien *nv;
    string chuNhiem="";
    string thuKi="";
    int soThanhVien=0;
    for(NhanVienDeTai *i=listNVDT.nvdtHead;i!=nullptr;i=i->next){
        if(i->maSoDT==dt->maSoDT && (i->vaiTro=="Chu nhiem" || i->vaiTro=="Thu ki")){
            nv=searchNV(listNV,i->maSoNV);
            if(i->vaiTro=="Chu nhiem"){
                chuNhiem=to_string(nv->maSoNV)+"-"+ nv->hoDem+" "+nv->ten;
            }
            if(i->vaiTro=="Thu ki"){
                thuKi=to_string(nv->maSoNV)+"-"+nv->hoDem+" "+nv->ten;
            }
        }
        if(i->maSoDT==dt->maSoDT && i->vaiTro=="Thanh vien"){
                soThanhVien++;
        }
    }
    if(chuNhiem==""){
        chuNhiem="Khong co";
    }
    if(thuKi==""){
        thuKi="Khong co";
    }
    cout<<endl<<"Thong tin chi tiet cua de tai "<<maSoDT<<" :"<<endl; addToText("Thong tin chi tiet cua de tai "+to_string(maSoDT)+" :\n");
    headerOutput("|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|            Chu nhiem            ","|            Thu ki            ","|");
    headerOutputToText("|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|            Chu nhiem            ","|            Thu ki            ","|");
    string kinhPhi=to_string(dt->kinhPhi);
    cout<<"| "<<dt->tenDeTai;spaceLength("|    Ten de tai    ",2+dt->tenDeTai.length());
    addToText("| "+dt->tenDeTai);spaceLengthToText("|    Ten de tai    ",2+dt->tenDeTai.length());
    cout<<" "<<dt->namBatDau;spaceLength("| Nam bat dau ",2+intLength(dt->namBatDau));
    addToText(" "+to_string(dt->namBatDau));spaceLengthToText("| Nam bat dau ",2+intLength(dt->namBatDau));
    cout<<" "<<dt->namKetThuc;spaceLength("| Nam ket thuc ",2+intLength(dt->namKetThuc));
    addToText(" "+to_string(dt->namKetThuc));spaceLengthToText("| Nam ket thuc ",2+intLength(dt->namKetThuc));
    cout<<" "<<kinhPhi;spaceLength("|        Kinh phi        ",2+kinhPhi.length());	
    addToText(" "+kinhPhi);spaceLengthToText("|        Kinh phi        ",2+kinhPhi.length());
    cout<<" "<<chuNhiem;spaceLength("|            Chu nhiem            ",2+chuNhiem.length());
    addToText(" "+chuNhiem);spaceLengthToText("|            Chu nhiem            ",2+chuNhiem.length());
    cout<<" "<<thuKi;spaceLength("|            Thu ki            ",2+thuKi.length());
    addToText(" "+thuKi);spaceLengthToText("|            Thu ki            ",2+thuKi.length());
    cout<<endl;
    addToText("\n");
    headerOutLine("|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|            Chu nhiem            ","|            Thu ki            ","|");
    headerOutLineToText("|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|            Chu nhiem            ","|            Thu ki            ","|");

    cout<<endl<<endl;
    if(soThanhVien==0){
        cout<<"De tai "<<maSoDT<<" Khong co thanh vien nao!";
        addToText("De tai "+to_string(maSoDT)+" Khong co thanh vien nao!");
    }
    else{
        cout<<"Danh sach thanh vien cua de tai "<<maSoDT<<" :"<<endl; addToText("\nDanh sach thanh vien cua de tai "+to_string(maSoDT)+" :\n");
        headerOutput("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
        headerOutputToText("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
        for(NhanVienDeTai *i=listNVDT.nvdtHead;i!=nullptr;i=i->next){
            if(i->maSoDT==dt->maSoDT && i->vaiTro=="Thanh vien"){
                nv=searchNV(listNV,i->maSoNV);

                cout<<"| "<<nv->maSoNV;spaceLength("| Ma so NV ",2+intLength(nv->maSoNV));
                addToText("| "+to_string(nv->maSoNV));spaceLengthToText("| Ma so NV ",2+intLength(nv->maSoNV));
                cout<<" "<<nv->hoDem;spaceLength("|    Ho ten dem    ",2+nv->hoDem.length());
                addToText(" "+nv->hoDem);spaceLengthToText("|    Ho ten dem    ",2+nv->hoDem.length());
                cout<<" "<<nv->ten;spaceLength("|   Ten   ",2+nv->ten.length());
                addToText(" "+nv->ten);spaceLengthToText("|   Ten   ",2+nv->ten.length());
                cout<<" "<<nv->gen;spaceLength("|  Gioi tinh  ",2+nv->gen.length());
                addToText(" "+nv->gen);spaceLengthToText("|  Gioi tinh  ",2+nv->gen.length());
                cout<<" "<<nv->birthDay;spaceLength("|     Ngay sinh     ",2+nv->birthDay.length());	
                addToText(" "+nv->birthDay);spaceLengthToText("|     Ngay sinh     ",2+nv->birthDay.length());
                cout<<endl;addToText("\n");
            }
            if(i==listNVDT.nvdtTail){
                headerOutLine("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
                headerOutLineToText("| Ma so NV ","|    Ho ten dem    ","|   Ten   ","|  Gioi tinh  ","|     Ngay sinh     ","|","");
            }
        }
    }
    cout<<endl<<endl;
    cout<<"Nhap phim bat ki de quay lai!"; addToText("Return\n");
    getch();
    cin.clear();
    cin.ignore();
}
void yeuCau6(NV &listNV,DT &listDT,NVDT &listNVDT){
    system("cls");
    cout<<"Tinh tong kinh phi cua tat ca de tai trong 1 nam."<<endl;
    cout<<"Nhap vao nam: "; addToText("Nhap vao nam: ");
    int namBatDau;
    while (!(cin >> namBatDau)|| namBatDau >2023 || namBatDau<1000) {
        addToText(to_string(namBatDau)+"\n");
        cin.clear();
        cin.ignore(1000, '\n'); 
        cout << "Nam bat dau khong hop le, hay nhap lai!" << endl; addToText("Nam bat dau khong hop le, hay nhap lai!\n");
        cout << "Nam bat dau: "; addToText("Nam bat dau: ");
    }
    addToText(to_string(namBatDau)+"\n");
    //Kiểm tra xem có đề tài nào bắt đầu trong năm đó không
    bool checkNamBatDau;
    for(DeTai *i=listDT.dtHead;i!=nullptr;i=i->next){
        if(i->namBatDau==namBatDau){
            checkNamBatDau=true;
            break;
        }else{
            checkNamBatDau=false;
        }
    }

    //in ket qua
    if(!checkNamBatDau){
        cout<<"Khong co de tai nao bat dau trong nam "<<namBatDau<<". "<<endl; addToText("Khong co de tai nao bat dau trong nam "+to_string(namBatDau)+". \n");
        cout<<endl<<"Nhap phim bat ki de tiep tuc."; addToText("Return\n");
        getch();
        cin.clear();
        cin.ignore();
        return;
    }
    int sumKinhPhi=0;
    cout<<endl<<"Danh sach de tai bat dau trong nam "<<namBatDau<<" :"<<endl; addToText("Danh sach de tai bat dau trong nam "+to_string(namBatDau)+" :\n");
    headerOutput("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
    headerOutputToText("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
    for(DeTai *i=listDT.dtHead;i!=NULL;i=i->next){
        if(i->namBatDau==namBatDau){
            string kinhPhi=to_string(i->kinhPhi);
            cout<<"| "<<i->maSoDT;spaceLength("| Ma so DT ",2+intLength(i->maSoDT));
                addToText("| "+ to_string(i->maSoDT) );spaceLengthToText("| Ma so DT ",2+intLength(i->maSoDT));
            cout<<" "<<i->tenDeTai;spaceLength("|    Ten de tai    ",2+i->tenDeTai.length());
                addToText(" "+i->tenDeTai);spaceLengthToText("|    Ten de tai    ",2+i->tenDeTai.length());
            cout<<" "<<i->namBatDau;spaceLength("| Nam bat dau ",2+intLength(i->namBatDau));
                addToText(" "+to_string(i->namBatDau));spaceLengthToText("| Nam bat dau ",2+intLength(i->namBatDau));
            cout<<" "<<i->namKetThuc;spaceLength("| Nam ket thuc ",2+intLength(i->namKetThuc));
                addToText(" "+to_string(i->namKetThuc));spaceLengthToText("| Nam ket thuc ",2+intLength(i->namKetThuc));
            cout<<" "<<kinhPhi;spaceLength("|        Kinh phi        ",2+kinhPhi.length());	
                addToText(" "+kinhPhi);spaceLengthToText("|        Kinh phi        ",2+kinhPhi.length());
            cout<<endl;
                addToText("\n");
            sumKinhPhi+=i->kinhPhi;
        }
        if(i==listDT.dtTail){
            headerOutLine("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
            headerOutLineToText("| Ma so DT ","|    Ten de tai    ","| Nam bat dau ","| Nam ket thuc ","|        Kinh phi        ","|","");
        }
    }
    cout<<"Tong kinh phi cua nhung de tai bat dau nam "<<namBatDau<<" la: "<<sumKinhPhi; addToText("Tong kinh phi cua nhung de tai bat dau nam "+to_string(namBatDau)+" la: "+to_string(sumKinhPhi));
    cout<<endl;
    cout<<endl<<"Nhap phim bat ki de tiep tuc."; addToText("\nReturn\n");
    getch();
    cin.clear();
    cin.ignore();
}

// Hàm menu chính
void menu(NV &listNV,DT &listDT,NVDT &listNVDT){
    //Kiểm tra nếu chưa có file thì tạo, nếu có rồi thì load dữ liệu của file vào danh sách
    if(fileExists("NV.bin")){
        loadListNvFromFile(listNV,"NV.bin");
    }else{
        ofstream file("NV.bin", ios::binary);
        file.close();
    }

    if(fileExists("DT.bin")){
        loadListDtFromFile(listDT,"DT.bin");
    }else{
        ofstream file("DT.bin", ios::binary);
        file.close();
    }

    if(fileExists("NVDT.bin")){
        loadListNvdtFromFile(listNVDT,"NVDT.bin");
    }else{
        ofstream file("NVDT.bin", ios::binary);
        file.close();
    }

    addToText("\n=========================== BAT DAU ==============================\n");
    
    const int numOptions = 10;
    string options[numOptions] = {  "0.  Xuat danh sach",                       //currentOption=0
                                    "1.  Luu danh sach vao file",            //currentOption=1    
                                    "2.1 Them du lieu vao danh sach",           //currentOption=2
                                    "2.2 Xoa du lieu cua danh sach",         //currentOption=3
                                    "2.3 Chinh sua du lieu cua danh sach",      //currentOption=4
                                    "3.  Yeu cau 3",                         //currentOption=5
                                    "4.  Xuat danh sach de tai theo tung nam bat dau",
                                    "5.  Xem chi tiet thong tin de tai",
                                    "6.  Tinh tong kinh phi cua nhung de tai trong 1 nam",
                                    "7.  Dong menu"};   
    int currentOption = 0;
    char ch;
	while(1){
		system("cls");
        // cout<<"============= DE TAI 2 ============="<<endl;
        string menuHeader="|                             MENU                             ";
        headerOutput(menuHeader,"|","","","","","");
        for (int i = 0; i < numOptions; ++i) {
            if (i == currentOption) {
                cout << "| --> " << options[i] ;spaceLength(menuHeader,options[i].length()+6);cout<< endl;
            } else {
                cout << "|     "<< options[i] ;spaceLength(menuHeader,options[i].length()+6);cout<< endl;
            }
        }
        headerOutLine(menuHeader,"|","","","","","");
        cout<<endl<<"======== Dieu khien ========"<<endl;
        cout<<"  W:   len tren"<<endl;
        cout<<"  S:   xuong duoi"<<endl;
        cout<<"  A:   sang trai"<<endl;
        cout<<"  D:   sang phai"<<endl;
        cout<<"Enter: chon"<<endl;
        ch = _getch();
        switch (ch) {
            case 'w':
            case 'W':
                // Di chuyển lên
                currentOption = (currentOption - 1 + numOptions) % numOptions;
                break;
            case 's':
            case 'S':
                // Di chuyển xuống
                currentOption = (currentOption + 1) % numOptions;
                break;
            case 13:
                addToText("\n"+options[currentOption]+":\n");
                if(currentOption==0){
                    menuXuatDuLieu(listNV,listDT,listNVDT);
                }
                else if(currentOption==1){
                    system("cls");
                    int x1=saveListNvToFile(listNV,"NV.bin");
                    int x2=saveListDtToFile(listDT,"DT.bin");
                    int x3=saveListNvdtToFile(listNVDT,"NVDT.bin");
                    if(x1==1|| x2==1 || x3==1){
                        cout<<"Luu file that bai ! ";
                        addToText("\tLuu file that bai ! \n");
                    }else{
                        cout<<"Luu file thanh cong!"<<endl;
                        addToText("\tLuu file thanh cong!\n");
                    }
                    cout<<endl<<"Nhap phim bat ki de quay lai!";
                    _getch();
                }
                else if(currentOption==2){
                    menuThemDuLieu(listNV,listDT,listNVDT);
                }
                else if(currentOption==3){
                    menuXoaMotDongDuLieu(listNV,listDT,listNVDT);
                }
                else if(currentOption==4){
                    menuChinhSuaDuLieu(listNV,listDT,listNVDT);
                }
                else if(currentOption==5){
                    yeuCau3(listNV,listNVDT);
                }
                else if(currentOption==6){
                    yeuCau4(listDT);
                }
                else if(currentOption==7){
                    yeuCau5(listNV,listDT,listNVDT);
                }
                else if(currentOption==8){
                    yeuCau6(listNV,listDT,listNVDT);
                }
                else if(currentOption==9){
                    addToText("\n=========================== KET THUC ==============================\n\n");
                    return;
                }
                break;
            case 27: // Phím ESC
                break;
            default:
                break;
        }
	}
}
