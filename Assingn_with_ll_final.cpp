#include <bits/stdc++.h>
using namespace std;
#define cn cout << "NO" << endl;
#define cy cout << "YES" << endl;
#define ll long long
#define pb push_back
#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
#define go(v, n)                \
    for (int i = 0; i < n; i++) \
    {                           \
        cout << v[i] << " ";    \
    }
#define take(v, n)              \
    for (int i = 0; i < n; i++) \
    {                           \
        cin >> v[i];            \
    }
#define all(v) v.begin(), v.end()
const ll N = 1e18 + 1;
bool cmp(pair<ll, ll> &a, pair<ll, ll> &b)
{
    return a.first > b.first;
}
class player // Particular match mate Particular Player no  data
{
public:
    string matchDate;
    int runscore;
    int wicket_taken;
    string role;
    player *next;
    player(string m, int r, int w, string role)
    {
        this->matchDate = m; 
        this->runscore = r;
        this->wicket_taken = w;
        this->role = role;
        this->next = NULL;
    }
};
class player1 // store player's name and runs
{
public:
    string name;
    int runs;
    int wickets;
    player1 *next;
    player1(string s, int r, int w)
    {
        this->name = s;
        this->runs = r;
        this->wickets = w;
        this->next = NULL;
    }
};
vector<string> v;                                  // Player name store thase
map<string, player *> m;                           // One Player & his history
map<string, player1 *> batter, bowler;             // total batsman data , total bowler data //string->role , player1 -> statistical data
map<string, string> type;                          // Player name and role
map<string, player1 *> match_info;                 // date , and whole team player data
map<string, pair<player1 *, player1 *>> data_info; // date and head (1st player's data),tail
void sortedInsert(player *&head, player *temp, string role)
{
    if (role == "Batsman")
    {
        player *current;
        if (head == NULL || (head)->runscore <= temp->runscore)
        { // first 4 ; second value 4 thi pan nani
            temp->next = head;
            head = temp;
        }
        else
        {
            current = head;
            while (current->next != NULL && current->next->runscore > temp->runscore)
            {
                current = current->next;
            }
            temp->next = current->next;
            current->next = temp;
        }
    }
    else
    {
        player *current;
        if (head == NULL || (head)->wicket_taken <= temp->wicket_taken)
        {
            temp->next = head;
            head = temp;
        }
        else
        {
            current = head;
            while (current->next != NULL && current->next->wicket_taken > temp->wicket_taken)
            {
                current = current->next;
            }
            temp->next = current->next;
            current->next = temp;
        }
    }
}
void insertionSort(player *&head, string role)
{
    player *sorted = NULL;
    player *current = head;

    while (current != NULL)
    {
        player *next = current->next;
        sortedInsert(sorted, current, role); // to choose best suitable position
        current = next;
    }
    head = sorted;
}
void sortedInsertB(player1 *&head, player1 *temp, string role)
{
    if (role == "Batsman")
    {
        player1 *current;
        if (head == NULL || (head)->runs <= temp->runs)
        {
            temp->next = head;
            head = temp;
        }
        else
        {
            current = head;
            while (current->next != NULL && current->next->runs > temp->runs)
            {
                current = current->next;
            }
            temp->next = current->next;
            current->next = temp;
        }
    }
    else
    {
        player1 *current;
        if (head == NULL || (head)->wickets <= temp->wickets)
        {
            temp->next = head;
            head = temp;
        }
        else
        {
            current = head;
            while (current->next != NULL && current->next->wickets > temp->wickets)
            {
                current = current->next;
            }
            temp->next = current->next;
            current->next = temp;
        }
    }
}
void insertionSortB(player1 *&head, string role)
{
    player1 *sorted = NULL;
    player1 *current = head;

    while (current != NULL)
    {
        player1 *next = current->next;
        sortedInsertB(sorted, current, role);
        current = next;
    }
    head = sorted;
}
void displayPlayerBattingPerformance(string name, int len)
{
    player *temp = m[name]; // m[name] = <string,ll> -> name and nodes
    if (len < 3)
    {
        for (int i = 0; i < len; i++)
        {
            cout << temp->matchDate << "            " << temp->runscore << endl;
            temp = temp->next;
        }
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            cout << temp->matchDate << "            " << temp->runscore << endl;
            temp = temp->next;
        }
    }
}
void displayPlayerBowlingPerformance(string name, int len)
{
    player *temp = m[name];
    if (len < 3)
    {
        for (int i = 0; i < len; i++)
        {
            cout << temp->matchDate << "            " << temp->wicket_taken << endl;
            temp = temp->next;
        }
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            cout << temp->matchDate << "            " << temp->wicket_taken << endl;
            temp = temp->next;
        }
    }
}
void topBatsman(player1 *head, int l)
{
    cout << "Top three Batsman are:" << endl;
    if (l < 3)
    {
        for (int i = 0; i < l; i++)
        {
            cout << head->name << "            " << head->runs << endl;
            head = head->next;
        }
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            cout << head->name << "            " << head->runs << endl;
            head = head->next;
        }
    }
}
void topBowler(player1 *head, int l)
{
    cout << "Top three Bowlers are:" << endl;
    if (l < 3)
    {
        for (int i = 0; i < l; i++)
        {
            cout << head->name << "            " << head->wickets << endl;
            head = head->next;
        }
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            cout << head->name << "            " << head->wickets << endl;
            head = head->next;
        }
    }
}
int getlenght(player1 *head)
{
    int count = 0;
    while (head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}
int getlenght1(player *head)
{
    int count = 0;
    while (head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}
int main()
{
    int n;
    cout << "Enter the number of player info you want to add:";
    cin >> n;
    cin.ignore(); // to avoid enter functionality
    player1 *h1 = NULL;
    player1 *t1 = NULL;
    player1 *h2 = NULL;
    player1 *t2 = NULL;
    while (n--)
    {
        string name, role;
        cout << "Enter the name of the player:";
        getline(cin, name);
        v.push_back(name);
        player *head = NULL;
        player *tail = NULL;
        // cin>>name;
        int num;
        int run, wicket;
        int tr = 0, tw = 0;

    label:
        cout << "Enter the role of player in the team(Batsman/Bowler):";
        cin >> role;
        if (role != "Batsman" && role != "Bowler")
        {
            cout << "Enter valid input!" << endl;
            goto label;
        }
        cout << "Enter the number of matches information you want to add:";
        cin >> num;

        bool ba = false, bo = false;
        while (num--)
        {
            string date;
            cout << "Enter the Date of Match:";
            cin >> date;
            if (role == "Batsman")
            {
                ba = true;
                type[name] = role;
                cout << "Enter the runScored by the player in that match:";
                cin >> run;
                wicket = 0;
            }
            else if (role == "Bowler")
            {
                cout << "Enter the wicket taken by the bowler in that match:";
                type[name] = role;
                bo = true;
                cin >> wicket;
                run = 0;
            }
            tr += run;
            tw += wicket;
            if (m.find(name) == m.end()) // only one player is there
            {
                // m[name]=vector<player>();
                head = new player(date, run, wicket, role);
                head->next = tail;
                tail = head;
            }
            else
            {
                player *p = new player(date, run, wicket, role); // new player data
                tail->next = p;
                tail = tail->next;
            }
            player1 *p = new player1(name, run, wicket);
            if (match_info.find(date) == match_info.end()) // that date is not present
            {
                player1 *head1 = p;
                player1 *tail1 = p;
                head1->next = tail1;
                data_info[date] = make_pair(head1, tail1);
                match_info[date] = p;
            }
            else
            {
                data_info[date].second->next = p;                      // add new player
                data_info[date].second = data_info[date].second->next; // tail forwarded
                match_info[date]->next = p;                            // match info new player inserted
            }
            // m[name].push_back(p);
        }
        if (role == "Batsman")
        {
            if (h1 == NULL) // batsman head
            {
                h1 = new player1(name, tr, 0);
                h1->next = t1;
                t1 = h1;
            }
            else
            {
                // Batsman* t=new Batsman(name,tr);
                player1 *t = new player1(name, tr, 0); // new player inserted
                t1->next = t;
                t1 = t1->next;
            }
        }
        else
        {
            if (h2 == NULL) // bowler head
            {
                // h2=new Bowler(name,tw);
                h2 = new player1(name, 0, tw);
                h2->next = t2;
                t2 = h2;
            }
            else
            {
                player1 *t = new player1(name, 0, tw);
                // Bowler* t=new Bowler(name,tw);
                t2->next = t;
                t2 = t2->next;
            }
        }
        insertionSort(head, role); // player wise info sorting date wise with highest record in decreasing order
        insertionSortB(h1, role);  // batsman
        insertionSortB(h2, role);  // bowler
        // cout<<head->matchDate<<endl;

        // now data is obtained is sorted acc to runs

        m[name] = head; //-> head = runs,wicket,role

        if (ba)
            batter[name] = h1;
        if (bo)
            bowler[name] = h2;
        cin.ignore();
    }
    cout << endl;
    for (auto it1 : v) // name wise traverse
    {
        player *t = m[it1];    // if data is <3 ;
        ll le = getlenght1(t); // indicates that no of matches data
        if (type[it1] == "Batsman")
        {
            cout << "Player Name: " << it1 << endl;
            cout << endl;
            cout << "MatchDate           RunScored" << endl;
            displayPlayerBattingPerformance(it1, le);
        }
        else
        {
            cout << "Player Name:" << it1 << endl;
            cout << endl;
            cout << "MatchDate           WicketsTaken" << endl;
            displayPlayerBowlingPerformance(it1, le);
        }
        cout << "----------------------------------------------------------" << endl;
    }
    // cout<<h2->wickets<<endl;
    int l1, l2;
    l1 = getlenght(h1); // how much batman
    l2 = getlenght(h2); // how much bowler
    // cout<<l1<<" "<<l2<<endl;
    if (h1 != NULL)
    {
        topBatsman(h1, l1);
        cout << "----------------------------------------------------------" << endl;
    }
    if (h2 != NULL)
    {
        topBowler(h2, l2);
        cout << "----------------------------------------------------------" << endl;
    }
    while (true)
    {
    detail:
        string Date;
        cout << "Enter the date of the match whose information is required: ";
        cin >> Date;
        if (match_info.find(Date) == match_info.end())
        {
            cout << "NO Data Found for the Date!";
        }
        else
        {
            player1 *temp = data_info[Date].first; // string and pair's first element which is head
            while (temp != NULL)
            {
                cout << "Name: " << temp->name << endl;
                cout << "Role:" << type[temp->name] << endl;
                cout << "Runscored: " << temp->runs << endl;
                cout << "Wickets: " << temp->wickets << endl;
                temp = temp->next;
                cout << "----------------------------------------------------------" << endl;
            }
        }
        cout << "If you want some more information of a particular match then enter 1 else to end enter 0: ";
        int number;
        cin >> number;
        if (number == 0)
        {
            break;
        }
        else
        {
            goto detail;
        }
    }
    // cout<<"----------------------------------------------------------"<<endl;
    cout << "------------------------THANK YOU-------------------------" << endl;
}