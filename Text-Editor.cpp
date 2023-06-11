#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <dirent.h> 
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

void menu(int msg);
void listFiles(); // Function to list all files in a folder

int main()
{
    menu(0);
    return 0;
}

void menu(int msg)
{
  system("CLS");
  if (msg == 0)
  {
      cout << "Welcome to Text Editor" << endl << endl;
  }
  if (msg == 1)
  {
      cout << "File Created Successfully" << endl << endl;
  }
  if (msg == 2)
  {
      cout << "File Updated Successfully" << endl << endl;
  }
  if (msg == 4)
  {
      cout << "File Emptied Successfully" << endl << endl;
  }
  if (msg == 5)
  {
      cout << "File Deleted Successfully" << endl << endl;
  }
  if (msg == 55)
  {
      cout << "File Not Found" << endl << endl;
  }
  if (msg == 6)
  {
      cout << "File Copied Successfully" << endl << endl;
  }
  if (msg == 7)
  {
      cout << "List of Files:" << endl;
      listFiles(); // Call the function to list files
  }

  cout << "Main Menu" << endl;
  cout << "-------------" << endl;
  cout << "1. Create File" << endl;
  cout << "2. Add to File" << endl;
  cout << "3. Read from File" << endl;
  cout << "4. Empty File" << endl;
  cout << "5. Delete File" << endl;
  cout << "6. Copy File" << endl;
  cout << "7. List Files" << endl;
  cout << "8. Exit" << endl << endl;
  cout << "Enter Choice: ";

  int choice = 0;
  string filename;
  string text;

  cin >> choice;
  if (choice == 1)
  {
    cout << endl << "Enter name of file: ";
    cin.ignore();
    getline(cin, filename);
    ofstream myfile((filename + ".txt").c_str());
    myfile.close();
    menu(1);
    cin >> choice;
  }
  if (choice == 2)
  {
    text = "";
    cout << endl << "Enter name of file: ";
    cin >> filename;
    cout << endl << "Enter text to write to file: (Enter END to complete)" << endl;
    ofstream myfile;
    myfile.open((filename + ".txt").c_str(), ios::app);
    string line;
    cin.ignore();
    while (getline(cin, line))
    {
      if (line.size() >= 3)
      {
        if (line.substr(line.size() - 3) == "END")
        {
          text += line.substr(0, line.size() - 3);
          break;
        }
        else
        {
          text += line + "\n";
        }
      }
      else
      {
        text += line + "\n";
      }
    }
    myfile << text;
    myfile.close();
    menu(2);
    cin >> choice;
  }
  if (choice == 3)
  {
    text = "";
    cout << endl << "Enter name of file: ";
    cin >> filename;
    fstream myfile;
    myfile.open((filename + ".txt").c_str());
    while (getline(myfile, text))
    {
      cout << text << "\n";
    }
    myfile.close();
    char now;
    cout << endl << "End of File. Press any key for main menu: ";
    cin >> now;
    menu(2);
    cin >> choice;
  }
  if (choice == 4)
  {
    cout << endl << "Enter name of file: ";
    cin >> filename;
    ofstream myfile;
    myfile.open((filename + ".txt").c_str());
    myfile << "";
    myfile.close();
    menu(4);
    cin >> choice;
  }
  if (choice == 5)
  {
    cout << endl << "Enter name of file: ";
    cin >> filename;
    if (remove((filename + ".txt").c_str()) == 0)
    {
      menu(5);
    }
    else
    {
      menu(55);
    }
  }
  if (choice == 6)
  {
    text = "";
    cout << endl << "Enter name of file to copy from: ";
    cin.ignore();
    getline(cin, filename);
    fstream myfile((filename + ".txt").c_str());
    string line;
    while (getline(myfile, line))
    {
      text += line + "\n";
    }
    myfile.close();
    cout << endl << "Enter name of file to copy to: ";
    string second;
    getline(cin, second);
    ofstream myfile2;
    myfile2.open((second + ".txt").c_str(), ios::app);
    myfile2 << text;
    myfile2.close();
    menu(6);
    cin >> choice;
  }
  if (choice == 7)
  {
    menu(7); // Display the list of files
  }
  if (choice == 8)
  {
    exit(EXIT_SUCCESS);
  }
}

void listFiles()
{
  DIR *dir;
  struct dirent *ent;
  struct stat fileStat;
  if ((dir = opendir(".")) != NULL) // Open the current directory
  {
    while ((ent = readdir(dir)) != NULL) // Read the directory entries
    {
      if (stat(ent->d_name, &fileStat) == 0) // Get file information
      {
        if (S_ISREG(fileStat.st_mode)) // Check if it's a regular file
        {
          cout << ent->d_name << endl; // Print the file name
        }
      }
    }
    cout<<endl;
    closedir(dir); // Close the directory
  }
  else
  {
    perror(""); // Print an error message
  }
}