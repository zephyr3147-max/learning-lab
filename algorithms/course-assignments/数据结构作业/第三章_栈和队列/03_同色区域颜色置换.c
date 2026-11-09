#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct PointNode
{
    int row;
    int col;
    struct PointNode* next;
} PointNode;

typedef struct
{
    PointNode* front;
    PointNode* rear;
} Queue;

/* 入队一个坐标。 */
void Enqueue(Queue* queue, int row, int col)
{
    PointNode* node = (PointNode*)malloc(sizeof(PointNode));
    if (node == NULL)
    {
        exit(1);
    }
    node->row = row;
    node->col = col;
    node->next = NULL;
    if (queue->rear == NULL)
    {
        queue->front = node;
        queue->rear = node;
    }
    else
    {
        queue->rear->next = node;
        queue->rear = node;
    }
}

/* 出队；调用前保证队列非空。 */
void Dequeue(Queue* queue, int* row, int* col)
{
    PointNode* node = queue->front;
    *row = node->row;
    *col = node->col;
    queue->front = node->next;
    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }
    free(node);
}

/* 邻居在界内且颜色等于 oldColor 时，染色并入队。 */
void TryPaint(int* image, int rows, int cols, int row, int col,
                     int oldColor, int newColor, Queue* queue)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        return;
    }
    if (image[row * cols + col] != oldColor)
    {
        return;
    }
    image[row * cols + col] = newColor; /* 先染色，避免重复入队。 */
    Enqueue(queue, row, col);
}

int main(void)
{
    int rows;
    int cols;
    scanf("%d%d", &rows, &cols);

    /* 题面要求二维颜色矩阵，这里用连续内存模拟 image[rows][cols]。 */
    int* image = (int*)malloc((size_t)rows * (size_t)cols * sizeof(int));
    if (image == NULL)
    {
        exit(1);
    }
    for (int i = 0; i < rows * cols; ++i)
    {
        scanf("%d", &image[i]);
    }

    int startRow;
    int startCol;
    int newColor;
    scanf("%d%d%d", &startRow, &startCol, &newColor);
    --startRow; /* 题面坐标从 1 开始，数组下标从 0 开始。 */
    --startCol;

    if (startRow >= 0 && startRow < rows && startCol >= 0 && startCol < cols)
    {
        int oldColor = image[startRow * cols + startCol];
        if (oldColor != newColor)
        {
            Queue queue = {NULL, NULL};
            Enqueue(&queue, startRow, startCol);
            image[startRow * cols + startCol] = newColor;

            while (queue.front != NULL)
            {
                int row;
                int col;
                Dequeue(&queue, &row, &col);
                TryPaint(image, rows, cols, row - 1, col, oldColor, newColor, &queue);
                TryPaint(image, rows, cols, row + 1, col, oldColor, newColor, &queue);
                TryPaint(image, rows, cols, row, col - 1, oldColor, newColor, &queue);
                TryPaint(image, rows, cols, row, col + 1, oldColor, newColor, &queue);
            }
        }
    }

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            if (col > 0)
            {
                putchar(' ');
            }
            printf("%d", image[row * cols + col]);
        }
        putchar('\n');
    }
    free(image);
    return 0;
}
