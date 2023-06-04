#include <iostream>

void Stairs(size_t *moves, size_t size, size_t stairs, size_t *_options) 
{
    if (0 == stairs)
    {
        *_options += 1;
        return;
    }

    if (stairs < 0)
    {
        return;
    }

    for(size_t i = 0; i < size; ++i)
    {
            stairs -= moves[i];
            Stairs(moves, size, stairs, _options);
    }
}

int main()
{
    size_t options = 0;
    size_t moves[] = {1, 2};
    Stairs(moves, 2, 3, &options);

    std::cout << "options:  " << options << std::endl;

    return 0;
}