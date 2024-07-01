//
//  Created by Federico Pagnozzi on 12/12/17.
//  Copyright (c) 2014 Federico Pagnozzi. All rights reserved.
//  This file is distributed under the BSD 2-Clause License. See LICENSE.TXT
//  for details.

#ifndef MDVRP_H
#define MDVRP_H
#include "../emilibase.h"
#include "mdvrpinstance.h"
#include <cstdlib>
#include <climits>
#include <string>
#include <sstream>
#include <assert.h>
#include <algorithm>
#include <limits>


void notyet();



namespace emili{
namespace mdvrp{

class Mdvrp: public emili::Problem{ // remember you have to give FULL PATH of file 
protected:
MdvrpInstance instance;
double init_sol_cost;
//std::vector<std::vector<int>> granular;

public:
    // need to understand how to use this (I assume second one is used since instance construct has no params)
    // Constructor that uses a MDVRPInstance implementation
    Mdvrp(MdvrpInstance& problemInstance):instance(problemInstance) {}
    //Constructor that loads the instance from file path
    Mdvrp(char* instance_path, int nlist_d):instance()
    {
        /**  Read data from file */
        if (! instance.readDataFromFile(instance_path,nlist_d) ){
            exit(-1);
        }
    }

    int getnbVehicles();
    int getnbCustomers();
    int getnbDepots();
    int getmaxDuration();
    int getmaxCapacity();
    double getInit_sol_cost();
    void setInit_sol_cost(double cost);

    std::vector<int>& getcustomers();
    std::vector<int>& getdepots();
    std::vector<std::vector<double>>& getcoordinates();
    std::vector<int>& getserviceDuration();
    std::vector<int>& getdemand();
    std::vector<std::vector<double>>& getdistanceMatrix();
    std::vector<std::vector<int>>& getnlist(); // neighborhood list
    bool checkConstraints(std::vector<int>& sol);

    double computeObjectiveFunction(std::vector< int > & partial_solution);

    /**
     * @brief calcObjectiveFunctionValue
     * This function calculates the objective function value of solution and returns
     * it as a double.
     * @param solution
     * the solution to use in the calculation of the objective function value.
     * @return
     * a double representing the cost of solution
     */
    virtual double calcObjectiveFunctionValue(Solution& solution);
    /**
     * @brief evaluateSolution
     *  This function calculates the objective function value and, using setSolutionValue,
     *  update the solution value in the Solution class.
     * @param solution
     * @return
     * the return value should be the objective function value of the solution
     */

    virtual double evaluateSolution(Solution & solution);
    /**
     * @brief problemSize
     * @return
     *  if overloaded this function should return the problem size as an integer number
     *  This value is used by some Termination criterion and by the -ro running option
     */
    virtual int problemSize() {return 1;}
    

    // instance functions:
    MdvrpInstance& getInstance();

};

/**
 * @brief The Solution class
 * This class models a solution to an optimization problem.
 * This class should contain all the data structures regarding the solution.
 */
class SolutionMdvrp: public emili::Solution
{
    std::vector<int> sol; 
    // int max_cap; 
    // int max_servduration;
    // std::vector<int> demands;
    // std::vector<int> times; 

protected:
    /**
     * @brief getRawData
     * It's ugly I know, but every problem has its own data structures.
     * The next version will have an object designed to be a data carrier.
     * @return
     *  a pointer to the raw data which is the problem dependent data structures of the solution
     */
    virtual const void* getRawData()const; 
    /**
     * @brief setRawData
     * changes the rawdata of the solution to data.
     *  The definition of the corresponding instance variable is not here because this variable
     *  can be defined, in the child class, as a pointer to the actual type of raw data
     *  so you can avoid the use of a pointer to void.
     * @param data
     */
    virtual void setRawData(const void* data);
public:
    SolutionMdvrp(double p_value): //int max_c, int max_sd, std::vector<int>& demands, std::vector<int>& durations
    emili::Solution(p_value),sol()//,max_cap(max_c),max_servduration(max_sd),demands(demands),times(durations)
    {}
    SolutionMdvrp(std::vector<int>& solution)
    :emili::Solution(1e9),sol(solution)//,max_cap(max_c),max_servduration(max_sd),demands(demands),times(durations)
    {}
    SolutionMdvrp(double p_value,std::vector<int>& solution )
    :emili::Solution(p_value),sol(solution)//,max_cap(max_c),max_servduration(max_sd),demands(demands),times(durations)
    {}

    std::vector<int>& get_sol(){return this->sol;}
    /**
     * @brief getSolutionRepresentation
     * @return
     * returns an empty string. A child class should return a representation of
     * the solution. ( e.g. for permutation flowshop a permutaion ).
     */
    virtual std::string getSolutionRepresentation();
    /**
     * @brief clone
     * this method should return a pointer to a clone of the Solution.
     * The clone is expected to be allocated on the heap (so created with 'new').
     * @return
     * return a pointer to a clone of the Solution.
     */
    virtual Solution* clone();
    /**
     *@brief isFeasible
     * This method should be overwritten if the problem has
     * unfeasible solutions.
     * this method should return true if the Solution is feasible and
     * false in the other case.
     */
    virtual bool isFeasible(){return true;}; 

    /**
     * @brief ~Solution
     * Destructor of Solution.
     * This method should always be overloaded and when called delete the raw data
     * (if allocated on the heap).
     */

    virtual bool operator==(Solution& a);
    
    virtual ~SolutionMdvrp() {}
};

/**
 * @brief The InitialSolution class
 * The initial solution generator
 */
class InitialSolutionMdvrp: public emili::InitialSolution
{
protected:
    Mdvrp& pis;
    virtual Solution* generate() = 0 ;
public:
    /**
     * @brief InitialSolution
     *  The constructor only needs the problem instance to build an initial solution
     * @param problem_instance
     */
    InitialSolutionMdvrp(Mdvrp& problem_instance):emili::InitialSolution(problem_instance),pis(problem_instance){}
    /**
     * @brief generateSolution
     * The generated solution must be a valid solution for the problem with
     * the appropriate data structures used for the implemented solution.
     * @return
     *  A new solution for instance
     */
    virtual Solution* generateSolution();
    /**
     * @brief generateEmptySolution
     * The method should generate an empty solution correctly allocated in
     * memory. This method is necessary because the LocalSearch class
     * and his extensions do not have any clou on how to allocate a solution.
     * @return
     * A solution object with all his data structures initialiazed
     */
    virtual Solution* generateEmptySolution();
    /**
     * @brief ~InitialSolution
     * This method should be overloaded by the child class to delete
     *  anything it allocates on the heap
     */
    virtual ~InitialSolutionMdvrp() {}
};

class MdvrpRandomInitialSolution: public emili::mdvrp::InitialSolutionMdvrp
{
protected:    
    virtual Solution* generate();
public:
    MdvrpRandomInitialSolution(Mdvrp& problem_instance):emili::mdvrp::InitialSolutionMdvrp(problem_instance){ }
};



class MdvrpCWInitialSolution: public emili::mdvrp::InitialSolutionMdvrp
{
protected:    
    virtual Solution* generate();
public:
    MdvrpCWInitialSolution(Mdvrp& problem_instance):emili::mdvrp::InitialSolutionMdvrp(problem_instance){ }
};


/**
 * @brief The Neighborhood class
 *     The class models the neighborhood of a solution
 *     This class should return the neighbors of a base solution
 *     given a specific neighborhood relation.
 */
class NeighborhoodMdvrp: public emili::Neighborhood
{
protected:
    Mdvrp& pis;
    std::vector<std::vector<int>> nlist = pis.getnlist();
    //std::vector<std::vector<int>> granular;
    //int routes;
    virtual Solution* computeStep(Solution* step) =0;
public:
    NeighborhoodMdvrp(Mdvrp& problem):pis(problem){}
    bool checkConstraints(std::vector<int>& sol);
    //std::vector<std::vector<int>> calculate_granular(emili::Solution* value);
    virtual Solution* step(Solution* currentSolution);
    virtual Mdvrp& getProblem() { return pis; }
    virtual std::pair<int,int> lastMove() { return std::pair<int,int>(0,0); }
    virtual void reset();
    virtual Solution* random(Solution *currentSolution) = 0;
    virtual int size();
    virtual ~NeighborhoodMdvrp() {}
};

// move neighborhood
class MdvrpMoveNeighborhood: public emili::mdvrp::NeighborhoodMdvrp{
protected:
    int start_position;
    int end_position;
    int sp_iterations;
    int ep_iterations;
    virtual Solution* computeStep(Solution* value);
    virtual void reverseLastMove(Solution *step);
public:
    MdvrpMoveNeighborhood(Mdvrp& problem):NeighborhoodMdvrp(problem),start_position(0),end_position(0),sp_iterations(1),ep_iterations(1){}
    virtual void reset();
    virtual Solution* random(Solution* currentSolution);
    
    virtual std::pair<int,int> lastMove(){return std::pair<int,int>(end_position,start_position);}; 
    virtual NeighborhoodIterator begin(Solution *base);
    virtual ~MdvrpMoveNeighborhood() {}
    
};


// move2 neighborhood 
class MdvrpMove2Neighborhood: public emili::mdvrp::NeighborhoodMdvrp{
protected:
    int start_position;
    int start_position2;
    int end_position;
    int real_end_position;
    int sp_iterations;
    int ep_iterations;
    virtual Solution* computeStep(Solution* value);
    virtual void reverseLastMove(Solution *step);
public:
    MdvrpMove2Neighborhood(Mdvrp& problem):NeighborhoodMdvrp(problem),start_position(0),end_position(0),sp_iterations(1),ep_iterations(1){}
    virtual void reset();
    virtual Solution* random(Solution* currentSolution);
    virtual std::pair<int,int> lastMove(){return std::pair<int,int>(end_position,start_position);}; 
    virtual NeighborhoodIterator begin(Solution *base);
    virtual ~MdvrpMove2Neighborhood() {}
    
};


class MdvrpTransposeNeighborhood: public emili::mdvrp::NeighborhoodMdvrp{
protected:
    int start_position;
    int endpos;
    int sp_iterations;
    virtual Solution* computeStep(Solution* value);
    virtual void reverseLastMove(Solution *step);
public:
    MdvrpTransposeNeighborhood(Mdvrp& problem):NeighborhoodMdvrp(problem),start_position(0),endpos(0),sp_iterations(1){}
    virtual void reset();
    virtual Solution* random(Solution* currentSolution);
    virtual std::pair<int,int> lastMove(){return std::pair<int,int>(endpos,start_position);}; 
    virtual NeighborhoodIterator begin(Solution *base);
    virtual ~MdvrpTransposeNeighborhood() {}
    
};


class MdvrpExchangeNeighborhood: public emili::mdvrp::NeighborhoodMdvrp{
protected:
    int start_position;
    int end_position;
    int sp_iterations;
    int ep_iterations;
    virtual Solution* computeStep(Solution* value);
    virtual void reverseLastMove(Solution *step);
public:
    MdvrpExchangeNeighborhood(Mdvrp& problem):NeighborhoodMdvrp(problem),start_position(0),end_position(0),sp_iterations(1),ep_iterations(1){}
    virtual void reset();
    virtual Solution* random(Solution* currentSolution);
    virtual std::pair<int,int> lastMove(){return std::pair<int,int>(end_position,start_position);}; 
    virtual NeighborhoodIterator begin(Solution *base);
    virtual ~MdvrpExchangeNeighborhood() {}
    
};

class MdvrpExchange2Neighborhood: public emili::mdvrp::NeighborhoodMdvrp{
protected:
    int start_position;
    int start_position2;
    int end_position;
    int end_position2;
    int sp_iterations;
    int ep_iterations;
    virtual Solution* computeStep(Solution* value);
    virtual void reverseLastMove(Solution *step);
public:
    MdvrpExchange2Neighborhood(Mdvrp& problem):NeighborhoodMdvrp(problem),start_position(0),end_position(0),sp_iterations(1),ep_iterations(1){}
    virtual void reset();
    virtual Solution* random(Solution* currentSolution);
    virtual std::pair<int,int> lastMove(){return std::pair<int,int>(end_position,start_position);}; 
    virtual NeighborhoodIterator begin(Solution *base);
    virtual ~MdvrpExchange2Neighborhood() {}
    
};

class MdvrpExchange21Neighborhood: public emili::mdvrp::NeighborhoodMdvrp{
protected:
    int start_position;
    int start_position2;
    int end_position;
    int sp_iterations;
    int ep_iterations;
    virtual Solution* computeStep(Solution* value);
    virtual void reverseLastMove(Solution *step);
public:
    MdvrpExchange21Neighborhood(Mdvrp& problem):NeighborhoodMdvrp(problem),start_position(0),end_position(0),sp_iterations(1),ep_iterations(1){}
    virtual void reset();
    virtual Solution* random(Solution* currentSolution);
    virtual std::pair<int,int> lastMove(){return std::pair<int,int>(end_position,start_position);}; 
    virtual NeighborhoodIterator begin(Solution *base);
    virtual ~MdvrpExchange21Neighborhood() {}
    
};

class Mdvrp2optNeighborhood: public emili::mdvrp::NeighborhoodMdvrp{
protected:
    int start_position;
    int start_position2;
    int end_position;
    int end_position2;
    int sp_iterations;
    int ep_iterations;
    bool diff_route;
    virtual Solution* computeStep(Solution* value);
    virtual void reverseLastMove(Solution *step);
public:
    Mdvrp2optNeighborhood(Mdvrp& problem):NeighborhoodMdvrp(problem),start_position(0),end_position(0),sp_iterations(1),ep_iterations(1){}
    virtual void reset();
    virtual Solution* random(Solution* currentSolution);
    virtual std::pair<int,int> lastMove(){return std::pair<int,int>(end_position2,start_position2);}; 
    virtual NeighborhoodIterator begin(Solution *base);
    bool different_depot(std::vector<int>& newsol, int best_i, int best_j, int best_i2, int best_j2);
    virtual ~Mdvrp2optNeighborhood() {}
    
};



class Mdvrp2optstarNeighborhood: public emili::mdvrp::NeighborhoodMdvrp{
protected:
    int start_position;
    int start_position2;
    int end_position;
    int end_position2;
    int sp_iterations;
    int ep_iterations;
    bool diff_route;
    int diff;
    int cases; 
    bool diff_depot;
    std::vector<int> route1;
    std::vector<int> route2;
    virtual Solution* computeStep(Solution* value);
    virtual void reverseLastMove(Solution *step);
public:
    Mdvrp2optstarNeighborhood(Mdvrp& problem):NeighborhoodMdvrp(problem),start_position(0),end_position(0),sp_iterations(1),ep_iterations(1),route1(),route2(),diff_route(false),diff(){}
    virtual void reset();
    virtual Solution* random(Solution* currentSolution);
    virtual std::pair<int,int> lastMove(){return std::pair<int,int>(end_position2,start_position2);}; 
    virtual NeighborhoodIterator begin(Solution *base);
    bool different_route(std::vector<int>& newsol, int best_i, int best_j, int best_i2, int best_j2);
    virtual ~Mdvrp2optstarNeighborhood() {}
    
};



// this is just random move, not used right now
/** @brief The Perturbation class
* The pertubation phase of the ils.
*/
class PerturbationRandomMove: public emili::Perturbation
{
    emili::mdvrp::Mdvrp& prob;
  public:
    PerturbationRandomMove(emili::mdvrp::Mdvrp& problem):prob(problem) {}
    /**
     * @brief perturb
     * The method returns a perturbed solution generated starting from solution
     * @param solution
     * The solution to perturb
     * @return
     * perturbed solution
     */
    virtual Solution* perturb(Solution* solution);
    virtual bool checkConstraints(std::vector<int>& sol);

    virtual ~PerturbationRandomMove() { }
};

class RestartPerturbation: public emili::Perturbation
{
protected:
    int num_of_solutions;
    bool locser;
    emili::InitialSolution* initial;
    emili::LocalSearch* ls;
public:
    RestartPerturbation(int np, emili::InitialSolution* init, emili::LocalSearch* ll):num_of_solutions(np),initial(init),ls(ll),locser(true) {}
    RestartPerturbation(int np, emili::InitialSolution* init):num_of_solutions(np),initial(init),ls(nullptr),locser(false) {}

    emili::Solution* perturb(Solution *solution);
    ~RestartPerturbation();
};


class Iteratermination: public emili::Termination{
protected:
    int numberOfSteps;
    int currentStep;
public:
    Iteratermination(int number_of_steps):numberOfSteps(number_of_steps),currentStep(0) { }
    virtual bool terminate(Solution* currentSolution, Solution* newSolution);
    void reset();

};

class MdvrpTerminationIterations: public emili::Termination
{
protected:
    int iterations;
    int maxIterations;
public:
    MdvrpTerminationIterations(int max_badIterations):maxIterations(max_badIterations),iterations(0) { }
    virtual bool terminate(Solution* currentSolution, Solution* newSolution);
    void reset();
};



class MdvrpTestAcceptance: public emili::Acceptance
{
protected:
    Mdvrp& mdvrp;
    int percentage;
public:
    MdvrpTestAcceptance(Mdvrp& problem_instance):mdvrp(problem_instance),percentage(70) { }
    MdvrpTestAcceptance(Mdvrp& problem_instance,int perc):mdvrp(problem_instance),percentage(perc) { }
    virtual Solution* accept(Solution* candidate1, Solution* candidate2);
};


// tabu 
class MdvrpTabuValueMemory: public emili::TabuMemory
{
    std::vector < double> tabuVector;
    int tt_index;
public:
    MdvrpTabuValueMemory(int tabuTenure):emili::TabuMemory(tabuTenure),tabuVector(),tt_index(0) { }
    MdvrpTabuValueMemory():emili::TabuMemory(),tabuVector(),tt_index(0) { }
    /**
     * this method should return true if the solution is not tabu and false in the other case,
     */
    virtual bool tabu_check(Solution *solution);
    virtual void forbid(Solution* solution);
    virtual void reset();

};


class MdvrpMovesMemory: public emili::TabuMemory
{
protected:
    std::vector < std::pair < int,int > > tabuVector;
    emili::mdvrp::NeighborhoodMdvrp* neigh;
    int tt_index;
    std::pair <int,int> lastMove;
    virtual bool tabu_check(std::pair< int,int > value);
  public:
      MdvrpMovesMemory(int tabtenure,emili::mdvrp::NeighborhoodMdvrp* n):emili::TabuMemory(tabtenure),tt_index(0),neigh(n),lastMove(0,0) { }
      MdvrpMovesMemory(emili::mdvrp::NeighborhoodMdvrp* n):emili::TabuMemory(),tt_index(0),neigh(n),lastMove(0,0) { }
      MdvrpMovesMemory(int tabtenure):emili::TabuMemory(tabtenure),tt_index(0),neigh(nullptr),lastMove(0,0) { }
      /**
       * this method should return true if the solution is not tabu and false in the other case,
       */
      virtual bool tabu_check(Solution *solution);
      virtual void forbid(Solution *solution);
      virtual void registerMove(emili::Solution* base,emili::Solution* solution);
      virtual void reset();
      virtual void setNeighborhood(Neighborhood *neighborhood) {neigh = (emili::mdvrp::NeighborhoodMdvrp*)neighborhood;}
};


class MdvrpFullSolutionMemory: public emili::TabuMemory
{
  std::vector < std::vector < int > > tabuVector;

  int tt_index;
public:
    MdvrpFullSolutionMemory(int tabtenure):emili::TabuMemory(tabtenure),tt_index(0) { }
    MdvrpFullSolutionMemory():emili::TabuMemory(),tt_index(0) { }
    /**
     * this method should return true if the solution is not tabu and false in the other case,
     */
    virtual bool tabu_check(Solution *solution);
    virtual void forbid(Solution *solution);
    virtual void reset();
};

class MdvrpMovesMemory2: public MdvrpMovesMemory
{
  public:
      MdvrpMovesMemory2(int tabtenure,emili::mdvrp::NeighborhoodMdvrp* n):MdvrpMovesMemory(tabtenure,n) { }
      MdvrpMovesMemory2(emili::mdvrp::NeighborhoodMdvrp* n):MdvrpMovesMemory(n) { }
        MdvrpMovesMemory2(int tabtenure):MdvrpMovesMemory(tabtenure) { }
      /**
       * this method should return true if the solution is not tabu and false in the other case,
       */
      virtual void registerMove(emili::Solution* base,emili::Solution* solution);
};


}
}

#endif // EMILIBASE_H