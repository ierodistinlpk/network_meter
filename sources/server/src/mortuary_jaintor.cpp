/***************************************************************************
 *   Copyright (C) 2009 by IERO   *
 *   iero@localhost   *
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
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "mortuary_janitor.h" 
#include <cstdlib>
#include <iostream>
#include <pthread.h>
//void * Mortuary_Jaintor::FstThread (void * pthis );

Mortuary_Jaintor::Mortuary_Jaintor(list<secretarsha_Lena*> * llist):m_die_status(0),List(llist)
{
  pthread_mutex_init(&handle_mutex, NULL);
  pthread_cond_init(&handle, NULL);
  if ( ( pthread_create ( &ctl_thr, NULL, & ( Mortuary_Jaintor::FstThread ),this ) ) !=0 )
  {
    cout<<"out of resource. exiting"<<endl;
    exit(0);
  }
}
Mortuary_Jaintor::~Mortuary_Jaintor()
{
  m_die_status=1;
  pthread_mutex_lock(&Mortuary_Jaintor::handle_mutex);
  pthread_cond_signal(&Mortuary_Jaintor::handle);
  pthread_mutex_unlock(&Mortuary_Jaintor::handle_mutex);
  pthread_join(ctl_thr,NULL);
  pthread_mutex_destroy(&handle_mutex);
  pthread_cond_destroy(&handle);
}

void Mortuary_Jaintor::ctl_thread ( )
{
  pthread_mutex_lock(&handle_mutex);
  pthread_cond_wait(&handle,&handle_mutex);
  pthread_mutex_unlock(&handle_mutex);
  if(m_die_status)
    pthread_exit(NULL);
/*  for (list<secretarsha_Lena*>::iterator it=List->begin();it!=List->end();it++)
    if( (*it)->Status()==1)
  {
    delete *it;
    List->erase(it);
  }*/
}

void * Mortuary_Jaintor::FstThread (void * pthis )
{
  ((Mortuary_Jaintor*)pthis)->ctl_thread();
  return NULL;
}