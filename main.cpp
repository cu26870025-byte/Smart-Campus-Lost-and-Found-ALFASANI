#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// Maximum number of records that can be stored at one time.
const int MAX_ITEMS = 500;
const string DATA_FILE = "lost_found_records.txt";

// Structure stores all details of one lost or found item.
struct Item
{
    int itemID;
    string itemName;
    string category;
    string description;
    string location;
    string date;
    string contact;
    string status;       // "Lost" or "Found"
};

Item items[MAX_ITEMS];
int itemCount = 0;

// Read a complete line, including spaces.
string readLine(string message)
{
    string value;
    cout << message;
    getline(cin, value);
    return value;
}

// Save all records in a text file.
void saveRecords()
{
    ofstream file(DATA_FILE.c_str());

    if (!file)
    {
        cout << "Error: Could not save the records.\n";
        return;
    }

    for (int i = 0; i < itemCount; i++)
    {
        file << items[i].itemID << "|"
             << items[i].itemName << "|"
             << items[i].category << "|"
             << items[i].description << "|"
             << items[i].location << "|"
             << items[i].date << "|"
             << items[i].contact << "|"
             << items[i].status << "\n";
    }

    file.close();
}

// Load previously saved records when the program starts.
void loadRecords()
{
    ifstream file(DATA_FILE.c_str());

    if (!file)
    {
        return; // The file will be created when the first record is saved.
    }

    string line;

    while (getline(file, line) && itemCount < MAX_ITEMS)
    {
        string fields[8];
        stringstream lineStream(line);
        int fieldCount = 0;

        while (fieldCount < 8 && getline(lineStream, fields[fieldCount], '|'))
        {
            fieldCount++;
        }

        if (fieldCount == 8)
        {
            items[itemCount].itemID = atoi(fields[0].c_str());
            items[itemCount].itemName = fields[1];
            items[itemCount].category = fields[2];
            items[itemCount].description = fields[3];
            items[itemCount].location = fields[4];
            items[itemCount].date = fields[5];
            items[itemCount].contact = fields[6];
            items[itemCount].status = fields[7];
            itemCount++;
        }
    }

    file.close();
}

// Find the next available record ID.
int getNextID()
{
    int highestID = 0;

    for (int i = 0; i < itemCount; i++)
    {
        if (items[i].itemID > highestID)
        {
            highestID = items[i].itemID;
        }
    }

    return highestID + 1;
}

// Login system for a student.
bool studentLogin()
{
    string username;
    string password;

    cout << "\n========== STUDENT LOGIN ==========\n";
    cout << "Demo username: student\n";
    cout << "Demo password: 1234\n";

    cout << "Enter username: ";
    getline(cin, username);

    cout << "Enter password: ";
    getline(cin, password);

    if (username == "student" && password == "1234")
    {
        cout << "\nLogin successful. Welcome!\n";
        return true;
    }

    cout << "\nInvalid username or password.\n";
    return false;
}

// Add a lost item or a found item.
void addItem(string itemStatus)
{
    if (itemCount >= MAX_ITEMS)
    {
        cout << "\nRecord limit reached. Cannot add more items.\n";
        return;
    }

    Item newItem;
    newItem.itemID = getNextID();
    newItem.status = itemStatus;

    cout << "\n========== REPORT " << itemStatus << " ITEM ==========\n";
    newItem.itemName = readLine("Enter item name: ");
    newItem.category = readLine("Enter category: ");
    newItem.description = readLine("Enter description: ");
    newItem.location = readLine("Enter location: ");
    newItem.date = readLine("Enter date (DD-MM-YYYY): ");
    newItem.contact = readLine("Enter student contact: ");

    if (newItem.itemName.empty() || newItem.category.empty() ||
        newItem.location.empty() || newItem.date.empty())
    {
        cout << "\nRequired details cannot be empty. Record was not added.\n";
        return;
    }

    items[itemCount] = newItem;
    itemCount++;
    saveRecords();

    cout << "\n" << itemStatus << " item reported successfully.\n";
    cout << "Your record ID is: " << newItem.itemID << "\n";
}

// Convert a string to lowercase for simple case-insensitive searching.
string toLowerCase(string value)
{
    for (int i = 0; i < (int)value.length(); i++)
    {
        if (value[i] >= 'A' && value[i] <= 'Z')
        {
            value[i] = value[i] - 'A' + 'a';
        }
    }
    return value;
}

// Search records by item name or category.
void searchItem()
{
    if (itemCount == 0)
    {
        cout << "\nNo records are available.\n";
        return;
    }

    string keyword = toLowerCase(readLine("\nEnter item name or category to search: "));
    bool found = false;

    for (int i = 0; i < itemCount; i++)
    {
        if (toLowerCase(items[i].itemName).find(keyword) != string::npos ||
            toLowerCase(items[i].category).find(keyword) != string::npos)
        {
            cout << "\nRecord ID: " << items[i].itemID
                 << "\nItem: " << items[i].itemName
                 << "\nCategory: " << items[i].category
                 << "\nLocation: " << items[i].location
                 << "\nDate: " << items[i].date
                 << "\nStatus: " << items[i].status
                 << "\nContact: " << items[i].contact << "\n";
            found = true;
        }
    }

    if (!found)
    {
        cout << "\nNo matching item found.\n";
    }
}

// Compare a lost item with found items using item name and category.
void autoMatchItems()
{
    bool matchFound = false;

    cout << "\n========== LOST AND FOUND MATCHES ==========\n";

    for (int i = 0; i < itemCount; i++)
    {
        if (items[i].status == "Lost")
        {
            for (int j = 0; j < itemCount; j++)
            {
                if (items[j].status == "Found" &&
                    toLowerCase(items[i].itemName) == toLowerCase(items[j].itemName) &&
                    toLowerCase(items[i].category) == toLowerCase(items[j].category))
                {
                    cout << "\nPossible match found!\n";
                    cout << "Lost record ID: " << items[i].itemID
                         << " | Item: " << items[i].itemName
                         << " | Location: " << items[i].location << "\n";
                    cout << "Found record ID: " << items[j].itemID
                         << " | Item: " << items[j].itemName
                         << " | Location: " << items[j].location << "\n";
                    matchFound = true;
                }
            }
        }
    }

    if (!matchFound)
    {
        cout << "No exact name-and-category matches found.\n";
    }

    cout << "Note: A possible match should be verified by the student.\n";
}

// Sort records by item name using a simple bubble sort, then display them.
void viewAllRecords()
{
    if (itemCount == 0)
    {
        cout << "\nNo records are available.\n";
        return;
    }

    Item sortedItems[MAX_ITEMS];

    for (int i = 0; i < itemCount; i++)
    {
        sortedItems[i] = items[i];
    }

    for (int i = 0; i < itemCount - 1; i++)
    {
        for (int j = 0; j < itemCount - i - 1; j++)
        {
            if (toLowerCase(sortedItems[j].itemName) >
                toLowerCase(sortedItems[j + 1].itemName))
            {
                Item temp = sortedItems[j];
                sortedItems[j] = sortedItems[j + 1];
                sortedItems[j + 1] = temp;
            }
        }
    }

    cout << "\n========== ALL ITEM RECORDS (SORTED BY NAME) ==========\n";

    for (int i = 0; i < itemCount; i++)
    {
        cout << "\nID: " << sortedItems[i].itemID
             << "\nName: " << sortedItems[i].itemName
             << "\nCategory: " << sortedItems[i].category
             << "\nDescription: " << sortedItems[i].description
             << "\nLocation: " << sortedItems[i].location
             << "\nDate: " << sortedItems[i].date
             << "\nContact: " << sortedItems[i].contact
             << "\nStatus: " << sortedItems[i].status << "\n";
        cout << "----------------------------------------\n";
    }
}

// Delete a record using its record ID.
void deleteRecord()
{
    if (itemCount == 0)
    {
        cout << "\nNo records are available to delete.\n";
        return;
    }

    int deleteID;
    cout << "\nEnter record ID to delete: ";
    cin >> deleteID;
    cin.ignore(10000, '\n');

    int position = -1;

    for (int i = 0; i < itemCount; i++)
    {
        if (items[i].itemID == deleteID)
        {
            position = i;
            break;
        }
    }

    if (position == -1)
    {
        cout << "\nRecord ID not found.\n";
        return;
    }

    for (int i = position; i < itemCount - 1; i++)
    {
        items[i] = items[i + 1];
    }

    itemCount--;
    saveRecords();

    cout << "\nRecord deleted successfully.\n";
}

// Display total, lost, and found item counts.
void itemStatistics()
{
    int lostCount = 0;
    int foundCount = 0;

    for (int i = 0; i < itemCount; i++)
    {
        if (items[i].status == "Lost")
        {
            lostCount++;
        }
        else if (items[i].status == "Found")
        {
            foundCount++;
        }
    }

    cout << "\n========== ITEM STATISTICS ==========\n";
    cout << "Total records: " << itemCount << "\n";
    cout << "Lost items: " << lostCount << "\n";
    cout << "Found items: " << foundCount << "\n";
}

// Export all current records to a separate report file.
void exportReport()
{
    ofstream report("exported_report.txt");

    if (!report)
    {
        cout << "\nError: Could not create the report file.\n";
        return;
    }

    report << "SMART CAMPUS LOST & FOUND MANAGEMENT SYSTEM\n";
    report << "============== ITEM REPORT ==============\n\n";

    for (int i = 0; i < itemCount; i++)
    {
        report << "Record ID: " << items[i].itemID << "\n";
        report << "Item Name: " << items[i].itemName << "\n";
        report << "Category: " << items[i].category << "\n";
        report << "Description: " << items[i].description << "\n";
        report << "Location: " << items[i].location << "\n";
        report << "Date: " << items[i].date << "\n";
        report << "Contact: " << items[i].contact << "\n";
        report << "Status: " << items[i].status << "\n";
        report << "----------------------------------------\n";
    }

    report.close();
    cout << "\nReport exported successfully to exported_report.txt\n";
}

// Display the project menu.
void displayMenu()
{
    cout << "\n========== SMART CAMPUS LOST & FOUND ==========\n";
    cout << "1. Report Lost Item\n";
    cout << "2. Report Found Item\n";
    cout << "3. Search Item\n";
    cout << "4. Auto Match Lost & Found\n";
    cout << "5. View All Records\n";
    cout << "6. Delete Record\n";
    cout << "7. Item Statistics\n";
    cout << "8. Export Report\n";
    cout << "9. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    loadRecords();

    cout << "SMART CAMPUS LOST & FOUND MANAGEMENT SYSTEM\n";

    if (!studentLogin())
    {
        return 0;
    }

    int choice;

    do
    {
        displayMenu();
        cin >> choice;
        cin.ignore(10000, '\n');

        switch (choice)
        {
            case 1:
                addItem("Lost");
                break;

            case 2:
                addItem("Found");
                break;

            case 3:
                searchItem();
                break;

            case 4:
                autoMatchItems();
                break;

            case 5:
                viewAllRecords();
                break;

            case 6:
                deleteRecord();
                break;

            case 7:
                itemStatistics();
                break;

            case 8:
                exportReport();
                break;

            case 9:
                cout << "\nThank you for using the system. Goodbye!\n";
                break;

            default:
                cout << "\nInvalid choice. Please enter a number from 1 to 9.\n";
        }

    } while (choice != 9);

    return 0;
}
