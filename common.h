/*
* common.h
*
* Created: 02-Apr-18 10:28:35 AM
*  Author: mosta
*/


#ifndef COMMON_H_
#define COMMON_H_

#define SET_BIT_REG(PORT,BIT) (PORT|=(1<<(BIT)))
#define CLEAR_BIT_REG(PORT,BIT) ((PORT)&=~(1<<(BIT)))
#define TOGGLE_BIT_REG(PORT,BIT) ((PORT)^=(1<<(BIT)))
#define GET_BIT_REG(PORT,BIT) (((PORT)>>(BIT))&(0x01))


#define SET_BIT(BIT) ((1<<(BIT)))



#endif /* COMMON_H_ */