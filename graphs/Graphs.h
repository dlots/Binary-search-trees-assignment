#ifndef SEMINAR_LAB2_GRAPHS_H
#define SEMINAR_LAB2_GRAPHS_H

#include <cinttypes>


const uint64_t N_end = 5000000;
const uint64_t step = 25000;
const uint64_t simultaneous = 10000;



void measureSearch();
void measureInsert();
void measureRemove();

void launchMeasure();

#endif //SEMINAR_LAB2_GRAPHS_H
