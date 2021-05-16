// Copyright 2021 Gushchin Artem

#ifndef MODULES_KRUSKAL_ALGORITHM_INCLUDE_KRUSKAL_ALGORITHM_APP_H_
#define MODULES_KRUSKAL_ALGORITHM_INCLUDE_KRUSKAL_ALGORITHM_APP_H_

#include <string>

class KruskalAlgorithm {
 public:
    KruskalAlgorithm();

    std::string operator()(int argc, const char** argv);

 private:
    void help(const char* appname, const char* message = "");
    bool validateNumberOfArguments(int argc, const char** argv);
    std::string message_;
};

#endif  // MODULES_KRUSKAL_ALGORITHM_INCLUDE_KRUSKAL_ALGORITHM_APP_H_
