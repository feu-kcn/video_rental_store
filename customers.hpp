#include <string>

using namespace std;

class Customer
{
private:
    static int nextId;
    int id;
    string name;
    string address;

public:
    // Default constructor
    Customer()
    {
        id = nextId;
        name = "";
        address = "";
    }

    // Parameterized constructor
    Customer(string name, string address)
    {
        this->id = nextId;
        this->name = name;
        this->address = address;
    }

    int getId()
    {
        return id;
    }

    string getName()
    {
        return name;
    }

    string getAddress()
    {
        return address;
    }

    // Static methods
    static Customer createCustomer();
    static void displayCustomer(Customer customer);
    static void displayAllCustomers(queue<Customer> customers);
    static Customer displayAndGetCustomer(queue<Customer> customers);

    static void exportToFile(const string &filename, queue<Customer> customers);
    static queue<Customer> importFromFile(const string &filename);
};

Customer Customer::createCustomer()
{
    string name;
    string address;

    cout << "Enter customer name: ";
    cin >> name;
    cout << "Enter customer address: ";
    cin >> address;

    return Customer(name, address);
}

void Customer::displayCustomer(Customer customer)
{
    cout << "ID: " << customer.getId() << endl;
    cout << "Customer name: " << customer.getName() << endl;
    cout << "Customer address: " << customer.getAddress() << endl;
}

void Customer::displayAllCustomers(queue<Customer> customers)
{
    queue<Customer> temp = customers;

    while (!temp.empty())
    {
        Customer::displayCustomer(temp.front());
        cout << endl;

        temp.pop();
    }
}

Customer Customer::displayAndGetCustomer(queue<Customer> customers)
{
    Customer customer;
    bool customerFound = false;

    do
    {
        Customer::displayAllCustomers(customers);

        int customerId;
        cout << "Enter customer ID: ";
        cin >> customerId;

        queue<Customer> temp = customers;

        while (!temp.empty())
        {
            Customer current = temp.front();
            if (current.getId() == customerId)
            {
                customer = current;
                customerFound = true;
                break;
            }
            temp.pop();
        }

        if (!customerFound)
        {
            cout << "Customer ID not found. Please try again." << endl;
        }

    } while (!customerFound);

    return customer;
}

void Customer::exportToFile(const string &filename, queue<Customer> customers)
{
    ofstream outFile(filename);
    if (!outFile)
    {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    while (!customers.empty())
    {
        Customer customer = customers.front();
        outFile << customer.getId() << "\n"
                << customer.getName() << "\n"
                << customer.getAddress() << "\n";
        customers.pop();
    }

    outFile.close();
}

queue<Customer> Customer::importFromFile(const string &filename)
{
    ifstream inFile(filename);
    if (!inFile)
    {
        cerr << "Error opening file for reading: " << filename << endl;

        // Return an empty queue
        queue<Customer> emptyQueue;
        return emptyQueue;
    }

    // Reset the nextId
    nextId = 1;
    queue<Customer> customers;

    int id;
    string name;
    string address;

    while (inFile >> id)
    {
        inFile.ignore(); // Ignore the newline after the ID
        getline(inFile, name);
        getline(inFile, address);

        Customer customer;
        customer.id = id;
        customer.name = name;
        customer.address = address;

        customers.push(customer);

        if (id >= nextId)
        {
            nextId = id + 1;
        }
    }

    inFile.close();
    return customers;
}

/// Static variable initialization
int Customer::nextId = 1;
