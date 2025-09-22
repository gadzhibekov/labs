#include "item.h"

#include <iostream>

Item::Item(SVector answers, SVector value_of_answers, string question, string result, size_t index)
    : answers(answers), value_of_answers(value_of_answers), question(question), result(result), index(index) 
    {}

size_t                      Item::get_index()               const     { return this->index; }       
SVector                     Item::get_answers()             const     { return this->answers; }
SVector                     Item::get_value_of_answers()    const     { return this->value_of_answers; }
string                      Item::get_question()            const     { return this->question; }
string                      Item::get_result()              const     { return this->result; }

std::ostream& operator << (std::ostream& os, const Item& item)
{
    os << "answers: ";
    for (int i = 0; i < item.get_answers().size(); ++i)
    {
        os << item.get_answers()[i] << " ";
    }
    os << "\n";


    os << "value_of_answers: ";
    for (int i = 0; i < item.get_value_of_answers().size(); ++i)
    {
        os << item.get_value_of_answers()[i] << " ";
    }
    os << "\n";


    os << "question: " << item.get_question() << "\n" << "index: " << item.get_index() << "\n";

    
    return os;
}