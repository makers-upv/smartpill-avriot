/* 
 * File:   IoTPill.h
 * Author: Javier
 *
 * Created on 24 de enero de 2021, 19:33
 */

#ifndef IOTPILL_H
#define	IOTPILL_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MAX_NUM_DEPOSITS 4

typedef struct {
    char pillname[20];
    char quantity[5];
    char deposit[5];
    char weight[10];

} pilltype;

typedef struct {
    uint8_t numpill;
    char time[10];
    pilltype pill[MAX_NUM_DEPOSITS];
}datapills;


#ifdef	__cplusplus
}
#endif

#endif	/* IOTPILL_H */

