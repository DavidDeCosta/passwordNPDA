//Name: David DeCosta
//Date: 11/9/2022
/*Program Description:
                        This program implements a NPDA that validates whether a password compiles
                        given requirements. The requirements as of now are the NDPA will accept
                        E={a,b,0,1}. The password can be arbitrarily long, will contain 1 letter and 1 digit,
                        and must contain more letters than digits.
*/

#include <iostream>
#include <map>
#include <stack>
#include <vector>

using namespace std;

void checkAccepted(string password , map <tuple<string, char, char>, pair<string,char>> m, stack<char> myStack);

int main()
{

    string password;

    map <tuple<string, char, char>, pair<string,char>> justAMap;

    stack<char> myStack;

    justAMap[{"Q0", '1', 'z'}] = {"Q0", 'D'}; // push
    justAMap[{"Q0", '0', 'z'}] = {"Q0", 'D'}; // push
    justAMap[{"Q0", 'a', 'z'}] = {"Q0", 'L'}; // push
    justAMap[{"Q0", 'b', 'z'}] = {"Q0", 'L'}; // push
    justAMap[{"Q0", '1', 'D'}] = {"Q0", 'D'}; // push
    justAMap[{"Q0", '0', 'D'}] = {"Q0", 'D'}; // push
    justAMap[{"Q0", 'a', 'L'}] = {"Q0", 'L'}; // push
    justAMap[{"Q0", 'b', 'L'}] = {"Q0", 'L'}; // push
    justAMap[{"Q0", '1', 'L'}] = {"Q1", '~'}; // pop
    justAMap[{"Q0", '0', 'L'}] = {"Q1", '~'}; // pop
    justAMap[{"Q0", 'a', 'D'}] = {"Q1", '~'}; // pop
    justAMap[{"Q0", 'b', 'D'}] = {"Q1", '~'}; // pop
    justAMap[{"Q1", '1', 'L'}] = {"Q1", '~'}; // pop
    justAMap[{"Q1", '0', 'L'}] = {"Q1", '~'}; // pop
    justAMap[{"Q1", 'a', 'D'}] = {"Q1", '~'}; // pop
    justAMap[{"Q1", 'b', 'D'}] = {"Q1", '~'}; // pop
    justAMap[{"Q1", '1', 'D'}] = {"Q1", 'D'}; // push
    justAMap[{"Q1", '0', 'D'}] = {"Q1", 'D'}; // push'
    justAMap[{"Q1", 'a', 'L'}] = {"Q1", 'L'}; // push
    justAMap[{"Q1", 'b', 'L'}] = {"Q1", 'L'}; // push
    justAMap[{"Q1", '~', 'L'}] = {"Q2", 'L'}; // do nothing


    while(true)
    {
        cout << "Enter a password (Ctrl^C to end): \n";
        cin >> password;

        for(int i = 0; i < password.length();i++)
        {
            if(password[i] != 'a' && password[i] != 'b' && password[i] != '0' && password[i] !='1')
            {
                exit(0);
            }
        }

           checkAccepted(password, justAMap,myStack);
    }


    return 0;
}

void checkAccepted(string password, map <tuple<string, char, char>, pair<string,char>> m, stack<char> myStack)
{

    string currstate = "Q0";                       //always start at Q0 but will update after every itteration
    string nextstate = " ";                        //will be assigned by the make_tuple function return
    string finalState = "Q2";


//    password.insert(0, "~");                          //make the password terminate with lambda
    myStack.push('z');                              //start the stack with z on the top
    char c = myStack.top();



    cout <<"   (" + currstate + " ,";
    cout << password << " , ";
    cout << myStack.top() << " )\n";

    pair<string, char> t;

    int j;                                            //for the loop
    int length = password.length();


    for(j = 0; j < password.length(); j++)
    {

        t = m[make_tuple(currstate,password[j], c)];
        nextstate = t.first;                          //defined from the map returns the next state
        c = t.second;                                 //desfine from the map returns what should happen on the stack (push or pop)

        if(c == 'L')
        {
            myStack.push('L');
        }
        else if(c == 'D')
        {
            myStack.push('D');
        }
        else if(c == '~')
        {
            myStack.pop();
        }
        else
        {

        }

        password.pop_back();
        cout << "|- (" << nextstate << ", " << password <<" , " << myStack.top() << ") \n" ;
        

        currstate = nextstate;
    }
    
    if(currstate == finalState)
    {
        cout << " : Accepted \n";
    }
    else
    {
        cout << " : Rejected \n";
    }   

}

