#include <iostream>
#include <fstream>

int** create_arr(int rows) {
    int** arr = new int* [rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new int[rows];
    }
    return arr;
}

void delete_arr(int** arr, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    arr = nullptr;
}

void dfs(int** arr, int vertex, int* cids, const int num_vertex, int cid) {

    cids[vertex - 1] = cid;
    std::cout << vertex << " - " << cid;
    std::cout << std::endl;

    for (int j = 0; j < num_vertex; j++) {
        if ((arr[vertex - 1][j] == 1) && (cids[j] == 0)) {
            dfs(arr, (j + 1), cids, num_vertex, cid);
        }
    }
}

void components(int** arr, const int num_vertex) {

    int* cids = new int[num_vertex] {0};
    int cid = 1;

    for (int i = 0; i < num_vertex; i++) {
        if (cids[i] == 0) {
            dfs(arr, (i + 1), cids, num_vertex, cid);
            cid += 1;
        }
    }

    std::cout << "Количество компонентов связности в графе: ";
    std::cout << cid - 1;

    delete[] cids;
}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");

    std::ifstream input_data("in.txt");

    if (input_data.is_open()) {

        int num_vertex;
        input_data >> num_vertex;
        int** adj_matrix = create_arr(num_vertex);

        for (int i = 0; i < num_vertex; i++) {
            for (int j = 0; j < num_vertex; j++) {
                input_data >> adj_matrix[i][j];
            }
        }

        std::cout << "Принадлежность вершин компонентам связности: " << std::endl;

        components(adj_matrix, num_vertex);

        std::cout << std::endl;

        delete_arr(adj_matrix, num_vertex);

        input_data.close();
    }
    else {
        std::cout << "Ошибка! Не удалось открыть файл" << std::endl;
    }

    return 0;
}