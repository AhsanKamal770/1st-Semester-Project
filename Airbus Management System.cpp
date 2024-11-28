#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void logo();      //  Logo Of Management System
void adminmenu(); // Displays Admin Menu
void usermenu();  // Displays User Menu
void adminbar();
void breaking();
void line();
void storedatauser(string name[], string tel[], string userid[], string pass[],
                   int bookings[], string bookbus[][5], int seat[][5]);
bool loaddatauser(string name[], string tel[], string userid[], string pass[], int bookings[], string bookbus[][5], int seat[][5]);
void checkage(int &age);
void storedatabus(string bus[], string departure[], string deptime[], string destination[], string arrtime[], int capacity[]);
bool loaddatabus(string bus[], string departure[], string deptime[], string destination[], string arrtime[], int capacity[]);
void findindex1(string name[], string name1, int &adflag, int &k);
void findindex2(string name[], string pass[], string name1, string password, int &adflag, int &k);
void checkpass(string &pass);
void checktel(string &tel);
void checkid(string &id);
void checkname(string &tel);
void checktime(string &time);
void checkbus(string &bus);

int main()
{
    int input, input1, choice;
    string password, choice1;
    int uflag, k, adflag;
    string user, dep, des, busname;
    // Airbus
    int capacity[5]={0};
    string deptime[5], arrtime[5], departure[5], destination[5];
    string bus[5] = {"0", "0", "0", "0", "0"};
    // user
    int age[5], seat[5][5], bookings[5] = {0, 0, 0, 0, 0};
    string name[5]={"0","0","0","0","0"}, tel[5], bookbus[5][5], userid[5] = {"0", "0", "0", "0", "0"}, pass[5] = {"0", "0", "0", "0", "0"};
    loaddatauser(name, tel, userid, pass, bookings, bookbus, seat);
    loaddatabus(bus, departure, deptime, destination, arrtime, capacity);

    do
    {
        input = 1, input1 = 1;
        uflag = 0, adflag = 0;
        logo();
        cout << "Choose an option: "; //    Prompts User to Enter out of Three of Menu Options
        cin >> input;
        while (!cin)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            system("cls");
            cout << "You Entered an Invalid Input" << endl;
            logo();
            cout << "Choose an option: ";
            cin >> input;
        }
        cout << "\n\n";

        switch (input)
        {
        case 1: // Admin login
            cout << setw(65) << "Enter Admin ID: ";
            cin >> user;
            cout << setw(65) << "Enter Password: ";
            cin >> password;
            if (user == "Administrator" && password == "PF2020")
            {
                uflag = 1;
            }
            else
            {
                uflag = 0;
            }
            break;

        case 2: // User login
            cout << setw(65) << "Enter User ID: ";
            cin.ignore(256, '\n');
            getline(cin, user);
            cout << setw(65) << "Enter Password: ";
            cin >> password;

            for (int i = 0; i < 5; i++) //  Loop to Check For user
            {
                if (user == userid[i] && password == pass[i])
                {
                    uflag = 2;
                    k = i;
                    break;
                }
            }
            if (uflag != 2)
            {
                uflag = 0;
            }
            break;
        case 3:
            for (int i = 0; i < 5; i++)
            {
                if (userid[i] == "0")
                {
                    uflag = 3;
                    k = i;
                    break;
                }
                else
                {
                    uflag = 4;
                }
            }
            break;
        case 0: // Logout
            cout << "Logged out Successfully!" << endl;
            cout << "Thank you for using this system." << endl;
            uflag = 10;
            input = 0;
            break;

        default:
            cout << "Wrong input! Please try again." << endl;
            break;
        }

        if (uflag == 1) // Admin menu
        {
            input1 = 1;
            while (input1 != 0)
            {
                adminmenu();
                cout << "\tChoose an option: ";
                cin >> input1; //    Prompts User to Enter out of Eleven of Menu Options
                while (!cin)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    adminmenu();
                    cout << "\tChoose an option: ";
                    cin >> input1;
                }

                switch (input1)
                {
                case 1: // Add an Airbus
                {

                    adminbar();
                    adflag = 0;

                    for (int i = 0; i < 5; i++)
                    {
                        if (bus[i] == "0")
                        {
                            cin.ignore();
                            cout << setw(65) << "Enter Airbus Name: ";
                            getline(cin, bus[i]);
                            checkbus(bus[i]);

                            cout << setw(65) << "Enter Capacity: ";
                            cin >> capacity[i];
                            cin.ignore(256, '\n');
                            while (!cin || capacity[i] < 100 || capacity[i] > 1000)
                            {
                                if (!cin)
                                {
                                    cin.clear();
                                    cin.ignore(256, '\n');
                                }
                                cout << "Invalid capacity! Please enter a value between 100 and 1000.\n";
                                cout << setw(65) << "Enter Capacity:";
                                cin >> capacity[i];
                                cin.ignore(256, '\n');
                            }

                            cout << setw(65) << "Enter Departure Location: ";
                            getline(cin, departure[i]);
                            checkname(departure[i]);

                            cout << setw(65) << "Enter Destination: ";
                            getline(cin, destination[i]);
                            checkname(destination[i]);

                            cout << setw(65) << "Enter Departure Time: ";
                            getline(cin, deptime[i]);
                            checktime(deptime[i]);

                            cout << setw(65) << "Enter Arrival Time: ";
                            getline(cin, arrtime[i]);
                            checktime(arrtime[i]);

                            adflag = 1;
                            break;
                        }
                    }

                    if (adflag == 0)
                    {
                        cout << "No more space!" << endl;
                    }
                    breaking();
                    break;
                }
                case 2: // Delete an Airbus
                {

                    adminbar();
                    adflag = 0;
                    cin.ignore();
                    cout << setw(65) << "Enter Airbus you want to delete: ";
                    getline(cin, busname);
                    findindex1(bus, busname, adflag, k);
                    if (adflag == 1)
                    {
                        cout << setw(65) << "Do you really want to dalete(Y/N): ";
                        cin >> choice1;
                        if (choice1 == "Y" || choice1 == "y")
                        {
                            bus[k] = "0";
                            capacity[k] = 0;
                            departure[k] = "0";
                            destination[k] = "0";
                            deptime[k] = "0";
                            arrtime[k] = "0";
                            cout << "Bus was deleted Successfully!" << endl;
                        }
                        else if (choice1 == "N" || choice1 == "n")
                        {
                            cout << "No bus was deleted!" << endl;
                        }
                        else
                        {
                            cout << "Wrong Input" << endl;
                        }
                    }
                    else
                    {
                        cout << "No bus of such name is present!";
                    }
                    breaking();
                    break;
                }
                case 3: // Update an Airbus
                {
                    adflag = 0;
                    adminbar();
                    cin.ignore();
                    cout << setw(65) << "Enter bus name whose data is to be updated: ";
                    cin >> busname;
                    findindex1(bus, busname, adflag, k);
                    if (adflag == 1)
                    {
                        system("cls");
                        line();
                        cout << "\t\t\t\t\t\tUpdate a Bus" << endl;
                        line();
                        cout << endl
                             << endl;
                        cout << left;
                        cout << setw(20) << "\t\t1.Capacity";
                        cout << setw(20) << "2.Departure";
                        cout << setw(20) << "3.Destination";
                        cout << setw(20) << "4.Timings\n"
                             << endl;
                        cout << setw(20) << "\t\t0.Logout" << endl;
                        cout << "\tChoose an option: ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            cout << setw(65) << "Enter Capacity:";
                            cin >> capacity[k];
                            cout << "Data was updated successfully!" << endl;
                            break;
                        case 2:
                            cout << setw(65) << "Enter Departure: ";
                            cin >> departure[k];
                            checkname(departure[k]);
                            cout << "Data was updated successfully!" << endl;
                            break;
                        case 3:
                            cout << setw(65) << "Enter Destination: ";
                            cin >> destination[k];
                            checkname(destination[k]);
                            cout << "Data was updated successfully!" << endl;
                            break;
                        case 4:
                            cout << "Enter Departure Time:";
                            cin >> deptime[k];
                            checktime(deptime[k]);
                            cout << "Enter Destination Time:";
                            cin >> arrtime[k];
                            checktime(arrtime[k]);
                            cout << "Data was updated successfully!" << endl;
                            break;
                        case 0:
                            cout << "Looged out Successfully!" << endl;
                            break;
                        default:
                            cout << "Wrong Input";
                            break;
                        }
                    }
                    else
                    {
                        cout << "No airbus of such name found!" << endl;
                    }
                    breaking();
                    break;
                }
                case 4: // List of all Airbuses
                {

                    adflag = 0;
                    for (int i = 0; i < 5; i++)
                    {
                        if (bus[i] != "0")
                        {
                            adflag = 1;
                            break;
                        }
                    }

                    if (adflag == 1)
                    {
                        system("cls");
                        line();
                        cout << "\t\t\t\t\t\tList of Buses" << endl;
                        line();
                        cout << left;
                        cout << setw(20) << "Airbus" << setw(20) << "Capacity" << setw(20) << "Departure"
                             << setw(20) << "Destination" << endl;
                        line();
                        for (int i = 0; i < 5; i++)
                        {
                            if (bus[i] != "0"&&capacity[i]!=0)
                            {
                                cout << setw(20) << bus[i] << setw(20) << capacity[i] << setw(20) << departure[i]
                                     << setw(20) << destination[i] << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << "No Bus available!" << endl;
                    }
                    breaking();
                    break;
                }
                case 5: // Register a User

                {

                    adminbar();
                    cin.ignore();
                    for (int i = 0; i < 5; i++)
                    {
                        if (userid[i] == "0")
                        {
                            k = i;
                            break;
                        }
                    }
                    cout << setw(65) << "Enter Name: ";
                    getline(cin, name[k]);
                    checkname(name[k]);
                    checkname(name[k]);
                    cout << setw(69) << "Enter Contact No: +92 ";
                    getline(cin, tel[k]);
                    checktel(tel[k]);
                    cout << setw(65) << "Enter Age: ";
                    cin >> age[k];
                    checkage(age[k]);
                    cin.ignore(256, '\n');
                    if (age[k] < 1 || age[k] > 75)
                    {
                        name[k] = "0";
                        tel[k] = "0";
                        age[k] = 0;
                        cout << "Age must be between 1 and 75.Data has been reset!" << endl;
                    }
                    else
                    {
                        cout << setw(65) << "Enter User ID: ";
                        getline(cin, userid[k]);
                        checkname(name[k]);
                        if (k != 0)
                            for (int i = 0; i < k; i++)
                            {
                                if (userid[k] == userid[i])
                                {
                                    cout << "This ID has been already used. Plz use another one: ";
                                    getline(cin, userid[k]);
                                }
                            }

                        cout << setw(65) << "Enter password: ";
                        getline(cin, pass[k]);
                        checkpass(pass[k]);
                    }
                    cout << endl;
                    breaking();
                    break;
                }
                case 6: // Edit a User
                    system("cls");
                    adflag = 0;
                    line();
                    cout << "\t\t\t\t\t\tUser Info" << endl;
                    line();
                    cin.ignore();
                    cout << setw(65) << "Enter User ID: ";
                    getline(cin, user);
                    cout << setw(65) << "Enter User Password: ";
                    getline(cin, password);

                    findindex2(name, pass, user, password, adflag, k);

                    if (adflag == 1)
                    {
                        system("cls");
                        choice1 = "Y";
                        line();
                        cout << "\t\t\t\t\t\tUser Info" << endl;
                        line();
                        cout << left;

                        while (choice1 == "Y" || choice1 == "y")
                        {
                            cout << setw(20) << "\t1.Name" << setw(20) << "2.Age" << setw(20) << "3.Telephone" << setw(20) << "4.ID\n"
                                 << endl;
                            cout << setw(20) << "\t5.Password" << setw(60) << "0.Logout\n"
                                 << endl;
                            cout << "Choose an option: ";
                            cin >> choice;
                            cin.ignore();

                            switch (choice)
                            {
                            case 1:
                                cout << setw(65) << "Enter Name: ";
                                getline(cin, name[k]);
                                checkname(name[k]);
                                break;
                            case 2:
                                cout << setw(65) << "Enter Age: ";
                                cin >> age[k];
                                checkage(age[k]);
                                break;
                            case 3:
                                cout << setw(65) << "Enter Tel.: ";
                                getline(cin, tel[k]);
                                checktel(tel[k]);
                                break;
                            case 4:
                                cout << setw(65) << "Enter ID: ";
                                getline(cin, userid[k]);
                                checkid(userid[k]);
                                break;
                            case 5:
                                cout << setw(65) << "Enter Password: ";
                                getline(cin, pass[k]);
                                break;
                            case 0:
                                cout << "Logged out Successfully!" << endl;
                                choice1 = "N";
                                break;
                            default:
                                cout << "Wrong Input!" << endl;
                                break;
                            }

                            if (choice != 0)
                            {
                                cout << "Want to perform more changes (Y/N): ";
                                getline(cin, choice1);
                            }
                        }
                    }
                    else
                    {
                        cout << "Invalid ID or password!!" << endl;
                        breaking();
                    }
                    break;
                case 7: // Delete a User
                {
                    system("cls");
                    line();

                    adminbar();
                    line();
                    adflag = 0;
                    cin.ignore();
                    cout << setw(65) << "Enter User ID you want to delete: ";
                    getline(cin, user);
                    checkid(user);
                    cout << setw(65) << "Enter Password: ";
                    getline(cin, password);
                    checkpass(password);
                    findindex2(name, pass, user, password, adflag, k);
                    if (adflag == 1)
                    {
                        cout << setw(65) << "Do you really want to dalete(Y/N): ";
                        cin >> choice1;
                        if (choice1 == "Y" || choice1 == "y")
                        {
                            name[k] = "0";
                            for (int i = 0; i < 5; i++)
                            {
                                seat[k][i] = 0;
                                bookbus[k][i] = "0";
                            }
                            bookings[k] = 0;
                            userid[k] = "0";
                            tel[k] = "0";
                            age[k] = -1;
                            cout << "User deleted successfully!<<endl";
                        }
                        else if (choice1 == "N" || choice1 == "n")
                        {
                            cout << "No ID was deleted!" << endl;
                        }
                        else
                        {
                            cout << "Wrong Input" << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid ID or Password!";
                    }
                    breaking();

                    break;
                }
                case 8: // List of All Flights
                {

                    adflag = 0;
                    for (int i = 0; i < 5; i++)
                    {
                        if (bus[i] != "0")
                        {
                            adflag = 1;
                            break;
                        }
                    }

                    if (adflag == 1)
                    {
                        system("cls");
                        line();
                        cout << "\t\t\t\t\t\tList of Flights" << endl;
                        line();
                        cout << left;
                        cout << setw(20) << "Airbus" << setw(20) << "Departure" << setw(20) << "Destination"
                             << setw(20) << "Departure Time" << setw(20) << "Arrival Time" << endl;

                        line();
                        for (int i = 0; i < 5; i++)
                        {
                            if (bus[i] != "0"&&capacity[i]!=0)
                            {
                                cout << setw(20) << bus[i] << setw(20) << departure[i] << setw(20) << destination[i]
                                     << setw(20) << deptime[i] << setw(20) << arrtime[i] << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << "No Bus available!" << endl;
                    }
                    breaking();
                    break;
                }
                case 9: // Book a Ticket for User
                {
                    line();
                    adminbar();
                    line();
                    cin.ignore();

                    bool flag = false;

                    cout << setw(65) << "Enter User ID: ";
                    getline(cin, user);
                    checkid(user);
                    cout << setw(65) << "Enter Password: ";
                    getline(cin, password);
                    checkpass(password);

                    adflag = 0;

                    findindex2(userid, pass, user, password, adflag, k);

                    if (adflag == 1)
                    {
                        cout << setw(65) << "Enter Departure: ";
                        getline(cin, dep);
                        cout << setw(65) << "Enter Destination: ";
                        getline(cin, des);
                        system("cls");

                        cout << left;
                        cout << setw(15) << "Airbus" << setw(15) << "Departure"
                             << setw(15) << "Destination" << setw(15) << "Dep.Time"
                             << setw(15) << "Arr.Time" << endl;

                        for (int i = 0; i < 5; i++)
                        {
                            if (dep == departure[i] && des == destination[i])
                            {
                                flag = true;
                                cout << setw(15) << bus[i] << setw(15) << departure[i]
                                     << setw(15) << destination[i] << setw(15) << deptime[i]
                                     << setw(15) << arrtime[i] << endl;
                            }
                        }

                        if (flag)
                        {
                            cout << "Enter Airbus in which you want to travel: ";
                            getline(cin, busname);

                            bool busFound = false;

                            bool alreadyBooked = false;
                            for (int i = 0; i < 5; i++)
                            {
                                if (bookbus[k][i] == busname)
                                {
                                    alreadyBooked = true;
                                    break;
                                }
                            }

                            if (alreadyBooked)
                            {
                                cout << "You have already booked this bus." << endl;
                            }
                            else
                            {
                                for (int i = 0; i < 5; i++)
                                {
                                    if (busname == bus[i])
                                    {
                                        busFound = true;

                                        if (capacity[i] > 0)
                                        {
                                            for (int j = 0; j < 5; j++)
                                            {
                                                if (bookbus[k][j] == "")
                                                {
                                                    bookbus[k][j] = busname;
                                                    seat[k][j] = capacity[i];
                                                    capacity[i]--;
                                                    bookings[i]++;
                                                    cout << "Your seat has been booked." << endl;
                                                    cout << "Your seat number is: " << seat[k][j] << endl;
                                                    break;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            cout << "No seats available in this airbus." << endl;
                                        }
                                        break;
                                    }
                                }

                                if (!busFound)
                                {
                                    cout << "Wrong Bus Name." << endl;
                                }
                            }
                        }
                        else
                        {
                            cout << "No airbus available for the route." << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid ID or Password!" << endl;
                    }

                    breaking();
                    break;
                }
                case 10: // Cancel a User's Booking
                {
                    line();
                    adminbar();
                    line();
                    cin.ignore();

                    cout << setw(65) << "Enter User ID: ";
                    getline(cin, user);
                    cout << setw(65) << "Enter Password: ";
                    getline(cin, password);

                    adflag = 0;

                    findindex2(userid, pass, user, password, adflag, k);

                    if (adflag == 1)
                    {
                        system("cls");

                        cout << left;
                        line();
                        cout << setw(15) << "Airbus" << setw(15) << "Departure"
                             << setw(15) << "Destination" << setw(15) << "Dep.Time"
                             << setw(15) << "Arr.Time" << endl;

                        line();
                        bool flag = false;
                        for (int i = 0; i < 5; i++)
                        {
                            for (int j = 0; j < 5; j++)
                            {
                                if (bookbus[k][j] == bus[i])
                                {
                                    flag = true;
                                    cout << setw(15) << bus[i] << setw(15) << departure[i]
                                         << setw(15) << destination[i] << setw(15) << deptime[i]
                                         << setw(15) << arrtime[i] << endl;
                                    cout << "Seat Number: " << seat[k][j] << endl;
                                }
                            }
                        }

                        if (flag)
                        {
                            cout << "Do you really want to cancel Booking (Y / N)?: ";
                            getline(cin, choice1);

                            if (choice1 == "Y" || choice1 == "y")
                            {
                                cout << "Flight cancelled successfully!" << endl;

                                for (int i = 0; i < 5; i++)
                                {
                                    for (int j = 0; j < 5; j++)
                                    {
                                        if (bookbus[k][j] == bus[i])
                                        {
                                            bookbus[k][j] = "";
                                            seat[k][j] = 0;
                                            bookings[i]--;
                                            capacity[i]++;
                                            break;
                                        }
                                    }
                                }
                            }
                            else if (choice1 == "N" || choice1 == "n")
                            {
                                cout << "No flight was cancelled" << endl;
                            }
                            else
                            {
                                cout << "Wrong Input!" << endl;
                            }
                        }
                        else
                        {
                            cout << "No flights found!" << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid ID or Password!" << endl;
                    }

                    breaking();
                    break;
                }

                case 0: // Logout
                {

                    system("cls");
                    cout << "Logged out Successfully!" << endl;
                    input1 = 0;
                    break;
                }
                default:
                    cout << "Wrong Input!" << endl;
                    break;
                }
            }
        }
        else if (uflag == 2) // User menu
        {
            input1 = 1;
            while (input1 != 0)
            {
                usermenu(); // Display user menu
                cout << endl
                     << "\tChoose an option: ";
                cin >> input1; // Prompt user to enter an option
                while (!cin)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << endl
                         << "\tChoose an option: ";
                    cin >> input1;
                }

                switch (input1)
                {
                case 1: // Book a Ticket
                {
                    system("cls");
                    line();
                    cout << "\t\t\t\t\tBook a Flight" << endl;
                    line();
                    cout << endl
                         << setw(65) << "Enter Departure Location: ";
                    cin >> dep;
                    cout << setw(65) << "Enter Destination Location: ";
                    cin >> des;

                    bool busav = false;
                    system("cls");

                    cout << left;
                    line();
                    cout << setw(15) << "\tBus Name"
                         << setw(20) << "Departure Time"
                         << setw(20) << "Arrival Time"
                         << setw(15) << "Available Seats" << endl;
                    line();
                    for (int i = 0; i < 5; i++)
                    {
                        if (departure[i] == dep && destination[i] == des)
                        {
                            cout << "\t" << setw(15) << bus[i]
                                 << setw(20) << deptime[i]
                                 << setw(20) << arrtime[i]
                                 << setw(15) << capacity[i] << endl;
                            busav = true;
                        }
                    }

                    if (!busav)
                    {
                        cout << "No buses available for this route." << endl;
                    }
                    else
                    {
                        cout << "\nEnter the Bus Name to book a ticket: ";
                        cin >> busname;

                        bool flag = false;
                        bool alreadyBooked = false;

                        // Check if the user has already booked this bus
                        for (int i = 0; i < 5; i++)
                        {
                            if (bookbus[k][i] == busname)
                            {
                                alreadyBooked = true;
                                break;
                            }
                        }

                        if (alreadyBooked)
                        {
                            cout << "You have already booked this bus." << endl;
                        }
                        else
                        {
                            // Check if the bus exists and if there are available seats
                            for (int i = 0; i < 5; i++)
                            {
                                if (bus[i] == busname)
                                {
                                    flag = true;

                                    if (capacity[i] > 0)
                                    {

                                        for (int j = 0; j < 5; j++)
                                        {
                                            if (bookbus[k][j] == "")
                                            {
                                                bookbus[k][j] = busname;
                                                capacity[i]--;
                                                seat[k][j] = capacity[i];
                                                cout << "Ticket successfully booked!" << endl;
                                                cout << "Your seat number is " << seat[k][j] << "." << endl;
                                                break;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        cout << "No available seats on this flight!" << endl;
                                    }
                                    break;
                                }
                            }

                            if (!flag)
                            {
                                cout << "Invalid bus name entered!" << endl;
                            }
                        }
                    }
                    breaking();
                    break;
                }

                case 2: // Cancel a Booking
                {
                    system("cls");
                    line();
                    cout << "\t\t\t\t\tCancel a Flight" << endl;
                    line();
                    cout << setw(65) << "Enter Bus Name from which you want to cancel booking: ";
                    cin >> busname;

                    bool flag = false;
                    bool foundBooking = false;

                    for (int i = 0; i < 5; i++)
                    {
                        if (bookbus[k][i] == busname)
                        {
                            foundBooking = true;
                            bookbus[k][i] = "";
                            seat[k][i] = 0;
                            flag = true;

                            for (int j = 0; j < 5; j++)
                            {
                                if (bus[j] == busname)
                                {
                                    capacity[j]++;
                                    break;
                                }
                            }

                            cout << "Your booking has been canceled!" << endl;
                            break;
                        }
                    }

                    if (!foundBooking)
                    {
                        cout << "No booking found for the bus." << endl;
                    }
                    breaking();
                    break;
                }

                case 3: // View all Bookings
                {
                    system("cls");
                    line();
                    cout << "\t\t\t\t\tBookings" << endl;
                    line();
                    cout << "Your current bookings: " << endl;
                    bool flag = false;

                    system("cls");
                    line();
                    cout << "\t\t\t\t\tBookings" << endl;
                    line();
                    cout << setw(15) << "Bus Name"
                         << setw(20) << "Departure Time"
                         << setw(20) << "Arrival Time"
                         << setw(15) << "Seat Number" << endl;

                    line();
                    for (int i = 0; i < 5; i++)
                    {
                        if (bookbus[k][i] != "")
                        {
                            for (int j = 0; j < 5; j++)
                            {
                                if (bookbus[k][i] == bus[j])
                                {
                                    cout << setw(15) << bus[j]
                                         << setw(20) << deptime[j]
                                         << setw(20) << arrtime[j]
                                         << setw(15) << seat[k][i] << endl;
                                }
                            }
                        }
                    }

                    if (!flag)
                    {
                        cout << "You have no bookings yet." << endl;
                    }

                    breaking();
                    break;
                }

                case 4: // List of all Flights
                {
                    adflag = 0;
                    for (int i = 0; i < 5; i++)
                    {
                        if (bus[i] != "0")
                        {
                            adflag = 1;
                            break;
                        }
                    }

                    if (adflag == 1)
                    {
                        system("cls");
                        line();
                        cout << "\t\t\t\t\t\tList of Flights" << endl;
                        line();
                        cout << left;
                        cout << setw(20) << "Airbus" << setw(20) << "Departure" << setw(20) << "Destination"
                             << setw(20) << "Departure Time" << setw(20) << "Arrival Time" << endl;

                        for (int i = 0; i < 5; i++)
                        {
                            if (bus[i] != "0"&&capacity[i]!=0)
                            {
                                cout << setw(20) << bus[i] << setw(20) << departure[i] << setw(20) << destination[i]
                                     << setw(20) << deptime[i] << setw(20) << arrtime[i] << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << "No Flights available!" << endl;
                    }
                    breaking();
                    break;
                }
                case 5: // View Available Flights
                {
                    system("cls");
                    line();
                    cout << "\t\t\t\t\t\tList of Flights" << endl;
                    line();
                    adflag = 0;

                    cout << setw(65) << "Enter Departure Location: ";
                    cin >> dep;
                    cout << setw(65) << "Enter Destination Location: ";
                    cin >> des;

                    system("cls");
                    line();
                    cout << "\nAvailable flights from " << dep << " to " << des << ":" << endl;
                    line();
                    cout << left;
                    cout << setw(15) << "Airbus Name"
                         << setw(20) << "Departure Time"
                         << setw(20) << "Arrival Time"
                         << setw(15) << "Available Seats" << endl;
                    line();

                    for (int i = 0; i < 5; i++)
                    {
                        if (departure[i] == dep && destination[i] == des && bus[i] != "0" && capacity[i] > 0)
                        {
                            cout << setw(15) << bus[i]
                                 << setw(20) << deptime[i]
                                 << setw(20) << arrtime[i]
                                 << setw(15) << capacity[i] << endl;
                            adflag = 1;
                        }
                    }

                    if (adflag == 0)
                    {
                        cout << "No flights available from " << dep << " to " << des << endl;
                    }

                    breaking();
                    break;
                }
                case 6: // Show Flight Capacity
                {
                    system("cls");
                    line();
                    cout << "\t\t\t\t\t\tFlights Capacity" << endl;
                    line();
                    cout << setw(65) << "Enter Flight Bus Name to check capacity: ";
                    cin >> busname;
                    findindex1(bus, busname, uflag, k);
                    if (!uflag)
                        cout << "Flight " << bus[k] << " has no empty Seats." << endl;
                    breaking();
                    break;
                }
                case 7: // Search Flights by Destination case
                {
                    system("cls");
                    line();
                    cout << "\t\t\t\t\t\tFlights Capacity" << endl;
                    line();

                    cin.ignore();
                    cout << setw(65) << "Enter Departure:";
                    getline(cin, dep);
                    checkname(dep);
                    cout << setw(65) << "Enter destination: ";
                    getline(cin, des);
                    checkname(des);
                    adflag = 0;
                    for (int i = 0; i < 5; i++)
                    {
                        if (destination[i] == des && departure[i] == dep && bus[i] != "0")
                        {
                            adflag = 1;
                            cout << "Flight to " << des << ": " << bus[i] << ", Departure Time: " << deptime[i] << ", Arrival Time: " << arrtime[i] << endl;
                        }
                    }

                    if (adflag == 0)
                    {
                        cout << "No available flights to " << des << endl;
                    }
                    breaking();
                    break;
                }
                case 0:
                    system("cls");
                    cout << "Logged out Successfully!" << endl;
                    input1 = 0;
                    break;

                default:
                    cout << "Wrong Input!" << endl;
                    break;
                }
            }
        }
        else if (uflag == 3 || uflag == 4)
        {
            system("cls");
            line();
            cout << "\t\t\t\t\t\tSign In Menu" << endl;
            line();
            cout << left << endl;

            cout << endl
                 << "Welcome to Skyways" << endl;
            cout << "                  In order to Register" << endl;
            cout << "                                      Plz Fill in the Required Data" << endl
                 << endl;
            cout << right;
            if (uflag == 3)
            {

                cin.ignore();
                cout << setw(65) << "Enter Name: ";
                getline(cin, name[k]);
                checkname(name[k]);
                cout << setw(69) << "Enter Contact No: +92 ";
                getline(cin, tel[k]);
                checktel(tel[k]);
                cout << setw(65) << "Enter Age: ";
                cin >> age[k];
                checkage(age[k]);
                if (age[k] < 1 || age[k] > 75)
                {
                    cout << "Age must be between 1 and 75. Data has been reset.\n";
                    name[k] = "0";
                    tel[k] = "0";
                    userid[k] = "0";
                    age[k] = 0;
                }
                else
                {
                    cin.ignore();

                    cout << setw(65) << "Enter User ID: ";
                    getline(cin, userid[k]);
                    checkid(userid[k]);

                    for (int i = 0; i < k; i++)
                    {
                        if (k != 0)
                        {
                            if (userid[k] == userid[i])
                            {
                                cout <<setw(65)<< "This ID has been already used. Please use another one: ";
                                getline(cin, userid[k]);
                                checkid(userid[k]);
                            }
                        }
                    }
                    cout << setw(65) << "Enter password: ";
                    getline(cin, pass[k]);
                    checkpass(pass[k]);
                }
            }

            if (uflag == 4)
            {
                cout << "Network Issue !Please Try Again Later";
            }
            else if (age[k] != 0)
            {
                cout << "The user has signed in Successfully!";
            }
            cout << "\n\nPress any key to Continue: ";
            cin.ignore();
            cin.get();
            system("cls");
        }
        else if (uflag == 0)
        {
            system("cls");
            cout << "You've entered Invalid Credentials!\n\n\n";
        }
    } while (input != 0);
    storedatauser(name, tel, userid, pass, bookings, bookbus, seat);
    storedatabus(bus, departure, deptime, destination, arrtime, capacity);
    return 0;
}
void logo() //    Made a Separate Logo Function to make "MAIN FUNCTION" Readible!
{
    cout << "                                                        |                              " << endl;
    cout << "                                                        |      Airbus                        " << endl;
    cout << "                                                      .-'-.          Management                  " << endl;
    cout << "                                                     '(___)'                   System        " << endl;
    cout << "                                           ---------'  .-.  '---------                 " << endl;
    cout << "                           _________________________'  '-'  '_________________________ " << endl;
    cout << "                             ''''''-|---|--/   \\==][^',_m_,'^][==/   \\--|---|-''''''  " << endl;
    cout << "                                           \\   /  ||/   H  \\||   \\   /                " << endl;
    cout << "                                           '--'   OO   O|O   OO   '--'                 " << endl;
    cout << endl
         << endl
         << endl;
    cout << "\t\t  1. Login as Admin\t\t2. Login as User\t\t3. Sign in as User\n\n"
         << setw(88) << "  0.logout" << endl
         << endl;
}
void adminbar()
{
    system("cls");
    cout << "************************************************************************************************************************" << endl;
    cout << "\t\t\t\t\t\tADMIN MENU" << endl;
    cout << "************************************************************************************************************************" << endl;
}
void adminmenu()
{
    system("cls");
    adminbar();
    cout << left << endl
         << endl;
    cout << setw(25) << "\t1. Add an Airbus"
         << setw(25) << "2. Delete an Airbus"
         << setw(25) << "3. Update an Airbus"
         << setw(25) << "4. List of all Airbuses" << endl
         << endl;

    cout << setw(25) << "\t5. Register a user"
         << setw(25) << "6. Edit a user"
         << setw(25) << "7. Delete a user"
         << setw(25) << "8. List of all Flights" << endl
         << endl;

    cout << setw(50) << "\t9. Book a Ticket for User on a Flight"
         << setw(25) << "10. Cancel Ticket"
         << setw(25) << "0. Logout" << endl
         << endl;

    cout.unsetf(ios::left);
}
void usermenu()
{
    system("cls");
    cout << "************************************************************************************************************************" << endl;
    cout << "\t\t\t\t\t\tUSER MENU" << endl;
    cout << "************************************************************************************************************************" << endl;
    cout << left << endl
         << endl;
    cout << setw(40) << "\t1. Book a Ticket"
         << setw(40) << "2. Cancel a Booking" << endl
         << endl
         << setw(40) << "\t3. View all Bookings"
         << setw(40) << "4. List of all Flights" << endl
         << endl
         << setw(40) << "\t5. View Available Flights"
         << setw(40) << "6. Show Flight Capacity" << endl
         << endl
         << setw(40) << "\t7. Search Flights by Destination"
         << setw(40) << "0.Logout" << endl;

    cout.unsetf(ios::left);
    cout << endl;
}
void breaking()
{
    cout << "\n\nPress any key to Continue: ";
    cin.ignore();
    cin.get();
    system("cls");
}
void line()
{
    cout << "************************************************************************************************************************" << endl;
}
void checkname(string &name)
{
    while (true)
    {
        bool flag = true;

        if (name[0] < 'A' || name[0] > 'Z')
        {
            flag = false;
        }

        for (int i = 1; i < name.length(); i++)
        {
            if (name[i] == ' ')
            {
                if (name[i + 1] >= 'A' && name[i + 1] <= 'Z')
                {
                    i++;
                }
                else flag=false;
            }
            else if (name[i] < 'a' || name[i] > 'z')
            {
                flag = false;
                break;
            }
        }
        if (name == "")
            flag = false;

        if (flag)
        {
            break;
        }
        else
        {
            cout << setw(65) << "Invalid Name. Enter name again: ";
            getline(cin, name);
        }
    }
}
void checkage(int &age)
{
    while (true)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
            cin >> age;
        }
        else
        {
            break;
        }
    }
    if (age < 1 || age > 75)
    {
        cout << "You are ineligible to book a ticket!";
    }
}
void checkid(string &id)
{
    string c = "skyways.pk";
    bool flag = false;

    while (true)
    {
        if (id.length() > c.length())
        {
            flag = true;
            for (int i = 0; i < c.length(); i++)
            {
                if (id[id.length() - c.length() + i] != c[i])
                {
                    flag = false;
                    break;
                }
            }
        }
        else flag=false;
        if (flag)
        {
            break;
        }
        else
        {
            cout << setw(65) << "Wrong ID! Enter ID again: ";
            cin >> id;
        }
    }
}
void checktel(string &tel)
{
    bool flag = true;
    while (true)
    {
        flag = true;
        if (tel == "")
            flag = false;
        if (tel.length() != 10)
        {
            flag = false;
        }
        for (int i = 0; i < tel.length(); i++)
        {
            if (tel[i] < '0' || tel[i] > '9')
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            break;
        }
        else
        {
            cout << setw(65) << "Invalid Phone number! Enter number Again: +92 ";
            getline(cin, tel);
        }
    }
}
void checktime(string &time)
{
    while (true)
    {
        bool flag = true;
        if (time == "")
            flag = false;

        if (time.length() != 5 || time[2] != ' ')
        {
            flag = false;
        }
        else
        {
            if (time[0] < '0' || time[0] > '2' || (time[0] == '2' && time[1] > '3') || time[1] < '0' || time[1] > '9' || time[3] < '0' || time[3] > '5' || time[4] < '0' || time[4] > '9')
            {
                flag = false;
            }
        }

        if (flag)
        {
            break;
        }
        else
        {
            cout << setw(65) << "Invalid time format. Enter again (Hh Mm): ";
            getline(cin, time);
        }
    }
}
void checkpass(string &pass)
{
    bool flag = true;
    while (true)
    {
        flag = true;
        for (int i = 0; i < pass.length(); i++)
        {
            if (!((pass[i] >= 'A' && pass[i] <= 'Z') ||
                  (pass[i] >= 'a' && pass[i] <= 'z') ||
                  (pass[i] >= '0' && pass[i] <= '9')))
            {
                cout << setw(65) << "Password should only consist of letters and numbers. Enter Again:";
                getline(cin, pass);
                flag = false;
            }
        }
        if (pass.length() <= 3)
        {
            cout << setw(65) << "Password is short!.Enter Password Again: ";
            getline(cin, pass);
            flag = false;
        }
        if (flag)
            break;
    }
}
void checkbus(string &bus){
	bool flag;
	while(true){
		flag=true;
		if(bus.length()<4||bus.length()>6){
			flag=false;
		}
		if(bus=="")flag=false;
		if(bus[0]<'A'||bus[0]>'Z')flag=false;
		for(int i=0;i<bus.length();i++){
			if(!(bus[i]>='0'&&bus[i]<='9'||bus[i]>='A'&&bus[i]<='Z'))
		            flag=false;
		    if(!flag)break;
		}
		if(flag)break;
		else{
			cout<<setw(65)<<"Invalid Airbus name.Enter name again: ";
			getline(cin,bus);
		}
	}
	
}
void findindex1(string name[], string name1, int &adflag, int &k)
{
    adflag = 0;
    k = -1;
    for (int i = 0; i < 5; i++)
    {
        if (name[i] == name1)
        {
            adflag = 1;
            k = i;
            break;
        }
    }
}
void findindex2(string name[], string pass[], string name1, string password, int &adflag, int &k)
{
    adflag = 0;
    k = -1;
    for (int i = 0; i < 5; i++)
    {
        if (name[i] == name1 && password == pass[i])
        {
            adflag = 1;
            k = i;
            break;
        }
    }
}

void storedatauser(string name[], string tel[], string userid[], string pass[],
                   int bookings[], string bookbus[][5], int seat[][5])
{
    ofstream fout;
    fout.open("users.txt");

    if (!fout)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    for (int k = 0; k < 5; k++)
    {
        if (name[k] != "0"&&userid[k]!="0")
        {
            fout << name[k] << "," << tel[k] << "," << userid[k] << ","
                 << pass[k] << "," << bookings[k] << ",";

            if (bookings[k] != 0)
            {
                for (int i = 0; i < bookings[k]; i++)
                {
                    fout << bookbus[k][i] << "," << seat[k][i] << ",";
                }
            }

            fout << endl;
        }
    }

    fout.close();
}
bool loaddatauser(string name[], string tel[], string userid[], string pass[],
                  int bookings[], string bookbus[][5], int seat[][5])
{
    ifstream fin("users.txt");
    if (!fin)
    {
        cout << "Error opening file!" << endl;
        return false;
    }

    int k = 0;

    while (getline(fin, name[k], ','))
    {
        if (k >= 5 || name[k].empty()){
            name[k]="0";
            break;}

        getline(fin, tel[k], ',');
        getline(fin, userid[k], ',');
        getline(fin, pass[k], ',');
        fin >> bookings[k];
        if (fin.fail())
        {
            bookings[k] = 0;
            fin.clear();
        }
        fin.ignore();

        for (int i = 0; i < bookings[k]; i++)
        {
            getline(fin, bookbus[k][i], ',');
            fin >> seat[k][i];
            fin.ignore();
        }
        k++;
    }

    fin.close();
    return true;
}

void storedatabus(string bus[], string departure[], string deptime[], string destination[], string arrtime[], int capacity[])
{
    ofstream fout;
    fout.open("airbuses.txt");

    if (!fout)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    for (int k = 0; k < 5; k++)
    {
        if (bus[k] != "0")
        {
            fout << bus[k] << "," << departure[k] << "," << deptime[k] << ","
                 << destination[k] << "," << arrtime[k] << "," << capacity[k];

            fout << endl;
        }
    }

    fout.close();
}
bool loaddatabus(string bus[], string departure[], string deptime[], string destination[], string arrtime[], int capacity[])
{
    ifstream fin("airbuses.txt");
    if (!fin)
    {
        cout << "Error opening file!" << endl;
        return false;
    }

    int k = 0;

    while (getline(fin, bus[k], ','))
    {
        if (k >= 5 || bus[k].empty()){
            bus[k]="0";
            break;
		}
        getline(fin, departure[k], ',');
        getline(fin, deptime[k], ',');
        getline(fin, destination[k], ',');
        getline(fin, arrtime[k], ',');
        fin >> capacity[k];
        if (fin.fail())
        {
            capacity[k] = 0;
            fin.clear();
        }
        fin.ignore();
		
        k++;
    }

    fin.close();
    return true;
}

