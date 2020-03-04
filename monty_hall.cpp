#include <iostream>
#include <cstdlib>
#include <random>

#define NDOORS 3

class DoorPicker
{
    public:
        int pick(void) { return distribution(generator); }

    private:
        std::random_device rd;
        std::default_random_engine generator{ rd() };
        std::uniform_int_distribution<int> distribution{ 0, NDOORS - 1 };
};

long run(long nTests, bool stick)
{
    DoorPicker dp;

    long res = 0;
    while(nTests-- > 0)
    {
        bool doors[NDOORS] = {};
        doors[dp.pick()] = true;

        int choice = dp.pick();

        int eliminated = dp.pick();
        while(doors[eliminated] || eliminated == choice)
            eliminated = dp.pick();

        if(!stick)
        {
#if NDOORS == 3
            do
            {
                choice = (choice + 1) % NDOORS;
            } while(choice == eliminated);
#else
            // In case we have more than 3 doors this should still pick the random one
            int choice2 = dp.pick();
            while(choice2 == eliminated || choice2 == choice)
                choice2 = dp.pick();

            choice = choice2;
#endif
        }

        res += doors[choice];
    }

    return res;
}

void printStats(long nTests, long nWins, const char *name)
{
    std::cout << "===> " << name << " <===" << std::endl;
    std::cout << "\tTests: " << nTests << std::endl;
    std::cout << "\tWon:   " << nWins << std::endl;
    std::cout << "\tLost:  " << nTests - nWins << std::endl;
    std::cout << "\tRate:  " << nWins * 100.0 / nTests << "%" << std::endl;
}

int main(int argc, const char* argv[])
{
    long nTests = 1000000;

    if(argc > 1 && !(nTests = strtol(argv[1], nullptr, 10)))
    {
        std::cerr << "Usage: " << argv[0] << " [number of tests]" << std::endl;
        return EXIT_FAILURE;
    }

    printStats(nTests, run(nTests, true), "STICK");
    std::cout << std::endl;
    printStats(nTests, run(nTests, false), "SWITCH");

    return EXIT_SUCCESS;
}
