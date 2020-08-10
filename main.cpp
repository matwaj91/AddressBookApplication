#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <math.h>

using namespace std;

struct Person
{
    int id, userId;
    string name, surname, phoneNumber, emailAddress, address;
};
struct UserOfTheAdressBook
{
    int userId;
    string userName, password;
};
void registration(UserOfTheAdressBook structOfTheUsers, vector < UserOfTheAdressBook > &vectorOfTheUsers)
{
    int userId;
    string userName, password;
    cout << "Please enter the user name: ";
    cin >> userName;
    int i = 0;
    while(i < vectorOfTheUsers.size())
    {
        if(vectorOfTheUsers[i].userName == userName)
        {
            cout << "Such user already exists. Please enter another user name: ";
            cin >> userName;
            i = 0;
        }
        else
            i++;
    }
    cout << "Please enter the password: ";
    cin >> password;

    if(vectorOfTheUsers.size() == 0)
        userId = 1;
    else
        userId = vectorOfTheUsers.back().userId + 1;

    structOfTheUsers.userId = userId;
    structOfTheUsers.userName = userName;
    structOfTheUsers.password = password;

    fstream file;
    file.open("Users.txt", ios::out | ios::app);
    if (file.good())
    {
        file << userId << "|";
        file << userName << "|";
        file << password << "|" << endl;

        file.close();

        cout << endl << "Account has been created" << endl;
        Sleep(2000);
    }
    else
        cout << "Could not open file Users.txt " << endl;
    vectorOfTheUsers.push_back(structOfTheUsers);
}
int login(UserOfTheAdressBook structOfTheUsers, vector < UserOfTheAdressBook > &vectorOfTheUsers, int idLoggedInUser)
{
    string userName, password;
    cout << "Please enter the user name: ";
    cin >> userName;
    int i = 0;
    while(i < vectorOfTheUsers.size())
    {
        if(vectorOfTheUsers[i].userName == userName)
        {
            for(int test = 0; test < 3; test++)
            {
                cout << "Please enter the password: ";
                cin >> password;
                if(vectorOfTheUsers[i].password == password)
                {
                    cout << "You are already logged in" << endl;
                    Sleep(1000);
                    return vectorOfTheUsers[i].userId;
                }
            }
            cout << "You have just entered wrong password 3 times. Wait 3 seconds and try again" << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout <<"There is no such user name" << endl;
    Sleep(1500);
    return 0;
}
void splitTheUserIntoSeparateDataAndAddThemToTheAppriopiateFieldsOfTheObject (string theLineFromTheTextFile, UserOfTheAdressBook structOfTheUsers, vector < UserOfTheAdressBook > &vectorOfTheUsers)
{
    int userId;
    string userName, password;
    string substr;

    stringstream theLineToSplitToSeparateData;
    theLineToSplitToSeparateData << theLineFromTheTextFile;
    getline( theLineToSplitToSeparateData, substr, '|' );
    structOfTheUsers.userId = atoi(substr.c_str());
    getline( theLineToSplitToSeparateData, substr, '|' );
    structOfTheUsers.userName = substr;
    getline( theLineToSplitToSeparateData, substr, '|' );
    structOfTheUsers.password = substr;

    vectorOfTheUsers.push_back(structOfTheUsers);
}
void splitTheContactIntoSeparateDataAndAddThemToTheAppriopiateFieldsOfTheObject (string theLineFromTheTextFile, Person person, vector < Person > &people, int idLoggedInUser)
{
    string name, surname, phoneNumber, emailAddress, address;
    int id, userId;
    string substr;

    stringstream theLineToSplitToSeparateData;
    theLineToSplitToSeparateData << theLineFromTheTextFile;
    getline( theLineToSplitToSeparateData, substr, '|' );
    person.id = atoi(substr.c_str());
    getline( theLineToSplitToSeparateData, substr, '|' );
    person.userId = atoi(substr.c_str());
    getline( theLineToSplitToSeparateData, substr, '|' );
    person.name = substr;
    getline( theLineToSplitToSeparateData, substr, '|' );
    person.surname = substr;
    getline( theLineToSplitToSeparateData, substr, '|' );
    person.phoneNumber = substr;
    getline( theLineToSplitToSeparateData, substr, '|' );
    person.emailAddress = substr;
    getline( theLineToSplitToSeparateData, substr, '|' );
    person.address = substr;

    if(idLoggedInUser == person.userId)
        people.push_back(person);

}
string gettingTheLastLineFromTheTextFile()
{
    string lineFromTheAdressBook;
    string gettingLine;
    ifstream myfile ("adresaci.txt");
    while (getline (myfile,lineFromTheAdressBook))
    {
        gettingLine = lineFromTheAdressBook;
    }
    myfile.close();
    return gettingLine;
}
void addTheContact(Person  person, vector < Person > &people, int idLoggedInUser)
{
    int personId, userId;
    string name, surname, phoneNumber, emailAddress, address;
    system("cls");
    cout << "Enter the name of the user: ";
    cin >> name;
    cout << "Enter the surname of the user: ";
    cin >> surname;
    cout << "Enter the phone number of the user: ";
    cin.sync();
    getline(cin, phoneNumber);
    cout << "Enter the email address of the user: ";
    cin >> emailAddress;
    cout << "Enter the address of the user: ";
    cin.sync();
    getline(cin, address);

    userId = idLoggedInUser;

    person.id = personId;
    person.userId = idLoggedInUser;
    person.name = name;
    person.surname = surname;
    person.phoneNumber = phoneNumber;
    person.emailAddress = emailAddress;
    person.address = address;

    string theLastLineFromTheTextFile, stringTheLastContactIdInTheTextFile;
    int theLastContactIdInTheTextFile;
    theLastLineFromTheTextFile = gettingTheLastLineFromTheTextFile();
    stringTheLastContactIdInTheTextFile = theLastLineFromTheTextFile.substr (0,1);
    theLastContactIdInTheTextFile = atoi(stringTheLastContactIdInTheTextFile.c_str());
    personId = theLastContactIdInTheTextFile + 1;
    fstream file;
    file.open("adresaci.txt", ios::out | ios::app);
    if (file.good())
    {
        file << personId << "|";
        file << userId << "|";
        file << name << "|";
        file << surname << "|";
        file << phoneNumber << "|";
        file << emailAddress << "|";
        file << address << "|" << endl;

        file.close();

        cout << endl << "New person has been added" << endl;
        Sleep(2000);
    }
    else
        cout << "Could not open file adresaci.txt " << endl;
    people.push_back(person);

}
void loadTheUsersFromTheFile(UserOfTheAdressBook structOfTheUsers, vector < UserOfTheAdressBook > &vectorOfTheUsers)
{
    fstream file;
    file.open("Users.txt",ios::in);
    if(file.good() == false)
        cout << "Could not open file Users.txt" << endl;
    string theLineFromTheTextFile;

    while(getline(file, theLineFromTheTextFile))
    {
        if(theLineFromTheTextFile.empty())
            continue;
        else
            splitTheUserIntoSeparateDataAndAddThemToTheAppriopiateFieldsOfTheObject(theLineFromTheTextFile, structOfTheUsers, vectorOfTheUsers);
    }
    file.close();
}
void loadTheAppriopriateContactsFromTheFile(Person  person, vector < Person > &people, int idLoggedInUser)
{
    fstream file;
    file.open("adresaci.txt",ios::in);
    if(file.good() == false)
        cout << "Could not open file adresaci.txt" << endl;
    string theLineFromTheTextFile;

    while(getline(file, theLineFromTheTextFile))
    {
        if(theLineFromTheTextFile.empty())
            continue;
        else
            splitTheContactIntoSeparateDataAndAddThemToTheAppriopiateFieldsOfTheObject(theLineFromTheTextFile, person, people, idLoggedInUser);
    }
    file.close();

}
void loadTheContactByTheName(vector < Person > &people)
{
    string name;
    bool ifThePersonWasFound = false;
    cout << "Enter the name of the user: ";
    cin >> name;
    int i = 0;
    int numberingOfFoundPeople = 1;
    while(i < people.size())
    {
        if(people[i].name == name)
        {
            cout << endl << numberingOfFoundPeople << "." << "Name: " << people[i].name << endl;
            cout << "  Surname: " << people[i].surname << endl;
            cout << "  Phone number: " << people[i].phoneNumber << endl;
            cout << "  Email Address: " << people[i].emailAddress << endl;
            cout << "  Address: " << people[i].address << endl;
            ifThePersonWasFound = true;
            numberingOfFoundPeople++;
        }
        i++;
    }
    if(ifThePersonWasFound == false)
        cout<< endl << "There is no such contact. Return to the main menu." << endl;
    cout << endl;
    system("Pause");
}
void loadTheContactByTheSurname(vector < Person > &people)
{
    string surname;
    bool ifThePersonWasFound = false;
    cout << "Enter the surname of the user: ";
    cin >> surname;
    int i = 0;
    int numberingOfFoundPeople = 1;
    while(i < people.size())
    {
        if(people[i].surname == surname)
        {
            cout << endl << numberingOfFoundPeople << "." << "Name: " << people[i].name << endl;
            cout << "  Surname: " << people[i].surname << endl;
            cout << "  Phone number: " << people[i].phoneNumber << endl;
            cout << "  Email Address: " << people[i].emailAddress << endl;
            cout << "  Address: " << people[i].address << endl;
            ifThePersonWasFound = true;
            numberingOfFoundPeople++;
        }
        i++;
    }
    if(ifThePersonWasFound == false)
        cout<<"There is no such contact. Return to the main menu" << endl << endl;
    cout << endl;
    system("Pause");
}
void displayAllContacts(vector < Person > &people)
{
    int i = 0;
    int numberingOfFoundPeople = 1;
    while(i < people.size())
    {
        cout << numberingOfFoundPeople << "." << "Name: " << people[i].name << endl;
        cout << "  Surname: " << people[i].surname << endl;
        cout << "  Phone number: " << people[i].phoneNumber << endl;
        cout << "  Email Address: " << people[i].emailAddress << endl;
        cout << "  Address: " << people[i].address << endl << endl;
        numberingOfFoundPeople++;
        i++;
    }
    system("Pause");
}
void deleteContact(vector < Person > &people, Person person, int idLoggedInUser)
{
    int contactIdWhichShouldBeDeleted, lineWhichShouldBeDeleted;
    char confirmationOfRemoval;
    cout << "Enter a contact ID: ";
    cin >> contactIdWhichShouldBeDeleted;
    int i = 0;
    while( i < people.size())
    {
        if(people[i].id == contactIdWhichShouldBeDeleted)
        {
            cout << endl << "Are you sure you want to permanently remove this contact? If yes, enter 'y': ";
            cin >> confirmationOfRemoval;
            cout << endl;
            if(confirmationOfRemoval == 'y')
            {
                people.erase(people.begin()+ i);
                int contactIdFromAdressBook;
                fstream file;
                file.open("adresaci.txt",ios::in);
                if(file.good() == false)
                    cout << "Could not open file adresaci.txt" << endl;
                string theLineFromTheTextFile, contactIdFromTheLine, userIdFromTheLine;
                string substr;
                int userIdFromTheAdressBook;
                ofstream temp("temp.txt");

                while(getline(file, theLineFromTheTextFile))
                {
                    userIdFromTheLine = theLineFromTheTextFile.substr (2,3);
                    userIdFromTheAdressBook = atoi(userIdFromTheLine.c_str());
                    contactIdFromTheLine = theLineFromTheTextFile.substr (0,1);
                    contactIdFromAdressBook = atoi(contactIdFromTheLine.c_str());
                    if(contactIdFromAdressBook == contactIdWhichShouldBeDeleted)
                    {
                        if(userIdFromTheAdressBook != idLoggedInUser)
                        {
                            cout << "There is no such assigned contact" << endl;
                            temp << theLineFromTheTextFile << endl;
                            Sleep(2000);
                        }
                        else
                            continue;
                    }
                    else
                        temp << theLineFromTheTextFile << endl;
                }
                file.close();
                temp.close();
                remove("adresaci.txt");
                rename( "temp.txt", "adresaci.txt" );
                break;
            }
            else
            {
                cout << "Another character has been entered. Return to the main menu. " << endl;
                Sleep(2000);
            }
        }
        ++i;
    }
}
void editContact(vector < Person > &people, Person person, int idLoggedInUser)
{
    int contactIdWhichWillBeEdit, choice;
    string newName, oldName, newSurname, newPhoneNumber, newEmailAddress, newAddress;
    int i = 0;
    cout << "Enter contact ID: ";
    cin >> contactIdWhichWillBeEdit;
    while( i < people.size())
    {
        if(people[i].id == contactIdWhichWillBeEdit)
        {
            cout << endl << "1 - name" << endl;
            cout << "2 - surname" << endl;
            cout << "3 - phoneNumber" << endl;
            cout << "4 - emailAddress" << endl;
            cout << "5 - address" << endl;
            cout << "6 - return to menu" << endl;

            cout << endl << "Select the option: ";
            cin >> choice;

            switch(choice)
            {
            case 1:
            {
                cout << endl << "Enter a new name: ";
                cin >> newName;
                people[i].name = newName;
                break;
            }
            case 2:
            {
                cout << endl << "Enter a new surname: ";
                cin >> newSurname;
                people[i].surname = newSurname;
                break;
            }
            case 3:
            {
                cout << endl << "Enter a new phone number: ";
                cin >> newPhoneNumber;
                people[i].phoneNumber = newPhoneNumber;
                break;
            }
            case 4:
            {
                cout << endl << "Enter a new email address: ";
                cin >> newEmailAddress;
                people[i].emailAddress = newEmailAddress;
                break;
            }
            case 5:
            {
                cout << endl << "Enter a new address: ";
                cin >> newAddress;
                people[i].address = newAddress;
                break;
            }
            case 6:
                break;
            }
        }
        ++i;
    }
    int contactIdFromAdressBook;
    fstream file;
    file.open("adresaci.txt",ios::in);
    if(file.good() == false)
        cout << "Could not open file adresaci.txt" << endl;
    string theLineFromTheTextFile, contactIdFromTheLine, userIdFromTheLine;
    string substr;
    int userId, userIdFromTheAdressBook;
    userId = idLoggedInUser;
    ofstream temp("temp.txt");

    while(getline(file, theLineFromTheTextFile))
    {
        userIdFromTheLine = theLineFromTheTextFile.substr (2,3);
        userIdFromTheAdressBook = atoi(userIdFromTheLine.c_str());
        contactIdFromTheLine = theLineFromTheTextFile.substr (0,1);
        contactIdFromAdressBook = atoi(contactIdFromTheLine.c_str());
        if(contactIdFromAdressBook == contactIdWhichWillBeEdit)
        {
            if(userIdFromTheAdressBook == idLoggedInUser)
            {
                for(int i = 0; i < people.size(); ++i)
                {
                    if(people[i].id == contactIdWhichWillBeEdit)
                    {
                        temp << people[i].id << "|";
                        temp << people[i].userId << "|";
                        temp << people[i].name << "|";
                        temp << people[i].surname << "|";
                        temp << people[i].phoneNumber << "|";
                        temp << people[i].emailAddress << "|";
                        temp << people[i].address << "|" << endl;
                    }
                }
            }
            else
            {
                cout << "There is no such assigned contact" << endl;
                temp << theLineFromTheTextFile << endl;
                Sleep(2000);
            }
        }
        else
            temp << theLineFromTheTextFile << endl;
    }
    file.close();
    temp.close();
    remove("adresaci.txt");
    rename( "temp.txt", "adresaci.txt" );
}
void changePassword(UserOfTheAdressBook structOfTheUsers, vector < UserOfTheAdressBook > &vectorOfTheUsers, int idLoggedInUser)
{
    string newPassword;
    cout << "Please enter the new password: ";
    cin >> newPassword;
    for(int i = 0; i < vectorOfTheUsers.size(); i++)
    {
        if(vectorOfTheUsers[i].userId == idLoggedInUser)
        {
            vectorOfTheUsers[i].password = newPassword;
            cout << "Password has been changed" << endl;
            Sleep(2000);
            break;
        }
    }
    fstream file;
    file.open("Users.txt", ios::out);
    if (file.good())
    {
        for(int i = 0; i < vectorOfTheUsers.size(); ++i)
        {
            file << vectorOfTheUsers[i].userId << "|";
            file << vectorOfTheUsers[i].userName << "|";
            file << vectorOfTheUsers[i].password << "|" << endl;
        }
        file.close();
    }
    else
    {
        cout << "Could not open file Users.txt " << endl;
        Sleep(2000);
    }
}
int main()
{
    Person person;
    vector < Person > people;
    UserOfTheAdressBook structOfTheUsers;
    vector < UserOfTheAdressBook > vectorOfTheUsers;
    int idLoggedInUser = 0;
    char choice;
    loadTheUsersFromTheFile(structOfTheUsers, vectorOfTheUsers);

    while(true)
    {
        if(idLoggedInUser == 0)
        {
            system("cls");
            cout << "  == ADDRESS BOOK ==  " << endl;
            cout << "1. Registration" << endl;
            cout << "2. Login" << endl;
            cout << "3. End of the program" << endl;

            cin >> choice;
            system("cls");

            if(choice == '1')
                registration(structOfTheUsers, vectorOfTheUsers);
            else if(choice == '2')
                idLoggedInUser = login(structOfTheUsers, vectorOfTheUsers, idLoggedInUser);
            else if(choice == '3')
                exit(0);
        }
        else
        {
            loadTheAppriopriateContactsFromTheFile(person, people, idLoggedInUser);
            system ("cls");
            cout << "1.Add new contact" << endl;
            cout << "2.Load contact by name" << endl;
            cout << "3.Load contact by surname" << endl;
            cout << "4.Display all contacts" << endl;
            cout << "5.Remove contact" << endl;
            cout << "6.Edit contact" << endl;
            cout << "7.Change password" << endl;
            cout << "8.Log out" << endl <<endl;
            cin >> choice;
            system ("cls");

            if(choice == '1')
                addTheContact(person, people, idLoggedInUser);
            else if(choice == '2')
                loadTheContactByTheName(people);
            else if(choice == '3')
                loadTheContactByTheSurname(people);
            else if(choice == '4')
                displayAllContacts(people);
            else if(choice == '5')
                deleteContact(people, person, idLoggedInUser);
            else if(choice == '6')
                editContact(people, person, idLoggedInUser);
            else if(choice == '7')
                changePassword(structOfTheUsers, vectorOfTheUsers, idLoggedInUser);
            else if(choice == '8')
                idLoggedInUser = 0;
            people.clear();
        }
    }
    return 0;
}
