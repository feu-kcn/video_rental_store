class Rent
{
private:
    int videoId;
    int customerId;

public:
    Rent(int videoId, int customerId)
    {
        this->videoId = videoId;
        this->customerId = customerId;
    }

    int getVideoId()
    {
        return videoId;
    }

    int getCustomerId()
    {
        return customerId;
    }

    // Static methods
    static Rent createRent();
    static void add(Rent rent, std::stack<Rent> *rents);
    static void addRent(std::stack<Rent> *rents);
    static void displayRent(Rent rent);
    static void returnVideo(int videoId, int customerId, stack<Rent> *rents);
    static int getVideoAvailability(Video video, stack<Rent> rents);
    static std::vector<int> listOfVideosRentedByCustomer(int customerId, std::stack<Rent> rents);

    static void exportToFile(const string &filename, stack<Rent> rents);
    static stack<Rent> importFromFile(const string &filename);
};

Rent Rent::createRent()
{
    int videoId;
    int customerId;

    cout << "Enter video ID: ";
    cin >> videoId;
    cout << "Enter customer ID: ";
    cin >> customerId;

    return Rent(videoId, customerId);
}

void Rent::add(Rent rent, stack<Rent> *rents)
{
    rents->push(rent);
}

void Rent::addRent(stack<Rent> *rents)
{
    Rent rent = Rent::createRent();

    rents->push(rent);
}

void Rent::displayRent(Rent rent)
{
    cout << "Video ID: " << rent.getVideoId() << endl;
    cout << "Customer ID: " << rent.getCustomerId() << endl;
}

void Rent::returnVideo(int videoId, int customerId, stack<Rent> *rents)
{
    stack<Rent> tempStack;
    while (!rents->empty())
    {
        Rent rent = rents->top();
        if (rent.getVideoId() == videoId && rent.getCustomerId() == customerId)
        {
            rents->pop();
            break;
        }
        tempStack.push(rent);
        rents->pop();
    }
}

int Rent::getVideoAvailability(Video video, stack<Rent> rents)
{
    int count = 0;

    stack<Rent> tempStack = rents;

    while (!tempStack.empty())
    {
        Rent rent = tempStack.top();
        if (rent.getVideoId() == video.getId())
        {
            count++;
        }
        tempStack.pop();
    }

    return video.getNumberOfCopies() - count;
}

std::vector<int> Rent::listOfVideosRentedByCustomer(int customerId, std::stack<Rent> rents)
{
    std::vector<int> videoIds;

    stack<Rent> tempStack = rents;

    while (!tempStack.empty())
    {
        Rent rent = tempStack.top();
        if (rent.getCustomerId() == customerId)
        {
            videoIds.push_back(rent.getVideoId());
        }
        tempStack.pop();
    }

    return videoIds;
}
void Rent::exportToFile(const string &filename, stack<Rent> rents)
{
    ofstream outFile(filename);
    if (!outFile)
    {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    while (!rents.empty())
    {
        Rent rent = rents.top();
        outFile << rent.getVideoId() << "\n"
                << rent.getCustomerId() << "\n";
        rents.pop();
    }

    outFile.close();
}

stack<Rent> Rent::importFromFile(const string &filename)
{
    ifstream inFile(filename);
    if (!inFile)
    {
        cerr << "Error opening file for reading: " << filename << endl;

        stack<Rent> emptyStack;
        return emptyStack;
    }

    stack<Rent> rents;
    int videoId;
    int customerId;

    while (inFile >> videoId >> customerId)
    {
        Rent rent(videoId, customerId);
        rents.push(rent);
    }

    inFile.close();
    return rents;
}