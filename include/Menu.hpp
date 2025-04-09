#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include "HashTable.hpp"
#include "OpenAddressingHashTable.hpp"
#include "ClosedAddressingTable.hpp"
#include "Avl.hpp"
#include "CuckooHashingTable.hpp"


class Menu
{
protected:
      int userChoice = 0;
public:
      virtual void display() const = 0;
      virtual void run() = 0;
};

template <typename T1, typename T2>
class HashTableMenu : public Menu
{
protected: 
      std::unique_ptr<HashTable<T1, T2>> ht;
      const int exitOption = 4;
public:
      void display() const override;
      void run() override;

      template <typename T1, typename T2> friend class OperationMenu;
};

template <typename T1, typename T2>
class OperationMenu : public Menu
{
protected:
      std::unique_ptr<HashTable<T1, T2>> ht;
      const int exitOption = 3;
public:
    void display() const override;
    void run() override;

    template <typename T1, typename T2> friend class HashTableMenu;
};

class DataTypeMenu : public Menu
{
public:
    void display() const override;
    void run() override;
};


//Hash Table Menu

template <typename T1, typename T2>
void HashTableMenu<T1, T2>::display() const
{
      std::cout<<"------------------- Menu ------------------"<<std::endl;
      std::cout<<"1. Create an open addressing hash table"<<std::endl;
      std::cout<<"2. Create a closed addressing hash table"<<std::endl;
      std::cout<<"3. Create an AVL tree-based hash table"<<std::endl;
      std::cout<<"4. Create a Cuckoo hashing table"<<std::endl;
      std::cout<<"5. Exit program"<<std::endl;
      std::cout<<"--------------------------------------------"<<std::endl;
      std::cout<<"Choose one option from the menu:"<<std::endl;
}

template <typename T1, typename T2>
void HashTableMenu<T1, T2>::run()
{
      while ( userChoice != exitOption)
        {
            this->display();
            std::cin>>userChoice;

            switch(userChoice)
              {
                case 1:
                  {
                    int size;
                      std::cout << "Enter the size of the hash table: ";
                      std::cin >> size;
                      ht = std::make_unique<OpenAddressingTable<T1,T2>>(size);
                      break;
                  }

                case 2:
                  {
                    int size;
                      std::cout << "Enter the size of the hash table: ";
                      std::cin >> size;
                      ht = std::make_unique<ClosedAddressingTable<T1,T2>>(size);
                      break;
                  }

                case 3:
                  {
                    int size;
                    std::cout << "Enter the size of the hash table: ";
                    std::cin >> size;
                    ht = std::make_unique<AVL<T1,T2>>(size);
                      break;
                  }

                case 4:
                  {
                    int size;
                      std::cout << "Enter the size of the hash table: ";
                      std::cin >> size;
                      ht = std::make_unique<CuckooHashingTable<T1,T2>>(size);
                      break;
                  }

                case 5:
                  {
                    exit(0);
                    break;
                  }

                default:
                  {
                    std::cerr << "error: chosen option does not exist" << std::endl;
                    exit(1);
                  }
              }
           std::cout << "Press enter to continue";

        // Wait for enter
        std::cin.get();
        std::cin.get();
        
        system("cls");

        OperationMenu<T1, T2> m1;
        m1.ht = std::move(ht);
        m1.run();
    }             
}



//Operation Menu

template <typename T1, typename T2>
void OperationMenu<T1, T2>::display() const
{
      std::cout<<"------ Operation Menu ------"<<std::endl;
      std::cout<<"1. Insert"<<std::endl;
      std::cout<<"2. Remove"<<std::endl;
      std::cout<<"3. Exit structure menu"<<std::endl;
      std::cout<<"----------------------------"<<std::endl;
      std::cout<<"Choose an operation to perform: "<<std::endl;
}

template <typename T1, typename T2>
void OperationMenu<T1, T2>::run()
{
      T1 key;
      T2 value;

      while (userChoice != exitOption)
      {
        this->display();
        std::cin>>userChoice;

        switch (userChoice)
        {
            case 1:
            {
                std::cout<<"Enter key to be added: "<<std::endl;
                std::cin>>key;
                std::cout<<"Enter value: "<<std::endl;
                std::cin>>value;
                ht->insert(key, value);
                break;
            }
          
            case 2:
            {
                std::cout<<"Enter key to be removed: "<<std::endl;
                std::cin>>key;
                ht->remove(key);
                break;
            }
          
            case 3:
            {
                break;
            }
          
            default:
            {
                std::cerr<<"error: chosen option does not exist"<<std::endl;
                exit(1);
            }
        }

        std::cout<<"Press enter to continue"<<std::endl;

        // Wait for enter
        std::cin.get();
        std::cin.get();

        system("cls");
    }
}


//Data Type Menu

void DataTypeMenu::display() const
{
    std::cout << "----------" << std::endl;
    std::cout << "1. Int" << std::endl;
    std::cout << "2. Float" << std::endl;
    std::cout << "3. Char" << std::endl;
    std::cout << "4. String" << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << "Choose a data type to use with hash table: " << std::endl;
}

void DataTypeMenu::run()
{
    while (true)
    {
        this->display();
        std::cin>>userChoice;

        std::cout<<"Press enter to continue"<<std::endl;

        // Wait for enter
        std::cin.get();
        std::cin.get();

        system("cls");

        switch (userChoice)
        {
            case 1:
            {
                HashTableMenu<int,int> m1;
                m1.run();
                break;
            }
          
            case 2:
            {
                HashTableMenu<float,float> m2;
                m2.run();
                break;
            }
          
            case 3:
            {
                HashTableMenu<char,char> m3;
                m3.run();
                break;
            }
          
            case 4:
            {
                HashTableMenu<std::string,string> m4;
                m4.run();
                break;
            }
          
            default:
            {
                std::cerr<<"error: chosen option does not exist"<<std::endl;
                exit(1);
            }
        }
    }
}


#endif MENU_HPP
