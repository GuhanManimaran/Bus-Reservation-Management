#include <chrono>
#include <conio.h>
#include <dos.h>
#include <fstream>
#include <iostream>
#include <process.h>
#include <stdio.h>
#include <string.h>
#include <thread>

using namespace std;

const int MAX_BUS = 50;
const int MAX_USERNAME_LENGTH = 20;
const int MAX_PASSWORD_LENGTH = 20;
const int MAX_DRIVER_NAME_LENGTH = 20;
const int MAX_LOCATION_LENGTH = 20;

class ID {
public:
    char user_name[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

  string get_username() // Member function to get username
  {
    cout << "\n\n\t Enter the user name of the ID: ";
    cin>>user_name;
    return user_name;
  }

  string get_password() // Member function to get password
  {
    cout << "\n\n\t  Enter the password of the ID: ";
    cin>>password;
    return password;
  }
};

class reserve {
public:
    int busn;
    char driver[MAX_DRIVER_NAME_LENGTH];
    char arrival[6]; // Including null terminator
    char depart[6];  // Including null terminator
    char from[MAX_LOCATION_LENGTH];
    char to[MAX_LOCATION_LENGTH];
    char seat[8][4][10];
    char user_ID[8][4][MAX_USERNAME_LENGTH];
    int cost;

    // Member functions
    void display();
    void disp_seat();
    int check_empticket();
    int check_empty(int i, int j) // Member function to check whether the seat is empty
    {
        if (strcmp(seat[i][j], "Empty") == 0) {
          return 1;
        } else {
          return 0;
        }
    }
};



ID login_id;
reserve bus[MAX_BUS];

void loading();
void main_menu();
void admin_login();
void admin_mode();
void create_id();
void delete_id();
void standard_login();
void standard_mode();
void book_tickets();
void install_bus();
void show_bus();
void show_seats(reserve);
void cancel_ticket();
void vline(char);

void loading() {
    system("cls");
    for (int i = 1; i <= 50; i++) {
        system("cls");
        cout << "\n\n\n\n\t\t\t\t    Loading \n " << '\n' << '\t' << '\t';
        for (int j = 1; j <= i; j++)
            cout << "²";
        cout << "\n\n\t\t\t\t      " << 2 * i << "%";
        this_thread::sleep_for(chrono::milliseconds(150 - i * 3));
    }
}

void reserve::display() {
  system("cls");
  vline('*');
  cout << "\n\n\t\t\t     The details of the bus";
  cout << "\n\n";
  vline('*');
  cout << "\n\n\n\tBus number: ";
  cout << busn;
  cout << "\n\n\tDriver's name: ";
  cout << driver;
  cout << "\n\n\tArrival time: ";
  int a1 = 0;
  for (a1 = 0; a1 < 5; a1++) {
    cout << arrival[a1];
  }
  cout << "\n\n\tDeparture time: ";
  for (a1 = 0; a1 < 5; a1++) {
    cout << depart[a1];
  }
  cout << "\n\n\tOrigin: ";
  cout << from;
  cout << "\n\n\tDestination: ";
  cout << to;
  cout << "\n\n\tCost: ";
  cout << cost;
  cout << "\n\n\n\n\t\t   Press any key to continue to seat map";
    cin.ignore(); // Ignore newline character in input buffer
    cin.get();    // Wait for user input
}

void reserve::disp_seat() {
  int s = 0, p = 0;
  for (int i = 0; i < 8; i++) {
    cout << "\n";
    for (int j = 0; j < 4; j++) {
      if (j == 2) {
        cout << "\t";
      }
      s++;
      if (strcmp(seat[i][j], "Empty") == 0) {
        cout.width(5);
        cout.fill(' ');
        cout << s << ".";
        cout.width(10);
        cout.fill(' ');
        cout << seat[i][j];
        p++;
      } else {
        cout.width(5);
        cout.fill(' ');
        cout << s << ".";
        cout.width(10);
        cout.fill(' ');
        cout << seat[i][j];
      }
    }
  }
  cout << "\n\n\t\t     There are " << p << " seats empty in Bus No: " << busn;
}

int reserve::check_empticket() {
  int e = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 4; j++) {
      if (strcmp(seat[i][j], "Empty") == 0)
        e++;
    }
  }
  return e;
}

void vline(char ch) // Function to insert line
{
  for (int i = 1; i < 80; i++)
    cout << ch;
}

void start_screen() // Start Screen Function
{
  system("cls");
  cout << "\n\n";
  vline('*');
  cout << "\n\n\t\t\t     Welcome to GK Transports";
  cout << "\n\n";
  vline('*');
  cout << "\n\n\n\n\n\n\n\t\t\t Book your Tickets here and enjoy";
  cout << "\n\n\n\n\n\n\t\t\t    Press any key to continue";
  getch();
}

void main_menu() // Main menu function
{
  system("cls");
  int choice1;
  cout << "\n\n";
  vline('*');
  cout << "\n\n\t\t\t\t    MAIN MENU";
  cout << "\n\n";
  vline('*');
  cout << "\n\n\t\t\t      Choose the login mode";
  cout << "\n\n\t\t\t      1.ADMIN Mode";
  cout << "\n\n\t\t\t      2.STANDARD USER Mode";
  cout << "\n\n\t\t\t      0.Exit";
  cout << "\n\n\n\t   Enter your choice (0 ,1 or 2): ";
  cin >> choice1;
  switch (choice1) {
  case 1:
    admin_login();
    break;
  case 2:
    standard_login();
    break;
  case 0:
    cout << "\n\n\n\n\t\t\t     Press any key to exit";
    getch();
    exit(0);
    break;
  default:
    cout << "\n\n\t\t\t     Enter a valid choice";
    cout << "\n\n\t\t\t   Press any key to continue";
    getch();
    main_menu();
    getch();
    break;
  }
}

void admin_login() // Function for admin login page
{
  system("cls");
  char admin_name[20], admin_pass[20], try_choice;
  cout << "\n\n";
  vline('*');
  cout << "\n\n\t\t\t\t  ADMIN Login";
  cout << "\n\n";
  vline('*');
  cout << "\n\n\n\t\t\t Enter the admin name: ";
  cin>>admin_name;
  cout << "\n\n\t\t\t   Enter the password: ";
  cin>>admin_pass;
  if (strcmp("Guhan", admin_name) == 0 &&
      strcmp("123456789", admin_pass) == 0) {
    cout << "\n\n\n\n\n\t\t\t       Login Successful";
    cout << "\n\n\t\t\t   Press any key to continue";
    getch();
    admin_mode();
  } else {
    cout << "\n\n\n\n\t\t     Either your name or password is incorrect";
  label1:
    cout << "\n\n\t\t\t Do you want to try again(y/n):";
    cin >> try_choice;
    switch (try_choice) {
    case 'y':
      admin_login();
      break;
    case 'n':
      cout << "\n\n\t\t   Press any key to return back to main menu";
      getch();
      main_menu();
      break;
    case 'Y':
      admin_login();
      break;
    case 'N':
      main_menu();
      break;
    default:
      cout << "\n\n\t\t Enter a valid input";
      goto label1;
    }
  }
  getch();
}

void admin_mode() // Admin Page
{
  system("cls");
  cout << "\n\n";
  vline('*');
  cout << "\n\n\t\t\t\t   ADMIN MENU";
  cout << "\n\n";
  vline('*');
  cout << "\n\n\t 1.To create a standard user ID.";
  cout << "\n\n\t 2.To delete a existing standard user ID.";
  cout << "\n\n\t 3.Add a bus to the database.";
  cout << "\n\n\t 4.Return to main menu.";
  cout << "\n\n\t 0.Exit.";
  cout << "\n\n\t Enter your choice: ";
  int choice2;
  cin >> choice2;
  switch (choice2) {
  case 1:
    create_id();
    break;
  case 2:
    delete_id();
    break;
  case 3:
    install_bus();
    break;
  case 4:
    cout << "\n\n\t\t   Press any key to return back to main menu";
    getch();
    main_menu();
    break;
  case 0:
    cout << "\n\n\t\t\t     Press any key to exit";
    getch();
    exit(0);
    break;
  default:
    cout << "\n\n\t\t\t     Enter a valid choice";
    cout << "\n\n\t\t\t   Press any key to continue";
    getch();
    admin_mode();
    break;
  }
  getch();
}

void create_id() // Function to create a user ID
{
  char choice = 'n';
  do {
  label3:
    fstream login("user.dat", ios::app | ios::binary);
    fstream login2("user.dat", ios::in | ios::binary);
    system("cls");
    ID user, confirm, check;
    cout << "\n\n";
    vline('*');
    cout << "\n\n\t\t\t  Create a standard user ID";
    cout << "\n\n";
    vline('*');
    user.get_username();
    cout << "\n";
    cout << "\t          Retype the user name: ";
    cin >> confirm.user_name;
    if (strcmp(user.user_name, confirm.user_name) != 0) {
      cout << "\n\n\n\n\n\t\tThe usernames that you have entered doesn't match";
      cout << "\n\n\n\n\t\t\t   Press any key to try again";
      getch();
      goto label3;
    }
    while (!login2.eof()) {
      login2.read((char *)&check, sizeof(check));
      if (strcmp(user.user_name, check.user_name) == 0) {
        cout << "\n\n\n\n\t\tThe username that you have entered already exists";
        cout << "\n\n\n\n\t\t\t   Press any key to try again";
        getch();
        goto label3;
      }
    }
    login2.close();
    user.get_password();
    cout << "\n";
    cout << "\t           Retype the password: ";
    cin >> confirm.password;
    if (strcmp(user.password, confirm.password) != 0) {
      cout << "\n\n\n\n\n\t\tThe passwords that you have entered doesn't match";
      cout << "\n\n\n\n\t\t\t   Press any key to try again";
      getch();
      goto label3;
    }
    login.write((char *)&user, sizeof(user));
    loading();
    system("cls");
    cout << "\n\n";
    vline('*');
    cout << "\n\n\t\t\t  Create a standard user ID";
    cout << "\n\n";
    vline('*');
    cout << "\n\n\n\t\t     Your ID has been created successfully";
    login.close();
    cout << "\n\n\t\t      Do you want to create another ID: ";
    cin >> choice;
  } while (choice == 'y' || choice == 'Y');
  cout << "\n\n\t\t      Press any key to return to main menu";
  getch();
  admin_mode();
}

void delete_id() // Function to delete a user ID
{
  char choice = 'n';
  do {
  label4:
    system("cls");
    ID del_user, temp_del, confirm;
    cout << "\n\n";
    vline('*');
    cout << "\n\n\t\t\t   Delete a standard user ID";
    cout << "\n\n";
    vline('*');
    del_user.get_username();
    cout << "\n";
    cout << "\t          Retype the user name: ";
    cin>>confirm.user_name;
    if (strcmp(del_user.user_name, confirm.user_name) != 0) {
      cout << "\n\n\n\n\n\t\tThe usernames that you have entered doesn't match";
      cout << "\n\n\t\t\t Do you want to try again(y/n):";
      cin >> choice;
      if (choice == 'y' || choice == 'Y') {
        goto label4;
      } else {
        cout << "\n\n\t\t      Press any key to return to main menu";
        getch();
        admin_mode();
      }
    }
    del_user.get_password();
    cout << "\n";
    cout << "\t           Retype the password: ";
    cin>>confirm.password;
    if (strcmp(del_user.password, confirm.password) != 0) {
      cout << "\n\n\n\n\n\t\tThe passwords that you have entered doesn't match";
      cout << "\n\n\t\t\t Do you want to try again(y/n):";
      cin >> choice;
      if (choice == 'y' || choice == 'Y') {
        goto label4;
      } else {
        cout << "\n\n\t\t      Press any key to return to main menu";
        getch();
        admin_mode();
      }
    }
    char found = 'n';
    fstream del_org("user.dat", ios::in | ios::binary);
    fstream del_temp("temp.dat", ios::in | ios::app | ios::binary);
    while (!del_org.eof()) {
      del_org.read((char *)&temp_del, sizeof(temp_del));
      if (strcmp(del_user.user_name, temp_del.user_name) != 0) {
        del_temp.write((char *)&temp_del, sizeof(temp_del));
      }
      if (strcmp(del_user.user_name, temp_del.user_name) == 0 &&
          strcmp(del_user.password, temp_del.password) == 0) {
        found = 'y';
      }
    }
    del_org.close();
    del_temp.close();
    remove("user.dat");
    rename("temp.dat", "user.dat");
    if (found == 'y') {
      loading();
      system("cls");
      cout << "\n\n";
      vline('*');
      cout << "\n\n\t\t\t   Delete a standard user ID";
      cout << "\n\n";
      vline('*');
      cout << "\n\n\n\t\t     Your ID has been deleted successfully";
      cout << "\n\n\t\t      Do you want to delete another ID: ";
      cin >> choice;
    }
    if (found == 'n') {
      cout << "\n\n\n\t\t           Your ID has not been found";
      cout << "\n\n\t\t\t Do you want to try again(y/n):";
      cin >> choice;
    }
  } while (choice == 'y' || choice == 'Y');
  cout << "\n\n\t\t      Press any key to return to main menu";
  getch();
  admin_mode();
}

void install_bus() {
  char choice = 'n';
  do {
    system("cls");
    reserve ins;
    cout << "\n\n";
    vline('*');
    cout << "\n\n\t\t\t   Add a bus to the database";
    cout << "\n\n";
    vline('*');
    cout << "\n\n\n\tEnter bus no: ";
    cin >> ins.busn;
    cout << "\tEnter Driver's name: ";
    cin>>ins.driver;
    cout << "\n\tArrival time: ";
    cin>>ins.arrival;
    cout << "\tDeparture time: ";
    cin>>ins.depart;
    cout << "\n\tOrigin: ";
    cin>>ins.from;
    cout << "\tDestination: ";
    cin>>ins.to;
    cout << "\n\tCost: ";
    cin >> ins.cost;
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 4; j++) {
        strcpy(ins.seat[i][j], "Empty");
      }
    }
    fstream inst("busdata.dat", ios::app | ios::binary);
    inst.write((char *)&ins, sizeof(ins));
    loading();
    system("cls");
    cout << "\n\n";
    vline('*');
    cout << "\n\n\t\t\t   Add a bus to the database";
    cout << "\n\n";
    vline('*');
    cout << "\n\n\t The details of the bus had been added to the database "
            "successfully.";
    inst.close();
    cout << "\n\n\t\t Do you want to add another bus to the database(y/n): ";
    cin >> choice;
  } while (choice == 'Y' || choice == 'y');
  cout << "\n\n\t\t      Press any key to return to main menu";
  getch();
  admin_mode();
}

void standard_login(){ // Function for end user login{
  ID temp_user;
  fstream std_login;
  std_login.open("user.dat", ios::out | ios::in | ios::binary);
  system("cls");
  cout << "\n\n";
  vline('*');
  cout << "\n\n\t\t\t\tStandard login";
  cout << "\n\n";
  vline('*');
  login_id.get_username();
  login_id.get_password();
  char found = 'n';
  while (!std_login.eof()) {
    std_login.read((char *)&temp_user, sizeof(temp_user));
    if (strcmp(temp_user.user_name, login_id.user_name) == 0) {
      if (strcmp(temp_user.password, login_id.password) == 0) {
        found = 'y';
        break;
      }
    }
  }
  if (found == 'n') {
    cout
        << "\n\n\n\n\n\n\n\n\n\t\t   Either your name or password is incorrect";
  label2:
    cout << "\n\n\t\t\t   Do you want to try again(y/n):";
    char try_choice1;
    cin >> try_choice1;
    switch (try_choice1) {
    case 'y':
      standard_login();
      break;
    case 'n':
      main_menu();
      break;
    case 'Y':
      standard_login();
      break;
    case 'N':
      main_menu();
      break;
    default:
      cout << "\n\n\t\t Enter a valid input";
      goto label2;
    }
  }
  std_login.close();
  if (found == 'y') {
    cout << "\n\n\n\n\n\t\t\t       Login Successful";
    cout << "\n\n\t\t\t   Press any key to continue";
    getch();
    standard_mode();
  }
}

void standard_mode() // Function for end user menu
{
  system("cls");
  cout << "\n\n";
  vline('*');
  cout << "\n\n\t\t\t      STANDARD USER MODE";
  cout << "\n\n";
  vline('*');
  cout << "\n\n\n\n\t 1.Book Tickets.";
  cout << "\n\n\t 2.View the details of bus by entering number";
  cout << "\n\n\t 3.Cancel your booked Tickets";
  cout << "\n\n\t 4.Main Menu";
  cout << "\n\n\t 0.Exit";
  cout << "\n\n\n\n\t Enter your choice(0 to 4): ";
  int choice3;
  cin >> choice3;
  switch (choice3) {
  case 1:
    book_tickets();
    break;
  case 2:
    show_bus();
    break;
  case 3:
    cancel_ticket();
    break;
  case 4:
    main_menu();
    break;
  case 0:
    exit(0);
    break;
  default:
    cout << "\n\n\n\t\t\t     Enter a valid choice";
    cout << "\n\n\t\t\t   Press any key to continue";
    getch();
    standard_mode();
  }
  getch();
}

// Function to book tickets
void book_tickets() {
    system("cls");
    cout << "\n\n";
    vline('*');
    cout << "\n\n\t\t\t\t  Book Tickets\n\n";
    vline('*');

    reserve temp, temp1;
    cout << "\n\n\t Enter the bus number: ";
    cin >> temp1.busn;

    fstream ticket("busdata.dat", ios::in | ios::out | ios::binary);
    if (!ticket) {
        cout << "\nError: Cannot open file.";
        return;
    }

    bool found = false;
    while (ticket.read(reinterpret_cast<char*>(&temp), sizeof(temp))) {
        if (temp.busn == temp1.busn) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\n\n\tBus number not found.";
        ticket.close();
        return;
    }

    int n;
    cout << "\n\n\tEnter the number of tickets to be booked: ";
    cin >> n;

    if (n > temp.check_empticket()) {
        cout << "\n\n\tThere are only " << temp.check_empticket() << " available tickets in the bus.";
        cout << "\n\n\tPress any key to return to main menu";
        getch();
        ticket.close();
        return;
    }

    int temp_seat;
    for (int i = 1; i <= n; i++) {
        cout << "\n\tEnter the seat number for passenger " << i << ": ";
        cin >> temp_seat;
        if (temp_seat > 32) {
            cout << "\n\tThere are only 32 seats available in this bus.";
            cout << "\n\n\tPress any key to return to main menu";
            getch();
            ticket.close();
            return;
        }
        if (temp.check_empty((temp_seat / 4), (temp_seat % 4) - 1) == 1) {
            cout << "\n\tEnter the name of passenger " << i << ": ";
            cin >> temp.seat[temp_seat / 4][(temp_seat % 4) - 1];
            strcpy(temp.user_ID[temp_seat / 4][(temp_seat % 4) - 1], login_id.user_name);
        } else {
            cout << "\n\tThis seat is reserved for another passenger.";
            cout << "\n\tPress any key to continue";
            getch();
            i--; // Go back to the previous passenger
        }
    }

    // Update ticket data
    ticket.seekp(-sizeof(temp), ios::cur);
    ticket.write(reinterpret_cast<char*>(&temp), sizeof(temp));
    ticket.close();

    // Display booking confirmation
    system("cls");
    cout << "\n\n";
    vline('*');
    cout << "\n\n\t\t\t\t  Book Tickets\n\n";
    vline('*');
    cout << "\n\n\t\t   Your tickets have been booked successfully";
    cout << "\n\n\t The cost for the ticket is " << n * temp.cost;
    cout << "\n\n\t Please pay the bill to the conductor before you start the journey";
    cout << "\n\n\t Please carry each of the traveler's ID card for verification";
    cout << "\n\n\n\n\t\tPress any key to return to main menu";
    getch();
    /*
    if (tem.check_empticket() == 0) {
      cout << "\n\n\t There are no tickets available in this bus";
      cout << "\n\n\n\n\t\t      Press any key to return to main menu";
      getch();
      standard_mode();
    }
    */
    standard_mode();
}

void show_bus() // Function to show the details of a bus
{
  reserve temp, search;
  system("cls");
  vline('*');
  cout << "\n\n\t\t\t     The details of the bus";
  cout << "\n\n";
  vline('*');
  cout << "\n\n\n\t Enter the bus number: ";
  cin >> temp.busn;
  fstream disp("busdata.dat", ios::in | ios::out | ios::binary);
  while (!disp.eof()) {
    disp.read((char *)&search, sizeof(search));
    if (search.busn == temp.busn) {
      search.display();
      show_seats(search);
      break;
    }
  }
  disp.close();
  cout << "\n\n\n\t\t      Press any key to return to main menu";
  getch();
  standard_mode();
}

void show_seats(reserve seat) // Function to show the seat map of a bus
{
  system("cls");
  cout << "\n\n";
  vline('*');
  cout << "\n\n\t\t\t The details of the seats of the bus";
  cout << "\n\n";
  vline('*');
  cout << "\n";
  seat.disp_seat();
  cout << "\n\n\n\t\t      Press any key to return to main menu";
  getch();
  standard_mode();
}

void cancel_ticket() // Function to cancel a booked ticket
{
label6:
  system("cls");
  reserve del, temp, temp2;
  char choice = 'n';
  int seats;
  cout << "\n\n";
  vline('*');
  cout << "\n\n\t\t\t   Cancel the booked tickets";
  cout << "\n\n";
  vline('*');
  cout << "\n\n";
  do {
    cout << "\t Enter the bus number: ";
    cin >> temp.busn;
    fstream bus("busdata.dat", ios::binary | ios::in);
    while (!bus.eof()) {
      bus.read((char *)&del, sizeof(del));
      if (del.busn == temp.busn) {
        cout << "\n\n\t Enter the seat number to be cancelled: ";
        cin >> seats;
        if (strcmp(del.seat[seats / 4][(seats % 4) - 1], "Empty") != 0) {
          if (strcmp(del.user_ID[seats / 4][(seats % 4) - 1],
                     login_id.user_name) != 0) {
            cout << "\n\n\t\tThis ticket is not booked from your user id";
            cout << "\n\n\t\t\tDo you want to try again(y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
              goto label6;
            } else {
              standard_mode();
            }
          }
          strcpy(del.seat[seats / 4][(seats % 4) - 1], "Empty");
          fstream temp1("temp1.dat", ios::app | ios::binary);
          bus.seekg(0);
          while (!bus.eof()) {
            bus.read((char *)&temp2, sizeof(temp2));
            if (del.busn != temp2.busn) {
              temp1.write((char *)&temp2, sizeof(temp2));
            }
          }
          temp1.write((char *)&del, sizeof(del));
          temp1.close();
          bus.close();
          remove("busdata.dat");
          rename("temp1.dat", "busdata.dat");
          loading();
          system("cls");
          cout << "\n\n";
          vline('*');
          cout << "\n\n\t\t\t   Cancel the booked tickets";
          cout << "\n\n";
          vline('*');
          cout << "\n\n\t\t Your booked seat have been cancelled successfully";
          cout << "\n\n\t Do yo want cancel one more ticket(Y/N): ";
          cin >> choice;
          break;
        } else {
          cout << "\n\n\t The selected seat havent booked by anyone";
          cout << "\n\n\t\t\t Do yo want to try again(Y/N): ";
          cin >> choice;
          if (choice == 'y' || choice == 'Y')
            goto label6;
          else {
            cout << "\n\n\n\n\t\t      Press any key to return to main menu";
            getch();
            standard_mode();
          }
        }
      }
    }
  } while (choice == 'y' || choice == 'Y');
  cout << "\n\n\n\n\t\t      Press any key to return to main menu";
  getch();
  standard_mode();
}

int main() // Main Function
{
  loading();
  start_screen();
  main_menu();
}
