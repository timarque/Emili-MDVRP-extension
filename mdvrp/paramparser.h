#ifndef PARAMSPARSER_H
#define PARAMSPARSER_H
#include "../generalParser.h"
#include "mdvrp.h"
namespace prs
{
class ParamParser: public AlgoBuilder
{
protected:    
    emili::mdvrp::Mdvrp* instance;
    std::vector< emili::mdvrp::Mdvrp* > istances;
    /**  ALGOS */
    emili::LocalSearch* eparams(prs::TokenManager& tm);
    emili::LocalSearch* search(prs::TokenManager& tm);
    emili::LocalSearch* ils(prs::TokenManager& tm);
    emili::LocalSearch* gvns(prs::TokenManager& tm);
    emili::LocalSearch* ch6_params(prs::TokenManager& tm);
    emili::BestTabuSearch* tparams(prs::TokenManager& tm);
    emili::LocalSearch* vparams(prs::TokenManager& tm);
    void params(prs::TokenManager& tm);
    /** INITIAL SOLUTION*/
    emili::InitialSolution* init(prs::TokenManager& tm);
    /** TERMINATION*/
    emili::Termination* term(prs::TokenManager& tm);
    /** NEIGHBORHOOD*/
    emili::Neighborhood* neigh(prs::TokenManager& tm,bool checkExist);
    /** PERTURBATION*/
    emili::Perturbation* per(prs::TokenManager& tm);
    /** ACCEPTANCE*/
    emili::Acceptance* acc(prs::TokenManager& tm);
    /** TABU TENURE */
    emili::TabuMemory* tmemory(emili::mdvrp::NeighborhoodMdvrp* n,prs::TokenManager& tm);
    /** NEIGHBORHOOD UTILS*/
    void neighs(prs::TokenManager& tm);
    void neighs1(prs::TokenManager& tm);
    /** Problem load*/
    void problem(prs::TokenManager& tm, int nlist_d);
    virtual std::string availableProblems() const;
public:
    virtual bool isParsable(std::string& problem) ;
    virtual emili::LocalSearch* buildAlgo(prs::TokenManager& tm, int nlist_d);
    virtual std::string info();
    ParamParser() { }
    ~ParamParser() { delete instance; for(int i=0;i<istances.size();i++)delete istances[i];}
};




}


#endif // PARAMSPARSER_H