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
#ifndef MORTUARY_JAINTOR__H
#define MORTUARY_JAINTOR__H

#include <list>
#include <pthread.h>
#include "secretarsha_Lena.h"
class Mortuary_Jaintor{
  short m_die_status; //флаг завершения потока
  friend class secretarsha_Lena;
  static pthread_cond_t handle; //условная переменная необходимости начать работу
  static pthread_mutex_t handle_mutex; //мютекс для использования переменной
  pthread_t ctl_thr; //идентификатор потока работы
  list< secretarsha_Lena* > * List; //указатель на список за которым следить
  void ctl_thread ( ); //рабочий поток
public:
  Mortuary_Jaintor(list< secretarsha_Lena* > * llist); //конструктор
  ~Mortuary_Jaintor(); //деструктор
  static void * FstThread (void * pthis );
};


#endif //MORTUARY_JAINTOR__H