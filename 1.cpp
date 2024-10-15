#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int** create_incidence_matrix(int** adjacency_matrix, size_t size) {
    int edge_count = 0;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = i + 1; j < size; ++j) {
            if (adjacency_matrix[i][j] == 1) {
                ++edge_count;
            }
        }
    }

    int** incidence_matrix = (int**)malloc(size * sizeof(int*));
    if (!incidence_matrix) {
        return nullptr;
    }

    for (size_t i = 0; i < size; ++i) {
        incidence_matrix[i] = (int*)calloc(edge_count, sizeof(int));
        if (!incidence_matrix[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(incidence_matrix[j]);
            }
            free(incidence_matrix);
            return nullptr;
        }
    }

    size_t edge_index = 0;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = i + 1; j < size; ++j) {
            if (adjacency_matrix[i][j] == 1) {
                incidence_matrix[i][edge_index] = 1;
                incidence_matrix[j][edge_index] = 1;
                ++edge_index;
            }
        }
    }

    return incidence_matrix;
}

int** create_adjacency_matrix(size_t size)
{
    int** matrix = (int**)malloc(size * sizeof(int*));
    if (!matrix)
    {
        return nullptr;
    }

    for (size_t i = 0; i < size; ++i)
    {
        matrix[i] = (int*)malloc(size * sizeof(int));
        if (!matrix[i])
        {
            for (size_t j = 0; j < i; ++j)
            {
                free(matrix[j]);

            }
            free(matrix);
            return nullptr;
        }

    }
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = i + 1; j < size; ++j)
        {
            matrix[i][j] = rand() % 2;
        }
    }
    for (size_t i = 1; i < size; ++i)
    {
        for (size_t j = 0; j < i; ++j)
        {
            matrix[i][j] = matrix[j][i];
        }
    }

    for (size_t i = 0; i < size; ++i)
    {
        matrix[i][i] = 0;
    }

    return matrix;
}

void print_matrix(int** matrix, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j) {

            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


void free_matrix(int** matrix, size_t size)
{
    if (!matrix)
    {
        return;
    }
    else
    {
        for (size_t i = 0; i < size; ++i)
        {
            free(matrix[i]);
        }
        free(matrix);
    }
}

size_t size_G_grapg(int** matrix, size_t size)
{
    size_t size_g = 0;
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = i + 1; j < size; ++j)
        {
            if (matrix[i][j] == 1) ++size_g;
        }
    }
    return size_g;
}

void isolated(int** matrix, size_t size)
{
    size_t isol = 0;
    for (size_t i = 0; i < size; ++i)
    {
        int sum = 0;
        for (size_t j = 0; j < size; ++j)
        {
            sum += matrix[i][j] + matrix[j][i];
        }

        if (sum == 0) ++isol;
    }
    std::cout << "Isolated: " << isol << std::endl;
}

void terminal(int** matrix, size_t size)
{
    size_t term = 0;
    for (size_t i = 0; i < size; ++i)
    {
        int sum = 0;
        for (size_t j = 0; j < size; ++j)
        {
            sum += matrix[i][j] + matrix[j][i];
        }
        if (sum == 1) ++term;
    }
    std::cout << "Terminal: " << term << std::endl;
}

void dominating(int** matrix, size_t size)
{
    size_t dom = 0;
    for (size_t i = 0; i < size; ++i)
    {
        int sum = 0;
        for (size_t j = 0; j < size; ++j)
        {
            if (i != j)
            {
                sum += matrix[i][j];
            }
        }

        if (sum == size - 1)
        {
            ++dom;
        }
    }
    std::cout << "Dominating: " << dom << std::endl;
}


void start()
{

    srand(static_cast<unsigned int>(time(nullptr)));

    while (true)
    {
        std::cout << "if you wanna finish - enter '0'\n";
        std::cout << "Enter size matrix (type size_t) : ";
        size_t size;
        std::cin >> size;
        if (!size)
        {
            return;
        }
        int** matrix = create_adjacency_matrix(size);
        if (!matrix)
        {
            std::cerr << "Error allocate\n";
            continue;
        }
        print_matrix(matrix, size);
        std::cout << "Size G-praph - " << size_G_grapg(matrix, size) << std::endl;
        isolated(matrix, size);
        terminal(matrix, size);
        dominating(matrix, size);

        int** incidence_matrix = create_incidence_matrix(matrix, size);
        if (!incidence_matrix) {
            std::cerr << "Error allocating memory for identity matrix\n";
            free_matrix(matrix, size);
            continue;
        }
        std::cout << "\n\nIncidence Matrix:" << std::endl;
        print_matrix(incidence_matrix, size);

        free_matrix(matrix, size);

        std::cout << std::endl;

        std::cin.clear();
    }
}

int main() {

    start();

}
