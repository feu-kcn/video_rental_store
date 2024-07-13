#include <iostream>
#include <queue>
#include <stack>
#include <fstream>

#include "video.hpp"
#include "customers.hpp"
#include "rent.hpp"

using namespace std;

// Shows the customer menu and returns the choice
int customerMenu()
{
    int choice;

    cout << "[1] Add New Customer" << endl;
    cout << "[2] Show Customer Details" << endl;
    cout << "[3] List of Videos Rented by a Customer" << endl;
    cout << "[4] Exit" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    while (choice < 1 || choice > 4)
    {
        cout << "Invalid choice. Please enter a valid choice: ";
        cin >> choice;
    }

    return choice;
}

// Display the main menu
void displayMenu()
{
    cout << "LODS Video Rental System | Main Menu :" << endl;
    cout << "[1] New Video" << endl;
    cout << "[2] Rent a Video" << endl;
    cout << "[3] Return a Video" << endl;
    cout << "[4] Show Video Details" << endl;
    cout << "[5] Display all Videos" << endl;
    cout << "[6] Check Video Availability" << endl;
    cout << "[7] Customer Maintenance" << endl;
    cout << "[8] Exit" << endl;
}

// Get a valid choice from the user
// Returns the choice
// Loops until a valid choice is entered
int getValidChoice()
{
    int choice;
    bool validInput = false;

    do
    {
        cout << "Enter your choice (1-8): ";
        if (cin >> choice)
        {
            if (choice >= 1 && choice <= 8)
            {
                validInput = true;
            }
            else
            {
                cout << "Invalid choice. Please enter a number between 1 and 8." << endl;
            }
        }
        else
        {
            cout << "Invalid input. Please enter a number between 1 and 8." << endl;

            cin.clear();

            // Clear the input that has error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!validInput);

    return choice;
}

int main()
{
    /// Linked list of videos
    VideoList videos;

    /// Customers list
    queue<Customer> customers;

    /// Rent
    stack<Rent> rents;

    // Load data from files
    cout << "Importing data..." << endl;

    videos.importFromFile("videos.txt");
    customers = Customer::importFromFile("customers.txt");
    rents = Rent::importFromFile("rents.txt");

    /// Uncomment the following lines to add some sample data
    // videos.addVideo(Video("Avengers", "Sci-Fi", "Marvel", 2, "marvel.jpg"));
    // customers.push(Customer("Juan de la Cruz", "Manila PH"));
    // rents.push(Rent(1, 1));

    // Main loop
    int choice;
    do
    {
        displayMenu();
        choice = getValidChoice();

        switch (choice)
        {
        case 1:
            // New video
            videos.addVideo();
            break;
        case 2:
        {
            // Rent a video
            Video *video = videos.displayAndSelectVideoNoNull();

            Customer customer = Customer::displayAndGetCustomer(customers);

            // Check if the video is available

            int availability = Rent::getVideoAvailability(*video, rents);

            if (availability <= 0)
            {
                cout << "The video is not available." << endl;
                break;
            }
            else
            {
                Rent rent(video->getId(), customer.getId());

                Rent::add(rent, &rents);
            }
        }

        break;
        case 3:
        {
            // Return a video rent
            Video *video = videos.displayAndSelectVideoNoNull();

            Customer customer = Customer::displayAndGetCustomer(customers);

            Rent::returnVideo(video->getId(), customer.getId(), &rents);

            break;
        }

        case 4:

        {
            // Show video details
            Video *video = videos.displayAndSelectVideo();
            if (video != NULL)
            {
                Video::displayVideo(video);
            }
            break;
        }
        case 5:
            // Display all videos
            videos.displayVideos();

            break;
        case 6:
        {
            // Check video availability
            Video *video = videos.displayAndSelectVideo();

            int availability = Rent::getVideoAvailability(*video, rents);

            if (availability > 0)
            {
                cout << "The video is available. " << availability << " copy left remaining." << endl;
            }
            else
            {
                cout << "The video is not available." << endl;
            }

            break;
        }
        case 7:
        {
            // Customer maintenance menu
            int selection = customerMenu();
            switch (selection)
            {
            case 1:
                // Add new customer
                customers.push(Customer::createCustomer());
                break;
            case 2:
                // Show customer details
                Customer::displayCustomer(Customer::displayAndGetCustomer(customers));
                break;
            case 3:
            {
                // List of videos rented by a customer
                Customer customer = Customer::displayAndGetCustomer(customers);

                vector<int> ids = Rent::listOfVideosRentedByCustomer(customer.getId(), rents);

                for (int i = 0; i < ids.size(); i++)
                {
                    Video *video = videos.getVideo(ids[i]);

                    Video::displayVideo(video);
                }

                break;
            }
            case 4:
                break;
            }
        }
        break;
        case 8:
        {
            cout << "Saving data..." << endl;

            // Save videos
            videos.exportToFile("videos.txt");

            // Save customers
            Customer::exportToFile("customers.txt", customers);

            // Save rents
            Rent::exportToFile("rents.txt", rents);

            cout << "Exiting the program." << endl;
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}