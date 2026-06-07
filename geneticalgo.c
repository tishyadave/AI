#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_POP 100

double fitness(double x) {
    return x * sin(10 * 3.14 * x) + 1.0;
}

double rand_double(double min, double max) {
    return min + (double)rand() / RAND_MAX * (max - min);
}

int select_parent(double fit[], int size) {
    double total = 0;
    double r, sum = 0;
    int i;

    for (i = 0; i < size; i++)
        total = total + fit[i];

    r = rand_double(0, total);

    for (i = 0; i < size; i++) {
        sum = sum + fit[i];

        if (sum >= r)
            return i;
    }

    return size - 1;
}

double crossover(double p1, double p2) {
    return (p1 + p2) / 2.0;
}

double mutate(double x, double prob) {
    if ((double)rand() / RAND_MAX < prob) {
        x = x + rand_double(-0.1, 0.1);
    }

    if (x < 0)
        x = 0;

    if (x > 1)
        x = 1;

    return x;
}

void main() {
    int pop_size, generations;
    double crossover_prob, mutation_prob;
    double population[MAX_POP], new_population[MAX_POP];
    double fit[MAX_POP];
    double best_solution = 0;
    double best_fitness = -1;
    int i, gen;
    int p1, p2;
    double child;

    clrscr();

    printf("Enter population size: ");
    scanf("%d", &pop_size);

    printf("Enter number of generations: ");
    scanf("%d", &generations);

    printf("Enter crossover probability 0-1: ");
    scanf("%lf", &crossover_prob);

    printf("Enter mutation probability 0-1: ");
    scanf("%lf", &mutation_prob);

    srand(time(0));

    for (i = 0; i < pop_size; i++) {
        population[i] = rand_double(0, 1);
    }

    for (gen = 0; gen < generations; gen++) {
        for (i = 0; i < pop_size; i++) {
            fit[i] = fitness(population[i]);

            if (fit[i] > best_fitness) {
                best_fitness = fit[i];
                best_solution = population[i];
            }
        }

        for (i = 0; i < pop_size; i++) {
            p1 = select_parent(fit, pop_size);
            p2 = select_parent(fit, pop_size);

            if ((double)rand() / RAND_MAX < crossover_prob) {
                child = crossover(population[p1], population[p2]);
            } else {
                child = population[p1];
            }

            child = mutate(child, mutation_prob);
            new_population[i] = child;
        }

        for (i = 0; i < pop_size; i++) {
            population[i] = new_population[i];
        }
    }

    printf("\nBest Solution: %lf\n", best_solution);
    printf("Optimal Fitness: %lf\n", best_fitness);
    printf("Generations Taken: %d\n", generations);

    getch();
}