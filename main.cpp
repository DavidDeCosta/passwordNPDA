//Name: David DeCosta
//Date: 11/9/2022
/*Program Description:
                        This program implements a DFA that validates whether a password compiles
                        given requirements. The requirements as of now are the DFA will accept
                        E={a,b,0,1} and must be 3 to 4 characters long while containing atleast one letter.
*/

#include <iostream>
#include <map>
#include <stack>
#include <vector>

using namespace std;

void checkAccepted(string password , map <tuple<string, string, char>, pair<string,string>> m, stack<char> myStack);

int main()
{

    string password;

    map <tuple<string, string, char>, pair<string,string>> justAMap;

    stack<char> myStack;
//    myStack.push('z');
//    myStack.push('D');
//    myStack.push('~');


    justAMap[{"Q0", "1", 'z'}] = {"Q0", "D"}; // push
    justAMap[{"Q0", "0", 'z'}] = {"Q0", "D"}; // push
    justAMap[{"Q0", "a", 'z'}] = {"Q0", "L"}; // push
    justAMap[{"Q0", "b", 'z'}] = {"Q0", "L"}; // push
    justAMap[{"Q0", "1", 'D'}] = {"Q0", "D"}; // push
    justAMap[{"Q0", "0", 'D'}] = {"Q0", "D"}; // push
    justAMap[{"Q0", "a", 'L'}] = {"Q0", "L"}; // push
    justAMap[{"Q0", "b", 'L'}] = {"Q0", "L"}; // push
    justAMap[{"Q0", "1", 'L'}] = {"Q1", "~"}; // pop
    justAMap[{"Q0", "0", 'L'}] = {"Q1", "~"}; // pop
    justAMap[{"Q0", "a", 'D'}] = {"Q1", "~"}; // pop
    justAMap[{"Q0", "b", 'D'}] = {"Q1", "~"}; // pop
    justAMap[{"Q1", "1", 'L'}] = {"Q1", "~"}; // pop
    justAMap[{"Q1", "0", 'L'}] = {"Q1", "~"}; // pop
    justAMap[{"Q1", "a", 'D'}] = {"Q1", "~"}; // pop
    justAMap[{"Q1", "b", 'D'}] = {"Q1", "~"}; // pop
    justAMap[{"Q1", "1", 'D'}] = {"Q1", "D"}; // push
    justAMap[{"Q1", "0", 'D'}] = {"Q1", "D"}; // push
    justAMap[{"Q1", "a", 'L'}] = {"Q1", "L"}; // push
    justAMap[{"Q1", "b", 'L'}] = {"Q1", "L"}; // push
    justAMap[{"Q1", "~", 'L'}] = {"Q2", "L"}; // do nothing



    while(true)
    {
        cout << "Enter a password (Ctrl^C to end): \n";
        cin >> password;

        myStack.push('z');
        for(int i = 0; i < password.length();i++)
        {
            if(password[i] == 'a' || password[i] == 'b')
            {
                myStack.push('L');
            }
            else if(password[i] == '0' || password[i] == '1')
            {
                myStack.push('D');
            }
            if(password[i] != 'a' && password[i] != 'b' && password[i] != '0' && password[i] !='1')
            {
                exit(0);
            }
        }

/*        while(!myStack.empty())
        {
            cout << myStack.top() << "\n";
            myStack.pop();
        }
*/

           checkAccepted(password, justAMap,myStack);
    }


    

    return 0;
}

void checkAccepted(string password, map <tuple<string, string, char>, pair<string,string>> m, stack<char> myStack)
{

    string currstate = "Q0";   //always start at Q0 but will update after every itteration
    string nextstate = " ";    //will be assigned by the make_pair function return
    string finalState1 = "Q2";
    char c;

    cout <<"(" + currstate + " ,";
    cout << password << " ,";
    cout << myStack.top() << " )";

    for(int j = 0; j < password.length(); j++)
    {
        auto t = make_tuple(currstate,password[j], c);
        
        cout  <<password[j] << " -> " << + "["+ nextstate + "]";
        if(j < password.length()-1)
        {
            cout << "-> ";
        }
        currstate = nextstate;
    }
    
    if(currstate == finalState1)
    {
        cout << " : Accepted \n";
    }
    else
    {
        cout << " : Rejected \n";
    }   

}


/*
void checkAccepted(string password, map <tuple<string, string, char>, pair<string,string>> m)
{

    string currstate = "Q0";   //always start at Q0 but will update after every itteration
    string nextstate = " ";    //will be assigned by the make_pair function return
    string finalState1 = "Q2";

    cout <<"[" + currstate + "]" << "- ";
    for(int j = 0; j < password.length(); j++)
    {
//        nextstate = m[make_pair(currstate,password[j])];
        cout  <<password[j] << " -> " << + "["+ nextstate + "]";
        if(j < password.length()-1)
        {
            cout << "-> ";
        }
        currstate = nextstate;
    }
    
    if(currstate == finalState1)
    {
        cout << " : Accepted \n";
    }
    else
    {
        cout << " : Rejected \n";
    }   

}
*/