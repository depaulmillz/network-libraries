#include <iostream>
#include <rdma/fi_errno.h>
#include <rdma/fabric.h>
#include <string>

/*  Calling the library can result in failure.
    To handle this, it is best to use a error
    checking macro.
*/

#define ERRCHK(x) error_check((x), __FILE__, __LINE__)

void error_check(int err, std::string filename, int line){
    if(err < 0){
        // prints the error and string which is associated with the negative error
        std::cerr << "errno (" << err << "): " << fi_strerror(-err) << " " << filename << ":" << line << std::endl;
    }
}

int main(int argc, char** argv){
    fi_info* info;
    ERRCHK(fi_getinfo(FI_VERSION(1,12), nullptr, nullptr, 0, nullptr, &info));
    
    // this sets info to a linked list of potential fabrics to use
    // read the manual for more details on how to use fi_getinfo

    auto tmp = info;
    while(tmp != nullptr){
        std::cout << "Domain name: " << tmp->domain_attr->name << std::endl;
        std::cout << "Fabric name: " << tmp->fabric_attr->name << std::endl;
        tmp = tmp->next;
    }
    
    // we free the info at the end of using it
    fi_freeinfo(info);

    std::cout << std::endl;

    // get fabrics associated with an endpoint which has the following source address
    std::string address = "127.0.0.1";
    ERRCHK(fi_getinfo(FI_VERSION(1,12), address.c_str(), nullptr, FI_SOURCE, nullptr, &info));
    
    // this sets info to a linked list of potential fabrics to use
    // read the manual for more details on how to use fi_getinfo

    tmp = info;
    while(tmp != nullptr){
        std::cout << "Domain name: " << tmp->domain_attr->name << std::endl;
        std::cout << "Fabric name: " << tmp->fabric_attr->name << std::endl;
        tmp = tmp->next;
    }
    
    // we free the info at the end of using it
    fi_freeinfo(info);

    std::cout << std::endl;

    // get fabrics associated with 127.0.0.1 that supports messages and rma
    fi_info hints = {0};
    hints.caps = FI_MSG | FI_RMA; // set capability to use msg and rma
    ERRCHK(fi_getinfo(FI_VERSION(1,12), address.c_str(), nullptr, FI_SOURCE, &hints, &info));
    
    // this sets info to a linked list of potential fabrics to use
    // read the manual for more details on how to use fi_getinfo

    tmp = info;
    while(tmp != nullptr){
        std::cout << "Domain name: " << tmp->domain_attr->name << std::endl;
        std::cout << "Fabric name: " << tmp->fabric_attr->name << std::endl;
        tmp = tmp->next;
    }
    
    // we free the info at the end of using it
    fi_freeinfo(info);

    return 0;
}