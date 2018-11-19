#include "secretarsha_Lena.h"

// Constructors/Destructors
//  

secretarsha_Lena::secretarsha_Lena ( ) {
initAttributes();
}

secretarsha_Lena::~secretarsha_Lena ( ) { }

//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  


/**
 * @return int
 */
int secretarsha_Lena::Auth ( ) {

}


/**
 * задает список проб классу.
 * в name передавать параметр по которому определяется принадлежность зондов агенту
 * на этой линии связи.
 * @return int
 * @param  name
 */
int secretarsha_Lena::setProbelist (string name ) {

}


/**
 * @return int
 */
int secretarsha_Lena::StartContact ( ) {

}


/**
 * поток с авторизацией и приемкой данных
 */
void secretarsha_Lena::mainthread ( ) {

}


/**
 * поток отправляющий агенту управляющие данные
 * -номера последовательностей всего что можно
 * -приказы создать/убить/изменить зонд
 */
void secretarsha_Lena::ctl_thread ( ) {

}

void secretarsha_Lena::initAttributes ( ) {
}

