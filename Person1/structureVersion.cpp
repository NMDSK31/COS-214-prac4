#include "structureVersion.h"
#include <iostream>

using namespace std;
StructureVersion::StructureVersion()
{
    version=0;
}
unsigned long  StructureVersion::current()const
{
    return version;
}
void StructureVersion::bump()
{
    ++version;
}
