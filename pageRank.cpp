// Demonstration of page rank algorithm in C++

#include <bits/stdc++.h>
using namespace std;

void pageRank(vector<vector<int>> network, double df)  // implementation of page rank algorithm
{

    int n = network.size() - 1;

    vector<pair<double, int>> pgRank(n); // to store ranks of all pages

    for (int i = 0; i < n; i++)
    {
        pgRank[i] = {1.0, i + 1}; // initializing page ranks with 1
    }

    cout << "\nIteration 0" << ": \n";

    for (int i = 0; i < n; i++) // display initial ranks
    {
        cout << i + 1 << " - " << pgRank[i].first << "\n";
    }

    double prev = 0, curr = 0;
    int iteration = 0;

    for (iteration = 0; iteration < 100; iteration++) // iterating through all pages using random surfer model
    {
        vector<pair<double, int>> npgRank(n); // next iteration ranks

        for (int i = 0; i < n; i++)
        {
            npgRank[i] = {1 - df, i + 1}; // damping for randomness to jump to disconnected nodes
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j < network[i].size(); j++)
            {
                npgRank[network[i][j] - 1].first += df * (pgRank[i - 1].first / network[i].size()); // page rank calculation
            }
        }

        vector<pair<double, int>> temp = npgRank;

        sort(npgRank.begin(), npgRank.end());
        sort(pgRank.begin(), pgRank.end());

        pgRank = temp;
        cout << "\nIteration " << iteration + 1 << ": \n";

        for (int i = 0; i < n; i++) // display current iteration page ranks
        {
            curr += pgRank[i].first;
            cout << i + 1 << " - " << pgRank[i].first << endl;
        }

        if (abs(curr - prev) < 0.00001) // if the difference between page ranks in successive iterations is minimal, stop the iteration
        {
            break;
        }

        prev = curr;
        curr = 0;
    }

    cout << "\nPage Ranks: \n";

    sort(pgRank.begin(), pgRank.end());

    cout << "After " << iteration + 1 << " iterations: \n";

    for (int i = n - 1; i >= 0; i--) // display final rankings
    {
        cout << "Page=" << pgRank[i].second << "    Rank=" << n - i << "\n";
    }
}

int main(int argc, char const *argv[])
{
    int pages; // number of pages on the internet

    cout << "Enter the number of pages: ";
    cin >> pages;

    double df = 0.85; // damping factor fpgRank switches between disconnected nodes

    cout << "Enter value of damping factor between 0-1: ";
    cin >> df;

    vector<vector<int>> network(pages + 1); // network of pages connected in form of graph

    cout << "Enter the connection between pages in from->to format: \n\n";

    int from, to; // connection showing from->to relation

    while (cin >> from)
    {
        cin >> to;
        network[from].push_back(to);
    }

    pageRank(network, df); // sending network of pages to calculate ranks

    return 0;
}