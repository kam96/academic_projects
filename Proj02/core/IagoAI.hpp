#include "OthelloAI.hpp"
#include <vector>
using namespace std;

namespace kbalutch
{
    class IagoAI: public OthelloAI
    {
    private:
        bool player;
    public:
        int search(unique_ptr<OthelloGameState> &state, int depth);
        virtual pair<int,int> chooseMove(const OthelloGameState &state);
    };
}
