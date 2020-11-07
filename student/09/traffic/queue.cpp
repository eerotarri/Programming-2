#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle)
{
    cycle_ = cycle;
}

Queue::~Queue()
{
    while ( first_ != nullptr ) {
        Vehicle* car_to_remove = first_;
        first_ = first_->next;

        delete car_to_remove;
    }
}

void Queue::enqueue(string reg)
{
    Vehicle* new_car = new Vehicle{reg, nullptr};
    if ( first_ == nullptr ) {
        first_ = new_car;
        last_ = new_car;
    } else {
        last_->next = new_car;
        last_ = new_car;
    }

    if ( rounds_ < cycle_ ) {
        cout << "GREEN: The vehicle " << new_car->reg_num
             << " need not to stop" << endl;
        dequeue();
        rounds_ += 1;
        if ( rounds_ == cycle_p ) {
            is_green_ = false;
        }
    }

}

void Queue::dequeue()
{
    Vehicle* first_car = first_;

    if ( first_ == nullptr ) {
        return;
    } else if ( first_->next == nullptr ) {
        first_ = nullptr;
        last_ = nullptr;
    } else {
        first_ = first_->next;
    }

    delete first_car;
}

void Queue::switch_light()
{
    rounds_ = 0;

    Vehicle* car = first_;

    unsigned int cars_in_line = 0;

    string colour;

    if ( is_green_ ) {
        is_green_ = false;
        colour = "RED";
    } else {
        is_green_ = true;
        colour = "GREEN";
    }

    if ( car != nullptr ) {
        while ( car != nullptr ) {
            cars_in_line += 1;
            car = car->next;
        }
    }

    car = first_;


    if ( cars_in_line > 0 ) {
        cout << colour << ": Vehicle(s)";
        while ( rounds_ < cycle_ and car != nullptr ) {
            cout << " " << car->reg_num;
            rounds_ += 1;
            dequeue();
            car = first_;
        }
        cout << " can go on" << endl;
        if ( rounds_ == cycle_ ) {
            is_green_ = false;
        }

    } else {
        if ( is_green_ ) {
            cout << "GREEN: No vehicles waiting in traffic lights" << endl;
        } else {
            cout << "RED: No vehicles waiting in traffic lights" << endl;
        }
    }
}

void Queue::reset_cycle(unsigned int cycle)
{
    // Stub
}

void Queue::print()
{
    Vehicle* car = first_;
    if ( is_green_ ) {
        cout << "GREEN: ";
    } else {
        cout << "RED: ";
    }

    if ( car == nullptr ) {
        cout << "No vehicles waiting in traffic lights" << endl;
    } else {
        cout << "Vehicle(s)";
        while ( car != nullptr ) {
            cout << " ";
            cout << car->reg_num;
            car = car->next;
        }
        cout << " waiting in traffic lights" << endl;
    }

}
