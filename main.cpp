#include <iostream>
#include <memory>

void crear_puntero_unico() {
    std::unique_ptr<int> ptr_i;


    ptr_i = std::make_unique<int>(10);
    std::cout << *ptr_i  << std::endl;
    std::unique_ptr<int> ptr_i_2;
    std::cout << std::boolalpha << static_cast<bool>(ptr_i) << std::endl;
    std::cout << std::boolalpha << static_cast<bool>(ptr_i_2) << std::endl;
    std::cout << "---\n";
    ptr_i_2 = std::move(ptr_i);
    std::cout << std::boolalpha << static_cast<bool>(ptr_i) << std::endl;
    std::cout << std::boolalpha << static_cast<bool>(ptr_i_2) << std::endl;
    std::cout << "---\n";
    std::swap(ptr_i, ptr_i_2);
    std::cout << std::boolalpha << static_cast<bool>(ptr_i) << std::endl;
    std::cout << std::boolalpha << static_cast<bool>(ptr_i_2) << std::endl;
    std::cout << "---\n";

}

void crear_puntero_compartido() {
    std::shared_ptr<double> ptr_d;
    std::cout << ptr_d.use_count() << std::endl;
    {
        ptr_d = std::make_shared<double>(10);
        std::cout << ptr_d.use_count() << std::endl;
        {
            std::shared_ptr<double> ptr_d_2;
            ptr_d_2 = ptr_d;
            std::cout << ptr_d.use_count() << std::endl;
            std::cout << ptr_d_2.use_count() << std::endl;
            ptr_d = nullptr;
            std::cout << ptr_d.use_count() << std::endl;
            std::cout << ptr_d_2.use_count() << std::endl;
        }
        std::cout << ptr_d.use_count() << std::endl;
    }
    ptr_d = nullptr;
    std::cout << ptr_d.use_count() << std::endl;
    ptr_d = std::make_shared<double>(20);
    std::cout << ptr_d.use_count() << std::endl;
}

class Andrew;

struct Tobey {
    std::weak_ptr<Andrew> ptr;
};
struct Andrew {
    std::weak_ptr<Tobey> ptr;
};

void ejemplo_puntero_debil() {
    std::shared_ptr<Tobey> ptr_t = std::make_shared<Tobey>(); // 1
    {
        std::shared_ptr<Andrew> ptr_a = std::make_shared<Andrew>(); // 1
        ptr_t->ptr = ptr_a; // 1
        ptr_a->ptr = ptr_t; // 1
        std::cout << ptr_a.use_count() << std::endl;
    }
    std::cout << ptr_t.use_count() << std::endl;  // 1
}

int main() {
//    crear_puntero_unico();
//    crear_puntero_compartido();
    ejemplo_puntero_debil();
    return 0;
}
