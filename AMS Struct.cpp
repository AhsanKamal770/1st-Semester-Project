#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct airbus
{
    string busname;
    int capacity;
    string departure, deptime, destination, arrtime;
};

struct u_er
{
    string name, tel, bookbus[5], userid, pass;
    int age, seat[5], bookings;
};

void logo();      // Logo Of Management System
void adminmenu(); // Displays Admin Menu
void usermenu();  // Displays User Menu
void adminbar();  // Displays Admin Bar
void breaking();  // Pauses system("cls") function
void line();      // Prints a Line

bool loaddatabus(airbus buses[], int size);  // File Handling Functions
void storedatabus(airbus buses[], int size); 
bool loaddatauser(u_er users[], int size);   
void storedatauser(u_er users[], int size);  

void findindex1(u_er users[], string name1, int &adflag, int &k);
void findindex2(u_er users[], string name1, string password, int &adflag, int &k);

void checkage(int &age);           
void checkpass(string &pass);
void checktel(string &tel);
void checkid(string &id);
void checkname(string &name);
void checktime(string &time);
void checkbus(string &bus);

int main()
{
    airbus buses[5];
    u_er users[5];

    // Initialize buses and users
    for (int i = 0; i < 5; i++)
    {
        buses[i].busname = "0";buses[i].capacity = 0;buses[i].departure = "0";buses[i].deptime = "0";buses[i].destination = "0";buses[i].arrtime = "0";
		users[i].name = "0";users[i].age=-1;users[i].bookings=0;users[i].pass="0";users[i].userid="0";
		for (int k=0;k<5;k++){
			users[i].bookbus[k]="0";users[i].seat[k]=-1;
		}
		}

    loaddatabus(buses, 5);
    loaddatauser(users, 5);

    int input, input1, choice;
    string password, choice1;
    int uflag, k, adflag;
    string user, busname, dep, des;

    do
    {
        input = 1, input1 = 1;
        uflag = 0, adflag = 0;
        logo();
        cout << "Choose an option: "; // Prompts User to Enter out of Three of Menu Options
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
        {
            string user, password;
            cout << setw(65) << "Enter User ID: ";
            cin.ignore(256, '\n');
            getline(cin, user);
            cout << setw(65) << "Enter Password: ";
            cin >> password;

            bool found = false;
            for (int i = 0; i < 5; i++) // Loop to Check For user
            {
                if (users[i].userid == user && users[i].pass == password)
                {
                    uflag = 2;
                    k = i;
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                uflag = 0;
            }
            break;
        }
        case 3: // User Registration
        {
            bool flag = false;
            for (int i = 0; i < 5; i++)
            {
                if (users[i].userid == "0") // Check for empty spot in users array
                {
                    uflag = 3;
                    k = i;
                    flag = true;
                    break;
                }
                else
                {
                    uflag = 4;
                }
            }

            if (!flag)
            {
                cout << "Registration is full. Please try again later.\n";
            }
            break;
        }

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

        if (uflag == 1)
        { // Admin menu
            input1 = 1;
            while (input1 != 0)
            {
                adminmenu();
                cout << "\tChoose an option: ";
                cin >> input1;
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
                case 1:
                { // Add an Airbus
                    adminbar();
                    adflag = 0;

                    for (int i = 0; i < 5; i++)
                    {
                        if (buses[i].busname == "0")
                        {
                            cin.ignore();
                            cout << setw(65) << "Enter Airbus Name: ";
                            getline(cin, buses[i].busname);
                            checkbus(buses[i].busname);

                            cout << setw(65) << "Enter Capacity: ";
                            cin >> buses[i].capacity;
                            cin.ignore(256, '\n');
                            while (!cin || buses[i].capacity < 100 || buses[i].capacity > 1000)
                            {
                                if (!cin)
                                {
                                    cin.clear();
                                    cin.ignore(256, '\n');
                                }
                                cout << "Invalid capacity! Please enter a value between 100 and 1000.\n";
                                cout << setw(65) << "Enter Capacity: ";
                                cin >> buses[i].capacity;
                                cin.ignore(256, '\n');
                            }

                            cout << setw(65) << "Enter Departure Location: ";
                            getline(cin, buses[i].departure);
                            checkname(buses[i].departure);

                            cout << setw(65) << "Enter Destination: ";
                            getline(cin, buses[i].destination);
                            checkname(buses[i].destination);

                            cout << setw(65) << "Enter Departure Time: ";
                            getline(cin, buses[i].deptime);
                            checktime(buses[i].deptime);

                            cout << setw(65) << "Enter Arrival Time: ";
                            getline(cin, buses[i].arrtime);
                            checktime(buses[i].arrtime);

                            adflag = 1;
                            break;
                        }
                    }

                    if (adflag == 0)
                    {
                        cout << "No more space to add buses!" << endl;
                    }
                    breaking();
                    break;
                }
                case 2:
                { // Delete an Airbus
                    adminbar();
                    adflag = 0;
                    cin.ignore();
                    cout << setw(65) << "Enter Airbus you want to delete: ";
                    getline(cin, busname);
                    for (int i = 0; i < 5; i++)
                    {
                        if (buses[i].busname == busname)
                        {
                            cout << setw(65) << "Do you really want to delete (Y/N): ";
                            cin >> choice1;
                            if (choice1 == "Y" || choice1 == "y")
                            {
                                buses[i].busname = "0";buses[i].capacity = 0;buses[i].departure = "0";buses[i].deptime = "0";buses[i].destination = "0";buses[i].arrtime = "0";
		                        cout << "Bus was deleted successfully!" << endl;
                            }
                            else if (choice1 == "N" || choice1 == "n")
                            {
                                cout << "No bus was deleted!" << endl;
                            }
                            else
                            {
                                cout << "Invalid input!" << endl;
                            }
                            adflag = 1;
                            break;
                        }
                    }
                    if (adflag == 0)
                    {
                        cout << "No bus with such name found!" << endl;
                    }
                    breaking();
                    break;
                }
                case 3:
                { // Update an Airbus
                    adminbar();
                    adflag = 0;
                    cin.ignore();
                    cout << setw(65) << "Enter Airbus name to update: ";
                    getline(cin, busname);
                    for (int i = 0; i < 5; i++)
                    {
                        if (buses[i].busname == busname)
                        {
                            cout << "\nSelect data to update:\n";
                            cout << "\t1. Capacity\n";
                            cout << "\t2. Departure Location\n";
                            cout << "\t3. Destination\n";
                            cout << "\t4. Timings\n";
                            cout << "\t0. Exit\n";
                            cout << "Enter your choice: ";
                            cin >> choice;

                            switch (choice)
                            {
                            case 1:
                                cout << "Enter new Capacity: ";
                                cin >> buses[i].capacity;
                                break;
                            case 2:
                                cin.ignore();
                                cout << "Enter new Departure Location: ";
                                getline(cin, buses[i].departure);
                                break;
                            case 3:
                                cin.ignore();
                                cout << "Enter new Destination: ";
                                getline(cin, buses[i].destination);
                                break;
                            case 4:
                                cin.ignore();
                                cout << "Enter new Departure Time: ";
                                getline(cin, buses[i].deptime);
                                cout << "Enter new Arrival Time: ";
                                getline(cin, buses[i].arrtime);
                                break;
                            case 0:
                                cout << "Exiting update menu.\n";
                                break;
                            default:
                                cout << "Invalid choice!" << endl;
                                break;
                            }
                            cout << "Data updated successfully!" << endl;
                            adflag = 1;
                            break;
                        }
                    }
                    if (adflag == 0)
                    {
                        cout << "No bus with such name found!" << endl;
                    }
                    breaking();
                    break;
                }
                case 4: // List of all Airbuses
                {
                    adflag = 0;
                    for (int i = 0; i < 5; i++)
                    {
                        if (buses[i].busname != "0")
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
                            if (buses[i].busname != "0" && buses[i].capacity != 0)
                            {
                                cout << setw(20) << buses[i].busname << setw(20) << buses[i].capacity
                                     << setw(20) << buses[i].departure << setw(20) << buses[i].destination << endl;
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
                        if (users[i].userid == "0")
                        {
                            k = i;
                            break;
                        }
                    }
                    cout << setw(65) << "Enter Name: ";
                    getline(cin, users[k].name);
                    checkname(users[k].name);
                    cout << setw(69) << "Enter Contact No: +92 ";
                    getline(cin, users[k].tel);
                    checktel(users[k].tel);
                    cout << setw(65) << "Enter Age: ";
                    cin >> users[k].age;
                    checkage(users[k].age);
                    cin.ignore(256, '\n');
                    if (users[k].age < 1 || users[k].age > 75)
                    {
                        users[k].name = "0";users[k].age=-1;users[k].bookings=0;users[k].pass="0";users[k].userid="0";
		                for (int i=0;i<5;i++){
			                users[k].bookbus[i]="0";users[k].seat[i]=-1;
		                }
						cout << "Age must be between 1 and 75. Data has been reset!" << endl;
                    }
                    else
                    {
                        cout << setw(65) << "Enter User ID: ";
                        getline(cin, users[k].userid);
                        checkid(users[k].userid);

                        for (int i = 0; i < k; i++)
                        {
                            if (users[k].userid == users[i].userid)
                            {
                                cout << "This ID has been already used. Please use another one: ";
                                getline(cin, users[k].userid);
                            }
                        }

                        cout << setw(65) << "Enter Password: ";
                        getline(cin, users[k].pass);
                        checkpass(users[k].pass);
                    }
                    cout << endl;
                    breaking();
                    break;
                }
                case 6: // Edit a User
                {
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

                    // Find the user in the struct array
                    findindex2(users, user, password, adflag, k); // users array should be passed

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
                                getline(cin, users[k].name); // Modify user's name
                                checkname(users[k].name);
                                break;
                            case 2:
                                cout << setw(65) << "Enter Age: ";
                                cin >> users[k].age; // Modify user's age
                                checkage(users[k].age);
                                break;
                            case 3:
                                cout << setw(65) << "Enter Tel.: ";
                                getline(cin, users[k].tel); // Modify user's telephone number
                                checktel(users[k].tel);
                                break;
                            case 4:
                                cout << setw(65) << "Enter ID: ";
                                getline(cin, users[k].userid); // Modify user's ID
                                checkid(users[k].userid);
                                break;
                            case 5:
                                cout << setw(65) << "Enter Password: ";
                                getline(cin, users[k].pass); // Modify user's password
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
                }

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

                    // Find the user in the struct array
                    findindex2(users, user, password, adflag, k); // users array should be passed

                    if (adflag == 1)
                    {
                        cout << setw(65) << "Do you really want to delete (Y/N): ";
                        cin >> choice1;

                        if (choice1 == "Y" || choice1 == "y")
                        {
                            // Reset user data
                            users[k].name = "0";
                            users[k].age = -1;
                            users[k].userid = "0";
                            users[k].pass = "0";
                            users[k].tel = "0";

                            // Reset arrays in users struct
                            for (int i = 0; i < 5; i++)
                            {
                                users[k].seat[i] = 0;      // Reset seats
                                users[k].bookbus[i] = "0"; // Reset booked buses
                            }

                            users[k].bookings = 0; // Reset bookings

                            cout << "User deleted successfully!" << endl;
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
                        cout << "Invalid ID or Password!" << endl;
                    }

                    breaking();
                    break;
                }

                case 8: // List of All Flights
                {
                    adflag = 0;
                    for (int i = 0; i < 5; i++)
                    {
                        if (buses[i].busname != "0")
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
                            if (buses[i].busname != "0" && buses[i].capacity != 0)
                            {
                                cout << setw(20) << buses[i].busname << setw(20) << buses[i].departure
                                     << setw(20) << buses[i].destination << setw(20) << buses[i].deptime
                                     << setw(20) << buses[i].arrtime << endl;
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

                    // Find the user in the struct array
                    findindex2(users, user, password, adflag, k);

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
                            if (dep == buses[i].departure && des == buses[i].destination)
                            {
                                flag = true;
                                cout << setw(15) << buses[i].busname << setw(15) << buses[i].departure
                                     << setw(15) << buses[i].destination << setw(15) << buses[i].deptime
                                     << setw(15) << buses[i].arrtime << endl;
                            }
                        }

                        if (flag)
                        {
                            cout << "Enter Airbus in which you want to travel: ";
                            getline(cin, busname);

                            bool busFound = false, alreadyBooked = false;

                            for (int i = 0; i < 5; i++)
                            {
                                if (users[k].bookbus[i] == busname)
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
                                    if (busname == buses[i].busname)
                                    {
                                        busFound = true;

                                        if (buses[i].capacity > 0)
                                        {
                                            for (int j = 0; j < 5; j++)
                                            {
                                                if (users[k].bookbus[j] == "")
                                                {
                                                    users[k].bookbus[j] = busname;
                                                    users[k].seat[j] = buses[i].capacity;
                                                    buses[i].capacity--;
                                                    users[k].bookings++;
                                                    cout << "Your seat has been booked." << endl;
                                                    cout << "Your seat number is: " << users[k].seat[j] << endl;
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
                         << setw(15) << "Available Seats"
                         << setw(15) << "Price" << endl;
                    line();

                    // Display available buses
                    for (int i = 0; i < 5; i++)
                    {
                        if (buses[i].departure == dep && buses[i].destination == des)
                        {
                            cout << "\t" << setw(15) << buses[i].busname
                                 << setw(20) << buses[i].deptime
                                 << setw(20) << buses[i].arrtime
                                 << setw(15) << buses[i].capacity << endl;
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
                            if (users[k].bookbus[i] == busname)
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
                                if (buses[i].busname == busname)
                                {
                                    flag = true;

                                    if (buses[i].capacity > 0)
                                    {
                                        for (int j = 0; j < 5; j++)
                                        {
                                            if (users[k].bookbus[j] == "")
                                            {
                                                users[k].bookbus[j] = busname;
                                                users[k].seat[j] = buses[i].capacity;
                                                buses[i].capacity--;
                                                cout << "Ticket successfully booked!" << endl;
                                                cout << "Your seat number is " << users[k].seat[j] << "." << endl;
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
                        if (users[k].bookbus[i] == busname)
                        {
                            foundBooking = true;
                            users[k].bookbus[i] = "";
                            users[k].seat[i] = 0;
                            flag = true;

                            for (int j = 0; j < 5; j++)
                            {
                                if (buses[j].busname == busname)
                                {
                                    buses[j].capacity++;
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
                        if (users[k].bookbus[i] != "")
                        {
                            for (int j = 0; j < 5; j++)
                            {
                                if (users[k].bookbus[i] == buses[j].busname)
                                {
                                    cout << setw(15) << buses[j].busname
                                         << setw(20) << buses[j].deptime
                                         << setw(20) << buses[j].arrtime
                                         << setw(15) << users[k].seat[i] << endl;
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
                        if (buses[i].busname != "0")
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
                            if (buses[i].busname != "0" && buses[i].capacity != 0)
                            {
                                cout << setw(20) << buses[i].busname << setw(20) << buses[i].departure << setw(20) << buses[i].destination
                                     << setw(20) << buses[i].deptime << setw(20) << buses[i].arrtime << endl;
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
                        if (buses[i].departure == dep && buses[i].destination == des && buses[i].busname != "0" && buses[i].capacity > 0)
                        {
                            cout << setw(15) << buses[i].busname
                                 << setw(20) << buses[i].deptime
                                 << setw(20) << buses[i].arrtime
                                 << setw(15) << buses[i].capacity << endl;
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

                    // Find the index of the bus
                    bool busFound = false;
                    for (int i = 0; i < 5; i++)
                    {
                        if (buses[i].busname == busname)
                        {
                            busFound = true;
                            cout << "Flight " << buses[i].busname << " has " << buses[i].capacity << " empty seats." << endl;
                            break;
                        }
                    }

                    if (!busFound)
                    {
                        cout << "Flight not found!" << endl;
                    }

                    breaking();
                    break;
                }

                case 7: // Search Flights by Destination
                {
                    system("cls");
                    line();
                    cout << "\t\t\t\t\t\tFlights Search" << endl;
                    line();

                    cin.ignore();
                    cout << setw(65) << "Enter Departure: ";
                    getline(cin, dep);
                    checkname(dep);
                    cout << setw(65) << "Enter destination: ";
                    getline(cin, des);
                    checkname(des);
                    adflag = 0;

                    for (int i = 0; i < 5; i++)
                    {
                        if (buses[i].destination == des && buses[i].departure == dep && buses[i].busname != "0")
                        {
                            adflag = 1;
                            cout << "Flight to " << des << ": " << buses[i].busname
                                 << ", Departure Time: " << buses[i].deptime
                                 << ", Arrival Time: " << buses[i].arrtime << endl;
                        }
                    }

                    if (adflag == 0)
                    {
                        cout << "No available flights to " << des << endl;
                    }

                    breaking();
                    break;
                }

                case 0: // Sign Out
                {
                    system("cls");
                    cout << "Logged out Successfully!" << endl;
                    input1 = 0;
                    break;
                }

                default:
                {
                    cout << "Wrong Input!" << endl;
                    break;
                }
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
                getline(cin, users[k].name);
                checkname(users[k].name);

                cout << setw(69) << "Enter Contact No: +92 ";
                getline(cin, users[k].tel);
                checktel(users[k].tel);

                cout << setw(65) << "Enter Age: ";
                cin >> users[k].age;
                checkage(users[k].age);

                if (users[k].age < 1 || users[k].age > 75)
                {
                    cout << "Age must be between 1 and 75. Data has been reset.\n";
                    users[k].name = "0";
                    users[k].tel = "0";
                    users[k].userid = "0";
                    users[k].age = 0;
                }
                else
                {
                    cin.ignore();

                    cout << setw(65) << "Enter User ID: ";
                    getline(cin, users[k].userid);
                    checkid(users[k].userid);

                    for (int i = 0; i < k; i++)
                    {
                        if (k != 0)
                        {
                            if (users[k].userid == users[i].userid)
                            {
                                cout << setw(65) << "This ID has been already used. Please use another one: ";
                                getline(cin, users[k].userid);
                                checkid(users[k].userid);
                            }
                        }
                    }

                    cout << setw(65) << "Enter password: ";
                    getline(cin, users[k].pass);
                    checkpass(users[k].pass);
                }
            }

            if (uflag == 4)
            {
                cout << "Network Issue! Please Try Again Later.";
            }
            else if (users[k].age != 0)
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

    storedatauser(users, 5);
    storedatabus(buses, 5);

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
                else
                    flag = false;
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
        else
            flag = false;
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
void checkbus(string &bus)
{
    bool flag;
    while (true)
    {
        flag = true;
        if (bus.length() < 4 || bus.length() > 6)
        {
            flag = false;
        }
        if (bus == "")
            flag = false;
        if (bus[0] < 'A' || bus[0] > 'Z')
            flag = false;
        for (int i = 0; i < bus.length(); i++)
        {
            if (!(bus[i] >= '0' && bus[i] <= '9' || bus[i] >= 'A' && bus[i] <= 'Z'))
                flag = false;
            if (!flag)
                break;
        }
        if (flag)
            break;
        else
        {
            cout << setw(65) << "Invalid Airbus name.Enter name again: ";
            getline(cin, bus);
        }
    }
}
void findindex1(u_er users[], string name1, int &adflag, int &k)
{
    adflag = 0;
    k = -1;
    for (int i = 0; i < 5; i++)
    {
        if (users[i].name == name1)
        {
            adflag = 1;
            k = i;
            break;
        }
    }
}
void findindex2(u_er users[], string name1, string password, int &adflag, int &k)
{
    adflag = 0;
    k = -1;
    for (int i = 0; i < 5; i++)
    {
        if (users[i].name == name1 && users[i].pass == password)
        {
            adflag = 1;
            k = i;
            break;
        }
    }
}

void storedatauser(u_er users[], int size)
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
        if (users[k].name != "0" && users[k].userid != "0")
        {
            fout << users[k].name << "," << users[k].tel << "," << users[k].userid << ","
                 << users[k].pass << "," << users[k].bookings << ",";

            if (users[k].bookings != 0)
            {
                for (int i = 0; i < users[k].bookings; i++)
                {
                    fout << users[k].bookbus[i] << "," << users[k].seat[i] << ",";
                }
            }

            fout << endl;
        }
    }

    fout.close();
}bool loaddatauser(u_er users[], int size) {
    ifstream fin("users.txt");
    if (!fin) {
        cout << "Error opening file!" << endl;
        return false;
    }

    int k = 0;

    // Loop through users array and load data
    while (getline(fin, users[k].name, ',')) {
        if (k >= size)  // Use size instead of hardcoding 5
            break;
        if (users[k].name.empty() || users[k].name == "\n") {
            users[k].name = "0";
            break;
        }

        getline(fin, users[k].tel, ',');
        getline(fin, users[k].userid, ',');
        getline(fin, users[k].pass, ',');
        fin >> users[k].bookings;
        if (fin.fail()) {
            users[k].bookings = 0;
            fin.clear();
        }
        fin.ignore();

        // Load booked buses and seat information
        for (int i = 0; i < users[k].bookings; i++) {
            getline(fin, users[k].bookbus[i], ',');
            fin >> users[k].seat[i];
            fin.ignore();
        }
        k++;
    }

    fin.close();
    return true;
}
void storedatabus(airbus buses[], int size)
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
        if (buses[k].busname != "0" && buses[k].capacity != 0)
        {
            fout << buses[k].busname << "," << buses[k].departure << "," << buses[k].deptime << ","
                 << buses[k].destination << "," << buses[k].arrtime << "," << buses[k].capacity;
            fout << endl;
        }
    }

    fout.close();
}
bool loaddatabus(airbus buses[], int size)
{
    ifstream fin("airbuses.txt");
    if (!fin)
    {
        cout << "Error opening file!" << endl;
        return false;
    }

    int k = 0;

    while (getline(fin, buses[k].busname, ','))
    {
        if (k == 5)
            break;
        if (buses[k].busname.empty() || buses[k].busname == "\n")
        {
            buses[k].busname = "0";
            break;
        }

        getline(fin, buses[k].departure, ',');
        getline(fin, buses[k].deptime, ',');
        getline(fin, buses[k].destination, ',');
        getline(fin, buses[k].arrtime, ',');
        fin >> buses[k].capacity;
        if (fin.fail())
        {
            buses[k].capacity = 0;
            fin.clear();
        }
        fin.ignore();

        k++;
    }

    fin.close();
    return true;
}

