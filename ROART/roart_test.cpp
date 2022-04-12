#include "roart_wrapper.h"
#include <iostream>



int main() {

    tree_options_t tree_opt;
    tree_opt.pool_path = "/pmem0p1/roart";
    tree_api* tree = create_tree(tree_opt);

    //// insert test
    //const char * key_test = "testkey1";
    //const char * val_test = "testval1";
    //tree->insert(key_test, 8, val_test, 8);

    ////const char * key_test2 = "kevin11";
    ////const char * val_test2 = "kevinob";
    ////tree->insert(key_test2, 7, val_test2, 8);

    //char val_out[100];

    //if (tree->find(key_test, 8, val_out)){
    //    std::cout << "found key " << key_test << ". value is " << val_out << std::endl;
    //}

    //char val_out2[100];
    //if (tree->find(key_test2, 7, val_out2)){
    //    std::cout << "found key " << key_test2 << ". value is " << val_out2 << std::endl;
    //}

    //const char * val_test3 = "bobeeee";
    //tree->update(key_test2, 7, val_test3, 8);

    //char val_out3[100];
    //if (tree->find(key_test2, 7, val_out3)){
    //    std::cout << "found updated key " << key_test2 << ". value is " << val_out3 << std::endl;
    //}

    product test_prod;
    test_prod.field1 = 123;
    test_prod.field2 = 3.14;

    std::cout << "field1  " << test_prod.field1  << std::endl;
    std::cout << "field2  " << test_prod.field2  << std::endl;


    const product *test_prod_ptr = &test_prod;
    //void *test_prod_ptr2 = &test_prod_ptr;
    //uint64_t addr = reinterpret_cast<uint64_t>(&test_prod); // convert address of struct to int. We wish to store this int into ROART
    //uint64_t *addr_ptr = &addr; // to store addr into ROART, we need to provide a pointer to it. 
    //const char * val_test4 = reinterpret_cast<const char*>(addr_ptr); 
    const product **val_test4 = &test_prod_ptr;

    // test_val is actually product **
    // *test_val is product *, which is what we want to store
    //char *val_test4 = (char*)test_prod_ptr2;


   // char * test_val = reinterpret_cast<char*>(&test_prod_ptr);
    const char * key_test4 = "structke";

    //product **test_prod_out = reinterpret_cast<product**>(test_val);
    //product **test_prod_out = const_cast<product*>(reinterpret_cast<product*>(test_val));
    //std::cout << "from index field1  " << (*test_prod_out)->field1  << std::endl;
    //std::cout << "from index field2  " << (*test_prod_out)->field2  << std::endl;
    tree->insert(key_test4, 8, val_test4, 8);

    char val_out4[100];
    if (tree->find(key_test4, 8, val_out4)){
        product **test_prod_out = reinterpret_cast<product**>(val_out4);

        std::cout << "found inserted struct with key" << key_test4 << std::endl;
        std::cout << "from index field1  " << (*test_prod_out)->field1  << std::endl;
        std::cout << "from index field2  " << (*test_prod_out)->field2  << std::endl;
    }

    //product *test_prod_out = reinterpret_cast<product*>(val_out4);
    //std::cout << "from index field1  " << test_prod_out->field1  << std::endl;
    //std::cout << "from index field2  " << test_prod_out->field2  << std::endl;



}
