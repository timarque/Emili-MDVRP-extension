//
//  Created by Federico Pagnozzi on 12/12/17.
//  Copyright (c) 2014 Federico Pagnozzi. All rights reserved.
//  This file is distributed under the BSD 2-Clause License. See LICENSE.TXT
//  for details.

#include "mdvrp.h"
#include <iostream> 
#include <string.h>
#include <algorithm> 

void notyet()
{
    std::cout << "Not implemented yet \n";
    //std::exit(-5);
}
      int emili::mdvrp::Mdvrp::getnbVehicles(){
        return instance.getnbVehicles();
      };
      int emili::mdvrp::Mdvrp::getnbCustomers(){
        return instance.getnbCustomers();
      };
      int emili::mdvrp::Mdvrp::getnbDepots(){
        return instance.getnbDepots();
      };
      int emili::mdvrp::Mdvrp::getmaxDuration(){
        return instance.getmaxDuration();
      };
      int emili::mdvrp::Mdvrp::getmaxCapacity(){
        return instance.getmaxCapacity();
      };

      std::vector<int>& emili::mdvrp::Mdvrp::getcustomers(){
        return instance.getcustomers();
      };
      std::vector<int>& emili::mdvrp::Mdvrp::getdepots(){
        return instance.getdepots();
      };
      std::vector<std::vector<double>>& emili::mdvrp::Mdvrp::getcoordinates(){
        return instance.getcoordinates();
      };
      std::vector<int>& emili::mdvrp::Mdvrp::getserviceDuration(){
        return instance.getserviceDuration();
      };
      std::vector<int>& emili::mdvrp::Mdvrp::getdemand(){
        return instance.getdemand();
      };
      std::vector<std::vector<double>>& emili::mdvrp::Mdvrp::getdistanceMatrix(){
        return instance.getDistanceMatrix();
      };
      std::vector<std::vector<int>>& emili::mdvrp::Mdvrp::getnlist(){
        return instance.getnlists();
      }

    double emili::mdvrp::Mdvrp::getInit_sol_cost(){
      return this->init_sol_cost;
    }
    void emili::mdvrp::Mdvrp::setInit_sol_cost(double cost){
      this->init_sol_cost = cost;
    }

      double emili::mdvrp::Mdvrp::calcObjectiveFunctionValue(Solution& solution) // Check if this is correct  and change testing variable name
      {
        emili::mdvrp::SolutionMdvrp& s = dynamic_cast<emili::mdvrp::SolutionMdvrp&> (solution);
        return computeObjectiveFunction(s.get_sol());
        
      }

      double emili::mdvrp::Mdvrp::computeObjectiveFunction(std::vector<int>& sol){
        std::vector<std::vector<double>>& distancematrix = instance.getDistanceMatrix();
        std::vector<int>& depots = instance.getdepots();
        std::vector<double> route_costs;
        double route_cost = 0.0;
        bool end_depot = false;
        int nb_cust = instance.getnbCustomers();
        for (int i = 0; i < sol.size(); i++){
          if (sol[i] > nb_cust){
            if (!end_depot){
              end_depot = true;
              route_cost += distancematrix[sol[i] - 1][sol[i+1] - 1];
            }else{
              end_depot = false;
              route_costs.push_back(route_cost);
              route_cost = 0.0;
            }
          }else{
            route_cost += distancematrix[sol[i] - 1][sol[i+1] - 1];
          }
        }
        double total = 0;
        for (int z = 0; z < route_costs.size(); z++){
          total += route_costs[z];
        }
        
        return total;
      }
 
      double emili::mdvrp::Mdvrp::evaluateSolution(Solution& solution) // should just be the lower the distance the better the sol I guess
      {
        emili::mdvrp::SolutionMdvrp& s = dynamic_cast<emili::mdvrp::SolutionMdvrp&> (solution);
        double p = computeObjectiveFunction(s.get_sol());
        solution.setSolutionValue(p);
        return p;
      }
 
      MdvrpInstance& emili::mdvrp::Mdvrp::getInstance(){
        return instance;
      }

  
      const void* emili::mdvrp::SolutionMdvrp::getRawData()const
      {
        return &sol;
      }
 
      void emili::mdvrp::SolutionMdvrp::setRawData(const void* data)
      {
        std::vector<int>* data_vector = (std::vector<int>*) data;

        this->sol = *data_vector;
 
    }


    

    // bool emili::mdvrp::SolutionMdvrp::isFeasible(){
    //   // capacity and time constraints check
    //   int route_cap = 0, service_time = 0;
    //   int current_depot = 0;
    //   bool observed_depot = false;
    //   bool correct = true;
    //   for (int i = 0; i < sol.size(); i++){
    //     if (sol[i] >= demands.size()){
    //       if (observed_depot){
    //         observed_depot = false;
    //         if (route_cap > max_cap || service_time > max_servduration){
    //           correct = false;
    //           break; // maybe change this break
    //         }else{
    //           route_cap = 0;
    //           service_time = 0;
    //         }
    //       }else{
    //         current_depot = sol[i];
    //         observed_depot = true;
    //       }
    //     }else{
    //       route_cap += demands[sol[i] - 1];
    //       service_time += times[sol[i] - 1];
    //     }
    //   }

    //   return correct;
  
    // }
 
      std::string emili::mdvrp::SolutionMdvrp::getSolutionRepresentation() // REVIEW THIS 
      {

            // for (int t = 0; t < sol.size(); t++){
            //   std::cout << sol[t] << " ";
            // }
            // std::cout << std::endl;
        std::string solution ="{ " + std::to_string(sol[0]);
        int depot = sol[0]; 
        for (int i = 1 ; i < sol.size(); i++){
          if (sol[i] == depot && i < sol.size() - 1){
            solution += " " + std::to_string(sol[i]) + " } { "  + std::to_string(sol[i+1]);
            i++;
            depot = sol[i];
          }else if (i == sol.size() - 1 ){
              solution +=  " " + std::to_string(sol[i]) + " }";
          }else{
            solution += " " + std::to_string(sol[i]);
          }
        }
        // std::cout << solution << std::endl;
        return solution;  
    }
 
      emili::Solution* emili::mdvrp::SolutionMdvrp::clone()
    {
        return new emili::mdvrp::SolutionMdvrp(this->solution_value,this->sol); 
    }
 
    bool emili::mdvrp::SolutionMdvrp::operator==(Solution& a)
{
    bool ret = this->solution_value == a.getSolutionValue();
    if(ret)
    {
        emili::mdvrp::SolutionMdvrp* ap = (emili::mdvrp::SolutionMdvrp*) &a;
        std::vector<int>& ap_jobs = ap->get_sol();
        for(int i = 1; i < sol.size(); i++)
        {
            if(sol[i] != ap_jobs[i])
            {
                return false;
            }
        }
    }
    return ret;
}
 
      emili::Solution* emili::mdvrp::InitialSolutionMdvrp::generateSolution()
    {
      return generate();
    }
 
 
      emili::Solution* emili::mdvrp::InitialSolutionMdvrp::generateEmptySolution() 
    {
        std::vector< int > empty;
        emili::mdvrp::SolutionMdvrp*  em =  new emili::mdvrp::SolutionMdvrp(empty);
        em->setSolutionValue(std::numeric_limits<double>::max());
        return em;
    }

    // this is random initial solution
    emili::Solution* emili::mdvrp::MdvrpRandomInitialSolution::generate() 
    {
    std::vector<int> solution; 
    const std::vector<int>& depots = pis.getdepots();
    solution.push_back(depots[0]);
    std::vector<int>& use = pis.getcustomers(); 
    bool done = false;
    int cap = 0, routeduration = 0;
    int counter = 0;
    bool skip = false;
    const std::vector<int>& demand = pis.getdemand();
    const int max_c = pis.getmaxCapacity();
    const int max_d = pis.getmaxDuration();
    const std::vector<int>& durations = pis.getserviceDuration();
    const std::vector<std::vector<double>>& distancemat = pis.getdistanceMatrix();
    while (!done){
        int v1 = rand() % use.size();
        cap += demand[use[v1] - 1];
        routeduration += durations[use[v1] - 1] + distancemat[use[v1] - 1][solution[solution.size() - 1]]; 
        if (max_d > 0){
          if (routeduration > max_d){
            solution.push_back(depots[counter]);
            if (counter == depots.size() - 1){
                counter = 0;
                solution.push_back(depots[counter]);
            }else{
                counter++;
                solution.push_back(depots[counter]);
            }
            routeduration = durations[use[v1] - 1] + distancemat[use[v1] - 1][solution[solution.size() - 1]]; 

          }
        }
        if (cap > max_c){
          solution.push_back(depots[counter]);
          if (counter == pis.getnbDepots()-1){
            counter = 0;
              solution.push_back(depots[counter]);
            }else{
              counter++;
              solution.push_back(depots[counter]);
            }
          cap = demand[use[v1] - 1];
        }
        
        solution.push_back(use[v1]);
        use.erase(use.begin() + v1);
        if (use.size() == 0){
            done = true;
            solution.push_back(depots[counter]);
        }        


    }
    std::vector<std::vector<int>> reorder(pis.getnbDepots()); // reordering as it creates a solution of different order than the normal one 
    int last_depot_seen = solution[0];
    for (int y = 0; y < solution.size(); y++){
      if (solution[y] > pis.getnbCustomers()){
        last_depot_seen = solution[y];
      }
      reorder[last_depot_seen - pis.getnbCustomers() - 1].push_back(solution[y]); 
    }
    std::vector<int> final_sol;
    for (int x = 0; x < reorder.size(); x++){
      for (int z = 0; z < reorder[x].size(); z++){
        final_sol.push_back(reorder[x][z]);
      }
    }
    double value = pis.computeObjectiveFunction(final_sol);
    pis.setInit_sol_cost(value);
    std::cout << value << std::endl;
    SolutionMdvrp* s = new SolutionMdvrp(value, final_sol);
    return s;
    }



    // i dont know if this is correct 
    emili::Solution* emili::mdvrp::MdvrpCWInitialSolution::generate(){
      
    std::vector<int> solution;
    std::vector<std::vector<int>> depotforcust(pis.getnbDepots()); // vector[0] will contain vector of customers who are clostest to depot 1(0) etc
    const std::vector<std::vector<double>>& distanceMat = pis.getdistanceMatrix(); 
    const std::vector<int>& customers = pis.getcustomers();
    const std::vector<int>& demand = pis.getdemand();
    const int nb_customers = pis.getnbCustomers();
    const int nb_depots = pis.getnbDepots();
    int total = nb_customers + nb_depots;
    int closest_depot;
    double min_distance;
    const int maxcap = pis.getmaxCapacity();
    const int max_time = pis.getmaxDuration();
    const std::vector<int>& service_times = pis.getserviceDuration();
    // assign customers to nearest depot
    for (int i = 0; i < nb_customers; i ++){
      closest_depot = 0;
      min_distance = distanceMat[i][nb_customers];
      for (int j = nb_customers + 1; j < total; j ++){
        if (distanceMat[i][j] < min_distance){
          closest_depot = j - nb_customers;
          min_distance = distanceMat[i][j];
        }
      }
      depotforcust[closest_depot].push_back(customers[i]);
    }
    double savings;
    const std::vector<int>& depots = pis.getdepots();
    std::vector<std::vector<int>> final_routes;
    for (int z = 0; z < depotforcust.size(); z ++){
      std::vector<std::pair<double, std::pair<int, int>>> savingsMatrix;
      for (int r = 0; r < depotforcust[z].size(); r ++){
        for (int t = r + 1; t < depotforcust[z].size(); t++){
          savings = distanceMat[nb_customers + z][depotforcust[z][r]] 
          + distanceMat[nb_customers + z][depotforcust[z][t]] - distanceMat[depotforcust[z][r]][depotforcust[z][t]];
          savingsMatrix.push_back(std::make_pair(savings, std::make_pair(depotforcust[z][r], depotforcust[z][t])));
        }
      }
    std::sort(savingsMatrix.rbegin(), savingsMatrix.rend());
    std::vector<int> assigned;
    std::vector<int> usable;
    std::vector<std::vector<int>> routes;
    std::vector<int> loads;
    std::vector<double> durations;
    bool cust1_found, cust2_found;
    int index1 , index2;
    int routeindex1, routeindex2;
    int demands;
    double times = 0.0;
    for (const auto& savingPair : savingsMatrix) {
        if (assigned.size() != depotforcust[z].size()){
          int customer1 = savingPair.second.first;
          int customer2 = savingPair.second.second;
          cust1_found = false;
          cust2_found = false;
          for (int y = 0; y < routes.size(); y ++){
            if (routes.size() != 0){
            for (int u = 0; u < routes[y].size(); u++){
              if (customer1 == routes[y][u]){
                cust1_found = true;
                index1 = u;
                routeindex1 = y;
              }else if (customer2 == routes[y][u]){
                cust2_found = true;
                index2 = u;
                routeindex2 = y;
              }
            }
          }
        }
                if (!cust1_found && !cust2_found){
          bool timed = false;
          bool cont = false;
          demands = demand[customer1 - 1] + demand[customer2 - 1];
          if (max_time != 0){
            timed = true;
            times = service_times[customer1 - 1] + service_times[customer2 - 1] 
            + distanceMat[customer1 - 1][customer2 - 1] + distanceMat[customer1 - 1][nb_customers + z] +  distanceMat[customer2 - 1][nb_customers + z]; // travel times
            if(times < max_time){
              cont = true;
            }

          }
          if (demands < maxcap){
            if (timed && cont ){
              std::vector<int> route;
              route.push_back(depots[z]);
              route.push_back(customer1);
              route.push_back(customer2);
              assigned.push_back(customer1);
              assigned.push_back(customer2);
              routes.push_back(route);
              loads.push_back(demands);
              durations.push_back(times);
            }else if (!timed){
              std::vector<int> route;
              route.push_back(depots[z]);
              route.push_back(customer1);
              route.push_back(customer2);
              assigned.push_back(customer1);
              assigned.push_back(customer2);
              routes.push_back(route);
              loads.push_back(demands);
            }
          }
        }else if (cust1_found && !cust2_found){
          
          bool timed = false;
          bool cont = false;
          if (max_time != 0){
            timed = true;

            times = durations[routeindex1] - distanceMat[customer1 - 1][nb_customers + z] 
            + service_times[customer2 - 1] + distanceMat[customer2 - 1][nb_customers + z] + distanceMat[customer1 - 1][customer2 - 1];

            if (times < max_time){
              cont = true;
            }
          }
          if (index1 == routes[routeindex1].size() -1){
            if(timed && cont){
            demands = demand[customer2 - 1];
            int total_demand = demands + loads[routeindex1];
            if (total_demand < maxcap){
              routes[routeindex1].push_back(customer2);
              loads[routeindex1] = total_demand;
              durations[routeindex1] = times;
            }
          }else if ( !timed ){
              demands = demand[customer2 - 1];
              int total_demand = demands + loads[routeindex1];
              if (total_demand < maxcap){
                routes[routeindex1].push_back(customer2);
                loads[routeindex1] = total_demand;
              }
          }
          }else if (index1 == 1){
            if(timed && cont){
            demands = demand[customer2 - 1];
            int total_demand = demands + loads[routeindex1];
            if (total_demand < maxcap){
              routes[routeindex1].insert(routes[routeindex1].begin() + 1, customer2);
              loads[routeindex1] = total_demand;
              durations[routeindex1] = times;
            }
          }else if ( !timed ){
              demands = demand[customer2 - 1];
              int total_demand = demands + loads[routeindex1];
              if (total_demand < maxcap){
                routes[routeindex1].insert(routes[routeindex1].begin() + 1, customer2);
                loads[routeindex1] = total_demand;
              }
          }
          }
        }else if (!cust1_found && cust2_found){
          bool timed = false;
          bool cont = false;
          if (max_time != 0){
            timed = true;
            times = durations[routeindex2] - distanceMat[nb_customers + z][customer2 - 1]
            + service_times[customer1 - 1] + distanceMat[nb_customers + z][customer1 - 1] + distanceMat[customer1-1][customer2 - 1];
            if (times < max_time){
              cont = true;
            }
          }
          if (index2 == routes[routeindex2].size() -1){
            if(timed && cont){
            demands = demand[customer1 - 1];
            int total_demand = demands + loads[routeindex2];
            if (total_demand < maxcap){
              routes[routeindex2].push_back(customer1);
              loads[routeindex2] = total_demand;
              durations[routeindex2] = times;
            }
          }else if ( !timed ){
              demands = demand[customer1 - 1];
              int total_demand = demands + loads[routeindex2];
              if (total_demand < maxcap){
                routes[routeindex2].push_back(customer1);
                loads[routeindex2] = total_demand;
              }
          }
          }else if (index2 == 1){
            if(timed && cont){
            demands = demand[customer1 - 1];
            int total_demand = demands + loads[routeindex2];
            if (total_demand < maxcap){
              routes[routeindex2].insert(routes[routeindex2].begin() + 1, customer1);
              loads[routeindex2] = total_demand;
              durations[routeindex2] = times;
            }
          }else if ( !timed ){
              demands = demand[customer1 - 1];
              int total_demand = demands + loads[routeindex2];
              if (total_demand < maxcap){
                routes[routeindex2].insert(routes[routeindex2].begin() + 1, customer1);
                loads[routeindex2] = total_demand;
              }
          }
          }
        }
      }
    }
    for (int x = 0; x < depotforcust[z].size(); x++){
      bool ass = false;
      for (int p = 0; p < routes.size(); p++){
        if (std::find(routes[p].begin(), routes[p].end(), depotforcust[z][x]) != routes[p].end()){
          ass = true;
        }
      }
      if (!ass){
        std::vector<int> route;
        route.push_back(depots[z]);
        route.push_back(depotforcust[z][x]);
        routes.push_back(route);
        bool timed = false;
          bool cont = false;
          if (max_time != 0){
            timed = true;
            times = service_times[depotforcust[z][x] - 1] + distanceMat[depotforcust[z][x] - 1][nb_customers + z] + distanceMat[depotforcust[z][x] - 1][nb_customers + z];
            if (times < max_time){
              cont = true;
            }
          }
        demands = demand[depotforcust[z][x] - 1];
        loads.push_back(demands);
        if (timed){
          durations.push_back(times);
        }
      }
    } 
    for (int p = 0; p < routes.size(); p++){
      routes[p].push_back(depots[z]);
      final_routes.push_back(routes[p]);
    }
    }

    for (int w = 0; w < final_routes.size(); w++){
      for (int m = 0; m < final_routes[w].size(); m ++){
        solution.push_back(final_routes[w][m]);
      }
    }

    double value = pis.computeObjectiveFunction(solution);
    pis.setInit_sol_cost(value);
    std::cout << value << std::endl;
    SolutionMdvrp* s = new SolutionMdvrp(value, solution);
    return s;
    }
 
   
// bool emili::mdvrp::NeighborhoodMdvrp::checkConstraints(std::vector<int>& sol, int yes, int no){
//       // capacity and time constraints check
//       int route_cap = 0;
//       double service_time = 0.0;
//       int current_depot = 0;
//       bool observed_depot = false;
//       bool correct = true;
//       const std::vector<std::vector<double>>& distancemat = pis.getdistanceMatrix();
//       const std::vector<int> demands = pis.getdemand();
//       const int max_time = pis.getmaxDuration();
//       const int customers = pis.getnbCustomers();
//       const int max_cap = pis.getmaxCapacity();
//       while (sol[yes] <= customers){
//         yes --;
//       }
//       while (sol[yes] > customers && sol[yes+1] > customers){
//         yes ++;
//       }
//       while (sol[no] <= customers){
//         no ++;
//       }
//       no++;
//       no = std::min(no, static_cast<int>(sol.size()));
//       if (max_time > 0){
//         const std::vector<int>& durations = pis.getserviceDuration();
//         for (int i = yes; i < no; i++){
//           if (sol[i] > customers){
//             if (observed_depot){
//               observed_depot = false;
//               service_time += distancemat[sol[i - 1] - 1][sol[i] - 1];
//               if (route_cap > max_cap || service_time > max_time){
//                 correct = false;
//                 break; 
//               }else{
//                 route_cap = 0;
//                 service_time = 0;
//               }
//             }else{
//               current_depot = sol[i];
//               observed_depot = true;
//             }
//           }else{
//             route_cap += demands[sol[i] - 1];
//             service_time += distancemat[sol[i - 1] - 1][sol[i] - 1]; 
//             service_time += durations[sol[i] - 1];
//           }
//         }
//       }else{
//         for (int i = yes; i < no; i++){
//           if (sol[i] > customers){
//             if (observed_depot){
//               observed_depot = false;
//               if (route_cap > max_cap){
//                 correct = false;
//                 break; 
//               }else{
//                 route_cap = 0;
//                 service_time = 0;
//               }
//             }else{
//               current_depot = sol[i];
//               observed_depot = true;
//             }
//           }else{
//             route_cap += demands[sol[i] - 1];
//           }
//         }
//       }
//       return correct;
//     }


bool emili::mdvrp::NeighborhoodMdvrp::checkConstraints(std::vector<int>& sol){
      // Store the frequently accessed values in local variables
    const std::vector<std::vector<double>>& distancemat = pis.getdistanceMatrix();
    const std::vector<int>& demands = pis.getdemand();
    const int max_time = pis.getmaxDuration();
    const int max_capacity = pis.getmaxCapacity();
    int route_cap = 0;
    double service_time = 0.0;
    int current_depot = 0;
    bool observed_depot = false;
    bool correct = true;

    if (max_time > 0) {
        const std::vector<int>& durations = pis.getserviceDuration();
        for (int i = 0; i < sol.size(); i++) {
            if (sol[i] > nb_cust) {
                if (observed_depot) {
                    observed_depot = false;
                    service_time += distancemat[sol[i - 1] - 1][sol[i] - 1];
                    if (route_cap > max_capacity || service_time > max_time) {
                        correct = false;
                        break;
                    } else {
                        route_cap = 0;
                        service_time = 0;
                    }
                } else {
                    current_depot = sol[i];
                    observed_depot = true;
                }
            } else {
                route_cap += demands[sol[i] - 1];
                service_time += distancemat[sol[i - 1] - 1][sol[i] - 1];
                service_time += durations[sol[i] - 1];
            }
        }
    } else {
        for (int i = 0; i < sol.size(); i++) {
            if (sol[i] > nb_cust) {
                if (observed_depot) {
                    observed_depot = false;
                    if (route_cap > max_capacity) {
                        correct = false;
                        break;
                    } else {
                        route_cap = 0;
                        service_time = 0;
                    }
                } else {
                    current_depot = sol[i];
                    observed_depot = true;
                }
            } else {
                route_cap += demands[sol[i] - 1];
            }
        }
    }

    return correct;
    }


// std::vector<std::vector<int>> emili::mdvrp::NeighborhoodMdvrp::calculate_granular(emili::Solution* value){
//     std::vector < int >& newsol = ((emili::mdvrp::SolutionMdvrp*)value)->get_sol();
//     routes = 0;
//     int last_depot = newsol[0];
//     bool found_route = false;
//     int depot = newsol[0];
//     bool first_route = false; 
//     for (int i = 1 ; i < newsol.size(); i++){
//       if (newsol[i] < pis.getnbCustomers()){
//         first_route = true;
//       }
//       if (newsol[i] == depot && i < newsol.size() - 1 && first_route){
//         while (newsol[i + 1] > pis.getnbCustomers()){
//           i++;
//         }
//         depot = newsol[i];
//         routes +=1;
//       }else if (i == newsol.size() - 1 ){
//             routes += 1;
//       }
//     }
//     double z = pis.getInit_sol_cost();
//     double threshold = z / (routes + pis.getnbCustomers());
//     std::vector<int> customers = pis.getcustomers();
//     std::vector<std::vector<double>> distancemat = pis.getdistanceMatrix();
//     std::vector<std::vector<int>> arcs;
//     for (int u = 0; u < distancemat.size(); u++){
//       std::vector<int> custarcs;
//       for (int t = 0; t < distancemat[u].size(); t++){
//         if (distancemat[u][t] < threshold){
//           custarcs.push_back(t+1);
//         }
//       }
//       arcs.push_back(custarcs);
//     }
//     // for (int z = 0; z < arcs.size(); z++){
//     //   std::cout << z << " : ";
//     //   for (int r = 0; r < arcs[z].size(); r++){
//     //     std::cout << " " << arcs[z][r];
//     //   }
//     //   std::cout << std::endl;
//     // }
//     return arcs;

  //}


    emili::Solution* emili::mdvrp::NeighborhoodMdvrp::step(emili::Solution *currentSolution)
{
    return computeStep(currentSolution);
}


  int emili::mdvrp::NeighborhoodMdvrp::size()
{
    return (pis.getnbCustomers()+(pis.getnbDepots()));
}
 

    emili::Solution* emili::mdvrp::MdvrpMoveNeighborhood::computeStep(emili::Solution* value)
    {
      emili::iteration_increment();
      std::vector < int >& newsol = ((emili::mdvrp::SolutionMdvrp*)value)->get_sol();
      int size = newsol.size();
      if (sp_iterations >= size - 1){
        return nullptr;
      }else{
        end_position = ((end_position)%size)+1;
        if(ep_iterations < size){
            ep_iterations++;

        }
        else
        {
            sp_iterations++;
            ep_iterations = 1;
            start_position = ((start_position)%size)+1;
            end_position = ep_iterations;
            
        }

        // bool ah = false;
        // while (end_position < newsol.size() - 1 && start_position < newsol.size() - 1 && !ah){
        //   // std::cout << start_position << " " << end_position << " " << newsol.size() << std::endl;
        //   // std::cout << newsol[start_position] << " - " << newsol[end_position] << std::endl;
        //   // std::cout << granular[start_position - 1].size() << std::endl;

        //   auto it = std::find(granular[newsol[start_position] - 1].begin(), granular[newsol[start_position]- 1].end(), newsol[end_position] - 1);
        //   if (it == granular[newsol[start_position] - 1].end()){
        //     end_position +=1;
        //     ep_iterations++;
        //   }else{
        //     ah = true;
        //   }
        // }

        while (newsol[start_position] > nb_cust){
          start_position += 1;
          sp_iterations ++;
          if (start_position >= size){
            start_position = 1;
            end_position = 1;
            sp_iterations = size - 1;
          }
        }
        int route_depot;
        bool possible_depot = false;
        bool brake = false;
        while (!possible_depot && !brake){
          while (newsol[end_position] > nb_cust){
            end_position += 1;
            ep_iterations ++;
            if (end_position >= size - 1){
              end_position = start_position;
              ep_iterations = size;
              brake = true;
            }
          }

          for (int z = end_position; z >= 0; z--){
            if (newsol[z] > nb_cust){
              route_depot = newsol[z];
              break;
            }
          }
          for (int t = 0; t < this->nlist[newsol[start_position] - 1].size() ; t++){
            if (this->nlist[newsol[start_position] - 1][t] == route_depot){
              possible_depot = true;
              break;
            }
          }
          if (!possible_depot && ! brake){
            while (newsol[end_position] <= nb_cust){
              end_position += 1;
              ep_iterations ++;
            }
          }
        }
        // bool doable;
        int sol_i = newsol[start_position];
        newsol.erase(newsol.begin()+start_position);
        newsol.insert(newsol.begin()+end_position,sol_i);
        // if (start_position <= end_position){
        //   doable = checkConstraints(newsol, start_position, end_position); 
        // }else{
        //   doable = checkConstraints(newsol, end_position, start_position);
        // }
        bool doable = checkConstraints(newsol);
        if (doable){
          double new_val = pis.computeObjectiveFunction(newsol);
          value->setSolutionValue(new_val);
        } 
        return value;
        }
    }


      emili::Neighborhood::NeighborhoodIterator emili::mdvrp::MdvrpMoveNeighborhood::begin(emili::Solution* base)
    {
      ep_iterations = 1;
      sp_iterations = 1;
      //this->granular = calculate_granular(base);
      return emili::Neighborhood::NeighborhoodIterator(this,base);
    }
 

      void emili::mdvrp::MdvrpMoveNeighborhood::reset()
      {
          start_position = 1;
          end_position = 1;
      }

    void emili::mdvrp::NeighborhoodMdvrp::reset()
{
    /** No counters to reset*/
}      


      emili::Solution* emili::mdvrp::MdvrpMoveNeighborhood::random(Solution* currentSolution)
      {
      std::vector < int > newsol = (((emili::mdvrp::SolutionMdvrp*)currentSolution)->get_sol());
      int best_i, best_j;
      bool done = false;
      int counter = 0; // counter so that it doesnt stay here infinetly 
      int size = newsol.size();
      while (!done && counter < size / 2){
        best_i = (emili::generateRandomNumber()%size); 
        best_j = (emili::generateRandomNumber()%size);
        while (newsol[best_i] > nb_cust || newsol[best_j] > nb_cust){ // make sure we are not moving a depot 
          best_i = (emili::generateRandomNumber()%size);
          best_j = (emili::generateRandomNumber()%size);
        }
        int sol_i = newsol[best_i]; 
        newsol.erase(newsol.begin()+best_i);
        newsol.insert(newsol.begin()+best_j,sol_i);
        done = checkConstraints(newsol); // seems to be working
        counter ++;
        if (!done){ // reverse move if does not fit constraints
          newsol.erase(newsol.begin() + best_j);
          newsol.insert(newsol.begin() + best_i, sol_i);
        }
      }
      double new_val = pis.computeObjectiveFunction(newsol);
      return new emili::mdvrp::SolutionMdvrp(new_val, newsol);
      }
      


    void emili::mdvrp::MdvrpMoveNeighborhood::reverseLastMove(Solution* step)
    {
      
      std::vector < int >& newsol = ((emili::mdvrp::SolutionMdvrp*)step)->get_sol();
      int sol_i = newsol[end_position];
      newsol.erase(newsol.begin()+end_position);
      newsol.insert(newsol.begin()+start_position,sol_i);

    }


    emili::Solution* emili::mdvrp::MdvrpMove2Neighborhood::computeStep(emili::Solution* value)
    {
      emili::iteration_increment();
      std::vector < int >& newsol = ((emili::mdvrp::SolutionMdvrp*)value)->get_sol();
      int size = newsol.size();
      if (sp_iterations >= size - 2){
        return nullptr;
      }else{
        end_position = ((end_position)%size)+1;
        if(ep_iterations < size){
            ep_iterations++;
        }
        else
        {
            sp_iterations++;
            ep_iterations = 1;
            start_position = ((start_position)%size)+1;
            end_position = ep_iterations;
        }
        start_position2 = start_position + 1;
        while (newsol[start_position] > nb_cust || newsol[start_position2] > nb_cust){ 
          start_position +=1;
          start_position2 +=1;
          sp_iterations += 1;
          if (start_position2 > size - 2 || start_position > size - 3){
            start_position2 = 1;
            start_position = 0;
            end_position = 2;
            sp_iterations = size - 2;
          }
        }
       
        int route_depot;
        bool possible_depot = false;
        bool brake = false;
        while (!possible_depot && !brake){
          while (newsol[end_position] > nb_cust || newsol[end_position + 1] > nb_cust){
            end_position += 1;
            ep_iterations ++;
            if (end_position >= size - 1){
              end_position = 1;
              ep_iterations = size;
              brake = true;
              break;
            }
          }

          for (int z = end_position; z >= 0; z--){
            if (newsol[z] > nb_cust){
              route_depot = newsol[z];
              break;
            }
          }
          for (int t = 0; t < this->nlist[newsol[start_position] - 1].size() ; t++){
            if (this->nlist[newsol[start_position] - 1][t] == route_depot){
              possible_depot = true;
              break;
            }
          }
          if (!possible_depot && ! brake){
            while (newsol[end_position] <= nb_cust){
              end_position += 1;
              ep_iterations ++;
            }
          }
        }
        // bool doable;
        int sol_i = newsol[start_position];
        int sol_i2 = newsol[start_position2];
        real_end_position = end_position;
        newsol.erase(newsol.begin() + start_position2);
        newsol.erase(newsol.begin() + start_position);
        bool increase = false;
        while (real_end_position >= size - 1 || (newsol[real_end_position] > nb_cust + 1)){
          real_end_position -=1 ;
          increase = true;
        }
        newsol.insert(newsol.begin()+real_end_position,sol_i2);
        newsol.insert(newsol.begin()+real_end_position,sol_i);

        
        if (increase ){
           real_end_position += 1;
         }
        // if (start_position <= real_end_position){
        //   doable = checkConstraints(newsol, start_position, real_end_position); 
        // }else{
        //   doable = checkConstraints(newsol, real_end_position, start_position);
        // }
        bool doable = checkConstraints(newsol);
        if (doable){

          double new_value = pis.computeObjectiveFunction(newsol);
          value->setSolutionValue(new_value);
        }
        return value;
      }
        
    }
    

    emili::Neighborhood::NeighborhoodIterator emili::mdvrp::MdvrpMove2Neighborhood::begin(emili::Solution* base)
    {
      ep_iterations = 1;
      sp_iterations = 1;
      return emili::Neighborhood::NeighborhoodIterator(this,base);
    }
 

      void emili::mdvrp::MdvrpMove2Neighborhood::reset()
      {
          start_position = 1;
          start_position2 = 1;
          end_position = 2;
      }

    void emili::mdvrp::MdvrpMove2Neighborhood::reverseLastMove(Solution* step)
    {
    std::vector < int >& newsol = ((emili::mdvrp::SolutionMdvrp*)step)->get_sol();
    int sol_i = newsol[real_end_position];
    int sol_i2 = newsol[real_end_position+1];
    newsol.erase(newsol.begin()+real_end_position+1);
    newsol.erase(newsol.begin()+real_end_position);
    newsol.insert(newsol.begin()+start_position,sol_i2);
    newsol.insert(newsol.begin()+start_position,sol_i);

    }
    

     emili::Solution* emili::mdvrp::MdvrpMove2Neighborhood::random(Solution* currentSolution)
      {
      std::vector < int > newsol = (((emili::mdvrp::SolutionMdvrp*)currentSolution)->get_sol());
      int best_i, best_j;
      int nb_cust = pis.getnbCustomers();
      bool done = false;
      int counter = 0; // counter so that it doesnt stay here infinetly 
      int size = newsol.size();
      while (!done && counter < newsol.size() / 2){
        best_i = (emili::generateRandomNumber()%size); // dont make random, make test all positions
        best_j = (emili::generateRandomNumber()%size);

        while (newsol[best_i] > nb_cust || newsol[best_j] > nb_cust || newsol[best_i + 1] > nb_cust || newsol[best_j + 1] > nb_cust ){ // make sure we are not moving a depot 
          best_i = (emili::generateRandomNumber()%size);
          best_j = (emili::generateRandomNumber()%size);
        }
        int sol_i = newsol[best_i]; 
        int sol_i2 = newsol[best_i + 1]; 
        newsol.erase(newsol.begin()+best_i + 1);
        newsol.erase(newsol.begin()+best_i);
        bool increase = false;
        int best_j2 = best_j >= size - 1 ? size - 1 : best_j;
        // if (best_j > newsol.size() || best_j2 > newsol.size()){
        //           std::cout << newsol.size()<< std::endl;
        // std::cout << best_j << " " << best_j2 << std::endl;
        // }
        
        newsol.insert(newsol.begin()+best_j2,sol_i2);
        newsol.insert(newsol.begin()+best_j2,sol_i);

        done = checkConstraints(newsol); 
        counter ++;
        if (!done){ // reverse move if does not fit constraints
          newsol.erase(newsol.begin() + best_j2);
          newsol.erase(newsol.begin() + best_j2);
          newsol.insert(newsol.begin() + best_i, sol_i2);
          newsol.insert(newsol.begin() + best_i, sol_i);
        }
      }
      double new_val = pis.computeObjectiveFunction(newsol);
      return new emili::mdvrp::SolutionMdvrp(new_val, newsol);
      }




      /*int emili::mdvrp::Neighborhoodmdvrp::size()
      {
          notyet();
          return 0;
      }*/

      emili::Neighborhood::NeighborhoodIterator emili::mdvrp::MdvrpTransposeNeighborhood::begin(emili::Solution *base)
{    
    sp_iterations = 1;
    return emili::Neighborhood::NeighborhoodIterator(this,base);
}


emili::Solution* emili::mdvrp::MdvrpTransposeNeighborhood::computeStep(emili::Solution* value)
{

    emili::iteration_increment();
    std::vector < int >& newsol = ((emili::mdvrp::SolutionMdvrp*)value)->get_sol();
    int size = newsol.size();
    if(sp_iterations >= size)
    {
        return nullptr;
    }
    else
    {
        sp_iterations++;
        start_position = (start_position%size)+1;
        endpos = start_position + 1;
        while (newsol[start_position] >= nb_cust || newsol[endpos] >= nb_cust ){
          start_position ++;
          endpos ++;
          if (endpos >= size){
            endpos = 2;
            start_position = 1;
            sp_iterations ++;
          }
        }
        std::swap(newsol[start_position],newsol[endpos]);
        bool doable = checkConstraints(newsol);
        if (doable){
          double new_value = pis.computeObjectiveFunction(newsol);        
          value->setSolutionValue(new_value);
        }        
        return value;
    }
}

      emili::Solution* emili::mdvrp::MdvrpTransposeNeighborhood::random(Solution* currentSolution)
      {
      std::vector < int > newsol = (((emili::mdvrp::SolutionMdvrp*)currentSolution)->get_sol());
      int best_i;
      bool done = false;
      int counter = 0; // counter so that it doesnt stay here infinetly 
      while (!done && counter < newsol.size()/ 2){
        best_i = (emili::generateRandomNumber()%newsol.size()); 
        while (newsol[best_i] > nb_cust || newsol[best_i+1] > nb_cust){ // make sure we are not moving a depot 
          best_i = (emili::generateRandomNumber()%newsol.size());
        }
        int sol_i = newsol[best_i]; // change to start and end position i guess
        std::swap(newsol[best_i],newsol[best_i + 1]);
        done = checkConstraints(newsol); // seems to be working
        counter ++;
        if (!done){ // reverse move if does not fit constraints
          std::swap(newsol[best_i],newsol[best_i + 1]);
        }
      }
      double new_val = pis.computeObjectiveFunction(newsol);
      return new emili::mdvrp::SolutionMdvrp(new_val, newsol);
      }

void emili::mdvrp::MdvrpTransposeNeighborhood::reverseLastMove(Solution *step)
{
    std::vector < int >& newsol = ((emili::mdvrp::SolutionMdvrp*)step)->get_sol();
    std::swap(newsol[start_position],newsol[endpos]);
}

void emili::mdvrp::MdvrpTransposeNeighborhood::reset()
{
    sp_iterations = 1;
    start_position = 1;
}

emili::Neighborhood::NeighborhoodIterator emili::mdvrp::MdvrpExchangeNeighborhood::begin(emili::Solution *base)
{
    ep_iterations = 1;
    sp_iterations = 1;
    //this->granular = calculate_granular(base);
    return emili::Neighborhood::NeighborhoodIterator(this,base);
}

void emili::mdvrp::MdvrpExchangeNeighborhood::reset()
{    
    start_position = 1;
    end_position = 1;
}

// whiles are very ugly but needed for neighborhood lists to work + feasible ils not working correctly ( almost never finds a feasible answer even though every other)
emili::Solution* emili::mdvrp::MdvrpExchangeNeighborhood::computeStep(emili::Solution* value) 
{
   emili::iteration_increment();
    std::vector < int >& newsol = ((emili::mdvrp::SolutionMdvrp*)value)->get_sol();
    int size = newsol.size();
    if(sp_iterations >= size - 1)
    {    
        return nullptr;
    }else
    {
        if(ep_iterations < size - 1){
            ep_iterations++;
        }
        else
        {
            sp_iterations++;
            ep_iterations = sp_iterations+1;
            start_position = (start_position%size)+1;
            end_position = start_position;
        }
        end_position = (end_position%size)+1;
        // bool ah = false;
        // while (end_position < newsol.size() - 1 && start_position < newsol.size() - 1 && !ah){
        //   // std::cout << start_position << " " << end_position << " " << newsol.size() << std::endl;
        //   // std::cout << newsol[start_position] << " - " << newsol[end_position] << std::endl;
        //   // std::cout << granular[start_position - 1].size() << std::endl;

        //   auto it = std::find(granular[newsol[start_position] - 1].begin(), granular[newsol[start_position]- 1].end(), newsol[end_position] - 1);
        //   if (it == granular[newsol[start_position] - 1].end()){
        //     end_position +=1;
        //     ep_iterations++;
        //   }else{
        //     ah = true;
        //   }
        // }
        while (newsol[start_position] > nb_cust){
          start_position += 1;
          sp_iterations ++;
          if (start_position >= size){
            start_position = 1;
            end_position = 1;
            sp_iterations = size - 1;
          }
        }
       
        int route_depot;
        bool possible_depot = false;
        bool brake = false;
        if (end_position >= size){
              end_position = start_position;
              ep_iterations = size;
              brake = true;
        }
        while (!possible_depot && !brake){
          while (newsol[end_position] > nb_cust){
            end_position += 1;
            ep_iterations ++;
            if (end_position >= size){
              end_position = start_position;
              ep_iterations = size;
              brake = true;
              break;
            }
          }
          for (int z = end_position; z >= 0; z--){
            if (newsol[z] > nb_cust){
              route_depot = newsol[z];
              break;
            }
          }
          for (int t = 0; t < this->nlist[newsol[start_position] - 1].size() ; t++){
            if (this->nlist[newsol[start_position] - 1][t] == route_depot){
              possible_depot = true;
              break;
            }
          }
          if (!possible_depot && ! brake){
            while (newsol[end_position] <= nb_cust){
              end_position += 1;
              ep_iterations ++;
            }
          }
        }
        std::swap(newsol[start_position],newsol[end_position]);
        // bool doable = checkConstraints(newsol, start_position, end_position); 
        bool doable = checkConstraints(newsol);
        if (doable){
          double new_val = pis.computeObjectiveFunction(newsol);
          value->setSolutionValue(new_val);
        }
        return value;
    
  }
}

    void emili::mdvrp::MdvrpExchangeNeighborhood::reverseLastMove(Solution *step)
{
    std::vector < int >& newsol = ((emili::mdvrp::SolutionMdvrp*)step)->get_sol();
    std::swap(newsol[start_position],newsol[end_position]);
}


emili::Solution* emili::mdvrp::MdvrpExchangeNeighborhood::random(Solution *currentSolution)
{

    std::vector < int > newsol(((emili::mdvrp::SolutionMdvrp*)currentSolution)->get_sol());
    int best_i, best_j;
    bool done = false;
    int counter = 0; // counter so that it doesnt stay here infinetly or at least very long, MAYBE REMOVE THIS AT SOME POINT TO CHECK IF MAKES DIFF IN RESULTS
    int size = newsol.size();
    while (!done && counter < size/ 2){
      best_i = (emili::generateRandomNumber()%size); 
      best_j = (emili::generateRandomNumber()%size);
      if (newsol[best_i] <= nb_cust && newsol[best_j] <= nb_cust){ // make sure we are not moving a depot 
        std::swap(newsol[best_i],newsol[best_j]);
        done = checkConstraints(newsol); // seems to be working
        if (!done){
          std::swap(newsol[best_j],newsol[best_i]);
        }
      counter++;
      }
    }
    double value = pis.computeObjectiveFunction(newsol);
    return new emili::mdvrp::SolutionMdvrp(value,newsol);
}



emili::Neighborhood::NeighborhoodIterator emili::mdvrp::MdvrpExchange2Neighborhood::begin(emili::Solution *base)
{
    ep_iterations = 1;
    sp_iterations = 1;
    return emili::Neighborhood::NeighborhoodIterator(this,base);
}

void emili::mdvrp::MdvrpExchange2Neighborhood::reset()
{    
    start_position = 1;
    start_position2 = 2;
    end_position = 1;
    end_position2 = 2;
}



emili::Solution* emili::mdvrp::MdvrpExchange2Neighborhood::computeStep(emili::Solution* value)
{
   emili::iteration_increment();
    std::vector < int >& newsol = ((emili::mdvrp::SolutionMdvrp*)value)->get_sol();
    int size = newsol.size();
    if(sp_iterations >= size)
    {        
        return nullptr;
    }else{
      if(ep_iterations < size - 1){
            ep_iterations++;
        }
        else
        {
            sp_iterations++;
            ep_iterations = sp_iterations+1;
            start_position = (start_position%size)+1;
            end_position = start_position;
        }
        end_position = (end_position%size)+1;
        start_position2 = start_position + 1;
        end_position2 = end_position + 1;
        // if (start_position2 >= newsol.size() || start_position >= newsol.size()){
        //   start_position = newsol.size() - 1;
        //   start_position2 = newsol.size() - 1;
        // }
        while (newsol[start_position] > nb_cust || newsol[start_position2] > nb_cust){
          start_position +=1;
          start_position2 +=1;
          sp_iterations += 1;
          ep_iterations += 1; // this thing about end_positions is making it take longer somehow for bigger instances, pretty much non existant tho
          end_position2 +=1;
          end_position +=1;
          if (start_position >= size){
            reset();
            sp_iterations = size - 1;
          }
        }

        int route_depot;
        bool possible_depot = false;
        bool brake = false;
        while (!possible_depot && !brake){
          if (end_position >= size || end_position2 >= size){
            end_position = size - 1;
            end_position2 = size - 1;
          }
          while (newsol[end_position] > nb_cust || newsol[end_position2] > nb_cust){
            end_position += 1;
            end_position2 +=1;
            ep_iterations ++;
            if (end_position2 >= size){
              end_position = start_position;
              end_position2 = start_position2;
              ep_iterations = size;
              brake = true;
              break;
            }
          }
          for (int z = end_position; z >= 0; z--){
            if (newsol[z] > nb_cust){
              route_depot = newsol[z];
              break;
            }
          }
          for (int t = 0; t < this->nlist[newsol[start_position] - 1].size() ; t++){
            if (this->nlist[newsol[start_position] - 1][t] == route_depot){
              possible_depot = true;
              break;
            }
          }
          if (!possible_depot && ! brake){
            while (newsol[end_position2] <= nb_cust){
              end_position += 1;
              end_position2 +=1;
              ep_iterations ++;
            }
          }
        }


        std::swap(newsol[start_position],newsol[end_position]);
        std::swap(newsol[start_position2],newsol[end_position2]);
        //bool doable = checkConstraints(newsol, start_position, end_position); 
        bool doable = checkConstraints(newsol);
        if (doable){
          double new_val = pis.computeObjectiveFunction(newsol);
          value->setSolutionValue(new_val);
        }
        return value;
        
      
    }
}



    void emili::mdvrp::MdvrpExchange2Neighborhood::reverseLastMove(Solution *step)
{
    std::vector < int >& newsol = ((emili::mdvrp::SolutionMdvrp*)step)->get_sol();
    std::swap(newsol[start_position],newsol[end_position]);
    std::swap(newsol[start_position2],newsol[end_position2]);

}



emili::Solution* emili::mdvrp::MdvrpExchange2Neighborhood::random(Solution *currentSolution)
{

    std::vector < int > newsol(((emili::mdvrp::SolutionMdvrp*)currentSolution)->get_sol());
    int best_i, best_j,best_i2, best_j2;
    bool done = false;
    int counter = 0; // counter so that it doesnt stay here infinetly or at least very long, MAYBE REMOVE THIS AT SOME POINT TO CHECK IF MAKES DIFF IN RESULTS
    int size = newsol.size();
    while (!done && counter < size / 2 ){
      best_i = (emili::generateRandomNumber()%size); 
      best_j = (emili::generateRandomNumber()%size);
      best_i2 = best_i + 1;
      best_j2 = best_j + 1;
       while (newsol[best_i] > nb_cust || newsol[best_j] > nb_cust || newsol[best_i2] > nb_cust || newsol[best_j2] > nb_cust){ // make sure we are not moving a depot 
            best_i = (emili::generateRandomNumber()%size);
            best_j = (emili::generateRandomNumber()%size);
            best_i2 = best_i + 1;
            best_j2 = best_j + 1;
      }
      std::swap(newsol[best_i],newsol[best_j]);
      std::swap(newsol[best_i2], newsol[best_j2]);
      done = checkConstraints(newsol);
      if (!done){
              std::swap(newsol[best_j],newsol[best_i]);
              std::swap(newsol[best_i2], newsol[best_j2]);
      }
      counter++;
    }

    double value = pis.computeObjectiveFunction(newsol);
    return new emili::mdvrp::SolutionMdvrp(value,newsol);
}



emili::Neighborhood::NeighborhoodIterator emili::mdvrp::MdvrpExchange21Neighborhood::begin(emili::Solution *base)
{
    ep_iterations = 1;
    sp_iterations = 1;
    return emili::Neighborhood::NeighborhoodIterator(this,base);
}

void emili::mdvrp::MdvrpExchange21Neighborhood::reset()
{    
    start_position = 1;
    start_position2 = 2;
    end_position = 2;
}


emili::Solution* emili::mdvrp::MdvrpExchange21Neighborhood::computeStep(emili::Solution* value) // not sure this is 100% correct yet
{
   emili::iteration_increment();
    std::vector < int >& newsol = ((emili::mdvrp::SolutionMdvrp*)value)->get_sol();
    int size = newsol.size();
    if(sp_iterations >= size)
    {        
        return nullptr;
    }else{
      if(ep_iterations < size - 1){
            ep_iterations++;
        }
        else
        {
            sp_iterations++;
            ep_iterations = sp_iterations+1;
            start_position = (start_position%size)+1;
            end_position = ep_iterations;
        }
        end_position = (end_position%size)+1;
        start_position2 = start_position + 1;
        // bool ah = false;
        // while (end_position < newsol.size() && !ah){
        //   auto it = std::find(newsol.begin(), newsol.end(), newsol[end_position]);
        //   if (it == newsol.end()){
        //     end_position +=1;
        //     ep_iterations++;
        //   }else{
        //     ah = true;
        //   }
        // }
        while (newsol[start_position] > nb_cust || newsol[start_position2] > nb_cust){
          start_position +=1;
          start_position2 +=1;
          sp_iterations += 1;
          if (start_position2 >= size - 2){
            reset();
            sp_iterations = size - 1;
          }
        }
        int route_depot;
        bool possible_depot = false;
        bool brake = false;
        if (end_position >= size){
          brake = true;
        }
        while (!possible_depot && !brake){
          while (newsol[end_position] > nb_cust){
            end_position += 1;
            ep_iterations ++;
            if (end_position >= size - 1){
              end_position = start_position2;
              ep_iterations = size;
              brake = true;
            }
          }
          int route_depot;
          for (int z = end_position; z >= 0; z--){
            if (newsol[z] > nb_cust){
              route_depot = newsol[z];
              break;
            }
          }
          for (int t = 0; t < this->nlist[newsol[start_position] - 1].size() ; t++){
            if (this->nlist[newsol[start_position] - 1][t] == route_depot){
              possible_depot = true;
              break;
            }
          }
            if (!possible_depot && !brake){
              while (newsol[end_position] <= nb_cust){
                end_position += 1;
                ep_iterations ++;
            }
            }
        }

        //bool doable;
        if (end_position >= start_position2){
          int soli = newsol[start_position];
          std::swap(newsol[start_position2],newsol[end_position]);
          newsol.erase(newsol.begin() + start_position);
          newsol.insert(newsol.begin() + end_position - 1, soli);
        }else if (end_position < start_position){
          int soli = newsol[start_position];
          std::swap(newsol[start_position2],newsol[end_position]);
          newsol.erase(newsol.begin() + start_position);
          newsol.insert(newsol.begin() + end_position, soli);
        }


        // if (start_position <= end_position){
        //   doable = checkConstraints(newsol, start_position, end_position); 
        // }else{
        //   doable = checkConstraints(newsol, end_position, start_position);
        // } 
        bool doable = checkConstraints(newsol);
        if (doable){
          double new_val = pis.computeObjectiveFunction(newsol);
          value->setSolutionValue(new_val);
        }

        return value;
        
      
    }
}



    void emili::mdvrp::MdvrpExchange21Neighborhood::reverseLastMove(Solution *step)
{
    std::vector < int >& newsol = ((emili::mdvrp::SolutionMdvrp*)step)->get_sol();

    if (end_position >= start_position2){
      int soli = newsol[end_position - 1];
      newsol.erase(newsol.begin() + end_position - 1);
      newsol.insert(newsol.begin() + start_position, soli);
      std::swap(newsol[start_position2],newsol[end_position]);

    }else if(end_position < start_position){
      int soli = newsol[end_position];
      newsol.erase(newsol.begin() + end_position);
      newsol.insert(newsol.begin() + start_position, soli);
      std::swap(newsol[start_position2],newsol[end_position]);
    }

}



emili::Solution* emili::mdvrp::MdvrpExchange21Neighborhood::random(Solution *currentSolution)
{

    std::vector < int > newsol(((emili::mdvrp::SolutionMdvrp*)currentSolution)->get_sol());
    int best_i, best_j,best_i2;
    bool done = false;
    int counter = 0; // counter so that it doesnt stay here infinetly or at least very long, MAYBE REMOVE THIS AT SOME POINT TO CHECK IF MAKES DIFF IN RESULTS
    int size = newsol.size();
    while (!done && counter < size/ 2){
      best_i = (emili::generateRandomNumber()%size); 
      best_j = (emili::generateRandomNumber()%size);
      best_i2 = best_i + 1;
      while (newsol[best_i] > nb_cust || newsol[best_j] > nb_cust || newsol[best_i2] > nb_cust || best_j <= best_i){ // make sure we are not moving a depot 
            best_i = (emili::generateRandomNumber()%size);
            best_j = (emili::generateRandomNumber()%size);
            best_i2 = best_i + 1;
      }
      int soli = newsol[best_i];
      std::swap(newsol[best_i2],newsol[best_j]);
      newsol.erase(newsol.begin() + best_i);
      newsol.insert(newsol.begin() + best_j - 1, soli);
      done = checkConstraints(newsol);
      if (!done){
        soli = newsol[best_j - 1];
        newsol.erase(newsol.begin() + best_j - 1);
        newsol.insert(newsol.begin() + best_i, soli);
        std::swap(newsol[best_i2],newsol[best_j]);
      }
      counter++;
    }
    double value = pis.computeObjectiveFunction(newsol);
    return new emili::mdvrp::SolutionMdvrp(value,newsol);
}





emili::Neighborhood::NeighborhoodIterator emili::mdvrp::Mdvrp2optNeighborhood::begin(emili::Solution *base)
{
    ep_iterations = 1;
    sp_iterations = 1;
    return emili::Neighborhood::NeighborhoodIterator(this,base);
}

void emili::mdvrp::Mdvrp2optNeighborhood::reset()
{    
    start_position = 1;
    start_position2 = 2;
    end_position = 1;
    end_position2 = 2;
}


emili::Solution* emili::mdvrp::Mdvrp2optNeighborhood::computeStep(emili::Solution* value)
{
    emili::iteration_increment();
    std::vector < int >& newsol = ((emili::mdvrp::SolutionMdvrp*)value)->get_sol();
    int size = newsol.size();
    if(sp_iterations >= size - 2)
    {    
        return nullptr;
    }else
    {
        if(ep_iterations < size - 1){
            ep_iterations++;
        }
        else
        {
            sp_iterations++;
            ep_iterations = sp_iterations+2;
            start_position = (start_position%size)+1;
            end_position = start_position;
        }
        end_position = (end_position%size)+1;
        end_position2 = end_position + 1;
        start_position2 = start_position + 1;
        while (end_position < size && newsol[end_position] > nb_cust){
          end_position += 1;
          end_position2 +=1;
          ep_iterations ++;

        }
        if (end_position2 > size - 1){
            start_position ++;
            start_position2 ++;
            end_position2 = start_position + 3;
            end_position = start_position2 + 1;
        }
        while (start_position2 < size && newsol[start_position2] > nb_cust){
          start_position += 1;
          start_position2 += 1;
          sp_iterations ++;
        }
        if (start_position >= size - 3){
          start_position = 1;
          start_position2 = 2;
          end_position = 3;
          end_position2 = 4;

        }
        bool doable;
        diff_route = false;
        int last_depot = 0;
        for (int d = start_position2; d <= end_position2; d++){
          if (newsol[d] > nb_cust){
            diff_route = true;
            break;
          } 
        }

        if(diff_route){
          doable = false;
          ep_iterations = size;
        }else{
          std::swap(newsol[start_position2],newsol[end_position]);
          int invert1 = start_position2 + 1;
          int invert2 = end_position - 1;
          while(invert1 < invert2){
            std::swap(newsol[invert1], newsol[invert2]);
            invert1+=1;
            invert2-=1;
          }
          //doable = checkConstraints(newsol, start_position, end_position); 
          doable = checkConstraints(newsol);
        }
        
        if (doable){
          double new_val = pis.computeObjectiveFunction(newsol);
          value->setSolutionValue(new_val);
        }else{
          value->setSolutionValue(value->getSolutionValue());
        }

        return value;
    }
}


    void emili::mdvrp::Mdvrp2optNeighborhood::reverseLastMove(Solution *step)
{
    std::vector < int >& newsol = ((emili::mdvrp::SolutionMdvrp*)step)->get_sol();
    if (!diff_route){
      std::swap(newsol[start_position2],newsol[end_position]);
      int invert1 = start_position2 + 1;
      int invert2 = end_position - 1;
      while(invert1 < invert2){
        std::swap(newsol[invert1], newsol[invert2]);
        invert1+=1;
        invert2-=1;
      }
    }

}

bool emili::mdvrp::Mdvrp2optNeighborhood::different_depot(std::vector <int>& newsol, int best_i, int best_j, int best_i2, int best_j2){
  bool diff_depot = false;
  int last_depot = 0;
  for (int d = best_i2; d < best_j2; d++){
    if (last_depot = 0 && newsol[d] > nb_cust){
      last_depot = newsol[d];
    }else if (newsol[d] > nb_cust && newsol[d] != last_depot){
      diff_depot = true;
    }else if (newsol[d] > nb_cust){
      last_depot = newsol[d];
    }
  }
  return diff_depot;
}

emili::Solution* emili::mdvrp::Mdvrp2optNeighborhood::random(Solution *currentSolution)
{

    std::vector < int > newsol(((emili::mdvrp::SolutionMdvrp*)currentSolution)->get_sol());
    int best_i, best_j,best_i2, best_j2;
    bool done = false;
    int counter = 0; // counter so that it doesnt stay here infinetly or at least very long, MAYBE REMOVE THIS AT SOME POINT TO CHECK IF MAKES DIFF IN RESULTS
    const int max_c = pis.getmaxCapacity();
    const int max_d = pis.getmaxDuration();
    const std::vector<int>& demand = pis.getdemand();
    const std::vector<int>& durations = pis.getserviceDuration();
    int size = newsol.size();
    while (!done && counter < size / 2){
      best_i = (emili::generateRandomNumber()%size); 
      best_j = (emili::generateRandomNumber()%size);
      best_i2 = best_i + 1;
      best_j2 = best_j + 1;
      bool diff_depot = different_depot(newsol, best_i, best_j, best_i2, best_j2);
      while (newsol[best_i2] > nb_cust || newsol[best_j] > nb_cust || diff_depot || best_j < best_i){ 
            best_i = (emili::generateRandomNumber()%size);
            best_j = (emili::generateRandomNumber()%size);
            best_i2 = best_i + 1;
            best_j2 = best_j + 1;
            diff_depot = different_depot(newsol, best_i, best_j, best_i2, best_j2);
      }
      std::swap(newsol[best_i2],newsol[best_j]);
      int invert1 = best_i2 + 1;
      int invert2 = best_j - 1;
      while(invert1 < invert2){
        std::swap(newsol[invert1], newsol[invert2]);
        invert1+=1;
        invert2-=1;
      }
      
      done = checkConstraints(newsol); // seems to be working
      if (!done){
        std::swap(newsol[best_i2],newsol[best_j]);
        int invert1 = best_i2 + 1;
        int invert2 = best_j - 1;
        while(invert1 < invert2){
          std::swap(newsol[invert1], newsol[invert2]);
          invert1+=1;
          invert2-=1;
        }
      }
      counter++;
    }

    double value = pis.computeObjectiveFunction(newsol);
    return new emili::mdvrp::SolutionMdvrp(value,newsol);
}





emili::Neighborhood::NeighborhoodIterator emili::mdvrp::Mdvrp2optstarNeighborhood::begin(emili::Solution *base)
{
    ep_iterations = 1;
    sp_iterations = 1;
    return emili::Neighborhood::NeighborhoodIterator(this,base);
}

void emili::mdvrp::Mdvrp2optstarNeighborhood::reset()
{    
    start_position = 1;
    start_position2 = 2;
    end_position = 1;
    end_position2 = 2;
}


emili::Solution* emili::mdvrp::Mdvrp2optstarNeighborhood::computeStep(emili::Solution* value)
{
    emili::iteration_increment();
    bool skip;
    std::vector < int >& newsol = ((emili::mdvrp::SolutionMdvrp*)value)->get_sol();

    int size = newsol.size();
    if(sp_iterations >= size - 2)
    {    
        return nullptr;
    }else
    {
        if(ep_iterations < size - 1){
            ep_iterations++;
        }
        else
        {
            sp_iterations++;
            ep_iterations = sp_iterations+2;
            start_position = (start_position%size)+1;
            end_position = start_position;
        }
        end_position = (end_position%size)+1;
        end_position2 = end_position + 1;
        start_position2 = start_position + 1;
        while ((end_position < size && newsol[end_position] > nb_cust) || (end_position2 < size && newsol[end_position2] > nb_cust)){
          end_position += 1;
          end_position2 +=1;
          ep_iterations ++;
          if (end_position2 >= size - 1){
            start_position ++;
            start_position2 ++;
            end_position2 = start_position + 3;
            end_position = start_position2 + 1;
            ep_iterations = size;
          }
        }

      // uncomment this if trouble 
      // if (end_position2 >= size - 1){
      //       start_position ++;
      //       start_position2 ++;
      //       end_position2 = start_position + 3;
      //       end_position = start_position2 + 1;
      //       ep_iterations = size;
      //   }

        while ((start_position2 < size && newsol[start_position2] > nb_cust) || (start_position < size && newsol[start_position] > nb_cust)){
          start_position += 1;
          start_position2 += 1;
          sp_iterations ++;
        }
        if (start_position >= size - 3){
          start_position = newsol.size();
          skip = true;
        }
        if (!skip){
        double new_val, new_val2;
        diff_route = false;
        diff_depot = false;
        int last_depot = 0;
        int index;
        route1.clear();
        route2.clear();
        for (int d = start_position2; d <= end_position2; d++){
          if (newsol[d] > nb_cust){
            diff_route = true;
            index = d;
            break;
          } 
        }

      for (int d = start_position2; d <= end_position2; d++){
        if (last_depot == 0 && newsol[d] > nb_cust){
            last_depot = newsol[d];
          }else if (newsol[d] > nb_cust && newsol[d] != last_depot){
            diff_depot = true;
          }else if (newsol[d] > nb_cust){
            last_depot = newsol[d];
          }
        }

        cases = 0;
        if (diff_route && !diff_depot){
          for (int t = start_position2; t < index; t++){
            route1.push_back(newsol[t]);
          }
          int z = end_position2;
          while (newsol[z] < nb_cust){
            route2.push_back(newsol[z]);  
            z++;
          }
          for (int r = 0;r < route1.size(); r++){
            newsol.erase(newsol.begin() + start_position2);
          }
          for (int x = route2.size()-1; x >=0 ; x--){
            newsol.insert(newsol.begin() + start_position2, route2[x]);
          }
          diff = route1.size() - route2.size();
          for (int s = 0; s < route2.size(); s++){
            newsol.erase(newsol.begin() + end_position2 - diff);
          }
          for (int y = route1.size() - 1; y >= 0; y--){
            newsol.insert(newsol.begin() + end_position2 - diff, route1[y]);
          }
          bool doable = checkConstraints(newsol);
          if (doable){
            new_val = pis.computeObjectiveFunction(newsol);
          }

          for (int y = 0; y < route1.size(); y++) {
            newsol.erase(newsol.begin() + end_position2 - diff);
          }
          for (int x = route2.size() - 1; x >= 0; x--) {
              newsol.insert(newsol.begin() + end_position2 - diff, route2[x]);
          }
          for (int s = route2.size() - 1; s >= 0; s--) {
              newsol.erase(newsol.begin() + start_position2);
          }
          for (int r = route1.size() - 1; r >= 0; r--) {
              newsol.insert(newsol.begin() + start_position2, route1[r]);
          }


          std::swap(newsol[start_position2],newsol[end_position]);
          int invert1 = start_position2 + 1;
          int invert2 = end_position - 1;
          while(invert1 < invert2){
            std::swap(newsol[invert1], newsol[invert2]);
            invert1+=1;
            invert2-=1;
          }

          bool doable2 = checkConstraints(newsol);
          if (doable2){
            new_val2 = pis.computeObjectiveFunction(newsol);
            if (doable){
              if (new_val < new_val2){
                std::swap(newsol[start_position2],newsol[end_position]);
                int invert1 = start_position2 + 1;
                int invert2 = end_position - 1;
                while(invert1 < invert2){
                  std::swap(newsol[invert1], newsol[invert2]);
                  invert1+=1;
                  invert2-=1;
                }
                for (int r = 0;r < route1.size(); r++){
                  newsol.erase(newsol.begin() + start_position2);
                }
                for (int x = route2.size()-1; x >=0 ; x--){
                  newsol.insert(newsol.begin() + start_position2, route2[x]);
                }
                diff = route1.size() - route2.size();
                for (int s = 0; s < route2.size(); s++){
                  newsol.erase(newsol.begin() + end_position2 - diff);
                }
                for (int y = route1.size() - 1; y >= 0; y--){
                  newsol.insert(newsol.begin() + end_position2 - diff, route1[y]);
                }
                value->setSolutionValue(new_val);
                cases = 1;
              }else{
                value->setSolutionValue(new_val2);
                cases = 2;
              }
            }else{
                value->setSolutionValue(new_val2);
                cases = 2;
              }
          }else if (doable){

            std::swap(newsol[start_position2],newsol[end_position]);
            int invert1 = start_position2 + 1;
            int invert2 = end_position - 1;
            while(invert1 < invert2){
              std::swap(newsol[invert1], newsol[invert2]);
              invert1+=1;
              invert2-=1;
            }

            for (int r = 0;r < route1.size(); r++){
            newsol.erase(newsol.begin() + start_position2);
          }
          for (int x = route2.size()-1; x >=0 ; x--){
            newsol.insert(newsol.begin() + start_position2, route2[x]);
          }
          diff = route1.size() - route2.size();
          for (int s = 0; s < route2.size(); s++){
            newsol.erase(newsol.begin() + end_position2 - diff);
          }
          for (int y = route1.size() - 1; y >= 0; y--){
            newsol.insert(newsol.begin() + end_position2 - diff, route1[y]);
          }
             value->setSolutionValue(new_val);
             cases = 1;
          }else{
            cases = 2;
            value->setSolutionValue(value->getSolutionValue());
          }
        }else if (diff_route && diff_depot){
          cases = 1;
          // HERERERERERERE 

          for (int t = start_position2; t < index; t++){
            route1.push_back(newsol[t]);
          }
          int z = end_position2;
          while (newsol[z] < nb_cust){
            route2.push_back(newsol[z]);  
            z++;
          }
          for (int r = 0;r < route1.size(); r++){
            newsol.erase(newsol.begin() + start_position2);
          }
          for (int x = route2.size()-1; x >=0 ; x--){
            newsol.insert(newsol.begin() + start_position2, route2[x]);
          }
          diff = route1.size() - route2.size();
          for (int s = 0; s < route2.size(); s++){
            newsol.erase(newsol.begin() + end_position2 - diff);
          }
          for (int y = route1.size() - 1; y >= 0; y--){
            newsol.insert(newsol.begin() + end_position2 - diff, route1[y]);
          }

          bool doable = checkConstraints(newsol);
          if (doable){
            new_val = pis.computeObjectiveFunction(newsol);
          }

          for (int y = 0; y < route1.size(); y++) {
            newsol.erase(newsol.begin() + end_position2 - diff);
          }
          for (int x = route2.size() - 1; x >= 0; x--) {
              newsol.insert(newsol.begin() + end_position2 - diff, route2[x]);
          }
          for (int s = route2.size() - 1; s >= 0; s--) {
              newsol.erase(newsol.begin() + start_position2);
          }
          for (int r = route1.size() - 1; r >= 0; r--) {
              newsol.insert(newsol.begin() + start_position2, route1[r]);
          }

          // std::cout << " huh " << std::endl;
          // for (int t = 0; t < newsol.size(); t++){
          //     std::cout << newsol[t] << " ";
          //   }
          //   std::cout << std::endl;
          std::swap(newsol[start_position2],newsol[end_position]);
          int invert1 = start_position2 + 1;
          int invert2 = end_position - 1;
          while(invert1 < invert2 && newsol[invert1] <= nb_cust && newsol[invert2] <= nb_cust){
            std::swap(newsol[invert1], newsol[invert2]);
            invert1+=1;
            invert2-=1;
          }

          if (newsol[invert1] > nb_cust && newsol[invert2] <= nb_cust){
            //std::cout << invert1 << "-" << invert2 << std::endl;
            while (newsol[invert2] <= nb_cust && invert2 > invert1){
              int temp = newsol[invert2];
              newsol.erase(newsol.begin() + invert2);
              newsol.insert(newsol.begin() + invert1, temp);
              invert1++;
            }
          }else if (newsol[invert1] <= nb_cust && newsol[invert2] > nb_cust){
            while (newsol[invert1] <= nb_cust && invert1 < invert2){
              int temp = newsol[invert1];
              newsol.erase(newsol.begin() + invert1);
              newsol.insert(newsol.begin() + invert2, temp);
              invert2--;
            }
          }
          bool doable2 = checkConstraints(newsol);
          if (doable2){
            //std::cout << " here  " << std::endl;
            new_val2 = pis.computeObjectiveFunction(newsol);
            if (doable){
              if (new_val < new_val2){
                std::swap(newsol[start_position2],newsol[end_position]);
                int invert1 = start_position2 + 1;
                int invert2 = end_position - 1;
                while(invert1 < invert2 && newsol[invert1] <= nb_cust && newsol[invert2] <= nb_cust){
                  std::swap(newsol[invert1], newsol[invert2]);
                  invert1+=1;
                  invert2-=1;
                }
                if (newsol[invert1] > nb_cust && newsol[invert2] <= nb_cust){
                  while (newsol[invert2] <= nb_cust && invert2 > invert1){
                    int temp = newsol[invert2];
                    newsol.erase(newsol.begin() + invert2);
                    newsol.insert(newsol.begin() + invert1, temp);
                    invert1++;
                  }
                }else if (newsol[invert1] <= nb_cust && newsol[invert2] > nb_cust){
                  while (newsol[invert1] <= nb_cust && invert1 < invert2){
                    int temp = newsol[invert1];
                    newsol.erase(newsol.begin() + invert1);
                    newsol.insert(newsol.begin() + invert2, temp);
                    invert2--;
                  }
                }

                for (int r = 0;r < route1.size(); r++){
                  newsol.erase(newsol.begin() + start_position2);
                }
                for (int x = route2.size()-1; x >=0 ; x--){
                  newsol.insert(newsol.begin() + start_position2, route2[x]);
                }
                diff = route1.size() - route2.size();
                for (int s = 0; s < route2.size(); s++){
                  newsol.erase(newsol.begin() + end_position2 - diff);
                }
                for (int y = route1.size() - 1; y >= 0; y--){
                  newsol.insert(newsol.begin() + end_position2 - diff, route1[y]);
                }
                value->setSolutionValue(new_val);
                cases = 1;
              }else{
                value->setSolutionValue(new_val2);
                cases = 3;
              }
            }else{
                value->setSolutionValue(new_val2);
                cases = 3;
            }
          }else if (doable && !doable2){

            std::swap(newsol[start_position2],newsol[end_position]);
            int invert1 = start_position2 + 1;
            int invert2 = end_position - 1;
            while(invert1 < invert2 && newsol[invert1] <= nb_cust && newsol[invert2] <= nb_cust){
              std::swap(newsol[invert1], newsol[invert2]);
              invert1+=1;
              invert2-=1;
            }
            if (newsol[invert1] > nb_cust && newsol[invert2] <= nb_cust){
              while (newsol[invert2] <= nb_cust && invert2 > invert1){
                int temp = newsol[invert2];
                newsol.erase(newsol.begin() + invert2);
                newsol.insert(newsol.begin() + invert1, temp);
                invert1++;
              }
            }else if (newsol[invert1] <= nb_cust && newsol[invert2] > nb_cust){
              while (newsol[invert1] <= nb_cust && invert1 < invert2){
                int temp = newsol[invert1];
                newsol.erase(newsol.begin() + invert1);
                newsol.insert(newsol.begin() + invert2, temp);
                invert2--;
              }
            }
          for (int r = 0;r < route1.size(); r++){
            newsol.erase(newsol.begin() + start_position2);
          }
          for (int x = route2.size()-1; x >=0 ; x--){
            newsol.insert(newsol.begin() + start_position2, route2[x]);
          }
          diff = route1.size() - route2.size();
          for (int s = 0; s < route2.size(); s++){
            newsol.erase(newsol.begin() + end_position2 - diff);
          }
          for (int y = route1.size() - 1; y >= 0; y--){
            newsol.insert(newsol.begin() + end_position2 - diff, route1[y]);
          }

            //                   std::cout << " other " << std::endl;
            //  for (int t = 0; t < newsol.size(); t++){
            //    std::cout << newsol[t] << " ";
            //  }
            //std::cout << std::endl;
             value->setSolutionValue(new_val);
             cases = 1;
          }else{
            cases = 3;
            value->setSolutionValue(value->getSolutionValue());
          }
        }else{
          bool doable = false;
          value->setSolutionValue(value->getSolutionValue());
        } 
        }else{
          cases = 0;
          bool doable = false;
          value->setSolutionValue(value->getSolutionValue());
        } 

        return value;
    }
}


    void emili::mdvrp::Mdvrp2optstarNeighborhood::reverseLastMove(Solution *step)
{
    std::vector < int >& newsol = ((emili::mdvrp::SolutionMdvrp*)step)->get_sol();
    if (diff_route && cases == 1){
      for (int y = 0; y < route1.size(); y++) {
        newsol.erase(newsol.begin() + end_position2 - diff);
      }
      for (int x = route2.size() - 1; x >= 0; x--) {
          newsol.insert(newsol.begin() + end_position2 - diff, route2[x]);
      }
      for (int s = route2.size() - 1; s >= 0; s--) {
          newsol.erase(newsol.begin() + start_position2);
      }
      for (int r = route1.size() - 1; r >= 0; r--) {
          newsol.insert(newsol.begin() + start_position2, route1[r]);
      }
    }else if (diff_route && cases == 2){
      std::swap(newsol[start_position2],newsol[end_position]);
      int invert1 = start_position2 + 1;
      int invert2 = end_position - 1;
      while(invert1 < invert2){ 
        std::swap(newsol[invert1], newsol[invert2]);
        invert1+=1;
        invert2-=1;
      }
    }else if (diff_route && cases == 3){
      //  std::cout << start_position2 << " " << end_position << std::endl;
      // std::cout << newsol[start_position2] << "-" << newsol[end_position] << std::endl;
      std::swap(newsol[start_position2],newsol[end_position]);
      int invert1 = start_position2 + 1;
      int invert2 = end_position - 1;
      while(invert1 < invert2 && newsol[invert1] <= nb_cust && newsol[invert2] <= nb_cust){
        std::swap(newsol[invert1], newsol[invert2]);
        invert1+=1;
        invert2-=1;
      }
      // std::cout << invert1 << " inv " << invert2 << std::endl;
      // std::cout << newsol[invert1] << "inv n" << newsol[invert2] << std::endl;
      if (newsol[invert1] > nb_cust && newsol[invert2] <= nb_cust){
        //std::cout << " here " << std::endl;
        while (newsol[invert2] <= nb_cust && invert2 > invert1){
          int temp = newsol[invert2];
          newsol.erase(newsol.begin() + invert2);
          newsol.insert(newsol.begin() + invert1, temp);
          invert1++;
        }
      }else if (newsol[invert1] <= nb_cust && newsol[invert2] > nb_cust){
        //std::cout << " here " << std::endl;
        while (newsol[invert1] <= nb_cust && invert1 < invert2){
          int temp = newsol[invert1];
          newsol.erase(newsol.begin() + invert1);
          newsol.insert(newsol.begin() + invert2, temp);
          invert2--;
        }
      }
      // std::cout << invert1 << " end " << invert2 << std::endl;
      //  std::cout << newsol[invert1] << "end n" << newsol[invert2] << std::endl;
    }
}

bool emili::mdvrp::Mdvrp2optstarNeighborhood::different_route(std::vector <int>& newsol, int best_i, int best_j, int best_i2, int best_j2){
  bool diff_depot = false;
  int last_depot = 0;
  for (int d = best_i2; d < best_j2; d++){
    if (last_depot = 0 && newsol[d] > nb_cust){
      last_depot = newsol[d];
    }else if (newsol[d] > nb_cust && newsol[d] != last_depot){
      diff_depot = true;
    }else if (newsol[d] > nb_cust){
      last_depot = newsol[d];
    }
  }
  return diff_depot;
}

// this was not modifed i think its just 2opt
emili::Solution* emili::mdvrp::Mdvrp2optstarNeighborhood::random(Solution *currentSolution)
{

    std::vector < int > newsol(((emili::mdvrp::SolutionMdvrp*)currentSolution)->get_sol());
    int best_i, best_j,best_i2, best_j2;
    bool done = false;
    int counter = 0; // counter so that it doesnt stay here infinetly or at least very long, MAYBE REMOVE THIS AT SOME POINT TO CHECK IF MAKES DIFF IN RESULTS
    const int max_c = pis.getmaxCapacity();
    const int max_d = pis.getmaxDuration();
    const std::vector<int>& demand = pis.getdemand();
    const std::vector<int>& durations = pis.getserviceDuration();
    int size = newsol.size();
    while (!done && counter < size / 2){
      best_i = (emili::generateRandomNumber()%size); 
      best_j = (emili::generateRandomNumber()%size);
      if (best_i >= size){
        best_i -= 3;
      }
      if (best_j >= size){
        best_j -= 3;
      }
      best_i2 = best_i + 1;
      best_j2 = best_j + 1;
      bool diff_depot = different_route(newsol, best_i, best_j, best_i2, best_j2);
      while (newsol[best_i2] > nb_cust || newsol[best_j] > nb_cust || diff_depot || best_j < best_i){ 
            best_i = (emili::generateRandomNumber()%size);
            best_j = (emili::generateRandomNumber()%size);
            if (best_i >= size){
              best_i -= 3;
            }
            if (best_j >= size){
              best_j -= 3;
            }
            best_i2 = best_i + 1;
            best_j2 = best_j + 1;
            diff_depot = different_route(newsol, best_i, best_j, best_i2, best_j2);
      }
      std::swap(newsol[best_i2],newsol[best_j]);
      int invert1 = best_i2 + 1;
      int invert2 = best_j - 1;
      while(invert1 < invert2){
        std::swap(newsol[invert1], newsol[invert2]);
        invert1+=1;
        invert2-=1;
      }
      
      done = checkConstraints(newsol); // seems to be working
      if (!done){
        std::swap(newsol[best_i2],newsol[best_j]);
        int invert1 = best_i2 + 1;
        int invert2 = best_j - 1;
        while(invert1 < invert2){
          std::swap(newsol[invert1], newsol[invert2]);
          invert1+=1;
          invert2-=1;
        }
      }
      counter++;
    }

    double value = pis.computeObjectiveFunction(newsol);
    return new emili::mdvrp::SolutionMdvrp(value,newsol);
}



// out of date
bool emili::mdvrp::PerturbationRandomMove::checkConstraints(std::vector<int>& sol, int yes, int no){
      // capacity and time constraints check
      int route_cap = 0, service_time = 0;
      int current_depot = 0;
      bool observed_depot = false;
      bool correct = true;
      std::vector<int>& demands = prob.getdemand();
      std::vector<int>& durations = prob.getserviceDuration();
      for (int i = 0; i < sol.size(); i++){
        if (sol[i] > prob.getnbCustomers()){
          if (observed_depot){
            observed_depot = false;
            if (route_cap > prob.getmaxCapacity() || service_time > prob.getmaxDuration()){
              correct = false;
              break; // maybe change this break
            }else{
              route_cap = 0;
              service_time = 0;
            }
          }else{
            current_depot = sol[i];
            observed_depot = true;
          }
        }else{
          route_cap += demands[sol[i] - 1];
          service_time += durations[sol[i] - 1];
        }
      }

      return correct;
    }


      emili::Solution* emili::mdvrp::PerturbationRandomMove::perturb(Solution* solution)
      {
        std::vector < int >& newsol = (((emili::mdvrp::SolutionMdvrp*)solution)->get_sol());
        int best_i, best_j;
        int nb_cust = prob.getnbCustomers();
        bool done = false;
        int counter = 0;
        while (!done && counter < newsol.size() / 2){
          best_i = (emili::generateRandomNumber()%newsol.size()); // dont make random, make test all positions
          best_j = (emili::generateRandomNumber()%newsol.size());
          while (newsol[best_i] > nb_cust || newsol[best_j] > nb_cust){ // make sure we are not moving a depot 
            best_i = (emili::generateRandomNumber()%newsol.size());
            best_j = (emili::generateRandomNumber()%newsol.size());
          }
          int sol_i = newsol[best_i]; // change to start and end position i guess
          newsol.erase(newsol.begin()+best_i);
          newsol.insert(newsol.begin()+best_j,sol_i);
          done = checkConstraints(newsol, best_i, best_j); 
          counter ++;
        }
        emili::mdvrp::SolutionMdvrp* nsol = new emili::mdvrp::SolutionMdvrp(newsol);
        prob.evaluateSolution(*nsol);
        return nsol;
      }



emili::Solution* emili::mdvrp::RestartPerturbation::perturb(Solution *solution)
{
    emili::Solution* best;
    emili::Solution* current;
    best = initial->generateSolution();

    for(int i=0;i<num_of_solutions;i++)
    {
        current = initial->generateSolution();
        if( *current < *best)
        {
            delete best;
            best = current;
        }
        else
        {
            delete current;
        }

    }

    if(locser)
    {
        current = ls->search(best);
        if(current!=best)
            delete best;

        return current;
    }

    return best;
}


emili::mdvrp::RestartPerturbation::~RestartPerturbation()
{
    if(ls!=nullptr)
        delete ls;
    delete initial;
}


      bool emili::mdvrp::Iteratermination::terminate(Solution *currentSolution, Solution *newSolution)
      {
        if(currentStep < numberOfSteps){
          currentStep++;
          return false;
        }
        else
        {
          return true;
        }
      }

      void emili::mdvrp::Iteratermination::reset(){
      currentStep=0;
      }



  bool emili::mdvrp::MdvrpTerminationIterations::terminate(Solution* currentSolution, Solution* newSolution)
{
    if(iterations < maxIterations)
    {
        if(newSolution != nullptr && currentSolution->operator <=(*newSolution))
        {
            iterations++;
        }

            return false;
    }
    return true;
}

void emili::mdvrp::MdvrpTerminationIterations::reset()
{
    iterations=0;
}



    emili::Solution* emili::mdvrp::MdvrpTestAcceptance::accept(Solution *candidate1, Solution *candidate2)
{
    int chance = emili::generateRandomNumber()%100;
    emili::Solution* c = candidate1;
    emili::Solution* c2 = candidate2;
    if(candidate1->operator >(*candidate2)){
        c = candidate2;
        c2 = candidate1;
    }

    if(chance <= percentage)
    {
        return c;
    }
    else
    {
        return c2;
    }

}


bool emili::mdvrp::MdvrpTabuValueMemory::tabu_check(emili::Solution* toCheck)
{

    double value = toCheck->getSolutionValue();
    for(std::vector< double>::iterator iter = tabuVector.begin();iter!=tabuVector.end();++iter)
    {
        if( value == *iter){
            return false;
        }
    }
    return true;
}

void emili::mdvrp::MdvrpTabuValueMemory::forbid(Solution *solution)
{

    if(tabu_check(solution))
    {
        if(tt_index < this->tabutenure){
            tabuVector.push_back(solution->getSolutionValue());
            tt_index++;
        }
        else
        {
            tabuVector.erase(tabuVector.begin());
            tabuVector.push_back(solution->getSolutionValue());
        }
    }
}

void emili::mdvrp::MdvrpTabuValueMemory::reset()
{
    tt_index = 0;
    tabuVector.clear();
}


bool emili::mdvrp::MdvrpMovesMemory::tabu_check(emili::Solution* toCheck)
{

    return tabu_check(lastMove);
}

bool emili::mdvrp::MdvrpMovesMemory::tabu_check(std::pair< int,int > value)
{
    for(std::vector< std::pair<int,int > >::iterator iter = tabuVector.begin();iter!=tabuVector.end();++iter)
    {
        std::pair< int ,int> t = *iter ;
        if(value==t)
        {
            return false;
        }
    }
    return true;
}

void emili::mdvrp::MdvrpMovesMemory::forbid(Solution *solution)
{
    if(tabu_check(lastMove))
    {
        if(tt_index < this->tabutenure){
            tabuVector.push_back(lastMove);
            tt_index++;
        }
        else
        {
            tabuVector.erase(tabuVector.begin());
            tabuVector.push_back(lastMove);
        }
    }
}


void emili::mdvrp::MdvrpMovesMemory::registerMove(emili::Solution* base,emili::Solution* solution)
{
    lastMove = neigh->lastMove();
}

// void emili::mdvrp::MdvrpMovesMemory2::registerMove(emili::Solution* base,emili::Solution* solution)
// {
//     std::pair<int,int> lm = neigh->lastMove();

//     int job = ((emili::pfsp::PermutationFlowShopSolution*) base)->getJobSchedule()[lm.second];
//     lastMove = std::pair<int,int>(job,lm.first);
// }

void emili::mdvrp::MdvrpMovesMemory::reset()
{
    tt_index = 0;
    tabuVector.clear();
}




bool emili::mdvrp::MdvrpFullSolutionMemory::tabu_check(emili::Solution* toCheck)
{

    std::vector< int >& value = ((emili::mdvrp::SolutionMdvrp*)toCheck)->get_sol();

    for(std::vector< std::vector<int > >::iterator iter = tabuVector.begin();iter!=tabuVector.end();++iter)
    {
        std::vector< int > t = *iter ;
        bool ret = false;
        for(int i=0; i< t.size() ; i++)
        {
            if(t[i]!=value[i])
            {
                ret = true;
                break;
            }
        }
        if(!ret)
        {
            return ret;
        }
    }
    return true;
}

void emili::mdvrp::MdvrpFullSolutionMemory::forbid(Solution *solution)
{

    if(tabu_check(solution))
    {
        std::vector< int >& solution_vector = ((emili::mdvrp::SolutionMdvrp*)solution)->get_sol();
        if(tt_index < this->tabutenure){
            tabuVector.push_back(solution_vector);
            tt_index++;
        }
        else
        {
            tabuVector.erase(tabuVector.begin());            
            tabuVector.push_back(solution_vector);

        }
    }
}

void emili::mdvrp::MdvrpFullSolutionMemory::reset()
{
    tt_index = 0;
    tabuVector.clear();
}


void emili::mdvrp::MdvrpMovesMemory2::registerMove(emili::Solution* base,emili::Solution* solution)
{
    std::pair<int,int> lm = neigh->lastMove();

    int job = ((emili::mdvrp::SolutionMdvrp*) base)->get_sol()[lm.second];
    lastMove = std::pair<int,int>(job,lm.first);
}