#include <iostream>
#include <vector>
#include <sstream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

//define types
//cell location
typedef pair<int, int> coordinator;

//edges' coordinators
typedef pair<coordinator, coordinator> edge;

//define functions
void getUserInput();

vector<edge> mazeGenerator(int seed, int width, int height, bool withSeed);

void printLineWith(const string &stringToPrint);

void printLineWithInt(const int &intToPrint);

vector<int> randomGenerator(mt19937 generator, int min, int max, int times);

void saveSvg(basic_string<char, char_traits<char>, allocator<char> > &fileName, const vector<edge> &vector, int width,
             int height);

void saveBinary(basic_string<char, char_traits<char>, allocator<char> > &fileName, const vector<edge> &vector,
                int width,
                int height);

int main() {
    //    get user input form console
    getUserInput();

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
        //check if user input is exit
        vector<string> userInputVector; //create vector to store user input
        //        userInputVector.clear();
        pair<int, bool> hasGen;
        pair<int, bool> hasGenOpt;
        pair<int, bool> hasLoadBinary;
        pair<int, bool> hasLoadSvg;
        pair<int, bool> hasSaveBinary;
        pair<int, bool> hasSaveSvg;
        bool isValidInputFlag = false;

        //        get user input
        cout << "./mazer ";
        getline(cin, userInput);

        //        split it by space and add to vector
        stringstream stringStream(userInput);
        copy(istream_iterator<string>(stringStream), istream_iterator<string>(), back_inserter(userInputVector));
        //        check if first elment of user input vector = exit
        if (userInputVector[0] == EXIT) {
            break;
        }

        //        loop to check flag
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
        //        check if input contains flags/flag
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
                    //                    convert input to int
                    seed = stoi(userInputVector[hasGen.first + 1]);
                    width = stoi(userInputVector[hasGen.first + 2]);
                    height = stoi(userInputVector[hasGen.first + 3]);
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
                    //                    convert input to int
                    firstField = stoi(userInputVector[hasGenOpt.first + 1]);
                    secondField = stoi(userInputVector[hasGenOpt.first + 2]);
                    //                    printLineWithInt(firstField);
                    //                    printLineWithInt(secondField);
                    int thirdField = 0;
                    //                    printLineWithInt(thirdField);
                    try {
                        thirdField = stoi(userInputVector[hasGenOpt.first + 3]);
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
                //                TODO build load binary function
                //                canCallSaveFunctions = true;
                printLineWith("calling load binary func");
            }
            if (hasLoadSvg.second) {
                //                TODO build load svg function
                //                canCallSaveFunctions = true;
                printLineWith("calling load SVG func");
            }

            if ((hasGen.second || hasGenOpt.second || hasLoadBinary.second || hasLoadSvg.second) &&
                canCallSaveFunctions) {
                if (hasSaveBinary.second) {
                    //                    TODO check file format and validate user input
                    saveBinary(userInputVector[hasSaveBinary.first + 1], edgesVector, mainWidth, mainHeight);
                    printLineWith("calling save binary func");
                }
                if (hasSaveSvg.second) {
                    //                    TODO check file format and validate user input
                    saveSvg(userInputVector[hasSaveSvg.first + 1], edgesVector, mainWidth, mainHeight);
                    printLineWith("calling save SVG func");
                }
            } else {
                if (hasSaveBinary.second || hasSaveSvg.second) {
                    printLineWith("you must create or load the maze first");
                }
            }
        } else {
            //            if (userInputVector[0] != EXIT) {
            printLineWith(INVALID_INPUT_MESSAGE);
            //            }
        }
    }
    //    while (userInputVector[0] != EXIT && userInput != EXIT);
}

void
saveBinary(basic_string<char, char_traits<char>, allocator<char> > &fileName, const vector<edge> &vector, int width,
           int height) {
    fstream binary(fileName, ios::binary | ios::in | ios::out | ios::trunc);
    if (!binary.is_open()) {
        printLineWith("error while opening the file");
    } else {
        binary.write((char *) &width, sizeof(width));
        binary.write((char *) &height, sizeof(height));
        int numberOfEdges = vector.size();
        binary.write((char *) &numberOfEdges, sizeof(width));

        for (auto &edge: vector) {
            int x1 = edge.first.first;
            int y1 = edge.first.second;
            int x2 = edge.second.first;
            int y2 = edge.second.second;
            binary.write((char *) &x1, sizeof(x1));
            binary.write((char *) &y1, sizeof(y1));
            binary.write((char *) &x2, sizeof(x2));
            binary.write((char *) &y2, sizeof(y2));
        }

        binary.seekg(0);
        binary.close();
    }
}

void saveSvg(basic_string<char, char_traits<char>, allocator<char> > &fileName, const vector<edge> &vector, int width,
             int height) {
    ofstream svg(fileName, ofstream::out);
    svg << "<svg" << " viewBox=" << "\"0 0 " << width << " " << height << "\"" << " width" << "=" << "\"" << width * 10
            << "\"" << " height=\"" << height * 10 << "\"" << " xmlns=" << "\"http://www.w3.org/2000/svg\">" << endl;
    svg << "<rect width =" << "\'" << width << "\' " << "height=\'" << height << "\' " << "style=\'"
            << "fill: black\' " << "/>" << endl;
    for (auto &edge: vector) {
        int x1 = edge.first.first;
        int y1 = edge.first.second;
        int x2 = edge.second.first;
        int y2 = edge.second.second;
        svg << "<line stroke=\'" << "white\' " << "stroke-width=\'" << "0.5\'" << " x1=\'" << x1 << "\' y1=\'" << y1
                << "\' x2=\'" << x2 << "\' y2=\'" << y2 << "\'/>" << endl;
    }
    svg << "</svg>";
    svg.close();
}

void printLineWith(const string &stringToPrint) {
    cout << stringToPrint << endl;
}

void printLineWithInt(const int &intToPrint) {
    cout << intToPrint << endl;
}

vector<edge> mazeGenerator(int seed, int width, int height, bool withSeed) {
    //    create an array to monitize visited cells
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


    //    create vector to store edges
    vector<edge> edges;
    //    check user input seed
    if (!withSeed) {
        seed = time(nullptr);
        cout << "Your seed is " << seed << endl;
    }
    srand(seed);

    bool keepHunting = true;
    bool keepKilling = true;

    //    generate a random stating cell
    coordinator startingCell;
    startingCell.first = rand() % height;
    startingCell.second = rand() % width;
    //    flag it as visited
    visitedArray[startingCell.first][startingCell.second] = true;
    //    bool starting = true;


    //    loop as hunting continuously
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
        //        check if whe need to killing
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
        //        loop as killing continuously
        while (keepKilling) {
            //            if (starting) {
            //                int numberOfNeighbours = 0;

            //                create a vector to store neighbour cell
            vector<coordinator> neighbours;
            //                neighbours.clear();

            //                looking for neighbours

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

            //                create vector to store checked neighbours randomly
            vector<int> randomizedNeighbours;
            //                randomizedNeighbours.clear();
            //                coordinator nextCell;

            //                loop to check all neighbours randomly to find a not visited neighbour
            bool keepSeeking = true;
            while (keepSeeking) {
                int currentRandom = rand() % neighbours.size();
                bool addingRandom = true;
                //                    check if randomized neighbour is checked or not
                for (int randomizedNeighbour: randomizedNeighbours) {
                    if (randomizedNeighbour == currentRandom) {
                        addingRandom = false;
                        break;
                    }
                }
                //                    if not checked, add to checked vector
                if (addingRandom) {
                    randomizedNeighbours.push_back(currentRandom);
                    coordinator neighbour = neighbours[currentRandom];
                    //                        check if not visited
                    if (!visitedArray[neighbour.first][neighbour.second]) {
                        keepSeeking = false;
                        //                            mark as visited
                        visitedArray[neighbour.first][neighbour.second] = true;
                        //                            add edge
                        edge edge1;
                        edge1.first = startingCell;
                        edge1.second = neighbour;
                        edges.push_back(edge1);
                        startingCell.first = neighbour.first;
                        startingCell.second = neighbour.second;
                        printLineWith("killed");
                    }
                } else {
                    //                        else check if the neighbours vector is all checked
                    if (randomizedNeighbours.size() == neighbours.size()) {
                        keepSeeking = false;
                        keepKilling = false;
                    }
                }
            }
            //            }
        }

        //        hunting
        bool foundStarting = false;
        //        loop from left to right, top to bottom to find unvisited cell
        for (int k = 0; k < height; ++k) {
            for (int i = 0; i < width; ++i) {
                //                if unvisited step into an check
                if (!visitedArray[k][i]) {
                    //                    assume it has a least one
                    startingCell.first = k;
                    startingCell.second = i;

                    //                    create a vector to store neighbour cell
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
                    //                    check if any neighbour is visited, if not break to find the next cel
                    for (auto neighbour: neighbours) {
                        if (visitedArray[neighbour.first][neighbour.second]) {
                            foundStarting = true;
                            break;
                        }
                    }
                    //                    if any neighbour is visited
                    if (foundStarting) {
                        //                        create a checked neighbours vector
                        vector<int> randomizedNeighbours;
                        //                        randomizedNeighbours.clear();

                        //                        loop to randomized through neighbours vector
                        bool keepSeeking = true;
                        while (keepSeeking) {
                            int currentRandom = rand() % neighbours.size();
                            bool addingRandom = true;
                            //                            check if randomized neighbour is checked or not
                            for (int randomizedNeighbour: randomizedNeighbours) {
                                if (randomizedNeighbour == currentRandom) {
                                    addingRandom = false;
                                    break;
                                }
                            }
                            //                            if not checked, add to checked vector
                            if (addingRandom) {
                                randomizedNeighbours.push_back(currentRandom);
                                coordinator neighbour = neighbours[currentRandom];
                                //                                check if visited
                                if (visitedArray[neighbour.first][neighbour.second]) {
                                    keepSeeking = false;
                                    //                                    mark the starting cell is visisted
                                    visitedArray[startingCell.first][startingCell.second] = true;
                                    //                                    add edge
                                    edge edge1;
                                    edge1.first = startingCell;
                                    edge1.second = neighbour;
                                    edges.push_back(edge1);
                                    printLineWith("hunted");
                                }
                            } else {
                                //                                else check if the neighbours vector is all checked
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
        //        check if need hunting
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

    //    print edges
    for (auto edge1: edges) {
        cout << edge1.first.first << " " << edge1.first.second << " : " << edge1.second.first << " "
                << edge1.second.second << endl;
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
