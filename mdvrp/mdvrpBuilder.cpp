//
//  Created by Federico Pagnozzi on 12/12/17.
//  Copyright (c) 2014 Federico Pagnozzi. All rights reserved.
//  This file is distributed under the BSD 2-Clause License. See LICENSE.TXT
//  for details.

#include "mdvrpBuilder.h"
#include "mdvrpinstance.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

#define MDVRP "MDVRP"
#define INITIAL_RANDOM "random"
#define INITIAL_CW "cw"
#define NEIGHBORHOOD_MOVE "move"
#define NEIGHBORHOOD_MOVE2 "move2"
#define NEIGHBORHOOD_EXCHANGE "exchange"
#define NEIGHBORHOOD_EXCHANGE2 "exchange2"
#define NEIGHBORHOOD_EXCHANGE21 "exchange21"  
#define NEIGHBORHOOD_TRANSPOSE "transpose"
#define NEIGHBORHOOD_2OPT "2opt"
#define NEIGHBORHOOD_2OPTSTAR "2opt*"
#define PERTURBATION_RESTART "restart" 
#define TERMINATION_ITERA "iteration"
#define TERMINATION_ITERATIONS "iterations"
#define ACCEPTANCE_TEST "test"
#define TABU_MEMORY_MOVES "moves"
#define TABU_MEMORY_VALUE "value"
#define TABU_MEMORY_SOLUTIONS "solutions"

char* problem_string;
emili::mdvrp::Mdvrp* loadProblem(char* t, MdvrpInstance i);


std::string info()
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

 emili::LocalSearch* prs::MdvrpBuilder::buildAlgo()
{
    prs::incrementTabLevel();
    emili::LocalSearch* ls = nullptr;
    prs::decrementTabLevel();
    return ls;

}


emili::Perturbation* prs::MdvrpBuilder:: buildPerturbation()
{
    prs::incrementTabLevel();
    emili::mdvrp::Mdvrp* instance =(emili::mdvrp::Mdvrp*) gp.getInstance();
    std::ostringstream oss;
    emili::Perturbation* per=nullptr;
    if(tm.checkToken(PERTURBATION_RESTART))
    {
        int n = tm.getInteger();
        oss.str(""); oss  << "Restart perturbation, n =" << n << "";
        printTab(oss.str().c_str());
        emili::InitialSolution* init = retrieveComponent(COMPONENT_INITIAL_SOLUTION_GENERATOR).get<emili::InitialSolution>();
        per = new emili::mdvrp::RestartPerturbation(n,init);
    }
    prs::decrementTabLevel();
    return per;
}


emili::Acceptance* prs::MdvrpBuilder::buildAcceptance()
{
    prs::incrementTabLevel();
    emili::mdvrp::Mdvrp* instance =(emili::mdvrp::Mdvrp*) gp.getInstance();
    emili::Acceptance* acc = nullptr;
    std::ostringstream oss;
    if(tm.checkToken(ACCEPTANCE_TEST))
    {
        int n = tm.getInteger();
        oss.str(""); oss  << "Probabilistic Acceptance. improving solution accepted"<<n<<" % of the time";
        printTab(oss.str().c_str());
        acc = new  emili::mdvrp::MdvrpTestAcceptance(*instance,n);
    }
    prs::decrementTabLevel();
    return acc;
}


emili::TabuMemory* prs::MdvrpBuilder::buildTabuTenure()
{
    prs::incrementTabLevel();
    std::ostringstream oss;
    emili::TabuMemory* tmem = nullptr;
    if(tm.checkToken(TABU_MEMORY_MOVES))
    {
        oss.str(""); oss << "USING MOVES\n\t";
        int ts = tm.getInteger();
        oss << "Tabu tenure size " << ts;
        printTab(oss.str().c_str());
        tmem = new  emili::mdvrp::MdvrpMovesMemory(ts);
    }else if  (tm.checkToken(TABU_MEMORY_VALUE)){
        oss.str(""); oss << "USING VALUE\n\t" ;        
        int ts = tm.getInteger();
        oss << "Tabu tenure size " << ts;
        printTab(oss.str().c_str());
        tmem = new  emili::mdvrp::MdvrpTabuValueMemory(ts);
    }else if (tm.checkToken(TABU_MEMORY_SOLUTIONS)){
        oss.str(""); oss << "USING FULL SOLUTIONS\n\t" ;        
        int ts = tm.getInteger();
        oss << "Tabu tenure size " << ts;
        printTab(oss.str().c_str());
        tmem = new  emili::mdvrp::MdvrpFullSolutionMemory(ts);
    }
    //printTab(oss.str().c_str());
    prs::decrementTabLevel();
    return tmem;
}


emili::InitialSolution* prs::MdvrpBuilder::buildInitialSolution()
{
    prs::incrementTabLevel();
    std::ostringstream oss;
    emili::InitialSolution* init = nullptr;
    emili::mdvrp::Mdvrp* instance =(emili::mdvrp::Mdvrp*) gp.getInstance();

    if(tm.checkToken(INITIAL_RANDOM))
    {
        printTab("Random initial solution");
        init = new emili::mdvrp::MdvrpRandomInitialSolution(*instance);
    }else if (tm.checkToken(INITIAL_CW))
    {
        printTab("Clarke and wright initial solution");
        init = new emili::mdvrp::MdvrpCWInitialSolution(*instance);
    }
    prs::decrementTabLevel();
    return init;
}


emili::Termination* prs::MdvrpBuilder::buildTermination()
{
    prs::incrementTabLevel();

    emili::Termination* term=nullptr;
    emili::mdvrp::Mdvrp* instance =(emili::mdvrp::Mdvrp*) gp.getInstance();
    if(tm.checkToken(TERMINATION_ITERA))
    {
        int ti = instance->getnbCustomers();
        if (ti > 300){
            ti = 200; // experiment with this 
        }else if (ti > 200 && ti <= 300){
            ti = 300;
        }else if (ti > 100 && ti <= 200){ 
            ti = 400;
        // }else if (ti > 100 && ti < 200){
        //     ti = 600;  // idk yet, experiment
        }else{
            ti = 800;
        }        
        std::ostringstream oss;
        oss << "number of max iterations "<< ti;
        printTabPlusOne(oss.str().c_str());
        term =  new emili::mdvrp::Iteratermination(ti);
    }else if (tm.checkToken(TERMINATION_ITERATIONS)){
        int ti = tm.getInteger();        
        printTab("Relaxed local minima termination");
        std::ostringstream oss;
        oss << "number of max iterations "<< ti;
        printTabPlusOne(oss.str().c_str());
        term =  new emili::mdvrp::MdvrpTerminationIterations(ti);
    }
    
    prs::decrementTabLevel();
    return term;
}

emili::Neighborhood* prs::MdvrpBuilder::buildNeighborhood()
{
    prs::incrementTabLevel();
    emili::mdvrp::NeighborhoodMdvrp* neigh = nullptr;
    emili::mdvrp::Mdvrp* instance =(emili::mdvrp::Mdvrp*) gp.getInstance();
    if(tm.checkToken(NEIGHBORHOOD_MOVE))
    {
        printTab( "Move Neighborhood");
        neigh = new emili::mdvrp::MdvrpMoveNeighborhood(*instance);
    }else if(tm.checkToken(NEIGHBORHOOD_EXCHANGE))
    {
        printTab( "Exchange Neighborhood");
        neigh = new emili::mdvrp::MdvrpExchangeNeighborhood(*instance);
    }else if(tm.checkToken(NEIGHBORHOOD_EXCHANGE2))
    {
        printTab( "Exchange 2 Neighborhood");
        neigh = new emili::mdvrp::MdvrpExchange2Neighborhood(*instance);
    }else if(tm.checkToken(NEIGHBORHOOD_EXCHANGE21))
    {
        printTab( "Exchange 2-1 Neighborhood");
        neigh = new emili::mdvrp::MdvrpExchange21Neighborhood(*instance);
    }else if(tm.checkToken(NEIGHBORHOOD_MOVE2))
    {
        printTab( "Move 2 Neighborhood");
        neigh = new emili::mdvrp::MdvrpMove2Neighborhood(*instance); // NOT WORKING RIGHT NOW
    }else if(tm.checkToken(NEIGHBORHOOD_TRANSPOSE))
    {
        printTab( "transpose Neighborhood");
        neigh = new emili::mdvrp::MdvrpTransposeNeighborhood(*instance); // maybe wrong since worse than exchange, im not sure
    }else if(tm.checkToken(NEIGHBORHOOD_2OPT))
    {
        printTab( "2 opt Neighborhood");
        neigh = new emili::mdvrp::Mdvrp2optNeighborhood(*instance); // maybe wrong since worse than exchange, im not sure
    }else if(tm.checkToken(NEIGHBORHOOD_2OPTSTAR))
     {
         printTab( "2 opt* Neighborhood");
         neigh = new emili::mdvrp::Mdvrp2optstarNeighborhood(*instance); // maybe wrong since worse than exchange, im not sure
     }
    
    prs::decrementTabLevel();
    return neigh;
}

    
emili::Problem* prs::MdvrpBuilder::buildProblem()
{
    emili::mdvrp::Mdvrp* instance =(emili::mdvrp::Mdvrp*) gp.getInstance();
    return loadProblem(tm.nextToken(),instance->getInstance());
}


emili::mdvrp::Mdvrp* loadProblem(char* t, MdvrpInstance i)
{    
    emili::mdvrp::Mdvrp* prob;
    if(strcmp(t,MDVRP)==0)
    {
#ifdef ENABLE_SSE
        prs::printTab("SSE run path enabled");
#endif
        prs::printTab("MDVRP");
        prob = new emili::mdvrp::Mdvrp(i);
    }
    else
    {
        std::cerr<< "'" << t << "' -> ERROR a problem was expected! " << std::endl;
        prs::info();
        exit(-1);
    }
    return prob;
}


emili::Problem* prs::MdvrpBuilder::openInstance()
{
    MdvrpInstance i;    
    problem_string = tm.nextToken();
    bool ok;
    std::string pro(problem_string);
    std::string sdst("SDSTPFS");
    std::string nlistt_d = tm.nextToken();
    int nlist_d = stoi(nlistt_d);
    ok = i.readDataFromFile(tm.tokenAt(1), nlist_d);
    if(ok)
     {
        emili::mdvrp::Mdvrp* instance = loadProblem(problem_string, i);
        return instance;
     }
    exit(-1);
}


bool isParsable(std::string &problem)
{
    if(strcmp(problem.c_str(),MDVRP)==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool prs::MdvrpBuilder::isCompatibleWith(char *problem_definition)
{
    std::string s(problem_definition);
    return isParsable(s);
}
    
bool prs::MdvrpBuilder::canOpenInstance(char *problem_definition)
{
    std::string s(problem_definition);
    return isParsable(s);
}

extern "C" {
    prs::Builder* getBuilder(prs::GeneralParserE* ge)
    {
        return new prs::MdvrpBuilder(*ge,ge->getTokenManager());
    }
}