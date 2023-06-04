// Ex.16
template <class T> // == template <typename T>
T Max(T t1, T t2)
{
    return (t1 > t2) ? t1 : t2;
}

int main()
{
   int arr[12];

   int x =  Max<int>(3, 5);
   int *y = Max<int *>(arr, arr + 8);
   char c = Max('a', 'b');

   return 0;

}