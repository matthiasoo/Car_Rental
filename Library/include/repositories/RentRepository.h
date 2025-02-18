#ifndef RENTREPOSITORY_H
#define RENTREPOSITORY_H

#include "Rent.h"

class RentRepository {
private:
    std::vector<RentPtr> rentRepository;
public:
    const RentPtr get(int index) const;
    void add(RentPtr rent);
    void remove(RentPtr rent);
    std::string report() const;
    int size();

    std::vector<RentPtr> findBy(RentPredicate predicate) const;
    std::vector<RentPtr> findAll() const;
};



#endif //RENTREPOSITORY_H
