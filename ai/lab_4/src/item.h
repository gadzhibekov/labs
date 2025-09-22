#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>
#include <ostream>

typedef std::vector<std::string> SVector;
typedef std::string              string;

struct Item
{
    Item(SVector answers, SVector value_of_answers, string question, string result, size_t index);

    Item()                                                    = default;
    ~Item()                                                   = default;

    size_t                      get_index()                     const; 
    SVector                     get_answers()                   const;
    SVector                     get_value_of_answers()          const;
    string                      get_question()                  const;
    string                      get_result()                    const;

private:
    size_t                      index; 
    SVector                     answers;
    SVector                     value_of_answers;
    string                      question;
    string                      result;
};

std::ostream& operator << (std::ostream& os, const Item& item);

#endif // ITEM_H