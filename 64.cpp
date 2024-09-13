#include <./stdc++11.h>

using namespace std;

int getSmallestNeighbor(vector<vector<int>> & grid, int y, int x) {
    if (y - 1 < 0 && x - 1 < 0)
        return 0;
    else if (y - 1 < 0)
        return grid[y][x-1];
    else if (x - 1 < 0) {
        return grid[y-1][x];
    }

    return min(grid[y-1][x], grid[y][x-1]);
}

int minPathSum(vector<vector<int>>& grid) {
    int n = (int)grid.size();
    int m = (int)grid[0].size();

    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < m; ++x) {
            grid[y][x] += getSmallestNeighbor(grid, y, x);
        }
    }

    return grid[n - 1][m - 1];
}

int main() {
    //grid = [[1,3,1],[1,5,1],[4,2,1]]
    vector<vector<int>> test1{vector<int>{1,3,1}, vector<int>{1,5,1}, vector<int>{4,2,1}};
    cout << minPathSum(test1) << endl;
    //[[1,2,3],[4,5,6]]
    vector<vector<int>> test2{vector<int>{1,2,3}, vector<int>{4,5,6}};
    cout << minPathSum(test2) << endl;

    return 0;
}