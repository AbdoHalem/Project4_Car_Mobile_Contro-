/*
 * Dio.h
 *
 *  Created on: Oct 18, 2023
 *      Author: Abdo Halem
 */

#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_

/* Includes Section */
#include "Dio_Cfg.h"

/* Macros Declarations Section */

/* Function like Macros Section */

/* Data Type Declarations Section */

/* Software Interfaces Section */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

#endif /* MCAL_DIO_DIO_H_ */
