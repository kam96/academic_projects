#include "IagoAI.hpp"
#include <ics46/factory/DynamicFactory.hpp>

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, kbalutch::IagoAI, "IagoAI (Required)");

int kbalutch::IagoAI::search(unique_ptr<OthelloGameState> &state, int depth)
{
    if (depth == 0)
    {
        if (player) 
            return (state->whiteScore() - state->blackScore());
        else 
            return (state->blackScore() - state->whiteScore());
    }

    int value;
    vector<int> evaluator;
    unique_ptr<OthelloGameState> newState;

    for (int i = 0; i < state->board().height(); i++)
    {
        for (int j = 0; j < state->board().width(); j++)
        {
            if (state->isValidMove(i,j))
            {
                newState = state->clone();
                newState->makeMove(i,j);
                evaluator.push_back(search(newState, depth-1));
            }
        }
    }

    value = (evaluator.empty()) ? 0 : evaluator[0];

    for (int i = 0; i < evaluator.size(); i++)
    {
        if ((player && state->isWhiteTurn()) || (!player && state->isBlackTurn()))
        {
            if (evaluator[i] > value)
                value = evaluator[i]; 
        }
        else
        {
            if (evaluator[i] < value) 
                value = evaluator[i];
        }
    }

    return value;
}

pair<int,int> kbalutch::IagoAI::chooseMove(const OthelloGameState &state)
{
    unique_ptr<OthelloGameState> game = state.clone(); 
    player = game->isWhiteTurn();
    int path = search(game,5);

    for (int i = 0; i < game->board().height(); i++)
    {
        for (int j = 0; j < game->board().width(); j++)
        {
            if (game->isValidMove(i,j))
            {
                unique_ptr<OthelloGameState> newState = game->clone();
                newState->makeMove(i,j);
                if (search(newState,4) == path) 
                    return make_pair(i,j);
            } 
        }
    }

    return make_pair(0,0);
}
