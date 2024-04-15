
int multiples(int* arr, int size, int x) {
    int count = 0;
    for (int i=0; i < size; ++i) {
        if (arr[i]%x == 0) {++count;}
    }

    return count;
}

int main(void) {
    int x = 3;
    int arr[5] = {1, 2, 3, 4, 5};

    count_multiples(arr, 5, 3);
    return 0;
}


