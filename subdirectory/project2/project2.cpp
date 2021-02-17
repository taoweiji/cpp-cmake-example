//
// Created by Wiki on 2021/2/17.
//

#include "project2.h"
#include "project1.h"

std::string Project2::GetName() {
    return "Project2" + Project1().GetName();
}