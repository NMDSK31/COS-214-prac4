#ifndef STRUCTUREVERSION_H
#define STRUCTUREVERSION_H
#include <iostream>
using namespace std;

class StructureVersion
{
   private:
    unsigned long version;

    public:
        StructureVersion();
        unsigned long current()const;
        void bump();
};

#endif