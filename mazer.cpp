#include <iostream>
#include <vector>
#include <sstream>
#include <random>
#include <ctime>
#include <stdlib.h>
#include <fstream>

using namespace std;

typedef pair<int, int>  coordinator;

typedef pair<coordinator, coordinator> edge;

void getUserInput();

vector<edge> mazeGenerator(int seed, int width, int height, bool withSeed);

void printLineWith(const string& basicString);

void printLineWithInt(const int& inter);

vector<int> randomGenerator(mt19937 generator, int min, int max, int times);

void saveSvg(basic_string<char, char_traits<char>, allocator<char>> &basicString, const vector<edge>& vector, int width, int height);

int main() {

//    string userIn;
//    while (userIn != "exit") {
//        vector<string> userString = {"hello, {hello kitty}", " hello"};
//        for (int i = 0; i < userString.size(); ++i) {
//            printLineWith(userString[i]);
//        }
//    }

//    srand(1);
//    for (int i = 0; i < 20; ++i) {
//        cout<< rand() << endl;
//    }

//    mt19937 generator;
//    if (true) {
//        generator.seed(time(nullptr) + 123);
//    } else {
//        generator.seed(time(nullptr));
//    }
//    vector<int> random_numbers = randomGenerator(generator, 123, 456, 10);
//    for (int i = 0; i < random_numbers.size(); ++i) {
//        printLineWithInt(random_numbers[i]);
//    }

    getUserInput();

//    mazeGenerator(12, 3, 6, true);

    return 0;
}

void getUserInput() {
    string DUPLICATE_FLAG_MESSAGE = "duplication of flag occurs, please try again";
    string INVALID_INPUT_MESSAGE = "invalid input, please try again";
    string WRONG_FORMAT_G_FLAG = "invalid input format, please follow '--g seed width height'";
    string WRONG_FORMAT_G_OPT_FLAG = "invalid input format, please follow '-g seed width height' or '-g width height'";
    string NOT_LARGER_THAN_ZERO = "your specifications must be larger than 0";
    string EXIT = "exit";
    string userInput;

    while (userInput != EXIT) {
        vector<string> userInputVector;
//        userInputVector.clear();
        pair<int, bool> hasGen;
        pair<int, bool> hasGenOpt;
        pair<int, bool> hasLoadBinary;
        pair<int, bool> hasLoadSvg;
        pair<int, bool> hasSaveBinary;
        pair<int, bool> hasSaveSvg;
        bool isValidInputFlag = false;

        cout << "./mazer ";
        getline (cin, userInput);

        stringstream stringStream(userInput);
        copy(istream_iterator<string>(stringStream), istream_iterator<string>(), back_inserter(userInputVector));

        for (int i = 0; i < userInputVector.size(); ++i) {
            if (userInputVector[i] == "--g") {
                if (!hasGen.second) {
                    hasGen.first = i;
                    hasGen.second = true;
                    isValidInputFlag = true;
                } else {
                    isValidInputFlag = false;
                    printLineWith(DUPLICATE_FLAG_MESSAGE);
                    break;
                }
            } else if (userInputVector[i] == "-g") {
                if (!hasGenOpt.second) {
                    hasGenOpt.first = i;
                    hasGenOpt.second = true;
                    isValidInputFlag = true;
                } else {
                    isValidInputFlag = false;
                    printLineWith(DUPLICATE_FLAG_MESSAGE);
                    break;
                }
            } else if (userInputVector[i] == "--lb") {
                if (!hasLoadBinary.second) {
                    hasLoadBinary.first = i;
                    hasLoadBinary.second = true;
                    isValidInputFlag = true;
                } else {
                    isValidInputFlag = false;
                    printLineWith(DUPLICATE_FLAG_MESSAGE);
                    break;
                }
            } else if (userInputVector[i] == "--lv") {
                if (!hasLoadSvg.second) {
                    hasLoadSvg.first = i;
                    hasLoadSvg.second = true;
                    isValidInputFlag = true;
                } else {
                    isValidInputFlag = false;
                    printLineWith(DUPLICATE_FLAG_MESSAGE);
                    break;
                }
            } else if (userInputVector[i] == "--sb") {
                if (!hasSaveBinary.second) {
                    hasSaveBinary.first = i;
                    hasSaveBinary.second = true;
                    isValidInputFlag = true;
                } else {
                    isValidInputFlag = false;
                    printLineWith(DUPLICATE_FLAG_MESSAGE);
                    break;
                }
            } else if (userInputVector[i] == "--sv") {
                if (!hasSaveSvg.second) {
                    hasSaveSvg.first = i;
                    hasSaveSvg.second = true;
                    isValidInputFlag = true;
                } else {
                    isValidInputFlag = false;
                    printLineWith(DUPLICATE_FLAG_MESSAGE);
                    break;
                }
            }
        }
        if (isValidInputFlag) {
            bool canCallSaveFunctions = true;
            vector<edge> edgesVector;
            int mainWidth = 0;
            int mainHeight = 0;
            if (hasGen.second) {
                int seed = 0;
                int width = 0;
                int height = 0;
//                printLineWithInt(seed);
//                printLineWithInt(width);
//                printLineWithInt(height);
                try {
                    seed = stoi(userInputVector[hasGen.first+1]);
                    width = stoi(userInputVector[hasGen.first+2]);
                    height = stoi(userInputVector[hasGen.first+3]);
//                    cout << userInputVector[hasGen.first+1];
//                    cout << userInputVector[hasGen.first+2];
//                    cout << userInputVector[hasGen.first+3];
//                  printLineWith(userInputVector[hasGen.first+1]);
//                  printLineWith(userInputVector[hasGen.first+2]);
//                  printLineWith(userInputVector[hasGen.first+3]);
                    if (seed > 0 && width > 0 && height > 0) {
                        canCallSaveFunctions = true;
                        printLineWith("calling generating func");
                        mainWidth = width;
                        mainHeight = height;
                        edgesVector = mazeGenerator(seed, width, height, true);
                    } else {
                        canCallSaveFunctions = false;
                        printLineWith(NOT_LARGER_THAN_ZERO);
                    }
                } catch (...) {
                    canCallSaveFunctions = false;
                    printLineWith(WRONG_FORMAT_G_FLAG);
                }
            }
            if (hasGenOpt.second) {
                int firstField = 0;
                int secondField = 0;
//                printLineWithInt(firstField);
//                printLineWithInt(secondField);
                try {
                    firstField = stoi(userInputVector[hasGenOpt.first+1]);
                    secondField = stoi(userInputVector[hasGenOpt.first+2]);
//                    printLineWithInt(firstField);
//                    printLineWithInt(secondField);
                    int thirdField = 0;
//                    printLineWithInt(thirdField);
                    try {
                        thirdField = stoi(userInputVector[hasGenOpt.first+3]);
//                        printLineWithInt(thirdField);
                        if (firstField > 0 && secondField > 0 && thirdField > 0) {
                            canCallSaveFunctions = true;
                            printLineWith("calling generating with optional seed func");
                            mainWidth = secondField;
                            mainHeight = thirdField;
                            edgesVector = mazeGenerator(firstField, secondField, thirdField, true);
                        } else {
                            canCallSaveFunctions = false;
                            printLineWith(NOT_LARGER_THAN_ZERO);
                        }
                    } catch (...) {
                        if (firstField > 0 && secondField > 0) {
                            canCallSaveFunctions = true;
                            printLineWith("calling generating without optional seed func");
                            mainWidth = firstField;
                            mainHeight = secondField;
                            edgesVector = mazeGenerator(0, firstField, secondField, false);
                        } else {
                            canCallSaveFunctions = false;
                            printLineWith(NOT_LARGER_THAN_ZERO);
                        }
                    }
                } catch (...) {
                    canCallSaveFunctions = false;
                    printLineWith(WRONG_FORMAT_G_OPT_FLAG);
                }
            }
            if (hasLoadBinary.second) {
                printLineWith("calling load binary func");
            }
            if (hasLoadSvg.second) {
                printLineWith("calling load SVG func");
            }

            if ((hasGen.second || hasGenOpt.second || hasLoadBinary.second || hasLoadSvg.second) && canCallSaveFunctions) {
                if (hasSaveBinary.second) {
//                    TODO check file format
                    printLineWith("calling save binary func");
                }
                if (hasSaveSvg.second) {
//                    TODO check file format
                    saveSvg(userInputVector[hasSaveSvg.first + 1], edgesVector, mainWidth, mainHeight);
                    printLineWith("calling save SVG func");
                }
            } else {
                if (hasSaveBinary.second || hasSaveSvg.second) {
                    printLineWith("you must create or load the maze first");
                }
            }
        } else {
            if (userInputVector[0] != EXIT) {
                printLineWith(INVALID_INPUT_MESSAGE);
            } else if (userInputVector[0] == EXIT) {
                break;
            }
        }
    }
//    while (userInputVector[0] != EXIT && userInput != EXIT);
}

void saveSvg(basic_string<char, char_traits<char>, allocator<char>> &basicString, const vector<edge>& vector, int width, int height) {
    ofstream svgFile(basicString, ofstream::out);
    svgFile << "<svg"<< " viewBox="<< "\"0 0 " << width << " " << height << "\""<< " width" << "=" <<"\"" << width*10
    << "\""<<" height=\"" << height*10 << "\"" << " xmlns=" << "\"http://www.w3.org/2000/svg\">" << endl;
    svgFile << "<rect width =" <<"\'" << width << "\' " << "height=\'" << height << "\' " << "style=\'"<< "fill: black\' " << "/>" << endl;
    for (auto & edge : vector) {
        double x1 =  edge.first.first + 0.5;
        double y1 =  edge.first.second + 0.5;
        double x2 =  edge.second.first + 0.5;
        double y2 =  edge.second.second + 0.5;
        svgFile << "<line stroke=\'" << "white\' " << "stroke-width=\'" << "0.5\'" << " x1=\'" << x1 << "\' y1=\'" << y1
                << "\' x2=\'" << x2 << "\' y2=\'" << y2 << "\'/>" << endl;
    }
    svgFile << "</svg>" << endl;
    svgFile.close();
}

void printLineWith(const string& basicString) {
    cout << basicString << endl;
}

void printLineWithInt(const int& inter) {
    cout << inter << endl;
}

vector<edge> mazeGenerator(int seed, int width, int height, bool withSeed) {
    bool visitedArray[height][width];
    for (int m = 0; m < height; ++m) {
        for (int i = 0; i < width; ++i) {
            visitedArray[m][i] = false;
        }
    }

//    for (int n = 0; n < height; ++n) {
//        for (int i = 0; i < width; ++i) {
//            cout << n << i << " ";
//        }
//        cout << endl;
//    }

    vector<edge> edges;
    if (!withSeed) {
        seed = time(0);
        cout << "Your seed is " << seed << endl;
    }
    srand(seed);

    bool keepHunting = true;
    bool keepKilling = true;

    coordinator startingCell;
    startingCell.first = rand() % height;
    startingCell.second = rand() % width;
    visitedArray[startingCell.first][startingCell.second] = true;
    bool starting = true;

    while (keepHunting) {
//        for(int i=0;i < height;i++) {
//            for(int j=0;j < width;j++) {
//                if (!visitedArray[i][j]) {
//                    keepKilling = true;
//                    break;
//                } else {
//                    keepKilling = false;
//                }
//            }
//        }
        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                if (!visitedArray[j][i]) {
                    keepKilling = true;
                    break;
                } else {
                    keepKilling = false;
                }
            }
            if (keepKilling) {
                break;
            }
        }
        while (keepKilling) {
//            if (starting) {
//                int numberOfNeighbours = 0;
                vector<coordinator> neighbours;
//                neighbours.clear();

//                bool hasTop = false;
                if (startingCell.first - 1 > -1) {
                    coordinator topCell;
                    topCell.first = startingCell.first - 1;
                    topCell.second = startingCell.second;
                    neighbours.push_back(topCell);
//                    hasTop = true;
//                    numberOfNeighbours++;
                }

//                bool hasRight = false;
                if (startingCell.second + 1 < width) {
                    coordinator rightCell;
                    rightCell.first = startingCell.first;
                    rightCell.second = startingCell.second + 1;
                    neighbours.push_back(rightCell);
//                    hasRight = true;
//                    numberOfNeighbours++;
                }

//                bool hasBottom = false;
                if (startingCell.first + 1 < height) {
                    coordinator bottomCell;
                    bottomCell.first = startingCell.first + 1;
                    bottomCell.second = startingCell.second;
                    neighbours.push_back(bottomCell);
//                    hasBottom = true;
//                    numberOfNeighbours++;
                }

//                bool hasLeft = false;
                if (startingCell.second - 1 > -1) {
                    coordinator leftCell;
                    leftCell.first = startingCell.first;
                    leftCell.second = startingCell.second - 1;
                    neighbours.push_back(leftCell);
//                    hasLeft = true;
//                    numberOfNeighbours++;
                }

                vector<int> randomizedNeighbours;
//                randomizedNeighbours.clear();
//                coordinator nextCell;
                bool keepSeeking = true;
                while (keepSeeking) {
                    int currentRandom = rand() % neighbours.size();
                    bool addingRandom = true;
                    for (int i = 0; i < randomizedNeighbours.size(); ++i) {
                        if (randomizedNeighbours[i] == currentRandom) {
                            addingRandom = false;
                            break;
                        }
                    }
                    if (addingRandom) {
                        randomizedNeighbours.push_back(currentRandom);
                        coordinator neighbour = neighbours[currentRandom];
                        if (!visitedArray[neighbour.first][neighbour.second]) {
                            keepSeeking = false;
                            visitedArray[neighbour.first][neighbour.second] = true;
                            edge edge1;
                            edge1.first = startingCell;
                            edge1.second = neighbour;
                            edges.push_back(edge1);
                            startingCell.first = neighbour.first;
                            startingCell.second = neighbour.second;
                            printLineWith("killed");
                        }
                    } else {
                        if (randomizedNeighbours.size() == neighbours.size()) {
                            keepSeeking = false;
                            keepKilling = false;
                        }
                    }
                }
//            }
        }

        bool foundStarting = false;
        for (int k = 0; k < height; ++k) {
            for (int i = 0; i < width; ++i) {
                if (!visitedArray[k][i]) {
                    startingCell.first = k;
                    startingCell.second = i;
                    vector<coordinator> neighbours;
//                    neighbours.clear();

//                bool hasTop = false;
                    if (startingCell.first - 1 > -1) {
                        coordinator topCell;
                        topCell.first = startingCell.first - 1;
                        topCell.second = startingCell.second;
                        neighbours.push_back(topCell);
//                    hasTop = true;
//                    numberOfNeighbours++;
                    }

//                bool hasRight = false;
                    if (startingCell.second + 1 < width) {
                        coordinator rightCell;
                        rightCell.first = startingCell.first;
                        rightCell.second = startingCell.second + 1;
                        neighbours.push_back(rightCell);
//                    hasRight = true;
//                    numberOfNeighbours++;
                    }

//                bool hasBottom = false;
                    if (startingCell.first + 1 < height) {
                        coordinator bottomCell;
                        bottomCell.first = startingCell.first + 1;
                        bottomCell.second = startingCell.second;
                        neighbours.push_back(bottomCell);
//                    hasBottom = true;
//                    numberOfNeighbours++;
                    }

//                bool hasLeft = false;
                    if (startingCell.second - 1 > -1) {
                        coordinator leftCell;
                        leftCell.first = startingCell.first;
                        leftCell.second = startingCell.second - 1;
                        neighbours.push_back(leftCell);
//                    hasLeft = true;
//                    numberOfNeighbours++;
                    }
                    for (int j = 0; j < neighbours.size(); ++j) {
                        coordinator neighbour = neighbours[j];
                        if (visitedArray[neighbour.first][neighbour.second]) {
                            foundStarting = true;
                            break;
                        }
                    }
                    if (foundStarting) {
                        vector<int> randomizedNeighbours;
//                        randomizedNeighbours.clear();
                        bool keepSeeking = true;
                        while (keepSeeking) {
                            int currentRandom = rand() % neighbours.size();
                            bool addingRandom = true;
                            for (int m = 0; m < randomizedNeighbours.size(); ++m) {
                                if (randomizedNeighbours[m] == currentRandom) {
                                    addingRandom = false;
                                    break;
                                }
                            }
                            if (addingRandom) {
                                randomizedNeighbours.push_back(currentRandom);
                                coordinator neighbour = neighbours[currentRandom];
                                if (visitedArray[neighbour.first][neighbour.second]) {
                                    keepSeeking = false;
                                    visitedArray[startingCell.first][startingCell.second] = true;
                                    edge edge1;
                                    edge1.first = startingCell;
                                    edge1.second = neighbour;
                                    edges.push_back(edge1);
                                    printLineWith("hunted");
                                }
                            } else {
                                if (randomizedNeighbours.size() == neighbours.size()) {
                                    keepSeeking = false;
                                    foundStarting = false;
                                }
                            }
                        }
                    }
                    if (foundStarting) {
                        break;
                    }
                }
            }
            if (foundStarting) {
                break;
            }
        }
        for (int l = 0; l < height; ++l) {
            for (int i = 0; i < width; ++i) {
                if (!visitedArray[l][i]) {
                    keepHunting = true;
                    break;
                } else {
                    keepHunting = false;
                }
            }
            if (keepHunting) {
                break;
            }
        }
    }

    for (int n = 0; n < edges.size(); ++n) {
        edge edge1 = edges[n];
        cout << edge1.first.first << " " << edge1.first.second << " : " << edge1.second.first << " " << edge1.second.second << endl;
    }

//    mt19937 generator;
//    if (withSeed) {
//        generator.seed(time(nullptr) + seed);
//    } else {
//        generator.seed(time(nullptr));
//    }
//    uniform_int_distribution<u_int32_t> dice(0, width);
//    dice(generator);
//    uniform_int_distribution<u_int32_t> dice(0, height);
//    dice(generator);

    return edges;
}

vector<int> randomGenerator(mt19937 generator, int min, int max, int times) {
    uniform_int_distribution<u_int32_t> dice(min, max);
    vector<int> random_numbers;
    random_numbers.reserve(times);
    for (int i = 0; i < times; ++i) {
        random_numbers.push_back(dice(generator));
    }

    return random_numbers;
}