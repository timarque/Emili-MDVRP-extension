#include "paramparser.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "mdvrpinstance.h"

/* Algos */
#define IG "ig"
#define ILS "ils"
#define TABU "tabu"
#define FIRST "first"
#define BEST "best"
#define TB_FIRST "tfirst"
#define TB_BEST "tbest"
#define VND "vnd"
#define GVNS_ILS "gvns"
#define CH6_LS "ch6"
#define TEST_INIT "stin"
#define EMPTY_LOCAL "nols"

/* tabu tenure types */
#define TABU_MEMORY_MOVES "move"
#define TABU_MEMORY_HASHES "hash"
#define TABU_MEMORY_SOLUTIONS "solution"
#define TABU_MEMORY_TSAB "tsabm"
#define TABU_MEMORY_TSAB_TEST "tsabmt"
#define TABU_MEMORY_VALUE "value"


/* modifiers */
#define RO "-ro"
#define IT "-it"
#define TS "-ts"
#define TI "-ti"
#define IN "-in"
#define TE "-te"
#define NE "-ne"
#define NS "-ns"
#define RNDSEED "rnds"
#define DEFAULT_TS 10
#define DEFAULT_TI 10
#define DEFAULT_IT 0


/*  problem */
#define MDVRP "MDVRP"

/* initial solution heuristics */
#define INITIAL_RANDOM "random"


/* Termination criteria*/
#define TERMINATION_MAXSTEPS "maxstep"
#define TERMINATION_MAXSTEPS_OR_LOCMIN "msorlocmin"
#define TERMINATION_TIME "time"
#define TERMINATION_LOCMIN "locmin"
#define TERMINATION_ITERA "iteration"
//#define TERMINATION_WTRUE "true"
//#define TERMINATION_SOA "soater"

#define NEIGHBORHOOD_MOVE "move"

/* permutation flowshop solution perturbations */
#define PERTURBATION_RANDOM_MOVE "rndmv"
char* problem_type;

emili::Neighborhood* ne = nullptr;
emili::InitialSolution* in= nullptr;
emili::Termination* te= nullptr;
emili::TabuMemory* tmem= nullptr;
emili::Termination* ilt= nullptr;

emili::mdvrp::Mdvrp* instantiateProblem(char* t, MdvrpInstance i){

    emili::mdvrp::Mdvrp* prob;
    if(strcmp(t,MDVRP)==0){
#ifdef ENABLE_SSE
        prs::printTab("SSE run path enabled");
#endif
        prs::printTab("Permutation Flow Shop Weighted Tardiness");
        prob = new emili::mdvrp::Mdvrp(i);
    }

    return prob;
}


// modify trhis later
std::string prs::ParamParser::info()
{
    std::ostringstream oss;
    oss << "Usage:\n\n";
    oss << "EMILI INSTANCE_FILE_PATH MDVRP_PROBLEM <LOCAL_SEARCH | ITERATED_LOCAL_SEARCH | TABU_SEARCH | VND_SEARCH> [rnds seed]\n\n";
    oss << "PROBLEM               = "<<MDVRP <<"\n";
    oss << "LOCAL_SEARCH          = SEARCH_TYPE INITIAL_SOLUTION TERMINATION NEIGHBORHOOD" <<"\n";
    oss << "ITERATED_LOCAL_SEARCH = ils LOCAL_SEARCH TERMINATION PERTURBATION ACCEPTANCE -it seconds" << "\n";
    oss << "TABU_SEARCH           = tabu < first | best > INITIAL_SOLUTION TERMINATION NEIGHBORHOOD TABU_MEMORY " << "\n";
    oss << "VND_SEARCH            = vnd < first | best > INITIAL_SOLUTION TERMINATION NEIGHBORHOOD1 NEIGHBORHOOD2 ... NEIGHBORHOODn" << "\n";
    oss << "GVNS_SEARCH           = gvns INITIAL_SOLUTION PERTURBATION1 PERTURBATION2 -it seconds" << "\n";
    oss << "SEARCH_TYPE           = first | best | tabu | vnd | ils" << "\n";
    oss << "INITIAL_SOLUTION      = random | slack | nwslack | lit | rz | nrz | nrz2 | lr size(int)| nlr size(int) | mneh" <<"\n";
    oss << "TERMINATION           = true | time float | locmin | soater | iteration int | maxstep int" << "\n";
    oss << "NEIGHBORHOOD          = transpose | exchange | insert | binsert | finsert | tinsert | "<< NEIGHBORHOOD_MOVE<< " | " <<"\n";
    oss << "PERTURBATION           = igper int | testper | rndmv NEIGHBORHOOD #moves(int) | noper (int) | nrzper (int) | tmiigper (int) (int) | igls (int) LOCAL_SEARCH | rsls (int) LOCAL_SEARCH" << "\n";
    oss << "ACCEPTANCE            = soaacc float | testacc #swaps(int) | metropolis start_temperature(float) | always (intensify | diversify) | improve | sa_metropolis start_temp end_temp ratio | pmetro start_temp end_temp ratio frequence(int) | saacc start_temp end_temp ratio frequence(int) alpha ]0,1] | tmiigacc start_temperature(float) | implat number_of_non_improving_steps_accepted plateau_threshold" << std::endl;
    oss << "TABU_MEMORY           = move size(int) | hash size(int) | solution size(int) | tsabm size(int)" << "\n";
   // std::cout << " syntax->EMILI instancefile search_type intial_solution termination neighborhood" << std::endl;
    return oss.str();
}

emili::LocalSearch* prs::ParamParser::eparams(prs::TokenManager& tm)
{
    prs::incrementTabLevel();
    emili::LocalSearch* ls;
    if(tm.checkToken(ILS))
    {
        printTab("ILS");
        ls = ils(tm);
    }  

    prs::decrementTabLevel();
    return ls;
}

emili::LocalSearch* prs::ParamParser::search(prs::TokenManager& tm)
{
    prs::incrementTabLevel();
    emili::LocalSearch* ls;
    if(tm.checkToken(ILS))
    {
        printTab("ILS ");
        ls = ils(tm);

    }
    prs::decrementTabLevel();
    return ls;

}

emili::LocalSearch* prs::ParamParser::ils(prs::TokenManager& tm)
{

    //emili::LocalSearch* ls = search(tm);
    //ils_time = ilstime();
    //emili::Termination* pft = term(tm);
    //emili::Perturbation* prsp = per(tm);
    int rpc = 5;
    //emili::Perturbation* prsp = per(tm);
    //emili::AcceptanceCriteria* tac = new emili::pfsp::PfspTestAcceptance(istance);
    //emili::AcceptanceCriteria* tac = new emili::MetropolisAcceptance(1);
    //emili::Acceptance* tac = acc(tm);//new emili::pfsp::SOAacceptance(1.2f); new emili::IteratedLocalSearch(*ls,*pft,*prsp,*tac)
    emili::LocalSearch* iils = nullptr;   
    return iils;
}

void prs::ParamParser::params(prs::TokenManager& tm)
{
    in = init(tm);
    te = term(tm);
    ne = neigh(tm,true);
}



emili::InitialSolution* prs::ParamParser::init(prs::TokenManager& tm)
{
    prs::incrementTabLevel();
    std::ostringstream oss;
    emili::InitialSolution* init;
    if(tm.checkToken(INITIAL_RANDOM))
    {
        printTab("Random initial solution");
        init = new emili::mdvrp::MdvrpRandomInitialSolution(*instance);
    }
    else
    {
        std::cerr<< "'" << *tm << "' -> ERROR a initial solution generator specification was expected! (random,slack)" << std::endl;

        std::cout << info() << std::endl;
        exit(-1);
    }
    prs::decrementTabLevel();
    return init;
}



emili::Termination* prs::ParamParser::term(prs::TokenManager& tm)
{
    prs::incrementTabLevel();
    emili::Termination* term;
    // have to do this 
    if(tm.checkToken(TERMINATION_ITERA))
    {
        printTab("Max iteration number termination");
        int ti = instance->getnbCustomers();
         ti = 2*(ti-1);
        term =  new emili::mdvrp::Iteratermination(ti);
    }
    else if(tm.checkToken(TERMINATION_TIME))
    {

        float time =tm.getDecimal();
        if(time==0){
            time = 1;
        }
        std::ostringstream oss;
        oss << "Timed termination. ratio: " << time;
        printTab(oss.str().c_str());
        term =  new emili::TimedTermination(time);
    }
    else if(tm.checkToken(TERMINATION_MAXSTEPS))
    {
        int steps = tm.getInteger();
        std::ostringstream oss;
        oss << "Max Steps termination. # steps: "<< steps;
        printTab(oss.str().c_str());
        term = new emili::MaxStepsTermination(steps);
    }

    prs::decrementTabLevel();
    return term;
}



emili::Neighborhood* prs::ParamParser::neigh(prs::TokenManager& tm,bool checkExist)
{
    prs::incrementTabLevel();
    emili::Neighborhood* neigh = nullptr;
    if(tm.checkToken(NEIGHBORHOOD_MOVE))
    {
        printTab( "Insert Neighborhood");
        neigh = new emili::mdvrp::MdvrpMoveNeighborhood(*instance);
    }
    return neigh;
}


void prs::ParamParser::problem(prs::TokenManager& tm, int nlist_d)
{
    MdvrpInstance i;    
    problem_type = tm.nextToken();
    bool ok;
    std::string pro(problem_type);
    std::string sdst("SDSTMDVRP");
    ok = i.readDataFromFile(tm.tokenAt(1), nlist_d);
    if(ok)
     {
         instance = instantiateProblem(problem_type, i);
        return;
     }

        std::cout << info() << std::endl;
        exit(-1);
}

#include "mdvrpBuilder.h"
emili::LocalSearch* prs::ParamParser::buildAlgo(prs::TokenManager& tm, int nlist_d)
{
    /*tm.move(0);
    prs::GeneralParserE  ps(tm);
    prs::EmBaseBuilder emb(ps,ps.getTokenManager());
    prs::PfspBuilder pfspb(ps,ps.getTokenManager());
    ps.addBuilder(&emb);
    ps.addBuilder(&pfspb);
    emili::LocalSearch* local = ps.parseParams();*/
    problem(tm, nlist_d);  
    emili::LocalSearch* local = eparams(tm);
    std::cout << "------" << std::endl;
    return local;
}


bool prs::ParamParser::isParsable(std::string &problem)
{
    if(strcmp(problem.c_str(),MDVRP)==0)
    {
        return true;
    }else
    {
        return false;
    }
}