#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int main()
{
    int rows, cols;
    if (!(std::cin >> rows >> cols) || rows <= 0 || cols <= 0)
    {
        return 0;
    }
    // The image itself is specified as a two-dimensional array.
    std::vector<std::vector<int>> image(rows, std::vector<int>(cols));
    for (auto &row : image)
    {
        for (int &color : row)
        {
            std::cin >> color;
        }
    }
    int row, col, replacement;
    std::cin >> row >> col >> replacement;
    --row;
    --col;
    if (row >= 0 && row < rows && col >= 0 && col < cols)
    {
        const int original = image[row][col];
        if (original != replacement)
        {
            std::queue<std::pair<int, int>> pending;
            pending.push({row, col});
            image[row][col] = replacement;
            const int dr[4] = {-1, 1, 0, 0};
            const int dc[4] = {0, 0, -1, 1};
            while (!pending.empty())
            {
                const auto point = pending.front();
                pending.pop();
                for (int direction = 0; direction < 4; ++direction)
                {
                    const int nextRow = point.first + dr[direction];
                    const int nextCol = point.second + dc[direction];
                    if (nextRow >= 0 && nextRow < rows && nextCol >= 0 && nextCol < cols
                        && image[nextRow][nextCol] == original)
                    {
                        image[nextRow][nextCol] = replacement;
                        pending.push({nextRow, nextCol});
                    }
                }
            }
        }
    }
    for (const auto &line : image)
    {
        for (int i = 0; i < cols; ++i)
        {
            std::cout << (i == 0 ? "" : " ") << line[i];
        }
        std::cout << '\n';
    }
    return 0;
}
