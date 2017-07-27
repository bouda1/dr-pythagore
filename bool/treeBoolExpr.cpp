/* Dr-Pythagore
 * Copyright (C) 2016-2017 D. Boucher
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <vector>
#include "treeBoolExpr.h"

using namespace std;
using namespace DP;

/**
 * @brief TreeBoolExpr::TreeBoolExpr Constructor with one parameter
 * @param op The operator
 * @param a The parameter
 * @param descr The description
 */
TreeBoolExpr::TreeBoolExpr(const string &op, BoolExpr *a, const string &descr)
    : BoolExpr(op, descr != "" ? descr : a->getDescr())
    , vector(1)
{
    at(0) = a;
}

/**
 * @brief TreeBoolExpr::TreeBoolExpr Constructor with two parameters
 * @param op The operator
 * @param a The first parameter
 * @param b The second parameter
 * @param descr The description
 */
TreeBoolExpr::TreeBoolExpr(const string &op, BoolExpr *a, BoolExpr *b,
                           const string &descr)
    : BoolExpr(op, descr)
    , vector(2)
{
    at(0) = a;
    at(1) = b;
}

/**
 * @brief TreeBoolExpr::TreeBoolExpr Constructor with two parameters
 * @param op The operator
 * @param a The first parameter
 * @param b The second parameter
 * @param c The third parameter
 * @param descr The description
 */
TreeBoolExpr::TreeBoolExpr(const string &op, BoolExpr *a, BoolExpr *b,
                           BoolExpr *c, const string &descr)
    : BoolExpr(op, descr)
    , vector(3)
{
    at(0) = a;
    at(1) = b;
    at(2) = c;
}

void TreeBoolExpr::findArgs(BoolTable &table)
{
    for (BoolExpr *e : *this) {
        e->findArgs(table);
    }
}
