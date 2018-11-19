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
#include <string>
#include <list>
#include "../../agent_nix/src/datatypes.h"
#include "srvProbe.h"
using namespace std;
/**   структура в которой хранятся данные о состоянии прерванной сессии   */
class  SessionState{
  public:
    SessionState();
    ~SessionState();
    long long m_sessionId; //ID сессии. одинаков с клиентом
    unsigned long m_state_seq; //номер запроса получения статуса
    unsigned long m_cl_state_seq; //номер возвращенного клиентом запроса получения статуса
    unsigned long next_result;//номер ожидаемого результата
    unsigned long last_event; //номер последнего случившегося события
    unsigned long probe_count;
    unsigned long active_probe_count;
    list<ProbeState> ProbeList; //лист запущеных зондов
    timestamp_t cl_time;
    timestamp_t cl_comm_time;
    timestamp_t cl_state_time;
    unsigned long time_seek;
};