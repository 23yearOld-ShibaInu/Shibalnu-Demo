//
// Created by Trust on 2020-08-30.
//

#ifndef SHIBALNUCPP_TRUSTINSTANCE_H
#define SHIBALNUCPP_TRUSTINSTANCE_H

#endif //SHIBALNUCPP_TRUSTINSTANCE_H

#include <iostream>
#include "TrustLog.h"
class TrustInstance{
private:
    static TrustInstance *  instance;

    TrustInstance();
    ~TrustInstance();
public:
    static TrustInstance * getInstance();

    void show();

    void show2();

    void unInstance();
};