#include <iostream>
#include <vector>
#include <iterator>
#include <initializer_list>

int main(void)
{
    std::vector<int> v {1, 2, 3, 4, 5};
    int size = 2;
    int val = 1;
    // 検証1: sizeを元のsize以下にする
    std::cout << "v.begin(): " << v.begin() << std::endl;
    v.assign(size, val);
    // 要素数は縮小, capは変化なし
    std::cout << "v.capacity(): " << v.capacity() << std::endl;
    for (auto itr = v.begin(); itr != v.end(); itr++)
    {
        std::cout << "*itr: " << *itr << std::endl;
    }
    
    int size_2 = 8;
    val = 2;
    // 検証2: sizeを元のsizeよりも大きく    
    v.assign(size_2, val);
    // cap = 新しいサイズ
    std::cout << "v.capacity(): " << v.capacity() << std::endl;
    for (auto itr = v.begin(); itr != v.end(); itr++)
    {
        std::cout << "*itr: " << *itr << std::endl;
    }

}
