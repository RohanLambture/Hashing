#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <map>
#include <math.h>
using namespace std;

bool compare(pair<string, int> &a, pair<string, int> &b)
{
    return a.second > b.second;
}
vector<pair<string, int>> Sort_theMap(map<string, int> &M)
{
    vector<pair<string, int>> vect;
    for (auto &i : M)
    {
        vect.push_back(i);
    }
    sort(vect.begin(), vect.end(), compare);
    return vect;
}
long long int power_function(int a, int b)
{
    if (b == 0)
    {
        return 1;
    }
    else if (b == 1)
    {
        return a;
    }
    long long int temp = power_function(a, b / 2);
    if (b % 2 == 0)
    {
        return temp * temp;
    }
    else
    {
        return a * temp * temp;
    }
}
class PhoneRecord
{
private:
    string name;
    string organisation;
    vector<string> phoneNumbers;

public:
    // Constructor
    PhoneRecord(const string &n, const string &org, const vector<string> &numbers)
        : name(n), organisation(org), phoneNumbers(numbers) {}

    // Getter methods
    string getName() const
    {
        return name;
    }

    string getOrganisation() const
    {
        return organisation;
    }

    vector<string> getPhoneNumbers() const
    {
        return phoneNumbers;
    }
};
class HashTableRecord
{
private:
    int key;
    PhoneRecord *element; // Pointer to PhoneRecord
    HashTableRecord *next;

public:
    // Constructor
    HashTableRecord(int k, PhoneRecord *rec)
        : key(k), element(rec), next(nullptr) {}

    // Getter methods
    int getKey() const
    {
        return key;
    }

    PhoneRecord *getRecord() const
    {
        return element;
    }

    HashTableRecord *getNext() const
    {
        return next;
    }

    void setNext(HashTableRecord *nxt)
    {
        next = nxt;
    }
};

class PhoneBook
{
private:
    static const int HASH_TABLE_SIZE = 263;
    HashTableRecord *hashTable[HASH_TABLE_SIZE];

public:
    // Constructor
    PhoneBook()
    {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i)
        {
            hashTable[i] = nullptr;
        }
    }

    // Add your own implementation for hashing
    long long computeHash(const string &str)
    {
        long long int mod = 0;
        long long int p = 1e9 + 7;
        int x = HASH_TABLE_SIZE;
        long long int m = 263;
        // long long int val2= (long long int) p;
        for (int i = 0; i < str.length(); i++)
        {
            // long long int val = (long long int)pow(x, i);
            mod += ((int)str[i] * ((long long int)power_function(x, i) % p));
        }
        // mod = mod % p;
        mod = mod % m;
        return mod;
    }

    // Add your own implementation for adding a contact
    void addContact(const PhoneRecord *record) // why const
    {
        string input = record->getName();
        string new_orgn = record->getOrganisation();
        vector<string> phVec = record->getPhoneNumbers();
        PhoneRecord* newPR = new PhoneRecord(input,new_orgn,phVec);
        istringstream s(input);
        string word;
        while (s >> word)
        {
            long long int key = computeHash(word);
            HashTableRecord *Record = new HashTableRecord(key, newPR); // what is problem with the const keyword
            if (hashTable[key] == nullptr)
            {
                hashTable[key] = Record;
            }
            else
            {
                Record->setNext(hashTable[key]);
                hashTable[key] = Record;
            }
        }
    }

    // Add your own implementation for deleting a contact
    bool deleteContact(const string *searchName)
    {
        string n = *searchName;
        vector<PhoneRecord *> dup = fetchContacts(&n);
        if (dup.size() == 0)
        {
            return false;
        }
        string name = dup[0]->getName();
        string word1;
        stringstream sss(name);
        bool flag = false, ans = false;
        while (sss >> word1)
        {
            int position = 1;
            int k = computeHash(word1);
            HashTableRecord *temp = hashTable[k];
            while (temp != NULL)
            {
                if (temp->getRecord()->getName() == name)
                {
                    flag = true;
                    ans = true;
                    break;
                }
                position++;
                temp = temp->getNext();
            }
            if (flag)
            {
                HashTableRecord *temp1 = hashTable[k];
                if (position == 1)
                {
                    hashTable[k] = temp1->getNext();
                }
                else
                { // why it is not working
                    for (int j = 0; j < position - 2; j++)
                    {
                        temp1 = temp1->getNext();
                    }
                    temp = temp1->getNext();
                    temp1->setNext(temp->getNext());
                    free(temp);
                }
            }
        }
        return ans;
        // all the records with the name or only record matching the full name
    }

    // Add your own implementation for fetching contacts
    vector<PhoneRecord *> fetchContacts(const string *query)
    {
        vector<PhoneRecord *> output;
        vector<PhoneRecord *> answer;
        map<string, int> sort_map;
        string line = *query;
        stringstream iss(line);
        string word;
        while (iss >> word)
        {
            long long int key = computeHash(word);
            HashTableRecord *pt = hashTable[key];
            while (pt != NULL)
            {
                string name = pt->getRecord()->getName();
                stringstream is(name);
                string str;
                while (is >> str)
                {
                    if (str == word)
                    {
                        sort_map[pt->getRecord()->getName()]++;
                        output.push_back(pt->getRecord());
                    }
                }
                pt = pt->getNext();
            }
        }
        vector<pair<string, int>> ans;
        ans = Sort_theMap(sort_map);
        for (auto &it : ans)
        {
            for (auto &ite : output)
            {
                if (it.first == ite->getName())
                {
                    answer.push_back(ite);
                }
            }
        }

        return answer;
    }

    // void traversal()
    // {
    //     for (int i = 0; i < HASH_TABLE_SIZE; i++)
    //     {
    //         HashTableRecord *head = hashTable[i];
    //         while (head != nullptr)
    //         {
    //             cout <<  head->getKey() << endl;
    //             cout <<  head->getRecord()->getName() << endl;
    //             cout <<  head->getRecord()->getOrganisation() << endl;
    //             head = head->getNext();
    //         }
    //     }
    // }

    // Add your own implementation for counting records pointing to a contact
    int countRecordsPointingTo(const PhoneRecord *record) const
    {
        string name = record->getName();
        stringstream ms(name);
        string w;
        int count = 0;
        while (ms >> w)
        {
            count++;
        }
        return count;
    }

    // Add your own implementation for reading records from a file
    void readRecordsFromFile(const string &filename)
    {
        fstream fin;
        fin.open(filename, ios::in);
        string line;
        string name, temp, organisation;
        // PhoneBook Book;
        while (getline(fin, line))
        {
            stringstream s(line);
            getline(s, name, ',');
            vector<string> phoneNumber;
            while (getline(s, temp, ','))
            {
                phoneNumber.push_back(temp);
            }
            organisation = phoneNumber.back();
            phoneNumber.pop_back();
            PhoneRecord *P1 = new PhoneRecord(name, organisation, phoneNumber);
            addContact(P1);
            // test.push_back(P1);
        }
    }
    // Destructor
    ~PhoneBook()
    {
    }
};

// void read_file(string file_path){
//     // fstream fin;
//     // fin.open(file_path,ios::in);
//     // string line;
//     // string name,temp,organisation;
//     // PhoneBook Book;
//     // while(getline(fin,line)){
//     //     stringstream s(line);
//     //     getline(s,name,',');
//     //     vector<string>phoneNumber;
//     //     while(getline(s,temp,',')){
//     //         phoneNumber.push_back(temp);
//     //     }
//     //     organisation=phoneNumber.back();
//     //     phoneNumber.pop_back();
//     //     PhoneRecord P1(name,organisation,phoneNumber);
//     //     Book.addContact(&P1);
//     // }
// }
// int main()
// {
//     PhoneBook Book;
//     // Your test cases and program logic can go here.
//     Book.readRecordsFromFile("Details.txt");
//     vector<string> phoneNumbers1 = {"1234567890", "4567891230"};
//     PhoneRecord record1("John Doe Rohan Lambture Ravindra Rahul Aansh", "Company A", phoneNumbers1);
//     cout << Book.countRecordsPointingTo(&record1) << endl;
//         // for(int i=0;i<test.size();i++){
//         //     cout << test[i].getName();
//         //     cout << "   ";
//         //     cout << test[i].getOrganisation() << endl;
//         // }
//         return 0;
// }
