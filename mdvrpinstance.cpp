#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <exception>
#include <stdexcept>
#include "mdvrpinstance.h"
#include  <assert.h>

int MdvrpInstance::getnbVehicles(){
    return nbVehicles;
}

void MdvrpInstance::setnbVehicles(int vehicleCount){
    this->nbVehicles = vehicleCount;
}

int MdvrpInstance::getnbCustomers(){
    return nbCustomers;
}

void MdvrpInstance::setnbCustomers(int customerCount){
    this->nbCustomers = customerCount;
}

int MdvrpInstance::getnbDepots(){
    return nbDepots;
}

void MdvrpInstance::setnbDepots(int depotCount){
    this->nbDepots = depotCount;
}

std::vector<int>& MdvrpInstance::getdepots(){
    return depots;
}

int MdvrpInstance::getmaxDuration(){
    return maxDuration;
}

void MdvrpInstance::setmaxDuration(int duration){
    this->maxDuration = duration;
}

int MdvrpInstance::getmaxCapacity(){
    return maxCapacity;
}

void MdvrpInstance::setmaxCapacity(int capacity){
    this->maxCapacity = capacity;
}

std::vector<int>& MdvrpInstance::getcustomers(){
    return customers;
}

void MdvrpInstance::setcustomers(std::vector<int> customers){
    this->customers = customers;
}

std::vector<std::vector<double>>& MdvrpInstance::getcoordinates(){
    return coordinates;
}

void MdvrpInstance::setcoordinates(std::vector<std::vector<double>> customerCoordinates){
    this->coordinates = customerCoordinates;
}

std::vector<int>& MdvrpInstance::getserviceDuration(){
    return serviceDuration;
}
void MdvrpInstance::setserviceDuration(std::vector<int> servDuration){
    this->serviceDuration = servDuration;
}

std::vector<int>& MdvrpInstance::getdemand(){
    return demand;
}
void MdvrpInstance::setdemand(std::vector<int> customerDemand){
    this->demand = customerDemand;
}
void MdvrpInstance::setnlists(std::vector<std::vector<int>> nlist){
    this->neighborhood_list = nlist;
}



bool MdvrpInstance::readDataFromFile(char* filename, int nlist_d){
    bool everythingOK = true;
    long int readValue = 0;
    std::string str;
    std::ifstream fileIn;
    int cust;
    double coordx;
    double coordy;
    int servdur;
    int dem;
    int pvc;
    int v;
    int dep;
    double depcoordx;
    double depcoordy;
    std::vector<double> depcoords;

    fileIn.open(filename);
    if (fileIn.is_open()){
        fileIn >> this->type;
        fileIn >> this->nbVehicles;
        fileIn >> this->nbCustomers;
        fileIn >> this->nbDepots;
        fileIn >> this->maxDuration;
        fileIn >> this->maxCapacity;
    }
    for (int i = 0; i < this->nbDepots - 1; i++){
        // skiping since same for all
        for (int j = 0; j < 2; j++){
            fileIn >> readValue;
        }
    }

    for (int z = 0; z < this->nbCustomers; z++){
        std::vector<double> coords;
        fileIn >> cust;
        this->customers.push_back(cust);
        fileIn >> coordx;
        fileIn >> coordy;
        coords.push_back(coordx);
        coords.push_back(coordy);
        this->coordinates.push_back(coords);
        fileIn >> servdur;
        this->serviceDuration.push_back(servdur);
        fileIn >> dem;
        this->demand.push_back(dem);
        fileIn >> readValue; // skip frequency visit since always 1
        fileIn >> pvc;
        for (int c = 0; c < pvc; c++){ // skip visit combinations since not used in mdvrp
            fileIn >> readValue;
        }
    }

    for (int d = 0; d < this->nbDepots; d++){
        std::vector<double> depcoords;
        fileIn >> dep;
        depots.push_back(dep);
        fileIn >> depcoordx;
        fileIn >> depcoordy;
        depcoords.push_back(depcoordx);
        depcoords.push_back(depcoordy);
        this->depotCoordinates.push_back(depcoords);
        for (int s = 0; s < 4; s++){
            // skip fields that are set to 0 for all depots
            fileIn >> readValue;
        }
    }
    std::vector<std::vector<int>> nlist;
    std::vector<int> neighbors;
    this->distanceMatrix = createDistanceMatrix();
    this->neighborhood_list = createNlists(nlist_d);
    //   std::cout << " huh " << std::endl;
    //   for (int r = 0; r < neighborhood_list.size(); r++){
    //      std::cout << "n " << r << " :";
    //      int counter = 0;
    //       for (int t = 0; t < neighborhood_list[r].size(); t++){
    //          counter ++;
    //        }

    //        std::cout<< counter << std::endl;
    //    }
    return everythingOK; // remember to put this to false if something go wrong
}


std::vector<std::vector<int>> MdvrpInstance::createNlists(int nlist_d){
    std::vector<std::vector<int>> nlists;
    for (int i = 0; i < this->nbCustomers; i++){
        std::vector<int> neighbors;
        for (int j = 0; j < this->nbDepots; j++){
            bool add_depot = true;
            for (int d = 0; d < this->nbDepots; d++){
                if (d != j){
                if (this->coordinates[i][0] > this->depotCoordinates[j][0] && this->coordinates[i][1] > this->depotCoordinates[j][1]){
                    if (this->depotCoordinates[d][0] > this->depotCoordinates[j][0]  && this->depotCoordinates[d][0] < this->coordinates[i][0] 
                    && this->depotCoordinates[d][1] > this->depotCoordinates[j][1] && this->depotCoordinates[d][1] < this->coordinates[i][1]){
                        add_depot = false;
                        break;
                    }
                }else if (this->coordinates[i][0] > this->depotCoordinates[j][0] && this->coordinates[i][1] < this->depotCoordinates[j][1]){
                    if (this->depotCoordinates[d][0] > this->depotCoordinates[j][0]  && this->depotCoordinates[d][0] < this->coordinates[i][0] 
                    && this->depotCoordinates[d][1] < this->depotCoordinates[j][1] && this->depotCoordinates[d][1] > this->coordinates[i][1]){
                        add_depot = false;
                        break;
                    }
                }else if (this->coordinates[i][0] < this->depotCoordinates[j][0] && this->coordinates[i][1] < this->depotCoordinates[j][1]){
                    if (this->depotCoordinates[d][0] < this->depotCoordinates[j][0]  && this->depotCoordinates[d][0] > this->coordinates[i][0] 
                    && this->depotCoordinates[d][1] < this->depotCoordinates[j][1] && this->depotCoordinates[d][1] > this->coordinates[i][1]){
                        add_depot = false;
                        break;
                    }
                }else if (this->coordinates[i][0] < this->depotCoordinates[j][0] && this->coordinates[i][1] > this->depotCoordinates[j][1]){
                    if (this->depotCoordinates[d][0] < this->depotCoordinates[j][0]  && this->depotCoordinates[d][0] > this->coordinates[i][0] 
                    && this->depotCoordinates[d][1] > this->depotCoordinates[j][1] && this->depotCoordinates[d][1] < this->coordinates[i][1]){
                        add_depot = false;
                        break;
                    }
                }
                }
            }
            if (add_depot){
                neighbors.push_back(this->depots[j]);
            }
        }
        double furthest;
        int furth;
        double current;
        while (neighbors.size() > nlist_d){
            furth = 0;
            furthest = 0;
            for (int z = 0; z < neighbors.size(); z++){
                if (this->distanceMatrix[i][neighbors[z] - 1] > furthest){
                    furth = z;
                    furthest = distanceMatrix[i][neighbors[z] - 1];
                }
            }
            neighbors.erase(neighbors.begin() + furth);
        }
        nlists.push_back(neighbors);
    }
    std::cout << " number of max depots per customer : " << nlist_d << std::endl;
    return nlists;
}



std::vector<std::vector<double>> MdvrpInstance::createDistanceMatrix(){
    int total = this->nbCustomers + this->nbDepots;
    std::vector<std::vector<double>> costMatrix(total);
    double distance;
    for (int i = 0; i < this->nbCustomers; i++){
        for (int j=0; j < this->nbCustomers; j++){
            distance = std::sqrt(std::pow(this->coordinates[j][0]- this->coordinates[i][0], 2) + std::pow(this->coordinates[j][1] - this->coordinates[i][1], 2));
            costMatrix[i].push_back(distance);
        }
        for (int z=0; z< this->nbDepots; z++){
            distance = std::sqrt(std::pow(this->depotCoordinates[z][0]- this->coordinates[i][0], 2) + std::pow(this->depotCoordinates[z][1] - this->coordinates[i][1], 2));
            costMatrix[i].push_back(distance);
        }
    }

    for (int i = 0; i < this->nbDepots; i++){
        for (int j=0; j < this->nbCustomers; j++){
            distance = std::sqrt(std::pow(this->coordinates[j][0]- this->depotCoordinates[i][0], 2) + std::pow(this->coordinates[j][1] - this->depotCoordinates[i][1], 2));
            costMatrix[i+this->nbCustomers].push_back(distance);
        }
        for (int z=0; z< this->nbDepots; z++){
            distance = std::sqrt(std::pow(this->depotCoordinates[z][0]- this->depotCoordinates[i][0], 2) + std::pow(this->depotCoordinates[z][1] - this->depotCoordinates[i][1], 2));
            costMatrix[i + this->nbCustomers].push_back(distance);
        }
    }

    return costMatrix;
}