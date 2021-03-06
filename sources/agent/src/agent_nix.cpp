/***************************************************************************
 *   Copyright (C) 2009 by IERO   *
 *   iero@lna.org.ru   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 ***************************************************************************/


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <string>
#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include "Agent.h"
#include "datatypes.h"
using namespace std;


int main(int argc, char *argv[])
{
  if ( argc!=2 )
  {
    cout<<"usage: agent_nix config.file \n        exiting.\n";
    return 0;
  }
 Agent x;
 x.ReadConfig(argv[1]);
 int exit_type=x.StartWork();
 cout << exit_type << endl;
  return exit_type;
}
