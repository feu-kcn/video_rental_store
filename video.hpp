#include <string>
#include <fstream>

using namespace std;

class Video
{
private:
    int id;
    string title;
    string genre;
    string production;
    int numberOfCopies;
    string movieImageFilename;

public:
    static int nextId;

    // Default constructor
    Video()
    {
        id = nextId++;
        title = "";
        genre = "";
        production = "";
        numberOfCopies = 0;
        movieImageFilename = "";
    }

    Video(int id, string title, string genre, string production, int numberOfCopies, string movieImageFilename)
    {
        this->id = id;
        this->title = title;
        this->genre = genre;
        this->production = production;
        this->numberOfCopies = numberOfCopies;
        this->movieImageFilename = movieImageFilename;
    }

    // Parameterized constructor
    Video(string title, string genre, string production, int numberOfCopies, string movieImageFilename)
    {
        this->id = nextId;
        this->title = title;
        this->genre = genre;
        this->production = production;
        this->numberOfCopies = numberOfCopies;
        this->movieImageFilename = movieImageFilename;
    }

    // Getters
    int getId()
    {
        return id;
    }

    string getTitle()
    {
        return title;
    }

    string getGenre()
    {
        return genre;
    }

    string getProduction()
    {
        return production;
    }

    int getNumberOfCopies()
    {
        return numberOfCopies;
    }

    string getMovieImageFilename()
    {
        return movieImageFilename;
    }

    void setId(int newId)
    {
        this->id = newId;
    }

    static void setNextId(int newNextId)
    {
        nextId = newNextId;
    }

    // Static methods
    static Video createVideo();
    static void displayVideo(Video *video, bool displayAll = true);
};

class VideoList
{
private:
    struct VideoNode
    {
        Video value;
        VideoNode *next;

        VideoNode()
        {
            next = NULL;
        }
    };

    VideoNode *head;

public:
    VideoList()
    {
        head = NULL;
    }

    void addVideo(Video video)
    {
        VideoNode *newVideoNode = new VideoNode;
        newVideoNode->value = video;
        newVideoNode->next = NULL;

        if (head == NULL)
        {
            head = newVideoNode;
        }
        else
        {
            VideoNode *current = head;
            while (current->next != NULL)
            {
                current = current->next;
            }

            current->next = newVideoNode;
        }
    }

    void addVideo()
    {
        Video video = Video::createVideo();

        addVideo(video);
    }

    void displayVideos()
    {
        VideoNode *current = head;
        while (current != NULL)
        {
            Video::displayVideo(&current->value);
            cout << endl;

            current = current->next;
        }
    }

    Video *displayAndSelectVideo()
    {
        VideoNode *current = head;
        while (current != NULL)
        {
            Video::displayVideo(&current->value, false);
            cout << endl;

            current = current->next;
        }

        int videoId;
        cout << "Enter video ID: ";
        cin >> videoId;

        return getVideo(videoId);
    }

    Video *displayAndSelectVideoNoNull()
    {
        Video *selectedVideo = nullptr;
        bool videoFound = false;

        do
        {
            VideoNode *current = head;
            while (current != NULL)
            {
                Video::displayVideo(&current->value, false);
                cout << endl;

                current = current->next;
            }

            int videoId;
            cout << "Enter video ID: ";
            cin >> videoId;

            selectedVideo = getVideo(videoId);

            if (selectedVideo != nullptr)
            {
                videoFound = true;
            }
            else
            {
                cout << "Video ID not found. Please try again." << endl;
            }

        } while (!videoFound);

        return selectedVideo;
    }

    Video *getVideo(int videoId)
    {
        VideoNode *current = head;
        while (current != NULL)
        {
            if (current->value.getId() == videoId)
            {
                return &current->value;
            }

            current = current->next;
        }

        return NULL;
    }

    void exportToFile(const string &filename)
    {
        ofstream outFile;
        outFile.open(filename);

        if (!outFile)
        {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        VideoNode *current = head;
        while (current != NULL)
        {
            outFile << current->value.getId() << "\n"
                    << current->value.getTitle() << "\n"
                    << current->value.getGenre() << "\n"
                    << current->value.getProduction() << "\n"
                    << current->value.getNumberOfCopies() << "\n"
                    << current->value.getMovieImageFilename() << "\n";
            current = current->next;
        }

        outFile.close();
    }

    void importFromFile(const string &filename)
    {
        ifstream inFile(filename);
        if (!inFile)
        {
            cerr << "Error opening file for reading: " << filename << endl;
            return;
        }

        // Clear the current list
        VideoNode *current = head;
        while (current != NULL)
        {
            VideoNode *next = current->next;
            delete current;
            current = next;
        }
        head = NULL;
        Video::setNextId(1); // Reset the next ID

        int id;
        string title, genre, production, movieImageFilename;
        int numberOfCopies;

        while (inFile >> id)
        {
            inFile.ignore(); // Ignore the newline after the ID
            getline(inFile, title);
            getline(inFile, genre);
            getline(inFile, production);
            inFile >> numberOfCopies;
            inFile.ignore(); // Ignore the newline after the number of copies
            getline(inFile, movieImageFilename);

            Video video = Video(id, title, genre, production, numberOfCopies, movieImageFilename);

            addVideo(video);

            // if (id >= Video::nextId)
            // {
            //     Video::setNextId(id + 1);
            // }
        }

        inFile.close();
    }
};

Video Video::createVideo()
{
    string title;
    string genre;
    string production;
    int numberOfCopies;
    string movieImageFilename;

    cout << "Enter video title: ";
    cin >> title;

    cout << "Enter video genre: ";
    cin >> genre;

    cout << "Enter video production: ";
    cin >> production;

    cout << "Enter number of copies: ";
    cin >> numberOfCopies;

    cout << "Enter movie image filename: ";
    cin >> movieImageFilename;

    return Video(title, genre, production, numberOfCopies, movieImageFilename);
}

void Video::displayVideo(Video *video, bool displayAll)
{
    cout << "ID: " << video->getId() << endl;
    cout << "Video title: " << video->getTitle() << endl;

    if (displayAll)
    {
        cout << "Video genre: " << video->getGenre() << endl;
        cout << "Video production: " << video->getProduction() << endl;
        cout << "Number of copies: " << video->getNumberOfCopies() << endl;
        cout << "Movie image filename: " << video->getMovieImageFilename() << endl;
    }
}

/// Initialize static variable
int Video::nextId = 1;
