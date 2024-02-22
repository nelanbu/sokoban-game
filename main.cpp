//Yagmur Eren
#include <iostream>
#include <string>
#include <fstream>
#include "include/StackQueue.h"
#include "include/StackQueue2.h"
#include "include/Sokoban.h"

using namespace std;

int main()
{
    //StackQueue <Sokoban> SQ   this must be out of comment to use Stackqueue
    StackQueue2 <Sokoban> SQ; //


    string path = "Sample_puzzle.txt"; //for reading from text file
    Sokoban S(path); //A Sokoban object is created from the path text file



    S.print_puzzle();
    char key_pressed=' ';
    cout<<"use w to move up, a to move right, s to move down, d to move left, z to undo the last move, r to print all steps you have done"<<endl;
    while(key_pressed!='r' && key_pressed!='R') //in this loop we get keyboard input to move the player and the puzzle is modified accordingly
    {

        cin >> key_pressed;
        Sokoban temp=S;
        switch (key_pressed)
        {
            case 'w':
            case 'W':

                if(S.move_up())
                {
                    SQ.push_front(temp);
                    S.print_puzzle();

                }

                break;


            case 's':
            case 'S':

                if(S.move_down())
                {

                    SQ.push_front(temp);
                    S.print_puzzle();

                }

                break;

            case 'a':
            case 'A':

                if(S.move_left())
                {

                    SQ.push_front(temp);
                    S.print_puzzle();

                }

                break;

            case 'd':
            case 'D':

                if(S.move_right())
                {

                    SQ.push_front(temp);
                    S.print_puzzle();

                }
                break;

            case 'z':
            case 'Z':

                if(!SQ.is_Empty())
                {

                    S=SQ.pop_front();
                    S.print_puzzle();
                }
                break;

            case 'r':
            case 'R':

                while(!SQ.is_Empty())
                {
                    Sokoban step=SQ.pop_rear();
                    step.print_puzzle();
                    //TO DO delete step??

                }
                S.print_puzzle(); //last state

                break;

        }


    }





    return 0;
    }






   /* S.move_up();
    S.print_puzzle();
    S.move_right();
    S.print_puzzle();

    S.move_down();
    S.print_puzzle();

    S.move_down();
    S.print_puzzle();

    S.move_right();
    S.print_puzzle();

    S.move_left();
    S.print_puzzle();


  /*  Sokoban S(A);
    cout<<"Sin adresi: "<<endl;
    S.print_Adress();
    S.print_puzzle();

    Sokoban S2(B);
    cout<<"S2nin adresi: "<<endl;
    S2.print_Adress();
    S2.print_puzzle();

    S2=S;
    S.print_puzzle();
    S2.print_puzzle();

    S.print_Adress();
    S2.print_Adress();*/


