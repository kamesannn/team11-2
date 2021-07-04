#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <time.h> 
#include <string.h>

using namespace std;

struct Parent_reg
{
    char full_name[40];
    char gender[10];
    char dob[20];
    char phone[20];
    char child_name[40];
    int room_no;
    char username[40];
    char password[40];
}par_reg;

struct Staff_reg
{
    char full_name[40];
    char gender[10];
    char dob[20];
    char username[40];
    char password[40];
}sta_reg;

struct Parent_login
{
    char username[40];
    char password[40];
}par_log;

struct Staff_login
{
    char username[40];
    char password[40];
}sta_log;

struct Order
{
    int roll, menu_no;
    char fullname[40];
    char date[20];
    char quantity;             
    float price;
    char child_name[40];
    int room_no;
    char contact_no[20];
    string voucher;
    char payment_status[10];     
    char issued_status;        
    char ansewr;               
}order;

struct Menu
{
    int no;
    char main[30];
    char side[30];
    char fruit[30];
    double priceL, priceM, priceS;

    Menu()
    {
       priceL = 20.00;
       priceM = 15.00;
       priceS = 10.00;
    }
    
}menu;

struct Compliant
{
    int roll;
    char full_name[40];
    char doo[20];
    int item_no;
    char complaint_des[100];
    char contact_no[20];
    char email[40];
    char act_status;
}comp;

// functions
void weekly_menu_list(int);
void make_comp(fstream& complaint_file);
void order_screen(fstream& order_file);
void parent_reg(struct Parent_reg par_reg);
void staff_reg(struct Staff_reg sta_reg);
void staff_login(char username[], char password[]);
void parent_login(char username[], char password[]);
void par_sta_menu();
void admin_login();
void admin_menu(fstream& menu_file, fstream& complaint_file, fstream& order_file);
void line(int, char);

// files
fstream reg_sta_file;
fstream reg_par_file;
fstream order_file;
fstream menu_file;
string read_rec;
fstream complaint_file;

// grobal dec
char login_name_ad[20];
int pw_ad;
int menu_no;


int main()
{
    // local dec
    int main_opt;
    int main_login_as, main_reg_as;
    char username[20], password[20];
    

    cout << "\n\t\t\t\t\tYoobee School Lunch \n";

    line(100, '*');

    cout << "\n\t\t\t\t----- Weekly Menu -----\n\n";
    cout << "Week 1 (July, 2021)\n";

    cout << "MENU NO   \t\tMAIN   \t\tSIDE      \tFRUIT       PRICE(L)    PRICE(M)    PRICE(S)\n\n"; 

    menu_no = rand() % 10;           // displaying three menu of the week by using rand()
    weekly_menu_list(menu_no);
    menu_no = rand() % 10;
    weekly_menu_list(menu_no);
    menu_no = rand() % 10;
    weekly_menu_list(menu_no);
    line(100, '*');

    cout << "\n\t\t\t----- Special limited discount -----\n\n";
    cout << "We are offering special price for our customer!!!!!\n";
    cout << "Enter (( yoobee )) to use the discount. You will get 10% off from your order.\n";
    line(100, '*');

    cout << "\n\t\t\t\t----- Contact Us -----\n\n";
    cout << "Phone   :   0800 000 000\n";
    cout << "E-mail  :   Yoobeelunch@gmail.com\n";
    cout << "Address :   4/3 City Road, Grafton Auckland\n";
    line(100, '*');

    cout << "\nRegistar with us from today!!      (Press 1)";
    cout << "\nDo you already have an account?    (Press 2)";
   

    cout << "\n\nToday I want......(Please Enter the number from above) : ";
    cin >> main_opt;

    switch (main_opt)
    {
    case 1:
        cout << "\n\nRegistar as parents   (Press 1)";
        cout << "\nRegistar as staff     (Press 2)\n\n";
        cout << "Registar as ...... : "; cin >> main_reg_as;

        if (main_reg_as == 1)
        {
            parent_reg(par_reg);
            par_sta_menu();
        }
        else if (main_reg_as == 2)
        {
            staff_reg(sta_reg);
            par_sta_menu();
        }
        else
        {
            cout << "\nSorry try again....\n";
        }
        break;
    
    case 2:
        cout << "\nLogin as parents   (Press 1)";
        cout << "\nLogin as staff     (Press 2)";
        cout << "\nLogin as admin     (Press 3)\n\n";
        cout << "Login as ...... : "; cin >> main_login_as;

        if (main_login_as == 1)         
        {
            cin.ignore();
            cout << "\n\t\tEnter User Name : ";
            cin.getline(username, 40);

            cout << "\n\t\tEnter Password : ";
            cin.getline(password, 40);
            parent_login(username, password);
            
        }
        else if (main_login_as == 2)
        {
            
            cin.ignore();
            cout << "\n\t\tEnter User Name : ";
            cin.getline(username, 40);

            cout << "\n\t\tEnter Password : ";
            cin.getline(password, 40);
            staff_login(username, password);
                
                
        }  
        else if (main_login_as == 3)
        {
            admin_login();

            if(pw_ad == 123)
            {
                admin_menu(menu_file, complaint_file, order_file);
                break;
            }
            else
            {
                cout << "\nInvaild passward, try again....";
                
            }
        }
        else
        {
            cout << "\nSorry try again....\n";
        }
        break;

    default:
        cout << "\nPlease enter a number between 1 and 3....";
        break;
    }

    cout << "\n\t\t~~~~~~~~~ Thank you for using Yoobee School Lunch ~~~~~~~~~";
    cout << "\n\n\n";

    return 0;
}



//////////// functions ///////////

void line(int n, char ch)                               // line generator
{
    cout << "\n";

    for (int i = 0; i < n; i++)
    {
        cout << ch;
    }

    cout << "\n";
}

void weekly_menu_list(int menu_no)                     // weekly menu
{
    int numOfLines = 0, random;
    struct Menu menu;

    menu_file.open("menu_file.dat", ios::in | ios::binary);

    while (!menu_file.eof())
    {
        
        while (menu_file.read(reinterpret_cast<char*>(&menu),sizeof(menu)))
        {
            ++numOfLines;

           if(numOfLines == menu_no)
            {
                cout << setw(5) << menu.no;
                cout << setw(24) << menu.main;
                cout << setw(18) << menu.side;
                cout << setw(15) << menu.fruit;
                cout << setw(13) << menu.priceL;
                cout << setw(12) << menu.priceM;
                cout << setw(12) << menu.priceS << "\n";
            
                break;
                
            }
        }

    }

    menu_file.close();
}


void parent_reg(struct Parent_reg par_reg)
{
    cout<< "\nParent's Registration Screen\n";
    cout << "****************************\n\n";

    cin.ignore();
    cout << "Enter your full name: ";
    cin.getline(par_reg.full_name, 40);
    cout << "Enter your gender : ";
    cin >>par_reg.gender;
    cout << "Enter your date of birth : ";
    cin >> par_reg.dob;
    cout << "Enter your phone number : ";
    cin >> par_reg.phone;
    cout << "Enter your child name : ";
    cin >> par_reg.child_name;
    cout << "Enter your child room number : ";
    cin >> par_reg.room_no;
    cin.ignore();
    cout << "Enter your user name : ";
    cin.getline(par_reg.username, 40);
    cout << "Create your password : ";
    cin.getline(par_reg.password, 40);
    
    reg_par_file.open("Reg_parent.dat", ios::out | ios::app | ios::binary);

        reg_par_file.write(reinterpret_cast<char*>(&par_reg),sizeof(par_reg));
   
    reg_par_file.close();

    cout << "\nNew Registration\n";
    cout << "*******************\n\n";
    cout << "Name: " << par_reg.full_name << endl;
    cout << "Gender: " << par_reg.gender << endl;
    cout << "Date of Birth: " << par_reg.dob << endl;
    cout << "Contact Number: " << par_reg.phone << endl;
    cout << "Child Name: " << par_reg.child_name << endl;
    cout << "Child room number: " << par_reg.room_no << endl;

 
}

void staff_reg(struct Staff_reg sta_reg)
{
    cout << "\nStaff Registration\n";
    cout << "*******************\n\n";

    cin.ignore();
    cout << "Enter full name : ";
    cin.getline(sta_reg.full_name, 40);
    cout << "Enter your gender : ";
    cin.getline(sta_reg.gender, 10);
    cout << "Enter your date of birth : ";
    cin.getline(sta_reg.dob, 20);
    cout << "Enter your user name : ";
    cin.getline(sta_reg.username, 40);
    cout << "Create your password : ";
    cin.getline(sta_reg.password, 40);

    reg_sta_file.open("Reg_staff.dat", ios::out | ios::app | ios::binary);

        reg_sta_file.write(reinterpret_cast<char*>(&sta_reg),sizeof(sta_reg));
   
    reg_sta_file.close();

    cout << "\nNew Registration\n";
    cout << "*****************\n";
    cout << "Name: " << sta_reg.full_name << endl;
    cout << "Gender: " << sta_reg.gender << endl;
    cout << "Date of Birth: " << sta_reg.dob << endl;
}

void parent_login(char username[], char password[])
{
    Parent_reg par_reg;
    fstream reg_par_file;
    bool flag = false;;
    
    reg_par_file.open("Reg_parent.dat", ios::in | ios::binary);


	while (!reg_par_file.eof())  
	{
		reg_par_file.read(reinterpret_cast<char*>(&par_reg), sizeof(par_reg));
		
		if ((strcmp(username, par_reg.username) == 0) && (strcmp(password, par_reg.password) == 0))
		{
			par_sta_menu();
			flag = false;
            break;
		}
		else
		{
			flag = true;
			
		}
	}

	if (flag)
	{
		cout << "\n\n\t\t******************************************\n\n";
		cout << "\nSorry user not found .. Please try again later...";
		cout << "\n\n\t\t******************************************\n\n";
	}
	reg_par_file.flush();
	reg_par_file.close();

}
            


void staff_login(char username[], char password[])
{
    Staff_reg sta_reg;
    fstream reg_sta_file;

    bool flag = false;


	reg_sta_file.open("Reg_staff.dat", ios::in | ios::binary);

	while (!reg_sta_file.eof())  
	{
		reg_sta_file.read(reinterpret_cast<char*>(&sta_reg), sizeof(sta_reg));
		
		if ((strcmp(username, sta_reg.username) == 0) && (strcmp(password, sta_reg.password) == 0))
		{
			par_sta_menu();
			flag = false;
            break;
		}
		else
		{
			flag = true;
			
		}
	}

	if (flag)
	{
		cout << "\n\n\t\t******************************************\n\n";
		cout << "\nSorry user not found .. Please try again later...";
		cout << "\n\n\t\t******************************************\n\n";
	}
	reg_sta_file.flush();
	reg_sta_file.close();

}

void par_sta_menu()
{
    int par_sta_opt;

    do
    {
        cout << "\n\n\t\t\t****** Welcome to Yoobee School Lunch ******\n";
        cout << "\t\t\t*                                          *\n";
        cout << "\t\t\t*       1. Menu list & Order lunch         *\n";
        cout << "\t\t\t*       2. Make compliant                  *\n";
        cout << "\t\t\t*       3. Exit                            *\n";
        cout << "\t\t\t*                                          *\n";
        cout << "\t\t\t********************************************\n";
        
        
        cout << "\n\t\t\t\tEnter your option : ";
        cin >> par_sta_opt; 
        cout << "\n\n";

        switch (par_sta_opt)
        {
        case 1: 
            cout << "\n\t\t\t\t-----  Menu list -----\n\n";

            cout << "MENU NO   \t\tMAIN   \t\tSIDE      \tFRUIT       PRICE(L)    PRICE(M)    PRICE(S)\n\n";

            menu_file.open("menu_file.dat", ios::in | ios::binary);

        
	        if (menu_file.is_open())
	        {
                while (menu_file.read(reinterpret_cast<char*>(&menu), sizeof(menu)))
                {
                    cout << setw(5) << menu.no;
                    cout << setw(24) << menu.main;
                    cout << setw(18) << menu.side;
                    cout << setw(15) << menu.fruit;
                    cout << setw(13) << menu.priceL;
                    cout << setw(12) << menu.priceM;
                    cout << setw(12) << menu.priceS << "\n";
                }
            }
            menu_file.close();

            order_screen(order_file);
            break;

        case 2: 
            make_comp(complaint_file);
            break;
            
        
        case 3: 
            
            break;    
        
        default:
            cout << "\nEnter vaild number....";
            break;
        }

    }while(par_sta_opt != 3);
}


void order_screen(fstream& order_file)
{
    float quantity;

    cout << "\n\n\t\t\t\t----- Order lunch -----\n\n";

    srand(time(NULL));
    order.roll = rand() % 100;                     // generating order roll no by using rand()
    cout << "\nOrder number : " << order.roll;
    
    cin.ignore();
    cout << "\n\nEnter fullname : ";
    cin.getline(order.fullname, 40);
    cout << "\nEnter order date(dd/mm/year) : ";
    cin.getline(order.date, 20);
    cout << "\nEnter menu number : ";
    cin >> order.menu_no;
    cout << "\nEnter quantity (Large = l, Medium = m, Small = s) : ";
    cin >> order.quantity;
    cin.ignore();
    cout << "\nEnter child name : ";
    cin.getline(order.child_name, 40);
    cout << "\nEnter room number : ";
    cin >> order.room_no;
    cin.ignore();
    cout << "\nEnter your contact number : ";
    cin.getline(order.contact_no, 20);
    cout << "\nDo you have a voucher?\nEnter the code here (if not, enter 'n') : ";
    cin >> order.voucher;
    cout << "\nEnter payment status (Paid = p, NotPaid = n) : ";
    cin >> order.payment_status;
    cout << "\nEnter issued status (Pending = p, Issued = i) : ";
    cin >> order.issued_status;
    cout << "\nEnter payment proceed (Yes = y, No = n) : ";
    cin >> order.ansewr;

    if(order.ansewr == 'y')
    {
        strcpy(order.payment_status, "PAID");
        
    }
    else if(order.ansewr == 'n')
    {
        strcpy(order.payment_status, "NOT_PAID");
    }
    else
    {
        cout << "\nPlease answer by y or n...";
    }

    if(order.quantity == 'l')
    {
        if(order.voucher == "yoobee")
        {
            quantity = 20.00 - (20.00 * 10 / 100);
        }
        else
        {
            quantity = 20.00;
        }
    }
    else if(order.quantity == 'm')
    {
        if(order.voucher == "yoobee")
        {
            quantity = 15.00 - (15.00 * 10 / 100);   
        }
        else
        {
            quantity = 15.00;
        }
    }
    else if(order.quantity == 's')
    {
        if(order.voucher == "yoobee")
        {
            quantity = 10.00 - (10.00 * 10 / 100);   
        }
        else
        {
            quantity = 10.00;
        }
    }
    else
    {
        cout << "\nError... Please check the inital of quantity!";
    }
    
    order_file.open("Order_file.dat", ios::out | ios::app | ios::binary);

	  order_file.write(reinterpret_cast<char*>(&order), sizeof(order));         // wrting to order_file

	order_file.close(); 
    
    cout << "\n\n\nHere is your bill...\n";

	cout << "\nOrder number\tDate of order   \tMenu number\t Price \tStudent name \tRoom number \n\n ";
		
	cout << setw(8) << order.roll;
	cout << setw(18) << order.date;
	cout << setw(17) << order.menu_no;
	cout << setw(16) << quantity;
	cout << setw(15) << order.child_name;
	cout << setw(15) << order.room_no;
    cout << "\n\nOrder payment : " << order.payment_status;
			
    cout << "\n\n\n\tThank you for your order!!!";
	cout << "\n****************************************\n";
	
}

void make_comp(fstream& complaint_file)
{
    
    cout << "\n\t\t\t\t----- Make complaint -----\n\n";

    srand(time(NULL));
    comp.roll = rand() % 100;                               // generating compliant number by using rand()
    cout << "\nCompliant number : " << comp.roll;

    cin.ignore();
    cout << "\n\nEnter full name : ";
    cin.getline(comp.full_name, 40);
    cout << "\nEnter date of order : ";
    cin.getline(comp.doo, 20);
    cout << "\nEnter menu number : ";
    cin >> comp.item_no;
    cin.ignore();
    cout << "\nEnter compliant description : ";
    cin.getline(comp.complaint_des, 100);
    cout << "\nEnter contact number : ";
    cin.getline(comp.contact_no, 20);
    cout << "\nEnter email : ";
    cin.getline(comp.email, 40);
    cout << "\nEnter action status (responded = r, pending = p) : ";
    cin >> comp.act_status;
            
    complaint_file.open("Complaint_file1.dat", ios::out | ios::app | ios::binary);      
      complaint_file.write(reinterpret_cast<char*>(&comp), sizeof(comp));               // wrting to complaint_file
	complaint_file.close(); 

}

void admin_login()
{
    cin.ignore();
    cout << "\n\t\tEnter login name : ";
    cin.getline(login_name_ad, 20);

    cout << "\n\t\tEnter your password :";
    cin >> pw_ad;
}


void admin_menu(fstream& menu_file, fstream& complaint_file, fstream& order_file)
{
    int admin_opt;
    int numOforder = 0;
    int dailyorder = 0;
    char update_y_n;
    char s_date[15];
    bool flag = false;

    do
    {
        cout << "\n\n\t\tAdmin menu\n";
        cout << "\n1. Menu update";
        cout << "\n2. Daily order report";
        cout << "\n3. Weekly sales report";
        cout << "\n4. Weekly pending payment report";
        cout << "\n5. Weekly comlaint";
        cout << "\n6. Quit";

        cout << "\nEnter your option : ";
        cin >> admin_opt;

        switch (admin_opt)
        {
        case 1:
            cout << "\n\n\t\t---- Menu update ----";                            // updating menu by admin
            
            do{
                cout  << "\n\nEnter menu number (between 100 and 200): ";
                cin >> menu.no;

                cin.ignore();
                cout << "\nEnter main : ";
                cin.getline(menu.main, 30);

                cout << "\nEnter side : ";
                cin.getline(menu.side, 30);

                cout << "\nEnter fruit : ";
                cin.getline(menu.fruit, 30);

                menu_file.open("menu_file.dat", ios::out | ios::app | ios::binary);

                  menu_file.write(reinterpret_cast<char*>(&menu),sizeof(menu));     // wrting to menu_file

                menu_file.close();

                cout << "\nDo you want to add more menu? (y or n) : ";
                cin >> update_y_n;

            }while(update_y_n == 'y');

            break;

        case 2:
            cout << "\n\t\t---- Daily order report  ----\n\n";          // displaying daily order by searching the date

            cin.ignore();
            cout << "\nEnter the date here(dd/mm/year) : ";
            cin.getline(s_date, 20);

            order_file.open("Order_file.dat", ios::in | ios::binary);            // opening Order_file1 in reading and binary mode
            
	        if (order_file.is_open())
            {
                while (!order_file.eof()) 
                {
                    order_file.read(reinterpret_cast<char*>(&order), sizeof(order));

                    if ((strcmp(s_date, order.date) == 0))                  // if s_date and order.date is mached, display daily order record
                    {
                        cout << "\nDate of order" << setw(20) << "Menu number\n";
                        cout << setw(8) << order.date;
                        cout << "\t\t " << order.menu_no;
                        dailyorder++;                                       // counting the number of daily order
                        flag = false;
                        break;
                    }
                    else
                    {
                        flag = true;
                    }
                }
            }
            else
            {
                cout << "\nFile unable to access ....";
            }

            if (flag)
            {
                cout << "\nNo order on the date...";
            }
                
		    cout << "\n\n(( Number of Daily Order : " << dailyorder << " ))";
            
            order_file.close();
            break;

        case 3:
            cout << "\n\t\t---- Weekly sales report ----\n\n";
            
            order_file.open("Order_file.dat", ios::in | ios::binary);

	        if (order_file.is_open())
	        {
		        cout << "Order dates" << setw(20) << "Amount\n";
		        
                while (order_file.read(reinterpret_cast<char*>(&order), sizeof(order)))
		        {
                    cout << setw(8) << order.date;
                    cout << "\t\t   "<< order.quantity << "\n";
                    numOforder++;                 
                }
                
                cout << "\n(( Number of Order : " << numOforder << " ))";
		    }
            order_file.close();
            break;

        case 4:
            cout << "\n\t\t---- Weekly pending payment report ----";
            
            order_file.open("Order_file.dat", ios::in | ios::binary);

	        if (order_file.is_open())
	        {
		        cout << "\n\nFull name\t\t  Date of order     \tContact number     \tMenu number\n\n";
		        
                while (order_file.read(reinterpret_cast<char*>(&order), sizeof(order)))
		        {
                    cout << order.fullname;
                    cout << "\t\t  " << order.date;
                    cout << setw(20) << order.contact_no;
                    cout << setw(20) << order.menu_no << "\n";                 
                }
		    }
            order_file.close();
            break;

        case 5:
            cout << "\n\t\t---- Weekly comlaint ----\n\n";
            
            complaint_file.open("Complaint_file1.dat", ios::in | ios::binary);      // opening Complaint_file1 in reading and binary mode

            if (complaint_file.is_open())
            {
                
                while (complaint_file.read(reinterpret_cast<char*>(&comp), sizeof(comp)))
                {
                    cout << "\n" << "     Complaint number : " << comp.roll;
                    cout << "\n" << "            Full name : " << comp.full_name;
                    cout << "\n" << "       Date of ordert : " << comp.doo;
                    cout << "\n" << "          Menu number : " << comp.item_no;
                    cout << "\n" << "Compliant description : " << comp.complaint_des;
                    cout << "\n" << "       Contaxt number : " << comp.contact_no;
                    cout << "\n" << "               E-mail : " << comp.email;
                    cout << "\n************************************\n\n";                  
                }
            
            }
            complaint_file.close();
            break;
       
        case 6:
            break;
        
        default:
            cout << "\nInvaild number.. try again....";
            break;
        }
    
    }while (admin_opt != 6);

    
}

