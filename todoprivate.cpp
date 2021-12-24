
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

fstream myfile;
fstream ki;

bool postojeci = false;

string sq, sqa;
string prijavljen = "Ne";
string ime;
string korime7;
string mail;

void korekcijateksta(string txtfile){
    string recenica, interpunkcija = ".,!?:;", interpunkcijaRecenica, velikaSlova = ".!?", vasTekst, preRazmaka = "-+*/";
    system("cls");
    myfile.open(txtfile, ios :: in);
    ki.open("temp.txt", ios :: out);
    int z = 0;
    while(getline(myfile, recenica)){
        if (recenica[0] >= 'a' && recenica[0] <= 'z') recenica[0] = recenica[0] - 32; // Prvo veliko slovo proverava i ispravlja.
        for (int i = 0; i < recenica.length(); i++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (recenica[i] == velikaSlova[k])
                {
                    if (recenica[i + 1] >= 'a' && recenica[i + 1] <= 'z') recenica[i + 1] = recenica[i + 1] - 32; // Posle tacke, upitnika i uzvicnika veliko slovo ispravlja.
                    if (recenica[i + 2] >= 'a' && recenica[i + 2] <= 'z' && recenica[i + 1] == ' ') recenica[i + 2] = recenica[i + 2] - 32; // Posle tacke, upitnika i uzvicnika i razmaka ako ima veliko slovo ispravlja.
                }
            }
            char c = recenica[i];
            if (preRazmaka.find(c) != -1 && i + 1 < recenica.length() && recenica[i + 1] != ' ' && recenica [i - 1] != ' ') interpunkcijaRecenica = interpunkcijaRecenica + ' ' + c + ' '; // Pre razmak i posle
            else if (preRazmaka.find(c) != -1 && i + 1 < recenica.length() && recenica[i + 1] != ' ') interpunkcijaRecenica = interpunkcijaRecenica + c + ' '; // Posle razmak
            else if (preRazmaka.find(c) != -1 && i + 1 < recenica.length() && recenica[i - 1] != ' ') interpunkcijaRecenica = interpunkcijaRecenica + ' ' + c; // Pre razmak
            else if (interpunkcija.find(c) != -1 && i + 1 < recenica.length() && recenica[i + 1] != ' ') interpunkcijaRecenica = interpunkcijaRecenica + c + ' '; // Razmaci posle znakova interpunkcije.
            else interpunkcijaRecenica = interpunkcijaRecenica + c;
        }
        recenica = interpunkcijaRecenica;
        interpunkcijaRecenica = "";
        if (recenica[recenica.length() - 1] == ',') recenica.replace(recenica.length() - 1, 1,  "."); // Ako ima zarez umesto tacke na kraju teksta, zamenice je.
        ki << recenica; 
        if (recenica[recenica.length() - 1] != '.' && recenica[recenica.length() - 1] != '!' && recenica[recenica.length() - 1] != '?') ki << '.'; // Dodaje tacku na kraju reda ako je to potrebno.
        ki << endl;
    }
    myfile.close();
    ki.close();
    myfile.open(txtfile, ios::out);
    ki.open("temp.txt", ios::in);
    if (myfile.is_open() && ki.is_open()){
        string linija;
        while (getline(ki, linija)){
            myfile << linija << endl;
        }
        myfile.close();
        ki.close();
    }
    if (prijavljen != "Da" || prijavljen != "da" || prijavljen != "dA" || prijavljen != "DA"){
        cout << "==========================================================================" << endl; 
        cout << "\t\tLista nakon ispravljanja." << endl;
        cout << "==========================================================================" << endl; 
    }
    else{
        cout << "==========================================================================" << endl; 
        cout << "\t\tPrivatna lista nakon ispravljanja." << endl;
        cout << "==========================================================================" << endl; 
    }
    myfile.open(txtfile, ios::in); //citanje je in
    if (myfile.is_open()){
        string linija;
        while (getline(myfile, linija)){
            cout << linija << endl;
        }
        myfile.close();
    }
}

void registracijaLozinkaProvera(){
    bool trajanje = true;
    while (trajanje){
        string lozinka;
        int greska;
        char karakteri[26] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')','-', '_', '+', '=', '/','?', '|', '<', '>', ':', ';','-', '`','~',' '};
        char brojevi [10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
        bool karakteriBool = false, velikaSlova = false, brojeviBool = false;
        cout << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
        cout << "Unesite lozinku: "; 
        getline(cin,lozinka);
        cout << endl;
        for (int i = 0; i < lozinka.length(); i++){
            for (int j = 0; j < 26; j++){
                if (lozinka[i] == karakteri[j]) {
                    karakteriBool = true;
                    break;
                }
            }
        }
        for (int i = 0; i < lozinka.length(); i++){
            for (int j = 0; j < 10; j++){
                if (lozinka[i] == brojevi[j]) {
                    brojeviBool = true;
                    break;
                }
            }
        }
        for (int i = 0; i < lozinka.length(); i++){
            if (lozinka[i] >= 'A' && lozinka[i] <= 'Z') {
                velikaSlova = true;
                break;
            }
        }
        if (lozinka.length() >= 6 && lozinka.length() <= 14 && karakteriBool && velikaSlova && brojeviBool){
            system("cls");
            cout << "==========================================================================" << endl;            
            cout << "\t\t\tUspesno ste se registrovali." << endl;
            cout << "==========================================================================" << endl;
            trajanje = false;
            cout << endl;
            ki << lozinka << endl;
        }
        else {
            if (lozinka.length() < 6){
                system("cls");
                greska = 6 - lozinka.length();
                cout << "==========================================================================" << endl;                
                cout << "Vasa lozinka je kratka za: " << greska << " karaktera, pokusajte ponovo." << endl;
                cout << "==========================================================================" << endl;
            }
            else if (lozinka.length() > 14){
                system("cls");
                greska = lozinka.length() - 14;
                cout << "==========================================================================" << endl;              
                cout << "Vasa lozinka je presla: " << greska << " karaktera, pokusajte ponovo." << endl;
                cout << "==========================================================================" << endl;
            }
            else if (!karakteriBool){
                system("cls");
                cout << "==========================================================================" << endl;              
                cout << "Nemate dovoljno specijalnih karaktera u lozinki, pokusajte ponovo." << endl;
                cout << "==========================================================================" << endl;
            }
            else if (!velikaSlova){
                system("cls");
                cout << "==========================================================================" << endl;               
                cout << "Nemate dovoljno velikih slova  u lozinki, pokusajte ponovo." << endl;
                cout << "==========================================================================" << endl;                
            }
            else{
                system("cls");
                cout << "==========================================================================" << endl;                
                cout << "Nemate dovoljno brojeva u lozinki, pokusajte ponovo." << endl;
                cout << "==========================================================================" << endl;
            }
        }
    }
}

void registracijaMailProvera(){
    while(1){
        bool prviChar = false, et = false, mailserver = false, domen = false;
        cout << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl; 
        cout << "Unesite email adresu: ";
        cin >> mail;
        if (mail[0] >= 'a' && mail[0] <= 'z' || mail[0] >= 'A' && mail[0] <= 'Z') prviChar = true; // proveravam prvi karakter da li je slovo
        for (int i = 0; i < mail.length(); i++){ // prolazim kroz string da vidim da li ima @
            if (mail[i] == '@'){
                et = true;
            for (int k = 0; k < mail.length() - i; k++){ // prolazi kroz deo maila posle @
                if (mail[k + i] == '.'){ // nalazi tacku, proverava da li je ima
                    mailserver = true;
                    if (k + i + 1 < mail.length()){ // ako je mesto tacke posle @ manje od duizine maila, znaci da posle toga postoji neki tekst
                        domen = true;
                        break;
                    }
                }
            }
            }
        }
        if (prviChar && et && mailserver && domen){
            myfile.open("mailovi.txt",ios::in);
            if (myfile.is_open()){
                string linija2;
                while (getline(myfile, linija2)){
                    if (linija2 == mail)
                        postojeci = true;
                }
                myfile.close();
            }
            ki.open(ime, ios::app);
            myfile.open("mailovi.txt",ios::app);
            if (myfile.is_open() && ki.is_open()) {
                if (postojeci) {
                    system("cls");
                    cout << "==========================================================================" << endl; 
                    cout << "\t\tNalog sa tom adresom vec postoji u bazi." << endl;
                    cout << "==========================================================================" << endl; 
                }
                else {
                    myfile << mail << endl;
                    ki << mail << endl;
                    myfile.close();
                    cin.ignore();
                    registracijaLozinkaProvera();
                    ki << sq << endl;
                    ki << sqa << endl;
                    ki.close();
                }
            }
            break;
        }
        else if (!prviChar){
            system("cls");
            cout << "==========================================================================" << endl; 
            cout << "\t\tPrvi karakter mora biti slovo." << endl;
            cout << "==========================================================================" << endl; 
        }
        else if (!et){
            system("cls");
            cout << "==========================================================================" << endl; 
            cout << "\t\tNemate '@' u mailu." << endl;
            cout << "==========================================================================" << endl; 
        }
        else if (!mailserver){
            system("cls");
            cout << "==========================================================================" << endl; 
            cout << "\t\tNemate mail server." << endl;
            cout << "==========================================================================" << endl; 
        }
        else if (!domen){
            system("cls");
            cout << "==========================================================================" << endl; 
            cout << "\t\tNemate domen u mailu." << endl;
            cout << "==========================================================================" << endl; 
        }
    }
}

void registracijaLozinkaProveraReset(){
    bool trajanje = true;
    while (trajanje){
        string lozinka;
        int greska;
        char karakteri[26] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')','-', '_', '+', '=', '/','?', '|', '<', '>', ':', ';','-', '`','~',' '};
        char brojevi [10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
        bool karakteriBool = false, velikaSlova = false, brojeviBool = false;
        cout << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl; 
        cout << "Unesite vasu novu lozinku: ";
        getline(cin,lozinka);
        cout << endl;
        myfile.open(korime7, ios::in);
        string istaloz;
        int c = 0;
        bool isloz = false;
        while(getline(myfile, istaloz)){
            if (c == 1 && istaloz == lozinka){
                isloz = true;
                myfile.close();
                break;
            }
            else c++;
            if (c == 2) {
                myfile.close();
                break;
            }
        }
        for (int i = 0; i < lozinka.length(); i++){
            for (int j = 0; j < 26; j++){
                if (lozinka[i] == karakteri[j]) {
                    karakteriBool = true;
                    break;
                }
            }
        }
        for (int i = 0; i < lozinka.length(); i++){
            for (int j = 0; j < 10; j++){
                if (lozinka[i] == brojevi[j]) {
                    brojeviBool = true;
                    break;
                }
            }
        }
        for (int i = 0; i < lozinka.length(); i++){
            if (lozinka[i] >= 'A' && lozinka[i] <= 'Z') {
                velikaSlova = true;
                break;
            }
        }
        if (lozinka.length() >= 6 && lozinka.length() <= 14 && karakteriBool && velikaSlova && brojeviBool && !isloz){
            fstream temp;
            myfile.open(korime7, ios::in);
            temp.open("temp.txt", ios::out);
            if (myfile.is_open()){
                string linija;
                int i = 0;
                while (getline(myfile, linija)) {
                    if (i != 1){
                        temp << linija << endl;
                        i++;
                    }
                    else {
                        temp << lozinka << endl;
                        i++;
                    }
                }
                myfile.close();
                temp.close();
            }
            myfile.open(korime7, ios::out);
            temp.open("temp.txt", ios::in);
            if (myfile.is_open()){
                string linija;
                while (getline(temp, linija)){
                    myfile << linija << endl;
                }
                myfile.close();
                temp.close();
            }
            system("cls");
            cout << "==========================================================================" << endl; 
            cout << "\t\t\tLozinka je uspesno izmenjena." << endl;
            cout << "==========================================================================" << endl; 
            trajanje = false;
        }
        else {
            if (isloz){
                system("cls");
                cout << "==========================================================================" << endl; 
                cout << "\t\tNova lozinka ne moze biti ista." << endl;
                cout << "==========================================================================" << endl; 
            }
            else if (lozinka.length() < 6){
                system("cls");
                greska = 6 - lozinka.length();
                cout << "==========================================================================" << endl;                
                cout << "Vasa lozinka je kratka za: " << greska << " karaktera, pokusajte ponovo." << endl;
                cout << "==========================================================================" << endl;
            }
            else if (lozinka.length() > 14){
                system("cls");
                greska = lozinka.length() - 14;
                cout << "==========================================================================" << endl;              
                cout << "Vasa lozinka je presla: " << greska << " karaktera, pokusajte ponovo." << endl;
                cout << "==========================================================================" << endl;
            }
            else if (!karakteriBool){
                system("cls");
                cout << "==========================================================================" << endl;              
                cout << "Nemate dovoljno specijalnih karaktera u lozinki, pokusajte ponovo." << endl;
                cout << "==========================================================================" << endl;
            }
            else if (!velikaSlova){
                system("cls");
                cout << "==========================================================================" << endl;               
                cout << "Nemate dovoljno velikih slova  u lozinki, pokusajte ponovo." << endl;
                cout << "==========================================================================" << endl;                
            }
            else{
                system("cls");
                cout << "==========================================================================" << endl;                
                cout << "Nemate dovoljno brojeva u lozinki, pokusajte ponovo." << endl;
                cout << "==========================================================================" << endl;
            }
        }
    }
}

int main(){
    string trajanje = "Da";
    while (trajanje == "Da" || trajanje == "da" || trajanje == "dA" || trajanje == "DA"){
        system("cls");
        int izbor;
        string unos;
        cout << "==========================================================================" << endl; 
        cout << "\t\tUnesite 1 za unos u TODO listu." << endl;
        cout << "\t\tUnesite 2 za prikaz TODO liste." << endl;
        cout << "\t\tUnesite 3 za registraciju." << endl;
        cout << "\t\tUnesite 4 za prijavljivanje." << endl;
        cout << "\t\tUnesite 5 za brisanje cele TODO liste." << endl;
        cout << "\t\tUnesite 6 za brisanje 1 linije TODO liste." << endl;
        cout << "\t\tUnesite 7 ako ste zaboravili sifru." << endl;
        cout << "\t\tUnesite 8 da korigujete tekst TODO liste." << endl;
        cout << "==========================================================================" << endl; 
        cin >> izbor;
        switch (izbor) {
            case 1: {
                system("cls");
                cin.ignore();
                cout << "==========================================================================" << endl; 
                cout << "\t\t\tUnesite dodatak" << endl;
                cout << "==========================================================================" << endl; 
                getline(cin, unos);
                myfile.open("lista.txt", ios::app); //write je ios::out, a za dodavanje je ovo ios::app
                if (myfile.is_open()){
                    myfile << unos << endl;
                    myfile.close();
                    system("cls");
                    cout << "==========================================================================" << endl; 
                    cout << "\t\t\tUspesno dodato" << endl;
                    cout << "==========================================================================" << endl; 
                }
                break;
            }
            case 2: {
                system("cls");
                cout << "==========================================================================" << endl; 
                cout << "\t\t\tVasa TODO lista" << endl;
                cout << "==========================================================================" << endl; 
                myfile.open("lista.txt", ios::in); //citanje je in
                if (myfile.is_open()){
                    string linija;
                    while (getline(myfile, linija)){
                        cout << linija << endl;
                    }
                    myfile.close();
                }
                break;
            }
            case 3: {
                system("cls");
                bool sqnjsqa = true;
                cin.ignore();
                cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl; 
                cout << "Unesite korisnicko ime: ";
                getline(cin, ime);
                cout << endl;
                ime.append(".txt");
                ki.open(ime, ios::in);
                if (ki.is_open()){
                    system("cls");
                    cout << "==========================================================================" << endl; 
                    cout << "\t\tNalog sa tim imenom vec postoji u bazi." << endl;
                    cout << "==========================================================================" << endl; 
                    break;
                }
                ki.close();
                while(sqnjsqa){
                    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl; 
                    cout << "Unesite sigurnostno pitanje (CASE SENSITIVE JE): ";
                    getline(cin, sq);
                    cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl; 
                    cout << "Unesite odgovor na sigurnostno pitanje: ";
                    getline(cin, sqa);
                    if (sqa == sq){
                        system("cls");
                        cout << "==========================================================================" << endl; 
                        cout << "\tSigurnostno pitanje ne moze da bude isto kao i odgovor !" << endl;
                        cout << "==========================================================================" << endl; 
                    }
                    else{
                        sqnjsqa = false;
                    }
                }
                registracijaMailProvera();
                break;
            }
            case 4: {
                cin.ignore();
                system("cls");
                bool prijavaLoz = false, prijavaMail = false;
                string mailLog;
                cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl; 
                cout << "Unesite korisnicko ime: ";
                getline(cin, ime);
                ime.append(".txt");
                cout << endl;
                ki.open(ime, ios::in);
                if (!ki.is_open()){
                    system("cls");
                    cout << "==========================================================================" << endl; 
                    cout << "\t\tNalog sa tim imenom  ne postoji u bazi." << endl;
                    cout << "==========================================================================" << endl; 
                    break;
                }
                ki.close();
                while (!prijavaMail){
                    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl; 
                    cout << "Unesite mail: ";
                    cin >> mailLog;
                    myfile.open(ime, ios::in);
                    if (myfile.is_open()){
                        string linija3;
                        int i = 0;
                        while (getline(myfile, linija3)){
                            if (linija3 == mailLog){
                                prijavaMail = true;
                                break;
                            }
                            if (i == 1)
                                break;
                            i++;
                        }
                    }
                    if (!prijavaMail){
                        system("cls");
                        cout << "==========================================================================" << endl; 
                        cout << "\t\tNalog sa tom adresom ne odgovara korisnickom imenu." << endl;
                        cout << "==========================================================================" << endl; 
                        break;
                    }
                }
                while (!prijavaLoz){
                    myfile.close();
                    string lozLog;
                    cin.ignore();
                    cout << endl;
                    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl; 
                    cout << "Unesite lozinku: ";
                    getline(cin, lozLog);
                    myfile.open(ime, ios::in);
                    if (myfile.is_open()){
                        string linija4;
                        int i = 0;
                        while (getline(myfile, linija4)){
                            if (linija4 == lozLog && i == 1){
                                prijavaLoz = true;
                                break;
                            }
                            i++;
                        }
                    }
                    if (!prijavaLoz){
                        system("cls");
                        cout << "==========================================================================" << endl; 
                        cout << "\t\tLozinka se ne poklapa sa mail adresom." << endl;
                        cout << "==========================================================================" << endl; 
                        break;
                    }
                    else{
                        myfile.close();
                        prijavljen = "Da";
                        while (prijavljen == "Da" || prijavljen == "da" || prijavljen == "dA" || prijavljen == "DA"){
                            int izborpriv;
                            system("cls");
                            cout << "==========================================================================" << endl; 
                            cout << "\t\t\tPrijavljeni ste." << endl;
                            cout << "==========================================================================" << endl;
                            cout << endl;
                            cout << "==========================================================================" << endl; 
                            cout << "\t\tUnesite 1 za unos u privatnu TODO listu." << endl;
                            cout << "\t\tUnesite 2 za prikaz privatne TODO liste." << endl;
                            cout << "\t\tUnesite 3 za brisanje cele privatne TODO liste." << endl;
                            cout << "\t\tUnesite 4 za brisanje 1 linije TODO liste." << endl;
                            cout << "\t\tUnesite 5 da korigujete tekst privatne TODO liste." << endl;
                            cout << "==========================================================================" << endl; 
                            cin >> izborpriv;
                            string priv = "Privatna Od ";
                            priv.append(ime);
                            switch (izborpriv){
                                case 1: {
                                    system("cls");
                                    cin.ignore();
                                    cout << "==========================================================================" << endl; 
                                    cout << "\t\tUnesite dodatak za privatnu listu" << endl;
                                    cout << "==========================================================================" << endl; 
                                    getline(cin, unos);
                                    myfile.open(priv, ios::app);
                                    if (myfile.is_open()){
                                        myfile << unos << endl;
                                        myfile.close();
                                    }
                                    break;
                                }
                                case 2: {
                                    system("cls");
                                    cout << "==========================================================================" << endl; 
                                    cout << "\t\t\tVasa privatna TODO lista" << endl;
                                    cout << "==========================================================================" << endl; 
                                    myfile.open(priv, ios::in);
                                    if (myfile.is_open()){
                                        string linija;
                                        while (getline(myfile, linija)){
                                            cout << linija << endl;
                                        }
                                        myfile.close();
                                    }
                                    break;
                                }
                                case 3: {
                                    myfile.open(priv, ios::out);
                                    if (myfile.is_open()){
                                        myfile.close();
                                    }
                                    system("cls");
                                    cout << "==========================================================================" << endl; 
                                    cout << "\t\t\tPrivatna lista uspesno izbrisana." << endl;
                                    cout << "==========================================================================" << endl; 
                                    break;
                                }
                                case 4: {
                                    system("cls");
                                    myfile.open(priv, ios::in);
                                    if (myfile.is_open()){
                                        string linija;
                                        int i = 0;
                                        while (getline(myfile, linija)){
                                            cout << i << ". " << linija << endl;
                                            i++;
                                        }
                                        myfile.close();
                                        if (i == 0){
                                            system("cls");
                                            cout << "==========================================================================" << endl; 
                                            cout << "\t\tGreska, vasa privatna TODO lista je prazna." << endl;
                                            cout << "==========================================================================" << endl; 
                                            break;
                                        }
                                    }
                                    int rbr;
                                    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl; 
                                    cout << "\tUnesite redni broj linije koju zelite da izbrisete: ";
                                    cin >> rbr;
                                    cout << endl;
                                    fstream temp;
                                    myfile.open(priv, ios::in);
                                    temp.open("temp.txt", ios::out);
                                    if (myfile.is_open()){
                                        string linija;
                                        int i = 0;
                                        while (getline(myfile, linija)){
                                            if (rbr != i){
                                                temp << linija << endl;
                                                i++;
                                            }
                                            else {
                                                i++;
                                                continue;
                                            }
                                        }
                                        myfile.close();
                                        temp.close();
                                    }
                                    myfile.open(priv, ios::out);
                                    temp.open("temp.txt", ios::in);
                                    if (myfile.is_open()){
                                        string linija;
                                        while (getline(temp, linija)){
                                            myfile << linija << endl;
                                        }
                                        myfile.close();
                                        temp.close();
                                    }
                                    system("cls");
                                    cout << "==========================================================================" << endl; 
                                    cout << "\t\t\tVasa privatna TODO lista" << endl;
                                    cout << "==========================================================================" << endl; 
                                    myfile.open(priv, ios::in);
                                    if (myfile.is_open()){
                                        string linija;
                                        int i = 0;
                                        while (getline(myfile, linija)) {
                                            cout << linija << endl;
                                            i++;
                                        }
                                        myfile.close();
                                    }
                                    break;
                                }
                                case 5: {
                                    korekcijateksta(priv);
                                    break;
                                }
                                default: {
                                    system("cls");
                                    cout << "==========================================================================" << endl; 
                                    cout << "\t\t\tNeispravan unos." << endl;
                                    cout << "==========================================================================" << endl; 
                                }
                            }
                            cout << endl;
                            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl; 
                            cout << "Da li zelite da nastavite rad sa programom prijavljeni, Da/Ne: "; 
                            cin >> prijavljen;
                            cout << endl;
                        }
                    }
                }
                break;
            }
            case 5: {
                myfile.open("lista.txt", ios::out);
                if (myfile.is_open()){
                    myfile.close();
                }
                system("cls");
                cout << "==========================================================================" << endl; 
                cout << "\t\t\tLista uspesno izbrisana." << endl;
                cout << "==========================================================================" << endl; 
                break;
            }
            case 6: {
                    system("cls");
                    myfile.open("lista.txt", ios::in);
                    if (myfile.is_open()){
                        string linija;
                        int i = 0;
                        while (getline(myfile, linija)){
                            cout << i << ". " << linija << endl;
                            i++;
                        }
                        myfile.close();
                        if (i == 0){
                            system("cls");
                            cout << "==========================================================================" << endl; 
                            cout << "\t\tGreska, vasa TODO lista je prazna." << endl;
                            cout << "==========================================================================" << endl; 
                            break;
                        }
                    }
                    int rbr;
                    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl; 
                    cout << "Unesite redni broj linije koju zelite da izbrisete: ";
                    cin >> rbr;
                    cout << endl;
                    fstream temp;
                    myfile.open("lista.txt", ios::in);
                    temp.open("temp.txt", ios::out);
                    if (myfile.is_open()){
                        string linija;
                        int i = 0;
                        while (getline(myfile, linija)) {
                            if (rbr != i){
                                temp << linija << endl;
                                i++;
                            }
                            else {
                                i++;
                                continue;
                            }
                        }
                        myfile.close();
                        temp.close();
                    }
                    myfile.open("lista.txt", ios::out);
                    temp.open("temp.txt", ios::in);
                    if (myfile.is_open()){
                        string linija;
                        while (getline(temp, linija)){
                            myfile << linija << endl;
                        }
                        myfile.close();
                        temp.close();
                    }
                    system("cls");
                    cout << "==========================================================================" << endl; 
                    cout << "\t\t\tVasa TODO lista" << endl;
                    cout << "==========================================================================" << endl; 
                    myfile.open("lista.txt", ios::in);
                    if (myfile.is_open()){
                        string linija;
                        int i = 0;
                        while (getline(myfile, linija)){
                            cout << linija << endl;
                            i++;
                        }
                        myfile.close();
                    }
                    break;
                }
            case 7: {
                bool sigp = false;
                system("cls");
                cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl; 
                cout << "Unesite vase koriscnicko ime: ";
                cin.ignore();
                getline(cin, korime7);
                korime7.append(".txt");
                myfile.open(korime7, ios::in);
                if (!myfile.is_open()){
                    system("cls");
                    cout << "==========================================================================" << endl; 
                    cout << "\t\tKorisnicko ime ne postoji u bazi podataka." << endl;
                    cout << "==========================================================================" << endl; 
                    break;
                }
                myfile.close();
                myfile.open(korime7, ios::in);
                if (myfile.is_open()){
                    string linija;
                    int brojac = 0;
                    while (getline(myfile, linija)){
                        if (brojac == 2){
                            cout << linija << endl;
                            break;
                        }
                        else{
                            brojac++;
                        }
                    }
                    myfile.close();
                }
                string odg;
                getline(cin, odg);
                myfile.open(korime7, ios::in);
                if (myfile.is_open()){
                    string linija7;
                    int brojac = 0;
                    while (getline(myfile, linija7)){
                        if (brojac == 3 && odg == linija7){
                            sigp = true;
                            break;
                        }
                        else{
                            brojac++;
                        }
                    }
                }
                myfile.close();
                if (sigp){
                    registracijaLozinkaProveraReset();
                    break;
                }
                else{
                    system("cls");
                    cout << "==========================================================================" << endl; 
                    cout << "\t\tNetacan odgovor na sigurnostno pitanje." << endl;
                    cout << "==========================================================================" << endl; 
                }
                break;
            }
            case 8: {
                    korekcijateksta("lista.txt");
                break;
            }
            default: {
                system("cls");
                cout << "==========================================================================" << endl; 
                cout << "\t\t\tNeispravan unos." << endl;
                cout << "==========================================================================" << endl; 
            }
        }
        cout << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl; 
        cout << "Da li zelite da nastavite rad sa programom, Da/Ne: "; 
        cin >> trajanje;
        cout << endl;
        cin.ignore();
    }
    return 0;
}