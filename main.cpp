
#include <iostream>
#include <string>
using namespace std;

// Structure to store item details
struct Item
{
    int itemID;
    string itemName;
    string category;
    string location;
    string date;
    string status;
};

// Array to store records
Item items[100];
int itemCount = 0;

// Function to report a lost item
void reportLostItem()
{
    if (itemCount >= 100)
    {
        cout << "Record limit reached!\n";
        return;
    }

    items[itemCount].itemID = itemCount + 1;

    cout << "\nEnter Item Name: ";
    cin.ignore();
    getline(cin, items[itemCount].itemName);

    cout << "Enter Category: ";
    getline(cin, items[itemCount].category);

    cout << "Enter Lost Location: ";
    getline(cin, items[itemCount].location);

    cout << "Enter Date: ";
    getline(cin, items[itemCount].date);

    items[itemCount].status = "Lost";

    itemCount++;

    cout << "\nLost Item Report Submitted Successfully!\n";
}

// Main function
int main()
{
    string username, password;

    cout << "SMART CAMPUS LOST & FOUND SYSTEM\n";

    cout << "\nEnter Username: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;

    if (username == "student" && password == "1234")
    {
        int choice;

        do
        {
            cout << "\n========== MAIN MENU ==========\n";
            cout << "1. Report Lost Item\n";
            cout << "2. Report Found Item\n";
            cout << "3. Search Item\n";
            cout << "4. Auto Match Lost & Found\n";
            cout << "5. View All Records\n";
            cout << "6. Delete Record\n";
            cout << "7. Item Statistics\n";
            cout << "8. Export Report\n";
            cout << "9. Exit\n";

            cout << "\nEnter your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    reportLostItem();
                    break;

                case 2:
                    cout << "Report Found Item selected.\n";
                    break;

                case 3:
                    cout << "Search Item selected.\n";
                    break;

                case 4:
                    cout << "Auto Match selected.\n";
                    break;

                case 5:
                    cout << "View All Records selected.\n";
                    break;

                case 6:
                    cout << "Delete Record selected.\n";
                    break;

                case 7:
                    cout << "Item Statistics selected.\n";
                    break;

                case 8:
                    cout << "Export Report selected.\n";
                    break;

                case 9:
                    cout << "Thank you for using the system!\n";
                    break;

                default:
                    cout << "Invalid choice!\n";
            }

        } while (choice != 9);
    }
    else
    {
        cout << "Invalid Username or Password!\n";
    }

    return 0;
}
