//
//  main.cpp
//  funcGen
//
//  Created by Joe Sherry on 3/12/20.
//  Copyright © 2020 JMacDev. All rights reserved.
//

#include <fstream>
#include <iostream>

class DataDesc {
public:
    DataDesc(double st, double end, double delta) :
    _start(st), _end(end), _delta(delta) {}
    double _start;
    double _end;
    double _delta;
};

namespace fg {

    using func1 = double (*)(double);
    using func2 = double (*)(double, double);

    void writePoints1(std::ofstream& out, func1 fp, const DataDesc& d);

    double f_square(double x);

}


// TODO: I had wanted to use wide character streams everywhere, but
// couldn't get these to compile for std::wstring outFilePath:
// std::wofstream outfile(outFilePath, std::ios::out);
// std::wofstream outfile(outFilePath.c_str(), std::ios::out);

static std::string s_outFolder = "/Users/joe/LocalFiles/Data/";
static size_t kMaxFileNameLen = 32;

int main(int argc, char * argv[]) {
    
    if (argc < 2) {
        std::cout << "Usage: funcGen filename\n";
        return 0;
    }
    std::string fileName = argv[1];
    if (fileName.length() > kMaxFileNameLen) {
        std::cout << "Security alert: input filename too long!\n";
        return -1;
    }
    std::string outFilePath = s_outFolder + fileName;
    std::ofstream outStream(outFilePath.c_str(), std::ios::out);
    if (!outStream.is_open()) {
        std::cout << "Could not open file for writing\n";
        return -1;
    }
    std::cout << "Writing points to " << outFilePath << " ...\n";
    DataDesc dd(-3.0, +3.0, 0.1);
    fg::writePoints1(outStream, fg::f_square, dd);
    outStream.close();
    return 0;
}

void fg::writePoints1(std::ofstream& out, func1 fp, const DataDesc& dd)
{
    for (double x = dd._start; x <= dd._end; x+= dd._delta) {
        out << x << "    " << fp(x) << "\n";
    }
}

double fg::f_square(double x)
{
    return x*x;
}
