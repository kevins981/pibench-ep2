#include "roart_wrapper.h"
#include <iostream>

int main() {

    tree_options_t tree_opt;
    tree_opt.pool_path = "/pmem0p1/roart";
    tree_api* tree = create_tree(tree_opt);

    // insert test
    const char * key_test = "testkey1";
    const char * val_test = "testval1";
    tree->insert(key_test, 8, val_test, 8);

    const char * key_test2 = "kevin11";
    const char * val_test2 = "kevinob";
    tree->insert(key_test2, 7, val_test2, 7);

    char val_out[100];

    if (tree->find(key_test, 8, val_out)){
        std::cout << "found key " << key_test << ". value is " << val_out << std::endl;
    }

    char val_out2[100];
    if (tree->find(key_test2, 7, val_out2)){
        std::cout << "found key " << key_test2 << ". value is " << val_out2 << std::endl;
    }

    const char * val_test3 = "bobeeee";
    tree->update(key_test2, 7, val_test3, 7);

    char val_out3[100];
    if (tree->find(key_test2, 7, val_out3)){
        std::cout << "found updated key " << key_test2 << ". value is " << val_out3 << std::endl;
    }

}
