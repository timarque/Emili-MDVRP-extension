#ifndef MDVRPINSTANCE_H
#define MDVRPINSTANCE_H

#include <string>
#include <vector>

class MdvrpInstance{
private:
    int type;
    int nbVehicles;
    int nbCustomers;
    int nbDepots;
    int maxDuration; // same for all depots so int 
    int maxCapacity; // same 
    std::vector<int> customers; 
    std::vector<std::vector<double>> coordinates; 
    std::vector<int> serviceDuration;
    std::vector<int> demand;
    int frequencyVisit = 1; 
    std::vector<int> depots; 
    std::vector<std::vector<double>> depotCoordinates;
    std::vector<std::vector<double>> distanceMatrix;
    std::vector<std::vector<int>> neighborhood_list; // contains possible depots to check for each customer

public:

    MdvrpInstance(MdvrpInstance& is){
        this->nbVehicles = is.getnbVehicles();
        this->nbCustomers = is.getnbCustomers();
        this->nbDepots = is.getnbDepots();
        this->maxDuration = is.getmaxDuration();
        this->maxCapacity = is.getmaxCapacity();
        this->customers = is.getcustomers();
        this->coordinates = is.getcoordinates();
        this->serviceDuration = is.getserviceDuration();
        this->demand = is.getdemand();
        this->depots = is.getdepots();
        this->neighborhood_list = is.getnlists();
        this->distanceMatrix = is.getDistanceMatrix();
        this->neighborhood_list = is.getnlists();
    }

    MdvrpInstance(char* filename, int nlist_d){
    readDataFromFile(filename, nlist_d);
    }

    MdvrpInstance(){};
    ~MdvrpInstance(){};

    bool readDataFromFile(char* filename, int nlist_d);

    int getnbVehicles();
    void setnbVehicles(int vehicleCount);

    int getnbCustomers();
    void setnbCustomers(int customerCount);

    int getnbDepots();
    void setnbDepots(int depotCount);

    int getmaxDuration();
    void setmaxDuration(int duration);

    int getmaxCapacity();
    void setmaxCapacity(int capacity);

    std::vector<int>& getcustomers();
    void setcustomers(std::vector<int> customers);

    std::vector<int>& getdepots();
    void setdepots(std::vector<int> depots);

    std::vector<std::vector<double>>& getcoordinates();
    void setcoordinates(std::vector<std::vector<double>> customerCoordinates);

    std::vector<int>& getserviceDuration();
    void setserviceDuration(std::vector<int> servDuration);

    std::vector<int>& getdemand();
    void setdemand(std::vector<int> customerDemand);

    std::vector<std::vector<int>> createNlists(int nlist_d);
    std::vector<std::vector<int>>& getnlists(){return this->neighborhood_list;};
    void setnlists(std::vector<std::vector<int>> nlists);

    std::vector<std::vector<double>> createDistanceMatrix();
    std::vector<std::vector<double>>& getDistanceMatrix(){return this->distanceMatrix;};

};

#endif