#ifndef SOKOBAN_H
#define SOKOBAN_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int COLUMNS=8;
const int ROWS=6;


class Sokoban
{
private:  //in this part all characters are defined as static const since they are not going to modified.
    static const char MAN='@' ;
    static const char MAN_ON_TARGET='+' ;
    static const char BOX ='$' ;
    static const char BOX_ON_TARGET='*' ;
    static const char SPACE=' ' ;
    static const char WALL='#'  ;
    static const char TARGET_POINT='.' ;



    char **mArr=nullptr; // we have a member pointer pointing to a pointer(because we will use 2D array) which shows null pointer at the beginning.
    void set_mArr(char **arr); //this is the method sets the member 2D array to given char array.
    int man_row, man_column; //these are row and column numbers of the player, will be used in move methods

    void find_location() // this method helps to find the player's row and column numbers either it is on a target point or not.
    {

        for(int i=0; i<ROWS; i++)
        {
            for (int j=0; j<COLUMNS; j++)
            {
                if(mArr[i][j]==MAN || mArr[i][j]==MAN_ON_TARGET) // while going through the already set array by using for loops, we are searching for player
                {
                    man_row=i;
                    man_column=j;
                    //cout<<i<<" "<<j<<endl;

                }
            }
        }
    }




public:
    Sokoban(); //constructor for Sokoban class
    Sokoban(char **arr); //constructor with parameter to initialize member data
    Sokoban(const Sokoban &skb); //create a copy of the input object
    Sokoban &operator = (const Sokoban &rhs); //assignment operator
    Sokoban(string &path); //constructor which initializes from a text file
    ~Sokoban();
// following four methods for moving the player
    bool move_up();
    bool move_down();
    bool move_left();
    bool move_right();
    bool is_solved() const; // this method returns true if the puzzle is solved

    void print_puzzle() const; //this method prints the current puzzle
    void print_Adress() const; //this method prints the address of member array (**mArr)







};

Sokoban::Sokoban()
{

}


Sokoban::Sokoban(char **arr) //constructor, sets the member array to input array
{
    set_mArr(arr);

}

void Sokoban::set_mArr(char **arr) //method that sets the input array to member array
{
    mArr= new char*[ROWS]; //since we use **mArr, first char pointers for each row is created.


    for (int i=0;i<ROWS;i++) //then by using a for loop, columns are created for the each row pointers and we get 2D array
    {
        mArr[i]= new char[COLUMNS];

        for (int j=0; j<COLUMNS; j++)
        {
            mArr[i][j]=arr[i][j];
        }

    }
    find_location(); //location of the player is set
}



Sokoban::Sokoban(const Sokoban &skb) //copy constructor to create a copy object
{
    if(skb.mArr == nullptr) //if the member array of copy object shows null pointer, it returns
    {
        return;
    }

    set_mArr(skb.mArr); //if not, we build another identical array by using set method


}


Sokoban& Sokoban:: operator = (const Sokoban &rhs) //assignment operator
{
    if (mArr!=nullptr) //this method first deletes the mArr if it does not show null pointer
    {
        for(int i=0;i<ROWS;i++) //we delete it as the reverse order we created the 2D array
        {
            delete[] mArr[i];
        }
        delete[] mArr;
    }
    if(rhs.mArr == nullptr) //then it creates, as the copy constructor, o new object where its member array shows null pointer
    {
        return *this; //operator returns current member by using *this
    }

    set_mArr(rhs.mArr); //then we set given array to new created array
    return *this;


}
Sokoban:: Sokoban(string &path) //constructor reads from a text file
{
    /* code segment to read the */
    /* sample file into a char array */
    /* you can use relative path if */
    /* the file is in project folder */

    /* contents of the file will be */
    /* stored in this array */
    char **data;                         //here I have changed the declaration of data since I have used as **mArr the char array
    /* newline character will be */
    /* read in dummy */
    char dummy;
    /* input file stream */
    ifstream file;
    file.open(path);

    data= new char *[ROWS];     //data named 2D char array is created first the row pointers, then columns are created for the each row pointer
    for (int i=0;i<ROWS;i++)
    {
        data[i]= new char[COLUMNS];

        for (int j=0; j<COLUMNS; j++) //following are the reading operations from a file
        {
            file >> noskipws >> data[i][j];
        }
        file >> noskipws >> dummy;
    }

    set_mArr(data); // and we set already read char array data to member array by using this method
}


//following four methods are for move operations of the player, they have same idea with slightly different code

bool Sokoban::move_up() // by considering the possibilities, the row number of the player is decreased and the characters are set accordingly
{
    if(mArr[man_row-1][man_column]== WALL) //if there is wall above the player it returns false
    {
        return false;
    }
    if(mArr[man_row-1][man_column]== SPACE) //if there is a blank above the player, we check the current position of the player first whether it is on a target point or not
    {
        if(mArr[man_row][man_column]==MAN)
        {
            mArr[man_row][man_column]=SPACE;
        }
        else if(mArr[man_row][man_column]==MAN_ON_TARGET)
        {
            mArr[man_row][man_column]=TARGET_POINT;
        }
        mArr[man_row-1][man_column]= MAN;
        man_row=man_row-1;

    }
    else if(mArr[man_row-1][man_column]== TARGET_POINT)// if there is a target point above the player, again we check the current position whether it is a target point or not
    {
        if(mArr[man_row][man_column]==MAN)
        {
            mArr[man_row][man_column]=SPACE;
        }
        else if(mArr[man_row][man_column]==MAN_ON_TARGET)
        {
            mArr[man_row][man_column]=TARGET_POINT;
        }
        mArr[man_row-1][man_column]= MAN_ON_TARGET;
        man_row=man_row-1;
    }
    else if(mArr[man_row-1][man_column]== BOX || mArr[man_row-1][man_column]== BOX_ON_TARGET) //it there is a box above the player, we check the player can move the box to forward or not (whether there is another box or wall beyond the box)
    {
        if(mArr[man_row-2][man_column]==WALL || mArr[man_row-2][man_column]== BOX || mArr[man_row-2][man_column]== BOX_ON_TARGET)
        {
            return false;
        }
        if(mArr[man_row-2][man_column]== SPACE)
        {
            mArr[man_row-2][man_column]=BOX;
            if(mArr[man_row-1][man_column]== BOX_ON_TARGET)
            {
                mArr[man_row-1][man_column]=MAN_ON_TARGET;
            }
            else if(mArr[man_row-1][man_column]==BOX)
            {
                mArr[man_row-1][man_column]=MAN;
            }

            if(mArr[man_row][man_column]==MAN)
            {
                mArr[man_row][man_column]=SPACE;
            }
            else if(mArr[man_row][man_column]==MAN_ON_TARGET)
            {
                mArr[man_row][man_column]=TARGET_POINT;
            }
            man_row=man_row-1;
        }


        if(mArr[man_row-2][man_column]== TARGET_POINT) //
        {
            mArr[man_row-2][man_column]=BOX_ON_TARGET;
            if(mArr[man_row-1][man_column]== BOX_ON_TARGET)
            {
                mArr[man_row-1][man_column]=MAN_ON_TARGET;
            }
            else if(mArr[man_row-1][man_column]==BOX)
            {
                mArr[man_row-1][man_column]=MAN;
            }

            if(mArr[man_row][man_column]==MAN)
            {
                mArr[man_row][man_column]=SPACE;
            }
            else if(mArr[man_row][man_column]==MAN_ON_TARGET)
            {
                mArr[man_row][man_column]=TARGET_POINT;
            }
            man_row=man_row-1;
        }

    }

    return true;
}

bool Sokoban::move_down() //in this move down method, we do the similar thing in th move up method, only difference is we increase the row number and we check the characters below the player
{
     if(mArr[man_row+1][man_column]== WALL)
    {
        return false;
    }
    if(mArr[man_row+1][man_column]== SPACE)
    {
        if(mArr[man_row][man_column]==MAN)
        {
            mArr[man_row][man_column]=SPACE;
        }
        else if(mArr[man_row][man_column]==MAN_ON_TARGET)
        {
            mArr[man_row][man_column]=TARGET_POINT;
        }
        mArr[man_row+1][man_column]= MAN;
        man_row=man_row+1;

    }
    else if(mArr[man_row+1][man_column]== TARGET_POINT)
    {
        if(mArr[man_row][man_column]==MAN)
        {
            mArr[man_row][man_column]=SPACE;
        }
        else if(mArr[man_row][man_column]==MAN_ON_TARGET)
        {
            mArr[man_row][man_column]=TARGET_POINT;
        }
        mArr[man_row+1][man_column]= MAN_ON_TARGET;
        man_row=man_row+1;
    }
    else if(mArr[man_row+1][man_column]== BOX || mArr[man_row+1][man_column]== BOX_ON_TARGET)
    {
        if(mArr[man_row+2][man_column]==WALL || mArr[man_row+2][man_column]== BOX || mArr[man_row+2][man_column]== BOX_ON_TARGET)
        {
            return false;
        }
        if(mArr[man_row+2][man_column]== SPACE)
        {
            mArr[man_row+2][man_column]=BOX;
            if(mArr[man_row+1][man_column]== BOX_ON_TARGET)
            {
                mArr[man_row+1][man_column]=MAN_ON_TARGET;
            }
            else if(mArr[man_row+1][man_column]==BOX)
            {
                mArr[man_row+1][man_column]=MAN;
            }

            if(mArr[man_row][man_column]==MAN)
            {
                mArr[man_row][man_column]=SPACE;
            }
            else if(mArr[man_row][man_column]==MAN_ON_TARGET)
            {
                mArr[man_row][man_column]=TARGET_POINT;
            }
            man_row=man_row+1;
        }


        if(mArr[man_row+2][man_column]== TARGET_POINT)
        {
            mArr[man_row+2][man_column]=BOX_ON_TARGET;
            if(mArr[man_row+1][man_column]== BOX_ON_TARGET)
            {
                mArr[man_row+1][man_column]=MAN_ON_TARGET;
            }
            else if(mArr[man_row+1][man_column]==BOX)
            {
                mArr[man_row+1][man_column]=MAN;
            }

            if(mArr[man_row][man_column]==MAN)
            {
                mArr[man_row][man_column]=SPACE;
            }
            else if(mArr[man_row][man_column]==MAN_ON_TARGET)
            {
                mArr[man_row][man_column]=TARGET_POINT;
            }
            man_row=man_row+1;
        }

    }

    return true;
}

bool Sokoban::move_left() //in this move left method, we do the similar thing in th move up and down methods, only difference is we decrease the column number and we check the characters on the left of the player
{
     if(mArr[man_row][man_column-1]== WALL)
    {
        return false;
    }
    if(mArr[man_row][man_column-1]== SPACE)
    {
        if(mArr[man_row][man_column]==MAN)
        {
            mArr[man_row][man_column]=SPACE;
        }
        else if(mArr[man_row][man_column]==MAN_ON_TARGET)
        {
            mArr[man_row][man_column]=TARGET_POINT;
        }
        mArr[man_row][man_column-1]= MAN;
        man_column=man_column-1;

    }
    else if(mArr[man_row][man_column-1]== TARGET_POINT)
    {
        if(mArr[man_row][man_column]==MAN)
        {
            mArr[man_row][man_column]=SPACE;
        }
        else if(mArr[man_row][man_column]==MAN_ON_TARGET)
        {
            mArr[man_row][man_column]=TARGET_POINT;
        }
        mArr[man_row][man_column-1]= MAN_ON_TARGET;
        man_column=man_column-1;
    }
    else if(mArr[man_row][man_column-1]== BOX || mArr[man_row][man_column-1]== BOX_ON_TARGET)
    {
        if(mArr[man_row][man_column-2]==WALL || mArr[man_row][man_column-2]== BOX || mArr[man_row][man_column-2]== BOX_ON_TARGET)
        {
            return false;
        }
        if(mArr[man_row][man_column-2]== SPACE)
        {
            mArr[man_row][man_column-2]=BOX;
            if(mArr[man_row][man_column-1]== BOX_ON_TARGET)
            {
                mArr[man_row][man_column-1]=MAN_ON_TARGET;
            }
            else if(mArr[man_row][man_column-1]==BOX)
            {
                mArr[man_row][man_column-1]=MAN;
            }

            if(mArr[man_row][man_column]==MAN)
            {
                mArr[man_row][man_column]=SPACE;
            }
            else if(mArr[man_row][man_column]==MAN_ON_TARGET)
            {
                mArr[man_row][man_column]=TARGET_POINT;
            }
            man_column=man_column-1;
        }


        if(mArr[man_row][man_column-2]== TARGET_POINT)
        {
            mArr[man_row][man_column-2]=BOX_ON_TARGET;
            if(mArr[man_row][man_column-1]== BOX_ON_TARGET)
            {
                mArr[man_row][man_column-1]=MAN_ON_TARGET;
            }
            else if(mArr[man_row][man_column-1]==BOX)
            {
                mArr[man_row][man_column-1]=MAN;
            }

            if(mArr[man_row][man_column]==MAN)
            {
                mArr[man_row][man_column]=SPACE;
            }
            else if(mArr[man_row][man_column]==MAN_ON_TARGET)
            {
                mArr[man_row][man_column]=TARGET_POINT;
            }
            man_column=man_column-1;
        }

    }

    return true;
}


bool Sokoban::move_right() //in this move right method, we do the similar things in th move up, down and left methods, only difference is we increase the column number and we check the characters on the right of the player
{
     if(mArr[man_row][man_column+1]== WALL)
    {
        return false;
    }
    if(mArr[man_row][man_column+1]== SPACE)
    {
        if(mArr[man_row][man_column]==MAN)
        {
            mArr[man_row][man_column]=SPACE;
        }
        else if(mArr[man_row][man_column]==MAN_ON_TARGET)
        {
            mArr[man_row][man_column]=TARGET_POINT;
        }
        mArr[man_row][man_column+1]= MAN;
        man_column=man_column+1;

    }
    else if(mArr[man_row][man_column+1]== TARGET_POINT)
    {
        if(mArr[man_row][man_column]==MAN)
        {
            mArr[man_row][man_column]=SPACE;
        }
        else if(mArr[man_row][man_column]==MAN_ON_TARGET)
        {
            mArr[man_row][man_column]=TARGET_POINT;
        }
        mArr[man_row][man_column+1]= MAN_ON_TARGET;
        man_column=man_column+1;
    }
    else if(mArr[man_row][man_column+1]== BOX || mArr[man_row][man_column+1]== BOX_ON_TARGET)
    {
        if(mArr[man_row][man_column+2]==WALL || mArr[man_row][man_column+2]== BOX || mArr[man_row][man_column+2]== BOX_ON_TARGET)
        {
            return false;
        }
        if(mArr[man_row][man_column+2]== SPACE)
        {
            mArr[man_row][man_column+2]=BOX;
            if(mArr[man_row][man_column+1]== BOX_ON_TARGET)
            {
                mArr[man_row][man_column+1]=MAN_ON_TARGET;
            }
            else if(mArr[man_row][man_column+1]==BOX)
            {
                mArr[man_row][man_column+1]=MAN;
            }

            if(mArr[man_row][man_column]==MAN)
            {
                mArr[man_row][man_column]=SPACE;
            }
            else if(mArr[man_row][man_column]==MAN_ON_TARGET)
            {
                mArr[man_row][man_column]=TARGET_POINT;
            }
            man_column=man_column+1;
        }


        if(mArr[man_row][man_column+2]== TARGET_POINT)
        {
            mArr[man_row][man_column+2]=BOX_ON_TARGET;
            if(mArr[man_row][man_column+1]== BOX_ON_TARGET)
            {
                mArr[man_row][man_column+1]=MAN_ON_TARGET;
            }
            else if(mArr[man_row][man_column+1]==BOX)
            {
                mArr[man_row][man_column+1]=MAN;
            }

            if(mArr[man_row][man_column]==MAN)
            {
                mArr[man_row][man_column]=SPACE;
            }
            else if(mArr[man_row][man_column]==MAN_ON_TARGET)
            {
                mArr[man_row][man_column]=TARGET_POINT;
            }
            man_column=man_column+1;
        }

    }

    return true;
}

bool Sokoban::is_solved() const //this method searches for any box character '$' in the array if it cannot find it returns true because it means that all the boxes are on the target point and the puzzle is solved
{
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLUMNS;j++)
        {
            if (mArr[i][j]==BOX)
                return false;

        }
    }
    cout<<"Puzzle is solved!"<<endl;
    return true;
}

void Sokoban::print_puzzle() const //this method prints the current puzzle
{
    int i,j;
    for (i=0;i<ROWS;i++)
    {
        for(j=0;j<COLUMNS;j++)
        {
            cout<<mArr[i][j];
        }
        cout<<endl;
    }
}
void Sokoban::print_Adress() const //this method just returns the address of member array and is used for testing to check the address of created copy of an object or assigned object have different address or not
{
    cout<<mArr<<endl;
}

Sokoban::~Sokoban() //destructor
{
    if (mArr!=nullptr) //this method first deletes the mArr if it does not show null pointer
    {
        for(int i=0;i<ROWS;i++) //we delete it as the reverse order we created the 2D array
        {
            delete[] mArr[i];
        }
        delete[] mArr;
    }
}



#endif // SOKOBAN_H
