/**
 * Computes for the determinant of a NxN matrix (https://en.wikipedia.org/wiki/Determinant)
 * author: Carlo Cochran <carlo.cochran at gmail.com>
*/

#include<string>
#include<iostream>

class DeterminantException : public std::exception{
    private:
        std::string message;

    public:
        DeterminantException(std::string message){
            this->message = message;
        }

        std::string getMessage(){
            return this->message;
        }
};

class Determinant{

    public:
        static int get_matrix_value(int *m, int size, int column, int row){
            return *(m + (column * size) + row);
        }

        static void set_matrix_value_static(int *m, int size, int column, int row, int value){
             *(m + (column * size) + row) = value;
        }

        static int* new_matrix(int size, int index, int *m){
            int new_size = size - 1;
            int *new_matrix = (int *)malloc(size * size * sizeof(int));
            for (int i=0; i < size; i++){
                for (int j=0; j < size; j++){
                    int x = i + 1;
                    int y = (j < index) ? j : j + 1;
                    int value = get_matrix_value(m, size, x, y);
                    set_matrix_value_static(new_matrix, new_size, i, j, value);
                }
            }
            return new_matrix;
        }

        static void print_matrix(int *m, int size){
            for (int i=0; i < size; i++){
                for (int j=0; j < size; j++){
                    std::cout << get_matrix_value(m, size, i, j) << "|";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

        static int matrix_determinant(int *m, int size){
            print_matrix(m, size);
            if (size < 2){
                throw new DeterminantException("Array size should be at least 2x2");
            }
            else if (size == 2){
                return (get_matrix_value(m, size, 0, 0) * get_matrix_value(m, size, 1, 1)) -
                            (get_matrix_value(m, size, 0, 1) * get_matrix_value(m, size, 1, 0));
            }
            else {
                int new_size = size - 1;
                int determinant = 0;
                int operation = -1;
                for (int i = 0; i < size; i++){
                    operation = operation * -1;
                    int *new_m = new_matrix(size, i, m);
                    int value = get_matrix_value(m, size, 0, i);
                    determinant += (operation * value * matrix_determinant(new_m, new_size));
                    free(new_m);
                }

                return determinant;
            }
        }
};

int main(){
    //int matrix[2][2] = {{3,1},{3,4}};
    //int matrix[3][3] = {{3,-4,2},{1,10,9},{-5,6,7}};
    int matrix[4][4] = {{3,-4,2,5},{1,10,9,2},{-5,6,7,9},{1,3,4,8}};

    try{
        std::cout << Determinant::matrix_determinant(&matrix[0][0], 4) << std::endl;
    }
    catch (DeterminantException *ex) {
        std::cout << ex->getMessage() << std::endl;
    }

    return 0;
}
