#include <vector>
#include <iostream>

int main (int argc, char const* argv[])
{
    std::vector<std::vector<double> > vecvec(5, std::vector<double>(5));
    for(int i = 0; i < vecvec.size(); ++i) {
        std::cout << "constructed vecvec(5) containing vectors of len " << vecvec[0].size() << std::endl;
    }
    return 0;
}
